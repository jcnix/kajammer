CMAKE_MINIMUM_REQUIRED( VERSION 2.6 )
PROJECT( kajammer )

SET( CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/CMake )

FIND_PACKAGE( Qt4 REQUIRED )
FIND_PACKAGE( Phonon REQUIRED )
FIND_PACKAGE( Kajamtag )
FIND_PACKAGE( LastFM )

SET( QT_USE_GUI TRUE )
INCLUDE( ${QT_USE_FILE} )
INCLUDE ( CheckIncludeFiles )
CHECK_INCLUDE_FILES ( kajamtag/kajamtag.h HAVE_KAJAMTAG_H )
CHECK_INCLUDE_FILES ( lastfm.h HAVE_LASTFM_H )
CONFIGURE_FILE( ${CMAKE_CURRENT_SOURCE_DIR}/src/config.h.in ${CMAKE_CURRENT_SOURCE_DIR}/src/headers/config.h )

SET( kajammer_SRCS src/main.cpp src/cli.cpp src/collectionscanner.cpp src/controller.cpp src/mainwindow.cpp src/mediacontrols.cpp src/menubar.cpp src/options.cpp src/optionsPanel.cpp src/playlist.cpp src/playlistEditor.cpp src/togglebutton.cpp src/trayicon.cpp )

SET( kajammer_MOC_HEADERS src/headers/cli.h src/headers/collectionscanner.h src/headers/controller.h src/headers/mainwindow.h src/headers/mediacontrols.h src/headers/menubar.h src/headers/optionsPanel.h src/headers/playlist.h src/headers/playlistEditor.h src/headers/togglebutton.h src/headers/trayicon.h )

QT4_WRAP_CPP( kajammer_MOC_HEADERS ${kajammer_MOC_HEADERS} )

IF( Kajamtag_LIBRARY )
  SET( Kajamtag_LIB ${Kajamtag_LIBRARY} )
ENDIF( Kajamtag_LIBRARY )

IF( LastFM_LIBRARY )
    SET( LastFM_LIB ${LastFM_LIBRARY} )
    SET( QTNETWORKLIB ${QT_QTNETWORK_LIBRAREIS} )
    SET( QTXMLLIB ${QT_QTXML_LIBRARIES} )
    SET( QTNETWORKHEAD ${QT_QTNETWORK_INCLUDE_DIR} )
    SET( QTXMLHEAD ${QT_QTXML_INCLUDE_DIR} )
ENDIF( LastFM_LIBRARY )

INCLUDE_DIRECTORIES(
        headers/
        ${QT_INCLUDE_DIR}
        ${QT_GUI_INCLUDE_DIR}
        ${QTNETWORKHEAD}
        ${QTXMLHEAD}
)

ADD_EXECUTABLE( kajammer ${kajammer_SRCS} ${kajammer_MOC_HEADERS} )

TARGET_LINK_LIBRARIES(
        kajammer
        ${QT_LIBRARIES}
        ${QT_GUI_LIBRARIES}
        ${Phonon_LIBRARY}
        ${Kajamtag_LIB}
        ${LastFM_LIB}
        ${QTNETWORKLIB}
        ${QTXMLLIB}
)

INSTALL(TARGETS kajammer DESTINATION /usr/bin)
INSTALL(FILES res/kajammer.png DESTINATION /usr/share/icons)
INSTALL(FILES res/kajammer.desktop DESTINATION /usr/share/applications)

