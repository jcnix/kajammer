/*
 * File:   collectionscanner.h
 * Author: Casey Jones
 *
 * Created on September 13, 2009, 4:48 PM
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

#ifndef _COLLECTIONSCANNER_H
#define _COLLECTIONSCANNER_H

#include <QtGui/QCloseEvent>
#include <QtGui/QDialog>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QFileDialog>
#include <QtGui/QStyle>
#include <QtGui/QVBoxLayout>
#include <QtGui/QHBoxLayout>
#include <QtCore/QDir>

#include "../playlists/Playlist.h"

class CollectionScanner : public QDialog
{
    Q_OBJECT;
    
public:
    CollectionScanner();
    ~CollectionScanner();
    
public slots:
    void browseDir();
    void scan();
    
protected:
    void closeEvent(QCloseEvent *event);
    
private:
    void init();
    QStringList ls_music(QDir);

    QLabel *dirLabel;
    QLineEdit *dirInput;
    QPushButton *browseDirButton;

    QDialogButtonBox *buttonBox;
};

#endif /* COLLECTIONSCANNER_H */