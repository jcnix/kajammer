/*
 * File:   optionsPanel.h
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

#ifndef _OPTIONSPANEL_H
#define _OPTIONSPANEL_H

#include <iostream>
#include <QtCore/QObject>
#include <QtCore/QDir>
#include <QtGui/QLabel>
#include <QtCore/QString>
#include <QtCore/QStringList>
#include <QtCore/QTextStream>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QFileDialog>
#include <QtGui/QLineEdit>
#include <QtGui/QHBoxLayout>
#include <QtGui/QPushButton>
#include <QtGui/QVBoxLayout>

#include "options.h"

class OptionsPanel : public QDialog
{
    Q_OBJECT;
    
public:
    OptionsPanel();
    
public slots:
    void save();
    void browseDefaultOpen();
    
private:
    void init();
    void populate();
    QString setDefaultOpen();
    
    Options *options;
    QString confPath;
    
    QDialogButtonBox *buttonBox;
    QLabel *defaultOpenLabel;
    QLineEdit *defaultOpen;
    QPushButton *browseDefaultOpenBtn;
};

#endif /* _OPTIONSPANEL_H */
