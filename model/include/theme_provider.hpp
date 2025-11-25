#pragma once

#include <QObject>
#include <QString>

class theme_provider_t : public QObject {
    Q_OBJECT

    // Цветовые свойства
    Q_PROPERTY(QString background READ background NOTIFY theme_changed)
    Q_PROPERTY(QString paper READ paper NOTIFY theme_changed)
    Q_PROPERTY(QString text READ text NOTIFY theme_changed)

    Q_PROPERTY(QString primary READ primary NOTIFY theme_changed)
    Q_PROPERTY(QString primary_light READ primary_light NOTIFY theme_changed)

    Q_PROPERTY(QString secondary READ secondary NOTIFY theme_changed)
    Q_PROPERTY(
        QString secondary_light READ secondary_light NOTIFY theme_changed
    )

    Q_PROPERTY(QString success READ success NOTIFY theme_changed)
    Q_PROPERTY(QString success_light READ success_light NOTIFY theme_changed)

    Q_PROPERTY(QString warning READ warning NOTIFY theme_changed)
    Q_PROPERTY(QString warning_light READ warning_light NOTIFY theme_changed)

    Q_PROPERTY(QString error READ error NOTIFY theme_changed)
    Q_PROPERTY(QString error_light READ error_light NOTIFY theme_changed)

    Q_PROPERTY(int font_size READ font_size NOTIFY theme_changed)

public:
    explicit theme_provider_t(QObject *parent = nullptr);

    // Геттеры
    [[nodiscard]] QString background() const {
        return m_background;
    }
    [[nodiscard]] QString paper() const {
        return m_paper;
    }
    [[nodiscard]] QString text() const {
        return m_text;
    }
    [[nodiscard]] QString primary() const {
        return m_primary;
    }
    [[nodiscard]] QString primary_light() const {
        return m_primaryLight;
    }
    [[nodiscard]] QString secondary() const {
        return m_secondary;
    }
    [[nodiscard]] QString secondary_light() const {
        return m_secondary_light;
    }
    [[nodiscard]] QString success() const {
        return m_success;
    }
    [[nodiscard]] QString success_light() const {
        return m_success_light;
    }
    [[nodiscard]] QString warning() const {
        return m_warning;
    }
    [[nodiscard]] QString warning_light() const {
        return m_warning_light;
    }
    [[nodiscard]] QString error() const {
        return m_error;
    }
    [[nodiscard]] QString error_light() const {
        return m_error_light;
    }

    [[nodiscard]] int font_size() const {
        return m_font_size;
    }

    // Метод смены темы
    Q_INVOKABLE void set_light_theme(bool light);

signals:
    void theme_changed();

private:
    // Поля
    QString m_background;
    QString m_paper;
    QString m_text;
    QString m_primary;
    QString m_primaryLight;
    QString m_secondary;
    QString m_secondary_light;
    QString m_success;
    QString m_success_light;
    QString m_warning;
    QString m_warning_light;
    QString m_error;
    QString m_error_light;

    int m_font_size = 14;

    void apply_light_theme();
    void apply_dark_theme();
};
