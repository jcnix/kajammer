/*
 * File:   options.h
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

#ifndef _OPTIONS_H
#define _OPTIONS_H

#include <QtCore/QDir>
#include <QtCore/QFile>
#include <QtCore/QString>
#include <QtXml/QDomDocument>
#include <QtXml/QDomNode>
#include <QtXml/QDomElement>
#include <iostream>

#include "headers/config.h"
#include "headers/kajammer.h"

namespace KJ
{
    enum OptionKeys_String
    {
        DEFAULT_OPEN_DIR,
        LASTFM_USER,
        LASTFM_PASS,
        LASTFM_KEY
    };

    enum OptionKeys_Bool
    {
        SHUFF_NO_REPEAT,
        SHOW_PLAYLISTS,
        USE_TRAY_ICON,
        NOTIFY_ON_TRACK_CHANGE,
        USE_LASTFM
    };

    enum OptionKeys_Int
    {
        NOTIFICATION_TIME,
        MAIN_WIDTH,
        MAIN_HEIGHT
    };
};

class Options
{
public:
    static QString getOption_String(KJ::OptionKeys_String o);
    static bool getOption_Bool(KJ::OptionKeys_Bool o);
    static int getOption_Int(KJ::OptionKeys_Int o);
    static void setOption(KJ::OptionKeys_String o, QString s);
    static void setOption(KJ::OptionKeys_Bool o, bool b);
    static void setOption(KJ::OptionKeys_Int o, int i);
    
private:
    Options();
    static QString getOption(QString key);
    static void setOption(QString key, QString value);
};

#endif /* _OPTIONS_H */
