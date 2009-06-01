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

#include <QtCore/QObject>
#include <QtCore/QDir>
#include <QtCore/QFile>
#include <QtCore/QIODevice>
#include <QtCore/QString>
#include <QtCore/QStringList>
#include <QtCore/QTextStream>

class Options
{
public:
    static Options* getInstance();
    void save();
    
    void setDefaultOpenDir(QString dir) { defaultOpenDir = dir; }
    void setShuff_no_repeat(bool no_repeat) { shuff_no_repeat = no_repeat; }
    
    QString getDefaultOpenDir();
    bool isShuff_no_repeat() { return shuff_no_repeat; }
    
protected:
    Options();
    
private:
    static Options *options;
    
    void readOptions();
    QString bool_to_qstring(bool);
    
    QString confPath;
    QString defaultOpenDir;
    bool shuff_no_repeat;
};

#endif /* _OPTIONS_H */