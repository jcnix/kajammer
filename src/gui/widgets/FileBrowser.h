/*
 * File:   FileBrowser.h
 * Author: Casey Jones
 *
 * Created on May 15, 2010, 11:21 PM
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

#ifndef _FILEBROWSER_H
#define _FILEBROWSER_H

#include <QtCore/QDir>
#include <QtCore/QFileInfo>
#include <QtCore/QStack>
#include <QtCore/QString>
#include <QtCore/QStringList>
#include <QtGui/QStyle>
#include <QtGui/QTreeWidget>
#include <QtGui/QTreeWidgetItem>

class FileBrowser : public QTreeWidget
{
    Q_OBJECT
    
public:
    FileBrowser();
    QString buildPath(QTreeWidgetItem *item);
    
public slots:
    void expandItem(QTreeWidgetItem *item);
    
signals:
    void clickedFile(QString file);
    
private:
    void fill(QString dir, QTreeWidgetItem *parent);
};

#endif
