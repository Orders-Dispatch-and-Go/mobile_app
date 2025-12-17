#include <QDebug>

#include "screens.hpp"
#include "state.hpp"


bool state_t::isPossibleMove(int screenId) const {
    // return true;    // TODO: DEBUG ONLY
    qDebug() << static_cast<int>(m_currentScreen) << " -> " << screenId;
    if (m_currentScreen == screenId) {
        return true;
    }
    switch (screenId) {
    case screens_t::pInvalid:
    case screens_t::pLogin:
        return true;
    case screens_t::pStartRoute:
        return m_isLoginned && (m_currentScreen == screens_t::pLogin)
               || (m_currentScreen == screens_t::pLogin)
               || (m_currentScreen == screens_t::pFinishRoute);
    case screens_t::pProfile:
    case screens_t::pGetOrders:
        // этот экран доступен только зарегестрированным
        return m_isLoginned && (m_currentScreen == screens_t::pStartRoute);
    case screens_t::pFinishOrder:
        // этот экран доступен только зарегестрированным и если есть заказы
        return m_isLoginned && (m_currentScreen == screens_t::pCurrentRoute)
               && !m_currentOrders.empty();
    case screens_t::pFinishRoute:
        return m_isLoginned && m_currentOrders.empty();
    case screens_t::pCurrentRoute:
        return m_isLoginned && !m_currentOrders.empty()
               && (m_currentScreen == screens_t::pGetOrders
                   || m_currentScreen == screens_t::pFinishOrder);
    default:
        return false;
    }
    return false;
}
