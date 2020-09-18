

###################################################

ifndef TARGET_PLATFORM
	%error TARGET_PLATFORM need to be defined
endif

ifndef BUILD_CONFIGURATION
	%error BUILD_CONFIGURATION need to be defined
endif

###################################################

OUTPUT_NAME = lcms
LCMS_SRC_PATH = lcms2-2.7


include ../../build_config/make_config_$(TARGET_PLATFORM).mk


#from original makefile
LIBOBJECTS = cmscam02.c \
    cmscgats.c \
    cmscnvrt.c \
    cmserr.c \
    cmsgamma.c \
    cmsgmt.c \
    cmshalf.c \
    cmsintrp.c \
    cmsio0.c \
    cmsio1.c \
    cmslut.c \
    cmsmd5.c \
    cmsmtrx.c \
    cmsnamed.c \
    cmsopt.c \
    cmspack.c \
    cmspcs.c \
    cmsplugin.c \
    cmsps2.c \
    cmssamp.c \
    cmssm.c \
    cmstypes.c \
    cmsvirt.c \
    cmswtpnt.c \
    cmsxform.c \

	
OBJ_LIST = $(LIBOBJECTS)


OBJS = $(addprefix $(OBJOUT_PATH)/,$(OBJ_LIST:.c=.obj))

INCLUDS += -I$(LCMS_SRC_PATH)/include

.PHONY: 


$(OBJOUT_PATH)/%.obj: $(LCMS_SRC_PATH)/src/%.c
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
	copyfile +src:src/lcms/$(LCMS_SRC_PATH)/include/*.h +dest:include/lcms/ +Recursive:false

	


#echo $(DEFINES)
#echo $(OBJS)
#echo $(SRCS)

