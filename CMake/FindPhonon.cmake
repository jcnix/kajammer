FIND_PATH( Phonon_INCLUDE_DIR phononnamespace.h /usr/include /usr/include/phonon /usr/local/include/phonon )

FIND_LIBRARY( Phonon_LIBRARY NAMES phonon PATH /usr/lib /usr/local/lib /usr/lib64 /usr/local/lib64 ) 

IF ( Phonon_INCLUDE_DIR AND Phonon_LIBRARY )
   SET( Phonon_FOUND TRUE )
ENDIF ( Phonon_INCLUDE_DIR AND Phonon_LIBRARY )

IF( Phonon_FOUND )
   IF( NOT Phonon_FIND_QUIETLY )
      MESSAGE( STATUS "Found Phonon: ${Phonon_LIBRARY}" )
   ENDIF( NOT Phonon_FIND_QUIETLY )
ELSE( Phonon_FOUND )
   IF( Phonon_FIND_REQUIRED )
	  MESSAGE( FATAL_ERROR "Could not find Phonon" )
   ENDIF( Phonon_FIND_REQUIRED )
ENDIF( Phonon_FOUND )
