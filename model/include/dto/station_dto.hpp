#pragma once

#include <QJsonObject>
#include <QObject>
#include <QString>
#include <utility>

#include <qjsonobject.h>

#include "dto/abstract_dto.hpp"

struct TStationDto : public TAbstractDto {
public:
    QString address  = "";
    double latitude  = 0.0;
    double longitude = 0.0;

    [[nodiscard]] QJsonObject toJsonObject() const override {
        QJsonObject coordsObject;
        coordsObject["lat"] = latitude;
        coordsObject["lon"] = longitude;

        QJsonObject createObject;
        createObject["address"] = address;
        createObject["coords"]  = coordsObject;

        return createObject;
    }

    void fromJsonObject(const QJsonObject &json) override {
        address   = json["address"].toString();
        latitude  = json["coords"]["lat"].toDouble();
        longitude = json["coords"]["lon"].toDouble();
    }
};
