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
    init();
    
    connect(newPlaylist, SIGNAL(triggered()), this, SLOT(createNewPlaylist()));
    connect(openFile, SIGNAL(triggered()), this, SLOT(open()));
    connect(delPlaylist, SIGNAL(triggered()), this, SLOT(deletePlaylist()));
    connect(close, SIGNAL(triggered()), this, SLOT(quit()));
    connect(about, SIGNAL(triggered()), this, SLOT(aboutDialog()));
}

void MenuBar::init()
{
    controller = Controller::getInstance();
    playlist = Playlist::getInstance();
    
    menuBar = new QMenuBar;

    file = new QMenu("&File");
    help = new QMenu("&Help");

    addMenu(file);
    addMenu(help);
    
    newPlaylist = new QAction("&New Playlist...", this);
    openFile = new QAction("&Open...", this);
    delPlaylist = new QAction("&Delete Playlist...", this);
    close = new QAction("E&xit", this);
    about = new QAction("&About", this);
    
    newPlaylist->setShortcut(QKeySequence::New);
    openFile->setShortcut(QKeySequence::Open);
    close->setShortcut(QKeySequence::fromString("Ctrl+X", QKeySequence::NativeText));

    file->addAction(newPlaylist);
    file->addAction(openFile);
    file->addAction(delPlaylist);
    file->addSeparator();
    file->addAction(close);
    help->addAction(about);
}

void MenuBar::createNewPlaylist()
{
    bool ok;
    QStringList addToList;
    
    QString input = QInputDialog::getText(this, "New Playlist", "Enter Playlist Name:",
                                           QLineEdit::Normal, "",
                                           &ok);
    if(ok && !input.isEmpty())
    {
        addToList = QFileDialog::getOpenFileNames(this, tr("Open File"), "~/", 
                                                   tr("Music Files (*.mp3 *.ogg *.aac)"));
                                                   
        if(!addToList.isEmpty())
        {
            playlist->newPlaylist(input, addToList);
        }
    }
}

void MenuBar::deletePlaylist()
{
    bool ok;
    
    QString input = QInputDialog::getText(this, "Delete Playlist", "Enter Playlist Name:",
                                           QLineEdit::Normal, "",
                                           &ok);
    if(ok && !input.isEmpty())
    {
        playlist->delPlaylist(input);
    }
}

void MenuBar::open()
{
    fileQueue = QFileDialog::getOpenFileNames(this, tr("Open File"), "~/", 
                                               tr("Music Files (*.mp3 *.ogg *.aac)"));
    //Make sure user didn't cancel out of the dialog
    if(!fileQueue.isEmpty())
    {
        controller->setQueue(fileQueue);
    }
}   

void MenuBar::aboutDialog()
{
    QMessageBox::information(this, ("About KaJammer"),
                            "KaJammer Media Player 0.4.5\n"
                            "Licensed under the GPLv3.\n\n"
                            "You are using a development version, keep your "
                            "git repository up to date for the latest version");
}

void MenuBar::quit()
{
    exit(0);
}