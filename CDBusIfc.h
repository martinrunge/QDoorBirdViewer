/* this file is part of roboctrld
 * Athor: Martin Runge <martin.runge@web.de>
 *
 *   SPDX-License-Identifier: GPL-3.0-or-later
 */
#ifndef CDBUSIFC_H
#define CDBUSIFC_H

#include <QObject>
#include <QUrl>

class CDBusIfc : public QObject
{
    Q_OBJECT
public:
    explicit CDBusIfc(QObject *parent = nullptr, QObject *player = nullptr);

signals:

public slots:
    void play();
    void stop();

    void setURL(QUrl url) { m_url = url; };

private:
    QObject *m_player;
    QUrl m_url;

};

#endif // CDBUSIFC_H
