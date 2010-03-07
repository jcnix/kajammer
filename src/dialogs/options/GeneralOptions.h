/*
 * File:   GeneralOptions.h
 * Author: Casey Jones
 *
 * Created on March 6, 2010, 7:06 PM
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

#ifndef _GENERALOPTIONS_H
#define _GENERALOPTIONS_H

#include <QtCore/QObject>
#include <QtCore/QDir>
#include <QtCore/QString>
#include <QtCore/QStringList>
#include <QtGui/QCheckBox>
#include <QtGui/QFileDialog>
#include <QtGui/QFormLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QStyle>

#include "../../Options.h"

class GeneralOptions : public QWidget
{
    Q_OBJECT;
    
public:
    GeneralOptions();
    ~GeneralOptions();
    
    void save();
    void browseDefaultOpen();
    void init();
    void populate();
    
private:    
    Options *options;
    
    QLineEdit *defaultOpen;
    QPushButton *browseDefaultOpenBtn;
    QCheckBox *shuffBox;
    QCheckBox *trayIconOption;
    QCheckBox *notifyBox;
    
    QHBoxLayout *defaultOpenLayout;
    QFormLayout *formLayout;
};

#endif /* _GENERALOPTIONS_H */
