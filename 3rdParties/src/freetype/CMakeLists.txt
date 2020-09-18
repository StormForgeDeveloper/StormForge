


include_directories(
	./
	freetype-2.10.0/include
	freetype-2.10.0/include/internal
	freetype-2.10.0/src
)

add_definitions(-DFT2_BUILD_LIBRARY)


set(SRC_FILES
	freetype-2.10.0/src/autofit/autofit.c
    freetype-2.10.0/src/base/ftbase.c
	freetype-2.10.0/src/base/md5.c
    freetype-2.10.0/src/bdf/bdf.c
    freetype-2.10.0/src/cache/ftccache.c
    freetype-2.10.0/src/cff/cff.c
    freetype-2.10.0/src/cid/type1cid.c
    freetype-2.10.0/src/gzip/ftgzip.c
    freetype-2.10.0/src/lzw/ftlzw.c
    freetype-2.10.0/src/lzw/ftzopen.c
    freetype-2.10.0/src/pcf/pcf.c
    freetype-2.10.0/src/pfr/pfr.c
    freetype-2.10.0/src/psaux/psaux.c
    freetype-2.10.0/src/pshinter/pshinter.c
    freetype-2.10.0/src/psnames/psnames.c
    freetype-2.10.0/src/raster/raster.c
    freetype-2.10.0/src/sfnt/sfnt.c
    freetype-2.10.0/src/smooth/smooth.c
    freetype-2.10.0/src/truetype/truetype.c
    freetype-2.10.0/src/type1/type1.c
    freetype-2.10.0/src/type42/t42drivr.c
    freetype-2.10.0/src/type42/t42objs.c
    freetype-2.10.0/src/type42/t42parse.c
    freetype-2.10.0/src/type42/type42.c
    freetype-2.10.0/src/winfonts/winfnt.c
)



add_library(freetype ${SRC_FILES})

install (TARGETS freetype
         ARCHIVE DESTINATION lib COMPONENT SF3rdParties
         LIBRARY DESTINATION lib COMPONENT SF3rdParties
         RUNTIME DESTINATION bin COMPONENT SF3rdParties)



