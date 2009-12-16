/*
 * File:   PlaylistManager.cpp
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

#include "PlaylistManager.h"

PlaylistManager* PlaylistManager::listManager = 0;

PlaylistManager::PlaylistManager()
{
    init();
}

void PlaylistManager::init()
{
    resetInfo();
    
    if(!KAJAM_QDIR.exists())
    {
        KAJAM_QDIR.mkdir(KAJAM_DIR);
        KAJAM_QDIR.mkdir(PLAYLIST_DIR);
    }
}

PlaylistManager* PlaylistManager::getInstance()
{
    if(listManager == 0)
    {
        listManager = new PlaylistManager;
    }
    
    return listManager;
}

void PlaylistManager::resetInfo()
{
    info = QDir(PLAYLIST_DIR).entryInfoList(QDir::Files, QDir::Name);
}

void PlaylistManager::newPlaylist(QString name, QStringList tracks)
{
    Playlist *playlist = new Playlist(name);
    if(!playlist->exists())
    {
        playlist->addTracks(tracks);
    }
    
    //Reset Info so it finds the new playlist
    resetInfo();
    emit resetPlaylists();
}

void PlaylistManager::delPlaylist(QString name)
{
    Playlist *playlist = new Playlist(name);
    if(playlist->exists()) {
        playlist->deleteList();
    }
    
    //Reset Info so it finds the new playlist
    resetInfo();
    emit resetPlaylists();
}

int PlaylistManager::count()
{    
    return info.count();
}

QStringList PlaylistManager::getPlaylistNames()
{
    resetInfo();
    
    QStringList names;
    for(int i = 0; i < count(); i++)
    {
        names.append(info.at(i).baseName());
    }
    
    return names;
}

/* Returns each line of a playlist in a QStringList */
QStringList PlaylistManager::getPlaylistContents(QString name)
{
    Playlist *playlist = new Playlist(name);
    QStringList tracks = playlist->getContents();
    
    return tracks;
}

/* Ensures that the playlist given exists.
 * Only used to check for collisions
 * when creating a new playlist */
bool PlaylistManager::playlistExists(QString name)
{
    Playlist *playlist = new Playlist(name);
    
    bool b = playlist->exists();
    return b;
}

// Prints list of playlists to stdout
void PlaylistManager::listPlaylists()
{
    QStringList lists = getPlaylistNames();
    for(int i = 0; i < count(); i++)
        std::cout << lists.at(i).toStdString() << "\n";
}
