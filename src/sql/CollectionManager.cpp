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
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    addTrack("/home/casey/music/tetris.mp3");
}

int CollectionManager::addTrack(QString qtrack)
{
    return 1;
}

int CollectionManager::close_db()
{
    return 1;
}
