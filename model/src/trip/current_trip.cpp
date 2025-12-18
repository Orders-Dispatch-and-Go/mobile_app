#include <cstddef>

#include <qjsonobject.h>

#include "dto/create_trip_dto.hpp"
#include "dto/id_dto.hpp"
#include "trip/current_trip.hpp"

const QString TCurrentTrip::m_trip_create = "http://51.250.34.151:8074/trip";
const QString TCurrentTrip::m_get_route   = "http://51.250.34.151:8074/trip";

void TCurrentTrip::createTrip(const TCreateTripDto &tripDto) {
    auto createObject = tripDto.toJsonObject();

    auto *reply =
        m_client->post<QJsonObject, QJsonObject>(m_trip_create, createObject);

    connect(
        reply, &reply_t::finished, this, [reply, this](const QVariant &data) {
            auto idDto = TIdDto(data.value<QJsonObject>());
            emit tripCreated(idDto.id);
            reply->deleteLater();
        }
    );

    connect(
        reply, &reply_t::reply_error, this, [reply, this](const QString &err) {
            emit tripError(err);
            reply->deleteLater();
        }
    );
}

void TCurrentTrip::getRoute(int id) { }


void TCurrentTrip::addOrder(const order_dto_t &order) { }

QList<order_dto_t> TCurrentTrip::orders() const {
    return {};
}

float TCurrentTrip::totalPrice() const {
    return 0.0;
}

void TCurrentTrip::setFilter(
    int width, int height, int depth, int price, const QString &date
) {
    if (width > 0 && height > 0 && depth > 0) {
        m_dimensions = { width, height, depth };
    }
    else {
        m_dimensions = std::nullopt;
    }
    if (price > 0) {
        m_price = price;
    }
    else {
        m_price = std::nullopt;
    }
    if (!date.isEmpty()) {
        m_date = date;
    }
    else {
        m_date = std::nullopt;
    }
}

void TCurrentTrip::startTrip(
    qreal beginLat, qreal beginLon, qreal endLat, qreal endLon
) { }
