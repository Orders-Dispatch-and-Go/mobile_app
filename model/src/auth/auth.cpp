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

const QString TAuth::m_url_check_email =
    "http://51.250.34.151:8074/check/email";
const QString TAuth::m_url_sign_in   = "http://51.250.34.151:8074/auth/sign_in";
const QString TAuth::m_url_log_out   = "http://51.250.34.151:8074/auth/logout";
const QString TAuth::m_url_user_info = "http://51.250.34.151:8074/users";

/*
 * +----------------+
 * | Login pipeline |
 * +----------------+
 */

void TAuth::login(const QString &email, const QString &password) {
    QJsonObject signInObj;
    signInObj["login"]    = email;
    signInObj["password"] = password;

    auto *reply =
        m_client->post<QJsonObject, QJsonObject>(m_url_sign_in, signInObj);

    connect(
        reply, &reply_t::finished, this, [reply, this](const QVariant &data) {
            on_token_ready(data.value<QJsonObject>());
            reply->deleteLater();
        }
    );

    connect(
        reply, &reply_t::reply_error, this, [reply, this](const QString &err) {
            emit authError(err);
            reply->deleteLater();
        }
    );
}

void TAuth::on_token_ready(const QJsonObject &token_object) {
    auto token = token_object["accessToken"].toString();
    m_client->setJwt(token);

    auto *reply = m_client->get<QJsonObject>(m_url_user_info);

    connect(
        reply,
        &reply_t::finished,
        this,
        [token, reply, this](const QVariant &data) {
            auto userObject = data.value<QJsonObject>();
            auto dto        = user_dto_t::from_json(userObject);

            createUserInfo(token, dto);
            reply->deleteLater();
        }
    );

    connect(
        reply, &reply_t::reply_error, this, [reply, this](const QString &err) {
            emit authError(err);
            reply->deleteLater();
        }
    );
}

/*
 * +-----------------+
 * | Logout pipeline |
 * +-----------------+
 */

void TAuth::logout() {
    auto *reply = m_client->post<void>(m_url_log_out);

    connect(reply, &reply_t::finished, this, [reply, this] {
        emit successLogout();
        reply->deleteLater();
    });

    connect(
        reply, &reply_t::reply_error, this, [reply, this](const QString &err) {
            emit authError(err);
            reply->deleteLater();
        }
    );
}

/*
 * +---------+
 * | Getters |
 * +---------+
 */

void TAuth::get_user_info() {
    auto *reply = m_client->get<QJsonObject>(m_url_user_info);

    connect(
        reply, &reply_t::finished, this, [reply, this](const QVariant &data) {
            emit userDtoRecv(user_dto_t::from_json(data.value<QJsonObject>()));
            reply->deleteLater();
        }
    );

    connect(
        reply, &reply_t::reply_error, this, [reply, this](const QString &err) {
            emit authError(err);
            reply->deleteLater();
        }
    );
}
