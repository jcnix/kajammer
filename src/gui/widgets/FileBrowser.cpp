/*
 * File:   FileBrowser.cpp
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

#include "FileBrowser.h"

FileBrowser::FileBrowser()
{
    setColumnCount(1);
    fill("/");
}

void FileBrowser::fill(QString dir)
{
    QDir qdir(dir);
    QStringList ls = qdir.entryList();
    ls.removeOne(".");
    ls.removeOne("..");
    
    for(int i = 0; i < ls.length(); i++)
    {
        QString fullPath = dir + ls.at(i);
        
        QTreeWidgetItem *itm = new QTreeWidgetItem;
        itm->setText(0, ls.at(i));
        
        QFileInfo info(fullPath);
        if(info.isDir())
        {
            itm->setIcon(0, style()->standardIcon( QStyle::SP_DirIcon));
            QTreeWidgetItem *nullItem = new QTreeWidgetItem;
            itm->addChild(nullItem);
        }
        
        addTopLevelItem(itm);
    }
}
