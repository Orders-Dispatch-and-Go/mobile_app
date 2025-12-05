#pragma once

#include <QObject>

/**
 * объект для контроля того, в какой части user-story находится пользователь
 */
class state_t : public QObject {
    Q_OBJECT

public:
    [[nodiscard]] int get_order_to_finish() const {
        return m_order_to_finish.value_or(-1);
    }

private:
    std::optional<int> m_order_to_finish = 100;
    // Private members and methods
};
