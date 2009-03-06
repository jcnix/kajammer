/*
 * File:   menubar.cpp
 * Author: casey
 *
 * Created on March 4, 2009, 4:35 PM
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
 * along with Foobar.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "menubar.h"
#include "menu.h"
#include <iostream>

MenuBar::MenuBar()
{
    menuBar = new QMenuBar;

    file = new QMenu("&File");
    help = new QMenu("&Help");

    addMenu(file);
    addMenu(help);

    openFile = file->addAction("&Open");
    close =file->addAction("E&xit");

    about = help->addAction("&About");
    
    connect(openFile, SIGNAL(triggered()), this, SLOT(open()));
    connect(close, SIGNAL(triggered()), this, SLOT(quit()));
}

void MenuBar::open()
{
    QString file = QFileDialog::getOpenFileName(this, tr("Open File"),
                    "~/", tr("Music Files (*.mp3 *.ogg *.aac)"));
    
    if(file != NULL)
    {
        fileName = file;
        emit songChanged(fileName);
    }
}

void MenuBar::quit()
{
    exit(0);
}