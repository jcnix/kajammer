/*
 * File:   playlist.h
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

#ifndef _PLAYLIST_H
#define _PLAYLIST_H

#include <QtCore/QObject>
#include <QtCore/QDir>
#include <QtCore/QFile>
#include <QtCore/QString>
#include <QtCore/QStringList>
#include <QtCore/QTextStream>
#include <iostream>

#include "../kajammer.h"

class Playlist : public QObject
{
    Q_OBJECT;
    
public:
    //Opens an existing playlist
    Playlist(QString);
    //Creates a brand new playlist
    Playlist(QString, QStringList);
    
    void addTrack(QString);
    void addTracks(QStringList);
    void deleteList();
    bool exists();
    QStringList getContents();
    
signals:
    void resetPlaylists();
    
private:
    QString playlist;
    QString playlistFile;
};

#endif /* _PLAYLIST_H */
