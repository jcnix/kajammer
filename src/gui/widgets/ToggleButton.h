/* 
 * File:   togglebutton.h
 * Author: Casey Jones
 *
 * Created on March 3, 2009, 6:49 PM
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

#ifndef _TOGGLEBUTTON_H
#define _TOGGLEBUTTON_H

#include <QtGui/QPushButton>
#include <QtGui/QPainter>
#include <QtGui/QWidget>
#include <QtGui/QPaintEvent>
#include <QtGui/QBrush>
#include <QtGui/QColor>
#include <QtGui/QPalette>
#include <iostream>

//This class will highlight a button when pressed
class ToggleButton : public QPushButton
{
    Q_OBJECT;
    
public:
    ToggleButton(QString);
    
public slots:
    void click();
    
private:
    bool isClicked;
    QPalette defaultPal;
    QPalette *clickedPal;
};

#endif /* _TOGGLEBUTTON_H */
