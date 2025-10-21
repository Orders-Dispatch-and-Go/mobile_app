#include "backend.hpp"

backend_t::backend_t(QObject *parent) : QObject(parent) { }


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
