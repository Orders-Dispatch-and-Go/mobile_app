#pragma once

#include <QJsonObject>
#include <QList>
#include <QObject>
#include <QString>

#include <qjsonobject.h>
#include <qsharedpointer.h>
#include <qtmetamacros.h>

#include "station_dto.hpp"

#include "dto/abstract_dto.hpp"


/**
 * DTO for order data.
 */
class TOrderDto : public TAbstractDto {
public:
    TOrderDto() = default;

    explicit TOrderDto(const QJsonObject &json) {
        fromJsonObject(json);
    }


    void fromJsonObject(const QJsonObject &json) override {
        id = json["id"].toString();
        fromStation.fromJsonObject(json["fromStation"].toObject());
        toStation.fromJsonObject(json["toStation"].toObject());
        status = json["status"].toString();
        code   = json["receiveCode"].toString();
        worth  = static_cast<float>(json["worth"].toDouble());
        weight = json["weight"].toInt();
        width  = json["width"].toInt();
        height = json["height"].toInt();
        length = json["length"].toInt();
        price  = std::stof(json["price"].toString().toStdString());
    }

    [[nodiscard]] QJsonObject toJsonObject() const override {
        QJsonObject obj;
        obj["id"]          = id;
        obj["price"]       = QString::number(price);
        obj["worth"]       = worth;
        obj["length"]      = length;
        obj["height"]      = height;
        obj["width"]       = width;
        obj["weight"]      = weight;
        obj["fromStation"] = fromStation.toJsonObject();
        obj["toStation"]   = toStation.toJsonObject();
        obj["status"]      = status;
        obj["code"]        = code;
        return obj;
    }

    QString id;
    int length {};
    int height {};
    int width {};
    int weight {};
    TStationDto fromStation;
    TStationDto toStation;
    float price {};
    float worth {};
    QString status;
    QString code;
};
