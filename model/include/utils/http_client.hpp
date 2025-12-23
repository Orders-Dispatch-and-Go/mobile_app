#pragma once

#include <QJsonDocument>
#include <QNetworkReply>

#include <qcontainerfwd.h>
#include <qjsonobject.h>
#include <qnetworkaccessmanager.h>
#include <qnetworkrequest.h>

#include "dto/user_dto.hpp"
#include "utils/reply.hpp"

class THttpClient : public QObject {
    Q_OBJECT
public:
    explicit THttpClient(QObject *parent = nullptr) : QObject(parent) { }

    template <typename T>
    reply_t *get(const QString &url);

    /**
     * Template function to post data to the server.
     *
     * @tparam T тип возвращаемого ответа
     * @tparam U тип отправляемых данных
     * @param url The URL to post the data to.
     * @param data The data to be posted.
     * @return A pointer to the reply object.
     */
    template <typename T, typename U>
    reply_t *post(const QString &url, const U &data);

    template <typename T, typename U>
    reply_t *patch(const QString &url, const U &data);

    template <typename T>
    reply_t *post(const QString &url);

    void setJwt(const QString &jwt);

private:
    QNetworkAccessManager m_manager;
    QString m_jwt;

    static std::optional<QJsonObject>
    json_from_byte_array(const QByteArray &data);
    QNetworkRequest create_request(const QString &url);
};
