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
 * along with Foobar.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef _CONTROLS_H
#define	_CONTROLS_H

#include <QtGui/QWidget>
#include <QtGui/QPushButton>
#include <phonon/audiooutput.h>
#include <phonon/mediaobject.h>

class MediaControls : public QWidget
{
    Q_OBJECT;

public:
    MediaControls(QWidget *parent = 0);

public slots:
    void changeSong(QString);

private:
    Phonon::AudioOutput *audioOutput;
    Phonon::MediaObject *mediaObject;
    QPushButton *play;
    QPushButton *pause;
};

#endif	/* _CONTROLS_H */