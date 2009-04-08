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
#include <QtCore/QString>
#include <QtCore/QStringList>

#include "mainwindow.h"
#include "cli.h"

int main(int argc, char *argv[]) 
{   
    if(argc == 2 && strcmp(argv[1], "--version") == 0)
    {
        std::cout << "KaJammer Music Player 0.4\n";
        return 0;
    }

    Cli *cli = new Cli(argc, argv);
    bool x = cli->useX();
    
    QApplication app(argc, argv);
    
    if(x)
    {
        app.setApplicationName("KaJammer");
        app.setWindowIcon(QIcon("/usr/share/icons/oxygen/22x22/categories/applications-multimedia.png"));
        app.setQuitOnLastWindowClosed(true);
        
        MainWindow window;
        window.resize(540, 380);
        window.show();
        return app.exec();
    }
    
    app.exit();
}
