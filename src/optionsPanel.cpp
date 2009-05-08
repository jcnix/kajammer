/*
 * File:   optionsPanel.cpp
 * Author: casey
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

#include "headers/optionsPanel.h"

OptionsPanel::OptionsPanel()
{
    init();
    populate();
    
    connect(buttonBox, SIGNAL(accepted()), this, SLOT(save()));
    connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));
    connect(browseDefaultOpenBtn, SIGNAL(clicked()), this, SLOT(browseDefaultOpen()));
}

void OptionsPanel::init()
{   
    options = Options::getInstance();

    buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    defaultOpenLabel = new QLabel("Music directory");
    defaultOpen = new QLineEdit;
    defaultOpen->setMinimumWidth(175);
    browseDefaultOpenBtn = new QPushButton("...");
    
    QHBoxLayout *defaultOpenLayout = new QHBoxLayout;
    defaultOpenLayout->addWidget(defaultOpenLabel);
    defaultOpenLayout->addWidget(defaultOpen);
    defaultOpenLayout->addWidget(browseDefaultOpenBtn);
    
    QVBoxLayout *vLayout = new QVBoxLayout;
    vLayout->addLayout(defaultOpenLayout);
    vLayout->addWidget(buttonBox);
    setLayout(vLayout);
}

void OptionsPanel::populate()
{    
    QString defaultOpenDir = options->getDefaultOpenDir();
    defaultOpen->setText(defaultOpenDir);
}

void OptionsPanel::save()
{
    options->setDefaultOpenDir(defaultOpen->text());
    options->save();
    
    accept();
}

void OptionsPanel::browseDefaultOpen()
{
    QString dir;
    dir = QFileDialog::getExistingDirectory(NULL, 
                                             "Open Directory", 
                                             QDir::homePath(),
                                             QFileDialog::ShowDirsOnly
                                             | QFileDialog::DontResolveSymlinks);
                                             
     defaultOpen->setText(dir);
}
