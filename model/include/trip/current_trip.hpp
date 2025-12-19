#pragma once

#include <QList>
#include <QObject>

#include <qcontainerfwd.h>
#include <qtmetamacros.h>

#include "dto/create_trip_dto.hpp"
#include "trip/icurrent_trip.hpp"
#include "utils/http_client.hpp"

class TCurrentTrip final : public ICurrentTrip {
    Q_OBJECT
public:
    TCurrentTrip(THttpClient *client, QObject *parent = nullptr)
        : ICurrentTrip(parent), m_client(client) { }

    TCurrentTrip(const TCurrentTrip &)            = delete;
    TCurrentTrip(TCurrentTrip &&)                 = delete;
    TCurrentTrip &operator=(const TCurrentTrip &) = delete;
    TCurrentTrip &operator=(TCurrentTrip &&)      = delete;
    ~TCurrentTrip() override                      = default;

    void startTrip(
        qreal beginLat, qreal beginLon, qreal endLat, qreal endLon
    ) override;

    void commitChoosen() override;

private:
    static const QString m_trip_create;
    static const QString m_get_route;

    THttpClient *m_client;
};
