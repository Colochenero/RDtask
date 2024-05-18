#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "FileHandler.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    QQmlApplicationEngine engine;

    // Register the FileHandler class with QML
    FileHandler fileHandler;
    engine.rootContext()->setContextProperty("fileHandler", &fileHandler);

    const QUrl url(QStringLiteral("qrc:/RDtask/Main.qml"));
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
