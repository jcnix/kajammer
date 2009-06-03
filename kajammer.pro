TEMPLATE = app
DESTDIR = bin
TARGET = kajammer
VERSION = 0.46
CONFIG -= debug_and_release
CONFIG += debug 
QT = core gui phonon

SOURCES += src/mainwindow.cpp src/mediacontrols.cpp src/controller.cpp src/menubar.cpp src/main.cpp src/playlist.cpp src/cli.cpp src/optionsPanel.cpp src/options.cpp src/playlistEditor.cpp src/widgets/togglebutton.cpp src/trayicon.cpp

HEADERS += src/headers/menubar.h src/headers/mainwindow.h src/headers/mediacontrols.h src/headers/controller.h src/headers/playlist.h src/headers/cli.h src/headers/optionsPanel.h src/headers/options.h src/headers/playlistEditor.h src/widgets/togglebutton.h src/headers/trayicon.h

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
LIBS += 
target.path = /usr/bin
target.files = bin/kajammer
menu.path = /usr/share/applications
menu.files = res/kajammer.desktop
INSTALLS += target menu

