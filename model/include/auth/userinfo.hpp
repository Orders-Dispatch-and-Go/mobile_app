#ifndef USERINFO_HPP
#define USERINFO_HPP

#include <QObject>

#include <qobject.h>

/**
 * @brief Объект, хранящий информацию о авторизованном пользователе
 */
class user_info_t {
public:
    explicit user_info_t() = default;

    void set_email(const QString &email);
    void set_surname(const QString &surname);
    void set_name(const QString &name);
    void set_patronymic(const QString &patronymic);
    void set_auth_token(const QString &auth_token);

    [[nodiscard]] QString email() const;
    [[nodiscard]] QString surname() const;
    [[nodiscard]] QString name() const;
    [[nodiscard]] QString patronymic() const;
    [[nodiscard]] QString auth_token() const;

    [[nodiscard]] bool is_valid() const;

private:
    QString m_email      = "";
    QString m_surname    = "";
    QString m_name       = "";
    QString m_patronymic = "";
    QString m_auth_token = "";
};

#endif
