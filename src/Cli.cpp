/*
 * File:   cli.cpp
 * Author: Casey Jones
 *
 * Created on March 24, 2009, 4:48 PM
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

#ifndef _WINDOWS

#include "Cli.h"

Cli::Cli(int argc, char *argv[])
{
    aFlag = false;
    pFlag = false;
    nFlag = false;
    lFlag = false;
    dFlag = false;
    xFlag = false;
    
    this->argc = argc;
    xFlag = false;
    
    //Process arguments
    cliArgs(argv);
}

void Cli::cliArgs(char *argv[])
{
    int c;
    QStringList args;
    opterr = 0;

    while ((c = getopt(argc, argv, "aplndvx")) != -1)
    {
        switch (c)
        {
            //Play
            case 'p':
                pFlag = true;
                break;
            
            //Play Playlist
            case 'a':
                aFlag = true;
                break;
                
            //List playlists
            case 'l':
                lFlag = true;
                xFlag = true;
                break;
            
            //New Playlist
            case 'n':
                nFlag = true;
                xFlag = true;
                break;
            
            //Delete Playlist
            case 'd':
                dFlag = true;
                xFlag = true;
                break;
            
            //Display version info
            case 'v':
                xFlag = true;
                std::cout << "KaJammer Music Player " << KAJAMMER_VER << "\n";
                exit(1);
                break;
            
            //Don't bring up main window, no Xorg mode.
            case 'x':
                xFlag = true;
                break;
            
            //Command not recognized
            default:
                xFlag = true;
                std::cout << "Usage: kajammer [options...] [arguments...]\n";
                std::cout << "\t" << "Where options include:\n";
                std::cout << "\t" << "-p\t" << "play\t\t" << "[Files]\n";
                std::cout << "\t" << "-a\t" << "play playlist\t" << "Playlist name\n";
                std::cout << "\t" << "-n\t" << "new playlist\t" << "[Name] [Files]\n";
                std::cout << "\t" << "-d\t" << "delete playlist\t" << "[Playlists]\n";
                std::cout << "\t" << "-l\t" << "list playlists\n";
                std::cout << "\t" << "-x\t" << "no X mode\n";
                break;
        }
    }
    
    //If no flags used, assume -p, File Managers do this
    if(!pFlag && !nFlag && !dFlag && !lFlag && !aFlag) {
        args = getArgList(argv, 1);
        play(args);
    }
    
    if(pFlag) {
        args = getArgList(argv, 2);
        play(args);
    }
    
    if(aFlag) {
        QString name = argv[2];
        playPlaylist(name);
    }
    
    if(nFlag) {
        args = appendFilePath(getArgList(argv, 3));
        newPlaylist(argv[2], args);
    }
    
    if(dFlag) {
        args = getArgList(argv, 2);
        delPlaylist(args);
    }
    
    if(lFlag) {
        listPlaylists();
    }
}

/* Take argv[], and create QStringList of args
 * startFrom is the index of argv to put as first in the list */
QStringList Cli::getArgList(char *argv[], int startFrom)
{
    QStringList args;
    for(int i = startFrom; i <= argc; i++)
    {
        args.append(argv[i]);
    }
    return args;
}

QStringList Cli::appendFilePath(QStringList files)
{
    QString path = QDir(".").absolutePath();

    QStringList newList;
    for(int i = 0; i < files.count(); i++)
    {
        if(!files.at(i).isEmpty())
            newList.append(path + "/" + files.at(i));
    }
    return newList;
}

void Cli::play(QStringList songs)
{
    Controller *controller = Controller::getInstance();
    if(!songs.isEmpty())
    {
        //print file names if not using Gui
        for(int i = 0; i < songs.count(); i++)
        {
            std::cout << songs.at(i).toStdString() << "\n";
        }
        controller->setQueue(songs);
    }
    if(xFlag) getchar();
}

void Cli::playPlaylist(QString name)
{
    Controller *controller = Controller::getInstance();
    PlaylistManager *listManager = PlaylistManager::getInstance();
    
    QList<QString> list = listManager->getPlaylistContents(name);
    controller->setQueue(list);
}

void Cli::newPlaylist(QString name, QStringList songs)
{
    PlaylistManager *listManager = PlaylistManager::getInstance();
    listManager->newPlaylist(name, songs);
}

//Delete all playlists given
void Cli::delPlaylist(QStringList names)
{
    PlaylistManager *listManager = PlaylistManager::getInstance();
    QString name;

    for(int i = 0; i < names.count(); i++)
    {
        name = names.at(i);
        listManager->delPlaylist(name);
    }
}

void Cli::listPlaylists()
{
    PlaylistManager *listManager = PlaylistManager::getInstance();
    listManager->listPlaylists();
}

bool Cli::getXFlag()
{
    return xFlag;
}

#endif
