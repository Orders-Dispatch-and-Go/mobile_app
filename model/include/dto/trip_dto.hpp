#pragma once

#include <QJsonObject>

class TTripDto {
public:
    int id = 0;

    static TTripDto fromJson(const QJsonObject &object) {
        TTripDto dto;
        dto.id = object["id"].toInt();
        
        return dto;
    }
};