#pragma once

#include <QJsonObject>
#include <QObject>
#include <QString>
#include <utility>

class station_dto_t : public QObject {
    Q_OBJECT
    Q_PROPERTY(QString address READ address)
    Q_PROPERTY(double latitude READ latitude)
    Q_PROPERTY(double longitude READ longitude)

public:
    explicit station_dto_t(const QJsonObject &json)
        : m_address(json["address"].toString()) {
        const QJsonObject coords = json["coords"].toObject();
        m_latitude               = coords["lat"].toDouble();
        m_longitude              = coords["lon"].toDouble();
    }

    explicit station_dto_t(QString address, double latitude, double longitude)
        : m_address(std::move(address)),
          m_latitude(latitude),
          m_longitude(longitude) { }

    [[nodiscard]] QString address() const {
        return m_address;
    }
    [[nodiscard]] double latitude() const {
        return m_latitude;
    }
    [[nodiscard]] double longitude() const {
        return m_longitude;
    }

private:
    QString m_address;
    double m_latitude;
    double m_longitude;
};
