

include_directories(AFTER 
	lpng1617
)


set(SRC_FILES
    lpng1617/png.h
    lpng1617/pngconf.h
    lpng1617/pnglibconf.h
    lpng1617/pngdebug.h
    lpng1617/pnginfo.h
    lpng1617/pngpriv.h
    lpng1617/pngstruct.h
    lpng1617/png.c
    lpng1617/pngerror.c
    lpng1617/pngget.c
    lpng1617/pngmem.c
    lpng1617/pngpread.c
    lpng1617/pngread.c
    lpng1617/pngrio.c
    lpng1617/pngrtran.c
    lpng1617/pngrutil.c
    lpng1617/pngset.c
    lpng1617/pngtrans.c
    lpng1617/pngwio.c
    lpng1617/pngwrite.c
    lpng1617/pngwtran.c
    lpng1617/pngwutil.c
)



add_library(png ${SRC_FILES})


install (TARGETS png
         ARCHIVE DESTINATION lib COMPONENT SF3rdParties
         LIBRARY DESTINATION lib COMPONENT SF3rdParties
         RUNTIME DESTINATION bin COMPONENT SF3rdParties)




