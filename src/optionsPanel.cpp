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
    connect(browseDefaultOpenBtn, SIGNAL(clicked()), this, 
            SLOT(browseDefaultOpen()));
}

OptionsPanel::~OptionsPanel()
{    
    delete defaultOpen;
    delete browseDefaultOpenBtn;
    delete shuffBox;
    delete trayIconOption;
    
    #ifdef HAVE_LASTFM_H
    delete lastfmBox;
    delete lastfmUser;
    delete lastfmPass;
    #endif
    
    delete defaultOpenLayout;
    delete formLayout;
}

void OptionsPanel::init()
{   
	setWindowTitle("KaJammer Options");
	
    options = Options::getInstance();
    buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok |
                                    QDialogButtonBox::Cancel);
    
    defaultOpen = new QLineEdit;
    defaultOpen->setMinimumWidth(175);
    browseDefaultOpenBtn = new QPushButton(style()->standardIcon(QStyle::SP_DialogOpenButton), "", this);
    
    shuffBox = new QCheckBox;
    trayIconOption = new QCheckBox;

    #ifdef HAVE_LASTFM_H
    lastfmBox = new QCheckBox;
    lastfmUser = new QLineEdit;
    lastfmPass = new QLineEdit;
    lastfmPass->setEchoMode(QLineEdit::Password);
    #endif
    
    defaultOpenLayout = new QHBoxLayout;
    defaultOpenLayout->addWidget(defaultOpen);
    defaultOpenLayout->addWidget(browseDefaultOpenBtn);

    formLayout = new QFormLayout;
    formLayout->addRow("Music directory", defaultOpenLayout);
    formLayout->addRow("No repeat on shuffle", shuffBox);
    formLayout->addRow("Enable Tray Icon", trayIconOption);
    #ifdef HAVE_LASTFM_H
    formLayout->addRow("Enable Last.fm", lastfmBox);
    formLayout->addRow("Last.fm Username", lastfmUser);
    formLayout->addRow("Last.fm Password", lastfmPass);
    formLayout->addRow("", buttonBox);
    #endif

    setLayout(formLayout);
}

void OptionsPanel::populate()
{    
    defaultOpen->setText(options->getDefaultOpenDir());
    shuffBox->setChecked(options->isShuff_no_repeat());
    trayIconOption->setChecked(options->trayIcon());
    #ifdef HAVE_LASTFM_H
    lastfmBox->setChecked(options->useLastFm());
    lastfmUser->setText(options->getLastFmUser());
    lastfmPass->setText(options->getLastFmPass());
    #endif
}

void OptionsPanel::save()
{
    options->setDefaultOpenDir(defaultOpen->text());
    options->setShuff_no_repeat(shuffBox->isChecked());
    options->setTrayIcon(trayIconOption->isChecked());
    #ifdef HAVE_LASTFM_H
    options->setLastFm(lastfmBox->isChecked());
    options->setLastFmUser(lastfmUser->text());
    options->setLastFmPass(lastfmPass->text());
    #endif
    options->save();
    
    accept();
}

void OptionsPanel::browseDefaultOpen()
{
    QString dir;
    dir = QFileDialog::getExistingDirectory(NULL, 
                                            "Open Directory", 
                                            QDir::homePath(),
                                            QFileDialog::ShowDirsOnly);
                                             
     defaultOpen->setText(dir);
}

void OptionsPanel::closeEvent(QCloseEvent *event)
{
    delete this;
    event->accept();
}
