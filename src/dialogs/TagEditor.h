/*
 * File:   TagEditor.h
 * Author: Casey Jones
 *
 * Created on April 20, 2010, 8:54 PM
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

#ifndef _TAGEDITOR_H
#define _TAGEDITOR_H

#include "../headers/config.h"
#ifdef HAVE_KAJAMTAG_H
#include <kajamtag/kajamtag.h>
#endif

#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QListWidget>
#include <QtGui/QListWidgetItem>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QTreeWidgetItem>
#include <QtGui/QFormLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QVBoxLayout>

#include "../Controller.h"
#include "../gui/widgets/FileBrowser.h"

class TagEditor : public QDialog
{
    Q_OBJECT

public:
    TagEditor();
    ~TagEditor();
    
private slots:
    void writeData();
    void openTag(QListWidgetItem*);
    void openFile(QTreeWidgetItem*, int);
    
private:
    void init();
    
    FileBrowser *m_fileBrowser;
    QListWidget *m_tagList;
    QLineEdit *m_lineEdit;
    QPushButton *m_acceptBtn;
    QDialogButtonBox *m_buttonBox;
    
    QHBoxLayout *hLayout;
    QFormLayout *m_form;
    QVBoxLayout *m_vlayout;
    
    bool file_open;
    QString m_file;
    #ifdef HAVE_KAJAMTAG_H
    Ktag m_ktag;
    #endif
    QString m_title;
    QString m_album;
    QString m_artist;
};

#endif
