/*
 * File:   Manager.cpp
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

Manager::Manager()
{
    controller = Controller::getInstance();
}

int Manager::start(int argc, char *argv[], QApplication *app)
{
    m_app = app;    
    cli = new Cli(argc, argv);
    bool xFlag = cli->getXFlag();
    
    if(!xFlag)
    {        
        if(QFile::exists(KAJAMMER_ICON))            
            app->setWindowIcon(QIcon(KAJAMMER_ICON));
        
        if(Options::getOption_Bool(KJ::USE_TRAY_ICON))
            app->setQuitOnLastWindowClosed(false);
        else
            app->setQuitOnLastWindowClosed(true);
        
        MainWindow *window = new MainWindow(app, this);
        window->resize(Options::getOption_Int(KJ::MAIN_WIDTH),
                       Options::getOption_Int(KJ::MAIN_HEIGHT));
        window->show();
        
        if(Options::getOption_Bool(KJ::USE_TRAY_ICON))
        {
            trayIcon = new TrayIcon;
            
            connect(trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
                    window, SLOT(showWindow(QSystemTrayIcon::ActivationReason)));
            connect(trayIcon, SIGNAL(exit()), this, SLOT(exit()));
        }
        
        #ifdef HAVE_LASTFM_H
        if(Options::getOption_Bool(KJ::USE_LASTFM))
        {
            lastfm = new LastFm();
            connect(controller, SIGNAL(songChanged(int)), lastfm, SLOT(nowPlaying()));
            connect(controller, SIGNAL(songFinished()), lastfm, SLOT(scrobble()));
        }
        #endif
    }
    return m_app->exec();
}

int Manager::exit()
{
    //Submit whats left over in the cache.
    #ifdef HAVE_LASTFM_H
    if(Options::getOption_Bool(KJ::USE_LASTFM))
        lastfm->scrobble();
    #endif
    
    //Quit now that everything is cleaned up.
    m_app->exit(0);
    #ifdef HAVE_LASTFM_H
    delete lastfm;
    #endif
    delete controller;
    delete cli;
    
    return 1;
}
