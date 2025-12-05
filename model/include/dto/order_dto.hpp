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
    Q_PROPERTY(size_t id READ getUuid)
    Q_PROPERTY(QString description READ getDescription)
    Q_PROPERTY(double startLat READ getStartLat)
    Q_PROPERTY(double startLon READ getStartLon)
    Q_PROPERTY(double finishLat READ getFinishLat)
    Q_PROPERTY(double finishLon READ getFinishLon)
    Q_PROPERTY(float price READ getPrice)
    Q_PROPERTY(float cost READ getCost)
    Q_PROPERTY(float weight READ getWeight)
    Q_PROPERTY(float length READ getLength)
    Q_PROPERTY(float height READ getHeight)
    Q_PROPERTY(float width READ getWidth)

public:
    [[nodiscard]] size_t getUuid() const {
        return m_uuid;
    }

    [[nodiscard]] float getPrice() const {
        return m_price;
    }
    [[nodiscard]] float getCost() const {
        return m_cost;
    }
    [[nodiscard]] float getWeight() const {
        return m_weight;
    }
    [[nodiscard]] float getLength() const {
        return m_length;
    }
    [[nodiscard]] float getHeight() const {
        return m_height;
    }
    [[nodiscard]] float getWidth() const {
        return m_width;
    }
    [[nodiscard]] float getVolume() const {
        return m_length * m_height * m_width;
    }
    [[nodiscard]] QString getDescription() const {
        return m_description;
    }
    [[nodiscard]] double getStartLat() const {
        return m_start.latitude;
    }
    [[nodiscard]] double getStartLon() const {
        return m_start.longitude;
    }
    [[nodiscard]] double getFinishLat() const {
        return m_finish.latitude;
    }
    [[nodiscard]] double getFinishLon() const {
        return m_finish.longitude;
    }

private:
    size_t m_uuid {};
    /// Вознаграждение за заказ
    float m_price {};
    /// Стоимость заказа
    float m_cost {};
    float m_length {};
    float m_height {};
    float m_width {};
    float m_weight {};
    /// Описание заказа
    QString m_description;
    /// Начальная остановка
    station_dto_t m_start;
    /// Конечная остановка
    station_dto_t m_finish;
};
