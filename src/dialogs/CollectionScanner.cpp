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

#include "CollectionScanner.h"

CollectionScanner::CollectionScanner()
{
    init();
    connect(browseDirButton, SIGNAL(clicked()), this, SLOT(browseDir()));
    connect(buttonBox, SIGNAL(accepted()), this, SLOT(scan()));
    connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));
}

CollectionScanner::~CollectionScanner()
{
    delete dirLabel;
    delete dirInput;
    delete browseDirButton;

    delete buttonBox;
}

void CollectionScanner::init()
{
    setWindowTitle("Scan Collection : KaJammer");
    buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    dirLabel = new QLabel("Scan Directory");
    dirInput = new QLineEdit;
    browseDirButton = new QPushButton(style()->standardIcon(QStyle::SP_DialogOpenButton), "", this);
    
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
    QString startDir = dirInput->text();
    Playlist *p = Playlist::getInstance();
    
    QList<QString> dirs;
    dirs.append(startDir);
    
    while(!dirs.isEmpty())
    {
        QString sdir = dirs.takeFirst();
        sdir += "/";
        QDir dir(sdir);
        
        if( dir.dirName().compare(".") == 0 ||
            dir.dirName().compare("..") == 0 )
        {
            continue;
        }
        
        QFileInfo *file = new QFileInfo(sdir);
        
        if(file->isDir())
        {
            QStringList contents = dir.entryList();
            
            //Queue up new dirs
            for(int i = 0; i < contents.length(); i++)
            {
                QFileInfo *lsfile = new QFileInfo(sdir);
                if(lsfile->isDir()) {
                    dirs.append(sdir + contents.at(i));
                }
            }
            
            QDir playlist (dir);
            QString playlistName = playlist.dirName();

            QStringList music = ls_music(playlist);
            
            if(music.length() > 0)
                p->newPlaylist(playlistName, music);
        }
    }
    
    accept();
}

/* Returns full path, not just file names */
QStringList CollectionScanner::ls_music(QDir dir)
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

void CollectionScanner::closeEvent(QCloseEvent *event)
{
    done(0);
    delete this;
    event->accept();
}
