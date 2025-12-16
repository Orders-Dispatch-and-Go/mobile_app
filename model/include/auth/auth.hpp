#pragma once

#include <qjsonobject.h>
#include <qobject.h>
#include <qqmlengine.h>
#include <qurl.h>
#include <QNetworkAccessManager>
#include "userinfo.hpp"
#include "utils/http_client.hpp"
#include "auth/iauth.hpp"
#include "dto/user_dto.hpp"


class auth_t final : public auth_iface_t {
public:
    explicit auth_t(QObject *parent = nullptr) :
        auth_iface_t(parent),
        m_client(this)
    { }
    auth_t(const auth_t &)            = delete;
    auth_t(auth_t &&)                 = delete;
    auth_t &operator=(const auth_t &) = delete;
    auth_t &operator=(auth_t &&)      = delete;
    ~auth_t() override                = default;

    void login(const QString &email, const QString &password) override;
    void logout() override;

private:
    static const QString m_url_check_email;
    static const QString m_url_sign_in;
    static const QString m_url_log_out;
    static const QString m_url_user_info;

    void get_user_info();

    void on_token_ready(const QJsonObject&);
    void on_user_ready(const QJsonObject&, const user_dto_t&);

    http_client_t m_client;
};
