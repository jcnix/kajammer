/*
 * File:   LastFmOptions.h
 * Author: Casey Jones
 *
 * Created on March 6, 2010, 4:00 PM
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

#ifndef _LASTFMOPTIONS_H
#define _LASTFMOPTIONS_H

#include <QtCore/QObject>
#include <QtCore/QString>
#include <QtGui/QCheckBox>
#include <QtGui/QFormLayout>
#include <QtGui/QLineEdit>
#include <QtGui/QWidget>

#include "../../config.h"
#include "../../Options.h"

//#ifdef HAVE_LASTFM_H

class LastFmOptions : public QWidget
{
    Q_OBJECT;
    
public:
    LastFmOptions(QWidget *parent = 0);
    ~LastFmOptions();
    
    void init();
    void populate();
    void save();
        
private:
    Options *options;
    QCheckBox *lastfmBox;
    QLineEdit *lastfmUser;
    QLineEdit *lastfmPass;
    QFormLayout *formLayout;
};

//#endif
#endif /* _LASTFMOPTIONS_H */
