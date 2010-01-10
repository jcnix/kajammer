/*
 * File:   ColletionManager.cpp
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

#include "CollectionManager.h"

CollectionManager::CollectionManager()
{
}

bool CollectionManager::connect_db()
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    QString dbPath = QDir::homePath() + "/.kajammer/kj.db";
    
    db.setDatabaseName(dbPath);
    bool open = db.open();
    
    if(open)
    {
        QSqlQuery query;
        query.exec("CREATE TABLE IF NOT EXISTS music("
                    "file text,"
                    "title text,"
                    "artist text,"
                    "album text"
                    ");");
    }
    
    return open;
}

bool CollectionManager::addTrack(QString track)
{
    Controller *c = Controller::getInstance();
    QMap<QString, QString> metaData = c->getMetadata(track);
    QString title = metaData.value("TITLE");
    QString artist = metaData.value("ARTIST");
    QString album = metaData.value("ALBUM");
    
    QSqlQuery query;
    query.exec("INSERT INTO music VALUES("
                "'"+track+"',"
                "'"+title+"',"
                "'"+artist+"',"
                "'"+album+"'"
                ");");
    
    return true;
}

bool CollectionManager::close_db()
{
    db.close();
    return true;
}
