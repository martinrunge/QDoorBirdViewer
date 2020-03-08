/* this file is part of roboctrld
 * Athor: Martin Runge <martin.runge@web.de>
 *
 *   SPDX-License-Identifier: GPL-3.0-or-later
 */
#ifndef CDBUSADAPTER_H
#define CDBUSADAPTER_H

#include <QObject>
#include <QUrl>

class CDBusAdapter : public QObject
{
    Q_OBJECT
public:
    explicit CDBusAdapter(QObject *parent = nullptr);

    bool isActiveInstance() { return m_is_active_instance; }

    QObject *mainwin() const {return m_mainwin;}
    void setMainwin(QObject *mainwin);

    QObject *player() const {return m_player; }
    void setPlayer(QObject *player);

signals:

public slots:
    void play();
    void stop();
    void fullscreen();
    void minimize();
    void geometry(int width, int height, int x, int y );

    void setURL(QUrl url) { m_url = url; };


private:
    QObject *m_mainwin;
    QObject *m_player;
    QUrl m_url;

    bool m_is_active_instance;

};

#endif // CDBUSADAPTER_H
