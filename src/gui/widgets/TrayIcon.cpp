/*
 * File:   trayicon.cpp
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

#include "TrayIcon.h"

TrayIcon::TrayIcon() : QSystemTrayIcon()
{
    controller = Controller::getInstance();
    
    trayIcon = new QIcon("/usr/share/icons/kajammer.png");
    setIcon(*trayIcon);
    setVisible(true);
    
    menu = new QMenu("KaJammer");
    nextAction = new QAction("Next", this);
    playAction = new QAction("Play", this);
    pauseAction = new QAction("Pause", this);
    prevAction = new QAction("Prev", this);
    quitAction = new QAction("Quit", this);
    
    menu->addAction(nextAction);
    menu->addAction(playAction);
    menu->addAction(pauseAction);
    menu->addAction(prevAction);
    menu->addAction(menu->addSeparator());
    menu->addAction(quitAction);
    setContextMenu(menu);
    
    connect(this, SIGNAL(activated(QSystemTrayIcon::ActivationReason)), 
             this, SLOT(openContextMenu(QSystemTrayIcon::ActivationReason)));
    
    connect(nextAction, SIGNAL(triggered()), controller, SLOT(setNextSong()));
    connect(playAction, SIGNAL(triggered()), controller, SLOT(play()));
    connect(pauseAction, SIGNAL(triggered()), controller, SLOT(pause()));
    connect(prevAction, SIGNAL(triggered()), controller, SLOT(setPrevSong()));
    connect(quitAction, SIGNAL(triggered()), this, SLOT(quit()));
}

void TrayIcon::openContextMenu(QSystemTrayIcon::ActivationReason activated)
{
    if(activated == QSystemTrayIcon::Context)
    {
        menu->show();
    }
}

void TrayIcon::quit()
{
    Manager *manager = Manager::getInstance();
    manager->exit();
}
