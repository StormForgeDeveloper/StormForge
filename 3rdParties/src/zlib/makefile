

###################################################

ifndef TARGET_PLATFORM
	%error TARGET_PLATFORM need to be defined
endif

ifndef BUILD_CONFIGURATION
	%error BUILD_CONFIGURATION need to be defined
endif

###################################################

OUTPUT_NAME = zlib
ZLIB_SRC_PATH = zlib-1.2.8


include ../../build_config/make_config_$(TARGET_PLATFORM).mk


#from original makefile
OBJZ = adler32.o crc32.o deflate.o infback.o inffast.o inflate.o inftrees.o trees.o zutil.o
OBJG = compress.o uncompr.o gzclose.o gzlib.o gzread.o gzwrite.o
OBJ_LIST = $(OBJZ) $(OBJG)


OBJS = $(addprefix $(OBJOUT_PATH)/,$(OBJ_LIST:.o=.obj))


.PHONY: 


$(OBJOUT_PATH)/%.obj: $(ZLIB_SRC_PATH)/%.c
	$(CC) -c $< $(CPPFLAGS) $(INCLUDS) $(DEFINES) -Fo$@ -Fa$(@:.obj=.asm)


	
validatepath:
	createpath $(OBJOUT_PATH)
	createpath $(BINOUT_PATH)
	createpath $(LIBOUT_PATH)

	

$(LIBOUT_PATH)/$(OUTPUT_NAME).lib: $(OBJS)
	echo compile $(OUTPUT_NAME).....
	$(AR) $(ARFLAGS) -OUT:$@ $(OBJS)

	

build: validatepath $(LIBOUT_PATH)/$(OUTPUT_NAME).lib
	echo $(OUTPUT_NAME) done.....
	copyfile +src:src/zlib/$(ZLIB_SRC_PATH)/*.h +dest:include/zlib/ +Recursive:false

	


