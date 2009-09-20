/*
 * File:   playlist.cpp
 * Author: Casey Jones
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

#include "headers/playlist.h"

Playlist* Playlist::playlist = 0;

Playlist::Playlist()
{
    init();
}

void Playlist::init()
{
    resetInfo();
    
    if(!QKAJAM_DIR.exists())
    {
        QKAJAM_DIR.mkdir(KAJAM_DIR);
        QKAJAM_DIR.mkdir(PLAYLIST_DIR);
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
    if(!playlistExists(name))
    {
        QFile newListFile(PLAYLIST_DIR + name);
        newListFile.open(QIODevice::WriteOnly);
        
        QTextStream out(&newListFile);
        for(int i = 0; i < newList.count(); i++) {
            out << newList.at(i) + "\n";
        }
        
        //Reset Info so it finds the new playlist
        resetInfo();
        emit resetPlaylists();
    }
}

void Playlist::delPlaylist(QString playlist)
{
    QFile listFile (PLAYLIST_DIR + playlist);
    
    if(listFile.exists())
    {
        listFile.remove();
    }
    else
    {
        std::cout << "Playlist does not exist: " << playlist.toStdString() << "\n";
    }
    
    //Reset Info so it finds the new playlist
    resetInfo();
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

QStringList Playlist::getPlaylistContents(QString name)
{
    QFile playlistFile(PLAYLIST_DIR + name);
    playlistFile.open(QIODevice::ReadOnly);
    
    QStringList playlist;    
    QTextStream in(&playlistFile);
    
    while(!in.atEnd())
        playlist.append(in.readLine(0));
    
    return playlist;
}

QString Playlist::getEntirePlaylist(QString name)
{
    QFile playlistFile(PLAYLIST_DIR + name);
    playlistFile.open(QIODevice::ReadOnly);
    
    QString playlist;    
    QTextStream in(&playlistFile);
    
    playlist = in.readAll();
    
    return playlist;
}

bool Playlist::playlistExists(QString name)
{
    for(int i = 0; i < count(); i ++)
    {
        if(getPlaylistName(i).compare(name) == 0)
            return true;
    }
    return false;
}

// Prints list of playlists to terminal
void Playlist::listPlaylists()
{
    for(int i = 0; i < count(); i++)
        std::cout << getPlaylistName(i).toStdString() << "\n";
}
