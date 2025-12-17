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

backend_t::backend_t(QObject *parent) : QObject(parent) {
    m_userInfoPtr   = new TUserInfo(this);    // NOLINT qt
    m_auth_model    = std::make_unique<TAuth>();
    m_profile_model = std::make_unique<moc_profile_t>();
}

void backend_t::login(const QString &email, const QString &password) {
    m_auth_model->login(email, password);

    connect(m_auth_model.get(), &IAuth::userInfoRecv, this, [this]() {
        m_userInfoPtr = m_auth_model->userInfo();
        if (m_userInfoPtr) {
            m_state.setCurrentScreen(screens_t::pStartRoute);
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

void backend_t::logout() {
    m_auth_model->logout();

    connect(&(*m_auth_model), &IAuth::successLogout, this, [this] {
        qDebug() << "Logout successfully";
        emit userLoggedOut();
        m_state.setCurrentScreen(screens_t::pLogin);
        emit screenSwitched();
    });

    connect(
        &(*m_auth_model), &IAuth::authError, this, [this](const QString &err) {
            qWarning() << err;
            // do something more smart then that
        }
    );
}

void backend_t::set_user_email(const QString &email) {
    m_userInfoPtr->setEmail(email);
    emit userUpdated();
}

void backend_t::set_user_surname(const QString &surname) {
    m_userInfoPtr->setSurname(surname);
    emit userUpdated();
}

void backend_t::set_user_name(const QString &name) {
    m_userInfoPtr->setName(name);
    emit userUpdated();
}

void backend_t::set_user_patronymic(const QString &patronymic) {
    m_userInfoPtr->setPatronymic(patronymic);
    emit userUpdated();
}

void backend_t::set_user_seria(int s) {
    m_profile_model->set_seria(s);
    emit userUpdated();
}

void backend_t::set_user_number(int n) {
    m_profile_model->set_number(n);
    emit userUpdated();
}

void backend_t::set_user_address(const QString &address) {
    m_profile_model->set_address(address);
    emit userUpdated();
}


QString backend_t::user_email() const {
    return m_userInfoPtr->getEmail();
}

QString backend_t::user_surname() const {
    return m_userInfoPtr->getSurname();
}

QString backend_t::user_name() const {
    return m_userInfoPtr->getName();
}

QString backend_t::user_patronymic() const {
    return m_userInfoPtr->getPatronymic();
}

int backend_t::user_seria() const {
    return m_profile_model->seria();
}

int backend_t::user_number() const {
    return m_profile_model->number();
}

QString backend_t::user_address() const {
    return m_profile_model->address();
}

void backend_t::switchScreen(int screen_id) {
    if (!m_state.isPossibleMove(screen_id)) {
        return;
    };
    m_state.setCurrentScreen(screen_id);
    emit screenSwitched();
}

void backend_t::startTrip() {
    qDebug() << "startTrip";
}

int backend_t::screenId() const {
    return m_state.currentScreen();
}
