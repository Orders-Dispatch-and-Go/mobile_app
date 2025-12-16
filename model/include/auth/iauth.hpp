#pragma once

#include <QObject>
#include <QString>

#include <qtmetamacros.h>

#include "userinfo.hpp"

class auth_iface_t : public QObject {
    Q_OBJECT
public:
    auth_iface_t(QObject *parent = nullptr) : QObject(parent) { }

    auth_iface_t(const auth_iface_t &)            = delete;
    auth_iface_t(auth_iface_t &&)                 = delete;
    auth_iface_t &operator=(const auth_iface_t &) = delete;
    auth_iface_t &operator=(auth_iface_t &&)      = delete;
    virtual ~auth_iface_t() override              = default;    // NOLINT

    /**
     * Login with email and password.
     */
    virtual void                                          // NOLINT
    login(const QString &email, const QString &password) = 0;    // NOLINT
    /**
     * Logout.
     */
    virtual void logout() = 0;    // NOLINT

signals:
    void recv_user_info(const user_info_t&);
    void success_logout();
    void auth_error(const QString&);
    void recv_user_dto(const user_dto_t&);
};
