/*
 * File:   manager.h
 * Author: Casey Jones
 *
 * Created on October, 11 2009, 7:41 PM
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

#ifndef _MANAGER_H
#define _MANAGER_H

#include <QtCore/QObject>
#include <QtGui/QApplication>
#include <QtGui/QIcon>

#include "headers/kajammer.h"
#include "Cli.h"
#include "config.h"
#include "Controller.h"
#include "Options.h"
#include "gui/widgets/TrayIcon.h"
#include "gui/MainWindow.h"
#include "gui/MediaControls.h"
#include "gui/MenuBar.h"
#include "sql/CollectionManager.h"

#ifdef HAVE_LASTFM_H
#include "services/LastFM.h"
#endif

class MenuBar;

class Manager : public QObject
{
    Q_OBJECT;

public:
    static Manager* getInstance();
    int start(int argc, char *argv[], QApplication*);
    void showMessage(QString message);
    
public slots:
    int exit();

protected:
    Manager();

private:
    static Manager *manager;
    QApplication *m_app;
    
    MenuBar *menuBar;
    MediaControls *mediaControls;
    
    Controller *controller;
    Options *options;
    Cli *cli;
    TrayIcon *trayIcon;
    #ifdef HAVE_LASTFM_H
    LastFm *lastfm;
    #endif
};

#endif /* _MANAGER_H */
