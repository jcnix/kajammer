/*
 * File:   playlistEditor.cpp
 * Author: casey
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
}

void PlaylistEditor::init()
{
    setWindowTitle("KaJammer Playlist Editor");
    
    playlist = Playlist::getInstance();
    textEdit = new QTextEdit;
    textEdit->setMinimumSize(550, 300);
    playlistDocument = new QTextDocument(playlist->getEntirePlaylist("test"));
    textEdit->setDocument(playlistDocument);
    
    buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    
    QVBoxLayout *vLayout = new QVBoxLayout;
    vLayout->addWidget(textEdit);
    vLayout->addWidget(buttonBox);
    setLayout(vLayout);
}

void PlaylistEditor::save()
{}
