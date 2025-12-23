#include <QDebug>
#include <QObject>
#include <QThread>

#include <qlogging.h>
#include <qobject.h>

#include "backend.hpp"
#include "screens.hpp"

#include "auth/auth.hpp"
#include "auth/userinfo.hpp"
#include "profile/moc_profile.hpp"
#include "trip/current_trip.hpp"
#include "trip/icurrent_trip.hpp"
#include "trip/moc_current_trip.hpp"

TBackend::TBackend(QObject *parent) : QObject(parent) {
    m_httpClient     = new THttpClient(this);                   // NOLINT
    m_currentTripPtr = new TCurrentTrip(m_httpClient, this);    // NOLINT qt
    m_userInfoPtr    = new TUserInfo(this);                     // NOLINT qt
    m_auth_model     = new TAuth(m_httpClient, this);           // NOLINT
    m_profile_model  = std::make_unique<moc_profile_t>();
    connect(
        m_currentTripPtr,
        &ICurrentTrip::tripCreated,
        this,
        [this](const QString &tripId) {
            m_state.setCurrentScreen(TScreens::pGetOrders);
            emit screenSwitched();
        }
    );
    connect(m_currentTripPtr, &ICurrentTrip::committed, this, [this]() {
        m_state.setCurrentScreen(TScreens::pCurrentRoute);
        emit routeUpdated();
        emit screenSwitched();
    });
    connect(this, &TBackend::routeUpdated, this, &TBackend::onRouteUpdated);
    connect(
        m_currentTripPtr,
        &ICurrentTrip::orderFinished,
        this,
        &TBackend::enterCodeSuccess
    );
}

void TBackend::login(const QString &email, const QString &password) {
    m_auth_model->login(email, password);

    connect(m_auth_model, &IAuth::userInfoRecv, this, [this]() {
        m_userInfoPtr = m_auth_model->userInfo();
        if (m_userInfoPtr->isValid()) {
            qDebug() << m_userInfoPtr->getId();
            qDebug() << m_userInfoPtr->getAuthToken();
            m_state.setCurrentScreen(TScreens::pStartRoute);
            emit screenSwitched();
            emit userLoggedIn();
            return;
        }
        emit userLoginFailed();
    });

    connect(
        &(*m_auth_model), &IAuth::authError, this, [this](const QString &err) {
            qWarning() << err;
            // do something more smart then that
        }
    );

    m_profile_model->load();
}

void TBackend::logout() {
    m_auth_model->logout();

    connect(m_auth_model, &IAuth::successLogout, this, [this] {
        qDebug() << "Logout successfully";
        emit userLoggedOut();
        m_state.setCurrentScreen(TScreens::pLogin);
        emit screenSwitched();
    });

    connect(m_auth_model, &IAuth::authError, this, [this](const QString &err) {
        qWarning() << err;
        // do something more smart then that
    });
}

void TBackend::set_user_email(const QString &email) {
    m_userInfoPtr->setEmail(email);
    emit userUpdated();
}

void TBackend::set_user_surname(const QString &surname) {
    m_userInfoPtr->setSurname(surname);
    emit userUpdated();
}

void TBackend::set_user_name(const QString &name) {
    m_userInfoPtr->setName(name);
    emit userUpdated();
}

void TBackend::set_user_patronymic(const QString &patronymic) {
    m_userInfoPtr->setPatronymic(patronymic);
    emit userUpdated();
}

void TBackend::set_user_seria(int s) {
    m_profile_model->set_seria(s);
    emit userUpdated();
}

void TBackend::set_user_number(int n) {
    m_profile_model->set_number(n);
    emit userUpdated();
}

void TBackend::set_user_address(const QString &address) {
    m_profile_model->set_address(address);
    emit userUpdated();
}


QString TBackend::user_email() const {
    return m_userInfoPtr->getEmail();
}

QString TBackend::user_surname() const {
    return m_userInfoPtr->getSurname();
}

QString TBackend::user_name() const {
    return m_userInfoPtr->getName();
}

QString TBackend::user_patronymic() const {
    return m_userInfoPtr->getPatronymic();
}

int TBackend::user_seria() const {
    return m_profile_model->seria();
}

int TBackend::user_number() const {
    return m_profile_model->number();
}

QString TBackend::user_address() const {
    return m_profile_model->address();
}

void TBackend::switchScreen(int screen_id) {
    if (!m_state.isPossibleMove(screen_id)) {
        return;
    };
    m_state.setCurrentScreen(screen_id);
    emit screenSwitched();
}

void TBackend::setupFilter(int width, int height, int depth, int price) {
    m_currentTripPtr->setFilter(width, height, depth, price);
}

void TBackend::startTrip(
    qreal beginLat, qreal beginLon, qreal endLat, qreal endLon
) {
    m_currentTripPtr->startTrip(beginLat, beginLon, endLat, endLon);
}


[[nodiscard]] QVariantList TBackend::getOrders() const {
    QVariantList list;
    const auto orders = m_currentTripPtr->orders();
    for (const TOrderDto &o : orders) {
        list.append(o.toJsonObject());
    }
    return list;
}

[[nodiscard]] QVariantList TBackend::getRelevantOrders() const {
    QVariantList list;
    const auto orders = m_currentTripPtr->relevantOrders();
    for (const TOrderDto &o : orders) {
        list.append(o.toJsonObject());
    }
    return list;
}

void TBackend::acceptRelevant(int index) {
    m_currentTripPtr->chooseOrderFormRelative(index);
    emit ordersUpdated();
}

void TBackend::rejectRelevant(int index) {
    m_currentTripPtr->removeOrderFormRelative(index);
    emit ordersUpdated();
}

void TBackend::commitTrip() {
    m_currentTripPtr->commitChoosen();
    emit routeUpdated();
}

int TBackend::screenId() const {
    return m_state.currentScreen();
}

QList<QPointF> TBackend::getWaypoints() const {
    return m_currentTripPtr->waypoints();
}

QVariantList TBackend::getStops() const {
    return m_currentTripPtr->ordersListDto();
}

QList<bool> TBackend::finishedOrders() const {
    return m_currentTripPtr->finishedOrders();
}


Q_INVOKABLE void TBackend::cancelOrder(int index) {
    m_currentTripPtr->cancelOrder(index);
    emit routeUpdated();
}

bool TBackend::hasOrders() const {
    const auto finished = m_currentTripPtr->finishedOrders();
    qDebug() << finished;
    for (int i = 0; i < finished.size(); ++i) {
        if (!finished[i])
            return true;
    }
    return false;
}


void TBackend::enterCode(int index, const QString &code) {
    m_currentTripPtr->enterCode(index, code);
    emit routeUpdated();
}
void TBackend::startNewTrip() {
    m_state.setCurrentScreen(TScreens::pStartRoute);
    emit screenSwitched();
}

void TBackend::onRouteUpdated() {
    qDebug() << "onRouteUpdated";
    if (!hasOrders()) {
        qDebug() << "No orders";
        m_state.setCurrentScreen(TScreens::pFinishRoute);
        emit screenSwitched();
    }
}
