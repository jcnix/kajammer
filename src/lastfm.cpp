/*
 * File:   lastfm.cpp
 * Author: Casey Jones
 *
 * Created on September 26, 2009, 4:27 PM
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

#include "headers/lastfm.h"
#include <iostream>

LastFm::LastFm()
{
    Options *options = Options::getInstance();
    
    std::cout << "Username: " << options->getLastFmUser().toStdString() << "\n";
    std::cout << "Password: " << options->getLastFmPass().toStdString() << "\n";
    
    lastfm::ws::Username = options->getLastFmUser();
    lastfm::ws::ApiKey = "519604ab5a867081cbb9a1edaf75ded4";
    lastfm::ws::SharedSecret = "d5d1806ea34cea02336917b15bff9dec";
    QString password = options->getLastFmPass();
    
    QMap<QString, QString> params;
    params["method"] = "auth.getMobileSession";
    params["username"] = lastfm::ws::Username;
    params["authToken"] = lastfm::md5((lastfm::ws::Username + lastfm::md5(password.toUtf8())).toUtf8());
    reply = lastfm::ws::post(params);
    
    std::cout << "Params: " << params["authToken"].toStdString() << "\n";
    
    connect(reply, SIGNAL(finished()), this, SLOT(parse()));
}

void LastFm::parse()
{
    //TODO: Parse this sucka myself.
    //lastfm::ws::parse() is failing me.
    //after that store the key in kajammer.conf
    //and use lastfm::getSession
    //see demo3.cpp
    
    try
    {
        QString qba = QString(reply->readAll());
        std::cout << "Have? " << qba.toStdString() << "\n";
    }
    catch (lastfm::ws::ParseError& e)
    {
        std::cout << "Error Code: " << e.enumValue() << "\n";
        qWarning() << e.what();
    }
}
