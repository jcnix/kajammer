/*
 * File:   trayicon.h
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

#ifndef _TRAYICON_H
#define _TRAYICON_H

#include <QtGui/QSystemTrayIcon>
#include <QtGui/QIcon>
#include <QtGui/QMenu>
#include <QtGui/QAction>
#include <QtGui/QStyle>

#include "../../Controller.h"
#include "../../Options.h"

class TrayIcon : public QSystemTrayIcon
{   
    Q_OBJECT;
    
public:
    TrayIcon();
    
public slots:
    void songChanged();
    void openContextMenu(QSystemTrayIcon::ActivationReason);
    void quit();
    
signals:
    void exit();
    
private:
    Controller *controller;
    
    QIcon *trayIcon;
    QMenu *menu;
    QAction *nextAction;
    QAction *playAction;
    QAction *pauseAction;
    QAction *prevAction;
    QAction *quitAction;
};

#endif /* _TRAYICON_H */
