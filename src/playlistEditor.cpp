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
    connect(open, SIGNAL(clicked()), this, SLOT(openPlaylist()));
    connect(add, SIGNAL(clicked()), this, SLOT(addTracks()));
}

void PlaylistEditor::init()
{
    setWindowTitle("KaJammer Playlist Editor");
    
    playlist = Playlist::getInstance();
    textEdit = new QTextEdit;
    textEdit->setMinimumSize(550, 300);
    
    open = new QPushButton("Open");
    add = new QPushButton("Add...");
    
    open->setMaximumWidth(75);
    add->setMaximumWidth(75);
    
    buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    
    QHBoxLayout *hLayout = new QHBoxLayout;
    hLayout->addWidget(open);
    hLayout->addWidget(add);
    
    QVBoxLayout *vLayout = new QVBoxLayout;
    vLayout->addWidget(textEdit);
    vLayout->addLayout(hLayout);
    vLayout->addWidget(buttonBox);
    setLayout(vLayout);
}

void PlaylistEditor::save()
{
    QTextDocument *document = textEdit->document();
    QStringList text;
    
    /* Got lazy.  The string that get put into text will (or should)
     * have linebreaks already if the user hasn't mashed everything into line
     * which I have really no way of fixing.
     * so the playlist will be written as one big string with linebreaks 
     * already inserted */
    text.append(document->toPlainText());
    
    //Delete old Playlist and replace with new
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
        // figure out the file's name, we don't need the full path
        QFileInfo file(playlistFile);
        playlistFile = file.fileName();
        playlistDocument = new QTextDocument(playlist->getEntirePlaylist(playlistFile));
        textEdit->setDocument(playlistDocument);
    }
}

void PlaylistEditor::addTracks()
{
    Options *options = Options::getInstance();
    QString defaultDir = options->getDefaultOpenDir();
    
    QStringList fileQueue = QFileDialog::getOpenFileNames(this, tr("Open File"), defaultDir, 
                                               tr("Music Files (*.mp3 *.ogg *.aac *.flac *.wma *.wav)"));
                                               
    QString currentDocument = textEdit->document()->toPlainText();
    
    QString newTracks;
    for(int i = 0; i < fileQueue.count(); i++)
        newTracks += fileQueue.at(i) + "\n";
    
    playlistDocument = new QTextDocument(currentDocument + newTracks);
    textEdit->setDocument(playlistDocument);
}
