#pragma once

#include <QObject>

#include <qtmetamacros.h>

class screens_t : public QObject {
    Q_OBJECT

    Q_PROPERTY(int login READ login)
    Q_PROPERTY(int profile READ profile)
    Q_PROPERTY(int invalid READ invalid)
    Q_PROPERTY(int startRoute READ startroute)
    Q_PROPERTY(int getOrders READ getorders)
    Q_PROPERTY(int finishOrder READ finishorder)
    Q_PROPERTY(int finishRoute READ finishroute)

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
    static int startroute() {
        return pStartRoute;
    }
    static int getorders() {
        return pGetOrders;
    }
    static int finishorder() {
        return pFinishOrder;
    }
    static int finishroute() {
        return pFinishRoute;
    }
};
