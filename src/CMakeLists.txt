INCLUDE_DIRECTORIES(.)

SET( QT_USE_GUI TRUE )
INCLUDE( ${QT_USE_FILE} )
INCLUDE ( CheckIncludeFiles )
CHECK_INCLUDE_FILES ( kajamtag.h HAVE_KAJAMTAG_H )
CONFIGURE_FILE( ${CMAKE_CURRENT_SOURCE_DIR}/config.h.in ${CMAKE_CURRENT_SOURCE_DIR}/headers/config.h )


SET(kajammer_SRCS main.cpp cli.cpp controller.cpp mainwindow.cpp mediacontrols.cpp menubar.cpp options.cpp optionsPanel.cpp playlist.cpp playlistEditor.cpp togglebutton.cpp trayicon.cpp)

SET( kajammer_MOC_HEADERS headers/cli.h headers/controller.h headers/mainwindow.h headers/mediacontrols.h headers/menubar.h headers/optionsPanel.h headers/playlist.h headers/playlistEditor.h headers/togglebutton.h headers/trayicon.h)

QT4_WRAP_CPP( kajammer_MOC_HEADERS ${kajammer_MOC_HEADERS} )

IF( Kajamtag_LIBRARY )
  SET( Kajamtag_LIB ${Kajamtag_LIBRARY} )
  SET( Kajamtag_H ${HAVE_KAJAMTAG_H} )
ENDIF( Kajamtag_LIBRARY )

INCLUDE_DIRECTORIES( headers/ ${QT_INCLUDE_DIR} ${QT_GUI_INCLUDE_DIR} ${Phonon_INCLUDE_DIR} ${Kajamtag_H} )
ADD_EXECUTABLE( kajammer ${kajammer_SRCS} ${kajammer_MOC_HEADERS} )

TARGET_LINK_LIBRARIES( kajammer ${QT_LIBRARIES} ${QT_PHONON_LIBRARIES} ${QT_GUI_LIBRARIES} ${Phonon_LIBRARY} ${Kajamtag} )
INSTALL(TARGETS kajammer DESTINATION bin)
