#pragma once

#include <QObject>
#include <stdexcept>

#include <qdatetime.h>
#include <qjsonobject.h>

#include "dto/abstract_dto.hpp"
#include "dto/station_dto.hpp"

class TCreateTripDto : public TAbstractDto {
public:
    TStationDto from;
    TStationDto to;
    QString startedAt;

    [[nodiscard]] QJsonObject toJsonObject() const override {
        QJsonObject createObject;
        createObject["fromStation"] = from.toJsonObject();
        createObject["toStation"]   = to.toJsonObject();
        createObject["startedAt"] =
            QDateTime::currentDateTimeUtc().toString(Qt::ISODate);
        return createObject;
    }

    void fromJsonObject(const QJsonObject &json) override {
        throw std::invalid_argument(
            "CreateTripDto::fromJsonObject() used only to send data"
        );
    }
};
