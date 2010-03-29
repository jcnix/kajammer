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

MenuBar::MenuBar(QApplication *app)
{
    m_app = app;
    init();
    
    connect(openFile, SIGNAL(triggered()), this, SLOT(open()));
    connect(close, SIGNAL(triggered()), this, SLOT(quit()));
    connect(optionsAction, SIGNAL(triggered()), this, SLOT(showOptions()));
    connect(playlistEditAction, SIGNAL(triggered()), this, SLOT(showPlaylistEditor()));
    connect(scanAction, SIGNAL(triggered()), this, SLOT(showCollectionScanner()));
    connect(about, SIGNAL(triggered()), this, SLOT(aboutDialog()));
    connect(aboutQt, SIGNAL(triggered()), m_app, SLOT(aboutQt()));
}

void MenuBar::init()
{
    controller = Controller::getInstance();
    listManager = PlaylistManager::getInstance();
    options = Options::getInstance();
    
    menuBar = new QMenuBar;

    file = new QMenu("&File");
    tools = new QMenu("&Tools");
    help = new QMenu("&Help");

    addMenu(file);
    addMenu(tools);
    addMenu(help);

    openFile = new QAction("&Open...", this);
    close = new QAction("E&xit", this);
    
    openFile->setIcon(style()->standardIcon(QStyle::SP_DialogOpenButton));
    
    optionsAction = new QAction("&Options", this);
    playlistEditAction = new QAction("&Playlist Editor", this);
    scanAction = new QAction("&Scan Collection", this);
    
    about = new QAction("&About", this);
    aboutQt = new QAction("About &Qt", this);
    
    openFile->setShortcut(QKeySequence::Open);
    close->setShortcut(QKeySequence::fromString("Ctrl+X", QKeySequence::NativeText));

    file->addAction(openFile);
    file->addSeparator();
    file->addAction(close);
    
    tools->addAction(optionsAction);
    tools->addAction(playlistEditAction);
    tools->addAction(scanAction);
    
    help->addAction(about);
    help->addAction(aboutQt);
}

void MenuBar::open()
{
    QString defaultDir = options->getDefaultOpenDir();
    QString filter = "Music Files (" + MUSIC_TYPES + ");;All Files(*)";
    
    QStringList fileQueue = QFileDialog::getOpenFileNames(this, tr("Open File"),
                                                          defaultDir, filter);
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
    PlaylistEditor *editor = new PlaylistEditor;
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