#pragma once

#include <QObject>

#include <qtmetamacros.h>


class profile_iface_t : public QObject {
    Q_OBJECT
public:
    virtual void load() = 0;

    [[nodiscard]] virtual int seria() const = 0;

    [[nodiscard]] virtual int number() const = 0;

    [[nodiscard]] virtual QString address() const = 0;

    virtual void set_seria(int seria)                = 0;
    virtual void set_number(int number)              = 0;
    virtual void set_address(const QString &address) = 0;
};
