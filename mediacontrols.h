/* 
 * File:   mediacontrols.h
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

#ifndef _CONTROLS_H
#define	_CONTROLS_H

#include <QtGui/QWidget>
#include <QtGui/QHBoxLayout>
#include <QtCore/QMap>
#include <QtGui/QPushButton>
#include <QtCore/QStringList>
#include <QtGui/QStyle>
#include <QtGui/QTableWidget>
#include <QtGui/QTableWidgetItem>
#include <QtGui/QVBoxLayout>
#include <phonon/audiooutput.h>
#include <phonon/mediaobject.h>
#include <phonon/seekslider.h>
#include <phonon/volumeslider.h>

#include <controller.h>

class MediaControls : public QWidget
{
    Q_OBJECT;

public:
    MediaControls(QWidget *parent = 0);
    void setupTable();

public slots:
    void changeSong(QString);
    void songEnded();

signals:
    void playNextSong();

private:
    Controller *controller;

    Phonon::AudioOutput *audioOutput;
    Phonon::MediaObject *mediaObject;
    Phonon::VolumeSlider *volumeSlider;
    Phonon::SeekSlider *seekSlider;

    QMap<QString, QString> map;
    QPushButton *play;
    QPushButton *pause;
    QPushButton *next;
    QPushButton *prev;
    QTableWidget *table;
    QTableWidgetItem *titles;
    
    QHBoxLayout *hLayout;
    QVBoxLayout *vLayout;
};

#endif	/* _CONTROLS_H */
