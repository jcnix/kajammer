CMAKE_MINIMUM_REQUIRED( VERSION 2.6 )
PROJECT( kajammer )

SET( CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/CMake )
set(CMAKE_CXX_FLAGS "-g -Wall")

FIND_PACKAGE( Qt4 REQUIRED )
FIND_PACKAGE( Phonon REQUIRED )
FIND_PACKAGE( Kajamtag )
FIND_PACKAGE( LastFM )

SET( QT_USE_GUI TRUE )
INCLUDE( ${QT_USE_FILE} )
INCLUDE ( CheckIncludeFiles )
CHECK_INCLUDE_FILES ( kajamtag/kajamtag.h HAVE_KAJAMTAG_H )
FIND_PATH( HAVE_LASTFM_H lastfm.h /usr/include /usr/local/include )
CONFIGURE_FILE( ${CMAKE_CURRENT_SOURCE_DIR}/src/config.h.in ${CMAKE_CURRENT_SOURCE_DIR}/src/config.h )

SET( kajammer_SRCS
	src/main.cpp
	src/dialogs/AboutDialog.cpp
	src/Cli.cpp
	src/dialogs/CollectionScanner.cpp
	src/Controller.cpp
	src/services/LastFM.cpp
	src/gui/MainWindow.cpp
	src/Manager.cpp
	src/gui/MediaControls.cpp
	src/gui/MenuBar.cpp
	src/Options.cpp
	src/dialogs/OptionsDialog.cpp
	src/playlists/Playlist.cpp
	src/playlists/PlaylistManager.cpp
	src/dialogs/PlaylistEditor.cpp
	src/gui/widgets/ToggleButton.cpp
	src/gui/widgets/TrayIcon.cpp 
)

SET( kajammer_MOC_HEADERS
	src/dialogs/AboutDialog.h
	src/Cli.h
	src/dialogs/CollectionScanner.h
	src/Controller.h
	src/services/LastFM.h
	src/gui/MainWindow.h
	src/Manager.h
	src/gui/MediaControls.h
	src/gui/MenuBar.h
	src/dialogs/OptionsDialog.h
	src/playlists/Playlist.h
	src/playlists/PlaylistManager.h
	src/dialogs/PlaylistEditor.h
	src/gui/widgets/ToggleButton.h
	src/gui/widgets/TrayIcon.h
)

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

