#include <QDebug>

#include "screens.hpp"
#include "state.hpp"


bool state_t::isPossibleMove(int screenId) const {
    return true;    // TODO: DEBUG ONLY
    qDebug() << static_cast<int>(m_currentScreen) << " -> " << screenId;
    if (m_currentScreen == screenId) {
        return true;
    }
    switch (screenId) {
    case TScreens::pInvalid:
    case TScreens::pLogin:
        return true;
    case TScreens::pStartRoute:
        return m_isLoginned && (m_currentScreen == TScreens::pLogin)
               || (m_currentScreen == TScreens::pLogin)
               || (m_currentScreen == TScreens::pFinishRoute);
    case TScreens::pProfile:
    case TScreens::pGetOrders:
        // этот экран доступен только зарегестрированным
        return m_isLoginned && (m_currentScreen == TScreens::pStartRoute);
    case TScreens::pFinishOrder:
        // этот экран доступен только зарегестрированным и если есть заказы
        return m_isLoginned && (m_currentScreen == TScreens::pCurrentRoute)
               && !m_currentOrders.empty();
    case TScreens::pFinishRoute:
        return m_isLoginned && m_currentOrders.empty();
    case TScreens::pCurrentRoute:
        return m_isLoginned && !m_currentOrders.empty()
               && (m_currentScreen == TScreens::pGetOrders
                   || m_currentScreen == TScreens::pFinishOrder);
    default:
        return false;
    }
    return false;
}
