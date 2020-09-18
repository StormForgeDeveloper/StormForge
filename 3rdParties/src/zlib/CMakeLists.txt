

configure_file(	zlib-1.2.8/zconf.h.cmakein
		zlib-1.2.8/zconf.h @ONLY)


set(SRC_FILES
    zlib-1.2.8/adler32.c
    zlib-1.2.8/compress.c
    zlib-1.2.8/crc32.c
    zlib-1.2.8/deflate.c
    zlib-1.2.8/gzclose.c
    zlib-1.2.8/gzlib.c
    zlib-1.2.8/gzread.c
    zlib-1.2.8/gzwrite.c
    zlib-1.2.8/infback.c
    zlib-1.2.8/inffast.c
    zlib-1.2.8/inflate.c
    zlib-1.2.8/inftrees.c
    zlib-1.2.8/trees.c
    zlib-1.2.8/uncompr.c
    zlib-1.2.8/zutil.c
)



add_library(zlib ${SRC_FILES})

install (TARGETS zlib
         ARCHIVE DESTINATION lib COMPONENT SF3rdParties
         LIBRARY DESTINATION lib COMPONENT SF3rdParties
         RUNTIME DESTINATION bin COMPONENT SF3rdParties)



