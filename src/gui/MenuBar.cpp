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
    
    connect(openFile, SIGNAL(triggered()), this, SLOT(open()));
    connect(close, SIGNAL(triggered()), this, SLOT(quit()));
    connect(viewPlaylistsAction, SIGNAL(triggered(bool)), this,
            SLOT(showPlaylistsSlot(bool)));
    connect(optionsAction, SIGNAL(triggered()), this, SLOT(showOptions()));
    connect(playlistEditAction, SIGNAL(triggered()), this, SLOT(showPlaylistEditor()));
    connect(scanAction, SIGNAL(triggered()), this, SLOT(showCollectionScanner()));
    connect(tagEditorAction, SIGNAL(triggered()), this, SLOT(showTagEditor()));
    connect(about, SIGNAL(triggered()), this, SLOT(aboutDialog()));
    connect(aboutQt, SIGNAL(triggered()), this, SLOT(showAboutQt()));
}

void MenuBar::init()
{
    controller = Controller::getInstance();
    listManager = PlaylistManager::getInstance();
    
    menuBar = new QMenuBar;

    file = new QMenu("&File");
    view = new QMenu("&View");
    tools = new QMenu("&Tools");
    help = new QMenu("&Help");

    addMenu(file);
    addMenu(view);
    addMenu(tools);
    addMenu(help);

    openFile = new QAction("&Open...", this);
    close = new QAction("E&xit", this);
    
    openFile->setIcon(style()->standardIcon(QStyle::SP_DialogOpenButton));
    
    openFile->setShortcut(QKeySequence::Open);
    close->setShortcut(QKeySequence::fromString("Ctrl+X", QKeySequence::NativeText));
    
    viewPlaylistsAction = new QAction("View &Playlists", this);
    viewPlaylistsAction->setCheckable(true);
    viewPlaylistsAction->setChecked(Options::getOption_Bool(KJ::SHOW_PLAYLISTS));
    
    optionsAction = new QAction("&Options", this);
    playlistEditAction = new QAction("&Playlist Editor", this);
    scanAction = new QAction("&Scan Collection", this);
    tagEditorAction = new QAction("&Tag Editor", this);
    
    about = new QAction("&About", this);
    aboutQt = new QAction("About &Qt", this);

    file->addAction(openFile);
    file->addSeparator();
    file->addAction(close);
    
    view->addAction(viewPlaylistsAction);
    
    tools->addAction(optionsAction);
    tools->addAction(playlistEditAction);
    tools->addAction(scanAction);
    tools->addAction(tagEditorAction);
    
    help->addAction(about);
    help->addAction(aboutQt);
}

void MenuBar::open()
{
    QString defaultDir = Options::getOption_String(KJ::DEFAULT_OPEN_DIR);
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

void MenuBar::showPlaylistsSlot(bool b)
{
    emit showPlaylists(b);
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

void MenuBar::showTagEditor()
{
    TagEditor *te = new TagEditor;
    te->show();
}

void MenuBar::aboutDialog()
{
    AboutDialog *about = new AboutDialog;
    about->show();
}

void MenuBar::showAboutQt()
{
    QMessageBox::aboutQt(this);
}

void MenuBar::quit()
{
    emit exit();
}