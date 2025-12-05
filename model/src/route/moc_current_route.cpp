#include "route/moc_current_route.hpp"

void moc_current_route_t::add_order(const order_dto_t &order) {
    m_orders.push_back(order);
}

QList<order_dto_t> moc_current_route_t::orders() const {
    return m_orders;
}

float moc_current_route_t::total_price() const {
    float res = 0;
    for (const auto &order : m_orders) {
        res += order.price();
    }
    return res;
}
