/*
 * File:   playlist.h
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

#ifndef _PLAYLIST_H
#define _PLAYLIST_H

#include <QtCore/QObject>
#include <QtCore/QDir>
#include <QtCore/QFile>
#include <QtCore/QFileInfo>
#include <QtCore/QIODevice>
#include <QtCore/QString>
#include <QtCore/QStringList>
#include <QtCore/QTextStream>
#include <iostream>

#define KAJAM_DIR QDir::homePath()+"/.kajammer/"
#define PLAYLIST_DIR KAJAM_DIR+"/playlists/"
#define QKAJAM_DIR QDir(QDir::homePath()+"/.kajammer/")

class Playlist : public QObject
{
    Q_OBJECT;
    
public:
    static Playlist* getInstance();
    void newPlaylist(QString, QStringList);
    void delPlaylist(QString);
    QString getPlaylistName(int);
    QStringList getPlaylistContents(QString);
    int count();
    void listPlaylists();
    QString getEntirePlaylist(QString);
    bool playlistExists(QString);
    
signals:
    void resetPlaylists();
    
protected:
    Playlist();
    
private:
    void init();
    void resetInfo() { info = QDir(PLAYLIST_DIR).entryInfoList(QDir::Files, QDir::Name); }
    
    static Playlist *playlist;
    QList<QFileInfo> info;
    QString playlistDir;
};

#endif /* _PLAYLIST_H */