/* 
 * File:   menubar.h
 * Author: Casey Jones
 *
 * Created on March 4, 2009, 4:35 PM
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

#ifndef _MENUBAR_H
#define	_MENUBAR_H

#include <QtGui/QAction>
#include <QtCore/QDir>
#include <QtGui/QFileDialog>
#include <QtGui/QInputDialog>
#include <QtGui/QKeySequence>
#include <QtGui/QMessageBox>
#include <QtGui/QMenuBar>
#include <QtGui/QMenu>
#include <QtCore/QString>
#include <QtCore/QStringList>

#include "controller.h"
#include "playlist.h"
#include "optionsPanel.h"
#include "options.h"
#include "playlistEditor.h"

class MenuBar : public QMenuBar
{
    Q_OBJECT;

public:
    MenuBar();
    QStringList getQueue();

private slots:
    void createNewPlaylist();
    void deletePlaylist();
    void open();
    void quit();
    void showOptions();
    void showPlaylistEditor();
    void aboutDialog();

private:
    void init();
    
    Controller *controller;
    Playlist *playlist;
    Options *options;
    
    QAction *newPlaylist;
    QAction *delPlaylist;
    QAction *openFile;
    QAction *close;
    QAction *optionsAction;
    QAction *playlistEditAction;
    QAction *about;
    QMenuBar *menuBar;
    QMenu *file;
    QMenu *tools;
    QMenu *help;
    QStringList fileQueue;
};

#endif	/* _MENUBAR_H */