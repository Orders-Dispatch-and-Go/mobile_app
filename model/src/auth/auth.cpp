#include <QJsonObject>

#include <qcontainerfwd.h>
#include <qjsondocument.h>
#include <qjsonobject.h>
#include <qnetworkrequest.h>
#include <qurl.h>
#include <qvariant.h>

#include "auth/auth.hpp"
#include "auth/userinfo.hpp"
#include "dto/user_dto.hpp"
#include "utils/reply.hpp"

const QString auth_t::m_url_check_email =
    "http://51.250.34.151:8074/check/email";
const QString auth_t::m_url_sign_in = "http://51.250.34.151:8074/auth/sign_in";
const QString auth_t::m_url_log_out = "http://51.250.34.151:8074/auth/logout";
const QString auth_t::m_url_user_info = "http://51.250.34.151:8074/users";

/*
 * +----------------+
 * | Login pipeline |
 * +----------------+
 */

void auth_t::login(const QString &email, const QString &password) {
    QJsonObject sign_in_obj;
    sign_in_obj["login"]    = email;
    sign_in_obj["password"] = password;

    auto *reply =
        m_client.post<QJsonObject, QJsonObject>(m_url_sign_in, sign_in_obj);

    connect(
        reply, &reply_t::finished, this, [reply, this](const QVariant &data) {
            on_token_ready(data.value<QJsonObject>());
            reply->deleteLater();
        }
    );

    connect(
        reply, &reply_t::reply_error, this, [reply, this](const QString &err) {
            emit auth_error(err);
            reply->deleteLater();
        }
    );
}

void auth_t::on_token_ready(const QJsonObject &token_object) {
    auto *reply = m_client.get<QJsonObject>(m_url_user_info);

    connect(
        reply,
        &reply_t::finished,
        this,
        [token_object, reply, this](const QVariant &data) {
            auto userObject = data.value<QJsonObject>();
            auto dto        = user_dto_t::from_json(userObject);

            on_user_ready(token_object, dto);
            reply->deleteLater();
        }
    );

    connect(
        reply, &reply_t::reply_error, this, [reply, this](const QString &err) {
            emit auth_error(err);
            reply->deleteLater();
        }
    );
}

void auth_t::on_user_ready(
    const QJsonObject &token_object, const user_dto_t &dto
) {
    auto token     = token_object["accessToken"].toString();
    auto user_info = user_info_t::from_user_dto(dto);
    user_info.set_auth_token(token);

    emit recv_user_info(user_info);
}

/*
 * +-----------------+
 * | Logout pipeline |
 * +-----------------+
 */

void auth_t::logout() {
    auto *reply = m_client.post<void>(m_url_log_out);

    connect(reply, &reply_t::finished, this, [reply, this] {
        emit success_logout();
        reply->deleteLater();
    });

    connect(
        reply, &reply_t::reply_error, this, [reply, this](const QString &err) {
            emit auth_error(err);
            reply->deleteLater();
        }
    );
}

/*
 * +---------+
 * | Getters |
 * +---------+
 */

void auth_t::get_user_info() {
    auto *reply = m_client.get<QJsonObject>(m_url_user_info);

    connect(
        reply, &reply_t::finished, this, [reply, this](const QVariant &data) {
            auto user_object = data.value<QJsonObject>();
            user_dto_t dto   = user_dto_t::from_json(user_object);

            emit recv_user_dto(dto);
            reply->deleteLater();
        }
    );

    connect(
        reply, &reply_t::reply_error, this, [reply, this](const QString &err) {
            emit auth_error(err);
            reply->deleteLater();
        }
    );
}
