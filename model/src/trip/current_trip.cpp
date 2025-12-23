#include "trip/current_trip.hpp"
//
#include <QDebug>

#include <qjsonarray.h>
#include <qjsonobject.h>
#include <qlogging.h>
#include <qurl.h>

#include "backend_address.h"

#include "dto/create_trip_dto.hpp"
#include "dto/id_dto.hpp"
#include "dto/station_dto.hpp"

const QString kTripCreate = BackendConfig::Address + "/trip";
const QString kTripFinish = BackendConfig::Address + "/cargo_request/";
const QString kTripPatch  = BackendConfig::Address + "/trip";
const QString kGetRoute   = BackendConfig::Address + "/trip";


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
    qDebug() << dto.toJsonObject();
    auto createObject = dto.toJsonObject();
    auto *reply =
        m_client->post<QJsonObject, QJsonObject>(kTripCreate, createObject);

    connect(
        reply, &reply_t::finished, this, [reply, this](const QVariant &data) {
            auto idDto = TIdDto(data.value<QJsonObject>());
            qDebug() << data;
            qDebug() << "id = " << idDto.id;
            emit tripCreated(idDto.id);
            reply->deleteLater();
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
