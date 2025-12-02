#pragma once

#include <QObject>

#include <qtmetamacros.h>

class screens_t : public QObject {
    Q_OBJECT

    Q_PROPERTY(int login READ login)
    Q_PROPERTY(int profile READ profile)
    Q_PROPERTY(int invalid READ invalid)
    Q_PROPERTY(int start_route READ start_route)
    Q_PROPERTY(int get_orders READ get_orders)
    Q_PROPERTY(int finish_order READ finish_order)
    Q_PROPERTY(int finish_route READ finish_route)

public:
    enum screens_e {
        pInvalid     = 0,
        pLogin       = 1,
        pStartRoute  = 2,
        pGetOrders   = 3,
        pFinishOrder = 4,
        pFinishRoute = 5,
        pProfile     = 6
    };
    Q_ENUM(screens_e)    // Делаем enum доступным в QML

    explicit screens_t(QObject *parent = nullptr) : QObject(parent) { }

    static int login() {
        return pLogin;
    }
    static int profile() {
        return pProfile;
    }
    static int invalid() {
        return pInvalid;
    }
    static int start_route() {
        return pStartRoute;
    }
    static int get_orders() {
        return pGetOrders;
    }
    static int finish_order() {
        return pFinishOrder;
    }
    static int finish_route() {
        return pFinishRoute;
    }
};
