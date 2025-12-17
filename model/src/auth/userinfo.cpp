#include "auth/userinfo.hpp"


TUserInfo::TUserInfo(const user_dto_t &dto, QString token, QObject *parent)
    : QObject(parent),
      m_id(dto.id),
      m_email(dto.email),
      m_surname(dto.second_name),
      m_name(dto.first_name),
      m_patronymic(dto.third_name),
      m_authToken(std::move(token)) { }

void TUserInfo::setId(int id) {
    m_id = id;
}

void TUserInfo::setEmail(const QString &email) {
    m_email = email;
}

void TUserInfo::setSurname(const QString &surname) {
    m_surname = surname;
}

void TUserInfo::setName(const QString &name) {
    m_name = name;
}

void TUserInfo::setPatronymic(const QString &patronymic) {
    m_patronymic = patronymic;
}

void TUserInfo::setAuthToken(const QString &auth_token) {
    m_authToken = auth_token;
}

int TUserInfo::getId() const {
    return m_id;
}
QString TUserInfo::getEmail() const {
    return m_email;
}

QString TUserInfo::getSurname() const {
    return m_surname;
}

QString TUserInfo::getName() const {
    return m_name;
}

QString TUserInfo::getPatronymic() const {
    return m_patronymic;
}

QString TUserInfo::getAuthToken() const {
    return m_authToken;
}

bool TUserInfo::isValid() const {
    return !m_authToken.isEmpty();
}
