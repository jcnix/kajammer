/*
 * File:   playlist.h
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

#ifndef _PLAYLIST_H
#define _PLAYLIST_H

#include <QtCore/QObject>
#include <QtCore/QDir>
#include <QtCore/QFile>
#include <QtCore/QFileInfo>
#include <QtCore/QIODevice>
#include <QtCore/QString>
#include <QtCore/QStringList>
#include <QtCore/QStack>
#include <QtCore/QTextStream>
#include <iostream>
#include <cstring>

class Playlist : public QObject
{
    Q_OBJECT;
    
public:
    static Playlist* getInstance();
    void newPlaylist(QString, QStringList);
    void delPlaylist(QString);
    QString getPlaylistName(int);
    QStringList getPlaylistContents(int);
    int count();
    
signals:
    void resetPlaylists();
    
protected:
    Playlist();
    
private:
    void init();
    
    static Playlist *playlist;
    QList<QFileInfo> info;
};

#endif /* _PLAYLIST_H */
