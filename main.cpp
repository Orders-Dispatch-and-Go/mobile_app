#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "backend.hpp"
#include "theme_provider.hpp"

int main(int argc, char *argv[]) {
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection
    );
    auto *backend = new backend_t(&app);           // NOLINT
    auto *theme   = new theme_provider_t(&app);    // NOLINT
    engine.rootContext()->setContextProperty("theme", theme);
    engine.rootContext()->setContextProperty("backend", backend);
    engine.loadFromModule("untitled", "Main");

    return QGuiApplication::exec();
}
