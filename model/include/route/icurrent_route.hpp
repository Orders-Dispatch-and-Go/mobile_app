#pragma once

#include <QList>
#include <QObject>

#include "dto/order_dto.hpp"

class current_route_iface_t : public QObject {
public:
    current_route_iface_t(const current_route_iface_t &)            = delete;
    current_route_iface_t(current_route_iface_t &&)                 = delete;
    current_route_iface_t &operator=(const current_route_iface_t &) = delete;
    current_route_iface_t &operator=(current_route_iface_t &&)      = delete;
    virtual ~current_route_iface_t()                                = default;

    virtual void add_order(const order_dto_t &order) = 0;

    [[nodiscard]] virtual QList<order_dto_t> orders() const = 0;

    [[nodiscard]] virtual float total_price() const = 0;
};
