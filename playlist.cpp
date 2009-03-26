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
    info = QDir(QDir::homePath() + "/.kajammer/playlists").entryInfoList(QDir::Files, QDir::Name);
    QDir kajamDir = QDir(QDir::homePath() + "/.kajammer/");
    
    if(!kajamDir.exists())
    {
        kajamDir.mkdir(QDir::homePath() + "/.kajammer");
        kajamDir.mkdir(QDir::homePath() + "/.kajammer/playlists");
    }
}

void Playlist::newPlaylist(QString name, QStringList newList)
{
    QFile newListFile(QDir::homePath() + "/.kajammer/playlists/" + name);
    newListFile.open(QIODevice::ReadWrite);
    
    QTextStream out(&newListFile);
    for(int i = 0; i < newList.count(); i++)
        out << newList.at(i) + "\n";
}

int Playlist::count()
{    
    return info.count();
}

QString Playlist::getPlaylist(int index)
{    
    QString name = info.at(index).baseName();
    
    return name;
}
