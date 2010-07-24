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
    delete notifyTimeBox;
    
    delete defaultOpenLayout;
    delete formLayout;
}

void GeneralOptions::init()
{                                    
    defaultOpen = new QLineEdit;
    defaultOpen->setMinimumWidth(175);
    browseDefaultOpenBtn = new QPushButton(style()->standardIcon(QStyle::SP_DialogOpenButton), "", this);
    
    shuffBox = new QCheckBox;
    trayIconOption = new QCheckBox;
    notifyBox = new QCheckBox;
    notifyTimeBox = new QSpinBox;
    
    defaultOpenLayout = new QHBoxLayout;
    defaultOpenLayout->addWidget(defaultOpen);
    defaultOpenLayout->addWidget(browseDefaultOpenBtn);

    formLayout = new QFormLayout;
    formLayout->addRow("Music directory", defaultOpenLayout);
    formLayout->addRow("No repeat on shuffle", shuffBox);
    formLayout->addRow("Enable Tray Icon", trayIconOption);
    formLayout->addRow("Tray Notifications", notifyBox);
    formLayout->addRow("Notification Time", notifyTimeBox);

    setLayout(formLayout);
}

void GeneralOptions::populate()
{
    defaultOpen->setText(Options::getOption_String(KJ::DEFAULT_OPEN_DIR));
    shuffBox->setChecked(Options::getOption_Bool(KJ::SHUFF_NO_REPEAT));
    trayIconOption->setChecked(Options::getOption_Bool(KJ::USE_TRAY_ICON));
    notifyBox->setChecked(Options::getOption_Bool(KJ::NOTIFY_ON_TRACK_CHANGE));
    notifyTimeBox->setValue(Options::getOption_Int(KJ::NOTIFICATION_TIME));
}

void GeneralOptions::save()
{
    Options::setOption(KJ::DEFAULT_OPEN_DIR, defaultOpen->text());
    Options::setOption(KJ::SHUFF_NO_REPEAT, shuffBox->isChecked());
    Options::setOption(KJ::USE_TRAY_ICON, trayIconOption->isChecked());
    Options::setOption(KJ::NOTIFY_ON_TRACK_CHANGE, notifyBox->isChecked());
    Options::setOption(KJ::NOTIFICATION_TIME, notifyTimeBox->value());
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
