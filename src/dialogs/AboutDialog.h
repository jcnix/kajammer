/*
 * File:   AboutDialog.h
 * Author: Casey Jones
 *
 * Created on November 13, 2009, 11:44 PM
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

#ifndef _ABOUTDIALOG_H
#define _ABOUTDIALOG_H

#include <sstream>
#include <QtGui/QCloseEvent>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QLabel>
#include <QtGui/QPixmap>
#include <QtGui/QVBoxLayout>

#include "../headers/kajammer.h"
#include "../headers/config.h"

#ifdef HAVE_KAJAMTAG_H
#include <kajamtag/kajamtag.h>
#endif

class AboutDialog : public QDialog
{
    Q_OBJECT;
    
public:
    AboutDialog();
    ~AboutDialog();
    
protected:
    void closeEvent(QCloseEvent *event);
    
private:
    void init();
    
    QLabel *iconLabel;
    QLabel *aboutLabel;
    QLabel *authorsLabel;
    
    QDialogButtonBox *buttonBox;
    
    QHBoxLayout *topLayout;
    QVBoxLayout *layout;
};

#endif //_ABOUTDIALOG_H
