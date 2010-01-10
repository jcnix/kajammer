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

#include <QtCore/QObject>
#include <QtCore/QDir>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>

#include "../Controller.h"

class CollectionManager : public QObject {
    Q_OBJECT;
    
public:
    CollectionManager();
    static bool connect_db();
    static bool close_db();
    static bool addTrack(QString);
};

#endif //_COLLECTIONMNAGER_H
