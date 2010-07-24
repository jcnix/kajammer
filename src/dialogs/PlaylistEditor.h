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
#include <QtCore/QList>
#include <QtCore/QMap>
#include <QtCore/QSet>
#include <QtCore/QString>
#include <QtCore/QStringList>
#include <QtGui/QCloseEvent>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QFileDialog>
#include <QtGui/QHBoxLayout>
#include <QtGui/QListWidget>
#include <QtGui/QListWidgetItem>
#include <QtGui/QPushButton>
#include <QtGui/QStyle>
#include <QtGui/QVBoxLayout>
#include <QtGui/QInputDialog>

#include "../playlists/PlaylistManager.h"
#include "../Options.h"

class PlaylistEditor : public QDialog
{
  Q_OBJECT;
  
public:
    PlaylistEditor();
    ~PlaylistEditor();
    
public slots:
    void save();
    void newPlaylist();
    void removePlaylist();
    void openPlaylist(QListWidgetItem*);
    void addTracks();
    void removeTracks();
    void moveTracksUp();
    void moveTracksDown();
    
protected:
    void closeEvent(QCloseEvent *event);
    
private:
    void init();
    void fillPlaylists();
    
    PlaylistManager *listManager;

    QListWidget *playlistList;
    QListWidget *playlistContents;
    
    QDialogButtonBox *buttonBox;
    QString playlistFile;
    
    QPushButton *btnNew;
    QPushButton *btnDelete;
    
    QPushButton *btnAdd;
    QPushButton *btnRemove;
    QPushButton *btnUp;
    QPushButton *btnDown;

    QMap<QListWidgetItem*, QString> playlistMap;
    
    QHBoxLayout *playlistLayout;
    QVBoxLayout *playlistControlsLayout;
    QHBoxLayout *squeezeTopLayout;
    QHBoxLayout *topLayout;
    QHBoxLayout *controlSqueezeLayout;
    QHBoxLayout *controlLayout;
    QVBoxLayout *vLayout;
};

#endif /* _PLAYLISTEDITOR_H */
