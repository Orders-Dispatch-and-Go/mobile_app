#pragma once

#include <QJsonObject>
#include <QList>
#include <QObject>
#include <QString>

#include <qtmetamacros.h>

#include "station_dto.hpp"


/**
 * DTO for order data.
 */
struct order_dto_t {
public:
    /// Вознаграждение за заказ
    float price {};
    /// Стоимость заказа
    float cost {};
    /// Описание заказа
    QString description;
    /// Начальная остановка
    station_dto_t start;
    /// Конечная остановка
    station_dto_t finish;
};
