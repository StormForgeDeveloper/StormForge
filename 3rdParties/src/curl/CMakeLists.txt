

#https://github.com/curl/curl.git



include_directories(
	./
	curl/lib
	curl/include
	curl/src
)


if(WIN32)
	include_directories( AFTER
		../../Windows/Common/include
	)
endif()


# From CURL make file
function(transform_makefile_inc INPUT_FILE OUTPUT_FILE)
  file(READ ${INPUT_FILE} MAKEFILE_INC_TEXT)
  string(REPLACE "$(top_srcdir)"   "\${CURL_SOURCE_DIR}" MAKEFILE_INC_TEXT ${MAKEFILE_INC_TEXT})
  string(REPLACE "$(top_builddir)" "\${CURL_BINARY_DIR}" MAKEFILE_INC_TEXT ${MAKEFILE_INC_TEXT})

  string(REGEX REPLACE "\\\\\n" "!π!α!" MAKEFILE_INC_TEXT ${MAKEFILE_INC_TEXT})
  string(REGEX REPLACE "([a-zA-Z_][a-zA-Z0-9_]*)[\t ]*=[\t ]*([^\n]*)" "SET(\\1 \\2)" MAKEFILE_INC_TEXT ${MAKEFILE_INC_TEXT})
  string(REPLACE "!π!α!" "\n" MAKEFILE_INC_TEXT ${MAKEFILE_INC_TEXT})

  string(REGEX REPLACE "\\$\\(([a-zA-Z_][a-zA-Z0-9_]*)\\)" "\${\\1}" MAKEFILE_INC_TEXT ${MAKEFILE_INC_TEXT})    # Replace $() with ${}
  string(REGEX REPLACE "@([a-zA-Z_][a-zA-Z0-9_]*)@" "\${\\1}" MAKEFILE_INC_TEXT ${MAKEFILE_INC_TEXT})    # Replace @@ with ${}, even if that may not be read by CMake scripts.
  file(WRITE ${OUTPUT_FILE} ${MAKEFILE_INC_TEXT})
  set_property(DIRECTORY APPEND PROPERTY CMAKE_CONFIGURE_DEPENDS "${INPUT_FILE}")
endfunction()

transform_makefile_inc("curl/lib/Makefile.inc" "curl/lib/Makefile.inc.cmake")
include(curl/lib/Makefile.inc.cmake)

list(TRANSFORM CSOURCES PREPEND curl/lib/)
list(TRANSFORM HHEADERS PREPEND curl/lib/)

list(APPEND HHEADERS
  curl_config.h
  )

set(SRC_FILES
    ${CSOURCES}
	${HHEADERS}
)

add_definitions(-DBUILDING_LIBCURL)
add_definitions(-DCURL_STATICLIB)
add_definitions(-DHAVE_CONFIG_H)
add_definitions(-DUSE_WEBSOCKETS)

add_library(curl ${SRC_FILES})

install (TARGETS curl
         ARCHIVE DESTINATION lib COMPONENT SF3rdParties
         LIBRARY DESTINATION lib COMPONENT SF3rdParties
         RUNTIME DESTINATION bin COMPONENT SF3rdParties)


