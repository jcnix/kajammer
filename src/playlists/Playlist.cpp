/*
 * File:   playlist.cpp
 * Author: Casey Jones
 *
 * Created on December 5, 2009, 4:48 PM
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

#include "Playlist.h"

Playlist::Playlist(QString name)
{
    playlist = name;
    playlistFile = PLAYLIST_DIR + name;
    
    QDir pdir(PLAYLIST_DIR);
    if(!pdir.exists()) {
        pdir.mkpath(PLAYLIST_DIR);
    }
    
    QFile file(playlistFile);
    if(!file.exists())
    {
        //Create a blank list to write a new file
        QStringList list;
        list.append("");
        addTracks(list);
    }
}

Playlist::Playlist(QString name, QStringList tracks)
{
    addTracks(tracks);
    playlist = name;
    playlistFile = PLAYLIST_DIR + name;
}

void Playlist::addTrack(QString track)
{
    QStringList tracks(track);
    addTracks(tracks);
}

void Playlist::addTracks(QStringList tracks)
{
    if(!exists())
    {
        QFile newList(playlistFile);
    }
    
    QFile file(playlistFile);
    file.open(QIODevice::WriteOnly);
    
    QTextStream out(&file);
    for(int i = 0; i < tracks.count(); i++) {
        if(tracks.at(i) == "")
            continue;
        
        out << tracks.at(i) + "\n";
    }
    out.flush();
    file.close();
    
    //Reset Info so it finds the new playlist
    emit resetPlaylists();
}

void Playlist::deleteList()
{
    QFile listFile (playlistFile);
    
    if(listFile.exists())
    {
        listFile.remove();
    }
    else
    {
        std::cout << "Playlist does not exist: " << playlist.toStdString() << "\n";
    }
    
    //Reset Info so it finds the new playlist
    emit resetPlaylists();
}

bool Playlist::exists()
{
    return QFile(playlistFile).exists();
}

/* Returns each line of a playlist in a QStringList */
QStringList Playlist::getContents()
{
    QFile file(playlistFile);
    file.open(QIODevice::ReadOnly);
    
    QStringList playlist;    
    QTextStream in(&file);
    
    while(!in.atEnd()) {
        QString track = in.readLine(0);
        playlist.append(track);
    }
    
    return playlist;
}

QString Playlist::getName()
{
    return playlist;
}

QString Playlist::getPath()
{
    return playlistFile;
}
