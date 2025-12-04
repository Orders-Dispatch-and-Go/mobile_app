#include "utils/http_client.hpp"
#include <qcontainerfwd.h>
#include <qjsondocument.h>
#include <qjsonobject.h>
#include <qlogging.h>

template<>
bool http_client_t::get<bool>(const QString &url) {
    QNetworkRequest request(url);
    QNetworkReply *reply = m_manager.get(request);
    auto data = reply->readAll();

    bool ok;
    bool response = data.toInt(&ok);

    reply->deleteLater();

    if (!ok) {
        throw "Can not cast received data to type bool!";
    }

    return response;
}

template<>
bool http_client_t::post<bool, QJsonObject>(const QString &url, const QJsonObject &data) {
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    QByteArray send_data = QJsonDocument(data).toJson();
    QNetworkReply *reply = m_manager.post(request, send_data);
    auto recv_data = reply->readAll();

    bool ok;
    bool response = recv_data.toInt(&ok);

    reply->deleteLater();

    if (!ok) {
        qWarning() << "Can not cast received data to type bool!";
    }

    return response;
}

template<>
QJsonObject http_client_t::post<QJsonObject, QJsonObject>(const QString &url, const QJsonObject &data) {
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    QByteArray send_data = QJsonDocument(data).toJson();
    QNetworkReply *reply = m_manager.post(request, send_data);
    auto recv_data = reply->readAll();

    reply->deleteLater();
    QJsonObject obj;
    if (auto json_opt = json_from_byte_array(recv_data)) {
        QJsonObject obj = *json_opt;
        return obj;
    }
    qWarning() << "Can not cast received data to type QJsonObject!";
   
    return obj;
}

template<>
bool http_client_t::post<bool, QString>(const QString &url, const QString &data) {
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    QByteArray send_data = data.toUtf8();
    QNetworkReply *reply = m_manager.post(request, send_data);
    auto recv_data = reply->readAll();

    bool ok;
    bool response = recv_data.toInt(&ok);

    reply->deleteLater();

    if (!ok) {
        qWarning() << "Can not cast received data to type bool!";
    }

    return response;
}

std::optional<QJsonObject> http_client_t::json_from_byte_array(const QByteArray& data) {
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