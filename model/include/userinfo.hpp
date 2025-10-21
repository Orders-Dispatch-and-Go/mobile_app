#ifndef USERINFO_HPP
#define USERINFO_HPP

#include <QObject>

#include <qobject.h>

/**
 * @brief Объект, хранящий информацию о авторизованном пользователе
 */
class user_info_t {
public:
    explicit user_info_t()                      = default;
    user_info_t(const user_info_t &)            = default;
    user_info_t(user_info_t &&)                 = delete;
    user_info_t &operator=(const user_info_t &) = default;
    user_info_t &operator=(user_info_t &&)      = delete;
    ~user_info_t()                              = default;

    void set_email(const QString &email);
    void set_surname(const QString &surname);
    void set_name(const QString &name);
    void set_patronymic(const QString &patronymic);

    [[nodiscard]] QString email() const;
    [[nodiscard]] QString surname() const;
    [[nodiscard]] QString name() const;
    [[nodiscard]] QString patronymic() const;

private:
    QString m_email      = "";
    QString m_surname    = "";
    QString m_name       = "";
    QString m_patronymic = "";
};

#endif
