#include "auth/userinfo.hpp"


void user_info_t::set_email(const QString &email) {
    m_email = email;
}

void user_info_t::set_surname(const QString &surname) {
    m_surname = surname;
}

void user_info_t::set_name(const QString &name) {
    m_name = name;
}

void user_info_t::set_patronymic(const QString &patronymic) {
    m_patronymic = patronymic;
}

void user_info_t::set_auth_token(const QString &auth_token) {
    m_auth_token = auth_token;
}

QString user_info_t::email() const {
    return m_email;
}

QString user_info_t::surname() const {
    return m_surname;
}

QString user_info_t::name() const {
    return m_name;
}

QString user_info_t::patronymic() const {
    return m_patronymic;
}

QString user_info_t::auth_token() const {
    return m_auth_token;
}

bool user_info_t::is_valid() const {
    return !m_email.isEmpty();
}
