#include <QPointer>

#include <qcontainerfwd.h>
#include <qjsondocument.h>
#include <qjsonobject.h>
#include <qlogging.h>
#include <qnetworkreply.h>
#include <qnetworkrequest.h>
#include <qvariant.h>

#include "dto/user_dto.hpp"
#include "utils/http_client.hpp"
#include "utils/reply.hpp"

/*
 * +-------------+
 * | Get queries |
 * +-------------+
 */

template <>
reply_t *THttpClient::get<QJsonObject>(const QString &url) {
    auto request         = create_request(url);
    QNetworkReply *reply = m_manager.get(request);

    QPointer<reply_t> typedReply = new reply_t(this);
    connect(reply, &QNetworkReply::finished, typedReply, [typedReply, reply]() {
        if (auto jsonOpt = json_from_byte_array(reply->readAll())) {
            const QJsonObject &obj = *jsonOpt;
            emit typedReply->finished(obj);
        }
        else {
            emit typedReply->reply_error(
                "Can not cast received data to type user_dto_t!"
            );
        }

        reply->deleteLater();
    });

    // Add another errors parsing

    return typedReply;
}

template <>
reply_t *THttpClient::get<bool>(const QString &url) {
    auto request         = create_request(url);
    QNetworkReply *reply = m_manager.get(request);

    QPointer<reply_t> typedReply = new reply_t(this);
    connect(reply, &QNetworkReply::finished, typedReply, [typedReply, reply]() {
        bool ok;
        bool response = reply->readAll().toInt(&ok);

        if (ok) {
            emit typedReply->finished(response);
        }
        else {
            emit typedReply->reply_error(
                "Can not cast received data to type bool!"
            );
        }

        reply->deleteLater();
    });

    return typedReply;
}

/*
 * +--------------+
 * | Post queries |
 * +--------------+
 */

template <>
reply_t *THttpClient::post<bool, QJsonObject>(
    const QString &url, const QJsonObject &data
) {
    auto request = create_request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QByteArray sendData  = QJsonDocument(data).toJson();
    QNetworkReply *reply = m_manager.post(request, sendData);

    QPointer<reply_t> typedReply = new reply_t(this);
    connect(reply, &QNetworkReply::finished, typedReply, [typedReply, reply]() {
        bool ok;
        bool response = reply->readAll().toInt(&ok);

        if (ok) {
            emit typedReply->finished(response);
        }
        else {
            emit typedReply->reply_error(
                "Can not cast received data to type bool!"
            );
        }

        reply->deleteLater();
    });

    return typedReply;
}

template <>
reply_t *THttpClient::post<QJsonObject, QJsonObject>(
    const QString &url, const QJsonObject &data
) {
    auto request = create_request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QByteArray sendData  = QJsonDocument(data).toJson();
    QNetworkReply *reply = m_manager.post(request, sendData);

    QPointer<reply_t> typedReply = new reply_t(this);
    connect(reply, &QNetworkReply::finished, typedReply, [typedReply, reply]() {
        if (auto jsonOpt = json_from_byte_array(reply->readAll())) {
            const QJsonObject &obj = *jsonOpt;
            emit typedReply->finished(obj);
        }
        else {
            emit typedReply->reply_error(
                "Can not cast received data to type QJsonObject!"
            );
        }

        reply->deleteLater();
    });

    return typedReply;
}

template <>
reply_t *
THttpClient::post<bool, QString>(const QString &url, const QString &data) {
    auto request = create_request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QByteArray sendData  = data.toUtf8();
    QNetworkReply *reply = m_manager.post(request, sendData);

    QPointer<reply_t> typedReply = new reply_t(this);
    connect(reply, &QNetworkReply::finished, typedReply, [typedReply, reply]() {
        bool ok;
        bool response = reply->readAll().toInt(&ok);

        if (ok) {
            emit typedReply->finished(response);
        }
        else {
            emit typedReply->reply_error(
                "Can not cast received data to type bool!"
            );
        }

        reply->deleteLater();
    });

    return typedReply;
}

template <>
reply_t *THttpClient::post<void>(const QString &url) {
    auto request = create_request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setHeader(QNetworkRequest::ContentLengthHeader, 0);

    QNetworkReply *reply = m_manager.post(request, nullptr);

    QPointer<reply_t> typedReply = new reply_t(this);
    connect(reply, &QNetworkReply::finished, typedReply, [typedReply, reply]() {
        QVariant var;
        emit typedReply->finished(var);

        reply->deleteLater();
    });

    return typedReply;
}


/*
 * +--------------+
 * | patch querys |
 * +--------------+
 */
template <>
reply_t *THttpClient::patch<QJsonObject, QJsonObject>(
    const QString &url, const QJsonObject &data
) {
    auto request = create_request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QByteArray sendData = QJsonDocument(data).toJson();
    QNetworkReply *reply =
        m_manager.sendCustomRequest(request, "PATCH", sendData);

    QPointer<reply_t> typedReply = new reply_t(this);
    connect(reply, &QNetworkReply::finished, typedReply, [typedReply, reply]() {
        if (auto jsonOpt = json_from_byte_array(reply->readAll())) {
            const QJsonObject &obj = *jsonOpt;
            emit typedReply->finished(obj);
        }
        else {
            emit typedReply->reply_error(
                "Can not cast received data to type QJsonObject!"
            );
        }

        reply->deleteLater();
    });

    return typedReply;
}


/*
 * +--------------------+
 * | Auxilary functions |
 * +--------------------+
 */

std::optional<QJsonObject>
THttpClient::json_from_byte_array(const QByteArray &data) {
    QJsonParseError error;
    QJsonDocument doc = QJsonDocument::fromJson(data, &error);

    if (error.error != QJsonParseError::NoError) {
        qWarning() << "Failed to parse JSON:" << error.errorString();
        return std::nullopt;
    }

    if (!doc.isObject()) {
        qWarning() << "JSON is not an object";
        return std::nullopt;
    }

    return doc.object();
}

QNetworkRequest THttpClient::create_request(const QString &url) {
    QNetworkRequest request(url);

    if (!m_jwt.isEmpty()) {
        request.setRawHeader(
            "Authorization", QByteArray("Bearer ") + m_jwt.toUtf8()
        );
    }

    return request;
}

void THttpClient::setJwt(const QString &jwt) {
    m_jwt = jwt;
}
