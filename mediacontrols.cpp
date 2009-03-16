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

#include "mediacontrols.h"
#include <iostream>

MediaControls::MediaControls(QWidget *parent) : QWidget(parent)
{
    controller = Controller::getInstance();

    audioOutput = new Phonon::AudioOutput(Phonon::MusicCategory);
    mediaObject = new Phonon::MediaObject;
    Phonon::Path path = Phonon::createPath(mediaObject, audioOutput);

    volumeSlider = new Phonon::VolumeSlider;
    volumeSlider->setAudioOutput(audioOutput);

    seekSlider = new Phonon::SeekSlider;
    seekSlider->setTracking(false);
    seekSlider->setMediaObject(mediaObject);

    //Media Control buttons
    play = new QPushButton(style()->standardIcon(QStyle::SP_MediaPlay), "", this);
    pause = new QPushButton(style()->standardIcon(QStyle::SP_MediaPause), "", this);
    next = new QPushButton(style()->standardIcon(QStyle::SP_MediaSkipForward), "", this);
    prev = new QPushButton(style()->standardIcon(QStyle::SP_MediaSkipBackward), "", this);

    //Table with meta info
    table = new QTableWidget(1, 1);
    QStringList tableHeaders;
    tableHeaders.append("Title");
    table->setHorizontalHeaderLabels(tableHeaders);

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

    connect(play, SIGNAL(clicked()), mediaObject, SLOT(play()));
    connect(pause, SIGNAL(clicked()), mediaObject, SLOT(pause()));
    connect(next, SIGNAL(clicked()), controller, SLOT(nextSong()));
    connect(prev, SIGNAL(clicked()), controller, SLOT(prevSong()));
    connect(mediaObject, SIGNAL(finished()), this, SLOT(songEnded()));
    connect(mediaObject, SIGNAL(metaDataChanged()), this, SLOT(setMetaData()));
}

void MediaControls::changeSong(QString song)
{
    mediaObject->setCurrentSource(Phonon::MediaSource(song));
    mediaObject->play();
}

void MediaControls::songEnded()
{
    emit playNextSong();
}

void MediaControls::setMetaData()
{
    QStringList currentTitles = mediaObject->metaData(Phonon::TitleMetaData);
    QString currentTitle = currentTitles.first();
    
    titles = new QTableWidgetItem(QTableWidgetItem::Type);
    titles->setText(currentTitle);
    table->setItem(0, 0, titles);
}
