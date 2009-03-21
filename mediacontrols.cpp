/*
 * File:   mediacontrols.cpp
 * Author: cjones
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

#include <QtGui/qabstractitemview.h>


#include "mediacontrols.h"

MediaControls::MediaControls(QWidget *parent) : QWidget(parent)
{
    init();

    connect(play, SIGNAL(clicked()), mediaObject, SLOT(play()));
    connect(pause, SIGNAL(clicked()), mediaObject, SLOT(pause()));
    connect(next, SIGNAL(clicked()), this, SLOT(setNextSong()));
    connect(prev, SIGNAL(clicked()), this, SLOT(setPrevSong()));
    
    connect(controller, SIGNAL(songChanged(Phonon::MediaSource)), this,    SLOT(changeSong(Phonon::MediaSource)));
    connect(mediaObject, SIGNAL(finished()), this, SLOT(songEnded()));
    connect(this, SIGNAL(playNextSong()), this, SLOT(setNextSong()));
    
    connect(controller, SIGNAL(queueSet(QList<Phonon::MediaSource>)), this,
            SLOT(getQueue(QList<Phonon::MediaSource>)));
    connect(metaResolver, SIGNAL(metaDataChanged()), this, SLOT(setMetaData()));
    connect(table, SIGNAL(cellClicked(int, int)), this, SLOT(tableClicked(int)));
}

void MediaControls::init()
{
    controller = Controller::getInstance();

    audioOutput = new Phonon::AudioOutput(Phonon::MusicCategory);
    mediaObject = new Phonon::MediaObject;
    Phonon::Path path = Phonon::createPath(mediaObject, audioOutput);
    metaResolver = new Phonon::MediaObject;
    index = 0;

    volumeSlider = new Phonon::VolumeSlider;
    volumeSlider->setAudioOutput(audioOutput);
    //volumeSlider->setMaximumWidth(100);

    seekSlider = new Phonon::SeekSlider;
    seekSlider->setTracking(false);
    seekSlider->setMediaObject(mediaObject);

    //Media Control buttons
    play = new QPushButton(style()->standardIcon(QStyle::SP_MediaPlay), "", this);
    pause = new QPushButton(style()->standardIcon(QStyle::SP_MediaPause), "", this);
    next = new QPushButton(style()->standardIcon(QStyle::SP_MediaSkipForward), "", this);
    prev = new QPushButton(style()->standardIcon(QStyle::SP_MediaSkipBackward), "", this);

    //Table with meta info
    table = new QTableWidget();
    table->setColumnCount(3);
    QStringList tableHeaders;
    tableHeaders.append("Title");
    tableHeaders.append("Artist");
    tableHeaders.append("Album");
    table->setHorizontalHeaderLabels(tableHeaders);
    table->setSelectionBehavior(QAbstractItemView::SelectRows);
    table->setShowGrid(false);

    hLayout = new QHBoxLayout;
    hLayout->addWidget(prev);
    hLayout->addWidget(play);
    hLayout->addWidget(pause);
    hLayout->addWidget(next);
    hLayout->addWidget(volumeSlider);

    vLayout = new QVBoxLayout;
    vLayout->addWidget(table);
    vLayout->addWidget(seekSlider);
    vLayout->addLayout(hLayout);
    setLayout(vLayout);
}

void MediaControls::changeSong(Phonon::MediaSource song)
{
    mediaObject->stop();
    mediaObject->setCurrentSource(song);
    mediaObject->play();
    table->selectRow(metaSources.indexOf(song));
}

void MediaControls::songEnded()
{
    emit playNextSong();
}

//New files opened, get the list of songs.
void MediaControls::getQueue(QList<Phonon::MediaSource> meta)
{
    metaSources = meta;
    //Set source so we activate metaDataChanged(), so it loops through our table
    metaResolver->setCurrentSource(metaSources.at(0));
    table->setRowCount(0);
    index = 0;
}

void MediaControls::setMetaData()
{
    QMap<QString, QString> metaData = metaResolver->metaData();

     QString title = metaData.value("TITLE");
     if (title == "")
         title = metaResolver->currentSource().fileName();

     QTableWidgetItem *titleItem = new QTableWidgetItem(title);
     QTableWidgetItem *artistItem = new QTableWidgetItem(metaData.value("ARTIST"));
     QTableWidgetItem *albumItem = new QTableWidgetItem(metaData.value("ALBUM"));
     QTableWidgetItem *yearItem = new QTableWidgetItem(metaData.value("DATE"));

     int row = table->rowCount();
     table->insertRow(row);
     table->setItem(row, 0, titleItem);
     table->setItem(row, 1, artistItem);
     table->setItem(row, 2, albumItem);
     table->setItem(row, 3, yearItem);

     Phonon::MediaSource source = metaResolver->currentSource();
     int index = metaSources.indexOf(source) + 1;
     if (metaSources.count() > index) 
     {
         /* emit a signal so we can loop through the queue and
          * set the table up */
         metaResolver->setCurrentSource(metaSources.at(index));
     }
     else {
         table->resizeColumnsToContents();
         if (table->columnWidth(0) > 300)
             table->setColumnWidth(0, 300);
         //Done setting up table, play first song.
         controller->setSong(0);
     }
}

void MediaControls::setNextSong()
{
    if(index > metaSources.count())
        controller->setSong(++index);
}

void MediaControls::setPrevSong()
{
    if(index != 0)
        controller->setSong(--index);
}

//If clicked, change song to the song in the row that was clicked
void MediaControls::tableClicked(int row)
{
    /* if index == row, we clicked the currently playing song
     * so do nothing */
    if(index != row)
    {
        //set the index so when we press next we know where we are in the queue.
        index = row;
        controller->setSong(index);
    }
}
