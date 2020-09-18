

###################################################

ifndef TARGET_PLATFORM
	%error TARGET_PLATFORM need to be defined
endif

ifndef BUILD_CONFIGURATION
	%error BUILD_CONFIGURATION need to be defined
endif

###################################################

OUTPUT_NAME = libmng
MNG_SRC_PATH = libmng-2.0.3


include ../../build_config/make_config_$(TARGET_PLATFORM).mk


#from original makefile

O = .o

OBJS1 = libmng_callback_xs$(O) libmng_chunk_io$(O) libmng_chunk_prc$(O) libmng_chunk_descr$(O)
OBJS2 = libmng_chunk_xs$(O) libmng_cms$(O) libmng_display$(O) libmng_dither$(O)
OBJS3 = libmng_error$(O) libmng_filter$(O) libmng_hlapi$(O) libmng_jpeg$(O)
OBJS4 = libmng_object_prc$(O) libmng_pixels$(O) libmng_prop_xs$(O)
OBJS5 = libmng_read$(O) libmng_trace$(O) libmng_write$(O) libmng_zlib$(O)

LIBOBJECTS	= $(OBJS1) $(OBJS2) $(OBJS3) $(OBJS4) $(OBJS5)


OBJ_LIST = $(LIBOBJECTS)


OBJS = $(addprefix $(OBJOUT_PATH)/,$(OBJ_LIST:.o=.obj))

INCLUDS += -I../../include/zlib -I../../include/jpeg -I../../include/lcms

.PHONY: 


$(MNG_SRC_PATH)/config.h:	config_win/config.h
	copyfile +src:src/libmng/$(<) +dest:src/libmng/$(@)


$(OBJOUT_PATH)/%.obj: $(MNG_SRC_PATH)/%.c
	$(CC) -c $< $(CPPFLAGS) $(INCLUDS) $(DEFINES) -Fo$@ -Fa$(@:.obj=.asm)


$(OBJOUT_PATH)/%.obj: $(MNG_SRC_PATH)/libmng/%.cxx
	$(CC) -c $< $(CPPFLAGS) $(INCLUDS) $(DEFINES) -Fo$@ -Fa$(@:.obj=.asm)

	
validatepath:
	createpath $(OBJOUT_PATH)
	createpath $(BINOUT_PATH)
	createpath $(LIBOUT_PATH)

	

$(LIBOUT_PATH)/$(OUTPUT_NAME).lib: $(MNG_SRC_PATH)/config.h $(OBJS)
	echo compile $(OUTPUT_NAME).....
	$(AR) $(ARFLAGS) -OUT:$@ $(OBJS)

	

build: validatepath $(LIBOUT_PATH)/$(OUTPUT_NAME).lib
	echo $(OUTPUT_NAME) done.....
	copyfile +src:src/libmng/$(MNG_SRC_PATH)/*.h +dest:include/libmng/ +Recursive:false

	


