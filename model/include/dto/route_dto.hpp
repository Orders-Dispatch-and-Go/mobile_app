#pragma once

#include <QObject>

#include "dto/order_dto.hpp"

class route_t : public QObject {
    Q_OBJECT

public:
    explicit route_t();

private:
    QList<order_dto_t> m_orders;
};
