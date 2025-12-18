#pragma once

#include <QList>
#include <QObject>

#include <qcontainerfwd.h>
#include <qtmetamacros.h>

#include "dto/create_trip_dto.hpp"
#include "dto/order_dto.hpp"
#include "dto/trip_dto.hpp"
#include "trip/icurrent_trip.hpp"
#include "utils/http_client.hpp"

class TCurrentTrip final : public ICurrentTrip {
    Q_OBJECT
public:
    TCurrentTrip(THttpClient *client, QObject *parent = nullptr)
        : ICurrentTrip(parent), m_client(client) { }

    TCurrentTrip(const TCurrentTrip &)            = delete;
    TCurrentTrip(TCurrentTrip &&)                 = delete;
    TCurrentTrip &operator=(const TCurrentTrip &) = delete;
    TCurrentTrip &operator=(TCurrentTrip &&)      = delete;
    ~TCurrentTrip() override                      = default;

    void createTrip(const TCreateTripDto &tripDto) override;
    void getRoute(int id) override;
    void addOrder(const order_dto_t &order) override;

    [[nodiscard]] QList<order_dto_t> orders() const override;

    [[nodiscard]] float totalPrice() const override;

    void setFilter(
        int width, int height, int depth, int price, const QString &date
    ) override;

    void startTrip(
        qreal beginLat, qreal beginLon, qreal endLat, qreal endLon
    ) override;

    void setUserId(int id) override;

private:
    static const QString m_trip_create;
    static const QString m_get_route;

    /**
     * @brief Ограничения (опционально) по габаритам (ширина, высота, глубина)
     */
    std::optional<std::tuple<int, int, int>> m_dimensions;

    /**
     * @brief Ограничения по цене
     */
    std::optional<int> m_price;

    /**
     * @brief Ограничения по дате
     */
    std::optional<QString> m_date;

    int m_userId = -1;

    THttpClient *m_client;
};
