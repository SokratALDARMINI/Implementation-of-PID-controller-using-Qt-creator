#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "./lib/controllerbackend.h"
#include "./blocks/pid_controller.h"
int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QApplication app(argc, argv);

    ControllerBackend controllerBackend(50, "Zsdnw82iuw");

    QQmlApplicationEngine engine;

    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);

    engine.rootContext()->setContextProperty("plant", &controllerBackend);
    PID_controller pid;

    QObject::connect(&controllerBackend, &ControllerBackend::outputBytesChanged,
                     &pid, &PID_controller::getMessage);

    QObject::connect(&pid, &PID_controller::computed,
                     &controllerBackend, &ControllerBackend::setInput);

    engine.load(url);


    return app.exec();
}
