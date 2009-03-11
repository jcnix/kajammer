/*
 * File:   controller.cpp
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

#include "controller.h"

Controller* Controller::controller = 0;

Controller::Controller()
{
}

Controller* Controller::getInstance()
{
    if(controller == 0)
    {
        controller = new Controller;
    }
    return controller;
}


void Controller::setQueue(QStringList queue)
{
    nextQueue = QVector<QString>::fromList(queue);
}

void Controller::nextSong()
{
    //If user cancels out of open dialog, don't stop playing the current song
    if(!nextQueue.isEmpty())
    {
        //Make sure that when you hit next it won't repeat the same song.
        if(fileName == nextQueue.at(0))
        {
            prevQueue.insert(0, fileName);
            nextQueue.remove(0);
        }

        fileName = nextQueue.at(0);

        /* Take song from nextQueue and place in prevQueue, so we can play songs
         * that have already been played. */
        prevQueue.insert(0, fileName);
        nextQueue.remove(0);
        
        emit songChanged(fileName);
    }
}

void Controller::prevSong()
{
    if(!prevQueue.isEmpty())
    {
        fileName = prevQueue.at(0);

        /* Take song from prevQueue and place in nextQueue, so we can play songs
         * that have already been played. */
        nextQueue.insert(0, fileName);
        prevQueue.remove(0);

        emit songChanged(fileName);
    }
}