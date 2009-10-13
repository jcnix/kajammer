/*
 * File:   playlistEditor.h
 * Author: Casey Jones
 *
 * Created on March 10, 2009, 4:27 PM
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

#ifndef _PLAYLISTEDITOR_H
#define _PLAYLISTEDITOR_H

#include <QtGui/QDialog>
#include <QtCore/QDir>
#include <QtCore/QFileInfo>
#include <QtCore/QString>
#include <QtCore/QStringList>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QFileDialog>
#include <QtGui/QHBoxLayout>
#include <QtGui/QListWidget>
#include <QtGui/QListWidgetItem>
#include <QtGui/QPushButton>
#include <QtGui/QVBoxLayout>

#include "playlist.h"
#include "options.h"

class PlaylistEditor : public QDialog
{
  Q_OBJECT;
  
public:
    PlaylistEditor();
    
public slots:
    void save();
    void openPlaylist();
    void addTracks();
    
private:
    void init();
    
    Playlist *playlist;
    QDialogButtonBox *buttonBox;
    QString playlistFile;
    QListWidget *listView;
    QPushButton *open;
    QPushButton *add;
};

/* PlaylistItem is an extenstion of QListWidgetItem
 * that will display a string of text while storing
 * a path to a file */
class PlaylistItem : public QListWidgetItem
{    
public:
    PlaylistItem(QString, QString);
    QString getPath();
    
private:
    QString path;
};

#endif /* _PLAYLISTEDITOR_H */