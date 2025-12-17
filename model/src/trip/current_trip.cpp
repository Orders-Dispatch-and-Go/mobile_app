#include "trip/current_trip.hpp"
#include <qjsonobject.h>
#include "dto/create_trip_dto.hpp"

const QString TCurrentTrip::m_trip_create = "http://51.250.34.151:8074/trip";
const QString TCurrentTrip::m_get_route = "http://51.250.34.151:8074/trip";

void TCurrentTrip::createTrip(const TCreateTripDto &tripDto) {
    auto createObject = TCreateTripDto::toJsonObject(tripDto);

    auto *reply =
        m_client.post<QJsonObject, QJsonObject>(m_trip_create, createObject);

    connect(
        reply, &reply_t::finished, this, [reply, this](const QVariant &data) {
            emit tripCreated(data.value<QJsonObject>());
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

void TCurrentTrip::getRoute(int id) {

}