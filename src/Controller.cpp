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

#include "Controller.h"

#ifdef HAVE_KAJAMTAG_H
#include <kajamtag/kajamtag.h>
#endif

Controller* Controller::controller = 0;

Controller::Controller()
{
    audioOutput = new Phonon::AudioOutput(Phonon::MusicCategory);
    mediaObject = new Phonon::MediaObject;
    Phonon::createPath(mediaObject, audioOutput);
    
    metaResolver = new Phonon::MediaObject;  //Used for finding metadata
    
    listManager = PlaylistManager::getInstance();
    options = Options::getInstance();
    
    currentSong = 0;
    currentList = -1;
    isShuffle = false;
    isRepeat = false;
    repeated = false;
    
    srand(time(0));
    
    //Track 1 is always played first, so just throw that in played tracks
    playedTracks.append(0);
    
    connect(mediaObject, SIGNAL(finished()), this, SLOT(setNextSong()));
    connect(mediaObject, SIGNAL(finished()), this, SLOT(emitSongFinished()));
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
    playedTracks.clear();
    currentSong = 0;

    // _Will_ crash if queue is empty
    if(!queue.isEmpty())
    {
        // Finally add new data to the queue
        for(int i = 0; i < queue.count(); i++)
        {
            //Make sure the track exists before adding it
            if(!QFile::exists(queue.at(i))) {
                continue;
            }
            
            Phonon::MediaSource source = queue.at(i);
            
            //turn a 0 into a 1, much more easy and standard way of dealing
            //with the tracks.
            trackQueue[i + 1] = source;
        }
        emitList();
    }
}

/* Mainly used if MediaControls missed the queueSet Signal
 * Only happens if user uses -p flag on command line */
void Controller::emitList()
{
    QList<Phonon::MediaSource> list;
    for(int i = 0; i < trackQueue.count(); i++)
    {
        list.append(trackQueue[i + 1]);
    }
    
    //Set source so we activate metaDataChanged(), so it loops through our table
    if(!list.isEmpty())
    {
        metaResolver->setCurrentSource(list.at(0));
    }
    metaSources = list;
    
    emit queueSet(list);
}

QMap<QString, QString> Controller::getCurrentMetadata()
{
    return getMetadata(trackQueue[currentSong].fileName());
}

QMap<QString, QString> Controller::getMetadata(QString file)
{
    QMap<QString, QString> metaData;
    
    QString title;
    QString artist;
    QString album;
    
    #ifdef HAVE_KAJAMTAG_H
    char* cfile = new char[file.size()+1];
    strcpy(cfile, file.toStdString().c_str());
    
    kajamtag_read(cfile);
        
    if(!kajamtag_isUtf16())
    {
        char* c_title =   k_getData(KTITLE);
        char* c_artist =  k_getData(KARTIST);
        char* c_album =   k_getData(KALBUM);
        
        title = QString(c_title);
        artist = QString(c_artist);
        album = QString(c_album);
    }
    else
    {
        wchar_t* c_title = k_getData16(KTITLE);
        wchar_t* c_artist = k_getData16(KARTIST);
        wchar_t* c_album = k_getData16(KALBUM);
        
        title = QString::fromWCharArray(c_title, 2);
        artist = QString::fromWCharArray(c_artist, 2);
        album = QString::fromWCharArray(c_album, 2);
    }
    
    //"BAD_TAG" means Kajamtag doesn't 
    //recognize the tag format.
    //If one is bad, they're all bad.
    if(title.compare("BAD_TAG") == 0) {
        title = "";
        artist = "";
        album = "";
    }
    else
    {
        //free(c_title);
        //free(c_artist);
        //free(c_album);
    }
    free(cfile);
    #endif
    
    #ifndef HAVE_KAJAMTAG_H
    metaData = metaResolver->metaData();
    title = metaData.value("TITLE");
    artist = metaData.value("ARTIST");
    album = metaData.value("ALBUM");
    #endif
    
    if (title.compare("") == 0)
    {
        #ifdef HAVE_KAJAMTAG_H
        QFileInfo fileInfo(file);
        #else
        QFileInfo fileInfo(metaResolver->currentSource().fileName());
        #endif
        title = fileInfo.baseName();
    }
    
    metaData.insert("TITLE", title);
    metaData.insert("ARTIST", artist);
    metaData.insert("ALBUM", album);
    
    #ifndef HAVE_KAJAMTAG_H
    Phonon::MediaSource source = metaResolver->currentSource();
    int index = metaSources.indexOf(source) + 1;
    if (metaSources.count() > index) 
    {            
        /* emit a signal so we can loop through the queue and
        * set the table up */
        metaResolver->setCurrentSource(metaSources.at(index));
    }
    #endif
    
    return metaData;
}

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
            
            //Tell MediaControls which row to highlight
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

void Controller::play()
{
    mediaObject->play();
}

void Controller::pause()
{
    mediaObject->pause();
}

void Controller::setNextSong()
{
    //std::cout << "Controller::setNextSong();\n";
    //subtract one to prevent a crash when last song on table finishes.
    if(currentSong < trackQueue.count()  || isShuffle || (isRepeat && !repeated))
    {
        bool error = false;
        if(isShuffle)
            error = shuffle();
        if(isRepeat)
            repeat();
    
        if(!error)
            setSong(currentSong + 1);
    }
}

void Controller::setPrevSong()
{
    //std::cout << "Controller::setPrevSong();\n";
    if(currentSong != 1 || isShuffle)
    {
        bool error = false;
        if(isShuffle)
            error = shuffle();
        if(isRepeat)
            repeat();
    
        if(!error)
            setSong(currentSong - 1);
    }
}

void Controller::emitSongFinished()
{
    emit songFinished();
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
    /* don't shuffle if current song is not repeated
     * return false so setNextSong/setPrevSong will work,
     * and the song can repeat */
    if(isRepeat && !repeated)
        return (error = false);

    currentSong = (rand() % trackQueue.count());
    
    if(options->isShuff_no_repeat())
    {
        if(playedTracks.count() == trackQueue.count()) return (error = true);
        else
        {
            while(playedTracks.contains(currentSong))    
            {
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

void Controller::resetCurrentList()
{
    currentList = -1;
}

Phonon::AudioOutput* Controller::getAudioOutput()
{
    return audioOutput;
}

Phonon::MediaObject* Controller::getMediaObject()
{
    return mediaObject;
}

Phonon::MediaObject* Controller::getMetaResolver()
{
    return metaResolver;
}

bool Controller::isPlaying()
{
    return (mediaObject->state() == Phonon::PlayingState);
}

bool Controller::isPaused()
{
    return (mediaObject->state() == Phonon::PausedState);
}

void Controller::changePlaylist(QString name, int index)
{
    // Clicking the current List won't restart it
    if(currentList != index)
    {
        currentList = index;
        QStringList list = listManager->getPlaylistContents(name);
        controller->setQueue(list);
    }
}
