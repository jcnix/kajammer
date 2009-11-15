/*
 * File:   AboutDialog.cpp
 * Author: Casey Jones
 *
 * Created on November 13, 2009, 11:44 PM
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

#include "AboutDialog.h"

AboutDialog::AboutDialog()
{
    init();
}

void AboutDialog::init()
{
    setWindowTitle("About KaJammer");
    
    QPixmap icon(KAJAMMER_ICON);
    icon = icon.scaled(64,64);
    
    iconLabel = new QLabel();
    iconLabel->setPixmap(icon);
    
    topLayout = new QHBoxLayout;
    topLayout->addWidget(iconLabel);
    
    layout = new QVBoxLayout;
    layout->addLayout(topLayout);
    
    setLayout(layout);
}
