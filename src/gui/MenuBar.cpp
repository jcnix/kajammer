/*
 * File:   menubar.cpp
 * Author: Casey Jones
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

#include "MenuBar.h"

MenuBar::MenuBar()
{
    init();
    
    connect(newPlaylist, SIGNAL(triggered()), this, SLOT(createNewPlaylist()));
    connect(openFile, SIGNAL(triggered()), this, SLOT(open()));
    connect(delPlaylist, SIGNAL(triggered()), this, SLOT(deletePlaylist()));
    connect(close, SIGNAL(triggered()), this, SLOT(quit()));
    connect(optionsAction, SIGNAL(triggered()), this, SLOT(showOptions()));
    connect(playlistEditAction, SIGNAL(triggered()), this, SLOT(showPlaylistEditor()));
    connect(scanAction, SIGNAL(triggered()), this, SLOT(showCollectionScanner()));
    connect(about, SIGNAL(triggered()), this, SLOT(aboutDialog()));
}

void MenuBar::init()
{
    controller = Controller::getInstance();
    playlist = Playlist::getInstance();
    options = Options::getInstance();
    
    menuBar = new QMenuBar;

    file = new QMenu("&File");
    tools = new QMenu("&Tools");
    help = new QMenu("&Help");

    addMenu(file);
    addMenu(tools);
    addMenu(help);
    
    newPlaylist = new QAction("&New Playlist...", this);
    openFile = new QAction("&Open...", this);
    delPlaylist = new QAction("&Delete Playlist...", this);
    close = new QAction("E&xit", this);
    
    optionsAction = new QAction("&Options", this);
    playlistEditAction = new QAction("&Playlist Editor", this);
    scanAction = new QAction("&Scan Collection", this);
    
    about = new QAction("&About", this);
    
    newPlaylist->setShortcut(QKeySequence::New);
    openFile->setShortcut(QKeySequence::Open);
    close->setShortcut(QKeySequence::fromString("Ctrl+X", QKeySequence::NativeText));

    file->addAction(newPlaylist);
    file->addAction(openFile);
    file->addAction(delPlaylist);
    file->addSeparator();
    file->addAction(close);
    
    tools->addAction(optionsAction);
    tools->addAction(playlistEditAction);
    tools->addAction(scanAction);
    
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
        QString defaultDir = options->getDefaultOpenDir();
        addToList = QFileDialog::getOpenFileNames(this, tr("Open File"), defaultDir, 
                                                   tr("Music Files (*.mp3 *.ogg *.aac)"));
                                                   
        if(!addToList.isEmpty())
        {
            playlist->newPlaylist(input, addToList);
            controller->resetCurrentList();
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
    QString defaultDir = options->getDefaultOpenDir();
    
    QStringList fileQueue = QFileDialog::getOpenFileNames(this, tr("Open File"), defaultDir, 
                                    tr("Music Files (*.mp3 *.ogg *.aac *.flac *.wma *.wav)"));
    //Make sure user didn't cancel out of the dialog
    if(!fileQueue.isEmpty())
    {
        controller->resetCurrentList();
        controller->setQueue(fileQueue);
    }
}

void MenuBar::showOptions()
{
    OptionsPanel *panel;
    panel = new OptionsPanel;
    panel->show();
}

void MenuBar::showPlaylistEditor() 
{
    PlaylistEditor *editor;
    editor = new PlaylistEditor;
    editor->show();
}

void MenuBar::showCollectionScanner()
{
    CollectionScanner *cs = new CollectionScanner;
    cs->show();
}

void MenuBar::aboutDialog()
{
    AboutDialog *about = new AboutDialog;
    about->show();
}

void MenuBar::quit()
{
    Manager *manager = Manager::getInstance();
    manager->exit();
}