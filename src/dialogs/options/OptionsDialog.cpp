/*
 * File:   OptionsPanel.cpp
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

#include "OptionsDialog.h"

OptionsPanel::OptionsPanel()
{
    init();
    
    connect(buttonBox, SIGNAL(accepted()), this, SLOT(save()));
    connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));
}

OptionsPanel::~OptionsPanel()
{
    delete genOptions;
    #ifdef HAVE_LASTFM_H
    delete lfmOptions;
    #endif
    delete layout;
}

void OptionsPanel::init()
{
	setWindowTitle("KaJammer Options");
	
    options = Options::getInstance();
    buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok |
                                    QDialogButtonBox::Cancel);
    
    tabWidget = new QTabWidget;

    genOptions = new GeneralOptions;
    #ifdef HAVE_LASTFM_H
    lfmOptions = new LastFmOptions;
    #endif
    
    tabWidget->addTab(genOptions, "General");
    tabWidget->addTab(lfmOptions, "Last.fm");
    
    layout = new QHBoxLayout;
    layout->addWidget(tabWidget);
    
    setLayout(layout);
}

void OptionsPanel::save()
{
    genOptions->save();
    #ifdef HAVE_LASTFM_H
    lfmOptions->save();
    #endif
    
    options->save();
    accept();
}

void OptionsPanel::closeEvent(QCloseEvent *event)
{
    done(0);
    delete this;
    event->accept();
}
