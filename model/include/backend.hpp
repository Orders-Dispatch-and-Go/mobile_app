#ifndef BACKEND_HPP
#define BACKEND_HPP

#include <QObject>

#include <memory.h>
#include <qtmetamacros.h>

#include "auth/iauth.hpp"
#include "auth/userinfo.hpp"
#include "profile/iprofile.hpp"


/**
 * @brief Backend class for the application.
 * Available from any QML component as "backend" property.
 */
class backend_t : public QObject {
    Q_OBJECT

    Q_PROPERTY(QString userEmail READ user_email)
    Q_PROPERTY(QString userSurname READ user_surname)
    Q_PROPERTY(QString userName READ user_name)
    Q_PROPERTY(QString userPatronymic READ user_patronymic)
    Q_PROPERTY(int userSeria READ user_seria)
    Q_PROPERTY(int userNumber READ user_number)
    Q_PROPERTY(QString userAddress READ user_address)

public:
    explicit backend_t(QObject *parent = nullptr);

    ~backend_t() override = default;

    Q_INVOKABLE void login(const QString &email, const QString &password);
    Q_INVOKABLE void logout();

    Q_INVOKABLE void set_user_email(const QString &email);
    Q_INVOKABLE void set_user_surname(const QString &surname);
    Q_INVOKABLE void set_user_name(const QString &name);
    Q_INVOKABLE void set_user_patronymic(const QString &patronymic);

    Q_INVOKABLE [[nodiscard]] QString user_email() const;
    Q_INVOKABLE [[nodiscard]] QString user_surname() const;
    Q_INVOKABLE [[nodiscard]] QString user_name() const;
    Q_INVOKABLE [[nodiscard]] QString user_patronymic() const;
    Q_INVOKABLE [[nodiscard]] int user_seria() const;
    Q_INVOKABLE [[nodiscard]] int user_number() const;
    Q_INVOKABLE [[nodiscard]] QString user_address() const;

private:
    Q_DISABLE_COPY_MOVE(backend_t)
    user_info_t m_user_info;

    std::unique_ptr<auth_iface_t> m_auth_model;
    std::unique_ptr<profile_iface_t> m_profile_model;

public:
signals:
    /// сигнал о том что надо переключиться на какой то экран
    void screen_switched(int screen_id);
    void user_logged_in();
    void user_logged_out();
};

#endif
