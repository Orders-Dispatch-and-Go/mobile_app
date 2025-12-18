#pragma once

#include <QList>
#include <QObject>

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

    virtual void addOrder(const order_dto_t &order) = 0;

    virtual void createTrip(const TCreateTripDto &tripDto) = 0;
    virtual void getRoute(int id)                          = 0;

    [[nodiscard]] virtual QList<order_dto_t> orders() const = 0;

    [[nodiscard]] virtual float totalPrice() const = 0;

signals:
    void tripCreated(const QString &id);
    void recvRouteForTrip(const TRouteInfo &);
    void tripError(const QString &);
};
