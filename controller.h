/* 
 * File:   controller.h
 * Author: casey
 *
 * Created on March 10, 2009, 4:27 PM
 *
 * This file is part of KaJammer.
 *
 * KaJammer is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * KaJammer is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with KaJammer.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef _CONTROLLER_H
#define	_CONTROLLER_H

#include <QtCore/QObject>
#include <QtCore/QStringList>
#include <QtCore/QStack>
#include <QtCore/QString>
#include <QtCore/QVector>

class Controller : public QObject
{
    Q_OBJECT;

public:
    static Controller* getInstance();
    void setQueue(QStringList);
    
public slots:
    void nextSong();
    void prevSong();

signals:
    void songChanged(QString);

protected:
    Controller();

private:
    static Controller *controller;
    QString fileName;
    QVector<QString> prevQueue;
    QVector<QString> nextQueue;
};

#endif	/* _CONTROLLER_H */

