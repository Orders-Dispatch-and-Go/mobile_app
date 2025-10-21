#ifndef BACKEND_HPP
#define BACKEND_HPP

#include <QObject>

#include <qtmetamacros.h>

#include "userinfo.hpp"


/**
 * @brief Backend class for the application.
 * Available from any QML component as "backend" property.
 */
class backend_t : public QObject {
    Q_OBJECT
public:
    explicit backend_t(QObject *parent = nullptr);

    ~backend_t() override = default;

    Q_INVOKABLE void set_user_email(const QString &email);
    Q_INVOKABLE void set_user_surname(const QString &surname);
    Q_INVOKABLE void set_user_name(const QString &name);
    Q_INVOKABLE void set_user_patronymic(const QString &patronymic);

    Q_INVOKABLE [[nodiscard]] QString user_email() const;
    Q_INVOKABLE [[nodiscard]] QString user_surname() const;
    Q_INVOKABLE [[nodiscard]] QString user_name() const;
    Q_INVOKABLE [[nodiscard]] QString user_patronymic() const;

private:
    Q_DISABLE_COPY_MOVE(backend_t)
    user_info_t m_user_info;
};

#endif
