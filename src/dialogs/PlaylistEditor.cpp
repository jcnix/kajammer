/*
 * File:   playlistEditor.cpp
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

#include "PlaylistEditor.h"

PlaylistEditor::PlaylistEditor()
{
    init();
    
    connect(playlistList, SIGNAL(itemActivated(QListWidgetItem*)), 
            this, SLOT(openPlaylist(QListWidgetItem*)));
    connect(buttonBox, SIGNAL(accepted()), this, SLOT(save()));
    connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));
    connect(btnAdd, SIGNAL(clicked()), this, SLOT(addTracks()));
    connect(btnRemove, SIGNAL(clicked()), this, SLOT(removeTracks()));
    connect(btnUp, SIGNAL(clicked()), this, SLOT(moveTracksUp()));
    connect(btnDown, SIGNAL(clicked()), this, SLOT(moveTracksDown()));
}

PlaylistEditor::~PlaylistEditor()
{
    delete playlistList;
    delete playlistContents;
    delete btnAdd;
    delete btnDown;
    delete btnRemove;
    delete buttonBox;
    delete squeezeTopLayout;
    delete topLayout;
    delete controlSqueezeLayout;
    delete controlLayout;
    delete vLayout;
}

void PlaylistEditor::init()
{
    setWindowTitle("KaJammer Playlist Editor");
    setMinimumSize(480,480);

    listManager = PlaylistManager::getInstance();
    options = Options::getInstance();

    playlistList = new QListWidget;
    fillPlaylists();
    
    playlistContents = new QListWidget;
    playlistContents->setSelectionMode(QAbstractItemView::MultiSelection);

    btnAdd = new QPushButton("Add");
    btnUp = new QPushButton(style()->standardIcon(QStyle::SP_ArrowUp), "");
    btnDown = new QPushButton(style()->standardIcon(QStyle::SP_ArrowDown), "");
    btnRemove = new QPushButton("Remove");

    btnAdd->setMaximumWidth(75);
    btnUp->setMaximumWidth(50);
    btnDown->setMaximumWidth(50);
    btnRemove->setMaximumWidth(75);

    buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | 
            QDialogButtonBox::Cancel);

    //Squeeze Layout "squeezes" widgets together so they don't spread
            
    squeezeTopLayout = new QHBoxLayout;
    squeezeTopLayout->addWidget(btnAdd);
    squeezeTopLayout->addWidget(btnRemove);

    QHBoxLayout *topLayout = new QHBoxLayout;
    topLayout->addLayout(squeezeTopLayout);

    controlSqueezeLayout = new QHBoxLayout;
    controlSqueezeLayout->addWidget(btnUp);
    controlSqueezeLayout->addWidget(btnDown);

    controlLayout = new QHBoxLayout;
    controlLayout->addLayout(controlSqueezeLayout);

    vLayout = new QVBoxLayout;
    vLayout->addWidget(playlistList);
    vLayout->addWidget(playlistContents);
    vLayout->addLayout(topLayout);
    vLayout->addLayout(controlLayout);
    vLayout->addWidget(buttonBox);
    
    setLayout(vLayout);
}

void PlaylistEditor::fillPlaylists()
{
    QStringList lists = listManager->getPlaylistNames();
    for(int i = 0; i < lists.count(); i++)
    {
        playlistList->addItem(lists.at(i));
    }
}

void PlaylistEditor::save()
{
    QStringList text;
    int rows = playlistContents->count();
    for(int i = 0; i < rows; i++) {
        QListWidgetItem *item = playlistContents->item(i);
        text.append(playlistMap.value(item));
    }

    listManager->delPlaylist(playlistFile);
    listManager->newPlaylist(playlistFile, text);

    accept();
}

void PlaylistEditor::openPlaylist(QListWidgetItem* item)
{    
    QString playlistDir = QDir::homePath() + "/.kajammer/playlists/";
    QString playlistFile = playlistDir + item->text();
    
    // figure out the playlist's name, we don't need the full path
    QFileInfo file(playlistFile);
    playlistFile = file.fileName();
    QStringList list = listManager->getPlaylistContents(playlistFile);
    
    for(int i = 0; i < list.length(); i++)
    {
        QFileInfo f(list.at(i));
        QListWidgetItem *item = new QListWidgetItem(f.fileName());
        playlistContents->addItem(item);
        playlistMap.insert(item, list.at(i));
    }
}

void PlaylistEditor::addTracks()
{
    QString defaultDir = options->getDefaultOpenDir();

    QStringList list = QFileDialog::getOpenFileNames(this, tr("Open File"), defaultDir, 
                                        tr("Music Files (*.mp3 *.ogg *.aac *.flac *.wma *.wav)"));

    for(int i = 0; i < list.length(); i++)
    {
        QFileInfo f(list.at(i));
        QListWidgetItem *item = new QListWidgetItem(f.fileName());
        playlistContents->addItem(item);
        playlistMap.insert(item, list.at(i));
    }
}

void PlaylistEditor::removeTracks()
{
    QList<QListWidgetItem*> items = playlistContents->selectedItems();
    for(int i = 0; i < items.length(); i++)
    {
        playlistContents->takeItem(playlistContents->row(items.at(i)));
        playlistMap.remove(items.at(i));
    }
}

void PlaylistEditor::moveTracksUp()
{
    QList<QListWidgetItem*> items = playlistContents->selectedItems();

    /* We need to sort the selected rows.
        * If they're unsorted, adjacent selected rows
        * will alternate which row goes first.  If a lower
        * row goes first it conflicts with the above 
        * selected row. So always make the above rows go first
        */
    QSet<int> set;
    for(int i = 0; i < items.size(); i++)
    {
        QListWidgetItem *item = items.at(i);
        int row = playlistContents->row(item);

        set << row;
    }

    QList<int> rowList = QList<int>::fromSet(set);
    qSort(rowList);

    //Now move the item
    for(int i = 0; i < rowList.size(); i++)
    {
        int row = rowList.at(i);
        QListWidgetItem *item = playlistContents->takeItem(row);
        
        playlistContents->insertItem(--row, item); //moves up
        playlistContents->setCurrentRow(row);
    }
}

void PlaylistEditor::moveTracksDown()
{
    QList<QListWidgetItem*> items = playlistContents->selectedItems();

    /* We need to sort the selected rows.
        * If they're unsorted, adjacent selected rows
        * will alternate which row goes first.  If a lower
        * row goes first it conflicts with the above 
        * selected row. So always make the above rows go first
        */
    QSet<int> set;
    for(int i = 0; i < items.size(); i++)
    {
        QListWidgetItem *item = items.at(i);
        int row = playlistContents->row(item);

        set << row;
    }

    QList<int> rowList = QList<int>::fromSet(set);
    qSort(rowList);

    //Now move the item, iterate backwards
    for(int i = rowList.size() - 1; i >= 0; i--)
    {
        int row = rowList.at(i);
        QListWidgetItem *item = playlistContents->takeItem(row);
        
        playlistContents->insertItem(++row, item); //moves up
        playlistContents->setCurrentRow(row);
    }
}

void PlaylistEditor::closeEvent(QCloseEvent *event)
{
    done(0);
    delete this;
    event->accept();
}
