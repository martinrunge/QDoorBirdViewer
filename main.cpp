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

#include "dbus_interfaceadaptor.h"
#include "CDBusAdapter.h"

#include "CDBusIfc.h"
#include "DBifc.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QString geometrystr;
    // hack: if -geometry was given, save it before QApplication removes it from the argument list
    for (int i=1; i < argc - 1; i++) {
        char* strmatch = strstr(argv[i], "geometry");
        if(strmatch != nullptr) {
            // argv[i] is "-geometry" or "--geoometry"
            geometrystr=QString::fromUtf8(argv[i+1]);
        }
    }

    QGuiApplication app(argc, argv);

    app.setOrganizationName("martinrunge");
    app.setOrganizationDomain("rungenetz.de");
    app.setApplicationName("QDoorBirdViewer");

    QStringList cmdlineargs = app.arguments();

    if (!QDBusConnection::sessionBus().isConnected()) {
        qWarning("Cannot connect to the D-Bus session bus.\n"
                 "Please check your system settings and try again.\n");
        return 1;
    }

    CDBusAdapter db_adapter(&app);

    do {
        if(!db_adapter.isActiveInstance()) {
            CDBusIfc db_ifc(&app);
            DeRungenetzDoorbirdviewerInterface ifc("de.rungenetz.doorbirdviewer", "/", QDBusConnection::sessionBus(), &db_ifc);

            if(cmdlineargs.contains("--fullscreen")) {
                ifc.fullscreen();
                return 0;
            }
            if(cmdlineargs.contains("--minimize")) {
                ifc.minimize();
                return 0;
            }
            if(!geometrystr.isEmpty()) {
                bool ok;
                int xcharpos = geometrystr.indexOf("x");
                if(xcharpos == -1) break;
                QStringRef width_str(&geometrystr, 0, xcharpos);
                int width = width_str.toInt(&ok);
                if(!ok) break;

                int p1charpos = geometrystr.indexOf("+", xcharpos);
                if(p1charpos == -1) break;
                QStringRef height_str(&geometrystr, xcharpos + 1, p1charpos - (xcharpos + 1));
                int height = height_str.toInt(&ok);
                if(!ok) break;

                int p2charpos = geometrystr.indexOf("+", p1charpos + 1);
                if(p2charpos == -1) break;
                QStringRef xpos_str(&geometrystr, p1charpos +1, p2charpos - (p1charpos + 1));
                int xpos = xpos_str.toInt(&ok);
                if(!ok) break;

                QStringRef ypos_str(&geometrystr, p2charpos + 1, geometrystr.length() - (p2charpos + 1));
                int ypos = ypos_str.toInt(&ok);
                if(!ok) break;

                ifc.geometry(width, height, xpos , ypos);
                return 0;
            }

            return 0;
        }
    }
    while(false);

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;


    QString n = engine.rootObjects().first()->objectName();
    QObject *mainwin = engine.rootObjects().first();
    db_adapter.setMainwin(mainwin);

    QObject *player = mainwin->findChild<QObject*>("player");
    db_adapter.setPlayer(player);


    if(cmdlineargs.contains("--fullscreen")) {
        db_adapter.fullscreen();
        // mainwin->setProperty("visibility", QWindow::FullScreen);
    }


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
            mainwin->setProperty("videosrc", URL);
            db_adapter.setURL(URL);
        }
        else {
            qWarning() << "Cannot parse URL.\n Please check the URL in the config file: " << QSettings().fileName();
        }
    }


    return app.exec();
}
