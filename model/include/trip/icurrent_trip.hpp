#pragma once

#include <QList>
#include <QObject>
#include <numeric>

#include <qcontainerfwd.h>
#include <qtmetamacros.h>

#include "dto/create_trip_dto.hpp"
#include "dto/order_dto.hpp"
#include "trip/routeinfo.hpp"


class ICurrentTrip : public QObject {
    Q_OBJECT
public:
    ICurrentTrip(QObject *parent = nullptr);

    ICurrentTrip(const ICurrentTrip &)            = delete;
    ICurrentTrip(ICurrentTrip &&)                 = delete;
    ICurrentTrip &operator=(const ICurrentTrip &) = delete;
    ICurrentTrip &operator=(ICurrentTrip &&)      = delete;
    virtual ~ICurrentTrip() override              = default;

    /**
     * начала поездrи
     */
    virtual void
    startTrip(qreal beginLat, qreal beginLon, qreal endLat, qreal endLon) = 0;

    /**
     * надо сделать запрос на наполнение маршрута заявками, поставить isStarted
     * после чего кинуть commited()
     */
    virtual void commitChoosen() = 0;

    [[nodiscard]] float totalPrice() const {
        return std::accumulate(
            m_relevantOrders.begin(),
            m_relevantOrders.end(),
            0.0f,
            [](float sum, const TOrderDto &dto) { return sum + dto.price; }
        );
    }

    [[nodiscard]] QList<TOrderDto> orders() const {
        return m_relevantOrders;
    }

    void resetFilter() {
        m_dimensions = std::nullopt;
        m_price      = std::nullopt;
        m_date       = std::nullopt;
    }

    void setFilter(
        int width, int height, int depth, int price, const QString &date
    ) {
        if (width > 0 && height > 0 && depth > 0) {
            m_dimensions = { width, height, depth };
        }
        else {
            m_dimensions = std::nullopt;
        }
        if (price > 0) {
            m_price = price;
        }
        else {
            m_price = std::nullopt;
        }
        if (!date.isEmpty()) {
            m_date = date;
        }
        else {
            m_date = std::nullopt;
        }
    }

    void setLoadedOrders(const QList<TOrderDto> &orders) {
        m_relevantOrders = orders;
    }

    /**
     * Добавить выбранный id выбранного заказа к поездке
     */
    void addOrderId(const QString &orderId) {
        m_choosenOrderIds.push_back(orderId);
    }

    void chooseOrderFormRelative(int index) {
        if (index >= 0 && index < m_relevantOrders.size()) {
            m_orders.push_back(m_relevantOrders[index]);
            m_choosenOrderIds.push_back(m_relevantOrders[index].uuid);
        }
    }


signals:
    void committed();
    void tripCreated(const QString &id);
    void recvRouteForTrip(const TRouteInfo &);
    void tripError(const QString &);

protected:
    // ID поездки
    QString m_currentTripId;    // NOLINT
    // ID заказов, которые будут добавлен
    QList<QString> m_choosenOrderIds;    // NOLINT
    // Заказы, которые можно выбрать
    QList<TOrderDto> m_relevantOrders;    // NOLINT
    // по факту выбранные заказы
    QList<TOrderDto> m_orders;    // NOLINT

    bool m_isStarted = false;    // NOLINT

    // === параметры фильтрации ===
    /**
     * @brief Ограничения (опционально) по габаритам (ширина, высота, глубина)
     */
    std::optional<std::tuple<int, int, int>> m_dimensions;    // NOLINT

    /**
     * @brief Ограничения по цене
     */
    std::optional<int> m_price;    // NOLINT

    /**
     * @brief Ограничения по дате
     */
    std::optional<QString> m_date;    // NOLINT
};
