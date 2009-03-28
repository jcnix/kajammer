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

Playlist* Playlist::playlist = 0;

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

Playlist* Playlist::getInstance()
{
    if(playlist == 0)
    {
        playlist = new Playlist;
    }
    return playlist;
}

void Playlist::newPlaylist(QString name, QStringList newList)
{
    QFile newListFile(QDir::homePath() + "/.kajammer/playlists/" + name);
    newListFile.open(QIODevice::WriteOnly);
    
    QTextStream out(&newListFile);
    for(int i = 0; i < newList.count(); i++)
        out << newList.at(i) + "\n";
    
    //Reset Info so it finds the new playlist
    info = QDir(QDir::homePath() + "/.kajammer/playlists").entryInfoList(QDir::Files, QDir::Name);
    emit resetPlaylists();
}

void Playlist::delPlaylist(QString playlist)
{
    QString homeDir = QDir::homePath() + "/.kajammer/playlists/";
    std::string list = homeDir.toStdString() + playlist.toStdString();
    remove(list.c_str()); //in iostream
    
    //Reset Info so it finds the new playlist
    info = QDir(QDir::homePath() + "/.kajammer/playlists").entryInfoList(QDir::Files, QDir::Name);
    emit resetPlaylists();
}

int Playlist::count()
{    
    return info.count();
}

QString Playlist::getPlaylistName(int index)
{    
    QString name = info.at(index).baseName();
    
    return name;
}

QStringList Playlist::getPlaylistContents(int index)
{
    QFile playlistFile(info.at(index).canonicalFilePath());
    playlistFile.open(QIODevice::ReadOnly);
    
    QStringList playlist;    
    QTextStream in(&playlistFile);
    
    while(!in.atEnd())
    {
        QString song = in.readLine(0);
        playlist.append(song);
    }
    
    return playlist;
}