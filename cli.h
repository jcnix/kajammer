/*
 * File:   cli.h
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

#ifndef _CLI_H
#define _CLI_H

#include <iostream>
#include <QtCore/QString>
#include <QtCore/QStringList>
#include "controller.h"
#include "playlist.h"

class Cli
{
public:
    Cli(int argc, char *argv[]);
    void cliArgs(char *argv[]);
    
private:
    Controller *controller;
    Playlist *playlist;
    int argc;
    
    void play(QStringList);
    void newPlaylist(QString, QStringList);
    void delPlaylist(QStringList);
    QStringList getArgList(char *argv[], int);
    QStringList appendFilePath(QStringList);
};
#endif /* _CLI_H */
