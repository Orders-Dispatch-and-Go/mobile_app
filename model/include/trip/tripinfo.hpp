#pragma once

#include <qjsonobject.h>

#include "dto/order_dto.hpp"
#include "dto/trip_dto.hpp"
#include "trip/routeinfo.hpp"

class TTripInfo {
public:
    int id = 0;
    TRouteInfo route;
    QList<TOrderDto> orders;

    static TTripInfo fromTripDto(const TTripDto &dto) {
        TTripInfo info;
        info.id = dto.id;

        return info;
    }
};
