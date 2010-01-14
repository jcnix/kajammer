/*
 * File:   mediacontrols.cpp
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

#include "MediaControls.h"

MediaControls::MediaControls(QWidget *parent) : QWidget(parent)
{
    init();
    
    connect(play, SIGNAL(clicked()), this, SLOT(playPressed()));
    connect(next, SIGNAL(clicked()), controller, SLOT(setNextSong()));
    connect(prev, SIGNAL(clicked()), controller, SLOT(setPrevSong()));
    connect(shuffleBtn, SIGNAL(clicked()), this, SLOT(shufflePressed()));
    connect(repeatBtn, SIGNAL(clicked()), this, SLOT(repeatPressed()));
    
    connect(controller, SIGNAL(songChanged(int)), this, SLOT(songChanged(int)));
    connect(controller, SIGNAL(queueSet(QList<Phonon::MediaSource>)), this,
            SLOT(getQueue(QList<Phonon::MediaSource>)));
    connect(controller->getMetaResolver(), SIGNAL(metaDataChanged()), this, SLOT(setMetaData()));
    connect(table, SIGNAL(cellClicked(int, int)), this, SLOT(tableClicked(int)));
    connect(playlistTable, SIGNAL(cellClicked(int, int)), this, SLOT(changePlaylist(int)));
    connect(listManager, SIGNAL(resetPlaylists()), this, SLOT(setupPlaylists()));
    connect(searchBar, SIGNAL(returnPressed()), this, SLOT(search()));
    
    /* If table is empty, re-emit the song list.
     * If the user used -p on the command line, this class will not
     * have recieved the first emit */
    if(table->rowCount() == 0)
        controller->emitList();
}

void MediaControls::init()
{
    controller = Controller::getInstance();
    listManager = PlaylistManager::getInstance();
    tableIndex = 0;
    
    volumeSlider = new Phonon::VolumeSlider;
    volumeSlider->setAudioOutput(controller->getAudioOutput());
    volumeSlider->setMaximumWidth(100);

    seekSlider = new Phonon::SeekSlider;
    seekSlider->setTracking(false);
    seekSlider->setMediaObject(controller->getMediaObject());

    //Media Control buttons
    play = new QPushButton(style()->standardIcon(QStyle::SP_MediaPlay), "", this);
    next = new QPushButton(style()->standardIcon(QStyle::SP_MediaSkipForward), "", this);
    prev = new QPushButton(style()->standardIcon(QStyle::SP_MediaSkipBackward), "", this);
    
    play->setShortcut(Qt::Key_Space);
    next->setShortcut(Qt::Key_Right);
    prev->setShortcut(Qt::Key_Left);
    
    shuffleBtn = new ToggleButton("S");
    repeatBtn = new ToggleButton("R");
    
    searchBar = new QLineEdit("Search");
    searchBar->setFixedWidth(150);
    
    //Table with meta info
    table = new QTableWidget;
    table->setColumnCount(4);
    QStringList tableHeaders;
    tableHeaders.append("Track");
    tableHeaders.append("Title");
    tableHeaders.append("Artist");
    tableHeaders.append("Album");
    table->setHorizontalHeaderLabels(tableHeaders);
    table->setSelectionBehavior(QAbstractItemView::SelectRows);
    table->setShowGrid(false);
    
    playlistTable = new QTableWidget;
    playlistTable->setColumnCount(1);
    QStringList playlistHeaders;
    playlistHeaders.append("Playlists");
    playlistTable->setHorizontalHeaderLabels(playlistHeaders);
    playlistTable->setShowGrid(false);
    playlistTable->setMaximumWidth(PLAYLIST_WIDTH);
    setupPlaylists(); //Fill table with playlists
    
    QHBoxLayout *tableLayout = new QHBoxLayout;
    tableLayout->addWidget(playlistTable);
    tableLayout->addWidget(table);
    
    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(prev);
    buttonLayout->addWidget(play);
    buttonLayout->addWidget(next);
    
    QHBoxLayout *shuffleRepeatLayout = new QHBoxLayout;
    shuffleRepeatLayout->addWidget(shuffleBtn);
    shuffleRepeatLayout->addWidget(repeatBtn);
    
    QHBoxLayout *hLayout = new QHBoxLayout;
    hLayout->addLayout(buttonLayout);
    hLayout->addLayout(shuffleRepeatLayout);
    hLayout->addWidget(volumeSlider);

    QVBoxLayout *vLayout = new QVBoxLayout;
    vLayout->addWidget(searchBar);
    vLayout->addLayout(tableLayout);
    vLayout->addWidget(seekSlider);
    vLayout->addLayout(hLayout);
    setLayout(vLayout);
}

