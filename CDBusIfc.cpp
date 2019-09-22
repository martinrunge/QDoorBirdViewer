/* this file is part of roboctrld
 * Athor: Martin Runge <martin.runge@web.de>
 *
 *   SPDX-License-Identifier: GPL-3.0-or-later
 */
#include "CDBusIfc.h"
#include "dbus-interfaceadaptor.h"
#include "DBifc.h"

CDBusIfc::CDBusIfc(QObject *parent, QObject *player) : QObject(parent), m_player(player)
{
    DoorbirdviewerAdaptor *ptr;
    ptr = new DoorbirdviewerAdaptor(this);

    QDBusConnection connection = QDBusConnection::sessionBus();
    connection.registerObject("/", this);
    connection.registerService("de.rungenetz.doorbirdviewer");

}


void CDBusIfc::play() {
    m_player->setProperty("source", m_url);

    QVariant returnedValue;
    bool res = QMetaObject::invokeMethod(m_player, "play");

    qDebug() << "QML function returned:" << returnedValue.toString();
}

void CDBusIfc::stop() {
    QVariant returnedValue;
    bool res = QMetaObject::invokeMethod(m_player, "stop");

    m_player->setProperty("source", QUrl());

    qDebug() << "QML function returned:" << returnedValue.toString();
}

