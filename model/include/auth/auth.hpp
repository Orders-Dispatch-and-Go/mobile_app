#pragma once

#include <qobject.h>
#include <qqmlengine.h>
#include <qurl.h>
#include <QNetworkAccessManager>
#include "userinfo.hpp"
#include "utils/http_client.hpp"
#include "auth/iauth.hpp"


class auth_t final : public auth_iface_t {
private slots:
    void error_handler(const QString &error);

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

    user_info_t login(const QString &email, const QString &password) override;
    user_info_t logout() override;

private:
    static const QString m_url_check_email;
    static const QString m_url_sign_in;
    static const QString m_url_log_out;

    http_client_t m_client;
};
