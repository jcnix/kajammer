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
    const char* db1 = QDir::homePath().toStdString().c_str();
    char *db = (char*) malloc(50);
    sprintf(db, "%s/.kajammer/kj.db", db1);
    printf("db: %s\n", db);
    int status = sqlite3_open(db, &pdb);
    
    if(status == SQLITE_OK)
    {
        printf("status is okay\n");
    }
    else
    {
        printf("error: %d\n", status);
    }
}

int CollectionManager::close_db()
{
    sqlite3_close(pdb);
    return 1;
}
