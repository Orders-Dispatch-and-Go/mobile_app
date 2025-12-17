#pragma once

#include <QJsonObject>
#include <QObject>
#include <QString>
#include <utility>
#include <qjsonobject.h>
#include <qlist.h>
#include "dto/station_dto.hpp"

struct TExtendedStationDto {
public:
    QList<station_dto_t> station;
    int distance = 0;
    int orderNum = 0;
    long arrivalAt = 0;
    long departureTime = 0;

    static TExtendedStationDto fromJson(const QJsonObject &json) {
        TExtendedStationDto dto;
        //dto.station = station_dto_t::fromJson(const QJsonObject &json)
    }
};