



include_directories(AFTER 
	../lcms/lcms2-2.7/include
)

set(SRC_FILES
    libmng-2.0.3/libmng.h
    libmng-2.0.3/libmng_chunk_descr.h
    libmng-2.0.3/libmng_chunk_io.h
    libmng-2.0.3/libmng_chunk_prc.h
    libmng-2.0.3/libmng_chunks.h
    libmng-2.0.3/libmng_cms.h
    libmng-2.0.3/libmng_conf.h
    libmng-2.0.3/libmng_data.h
    libmng-2.0.3/libmng_display.h
    libmng-2.0.3/libmng_dither.h
    libmng-2.0.3/libmng_error.h
    libmng-2.0.3/libmng_filter.h
    libmng-2.0.3/libmng_jpeg.h
    libmng-2.0.3/libmng_memory.h
    libmng-2.0.3/libmng_object_prc.h
    libmng-2.0.3/libmng_objects.h
    libmng-2.0.3/libmng_pixels.h
    libmng-2.0.3/libmng_read.h
    libmng-2.0.3/libmng_trace.h
    libmng-2.0.3/libmng_types.h
    libmng-2.0.3/libmng_write.h
    libmng-2.0.3/libmng_zlib.h
    libmng-2.0.3/libmng_callback_xs.c
    libmng-2.0.3/libmng_chunk_descr.c
    libmng-2.0.3/libmng_chunk_io.c
    libmng-2.0.3/libmng_chunk_prc.c
    libmng-2.0.3/libmng_chunk_xs.c
    libmng-2.0.3/libmng_cms.c
    libmng-2.0.3/libmng_display.c
    libmng-2.0.3/libmng_dither.c
    libmng-2.0.3/libmng_error.c
    libmng-2.0.3/libmng_filter.c
    libmng-2.0.3/libmng_hlapi.c
    libmng-2.0.3/libmng_jpeg.c
    libmng-2.0.3/libmng_object_prc.c
    libmng-2.0.3/libmng_pixels.c
    libmng-2.0.3/libmng_prop_xs.c
    libmng-2.0.3/libmng_read.c
    libmng-2.0.3/libmng_trace.c
    libmng-2.0.3/libmng_write.c
    libmng-2.0.3/libmng_zlib.c
)



add_library(mng ${SRC_FILES})


install (TARGETS mng
         ARCHIVE DESTINATION lib COMPONENT SF3rdParties
         LIBRARY DESTINATION lib COMPONENT SF3rdParties
         RUNTIME DESTINATION bin COMPONENT SF3rdParties)