void MediaControls::songChanged(int row)
{
    table->selectRow(row);
}

//New files opened, get the list of songs.
void MediaControls::getQueue(QList<Phonon::MediaSource> meta)
{
    metaSources = meta;
    #ifndef HAVE_KAJAMTAG_H
    setMetaData();
    #endif
    table->setRowCount(0);
    tableIndex = 1;
}

//Created these functions to reset keyboard shortcuts
void MediaControls::playPressed()
{
    if(controller->isPaused())
    {
        controller->play();
    }
    else
        controller->pause();
}

void MediaControls::shufflePressed()
{
    controller->toggleShuffle();
}

void MediaControls::repeatPressed()
{
    controller->toggleRepeat();
}

void MediaControls::search()
{
    CollectionManager *cm = new CollectionManager;
    
    QString query = searchBar->text();
    QStringList result = cm->search(query);
    
    controller->setQueue(result);
    
    cm->close_db();
    delete cm;
    
    setMetaData();
}

//Fills the music table with ID3 tag data.
void MediaControls::setMetaData()
{
    //kajamtag will only read one file at a time
    //Phonon will use signals to advance to the next file
    #ifdef HAVE_KAJAMTAG_H
    for(int i = 0; i < metaSources.count(); i++)
    {
        QString strFile = metaSources.at(i).fileName();
        QMap<QString, QString> metaData = controller->getMetadata(strFile);
        #else
        QMap<QString, QString> metaData = controller->getMetadata("");
        #endif
        
        QString title = metaData.value("TITLE");
        QString artist = metaData.value("ARTIST");
        QString album = metaData.value("ALBUM");
        
        QTableWidgetItem *indexItem = new QTableWidgetItem(QString::number(tableIndex++));
        QTableWidgetItem *titleItem = new QTableWidgetItem(title);
        QTableWidgetItem *artistItem = new QTableWidgetItem(artist);
        QTableWidgetItem *albumItem = new QTableWidgetItem(album);
    
        titleItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
        artistItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
        albumItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
        indexItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
    
        int row = table->rowCount();
        table->insertRow(row);
        table->setItem(row, 0, indexItem);
        table->setItem(row, 1, titleItem);
        table->setItem(row, 2, artistItem);
        table->setItem(row, 3, albumItem);
        
        //Don't put row numbers on the table
        tableLabels.append("");
        table->setVerticalHeaderLabels(tableLabels);

        Phonon::MediaSource source = controller->getMetaResolver()->currentSource();
        int index = metaSources.indexOf(source) + 1;
        if (metaSources.count() > index) 
        {
            table->resizeColumnsToContents();
            
            if (table->columnWidth(1) > 300)
                table->setColumnWidth(1, 300);
            else 
            {
                //Make columns just a bit bigger, so things aren't squeezed
                table->setColumnWidth(1, table->columnWidth(1) + 20);
                table->setColumnWidth(2, table->columnWidth(2) + 20);
            }
        }
    #ifdef HAVE_KAJAMTAG_H
    }
    #endif
}

void MediaControls::tableClicked(int row)
{
    //row 0 is track 1, row 5 is track 6, etc.
    controller->setSong(row + 1);
}

// Fill playlist table with playlists
void MediaControls::setupPlaylists()
{
    //Clear out playlistTable
    playlistTable->setRowCount(0);
    
    QStringList labels = listManager->getPlaylistNames();
    QStringList emptyLabels;
    
    for(int i = 0; i < labels.count(); i++)
    {
        QString list = labels.at(i);
        
        QTableWidgetItem *listName = new QTableWidgetItem(list);
        listName->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
        
        playlistTable->insertRow(i);
        playlistTable->setItem(i, 0, listName);
        
        //Don't put row numbers on the table
        emptyLabels.append("");
        playlistTable->setVerticalHeaderLabels(emptyLabels);
    }
    
    /* Subtract 35, so the column doesn't stretch past the table width
    * 35 seems to works best, but it seems like way too much to me*/
    playlistTable->setColumnWidth(0, PLAYLIST_WIDTH - 35);
}

// Get the name of the playlist, and switch to it.
void MediaControls::changePlaylist(int row)
{
    QTableWidgetItem *clickedList = playlistTable->item(row, 0);
    QString name = clickedList->text();
    controller->changePlaylist(name, row);
}
