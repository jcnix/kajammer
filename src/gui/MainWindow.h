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

#ifndef _MAINWINDOW_H
#define _MAINWINDOW_H

#include <QtGui/QMainWindow>
#include <QtGui/QSystemTrayIcon>
#include <QtCore/QObject>

#include "MediaControls.h"
#include "MenuBar.h"
#include "../Options.h"

class MenuBar;

class MainWindow : public QMainWindow
{
    Q_OBJECT;
    
public:
    MainWindow(QApplication*);

public slots:
    void showWindow(QSystemTrayIcon::ActivationReason);
    
protected:
    void closeEvent(QCloseEvent*);    
    
private:
    Controller *controller;
    MenuBar *menuBar;
    MediaControls *mediaControls;    
};

#endif  /* _MAINWINDOW_H */
