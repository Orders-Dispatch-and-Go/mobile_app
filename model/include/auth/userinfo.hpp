#pragma once

#include <QObject>

#include <qobject.h>
#include <qtmetamacros.h>

#include "dto/user_dto.hpp"

/**
 * @brief Объект, хранящий информацию о авторизованном пользователе
 */
class TUserInfo : public QObject {
    Q_OBJECT
    Q_PROPERTY(int id READ getId)
    Q_PROPERTY(QString email READ getEmail)
    Q_PROPERTY(QString surname READ getSurname)
    Q_PROPERTY(QString name READ getName)
    Q_PROPERTY(QString patronymic READ getPatronymic)
    Q_PROPERTY(QString authToken READ getAuthToken)
    Q_PROPERTY(bool valid READ isValid)

public:
    explicit TUserInfo(
        const user_dto_t &dto, QString token, QObject *parent = nullptr
    );
    explicit TUserInfo(QObject *parent = nullptr) : QObject(parent) { }

    void setId(int id);
    void setEmail(const QString &email);
    void setSurname(const QString &surname);
    void setName(const QString &name);
    void setPatronymic(const QString &patronymic);
    void setAuthToken(const QString &auth_token);

    [[nodiscard]] int getId() const;
    [[nodiscard]] QString getEmail() const;
    [[nodiscard]] QString getSurname() const;
    [[nodiscard]] QString getName() const;
    [[nodiscard]] QString getPatronymic() const;
    [[nodiscard]] QString getAuthToken() const;

    [[nodiscard]] bool isValid() const;

private:
    int m_id             = 0;
    QString m_email      = "";
    QString m_surname    = "";
    QString m_name       = "";
    QString m_patronymic = "";
    QString m_authToken  = "";
};
