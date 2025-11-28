#include <QDebug>

#include "backend.hpp"
#include "screens.hpp"

#include "auth/moc_auth.hpp"
#include "profile/moc_profile.hpp"

backend_t::backend_t(QObject *parent) : QObject(parent) {
    m_auth_model    = std::make_unique<moc_auth_t>();
    m_profile_model = std::make_unique<moc_profile_t>();
}

void backend_t::login(const QString &email, const QString &password) {
    m_user_info = m_auth_model->login(email, password);
    m_profile_model->load();
    if (m_user_info.is_valid()) {
        emit user_logged_in();
        emit screen_switched(SCREEN_MAIN);
    }
}

void backend_t::logout() {
    m_user_info = m_auth_model->logout();
    emit user_logged_out();
}

void backend_t::set_user_email(const QString &email) {
    m_user_info.set_email(email);
}

void backend_t::set_user_surname(const QString &surname) {
    m_user_info.set_surname(surname);
}

void backend_t::set_user_name(const QString &name) {
    m_user_info.set_name(name);
}

void backend_t::set_user_patronymic(const QString &patronymic) {
    m_user_info.set_patronymic(patronymic);
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
