/* 
 * File:   mediacontrols.h
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

#ifndef _CONTROLS_H
#define _CONTROLS_H

#include <QtGui/QWidget>
#include <QtGui/QAbstractItemView>
#include <QtCore/QFileInfo>
#include <QtGui/QHBoxLayout>
#include <QtGui/QKeySequence>
#include <QtCore/QList>
#include <QtGui/QLineEdit>
#include <QtCore/QMap>
#include <QtGui/QPushButton>
#include <QtCore/QString>
#include <QtCore/QStringList>
#include <QtGui/QStyle>
#include <QtGui/QTableWidget>
#include <QtGui/QTableWidgetItem>
#include <QtGui/QVBoxLayout>
#include <phonon/mediasource.h>
#include <phonon/seekslider.h>
#include <phonon/volumeslider.h>
#include <iostream>

#include "../headers/config.h"
#include "../Controller.h"
#include "../Options.h"
#include "../playlists/PlaylistManager.h"
#include "../gui/widgets/ToggleButton.h"
#include "../sql/CollectionManager.h"

#define PLAYLIST_WIDTH 180

class MediaControls : public QWidget
{
    Q_OBJECT;

public:
    MediaControls(QWidget *parent = 0);

public slots:
    void songChanged(int);
    void setMetaData();
    void getQueue(QList<Phonon::MediaSource>);
    void setupPlaylists();
    void tableClicked(int);
    void playPressed();
    void changePlaylist(int);
    void shufflePressed();
    void repeatPressed();
    void search();
    void searchDone(QStringList result);
    void showPlaylists(bool);

private:
    void init();

    Controller *controller;
    Options *options;
    PlaylistManager *listManager;
    CollectionManager *cm;
    
    Phonon::VolumeSlider *volumeSlider;
    Phonon::SeekSlider *seekSlider;

    QPushButton *play;
    QPushButton *next;
    QPushButton *prev;
    ToggleButton *shuffleBtn;
    ToggleButton *repeatBtn;
    QLineEdit *searchBar;
    QTableWidget *table;
    QTableWidget *playlistTable;
    QMap<QString, QString> metaMap;
    QList<Phonon::MediaSource> metaSources;
    QList<int> trackOrder;
    QStringList tableLabels;
    
    int tableIndex;
};

#endif /* _CONTROLS_H */
