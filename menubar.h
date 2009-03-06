/* 
 * File:   menubar.h
 * Author: casey
 *
 * Created on March 4, 2009, 4:35 PM
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

#ifndef _MENUBAR_H
#define	_MENUBAR_H

#include <QtGui/QAction>
#include <QtGui/QFileDialog>
#include <QtGui/QMenuBar>
#include <QtGui/QMenu>
#include <QtCore/QString>

class MenuBar : public QMenuBar
{
    Q_OBJECT;

public:
    MenuBar();

private slots:
    void open();
    void quit();

signals:
    void songChanged(QString);

private:
    QAction *openFile;
    QAction *close;
    QAction *about;
    QMenuBar *menuBar;
    QMenu *file;
    QMenu *help;
    QString fileName;
};

#endif	/* _MENUBAR_H */