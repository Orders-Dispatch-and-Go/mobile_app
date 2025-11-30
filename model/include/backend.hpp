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
    Q_PROPERTY(
        QString userSurname READ user_surname WRITE set_user_surname NOTIFY
            user_updated
    )
    Q_PROPERTY(
        QString userName READ user_name WRITE set_user_name NOTIFY user_updated
    )
    Q_PROPERTY(
        QString userPatronymic READ user_patronymic WRITE set_user_patronymic
            NOTIFY user_updated
    )
    Q_PROPERTY(
        int userSeria READ user_seria WRITE set_user_seria NOTIFY user_updated
    )
    Q_PROPERTY(
        int userNumber READ user_number WRITE set_user_number NOTIFY
            user_updated
    )
    Q_PROPERTY(
        QString userAddress READ user_address WRITE set_user_address NOTIFY
            user_updated
    )

public:
    explicit backend_t(QObject *parent = nullptr);

    ~backend_t() override = default;

    Q_INVOKABLE void login(const QString &email, const QString &password);
    Q_INVOKABLE void logout();

    Q_INVOKABLE void set_user_email(const QString &email);
    Q_INVOKABLE void set_user_surname(const QString &surname);
    Q_INVOKABLE void set_user_name(const QString &name);
    Q_INVOKABLE void set_user_patronymic(const QString &patronymic);
    Q_INVOKABLE void set_user_seria(int s);
    Q_INVOKABLE void set_user_number(int n);
    Q_INVOKABLE void set_user_address(const QString &address);

    Q_INVOKABLE [[nodiscard]] QString user_email() const;
    Q_INVOKABLE [[nodiscard]] QString user_surname() const;
    Q_INVOKABLE [[nodiscard]] QString user_name() const;
    Q_INVOKABLE [[nodiscard]] QString user_patronymic() const;
    Q_INVOKABLE [[nodiscard]] int user_seria() const;
    Q_INVOKABLE [[nodiscard]] int user_number() const;
    Q_INVOKABLE [[nodiscard]] QString user_address() const;

    Q_INVOKABLE void switch_screen(int screen_id) {
        emit screen_switched(screen_id);
    }

private:
    Q_DISABLE_COPY_MOVE(backend_t)
    user_info_t m_user_info;

    std::unique_ptr<auth_iface_t> m_auth_model;
    std::unique_ptr<profile_iface_t> m_profile_model;

public:
signals:
    /// сигнал о том что надо переключиться на какой то экран
    void screen_switched(int screen_id);
    void user_updated();
    void user_logged_in();
    void user_logged_out();
};

#endif
