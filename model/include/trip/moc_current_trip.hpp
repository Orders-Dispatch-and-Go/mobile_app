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

class TCurrentTripMoc final : public ICurrentTrip {
    Q_OBJECT
public:
    TCurrentTripMoc(THttpClient *client, QObject *parent = nullptr)
        : ICurrentTrip(parent) {
        Q_UNUSED(client);
    }

    TCurrentTripMoc(const TCurrentTripMoc &)            = delete;
    TCurrentTripMoc(TCurrentTripMoc &&)                 = delete;
    TCurrentTripMoc &operator=(const TCurrentTripMoc &) = delete;
    TCurrentTripMoc &operator=(TCurrentTripMoc &&)      = delete;
    ~TCurrentTripMoc() override                         = default;

    void startTrip(
        qreal beginLat, qreal beginLon, qreal endLat, qreal endLon
    ) override {
        Q_UNUSED(beginLat);
        Q_UNUSED(beginLon);
        Q_UNUSED(endLat);
        Q_UNUSED(endLon);
        emit tripCreated("6a014c84-c217-4f52-80c8-3fc0d12d8163");
    }

    void commitChoosen() override {
        emit committed();
    }

private:
};
