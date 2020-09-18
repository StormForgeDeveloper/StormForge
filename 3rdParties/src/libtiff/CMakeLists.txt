

include_directories(AFTER 
	./
	tiff-4.0.3/libtiff
)


set(SRC_FILES
    tiff-4.0.3/libtiff/tif_aux.c
    tiff-4.0.3/libtiff/tif_close.c
    tiff-4.0.3/libtiff/tif_codec.c
    tiff-4.0.3/libtiff/tif_color.c
    tiff-4.0.3/libtiff/tif_compress.c
    tiff-4.0.3/libtiff/tif_dir.c
    tiff-4.0.3/libtiff/tif_dirinfo.c
    tiff-4.0.3/libtiff/tif_dirread.c
    tiff-4.0.3/libtiff/tif_dirwrite.c
    tiff-4.0.3/libtiff/tif_dumpmode.c
    tiff-4.0.3/libtiff/tif_error.c
    tiff-4.0.3/libtiff/tif_extension.c
    tiff-4.0.3/libtiff/tif_fax3.c
    tiff-4.0.3/libtiff/tif_fax3sm.c
    tiff-4.0.3/libtiff/tif_flush.c
    tiff-4.0.3/libtiff/tif_getimage.c
    tiff-4.0.3/libtiff/tif_jbig.c
    tiff-4.0.3/libtiff/tif_jpeg.c
    tiff-4.0.3/libtiff/tif_jpeg_12.c
    tiff-4.0.3/libtiff/tif_luv.c
    tiff-4.0.3/libtiff/tif_lzma.c
    tiff-4.0.3/libtiff/tif_lzw.c
    tiff-4.0.3/libtiff/tif_next.c
    tiff-4.0.3/libtiff/tif_ojpeg.c
    tiff-4.0.3/libtiff/tif_open.c
    tiff-4.0.3/libtiff/tif_packbits.c
    tiff-4.0.3/libtiff/tif_pixarlog.c
    tiff-4.0.3/libtiff/tif_predict.c
    tiff-4.0.3/libtiff/tif_print.c
    tiff-4.0.3/libtiff/tif_read.c
    tiff-4.0.3/libtiff/tif_stream.cxx
    tiff-4.0.3/libtiff/tif_strip.c
    tiff-4.0.3/libtiff/tif_swab.c
    tiff-4.0.3/libtiff/tif_thunder.c
    tiff-4.0.3/libtiff/tif_tile.c
    tiff-4.0.3/libtiff/tif_unix.c
    tiff-4.0.3/libtiff/tif_version.c
    tiff-4.0.3/libtiff/tif_warning.c
    tiff-4.0.3/libtiff/tif_win32.c
    tiff-4.0.3/libtiff/tif_write.c
    tiff-4.0.3/libtiff/tif_zip.c
    tiff-4.0.3/libtiff/t4.h
    tiff-4.0.3/libtiff/tiff.h
    tiff-4.0.3/libtiff/tiffconf.h
    tiff-4.0.3/libtiff/tiffconf.vc.h
    tiff-4.0.3/libtiff/tiffconf.wince.h
    tiff-4.0.3/libtiff/tiffio.h
    tiff-4.0.3/libtiff/tiffio.hxx
    tiff-4.0.3/libtiff/tiffiop.h
    tiff-4.0.3/libtiff/tiffvers.h
    tiff-4.0.3/libtiff/tif_dir.h
    tiff-4.0.3/libtiff/tif_fax3.h
    tiff-4.0.3/libtiff/tif_predict.h
    tiff-4.0.3/libtiff/uvcode.h
)



add_library(tiff ${SRC_FILES})


install (TARGETS tiff
         ARCHIVE DESTINATION lib COMPONENT SF3rdParties
         LIBRARY DESTINATION lib COMPONENT SF3rdParties
         RUNTIME DESTINATION bin COMPONENT SF3rdParties)




