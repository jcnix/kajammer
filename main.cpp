/*
 * File:   main.cpp
 * Author: cjones
 *
 * Created on March 2, 2009, 6:47 PM
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

#include <iostream>
#include <QtGui/QApplication>
#include <QtGui/QIcon>

#include "mainwindow.h"
#include "cli.h"

int main(int argc, char *argv[]) 
{  
    QApplication app(argc, argv);
    app.setApplicationName("KaJammer");
    
    Cli *cli = new Cli(argc, argv);
    bool useXorg = cli->useX();
    
    if(useXorg)
    {
        app.setWindowIcon(QIcon("/usr/share/icons/oxygen/22x22/categories/applications-multimedia.png"));
        app.setQuitOnLastWindowClosed(true);
        
        MainWindow window;
        window.resize(540, 380);
        window.show();
        return app.exec();
    }
    
    app.exit();
}
