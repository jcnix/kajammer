/*
 * File:   optionsPanel.cpp
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

    setWindowTitle("KaJammer Options");
    
    buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    
    defaultOpenLabel = new QLabel("Music directory: ");
    defaultOpen = new QLineEdit;
    defaultOpen->setMinimumWidth(175);
    browseDefaultOpenBtn = new QPushButton("...");
    
    shuffLabel = new QLabel("Shuffle-no-repeat: ");
    shuffBox = new QCheckBox;
    
    QHBoxLayout *defaultOpenLayout = new QHBoxLayout;
    defaultOpenLayout->addWidget(defaultOpenLabel);
    defaultOpenLayout->addWidget(defaultOpen);
    defaultOpenLayout->addWidget(browseDefaultOpenBtn);
    
    QHBoxLayout *shuffLayout = new QHBoxLayout;
    shuffLayout->addWidget(shuffLabel);
    shuffLayout->addWidget(shuffBox);
    
    QVBoxLayout *vLayout = new QVBoxLayout;
    vLayout->addLayout(defaultOpenLayout);
    vLayout->addLayout(shuffLayout);
    vLayout->addWidget(buttonBox);
    setLayout(vLayout);
}

void OptionsPanel::populate()
{    
    QString defaultOpenDir = options->getDefaultOpenDir();
    defaultOpen->setText(defaultOpenDir);
    
    shuffBox->setChecked(options->isShuff_no_repeat());
}

void OptionsPanel::save()
{
    options->setDefaultOpenDir(defaultOpen->text());
    options->setShuff_no_repeat(shuffBox->isChecked());
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
