#pragma once


#include <qjsonarray.h>
#include <qjsonobject.h>
#include <qjsonvalue.h>

#include "dto/abstract_dto.hpp"
#include "dto/station_dto.hpp"

class TOrderListItemDto final : public TAbstractDto {
public:
    TOrderListItemDto() = default;
    TOrderListItemDto(const QJsonObject &json) {
        fromJsonObject(json);
    }
    void fromJsonObject(const QJsonObject &json) override {
        uuid        = json["id"].toString();
        consignerId = json["consignerId"].toInt();
        recipientId = json["recipientId"].toInt();
        fromStation.fromJsonObject(json["fromStation"].toObject());
        toStation.fromJsonObject(json["toStation"].toObject());
        routeId = json["routeId"].toString();
        tripId  = json["tripId"].toString();
        price   = json["price"].toDouble();
        status  = json["status"].toString();
        code    = json["code"].toString();
    }

    [[nodiscard]] QJsonObject toJsonObject() const override {
        QJsonObject json;
        json["id"]          = uuid;
        json["consignerId"] = consignerId;
        json["recipientId"] = recipientId;
        json["fromStation"] = fromStation.toJsonObject();
        json["toStation"]   = toStation.toJsonObject();
        json["routeId"]     = routeId;
        json["tripId"]      = tripId;
        json["price"]       = price;
        json["status"]      = status;
        json["code"]        = code;
        return json;
    }

    QString uuid;
    int consignerId {};
    int recipientId {};
    TStationDto fromStation;
    TStationDto toStation;
    QString routeId;
    QString tripId;
    double price {};
    QString status;
    QString code;
};

class TOrdersListDto final : public TAbstractDto {
public:
    TOrdersListDto() = default;
    TOrdersListDto(const QJsonObject &json) {
        fromJsonObject(json);
    }

    void fromJsonObject(const QJsonObject &json) override {
        QJsonArray array = json["cargoRequests"].toArray();
        for (const auto &item : array) {
            orders.append(TOrderListItemDto(item.toObject()));
        }
    }

    [[nodiscard]] QJsonObject toJsonObject() const override {
        QJsonObject json;
        QJsonArray array;
        for (const auto &order : orders) {
            array.append(order.toJsonObject());
        }
        json["cargoRequests"] = array;
        return json;
    }

    [[nodiscard]] QList<QJsonObject> ordersJson() const {
        QList<QJsonObject> jsonList;
        jsonList.reserve(orders.size());
        for (const auto &order : orders) {
            jsonList.append(order.toJsonObject());
        }
        return jsonList;
    }

    QList<TOrderListItemDto> orders;
};
