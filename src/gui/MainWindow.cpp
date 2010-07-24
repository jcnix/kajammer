/*
 * File:   mainwindow.h
 * Author: Casey Jones
 *
 * Created on March 2, 2009, 6:47 PM
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

#include "MainWindow.h"

MainWindow::MainWindow(QApplication *app, Manager* manager)
{
    m_manager = manager;
    mediaControls = new MediaControls;
    menuBar = new MenuBar;
    
    setWindowTitle("KaJammer Music Player");
    setMenuBar(menuBar);
    setCentralWidget(mediaControls);
    
    connect(menuBar, SIGNAL(showPlaylists(bool)), mediaControls,
            SLOT(showPlaylists(bool)));
    connect(menuBar, SIGNAL(exit()), m_manager, SLOT(exit()));
}

void MainWindow::showWindow(QSystemTrayIcon::ActivationReason activated)
{
    if(activated == QSystemTrayIcon::Trigger)
    {
        if(!isVisible())
            show();
        else if(isVisible())
            hide();
    }
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    Options::setOption(KJ::MAIN_WIDTH, width());
    Options::setOption(KJ::MAIN_HEIGHT, height());
    
    if(!Options::getOption_Bool(KJ::USE_TRAY_ICON))
        m_manager->exit();
    
    event->accept();
}
