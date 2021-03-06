/*
 * File:   AboutDialog.cpp
 * Author: Casey Jones
 *
 * Created on November 13, 2009, 11:44 PM
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

#include "AboutDialog.h"

AboutDialog::AboutDialog()
{
    init();
    
    connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
}

AboutDialog::~AboutDialog()
{
    delete iconLabel;
    delete aboutLabel;
    delete authorsLabel;
    delete buttonBox;
    delete topLayout;
    delete layout;
}

void AboutDialog::init()
{
    setWindowTitle("About KaJammer");
    
    buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok);
    
    QPixmap icon(KAJAMMER_ICON);
    icon = icon.scaled(64,64);
    
    iconLabel = new QLabel();
    iconLabel->setPixmap(icon);
    
    std::stringstream s;
    s << "Kajammer " << KAJAMMER_VER << " is licensed under the GPLv3.\n";
    #ifdef HAVE_KAJAMTAG_H
    s << "Kajamtag " << KAJAMTAG_VERSION << " is licensed under the LGPLv3.\n";
    #endif
    QString about(QString::fromStdString(s.str()));
    aboutLabel = new QLabel(about);
    
    authorsLabel = new QLabel("By Casey Jones");
    
    topLayout = new QHBoxLayout;
    topLayout->addWidget(iconLabel);
    topLayout->addWidget(aboutLabel);
    
    layout = new QVBoxLayout;
    layout->addLayout(topLayout);
    layout->addWidget(authorsLabel);
    layout->addWidget(buttonBox);
    
    setLayout(layout);
}

void AboutDialog::closeEvent(QCloseEvent *event)
{
    done(0);
    delete this;
    event->accept();
}
