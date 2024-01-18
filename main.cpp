#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include <QLocale>
#include <QTranslator>
#include "ColorMaker/colormaker.h"

#include <QQuickView>

// #include <QtQuick2ApplicationViewer>

#include <QRandomGenerator>
#include <QQmlContext>

#include "ChangeQmlColor/changeqmlcolor.h"

#include <QQuickItem>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    // qmlRegisterType 是一个可以将C++实现的类在QML中调用的，连接C++和QML的一个工具
    // 注冊QML類型
    qmlRegisterType<ColorMaker>("an.qt.ColorMaker", 1, 0, "ColorMaker");

    QQuickView viewer;

    // 在C++中定义对象
    // viewer.rootContext()->setContextProperty("colorMaker", new ColorMaker());

    viewer.setSource(QStringLiteral("qrc:/ColorMaker_QtQuick/main.qml"));
    viewer.show();

#if 1
    QQuickItem * rootItem = viewer.rootObject();
    new ChangeQmlColor((QObject*)rootItem);
    QObject * quitButton = rootItem->findChild<QObject*>("quitButton");
    if(quitButton)
    {
        QObject::connect(quitButton, SIGNAL(clicked()), &app, SLOT(quit()));
    }

    QObject *textLabel = rootItem->findChild<QObject*>("textLabel");
    if(textLabel)
    {
        //1. failed call
        bool bRet = QMetaObject::invokeMethod(textLabel, "setText", Q_ARG(QString, "world hello"));
        qDebug() << "call setText return - " << bRet;
        textLabel->setProperty("color", QColor::fromRgb(255,0,0));
        bRet = QMetaObject::invokeMethod(textLabel, "doLayout");
        qDebug() << "call doLayout return - " << bRet;
    }
#endif

#if 0

    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "ColorMaker_QtQuick_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            app.installTranslator(&translator);
            break;
        }
    }

    QQmlApplicationEngine engine;
    const QUrl url(u"qrc:/ColorMaker_QtQuick/main.qml"_qs);
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);
#endif

    return app.exec();
}
