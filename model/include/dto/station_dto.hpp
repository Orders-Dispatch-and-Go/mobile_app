#pragma once

#include <QJsonObject>
#include <QObject>
#include <QString>
#include <utility>
#include <qjsonobject.h>

struct station_dto_t {
public:
    QString address  = "";
    double latitude  = 0.0;
    double longitude = 0.0;

    static QJsonObject toJsonObject(const station_dto_t &dto) {
        QJsonObject coordsObject;
        coordsObject["lat"] = dto.latitude;
        coordsObject["lon"] = dto.longitude;

        QJsonObject createObject;
        createObject["address"] = dto.address;
        createObject["coords"] = coordsObject;

        return createObject;
    }

    static station_dto_t fromJson(const QJsonObject &json) {
        station_dto_t dto;
        dto.address = json["address"].toString();
        dto.latitude = json["coords"]["lat"].toDouble();
        dto.longitude = json["coords"]["lon"].toDouble();

        return dto;
    }
};
