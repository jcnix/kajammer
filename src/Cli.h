/*
 * File:   cli.h
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

#ifndef _CLI_H
#define _CLI_H

#ifndef _WINDOWS

#include <iostream>
#include <unistd.h>
#include <QtCore/QString>
#include <QtCore/QStringList>

#include "Controller.h"
#include "playlists/Playlist.h"

class Cli : public QObject
{
    Q_OBJECT;
    
public:
    Cli(int argc, char *argv[]);
    void cliArgs(char *argv[]);
    bool getXFlag();
    
private:   
    int argc;
    bool xFlag;
    bool pFlag;
    bool aFlag;
    bool nFlag;
    bool dFlag;
    bool lFlag;
    
    void play(QStringList);
    void playPlaylist(QString);
    void newPlaylist(QString, QStringList);
    void delPlaylist(QStringList);
    void listPlaylists();
    QStringList getArgList(char *argv[], int);
    QStringList appendFilePath(QStringList);
};

#endif /* Windows */
#endif /* _CLI_H */
