#pragma once


#include <qjsonarray.h>
#include <qjsonobject.h>
#include <qjsonvalue.h>
#include <qlogging.h>

#include "dto/abstract_dto.hpp"
#include "dto/order_dto.hpp"
#include "dto/station_dto.hpp"


class TOrdersListDto final : public TAbstractDto {
public:
    TOrdersListDto() = default;
    TOrdersListDto(const QJsonObject &json) {
        fromJsonObject(json);
    }

    void fromJsonObject(const QJsonObject &json) override {
        QJsonArray array = json["stations"].toArray();
        qDebug() << array;
        for (const auto &item : array) {
            qDebug() << "===";
            const QJsonObject o = item.toObject();
            qDebug() << o;
            orders.emplace_back(o);
            qDebug() << "===";
        }
    }

    [[nodiscard]] QJsonObject toJsonObject() const override {
        QJsonObject json;
        QJsonArray array;
        for (const auto &order : orders) {
            array.append(order.toJsonObject());
        }
        json["stations"] = array;
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

    QList<TOrderDto> orders;
};
