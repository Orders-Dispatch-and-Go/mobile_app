#pragma once

#include <QList>
#include <QObject>
#include <qcontainerfwd.h>
#include <qtmetamacros.h>

#include "dto/create_trip_dto.hpp"
#include "dto/order_dto.hpp"
#include "trip/current_trip.hpp"
#include "trip/routeinfo.hpp"

class current_trip_iface_t : public QObject {
    Q_OBJECT
public:
    current_trip_iface_t(QObject *parent = nullptr) : QObject(parent) { }

    current_trip_iface_t(const current_trip_iface_t &)            = delete;
    current_trip_iface_t(current_trip_iface_t &&)                 = delete;
    current_trip_iface_t &operator=(const current_trip_iface_t &) = delete;
    current_trip_iface_t &operator=(current_trip_iface_t &&)      = delete;
    ~current_trip_iface_t()                             override = default;

    virtual void add_order(const order_dto_t &order) = 0;

    virtual void createTrip(const TCreateTripDto &tripDto) = 0;
    virtual void getRoute(int id) = 0;

    [[nodiscard]] virtual QList<order_dto_t> orders() const = 0;

    [[nodiscard]] virtual float total_price() const = 0;

signals:
    void tripCreated(const TCurrentTrip&);
    void recvRouteForTrip(const TRouteInfo&);
    void tripError(const QString&);
};
