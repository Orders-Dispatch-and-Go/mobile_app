#include <QDebug>
#include <cstddef>

#include <qjsonobject.h>
#include <qlogging.h>
#include <qurl.h>

#include "backend_address.h"

#include "dto/create_trip_dto.hpp"
#include "dto/id_dto.hpp"
#include "dto/order_dto.hpp"
#include "dto/orders_list_dto.hpp"
#include "dto/station_dto.hpp"
#include "trip/moc_current_trip.hpp"


void TCurrentTripMoc::startTrip(
    qreal beginLat, qreal beginLon, qreal endLat, qreal endLon
) {
    Q_UNUSED(beginLat);
    Q_UNUSED(beginLon);
    Q_UNUSED(endLat);
    Q_UNUSED(endLon);
    auto order1            = TOrderDto();
    auto order1Start       = TStationDto();
    order1Start.address    = "ABACABA";
    order1Start.latitude   = 54.848820;
    order1Start.longitude  = 83.092405;
    auto order1Finish      = TStationDto();
    order1Start.address    = "Строителей 11";
    order1Finish.address   = "Строителей 14";
    order1Finish.latitude  = 54.847297;
    order1Finish.longitude = 83.092242;
    order1.start           = order1Start;
    order1.finish          = order1Finish;
    order1.uuid            = "AAAAAAAA-AAAA-AAAA-AAAA-AAAAAAAAAAAA";
    order1.cost            = 42;
    order1.price           = 1000;
    order1.weight          = 10;
    order1.width           = 100;
    order1.height          = 100;
    order1.length          = 100;
    order1.description     = "Description";
    auto order2            = TOrderDto();
    auto order2Start       = TStationDto();
    order2Start.address    = "EEEEEEE";
    order2Start.latitude   = 54.848;
    order2Start.longitude  = 83.092;
    auto order2Finish      = TStationDto();
    order2Start.address    = "Пирогова 14";
    order2Finish.address   = "Пирогова 11";
    order2Finish.latitude  = 54.847;
    order2Finish.longitude = 83.092;
    order2.start           = order2Start;
    order2.finish          = order2Finish;
    order2.uuid            = "BBBBBBBB-BBBB-AAAA-AAAA-AAAAAAAAAAAA";
    order2.cost            = 42;
    order2.price           = 999;
    order2.weight          = 19;
    order2.width           = 10;
    order1.height          = 20;
    order1.length          = 40;
    order1.description     = "Description 2";
    qDebug() << "set relevant orders";
    setRelevantOrders({ order1, order2 });

    emit tripCreated("6a014c84-c217-4f52-80c8-3fc0d12d8163");
}


void TCurrentTripMoc::commitChoosen() {
    TOrdersListDto dto;
    TOrderListItemDto order;
    order.uuid             = "AAAAAA-AAAA-AAAA-AAAA-AAAAAAAAAAAA";
    order.code             = "12345678";
    order.consignerId      = 1;
    order.recipientId      = 1;
    auto order1Start       = TStationDto();
    order1Start.address    = "Пирогова 1";
    order1Start.latitude   = 54.848820;
    order1Start.longitude  = 83.092405;
    auto order1Finish      = TStationDto();
    order1Start.address    = "Пирогова 14";
    order1Finish.latitude  = 54.847297;
    order1Finish.longitude = 83.092242;
    order.fromStation      = order1Start;
    order.toStation        = order1Finish;
    order.routeId          = "BBBBBB-CCCC-DDDD-EEEE-FFFFFFFFFF";
    order.tripId           = "QQQQQQ-CCCC-DDDD-EEEE-FFFFFFFFFF";
    order.price            = 32;
    order.status           = "NO STATUS";
    dto.orders             = { order };
    setOrdersListDto(
        dto, { QPointF(54.848820, 83.092405), QPointF(54.847297, 83.092242) }
    );
    setStarted(true);
    emit committed();
}

bool TCurrentTripMoc::enterCode(int index, const QString &code) {
    const auto dto = ordersListDtoObject();
    if (!dto.has_value()) {
        qDebug() << "no dto";
        return false;
    }
    if (index < 0 || index >= dto.value().orders.size()) {
        qDebug() << "invalid index";
        return false;
    }
    const auto &order = dto.value().orders[index];
    return order.code == code;
}
