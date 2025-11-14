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
    m_background = "#121212";
    m_paper      = "#1E1E1E";
    m_text       = "#FFFFFF";

    m_primary      = "#7986CB";
    m_primaryLight = "#9FA8DA";

    m_secondary       = "#F48FB1";
    m_secondary_light = "#F8BBD0";

    m_success       = "#81C784";
    m_success_light = "#A5D6A7";

    m_warning       = "#FFB300";
    m_warning_light = "#FFD54F";

    m_error       = "#E57373";
    m_error_light = "#EF9A9A";
}
