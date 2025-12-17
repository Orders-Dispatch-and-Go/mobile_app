#pragma once

#include <qcontainerfwd.h>
#include <qjsonobject.h>
#include <qnetworkaccessmanager.h>
#include <qnetworkrequest.h>
#include "dto/user_dto.hpp"
#include "utils/reply.hpp"
#include <QJsonDocument>
#include <QNetworkReply>

class http_client_t : public QObject
{
    Q_OBJECT
public:
    explicit http_client_t(QObject *parent = nullptr) : QObject(parent) {}

    template<typename T>
    reply_t *get(const QString &url);

    template<typename T, typename U>
    reply_t *post(const QString &url, const U &data);

    template<typename T>
    reply_t *post(const QString &url);

    void setJwt(const QString &jwt);
    
private:
    QNetworkAccessManager m_manager;
    QString m_jwt;

    static std::optional<QJsonObject> json_from_byte_array(const QByteArray& data);
    QNetworkRequest create_request(const QString &url);
};