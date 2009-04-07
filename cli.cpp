/*
 * File:   cli.cpp
 * Author: casey
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

#include "cli.h"

Cli::Cli(int argc, char *argv[])
{
    this->argc = argc;
    
    //Process arguments
    cliArgs(argv);
}

void Cli::cliArgs(char *argv[])
{    
    // play songs given as args: -p [Files]
    if(argc > 2 && strcmp(argv[1], "-p") == 0)
    {
        QStringList args = getArgList(argv, 2);
        play(args);
    }
    
    // Create new playlist: -n [Name] [Files]
    else if(argc > 2 && strcmp(argv[1], "-n") == 0)
    {
        QStringList args = getArgList(argv, 3);
        QStringList args2 = appendFilePath(args);
        newPlaylist(argv[2], args2);
    }
    
    // Delete Playlists: -d [Names]
    else if(argc > 2 && strcmp(argv[1], "-d") == 0)
    {
        QStringList args = getArgList(argv, 2);
        delPlaylist(args);
    }
    
    // Unrecognized Option
    else if (argc > 1) //If argc == 1, no arguments
    {
        std::cout << "Usage: kajammer [options...] [arguments...]\n";
        std::cout << "\t" << "where options include:\n";
        std::cout << "\t" << "-p\t" << "play" << "[Files]\n";
        std::cout << "\t" << "-n\t" << "new playlist\t" << "[Name] [Files]\n";
        std::cout << "\t" << "-d\t" << "delete playlist" << "[Files]\n";
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
    controller = Controller::getInstance();
    if(!songs.isEmpty())
    {       
        controller->setQueue(songs);
    }
}

void Cli::newPlaylist(QString name, QStringList songs)
{
    playlist = Playlist::getInstance();
    playlist->newPlaylist(name, songs);
}

//Delete all playlists given
void Cli::delPlaylist(QStringList names)
{
    playlist = Playlist::getInstance();
    QString name;
    
    for(int i = 0; i < names.count(); i++)
    {
        name = names.at(i);
        playlist->delPlaylist(name);
    }
}
