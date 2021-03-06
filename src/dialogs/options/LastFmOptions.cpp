/*
 * File:   LastFmOptions.cpp
 * Author: Casey Jones
 *
 * Created on March 6, 2010, 4:00 PM
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

#include "LastFmOptions.h"

LastFmOptions::LastFmOptions(QWidget *parent) : QWidget(parent)
{
    init();
    populate();
}

LastFmOptions::~LastFmOptions()
{
    delete lastfmBox;
    delete lastfmUser;
    delete lastfmPass;
    delete formLayout;
}

void LastFmOptions::init()
{
    lastfmBox = new QCheckBox;
    lastfmUser = new QLineEdit;
    lastfmPass = new QLineEdit;
    lastfmPass->setEchoMode(QLineEdit::Password);

    formLayout = new QFormLayout;
    formLayout->addRow("Enable Last.fm", lastfmBox);
    formLayout->addRow("Last.fm Username", lastfmUser);
    formLayout->addRow("Last.fm Password", lastfmPass);

    setLayout(formLayout);
}

void LastFmOptions::populate()
{
    #ifdef HAVE_LASTFM_H
    lastfmBox->setChecked(Options::getOption_Bool(KJ::USE_LASTFM));
    lastfmUser->setText(Options::getOption_String(KJ::LASTFM_USER));
    lastfmPass->setText(Options::getOption_String(KJ::LASTFM_PASS));
    #endif
}

void LastFmOptions::save()
{
    #ifdef HAVE_LASTFM_H
    Options::setOption(KJ::USE_LASTFM, lastfmBox->isChecked());
    Options::setOption(KJ::LASTFM_USER, lastfmUser->text());
    Options::setOption(KJ::LASTFM_PASS, lastfmPass->text());
    #endif
}
