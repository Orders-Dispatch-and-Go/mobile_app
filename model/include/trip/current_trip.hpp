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

class TCurrentTrip final : public current_trip_iface_t {
    Q_OBJECT
public:
    TCurrentTrip(QObject *parent = nullptr)
        : current_trip_iface_t(parent), m_client(this) { }

    TCurrentTrip(const TCurrentTrip &)            = delete;
    TCurrentTrip(TCurrentTrip &&)                 = delete;
    TCurrentTrip &operator=(const TCurrentTrip &) = delete;
    TCurrentTrip &operator=(TCurrentTrip &&)      = delete;
    ~TCurrentTrip()                     override = default;

    void createTrip(const TCreateTripDto &tripDto) override;
    void getRoute(int id) override;
    void add_order(const order_dto_t &order) override;

    [[nodiscard]] QList<order_dto_t> orders() const override;

    [[nodiscard]] float total_price() const override;

private:
    static const QString m_trip_create;
    static const QString m_get_route;

    http_client_t m_client;

    void onTripCreated(const TTripDto&);
    void onRecvRoute(const )
};
