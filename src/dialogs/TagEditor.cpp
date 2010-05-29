/*
 * File:   TagEditor.cpp
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

#ifdef HAVE_KAJAMTAG_H
#include <kajamtag/kajamtag.h>
#endif
#include "TagEditor.h"

TagEditor::TagEditor()
{
    init();
    
    connect(m_acceptBtn, SIGNAL(clicked()), this, SLOT(writeData()));
    connect(m_buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    connect(m_tagList, SIGNAL(itemClicked(QListWidgetItem*)),
            this, SLOT(openTag(QListWidgetItem*)));
    connect(m_fileBrowser, SIGNAL(itemDoubleClicked(QTreeWidgetItem*, int)),
            this, SLOT(openFile(QTreeWidgetItem*, int)));
}

TagEditor::~TagEditor()
{
    delete m_acceptBtn;
    delete m_buttonBox;
    delete m_form;
    delete m_vlayout;
}

void TagEditor::init()
{
    file_open = false;
    
    m_fileBrowser = new FileBrowser;
    m_tagList = new QListWidget;
    m_tagList->addItem("Title");
    m_tagList->addItem("Album");
    m_tagList->addItem("Artist");
    
    m_lineEdit = new QLineEdit;
    
    hLayout = new QHBoxLayout;
    hLayout->addWidget(m_fileBrowser);
    hLayout->addWidget(m_tagList);
    
    m_acceptBtn = new QPushButton("Accept");
    m_acceptBtn->setFixedWidth(80);
    m_buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok);
            
    m_form = new QFormLayout;
    m_form->addRow("Value", m_lineEdit);
    
    m_vlayout = new QVBoxLayout;
    m_vlayout->addLayout(hLayout);
    m_vlayout->addLayout(m_form);
    m_vlayout->addWidget(m_acceptBtn);
    m_vlayout->addWidget(m_buttonBox);
    
    setLayout(m_vlayout);
}

void TagEditor::writeData()
{
    QString data = m_lineEdit->text();
}

void TagEditor::openTag(QListWidgetItem* item)
{
    if(!file_open)
        return;
    
    QString text = item->text();
    QString data = "";
    
    if(text == "Title")
        data = m_title;
    else if(text == "Album")
        data = m_album;
    else if(text == "Artist")
        data = m_artist;
    
    m_lineEdit->setText(data);
}

void TagEditor::openFile(QTreeWidgetItem* item, int column)
{
    file_open = true;
    
    QString path = m_fileBrowser->buildPath(item);
    Controller *controller = Controller::getInstance();
    QMap<QString, QString> metaData = controller->getMetadata(path);
    
    m_title = metaData.value("TITLE");
    m_artist = metaData.value("ARTIST");
    m_album = metaData.value("ALBUM");
}
