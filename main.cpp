/* this file is part of roboctrld
 * Athor: Martin Runge <martin.runge@web.de>
 *
 *   SPDX-License-Identifier: GPL-3.0-or-later
 */
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QMetaObject>
#include <QDBusConnection>
#include <QSettings>

#include "dbus-interfaceadaptor.h"
#include "CDBusIfc.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    app.setOrganizationName("martinrunge");
    app.setOrganizationDomain("rungenetz.de");
    app.setApplicationName("QDoorBirdViewer");

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    if (!QDBusConnection::sessionBus().isConnected()) {
        qWarning("Cannot connect to the D-Bus session bus.\n"
                 "Please check your system settings and try again.\n");
        return 1;
    }

    QString n = engine.rootObjects().first()->objectName();
    QObject *player = engine.rootObjects().first()->findChild<QObject*>("player");

    CDBusIfc dbuf_ifc(&app, player);

    QString defaultURL("rtsp://<username>:<password>@hostname/path/to/video.mp4");
    QString URL_string = QSettings().value("url", defaultURL).toString();
    QUrl URL;

    if(URL_string == defaultURL) {
        // no settings were made, save default settings to get a skeleton config file
        QSettings().setValue("url", defaultURL);
        qWarning() << "Please set the video URL in the config file: " << QSettings().fileName();
    }
    else {
        URL = URL_string;
        if(URL.isValid()) {
            QVariant returnedValue;
            player->setProperty("source", URL);
            dbuf_ifc.setURL(URL);
        }
        else {
            qWarning() << "Cannot parse URL.\n Please check the URL in the config file: " << QSettings().fileName();
        }
    }


    return app.exec();
}
