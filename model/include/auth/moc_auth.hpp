#pragma once


#include "userinfo.hpp"

#include "auth/iauth.hpp"


/**
 * Ничего не делает
 */
class moc_auth_t final : public auth_iface_t {
public:
    explicit moc_auth_t(QObject *parent = nullptr) : auth_iface_t(parent) { }
    moc_auth_t(const moc_auth_t &)            = delete;
    moc_auth_t(moc_auth_t &&)                 = delete;
    moc_auth_t &operator=(const moc_auth_t &) = delete;
    moc_auth_t &operator=(moc_auth_t &&)      = delete;
    ~moc_auth_t() override                    = default;

    user_info_t login(const QString &email, const QString &password) override {
        user_info_t user;
        user.set_email(email);
        user.set_name("John");
        user.set_surname("Doe");
        return user;
    }

    user_info_t logout() override {
        return user_info_t();
    }
};
