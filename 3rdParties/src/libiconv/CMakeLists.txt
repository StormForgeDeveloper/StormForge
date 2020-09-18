



include_directories(BEFORE 
	./
	libiconv-1.15/libcharset/include
)

add_definitions(-DLIBDIR="")

set(SRC_FILES
    libiconv-1.15/libcharset/lib/localcharset.c
    libiconv-1.15/lib/iconv.c
)



add_library(iconv ${SRC_FILES})



install (TARGETS iconv
         ARCHIVE DESTINATION lib COMPONENT SF3rdParties
         LIBRARY DESTINATION lib COMPONENT SF3rdParties
         RUNTIME DESTINATION bin COMPONENT SF3rdParties)



