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


    void fromJsonObject(const QJsonObject &json) override { }

    [[nodiscard]] QJsonObject toJsonObject() const override {
        QJsonObject obj;

        obj["price"] = price;
        return obj;
    }

    QString uuid;
    /// Вознаграждение за заказ
    float price {};
    /// Стоимость заказа
    float cost {};
    float length {};
    float height {};
    float width {};
    float weight {};
    /// Описание заказа
    QString description;
    /// Начальная остановка
    TStationDto start;
    /// Конечная остановка
    TStationDto finish;
};
