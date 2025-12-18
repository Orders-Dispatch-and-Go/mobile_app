#include <qjsonobject.h>

#include "dto/create_trip_dto.hpp"
#include "dto/id_dto.hpp"
#include "trip/current_trip.hpp"

const QString TCurrentTrip::m_trip_create = "http://51.250.34.151:8074/trip";
const QString TCurrentTrip::m_get_route   = "http://51.250.34.151:8074/trip";

void TCurrentTrip::createTrip(const TCreateTripDto &tripDto) {
    auto createObject = tripDto.toJsonObject();

    auto *reply =
        m_client.post<QJsonObject, QJsonObject>(m_trip_create, createObject);

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
