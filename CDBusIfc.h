/* this file is part of roboctrld
 * Athor: Martin Runge <martin.runge@web.de>
 *
 *   SPDX-License-Identifier: GPL-3.0-or-later
 */
#ifndef CDBUSIFC_H
#define CDBUSIFC_H

#include <QObject>

class CDBusIfc : public QObject
{
    Q_OBJECT
public:
    explicit CDBusIfc(QObject *parent = nullptr);

signals:

public slots:
};

#endif // CDBUSIFC_H