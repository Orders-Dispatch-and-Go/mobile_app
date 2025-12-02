#pragma once

#include <QObject>

#include "dto/order_dto.hpp"

struct route_t {
public:
    QList<order_dto_t> orders;
};
