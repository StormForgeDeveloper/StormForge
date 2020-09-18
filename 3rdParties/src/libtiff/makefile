

###################################################

ifndef TARGET_PLATFORM
	%error TARGET_PLATFORM need to be defined
endif

ifndef BUILD_CONFIGURATION
	%error BUILD_CONFIGURATION need to be defined
endif

###################################################

OUTPUT_NAME = libtiff
TIFF_SRC_PATH = tiff-4.0.3


include ../../build_config/make_config_$(TARGET_PLATFORM).mk


#from original makefile

#OBJ_SYSDEP_MODULE = tif_unix.obj
OBJ_SYSDEP_MODULE = tif_win32.obj

LIBOBJECTS	= \
	tif_aux.obj \
	tif_close.obj \
	tif_codec.obj \
	tif_color.obj \
	tif_compress.obj \
	tif_dir.obj \
	tif_dirinfo.obj \
	tif_dirread.obj \
	tif_dirwrite.obj \
	tif_dumpmode.obj \
	tif_error.obj \
	tif_extension.obj \
	tif_fax3.obj \
	tif_fax3sm.obj \
	tif_getimage.obj \
	tif_jbig.obj \
	tif_jpeg.obj \
	tif_jpeg_12.obj \
	tif_ojpeg.obj \
	tif_flush.obj \
	tif_luv.obj \
	tif_lzw.obj \
	tif_next.obj \
	tif_open.obj \
	tif_packbits.obj \
	tif_pixarlog.obj \
	tif_predict.obj \
	tif_print.obj \
	tif_read.obj \
	tif_stream.obj \
	tif_swab.obj \
	tif_strip.obj \
	tif_thunder.obj \
	tif_tile.obj \
	tif_version.obj \
	tif_warning.obj \
	tif_write.obj \
	tif_zip.obj \
	$(OBJ_SYSDEP_MODULE)
# These objectfiles are included in libjpeg.lib
OBJ_LIST = $(LIBOBJECTS)


OBJS = $(addprefix $(OBJOUT_PATH)/,$(OBJ_LIST:.o=.obj))



.PHONY: 


$(TIFF_SRC_PATH)/libtiff/tif_config.h:	$(TIFF_SRC_PATH)/libtiff/tif_config.vc.h
	copyfile +src:src/libtiff/$(<) +dest:src/libtiff/$(@)


$(TIFF_SRC_PATH)/libtiff/tiffconf.h:	$(TIFF_SRC_PATH)/libtiff/tiffconf.vc.h
	copyfile +src:src/libtiff/$(<) +dest:src/libtiff/$(@)


$(OBJOUT_PATH)/%.obj: $(TIFF_SRC_PATH)/libtiff/%.c
	$(CC) -c $< $(CPPFLAGS) $(INCLUDS) $(DEFINES) -Fo$@ -Fa$(@:.obj=.asm)


$(OBJOUT_PATH)/%.obj: $(TIFF_SRC_PATH)/libtiff/%.cxx
	$(CC) -c $< $(CPPFLAGS) $(INCLUDS) $(DEFINES) -Fo$@ -Fa$(@:.obj=.asm)

	
validatepath:
	createpath $(OBJOUT_PATH)
	createpath $(BINOUT_PATH)
	createpath $(LIBOUT_PATH)

	

$(LIBOUT_PATH)/$(OUTPUT_NAME).lib: $(TIFF_SRC_PATH)/libtiff/tif_config.h $(TIFF_SRC_PATH)/libtiff/tiffconf.h $(OBJS)
	echo compile $(OUTPUT_NAME).....
	$(AR) $(ARFLAGS) -OUT:$@ $(OBJS)

	

build: validatepath $(LIBOUT_PATH)/$(OUTPUT_NAME).lib
	echo $(OUTPUT_NAME) done.....
	copyfile +src:src/libtiff/$(TIFF_SRC_PATH)/libtiff/*.h +dest:include/libtiff/ +Recursive:false

	


