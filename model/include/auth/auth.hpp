#pragma once

#include <QNetworkAccessManager>

#include <qjsonobject.h>
#include <qobject.h>
#include <qqmlengine.h>
#include <qurl.h>

#include "userinfo.hpp"

#include "auth/iauth.hpp"
#include "dto/user_dto.hpp"
#include "utils/http_client.hpp"


class TAuth final : public IAuth {
public:
    explicit TAuth(QObject *parent = nullptr)
        : IAuth(parent), m_client(this) { }
    TAuth(const TAuth &)            = delete;
    TAuth(TAuth &&)                 = delete;
    TAuth &operator=(const TAuth &) = delete;
    TAuth &operator=(TAuth &&)      = delete;
    ~TAuth() override               = default;

    void login(const QString &email, const QString &password) override;
    void logout() override;

private:
    static const QString m_url_check_email;
    static const QString m_url_sign_in;
    static const QString m_url_log_out;
    static const QString m_url_user_info;

    void get_user_info();

    void on_token_ready(const QJsonObject &);

    http_client_t m_client;
};
