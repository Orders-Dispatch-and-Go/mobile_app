#pragma once

#include <QObject>

#include <qtmetamacros.h>

class screens_t : public QObject {
    Q_OBJECT

    Q_PROPERTY(int login READ login)
    Q_PROPERTY(int loading READ loading)
    Q_PROPERTY(int get_order READ get_order)
    Q_PROPERTY(int execute_order READ execute_order)
    Q_PROPERTY(int end_order READ end_order)
    Q_PROPERTY(int finish_route READ finish_route)
    Q_PROPERTY(int history READ history)
    Q_PROPERTY(int profile READ profile)
    Q_PROPERTY(int invalid READ invalid)

public:
    enum screens_e {
        pLogin        = 0,
        pLoading      = 1,
        pGetOrder     = 2,
        pExecuteOrder = 3,
        pEndOrder     = 4,
        pFinishRoute  = 5,
        pHistory      = 6,
        pProfile      = 7,
        pInvalid      = 8
    };
    Q_ENUM(screens_e)    // Делаем enum доступным в QML

    explicit screens_t(QObject *parent = nullptr) : QObject(parent) { }

    static int login() {
        return pLogin;
    }
    static int loading() {
        return pLoading;
    }
    static int get_order() {
        return pGetOrder;
    }
    static int execute_order() {
        return pExecuteOrder;
    }
    static int end_order() {
        return pEndOrder;
    }
    static int finish_route() {
        return pFinishRoute;
    }
    static int history() {
        return pHistory;
    }
    static int profile() {
        return pProfile;
    }
    static int invalid() {
        return pInvalid;
    }
};
