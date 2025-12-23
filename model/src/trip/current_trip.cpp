#include "trip/current_trip.hpp"
//
#include <QDebug>
#include <tuple>

#include <qdebug.h>
#include <qjsonarray.h>
#include <qjsonobject.h>
#include <qlogging.h>
#include <qmargins.h>
#include <qurl.h>

#include "backend_address.h"

#include "dto/create_trip_dto.hpp"
#include "dto/id_dto.hpp"
#include "dto/station_dto.hpp"

const QString kTripCreate = BackendConfig::Address + "/trip";
const QString kTripFinish = BackendConfig::Address + "/cargo_request/";
const QString kTripPatch  = BackendConfig::Address + "/trip";
const QString kGetRoute   = BackendConfig::Address + "/trip";
const QString kOrderFind  = BackendConfig::Address + "/cargo_request/trip";


void TCurrentTrip::startTrip(
    qreal beginLat, qreal beginLon, qreal endLat, qreal endLon
) {
    auto dto      = TCreateTripDto();
    auto startDto = TStationDto();
    startDto.address =
        QString::number(beginLat) + ";" + QString::number(beginLon);
    startDto.latitude  = beginLat;
    startDto.longitude = beginLon;
    auto finishDto     = TStationDto();
    finishDto.address = QString::number(endLat) + ";" + QString::number(endLon);
    finishDto.latitude  = endLat;
    finishDto.longitude = endLon;
    dto.from            = startDto;
    dto.to              = finishDto;
    auto createObject   = dto.toJsonObject();
    auto *reply =
        m_client->post<QJsonObject, QJsonObject>(kTripCreate, createObject);

    connect(
        reply, &reply_t::finished, this, [reply, this](const QVariant &data) {
            qDebug() << "=== CREATED TRIP ===";
            auto idDto = TIdDto(data.value<QJsonObject>());
            qDebug() << idDto.toJsonObject();
            qDebug() << "=== CREATED TRIP ===";
            emit tripCreated(idDto.id);
            QString url      = kOrderFind + "/" + idDto.id + "?";
            auto priceFilter = price();
            if (priceFilter.has_value()) {
                url += "minPrice=" + QString::number(priceFilter.value());
            }
            auto dimensionsFiltrer = dimensions();
            if (dimensionsFiltrer.has_value()) {
                const auto dim    = dimensionsFiltrer.value();
                const auto width  = std::get<0>(dim);
                const auto height = std::get<1>(dim);
                const auto length = std::get<2>(dim);
                url += "&";
                url += "cargoWidthMax=" + QString::number(width) + "&";
                url += "cargoHeightMax=" + QString::number(height) + "&";
                url += "cargoLengthMax=" + QString::number(length);
            }
            qDebug() << "url = " << url;
            auto *replyFind = m_client->get<QJsonObject>(url);

            connect(
                replyFind,
                &reply_t::finished,
                this,
                [replyFind, this](const QVariant &data) {
                    const auto jsonResponse = data.value<QJsonObject>();
                    QJsonArray jsonArray =
                        jsonResponse["cargoRequests"].toArray();
                    QList<TOrderDto> orders;
                    orders.reserve(jsonArray.size());

                    for (const auto &value : jsonArray) {
                        qDebug() << "===";
                        qDebug() << value.toObject();
                        qDebug() << "===";
                        orders.emplace_back(value.toObject());
                    }

                    qDebug() << "=== FOUND ===";
                    qDebug() << jsonArray;
                    qDebug() << orders.size();
                    qDebug() << "=== FOUND ===";

                    setRelevantOrders(orders);

                    emit tripStarted();
                    replyFind->deleteLater();    // ✅ ТОЛЬКО ЗДЕСЬ
                }
            );

            connect(
                replyFind,
                &reply_t::reply_error,
                this,
                [replyFind, this](const QString &err) {
                    qDebug() << "error:" << err;
                    emit tripError(err);
                    replyFind->deleteLater();    // ✅ ИЛИ ЗДЕСЬ
                }
            );
        }
    );

    connect(
        reply, &reply_t::reply_error, this, [reply, this](const QString &err) {
            qDebug() << "error: " << err;
            emit tripError(err);
            reply->deleteLater();
        }
    );
}


void TCurrentTrip::enterCode(int index, const QString &code) {
    // TODO
    const auto url =
        kTripFinish + "/" + currentTripId() + "/finish/code/" + code;
    QJsonObject createObject;
    auto *reply = m_client->post<QJsonObject, QJsonObject>(url, createObject);

    connect(
        reply, &reply_t::finished, this, [reply, this](const QVariant &data) {
            emit orderFinished(true);
            reply->deleteLater();
        }
    );

    connect(
        reply, &reply_t::reply_error, this, [reply, this](const QString &err) {
            orderFinished(false);
            reply->deleteLater();
        }
    );
}

void TCurrentTrip::cancelOrder(int index) {
    // TODO: make request
    finishOneOrder(index);
}

void TCurrentTrip::commitChoosen() {
    // TODO: добавить запрос на получение текущего
    const auto patchUrl = kTripPatch + "/" + currentTripId() + "/start";
    QJsonObject createObject;
    QJsonArray uuids;
    const auto list = choosenOrderIds();
    for (const auto &id : list) {
        uuids.append(id);
    }
    createObject["cargoRequest"] = uuids;
    auto *reply =
        m_client->patch<QJsonObject, QJsonObject>(patchUrl, createObject);

    connect(
        reply, &reply_t::finished, this, [reply, this](const QVariant &data) {
            emit tripStarted();
            reply->deleteLater();
        }
    );

    connect(
        reply, &reply_t::reply_error, this, [reply, this](const QString &err) {
            qDebug() << "error: " << err;
            reply->deleteLater();
        }
    );
    setStarted(true);
    emit committed();
}
