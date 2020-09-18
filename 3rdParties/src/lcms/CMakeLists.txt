


include_directories(AFTER 
	lcms2-2.7/include
)



set(SRC_FILES
    lcms2-2.7/src/cmscam02.c
    lcms2-2.7/src/cmscgats.c
    lcms2-2.7/src/cmscnvrt.c
    lcms2-2.7/src/cmserr.c
    lcms2-2.7/src/cmsgamma.c
    lcms2-2.7/src/cmsgmt.c
    lcms2-2.7/src/cmshalf.c
    lcms2-2.7/src/cmsintrp.c
    lcms2-2.7/src/cmsio0.c
    lcms2-2.7/src/cmsio1.c
    lcms2-2.7/src/cmslut.c
    lcms2-2.7/src/cmsmd5.c
    lcms2-2.7/src/cmsmtrx.c
    lcms2-2.7/src/cmsnamed.c
    lcms2-2.7/src/cmsopt.c
    lcms2-2.7/src/cmspack.c
    lcms2-2.7/src/cmspcs.c
    lcms2-2.7/src/cmsplugin.c
    lcms2-2.7/src/cmsps2.c
    lcms2-2.7/src/cmssamp.c
    lcms2-2.7/src/cmssm.c
    lcms2-2.7/src/cmstypes.c
    lcms2-2.7/src/cmsvirt.c
    lcms2-2.7/src/cmswtpnt.c
    lcms2-2.7/src/cmsxform.c
    lcms2-2.7/include/lcms.h
    lcms2-2.7/include/lcms2.h
    lcms2-2.7/include/lcms2_plugin.h
    lcms2-2.7/src/lcms2_internal.h
)



add_library(lcms2 ${SRC_FILES})


install (TARGETS lcms2
         ARCHIVE DESTINATION lib COMPONENT SF3rdParties
         LIBRARY DESTINATION lib COMPONENT SF3rdParties
         RUNTIME DESTINATION bin COMPONENT SF3rdParties)




