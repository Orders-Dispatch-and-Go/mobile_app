#pragma once

#include <QList>
#include <QObject>

#include <qcontainerfwd.h>
#include <qlogging.h>
#include <qtmetamacros.h>

#include "dto/create_trip_dto.hpp"
#include "dto/order_dto.hpp"
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
    ) override;

    void enterCode(int index, const QString &code) override;


    void cancelOrder(int index) override {
        finishOneOrder(index);
    }

    void commitChoosen() override;

private:
};
