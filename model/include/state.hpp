#pragma once

#include <QObject>

#include <qtmetamacros.h>

#include "screens.hpp"

/**
 * объект для контроля того, в какой части user-story находится пользователь
 */
class state_t : public QObject {
    Q_OBJECT

    Q_PROPERTY(int currentScreen READ currentScreen)

private:
    screens_t::screens_e m_currentScreen = screens_t::pLogin;
    bool m_isLoginned                    = false;
    QList<QString> m_currentOrders;

public:
    Q_INVOKABLE [[nodiscard]] bool isPossibleMove(int screenId) const;

    Q_INVOKABLE [[nodiscard]] bool hasOrders() const {
        return !m_currentOrders.empty();
    }
    Q_INVOKABLE void addOrderId(const QString &orderId) {
        m_currentOrders.push_back(orderId);
    }
    Q_INVOKABLE void removeOrderId(const QString &orderId) {
        m_currentOrders.removeOne(orderId);
    }
    Q_INVOKABLE void setCurrentScreen(int screenId) {
        m_currentScreen = static_cast<screens_t::screens_e>(screenId);
    }

    [[nodiscard]] int currentScreen() const {
        return static_cast<int>(m_currentScreen);
    }

    [[nodiscard]] bool isLoginned() const {
        return m_isLoginned;
    }
    void setLoginned(bool isLoginned) {
        m_isLoginned = isLoginned;
    }
};
