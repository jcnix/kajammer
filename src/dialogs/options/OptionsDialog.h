/*
 * File:   OptionsPanel.h
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
#include <QtCore/QString>
#include <QtGui/QCloseEvent>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QVBoxLayout>
#include <QtGui/QTabWidget>

#include "../../headers/config.h"
#include "../../Options.h"
#include "GeneralOptions.h"
#include "LastFmOptions.h"

class OptionsPanel : public QDialog
{
    Q_OBJECT;
    
public:
    OptionsPanel();
    ~OptionsPanel();
    
public slots:
    void save();
    
protected:
    void closeEvent(QCloseEvent *event);    
    
private:
    void init();
    
    Options *options;
    QTabWidget *tabWidget;
    QDialogButtonBox *buttonBox;
    
    GeneralOptions *genOptions;
    #ifdef HAVE_LASTFM_H
    LastFmOptions *lfmOptions;
    #endif
    
    QHBoxLayout *layout;
    QVBoxLayout *vLayout;
};

#endif /* _OPTIONSPANEL_H */
