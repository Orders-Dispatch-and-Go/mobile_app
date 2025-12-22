#pragma once

#include <QList>
#include <QObject>
#include <numeric>

#include <qcontainerfwd.h>
#include <qjsonobject.h>
#include <qlogging.h>
#include <qtmetamacros.h>
#include <qvariant.h>

#include "dto/create_trip_dto.hpp"
#include "dto/order_dto.hpp"
#include "dto/orders_list_dto.hpp"
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
    Q_INVOKABLE virtual void
    startTrip(qreal beginLat, qreal beginLon, qreal endLat, qreal endLon) = 0;

    /**
     * надо сделать запрос на наполнение маршрута заявками, поставить isStarted
     * после чего кинуть commited()
     */
    Q_INVOKABLE virtual void commitChoosen() = 0;

    Q_INVOKABLE [[nodiscard]] float totalPrice() const {
        return std::accumulate(
            m_relevantOrders.begin(),
            m_relevantOrders.end(),
            0.0f,
            [](float sum, const TOrderDto &dto) { return sum + dto.price; }
        );
    }

    Q_INVOKABLE void resetFilter() {
        m_dimensions = std::nullopt;
        m_price      = std::nullopt;
    }

    Q_INVOKABLE void setFilter(int width, int height, int depth, int price) {
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
    }

    Q_INVOKABLE void setLoadedOrders(const QList<TOrderDto> &orders) {
        m_relevantOrders = orders;
    }

    /**
     * Добавить выбранный id выбранного заказа к поездке
     */
    Q_INVOKABLE void addOrderId(const QString &orderId) {
        m_choosenOrderIds.push_back(orderId);
    }

    Q_INVOKABLE void removeOrderFormRelative(int index) {
        if (index >= 0 && index < m_relevantOrders.size()) {
            m_relevantOrders.remove(index);
        }
    }
    Q_INVOKABLE void chooseOrderFormRelative(int index) {
        if (index >= 0 && index < m_relevantOrders.size()) {
            m_orders.push_back(m_relevantOrders[index]);
            m_choosenOrderIds.push_back(m_relevantOrders[index].uuid);
            m_relevantOrders.remove(index);
        }
    }

    void finishOneOrder(int index) {
        if (index >= 0 && index < m_orders.size()) {
            m_finished[index] = true;
        }
    }

    virtual bool enterCode(int index, const QString &code) = 0;
    virtual void completeOrder(int index)                  = 0;
    virtual void cancelOrder(int index)                    = 0;

    [[nodiscard]] QList<bool> finishedOrders() const {
        return m_finished;
    }

    [[nodiscard]] std::optional<TOrdersListDto> ordersListDtoObject() const {
        return m_ordersListDto;
    }

    void setOrdersListDto(
        const TOrdersListDto &dto, const QList<QPointF> &waypoints
    ) {
        m_ordersListDto = dto;
        m_waypoints     = waypoints;
        m_finished.resize(dto.orders.size());
        m_finished.fill(false);
    }

    void clearOrdersList() {
        m_ordersListDto = std::nullopt;
        m_finished.clear();
        m_waypoints.clear();
    }

    [[nodiscard]] QList<QPointF> waypoints() const {
        return m_waypoints;
    }
    [[nodiscard]] QVariantList ordersListDto() const {
        if (m_ordersListDto.has_value()) {
            QVariantList list;
            const auto &objects = m_ordersListDto.value().ordersJson();
            for (const auto &object : objects) {
                list.append(QVariant::fromValue(object));
            }
            return list;
        }
        return {};
    }

    void setStarted(bool started) {
        m_isStarted = started;
    }

    void setOrders(const QList<TOrderDto> &orders) {
        m_orders = orders;
    }

    void setRelevantOrders(const QList<TOrderDto> &orders) {
        m_relevantOrders = orders;
    }

    QString currentTripId() {
        return m_currentTripId;
    }

    [[nodiscard]] QList<QString> choosenOrderIds() const {
        return m_choosenOrderIds;
    }

    [[nodiscard]] QList<TOrderDto> relevantOrders() const {
        return m_relevantOrders;
    }

    [[nodiscard]] QList<TOrderDto> orders() const {
        return m_orders;
    }

    [[nodiscard]] bool isStarted() const {
        return m_isStarted;
    }

    [[nodiscard]] std::optional<std::tuple<int, int, int>> dimensions() const {
        return m_dimensions;
    }

    [[nodiscard]] std::optional<int> price() const {
        return m_price;
    }

signals:
    void committed();
    void tripCreated(const QString &id);
    void recvRouteForTrip(const TRouteInfo &);
    void tripError(const QString &);

private:
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

    std::optional<TOrdersListDto> m_ordersListDto = std::nullopt;
    QList<bool> m_finished;
    QList<QPointF> m_waypoints;
};
