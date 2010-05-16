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

#include "TagEditor.h"

#ifdef HAVE_KAJAMTAG_H
#include <kajamtag/kajamtag.h>
#endif

TagEditor::TagEditor()
{
    init();
    
    connect(m_acceptBtn, SIGNAL(clicked()), this, SLOT(writeData()));
    connect(m_buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
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
    m_tagList = new QListWidget;
    m_tagList->addItem("KTAG");
    m_tagList->addItem("KALBUM");
    m_tagList->addItem("KARTIST");
    
    m_lineEdit = new QLineEdit;
    
    hLayout = new QHBoxLayout;
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
