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

#include "headers/playlistEditor.h"
#include <iostream>

PlaylistEditor::PlaylistEditor()
{
    init();
    
    connect(buttonBox, SIGNAL(accepted()), this, SLOT(save()));
    connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));
    connect(open, SIGNAL(clicked()), this, SLOT(openPlaylist()));
    connect(add, SIGNAL(clicked()), this, SLOT(addTracks()));
}

void PlaylistEditor::init()
{
    setWindowTitle("KaJammer Playlist Editor");
    
    playlist = Playlist::getInstance();
    options = Options::getInstance();
    
    listView = new QListWidget;
    
    open = new QPushButton("Open");
    add = new QPushButton("Add");
	btnUp = new QPushButton(style()->standardIcon(QStyle::SP_ArrowUp), "");
	btnDown = new QPushButton(style()->standardIcon(QStyle::SP_ArrowDown), "");
    
    open->setMaximumWidth(75);
    add->setMaximumWidth(75);
    
    buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | 
			QDialogButtonBox::Cancel);
    
    QHBoxLayout *hLayout = new QHBoxLayout;
    hLayout->addWidget(open);
    hLayout->addWidget(add);
	
	QHBoxLayout *updownLayout = new QHBoxLayout;
	updownLayout->addWidget(btnUp);
	updownLayout->addWidget(btnDown);
    
    QVBoxLayout *vLayout = new QVBoxLayout;
    vLayout->addWidget(listView);
    vLayout->addLayout(hLayout);
	vLayout->addLayout(updownLayout);
    vLayout->addWidget(buttonBox);
    setLayout(vLayout);
}

void PlaylistEditor::save()
{
	QStringList text;
	int rows = listView->count();
	for(int i = 0; i < rows; i++) {
		QListWidgetItem *item = listView->item(i);
		text.append(playlistMap.value(item));
	}
	
    playlist->delPlaylist(playlistFile);
    playlist->newPlaylist(playlistFile, text);
	
    accept();
}

void PlaylistEditor::openPlaylist()
{
    QString playlistDir = QDir::homePath() + "/.kajammer/playlists";
    
    playlistFile = QFileDialog::getOpenFileName(this, tr("Open File"), 
                                                playlistDir, "");
                                                
    if(!playlistFile.isEmpty())
    {
        // figure out the playlist's name, we don't need the full path
        QFileInfo file(playlistFile);
        playlistFile = file.fileName();
        QStringList list = playlist->getPlaylistContents(playlistFile);
        
        for(int i = 0; i < list.length(); i++) {
            QFileInfo f(list.at(i));
            QListWidgetItem *item = new QListWidgetItem(f.fileName());
            listView->addItem(item);
			playlistMap.insert(item, list.at(i));
        }
    }
}

void PlaylistEditor::addTracks()
{
    QString defaultDir = options->getDefaultOpenDir();
    
    QStringList list = QFileDialog::getOpenFileNames(this, tr("Open File"), defaultDir, 
										tr("Music Files (*.mp3 *.ogg *.aac *.flac *.wma *.wav)"));
    
    for(int i = 0; i < list.length(); i++) {
        QFileInfo f(list.at(i));
        QListWidgetItem *item = new QListWidgetItem(f.fileName());
        listView->addItem(item);
		playlistMap.insert(item, list.at(i));
    }
}
