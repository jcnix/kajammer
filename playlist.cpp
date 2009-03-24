/*
 * File:   playlist.cpp
 * Author: casey
 *
 * Created on March 24, 2009, 4:48 PM
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

#include "playlist.h"

Playlist::Playlist()
{
    init();
}

void Playlist::init()
{
    kajamDir = QDir(QDir::homePath() + "/.kajammer/");
    
    if(!kajamDir.exists())
    {
        kajamDir.mkdir(QDir::homePath() + "/.kajammer");
        kajamDir.mkdir(QDir::homePath() + "/.kajammer/playlists");
    }
}

void Playlist::newPlaylist(QString name)
{
    QFile newList(QDir::homePath() +"/.kajammer/playlists/" + name);
    newList.open(QIODevice::ReadWrite);
    
    QTextStream out(&newList);
    out << "Test";
}
