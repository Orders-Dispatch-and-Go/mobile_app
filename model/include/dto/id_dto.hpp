#pragma once


#include <qjsonobject.h>

#include "dto/abstract_dto.hpp"

class TIdDto : public TAbstractDto {
public:
    QString id;

    explicit TIdDto(const QJsonObject &json) {
        fromJsonObject(json);
    }

    void fromJsonObject(const QJsonObject &json) override {
        id = json["id"].toString();
    }
    [[nodiscard]] QJsonObject toJsonObject() const override {
        QJsonObject json;
        json["id"] = id;
        return json;
    }
};
