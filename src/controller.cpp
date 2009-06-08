/*
 * File:   controller.cpp
 * Author: Casey Jones
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

#include "headers/controller.h"

Controller* Controller::controller = 0;

Controller::Controller()
{
    audioOutput = new Phonon::AudioOutput(Phonon::MusicCategory);
    mediaObject = new Phonon::MediaObject;
    Phonon::Path path = Phonon::createPath(mediaObject, audioOutput);
    
    playlist = Playlist::getInstance();
    options = Options::getInstance();
    currentSong = -1;
    currentList = -1;
    isShuffle = false;
    isRepeat = false;
    repeated = false;
    
    //Track 1 is always played first, so just throw that in played tracks
    playedTracks.append(0);
    
    connect(mediaObject, SIGNAL(finished()), this, SLOT(setNextSong()));
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
    // Clean out the queue so we can start empty
    trackQueue.clear();
    currentSong = -1;

    // _Will_ crash if queue is empty
    if(!queue.isEmpty())
    {
        // Finally add new data to the queue
        for(int i = 0; i < queue.count(); i++)
        {
            Phonon::MediaSource source = queue.at(i);
            
            //turn a 0 into a 1, much more easy and standard way of dealing with the tracks.
            trackQueue[i + 1] = source;
        }
        QList<Phonon::MediaSource> list;
        for(int i = 0; i < trackQueue.count(); i++)
            list.append(trackQueue[i + 1]);
        
        emit queueSet(list);
        setSong(1);
    }
}

// int row is only used to tell MediaControls which row to highlight
void Controller::setSong(int index)
{
    //If user cancels out of open dialog, don't stop playing the current song
    if(!trackQueue.isEmpty() && index >= 0 && index <= trackQueue.count())
    {
        //won't restart the song if you click it twice.
        if(currentSong != index)
        {
            // set currentSong so when we press next we know where we are in the queue.
            // and so we know what currentSong is next time the table is clicked
            currentSong = index;
            Phonon::MediaSource fileName;
            fileName = trackQueue[index];
            changeSong(fileName);
            emit songChanged(currentSong - 1);
        }
    }
}

void Controller::changeSong(Phonon::MediaSource song)
{
    mediaObject->stop();
    mediaObject->setCurrentSource(song);
    mediaObject->play();
}

void Controller::setNextSong()
{
    //std::cout << "Controller::setNextSong();\n";
    //subtract one to prevent a crash when last song on table finishes.
    if(currentSong < trackQueue.count()  || isShuffle || (isRepeat && !repeated))
    {
        bool error = false;
        if(isShuffle) error = shuffle();
        if(isRepeat) repeat();
    
        if(!error) setSong(currentSong + 1);
    }
}

void Controller::setPrevSong()
{
    //std::cout << "Controller::setPrevSong();\n";
    if(currentSong != 1 || isShuffle)
    {
        bool error = false;
        if(isShuffle) error = shuffle();
        if(isRepeat) repeat();
    
        if(!error) setSong(currentSong - 1);
    }
}

//Set isShuffle, if shuffle is enabled disable it and vice versa.
void Controller::toggleShuffle()
{
    if(isShuffle)
        isShuffle = false;
    else if(!isShuffle)
        isShuffle = true;
}

void Controller::toggleRepeat()
{
    if(isRepeat)
        isRepeat = false;
    else if(!isRepeat)
        isRepeat = true;
}

bool Controller::shuffle()
{    
    bool error = false;
    //don't shuffle if current song is not repeated
    if(isRepeat && !repeated) return (error = false);
    
    srand(time(0));
    currentSong = (rand() % trackQueue.count());
    
    if(options->isShuff_no_repeat())
    {
        if(!playedTracks.contains(currentSong))
            playedTracks.append(currentSong);
        //If all the tracks have been played, don't shuffle endlessly
        else if(playedTracks.count() == trackQueue.count()) return (error = true);
        else
        {
            while(playedTracks.contains(currentSong))    
            {
                srand(rand());
                currentSong = (rand() % trackQueue.count());
            }
            playedTracks.append(currentSong);
        }
    }
    return error;
}

void Controller::repeat()
{
    //If the song has not been repeated, do a repeat
    if(!repeated)
    {
        currentSong -= 1;
        repeated = true;
    }
    //if the song has been repeated then reset, so next time it'll come up false;
    else if(repeated)
    {
        repeated = false;
    }
}

void Controller::changePlaylist(QString name, int index)
{
    // Clicking the current List won't restart it
    if(currentList != index)
    {
        currentList = index;
        QStringList list = playlist->getPlaylistContents(name);
        controller->setQueue(list);
    }
}
