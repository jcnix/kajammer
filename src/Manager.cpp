/*
 * File:   manager.cpp
 * Author: Casey Jones
 *
 * Created on October 11, 2009, 7:41 PM
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

#include "Manager.h"

Manager* Manager::manager = 0;

Manager::Manager()
{
    controller = Controller::getInstance();
    options = Options::getInstance();
    
    #ifdef HAVE_LASTFM_H
    if(options->useLastFm())
    {
        lastfm = new LastFm();
        connect(controller, SIGNAL(songChanged(int)), lastfm, SLOT(nowPlaying()));
        connect(controller, SIGNAL(songFinished()), lastfm, SLOT(scrobble()));
    }
    #endif
}

Manager* Manager::getInstance()
{
    if(manager == 0)
    {
        manager = new Manager;
    }
    return manager;
}

int Manager::start(int argc, char *argv[], QApplication *app)
{
    m_app = app;
    
    Cli *cli = new Cli(argc, argv);
    bool xFlag = cli->getXFlag();
    
    if(!xFlag)
    {
        Options *options = Options::getInstance();
        
        QString icon = "/usr/share/icons/kajammer.png";
        if(QFile::exists(icon))            
            app->setWindowIcon(QIcon(icon));
        
        if(options->trayIcon())
            app->setQuitOnLastWindowClosed(false);
        else
            app->setQuitOnLastWindowClosed(true);
        
        MainWindow *window = new MainWindow;
        window->resize(options->getMainWidth(), options->getMainHeight());
        window->show();
        
        if(options->trayIcon())
        {
            TrayIcon *trayIcon = new TrayIcon;
            
            connect(trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
                    window, SLOT(showWindow(QSystemTrayIcon::ActivationReason)));
        }
    }
    return m_app->exec();
}

int Manager::exit()
{
    //Submit whats left over in the cache.
    #ifdef HAVE_LASTFM_H
    if(options->useLastFm())
        lastfm->scrobble();
    #endif
    
    //Quit now that everything is cleaned up.
    m_app->exit(0);
    
    return 1;
}
