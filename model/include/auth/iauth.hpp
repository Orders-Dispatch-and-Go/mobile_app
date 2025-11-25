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
    virtual user_info_t                                          // NOLINT
    login(const QString &email, const QString &password) = 0;    // NOLINT
    /**
     * Logout.
     */
    virtual user_info_t logout() = 0;    // NOLINT
};
