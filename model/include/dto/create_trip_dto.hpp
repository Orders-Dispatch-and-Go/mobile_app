#pragma once

#include <QObject>
#include <qdatetime.h>
#include <qjsonobject.h>

#include "dto/order_dto.hpp"
#include "dto/station_dto.hpp"

class TCreateTripDto {
public:
    int carrierId = 0;
    station_dto_t from;
    station_dto_t to;
    QString startedAt;

    static QJsonObject toJsonObject(const TCreateTripDto &dto) {
        QJsonObject createObject;
        createObject["carrier"] = dto.carrierId;
        createObject["fromStation"] = station_dto_t::toJsonObject(dto.from);
        createObject["toStation"] = station_dto_t::toJsonObject(dto.to);
        createObject["startedAt"] = QDateTime::currentDateTime().toString(Qt::ISODate);

        return createObject;
    }
};
