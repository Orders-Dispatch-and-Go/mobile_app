#pragma once

#include <QJsonObject>
#include <QObject>
#include <QString>

#include <qjsonobject.h>
#include <qlist.h>

#include "dto/abstract_dto.hpp"
#include "dto/station_dto.hpp"

struct TExtendedStationDto : public TAbstractDto {
public:
    QList<TStationDto> station;
    int distance       = 0;
    int orderNum       = 0;
    long arrivalAt     = 0;
    long departureTime = 0;

    void fromJsonObject(const QJsonObject &json) override {
        // TExtendedStationDto dto;
        // dto.station = station_dto_t::fromJson(const QJsonObject &json)
    }
    [[nodiscard]] QJsonObject toJsonObject() const override {
        QJsonObject json;
        return json;
    }
};
