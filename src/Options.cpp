/*
 * File:   options.cpp
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

#include "Options.h"

static QString bool_to_qstring(bool);
static bool qstring_to_bool(QString);
static QString encrypt(QString);
static void createXmlIfNeeded();

const char* OptionKeys_str[] = {
    "DefaultDir",
    "LastFmUser",
    "LastFmPass",
    "LastFmKey"
};

const char* OptionKeys_bool[] = {
    "ShuffNoRepeat",
    "ShowPlaylists",
    "UseTrayIcon",
    "NotifyOnTrackChange",
    "UseLastFm"
};

const char* OptionKeys_int[] = {
    "NotificationTime",
    "MainWidth",
    "MainHeight"
};

QString Options::getOption(QString key)
{
    createXmlIfNeeded();
    
    QDomDocument doc;
    QFile file(KAJAM_XML);
    if(!file.open(QIODevice::ReadOnly))
        return "";
    
    doc.setContent(&file);
    QDomElement root = doc.documentElement();
    QDomNode n = root.firstChild();
    QString text = "";
    while(!n.isNull())
    {
        QDomElement e = n.toElement();
        if(!e.isNull())
        {
            if(e.tagName() == key) {
                text = e.text();
                break;
            }
        }
        
        n = n.nextSibling();
    }
    
    file.close();
    return text;
}

QString Options::getOption_String(KJ::OptionKeys_String o)
{
    QString key = OptionKeys_str[o];
    return getOption(key);
}

bool Options::getOption_Bool(KJ::OptionKeys_Bool o)
{
    QString key = OptionKeys_bool[o];
    return qstring_to_bool(getOption(key));
}

int Options::getOption_Int(KJ::OptionKeys_Int o)
{
    QString key = OptionKeys_int[o];
    return getOption(key).toInt();
}

void Options::setOption(QString key, QString value)
{
    createXmlIfNeeded();
    //Fill this in...
}

void Options::setOption(KJ::OptionKeys_String o, QString value)
{
    setOption(OptionKeys_str[o], value);
}

void Options::setOption(KJ::OptionKeys_Bool o, bool b)
{
    setOption(OptionKeys_bool[o], bool_to_qstring(b));
}

void Options::setOption(KJ::OptionKeys_Int o, int i)
{
    setOption(OptionKeys_int[o], QString::number(i));
}

void createXmlIfNeeded()
{
    if(!KAJAM_QDIR.exists())
    {
        KAJAM_QDIR.mkdir(KAJAM_DIR);
        KAJAM_QDIR.mkdir(PLAYLIST_DIR);
    }
}

QString bool_to_qstring(bool truthiness)
{
    QString truth = "0";
    if(truthiness)
        truth = "1";
    return truth;
}

bool qstring_to_bool(QString truthiness) {
    if(truthiness == "1")
        return true;
    else
        return false;
}

QString encrypt(QString stringToEncrypt)
{    
    const char* cstring = stringToEncrypt.toStdString().c_str();
    int length = strlen(cstring);
    
    char alphabet[26] = "ABCDEFGHIJKLMOPQRSTUVWXYZ";
    
    char crypto[length + 1];
    int key_index = 0;
    for(int i = 0; i < length; i++)
    {
        key_index++;
        if(key_index == 26)
            key_index = 0;
        
        crypto[i] = cstring[i]^alphabet[key_index];
    }
    crypto[length] = '\0';
    
    return QString(crypto);
}
