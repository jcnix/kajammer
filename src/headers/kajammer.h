/*
 * File:   kajammer.h
 * Author: Casey Jones
 *
 * Created on November 11, 2009, 10:17 PM
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

//Global defines and stuff

#ifndef _KAJAMMER_H
#define _KAJAMMER_H

#define KAJAMMER_VER "1.0-dev"
#define KAJAMMER_ICON "/usr/share/icons/kajammer.png"

#define KAJAM_DIR QDir::homePath() + "/.kajammer"
#define PLAYLIST_DIR KAJAM_DIR + "/playlists/"
#define KAJAM_QDIR QDir(QDir::homePath() + "/.kajammer/")
#define KAJAM_XML QString(KAJAM_DIR + "/kajammer.xml")

#define MUSIC_TYPES QString("*.mp3 *.ogg *.aac *.flac *.wma *.wav")

#endif //_KAJAMMER_H
