/*
 * File:   ColletionManager.h
 * Author: Casey Jones
 *
 * Created on December 3, 2009, 8:38 PM
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

#ifndef _COLLECTIONMANAGER_H
#define _COLLECTIONMANAGER_H

#include <QtCore/QThread>
#include <QtCore/QDir>
#include <QtCore/QList>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>

#include "../Controller.h"

class CollectionManager : public QThread {
    Q_OBJECT;
    
public:
    CollectionManager();
    bool connect_db();
    bool close_db();
    bool isDbOpen();
    bool addTrack(QString);
    void search(QString);
    
signals:
    void searchDone(QStringList);

protected:
    void run();
    
private:
    QSqlDatabase db;
    QString queryString;
};

#endif //_COLLECTIONMNAGER_H
