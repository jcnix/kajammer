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
#include <iostream>

OptionsPanel::OptionsPanel()
{
    init();
    populate();
    
    connect(buttonBox, SIGNAL(accepted()), this, SLOT(save()));
    connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));
}

void OptionsPanel::init()
{   
    options = Options::getInstance();
    defaultOpen = new QLineEdit;
    
    buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    
    vLayout = new QVBoxLayout;
    vLayout->addWidget(defaultOpen);
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
