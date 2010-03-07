/*
 * File:   GeneralOptions.cpp
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

#include "OptionsDialog.h"

GeneralOptions::GeneralOptions()
{
    init();
    populate();
}

GeneralOptions::~GeneralOptions()
{
    delete defaultOpen;
    delete browseDefaultOpenBtn;
    delete shuffBox;
    delete trayIconOption;
    delete notifyBox;
    
    delete defaultOpenLayout;
    delete formLayout;
}

void GeneralOptions::init()
{    
    options = Options::getInstance();
                                    
    defaultOpen = new QLineEdit;
    defaultOpen->setMinimumWidth(175);
    browseDefaultOpenBtn = new QPushButton(style()->standardIcon(QStyle::SP_DialogOpenButton), "", this);
    
    shuffBox = new QCheckBox;
    trayIconOption = new QCheckBox;
    notifyBox = new QCheckBox;
    
    defaultOpenLayout = new QHBoxLayout;
    defaultOpenLayout->addWidget(defaultOpen);
    defaultOpenLayout->addWidget(browseDefaultOpenBtn);

    formLayout = new QFormLayout;
    formLayout->addRow("Music directory", defaultOpenLayout);
    formLayout->addRow("No repeat on shuffle", shuffBox);
    formLayout->addRow("Enable Tray Icon", trayIconOption);
    formLayout->addRow("Tray Notifications", notifyBox);

    setLayout(formLayout);
}

void GeneralOptions::populate()
{
    defaultOpen->setText(options->getDefaultOpenDir());
    shuffBox->setChecked(options->isShuff_no_repeat());
    trayIconOption->setChecked(options->trayIcon());
    notifyBox->setChecked(options->get_notify_on_change());
}

void GeneralOptions::save()
{
    options->setDefaultOpenDir(defaultOpen->text());
    options->setShuff_no_repeat(shuffBox->isChecked());
    options->setTrayIcon(trayIconOption->isChecked());
    options->set_notify_on_change(notifyBox->isChecked());
}

void GeneralOptions::browseDefaultOpen()
{
    QString dir;
    dir = QFileDialog::getExistingDirectory(NULL, 
                                            "Open Directory", 
                                            QDir::homePath(),
                                            QFileDialog::ShowDirsOnly);
                                             
     defaultOpen->setText(dir);
}
