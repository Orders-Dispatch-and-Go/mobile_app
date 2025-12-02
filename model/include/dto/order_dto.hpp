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
class order_dto_t : public QObject {
    Q_OBJECT
    Q_PROPERTY(float price READ price)
    Q_PROPERTY(float cost READ cost)
    Q_PROPERTY(QString description READ description)
    Q_PROPERTY(station_dto_t start READ start)
    Q_PROPERTY(station_dto_t finish READ finish)

public:
    order_dto_t(const QJsonObject &json);

    [[nodiscard]] float price() const {
        return m_price;
    }
    [[nodiscard]] float cost() const noexcept {
        return m_cost;
    }
    [[nodiscard]] const QString &description() const noexcept {
        return m_description;
    }
    [[nodiscard]] const station_dto_t &start() const noexcept {
        return m_start;
    }
    [[nodiscard]] const station_dto_t &finish() const noexcept {
        return m_finish;
    }

private:
    /// Вознаграждение за заказ
    float m_price;
    /// Стоимость заказа
    float m_cost;
    /// Описание заказа
    QString m_description;
    /// Начальная остановка
    station_dto_t m_start;
    /// Конечная остановка
    station_dto_t m_finish;
};
