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

#include "headers/options.h"

Options* Options::options = 0;

Options::Options()
{       
    //if height and width aren't found, these are defaults
    main_width = 640;
    main_height = 360;
    
    if(!QKAJAM_DIR.exists())
    {
        QKAJAM_DIR.mkdir(KAJAM_DIR);
        QKAJAM_DIR.mkdir(PLAYLIST_DIR);
    }
    
    readOptions();
}

Options* Options::getInstance()
{
    if(options == 0)
    {
        options = new Options;
    }
    return options;
}

void Options::readOptions()
{    
    QFile conf(KAJAM_CONF);
    conf.open(QIODevice::ReadOnly);
    
    QStringList options;
    QTextStream in(&conf);
    
    //Read conf file and store in list
    while(!in.atEnd())
        options.append(in.readLine(0));
    
    //Parse conf file and set options
    for(int i = 0; i < options.count(); i++)
    {
        QString option = options.at(i);
        QStringList list = option.split("=");
        
        if(list.at(0).contains("$MusicDir"))
        {
            defaultOpenDir = list.at(1);
        }
        else if(list.at(0).contains("$Shuff_No_Repeat"))
        {
            if(list.at(1).contains("1"))
                shuff_no_repeat = true;
            else
                shuff_no_repeat = false;
        }
        else if(list.at(0).contains("$Use_Tray_Icon"))
        {
            if(list.at(1).contains("1"))
                use_tray_icon = true;
            else
                use_tray_icon = false;
        }
        else if(list.at(0).contains("$Main_Width")) {
            main_width = list.at(1).toInt();
            if(main_width < 200)
                main_width = 640;
        }
        else if(list.at(0).contains("$Main_Height")) {
            main_height = list.at(1).toInt();
            if(main_height < 100)
                main_height = 360;
        }
        else if(list.at(0).contains("$LastFM_User")) {
            lastfmUser = list.at(1);
        }
        else if(list.at(0).contains("$LastFM_Pass")) {
            lastfmPass = list.at(1);
        }
    }
    
    conf.close();
}

void Options::save()
{
    QFile conf(KAJAM_CONF);
    conf.open(QIODevice::WriteOnly);
    
    QStringList options;
    QTextStream out(&conf);
    
    options.append("$MusicDir=" + defaultOpenDir + "\n");
    options.append("$Shuff_No_Repeat=" + bool_to_qstring(shuff_no_repeat) + "\n");
    options.append("$Use_Tray_Icon=" + bool_to_qstring(use_tray_icon) + "\n");
    options.append("$Main_Width=" + QString::number(main_width) + "\n");
    options.append("$Main_Height=" + QString::number(main_height) + "\n");
    options.append("$LastFM_User=" + lastfmUser + "\n");
    options.append("$LastFM_Pass=" + lastfmPass + "\n");

    //Write to file
    for(int i = 0; i < options.count(); i++)
        out << options.at(i);
    
    conf.close();
}

QString Options::bool_to_qstring(bool truthiness)
{
    QString truth = "0";
    if(truthiness)
        truth = "1";
    return truth;
}

QString Options::getDefaultOpenDir()
{
    if(defaultOpenDir.isEmpty() || defaultOpenDir == NULL)
        defaultOpenDir = QDir::homePath();
    return defaultOpenDir;
}
