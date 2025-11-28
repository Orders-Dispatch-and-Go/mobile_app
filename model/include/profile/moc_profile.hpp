#pragma once

#include <QObject>

#include <qtmetamacros.h>

#include "iprofile.hpp"


class moc_profile_t : public profile_iface_t {
    Q_OBJECT
public:
    void load() override { }

    [[nodiscard]] int seria() const override {
        return m_seria;
    }

    [[nodiscard]] int number() const override {
        return m_number;
    }

    [[nodiscard]] QString address() const override {
        return m_address;
    }

    void set_seria(int seria) override {
        m_seria = seria;
    }

    void set_number(int number) override {
        // Implementation
    }

    void set_address(const QString &address) override {
        m_address = address;
    }

private:
    int m_seria       = 1234;
    int m_number      = 567890;
    QString m_address = "Пирогова 1";
};
