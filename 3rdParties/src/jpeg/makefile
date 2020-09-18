

###################################################

ifndef TARGET_PLATFORM
	%error TARGET_PLATFORM need to be defined
endif

ifndef BUILD_CONFIGURATION
	%error BUILD_CONFIGURATION need to be defined
endif

###################################################

OUTPUT_NAME = libjpeg
JPEG_SRC_PATH = jpeg-9a


include ../../build_config/make_config_$(TARGET_PLATFORM).mk


#from original makefile
# library object files common to compression and decompression
COMOBJECTS= jaricom.obj jcomapi.obj jutils.obj jerror.obj jmemmgr.obj $(SYSDEPMEM)
# compression library object files
CLIBOBJECTS= jcapimin.obj jcapistd.obj jcarith.obj jctrans.obj jcparam.obj \
        jdatadst.obj jcinit.obj jcmaster.obj jcmarker.obj jcmainct.obj \
        jcprepct.obj jccoefct.obj jccolor.obj jcsample.obj jchuff.obj \
        jcdctmgr.obj jfdctfst.obj jfdctflt.obj jfdctint.obj
# decompression library object files
DLIBOBJECTS= jdapimin.obj jdapistd.obj jdarith.obj jdtrans.obj jdatasrc.obj \
        jdmaster.obj jdinput.obj jdmarker.obj jdhuff.obj jdmainct.obj \
        jdcoefct.obj jdpostct.obj jddctmgr.obj jidctfst.obj jidctflt.obj \
        jidctint.obj jdsample.obj jdcolor.obj jquant1.obj jquant2.obj \
        jdmerge.obj
# These objectfiles are included in libjpeg.lib
LIBOBJECTS= $(CLIBOBJECTS) $(DLIBOBJECTS) $(COMOBJECTS)
OBJ_LIST = $(LIBOBJECTS)


OBJS = $(addprefix $(OBJOUT_PATH)/,$(OBJ_LIST:.o=.obj))


.PHONY: 


$(JPEG_SRC_PATH)/jconfig.h :
	copyfile +src:src/jpeg/$(JPEG_SRC_PATH)/jconfig.vc +dest:src/jpeg/$(@)


$(OBJOUT_PATH)/%.obj: $(JPEG_SRC_PATH)/%.c
	$(CC) -c $< $(CPPFLAGS) $(INCLUDS) $(DEFINES) -Fo$@ -Fa$(@:.obj=.asm)


	
validatepath:
	createpath $(OBJOUT_PATH)
	createpath $(BINOUT_PATH)
	createpath $(LIBOUT_PATH)

	

$(LIBOUT_PATH)/$(OUTPUT_NAME).lib: $(JPEG_SRC_PATH)/jconfig.h $(OBJS)
	echo compile $(OUTPUT_NAME).....
	$(AR) $(ARFLAGS) -OUT:$@ $(OBJS)

	

build: validatepath $(LIBOUT_PATH)/$(OUTPUT_NAME).lib
	echo $(OUTPUT_NAME) done.....
	copyfile +src:src/jpeg/$(JPEG_SRC_PATH)/*.h +dest:include/jpeg/ +Recursive:false

	


#echo $(DEFINES)
#echo $(OBJS)
#echo $(SRCS)

