#include "theme_provider.hpp"

theme_provider_t::theme_provider_t(QObject *parent) : QObject(parent) {
    apply_light_theme();    // по умолчанию светлая тема
}

void theme_provider_t::set_light_theme(bool light) {
    if (light) {
        apply_light_theme();
    }
    else {
        apply_dark_theme();
    }
    emit theme_changed();
}

void theme_provider_t::apply_light_theme() {
    m_background = "#F5F5F5";
    m_paper      = "#FFFFFF";
    m_text       = "#000000";

    m_primary      = "#3F51B5";
    m_primaryLight = "#C5CAE9";

    m_secondary       = "#FF4081";
    m_secondary_light = "#FF80AB";

    m_success       = "#4CAF50";
    m_success_light = "#C8E6C9";

    m_warning       = "#FFC107";
    m_warning_light = "#FFECB3";

    m_error       = "#F44336";
    m_error_light = "#FFCDD2";
}

void theme_provider_t::apply_dark_theme() {
    m_background = "#001529";
    m_paper      = "#293645";
    m_text       = "#F4F6F7";

    m_primary      = "#FAAD14";
    m_primaryLight = "#D48806";

    m_secondary       = "#597EF7";
    m_secondary_light = "#597EF7";

    m_success       = "#52C41A";
    m_success_light = "#52C41A";

    m_warning       = "#D9D9D9";
    m_warning_light = "#D9D9D9";

    m_error       = "#FF4D4F";
    m_error_light = "#FF4D4F";
}
