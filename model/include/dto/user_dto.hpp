#pragma once

#include <QString>
#include <QVector>
#include <QJsonArray>
#include <QJsonValue>
#include <QJsonValueRef>
#include <QJsonObject>

class user_dto_t {
public:
    int id = 0;
    QString email = "";
    QVector<int> roles_id;
    QString first_name = "";
    QString second_name = "";
    QString third_name = "";
    QString phone = "";
    QString birth_date = "";
    QString created_at = "";

    static user_dto_t from_json(const QJsonObject &json) {
        user_dto_t dto;
        dto.id = json["id"].toInt();
        dto.email = json["email"].toString();
        dto.first_name = json["firstName"].toString();
        dto.second_name = json["secondName"].toString();
        dto.third_name = json["thirdName"].toString();
        dto.phone = json["phone"].toString();
        dto.birth_date = json["birthDate"].toString();
        dto.created_at = json["createdAt"].toString();
        
        QJsonArray array = json["rolesId"].toArray();

        for (const QJsonValueRef &value : array) {
            dto.roles_id.append(value.toInt());
        }

        return dto;
    }
};