#include <QDebug>
#include <cstddef>

#include <qjsonobject.h>
#include <qlogging.h>
#include <qurl.h>

#include "backend_address.h"

#include "dto/create_trip_dto.hpp"
#include "dto/id_dto.hpp"
#include "dto/station_dto.hpp"
#include "trip/moc_current_trip.hpp"


void TCurrentTripMoc::createTrip(const TCreateTripDto &tripDto) {
    auto createObject = tripDto.toJsonObject();

    auto *reply =
        m_client->post<QJsonObject, QJsonObject>(m_trip_create, createObject);

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
            emit tripError(err);
            reply->deleteLater();
        }
    );
}

void TCurrentTripMoc::getRoute(int id) { }


void TCurrentTripMoc::addOrderId(const QString &orderId) { }

QList<TOrderDto> TCurrentTripMoc::orders() const {
    return {};
}

float TCurrentTripMoc::totalPrice() const {
    return 0.0;
}

void TCurrentTripMoc::setFilter(
    int width, int height, int depth, int price, const QString &date
) {
    if (width > 0 && height > 0 && depth > 0) {
        m_dimensions = { width, height, depth };
    }
    else {
        m_dimensions = std::nullopt;
    }
    if (price > 0) {
        m_price = price;
    }
    else {
        m_price = std::nullopt;
    }
    if (!date.isEmpty()) {
        m_date = date;
    }
    else {
        m_date = std::nullopt;
    }
}

void TCurrentTripMoc::startTrip(
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
    createTrip(dto);
}
