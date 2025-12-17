#pragma once

#include <QObject>
#include <QString>

#include <qtmetamacros.h>

#include "userinfo.hpp"

class IAuth : public QObject {
    Q_OBJECT
public:
    IAuth(QObject *parent = nullptr) : QObject(parent) { }

    IAuth(const IAuth &)            = delete;
    IAuth(IAuth &&)                 = delete;
    IAuth &operator=(const IAuth &) = delete;
    IAuth &operator=(IAuth &&)      = delete;
    virtual ~IAuth() override       = default;    // NOLINT

    /**
     * Login with email and password.
     */
    virtual void                                                 // NOLINT
    login(const QString &email, const QString &password) = 0;    // NOLINT
    /**
     * Logout.
     */
    virtual void logout() = 0;    // NOLINT

    [[nodiscard]] TUserInfo *userInfo() const {
        return m_userInfo;
    }

    void createUserInfo(const QString &token, const user_dto_t &dto) {
        m_userInfo = new TUserInfo(dto, token);    // NOLINT
        emit userInfoRecv();
    }


signals:
    void userInfoRecv();
    void successLogout();
    void authError(const QString &);
    void userDtoRecv(const user_dto_t &);

private:
    TUserInfo *m_userInfo = nullptr;
};
