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

//don't put kajamtag.h at the end of includes,
//mainwindow.cpp thinks it defined k_tags first; it didn't.
//I don't know why it thinks it did, or why putthing this at the top works
extern "C" {
#include <kajamtag/kajamtag.h>
}

#include "headers/mediacontrols.h"

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
    connect(metaResolver, SIGNAL(metaDataChanged()), this, SLOT(setMetaData()));
    connect(table, SIGNAL(cellClicked(int, int)), this, SLOT(tableClicked(int)));
    connect(playlistTable, SIGNAL(cellClicked(int, int)), this, SLOT(changePlaylist(int)));
    connect(playlist, SIGNAL(resetPlaylists()), this, SLOT(setupPlaylists()));
    
    /* If table is empty, re-emit the song list.
     * If the user used -p on the command line, this class will not
     * have recieved the first emit */
    if(table->rowCount() == 0)
        controller->emitList();
}

void MediaControls::init()
{
    controller = Controller::getInstance();
    playlist = Playlist::getInstance();
    tableIndex = 0;

    metaResolver = new Phonon::MediaObject;  //Used for finding metadata
    
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
    //Set source so we activate metaDataChanged(), so it loops through our table
    metaResolver->setCurrentSource(metaSources.at(0));
    //setMetaData();
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

//Fills the music table with ID3 tag data.
void MediaControls::setMetaData()
{    
    for(int i = 0; i < metaSources.count(); i++)
    {
        QString strFile = metaSources.at(i).fileName();
        char* file = new char[strFile.size()+1];
        strcpy(file, strFile.toStdString().c_str());
        
        kajamtag_init(file);
        
        char* c_title = k_getTitle();
        char* c_artist = k_getArtist();
        char* c_album = k_getAlbum();
        
        QString *title = new QString(c_title);
        QString *artist = new QString(c_artist);
        QString *album = new QString(c_album);
        
        //"BAD_TAG" means Kajamtag doesn't recognize the tag format.
        if (title->compare("") == 0 || title->compare("BAD_TAG") == 0)
        {
            QFileInfo file(strFile);
            *title = file.baseName();
        }
        
        //If one is bad, they're all bad.
        if(artist->compare("BAD_TAG") == 0) {
            *artist = "";
            *album = "";
        }
        
        QTableWidgetItem *indexItem = new QTableWidgetItem(QString::number(tableIndex++));
        QTableWidgetItem *titleItem = new QTableWidgetItem(*title);
        QTableWidgetItem *artistItem = new QTableWidgetItem(*artist);
        QTableWidgetItem *albumItem = new QTableWidgetItem(*album);
    
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

        Phonon::MediaSource source = metaResolver->currentSource();
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
    }
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
    
    QStringList labels;
    
    for(int i = 0; i < playlist->count(); i++)
    {
        QString list = playlist->getPlaylistName(i);
        
        QTableWidgetItem *listName = new QTableWidgetItem(list);
        listName->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
        
        playlistTable->insertRow(i);
        playlistTable->setItem(i, 0, listName);
        
        //Don't put row numbers on the table
        labels.append("");
        playlistTable->setVerticalHeaderLabels(labels);
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
