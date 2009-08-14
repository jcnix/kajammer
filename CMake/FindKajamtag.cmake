FIND_PATH( Kajamtag_INCLUDE_DIR kajamtag.h /usr/include /usr/include/kajamtag /usr/local/include/kajamtag )

FIND_LIBRARY( Kajamtag_LIBRARY NAMES kajamtag PATH /usr/lib /usr/local/lib /usr/lib64 /usr/local/lib64 ) 

IF ( Kajamtag_INCLUDE_DIR AND Kajamtag_LIBRARY )
   SET( Kajamtag_FOUND TRUE )
ENDIF ( Kajamtag_INCLUDE_DIR AND Kajamtag_LIBRARY )

IF( Kajamtag_FOUND )
   IF( NOT Kajamtag_FIND_QUIETLY )
      MESSAGE( STATUS "Found Kajamtag: ${Kajamtag_LIBRARY}" )
   ENDIF( NOT Kajamtag_FIND_QUIETLY )
ELSE( Kajamtag_FOUND )
   IF( Kajamtag_FIND_REQUIRED )
	  MESSAGE( FATAL_ERROR "Could not find Kajamtag" )
   ENDIF( Kajamtag_FIND_REQUIRED )
ENDIF( Kajamtag_FOUND )