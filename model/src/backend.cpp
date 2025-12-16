#include <QThread>
#include <QDebug>
#include <QObject>
#include <qlogging.h>
#include <qobject.h>

#include "backend.hpp"
#include "screens.hpp"

#include "auth/auth.hpp"
#include "profile/moc_profile.hpp"

backend_t::backend_t(QObject *parent) : QObject(parent) {
    m_auth_model    = std::make_unique<auth_t>();
    m_profile_model = std::make_unique<moc_profile_t>();
}

void backend_t::login(const QString &email, const QString &password) {
    m_auth_model->login(email, password);

    connect(&(*m_auth_model), &auth_iface_t::recv_user_info, this,
        [this](const user_info_t &info) {
            qDebug() << "Login successfully";

            m_user_info = info;
            if (m_user_info.is_valid()) {
                emit user_logged_in();
                emit screen_switched(static_cast<int>(screens_t::pStartRoute));
            } else {
                // do something more smart then that
            }
        });
    
    connect(&(*m_auth_model), &auth_iface_t::auth_error, this,
        [this](const QString &err) {
            qWarning() << err;
            // do something more smart then that
        });

    m_profile_model->load();
}

void backend_t::logout() {
    m_auth_model->logout();

    connect(&(*m_auth_model), &auth_iface_t::success_logout, this,
        [this] {
            qDebug() << "Logout successfully";
            emit user_logged_out();
            emit screen_switched(static_cast<int>(screens_t::pLogin));
        });
    
    connect(&(*m_auth_model), &auth_iface_t::auth_error, this,
        [this](const QString &err) {
            qWarning() << err;
            // do something more smart then that
        });
}

void backend_t::set_user_email(const QString &email) {
    m_user_info.set_email(email);
    emit user_updated();
}

void backend_t::set_user_surname(const QString &surname) {
    m_user_info.set_surname(surname);
    emit user_updated();
}

void backend_t::set_user_name(const QString &name) {
    m_user_info.set_name(name);
    emit user_updated();
}

void backend_t::set_user_patronymic(const QString &patronymic) {
    m_user_info.set_patronymic(patronymic);
    emit user_updated();
}

void backend_t::set_user_seria(int s) {
    m_profile_model->set_seria(s);
    emit user_updated();
}

void backend_t::set_user_number(int n) {
    m_profile_model->set_number(n);
    emit user_updated();
}

void backend_t::set_user_address(const QString &address) {
    m_profile_model->set_address(address);
    emit user_updated();
}


QString backend_t::user_email() const {
    return m_user_info.email();
}

QString backend_t::user_surname() const {
    return m_user_info.surname();
}

QString backend_t::user_name() const {
    return m_user_info.name();
}

QString backend_t::user_patronymic() const {
    return m_user_info.patronymic();
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
