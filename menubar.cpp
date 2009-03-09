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
 * along with KaJammer.  If not, see <http://www.gnu.org/licenses/>.
 */


#include "menubar.h"

MenuBar::MenuBar()
{
    menuBar = new QMenuBar;

    file = new QMenu("&File");
    help = new QMenu("&Help");

    addMenu(file);
    addMenu(help);

    openFile = new QAction("&Open", this);
    close = new QAction("E&xit", this);
    about = new QAction("&About", this);

    openFile->setShortcut(QKeySequence::Open);
    close->setShortcut(QKeySequence::fromString("Ctrl+X", QKeySequence::NativeText));
    
    file->addAction(openFile);
    file->addAction(close);
    help->addAction(about);
    
    connect(openFile, SIGNAL(triggered()), this, SLOT(open()));
    connect(close, SIGNAL(triggered()), this, SLOT(quit()));
    connect(about, SIGNAL(triggered()), this, SLOT(aboutDialog()));
}

void MenuBar::open()
{
    fileQueue = QFileDialog::getOpenFileNames(this, tr("Open File"),
            "~/", tr("Music Files (*.mp3 *.ogg *.aac)"));

    nextSong();
}

void MenuBar::nextSong()
{
    //If user cancels out of open dialog, don't stop playing the current song
    if(!fileQueue.isEmpty())
    {
        fileName = fileQueue.first();
        fileQueue.removeFirst();
        emit songChanged(fileName);
    }
}

void MenuBar::aboutDialog()
{
    QMessageBox::information(this, ("About KaJammer"),
             "KaJammer MediaPlayer 0.1");
}

void MenuBar::quit()
{
    exit(0);
}