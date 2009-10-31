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

#include "headers/mainwindow.h"

MainWindow::MainWindow()
{
    setWindowTitle("KaJammer Music Player");

    menuBar = new MenuBar;
    setMenuBar(menuBar);

    mediaControls = new MediaControls;
    setCentralWidget(mediaControls);
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
    Options *options = Options::getInstance();
    options->setMainWidth(width());
    options->setMainHeight(height());
    options->save();
    
    event->accept();
}
