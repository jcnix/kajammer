FIND_PATH( LastFM_INCLUDE_DIR lastfm.h /usr/local/include /usr/include )

FIND_LIBRARY( LastFM_LIBRARY NAMES lastfm PATH /usr/lib /usr/local/lib /usr/lib64 /usr/local/lib64 ) 

IF ( LastFM_INCLUDE_DIR AND LastFM_LIBRARY )
   SET( LastFM_FOUND TRUE )
ENDIF ( LastFM_INCLUDE_DIR AND LastFM_LIBRARY )

IF( LastFM_FOUND )
    IF( NOT LastFM_FIND_QUIETLY )
        MESSAGE( STATUS "Found LastFM: ${LastFM_LIBRARY}" )
    ENDIF( NOT LastFM_FIND_QUIETLY )
ELSE( LastFM_FOUND )
   IF( LastFM_FIND_REQUIRED )
	  MESSAGE( FATAL_ERROR "Could not find LastFM" )
   ENDIF( LastFM_FIND_REQUIRED )
ENDIF( LastFM_FOUND )
