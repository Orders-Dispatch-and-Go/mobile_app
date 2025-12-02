#pragma once

#include "route/icurrent_route.hpp"

class moc_current_route_t : public current_route_iface_t {
public:
    moc_current_route_t(const moc_current_route_t &)            = delete;
    moc_current_route_t(moc_current_route_t &&)                 = delete;
    moc_current_route_t &operator=(const moc_current_route_t &) = delete;
    moc_current_route_t &operator=(moc_current_route_t &&)      = delete;
    ~moc_current_route_t() override                             = default;

    void add_order(const order_dto_t &order) override;
    [[nodiscard]] QList<order_dto_t> orders() const override;
    [[nodiscard]] float total_price() const override;

private:
    QList<order_dto_t> m_orders;
};
