/* this file is part of roboctrld
 * Athor: Martin Runge <martin.runge@web.de>
 *
 *   SPDX-License-Identifier: GPL-3.0-or-later
 */
#include "CDBusAdapter.h"
#include "dbus_interfaceadaptor.h"
#include <QWindow>


CDBusAdapter::CDBusAdapter(QObject *parent) : QObject(parent), m_is_active_instance(false)
{
    DoorbirdviewerAdaptor *ptr;
    ptr = new DoorbirdviewerAdaptor(this);

    QDBusConnection connection = QDBusConnection::sessionBus();
    bool success = connection.registerObject("/", this);
    success = connection.registerService("de.rungenetz.doorbirdviewer");

    if(success) {
        // registration of dbus service was successful -> we are the active instance
        m_is_active_instance = true;
    }
}


void CDBusAdapter::play() {
    m_player->setProperty("source", m_url);

    QVariant returnedValue;
    bool res = QMetaObject::invokeMethod(m_player, "play");

    qDebug() << "QML function returned:" << returnedValue.toString();
}

void CDBusAdapter::stop() {
    QVariant returnedValue;
    bool res = QMetaObject::invokeMethod(m_player, "stop");

    m_player->setProperty("source", QUrl());

    qDebug() << "QML function returned:" << returnedValue.toString();
}



void CDBusAdapter::fullscreen() {
    qDebug() << "fullscreen() called";
    m_mainwin->setProperty("visibility", QWindow::FullScreen);

}

void CDBusAdapter::geometry(int width, int height, int x, int y)
{
    qDebug() << "geometry(" << x << y << width << height << ")";
    m_mainwin->setProperty("width", width);
    m_mainwin->setProperty("height", height);
    m_mainwin->setProperty("x", x);
    m_mainwin->setProperty("y", y);
}

void CDBusAdapter::setPlayer(QObject *player)
{
    m_player = player;
}

void CDBusAdapter::setMainwin(QObject *mainwin)
{
    m_mainwin = mainwin;
}
