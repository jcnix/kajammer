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
#include "controller.h"

class TrayIcon : public QSystemTrayIcon
{    
public:
    TrayIcon();
    
private:
    QIcon *trayIcon;
};

#endif /* _TRAYICON_H */
