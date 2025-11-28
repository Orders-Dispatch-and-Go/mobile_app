#pragma once

#include <QObject>

#include <qtmetamacros.h>

#include "iprofile.hpp"


class moc_profile_t : public profile_iface_t {
    Q_OBJECT
public:
    void load() override { }

    [[nodiscard]] int seria() const override {
        return 1234;
    }

    [[nodiscard]] int number() const override {
        return 567890;
    }

    [[nodiscard]] QString address() const override {
        return "Пирогова 1";
    }
};
