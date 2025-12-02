#pragma once

#include <QJsonObject>
#include <QObject>
#include <QString>
#include <utility>

struct station_dto_t {
public:
    QString address  = "";
    double latitude  = 0.0;
    double longitude = 0.0;
};
