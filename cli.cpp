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
#include <iostream>

Cli::Cli()
{
    controller = Controller::getInstance();
}

void Cli::cliArgs(int argc, char *argv[])
{
    std::cout << argv[0];
    std::cout << argv[1];
    
    // if -p arg, play songs given as args
    if(argc > 2 && strcmp(argv[1], "-p") == 0)
    {
        QStringList args;
        for(int i = 2; i <= argc - 2; i++)
        {
            args.append(argv[i]);
        }
        play(args);
    }
}

void Cli::play(QStringList songs)
{
    if(!songs.isEmpty())
    {       
        controller->setQueue(songs);
    }
}