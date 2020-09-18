

###################################################

ifndef TARGET_PLATFORM
	%error TARGET_PLATFORM need to be defined
endif

ifndef BUILD_CONFIGURATION
	%error BUILD_CONFIGURATION need to be defined
endif

###################################################

OUTPUT_NAME = tinyxml
TINYXML_SRC_PATH = src


include ../../build_config/make_config_$(TARGET_PLATFORM).mk


#from original makefile
OBJ_LIST = tinyxml2.o


OBJS = $(addprefix $(OBJOUT_PATH)/,$(OBJ_LIST:.o=.obj))
SRCS = $(addprefix $(TINYXML_SRC_PATH)/,$(OBJ_LIST:.o=.cpp))


.PHONY: build



	 
$(OBJOUT_PATH)/%.obj: $(TINYXML_SRC_PATH)/%.cpp
	$(CC) -c $< $(CPPFLAGS) $(INCLUDS) $(DEFINES) -Fo$@ -Fa$(@:.obj=.asm)


	
validatepath:
	createpath $(OBJOUT_PATH)
	createpath $(BINOUT_PATH)
	createpath $(LIBOUT_PATH)

	

$(LIBOUT_PATH)/$(OUTPUT_NAME).lib: $(OBJS)
	echo compile %OUTPUT_NAME%.....
	$(AR) $(ARFLAGS) -OUT:$@ $(OBJS)

	

build : validatepath $(LIBOUT_PATH)/$(OUTPUT_NAME).lib
	echo $(OUTPUT_NAME) done.....
	copyfile +src:$(TINYXML_SRC_PATH)/*.h +dest:include/tinyxml/ +Recursive:false

	


