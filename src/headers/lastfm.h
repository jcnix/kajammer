/*
 * File:   lastfm.h
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

#ifndef _LASTFM_H
#define _LASTFM_H

#include <lastfm.h>
#include <QtCore/QEventLoop>

#include "options.h"

class LastFm :QObject
{
    Q_OBJECT;
    
public:
    LastFm();

private slots:
    void parse();
    
private:
    QNetworkReply* reply;
};

#endif //_LASTFM_H
