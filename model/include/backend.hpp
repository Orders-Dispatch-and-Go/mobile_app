#ifndef BACKEND_HPP
#define BACKEND_HPP

#include <QList>
#include <QObject>

#include <memory.h>
#include <qqml.h>
#include <qtmetamacros.h>

#include "state.hpp"

#include "auth/iauth.hpp"
#include "auth/userinfo.hpp"
#include "dto/order_dto.hpp"
#include "profile/iprofile.hpp"
#include "trip/icurrent_trip.hpp"
#include "utils/http_client.hpp"


/**
 * @brief Backend class for the application.
 * Available from any QML component as "backend" property.
 */
class TBackend : public QObject {
    Q_OBJECT
    QML_ELEMENT

    Q_PROPERTY(QString userEmail READ user_email)
    Q_PROPERTY(
        QString userSurname READ user_surname WRITE set_user_surname NOTIFY
            userUpdated
    )
    Q_PROPERTY(
        QString userName READ user_name WRITE set_user_name NOTIFY userUpdated
    )
    Q_PROPERTY(
        QString userPatronymic READ user_patronymic WRITE set_user_patronymic
            NOTIFY userUpdated
    )
    Q_PROPERTY(
        int userSeria READ user_seria WRITE set_user_seria NOTIFY userUpdated
    )
    Q_PROPERTY(
        int userNumber READ user_number WRITE set_user_number NOTIFY userUpdated
    )
    Q_PROPERTY(
        QString userAddress READ user_address WRITE set_user_address NOTIFY
            userUpdated
    )
    Q_PROPERTY(QVariantList userOrders READ getOrders NOTIFY ordersUpdated)
    Q_PROPERTY(
        QVariantList relevantOrders READ getRelevantOrders NOTIFY ordersUpdated
    )
    Q_PROPERTY(int screenId READ screenId)

    Q_PROPERTY(QList<QPointF> waypoints READ getWaypoints NOTIFY routeUpdated)
    Q_PROPERTY(QVariantList stops READ getStops NOTIFY routeUpdated)
    Q_PROPERTY(QList<bool> finished READ finishedOrders NOTIFY routeUpdated)
    Q_PROPERTY(bool hasOrders READ hasOrders NOTIFY routeUpdated)

public:
    explicit TBackend(QObject *parent = nullptr);

    ~TBackend() override = default;

    Q_INVOKABLE void login(const QString &email, const QString &password);
    Q_INVOKABLE void logout();

    Q_INVOKABLE void set_user_email(const QString &email);
    Q_INVOKABLE void set_user_surname(const QString &surname);
    Q_INVOKABLE void set_user_name(const QString &name);
    Q_INVOKABLE void set_user_patronymic(const QString &patronymic);
    Q_INVOKABLE void set_user_seria(int s);
    Q_INVOKABLE void set_user_number(int n);
    Q_INVOKABLE void set_user_address(const QString &address);

    Q_INVOKABLE [[nodiscard]] QString user_email() const;
    Q_INVOKABLE [[nodiscard]] QString user_surname() const;
    Q_INVOKABLE [[nodiscard]] QString user_name() const;
    Q_INVOKABLE [[nodiscard]] QString user_patronymic() const;
    Q_INVOKABLE [[nodiscard]] int user_seria() const;
    Q_INVOKABLE [[nodiscard]] int user_number() const;
    Q_INVOKABLE [[nodiscard]] QString user_address() const;

    Q_INVOKABLE void switchScreen(int screen_id);


    Q_INVOKABLE void setupFilter(int width, int height, int depth, int price);

    Q_INVOKABLE void
    startTrip(qreal beginLat, qreal beginLon, qreal endLat, qreal endLon);

    Q_INVOKABLE [[nodiscard]] QVariantList getRelevantOrders() const;
    Q_INVOKABLE [[nodiscard]] QVariantList getOrders() const;
    Q_INVOKABLE void acceptRelevant(int index);
    Q_INVOKABLE void rejectRelevant(int index);

    Q_INVOKABLE void commitTrip();

    Q_INVOKABLE [[nodiscard]] bool isPossibleMove(int screenId) const {
        return m_state.isPossibleMove(screenId);
    }

    Q_INVOKABLE [[nodiscard]] int screenId() const;

    /// маршрут
    [[nodiscard]] QList<QPointF> getWaypoints() const;
    /// список dto остановок
    [[nodiscard]] QVariantList getStops() const;
    [[nodiscard]] QList<bool> finishedOrders() const;
    Q_INVOKABLE void cancelOrder(int index);
    [[nodiscard]] bool hasOrders() const;

    Q_INVOKABLE void enterCode(int index, const QString &code);

    Q_INVOKABLE void startNewTrip();

    void onRouteUpdated();

private:
    Q_DISABLE_COPY_MOVE(TBackend)
    THttpClient *m_httpClient      = nullptr;
    TUserInfo *m_userInfoPtr       = nullptr;    // владелец - Auth
    ICurrentTrip *m_currentTripPtr = nullptr;
    state_t m_state {};

    IAuth *m_auth_model;
    std::unique_ptr<profile_iface_t> m_profile_model;

public:
signals:
    /// сигнал о том что надо переключиться на какой то экран
    void screenSwitched();
    /// сигналы о пользователе
    void userUpdated();
    void userLoggedIn();
    void userLoggedOut();
    void userLoginFailed();

    /// сигнал об изменении списка заказов
    void ordersUpdated();
    /// сигнал об изменении состояния маршрута
    void routeUpdated();
    void enterCodeSuccess(bool success);
};


#endif
