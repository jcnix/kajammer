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
#ifdef HAVE_LASTFM_H

LastFm::LastFm()
{
    //HACK work around a bug in liblastfm; it doesn't create its config dir, so when it
    // tries to write the track cache, it fails silently.
    QString lpath = QDir::home().filePath( ".local/share/Last.fm" );
    QDir ldir = QDir( lpath );
    if( !ldir.exists() )
    {
        ldir.mkpath( lpath );
    }
    
    controller = Controller::getInstance();
    options = Options::getInstance();
    
    QCoreApplication::setApplicationName("kjm");
    QCoreApplication::setApplicationVersion("1.0");
    
    init();
}

void LastFm::init()
{
    const QString password = options->getLastFmPass();
    const QString sessionKey = options->getLastFmKey();
    const QString userName = options->getLastFmUser();
    lastfm::ws::ApiKey = "519604ab5a867081cbb9a1edaf75ded4";
    lastfm::ws::SharedSecret = "d5d1806ea34cea02336917b15bff9dec";
    lastfm::ws::Username = userName;

    QString authToken = lastfm::md5((userName + lastfm::md5(password.toUtf8())).toUtf8());

    //we don't have a session key; get one
    if(sessionKey.isEmpty())
    {
        std::cout << "No saved session key, authenticating with last.fm\n";
        QMap<QString, QString> query;
        query[ "method" ] = "auth.getMobileSession";
        query[ "username" ] = userName;
        query[ "authToken" ] = authToken;
        reply = lastfm::ws::post( query );

        connect(reply, SIGNAL(finished()), SLOT(parseReply()));
    } 
    else
    {
        std::cout << "Using saved SessionKey\n";
        lastfm::ws::SessionKey = sessionKey.toLatin1().data();

        as = new lastfm::Audioscrobbler("kjm");
        QMap< QString, QString > params;
        params["method"] = "user.getInfo";
    }
}

void LastFm::nowPlaying()
{
    std::cout << "Now Playing\n";
    try
    {
        QMap<QString, QString> data = controller->getCurrentMetadata();
        
        lastfm::MutableTrack t;
        t.stamp(); //sets track start time
        t.setTitle(data["TITLE"]);
        t.setArtist(data["ARTIST"]);
        t.setAlbum(data["ALBUM"]);
        
        qint64 time = controller->getMediaObject()->remainingTime() / 1000;
        t.setDuration(time);
        
        t.setSource(lastfm::Track::Player);
        
        as->nowPlaying(t);
        //Audioscrobbler will submit whatever is in the cache when you call submit.
        //And the cache is persistent between sessions. So you should cache at the
        //scrobble point usually, not before
        as->cache(t);
    }
    catch (lastfm::ws::ParseError& e)
    {
        std::cout << "Error Code: " << e.enumValue() << "\n";
        qWarning() << e.what();
    }
}

void LastFm::scrobble()
{
    std::cout << "Srobble\n";
    try
    {
        as->submit();
    }
    catch (lastfm::ws::ParseError& e)
    {
        std::cout << "Error Code: " << e.enumValue() << "\n";
        qWarning() << e.what();
    }
}

void LastFm::parseReply()
{
    if( !reply )
    {
        std::cout << "WARNING: GOT RESULT but no object";
        return;
    }

    switch ( reply->error() )
    {
        case QNetworkReply::NoError:
        {
            lastfm::XmlQuery lfm = lastfm::XmlQuery(reply->readAll());

            if( lfm.children("error").size() > 0 )
            {
                std::cout << "error from authenticating with last.fm service:"
                        << lfm.text().toStdString();
                options->setLastFmKey("");
                options->save();
                break;
            }
            sessionKey = lfm["session"]["key"].text();

            lastfm::ws::SessionKey = sessionKey.toLatin1().data();
            options->setLastFmKey(sessionKey);
            options->save();

            break;
        } 
        case QNetworkReply::AuthenticationRequiredError:
            std::cout << "Last.fm: errorMessage Either the username was not recognized, "
                    << "or the password was incorrect.";
            break;

        default:
            std::cout << "Last.fm: errorMessage There was a problem communicating with "
                    << "the Last.fm services. Please try again later.";
            break;
    }
    reply->deleteLater();
}

#endif //HAVE_LASTFM_H
