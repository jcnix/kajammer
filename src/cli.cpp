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
    useXorg = true;

    //Process arguments
    cliArgs(argv);
}

void Cli::cliArgs(char *argv[])
{
    int c;
    QStringList args;
    QStringList args2;

    opterr = 0;

    while ((c = getopt(argc, argv, "plndvx")) != -1)
    {
        switch (c)
        {
            //Play
            case 'p':
                args = getArgList(argv, 2);
                play(args);
                break;
            //Play Playlist
            //New Playlist
            case 'n':
                useXorg = false;
                args = getArgList(argv, 3);
                args2 = appendFilePath(args);
                newPlaylist(argv[2], args2);
                break;
            //Delete Playlist
            case 'd':
                useXorg = false;
                args = getArgList(argv, 2);
                delPlaylist(args);
                break;
            //Display version info
            case 'v':
                useXorg = false;
                std::cout << "KaJammer Music Player 0.4.5\n";
                break;
            //Don't bring up main window, no Xorg mode.
            case 'x':
                useXorg = false;
                break;
            //Command not recognized
            default:
                useXorg = false;
                std::cout << "Usage: kajammer [options...] [arguments...]\n";
                std::cout << "\t" << "Where options include:\n";
                std::cout << "\t" << "-p\t" << "play" << "[Files]\n";
                std::cout << "\t" << "-n\t" << "new playlist\t" << "[Name] [Files]\n";
                std::cout << "\t" << "-d\t" << "delete playlist\t" << "[Playlists]\n";
                break;
        }
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
        for(int i = 0; i < songs.count() - 1; i++)
        {
            std::cout << songs.at(i).toStdString() << "\n";
        }
        controller->setQueue(songs);
    }
    getchar();
}

void Cli::newPlaylist(QString name, QStringList songs)
{
    Playlist *playlist = Playlist::getInstance();
    playlist->newPlaylist(name, songs);
}

//Delete all playlists given
void Cli::delPlaylist(QStringList names)
{
    Playlist *playlist = Playlist::getInstance();
    QString name;

    for(int i = 0; i < names.count(); i++)
    {
        name = names.at(i);
        playlist->delPlaylist(name);
    }
}

bool Cli::useX()
{
    return useXorg;
}
