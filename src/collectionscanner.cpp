/*
 * File:   collectionscanner.cpp
 * Author: Casey Jones
 *
 * Created on September 13, 2009, 4:48 PM
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

#include "headers/collectionscanner.h"

CollectionScanner::CollectionScanner()
{
    init();
    connect(browseDirButton, SIGNAL(clicked()), this, SLOT(browseDir()));
    connect(buttonBox, SIGNAL(accepted()), this, SLOT(scan()));
    connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));
}

void CollectionScanner::init()
{
    setWindowTitle("Scan Collection : KaJammer");
    buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    dirLabel = new QLabel("Scan Directory");
    dirInput = new QLineEdit;
    dirInput->setText("/home/casey/music");
    browseDirButton = new QPushButton("...");
    
    QHBoxLayout *hLayout = new QHBoxLayout;
    hLayout->addWidget(dirLabel);
    hLayout->addWidget(dirInput);
    hLayout->addWidget(browseDirButton);
    
    QVBoxLayout *vLayout = new QVBoxLayout;
    vLayout->addLayout(hLayout);
    vLayout->addWidget(buttonBox);
    setLayout(vLayout);
}

void CollectionScanner::browseDir()
{
    QString dir;
    dir = QFileDialog::getExistingDirectory(NULL,
                                            "Open Directory",
                                            QDir::homePath(),
                                            QFileDialog::ShowDirsOnly);
    dirInput->setText(dir);
}

void CollectionScanner::scan()
{
    QString strDir = dirInput->text() + "/";
    QDir dir (strDir);
    QStringList list = dir.entryList();
    
    for(int i = 0; i < list.length(); i++)
    {
        QFileInfo *file = new QFileInfo(strDir + list.at(i));
        
        if(file->isDir())
        {
            QDir playlist (strDir + list.at(i));
            std::cout << "Path: " << playlist.absolutePath().toStdString() << "\n";
            QString playlistName = playlist.dirName();
            
            if( playlistName.compare(".") == 0 ||
                playlistName.compare("..") == 0 )
            {
                continue;
            }
            
            QStringList music = ls(playlist);
            
            Playlist *p = Playlist::getInstance();
            p->newPlaylist(playlistName, music);
        }
    }
    accept();
}

/* Returns full path, not just file names */
QStringList CollectionScanner::ls(QDir dir)
{
    QStringList filters;
    filters << "*.mp3" << "*.ogg" << "*.flac" << "*.aac";
    filters << "*.wma" << "*.wav";
    
    dir.setNameFilters(filters);
    QStringList files = dir.entryList();
    QStringList filePaths;
    
    QString path = dir.absolutePath() + "/";
    
    for(int i = 0; i < files.length(); i++) {
        QString file = files.at(i);
        if( file.compare(".") == 0 ||
            file.compare("..") == 0 )
        {
            continue;
        }
        
        filePaths.append(path + file);
    }
    
    return filePaths;
}
