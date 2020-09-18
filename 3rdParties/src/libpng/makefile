

###################################################

ifndef TARGET_PLATFORM
	%error TARGET_PLATFORM need to be defined
endif

ifndef BUILD_CONFIGURATION
	%error BUILD_CONFIGURATION need to be defined
endif

###################################################

OUTPUT_NAME = libpng
PNG_SRC_PATH = lpng1617


include ../../build_config/make_config_$(TARGET_PLATFORM).mk


#from original makefile
LIBOBJECTS	= \
	pngerror.c \
	pngget.c \
	pngmem.c \
	pngpread.c \
	pngread.c \
	pngrio.c \
	pngrtran.c \
	pngrutil.c \
	pngset.c \
	pngtrans.c \
	pngwio.c \
	pngwrite.c \
	pngwtran.c \
	pngwutil.c \
	
	
	
	
	
	
# These objectfiles are included in libjpeg.lib
OBJ_LIST = $(LIBOBJECTS)


OBJS = $(addprefix $(OBJOUT_PATH)/,$(OBJ_LIST:.c=.obj))

INCLUDS += -I../../include/zlib -I../../include/jpeg


.PHONY: 


$(PNG_SRC_PATH)/pnglibconf.h:	$(PNG_SRC_PATH)/scripts\pnglibconf.h.prebuilt
	copyfile +src:src/$(OUTPUT_NAME)/$(<) +dest:src/$(OUTPUT_NAME)/$(@)



$(OBJOUT_PATH)/%.obj: $(PNG_SRC_PATH)/%.c
	$(CC) -c $< $(CPPFLAGS) $(INCLUDS) $(DEFINES) -Fo$@ -Fa$(@:.obj=.asm)


	
validatepath:
	createpath $(OBJOUT_PATH)
	createpath $(BINOUT_PATH)
	createpath $(LIBOUT_PATH)

	

$(LIBOUT_PATH)/$(OUTPUT_NAME).lib: $(PNG_SRC_PATH)/pnglibconf.h $(OBJS)
	echo compile $(OUTPUT_NAME).....
	$(AR) $(ARFLAGS) -OUT:$@ $(OBJS)

	

build: validatepath $(LIBOUT_PATH)/$(OUTPUT_NAME).lib
	echo $(OUTPUT_NAME) done.....
	copyfile +src:src/libpng/$(PNG_SRC_PATH)/*.h +dest:include/libpng/ +Recursive:false

	


