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
 * along with Foobar.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <QtGui/QHBoxLayout>

#include "mediacontrols.h"

MediaControls::MediaControls(QWidget *parent) : QWidget(parent)
{
    audioOutput = new Phonon::AudioOutput(Phonon::MusicCategory, this);
    mediaObject = new Phonon::MediaObject(this);
    Phonon::Path path = Phonon::createPath(mediaObject, audioOutput);

    play = new QPushButton("Play", this);
    pause = new QPushButton("Pause", this);

    QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget(play);
    layout->addWidget(pause);
    setLayout(layout);

    connect(play, SIGNAL(clicked()), mediaObject, SLOT(play()));
    connect(pause, SIGNAL(clicked()), mediaObject, SLOT(pause()));
}

void MediaControls::changeSong(QString string)
{
    mediaObject->setCurrentSource(Phonon::MediaSource(string));
    mediaObject->play();
}