#include "auth/auth.hpp"
#include <qcontainerfwd.h>
#include <qjsondocument.h>
#include <qnetworkrequest.h>
#include <qurl.h>
#include "auth/userinfo.hpp"
#include <QJsonObject>

const QString auth_t::m_url_check_email = "http://51.250.34.151:8074/check/email";
const QString auth_t::m_url_sign_in = "http://51.250.34.151:8074/auth/sign_in";
const QString auth_t::m_url_log_out = "http://51.250.34.151:8074/auth/logout";

user_info_t auth_t::login(const QString &email, const QString &password) {
    bool is_email_valid = m_client.post<bool, QString>(m_url_check_email, email);

    if (!is_email_valid) {
        qDebug() << "Email is invalid";
        user_info_t user;
        return user;
    }

    QJsonObject sign_in_obj;
    sign_in_obj["login"] = email;
    sign_in_obj["password"] = password;

    auto token_object = m_client.post<QJsonObject, QJsonObject>(m_url_sign_in, sign_in_obj);

    user_info_t user;
    user.set_email(email);
    user.set_name("John");
    user.set_surname("Doe");
    user.set_auth_token(token_object["accessToken"].toString());
    return user;
}

user_info_t auth_t::logout() {
    m_client.post<void>(m_url_log_out);
    user_info_t user;
    return user;
}