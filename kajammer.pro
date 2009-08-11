TEMPLATE = app
DESTDIR = bin
TARGET = kajammer
VERSION = 0.46
CONFIG -= debug_and_release
CONFIG += debug 
QT = core gui phonon

SOURCES += src/mainwindow.cpp src/mediacontrols.cpp src/controller.cpp src/menubar.cpp src/main.cpp src/playlist.cpp src/cli.cpp src/optionsPanel.cpp src/options.cpp src/playlistEditor.cpp src/togglebutton.cpp src/trayicon.cpp

HEADERS += src/headers/menubar.h src/headers/mainwindow.h src/headers/mediacontrols.h src/headers/controller.h src/headers/playlist.h src/headers/cli.h src/headers/optionsPanel.h src/headers/options.h src/headers/playlistEditor.h src/headers/togglebutton.h src/headers/trayicon.h

FORMS +=
RESOURCES +=
TRANSLATIONS +=
OBJECTS_DIR = build
MOC_DIR = moc/  
RCC_DIR = 
UI_DIR = 
QMAKE_CC = gcc
QMAKE_CXX = g++
DEFINES += 
INCLUDEPATH += /usr/include/qt4
LIBS += -L/usr/lib/ -lkajamtag 
bintarget.path = /usr/bin
bintarget.files = bin/kajammer
menu.path = /usr/share/applications
menu.files = res/kajammer.desktop
icon.path = /usr/share/icons
icon.files = res/kajammer.png
INSTALLS += bintarget menu icon

