

###################################################

ifndef TARGET_PLATFORM
	%error TARGET_PLATFORM need to be defined
endif

ifndef BUILD_CONFIGURATION
	%error BUILD_CONFIGURATION need to be defined
endif

###################################################

OUTPUT_NAME = libxml
LIBXML_SRC_PATH = libxml2


include ../../build_config/make_config_$(TARGET_PLATFORM).mk


#from original makefile
SRC_LIST = c14n.c catalog.c chvalid.c debugXML.c dict.c DOCBparser.c encoding.c entities.c error.c globals.c hash.c HTMLparser.c HTMLtree.c legacy.c list.c \
	nanoftp.c nanohttp.c parser.c parserInternals.c pattern.c relaxng.c SAX.c SAX2.c \
	schematron.c threads.c tree.c uri.c valid.c xinclude.c xlink.c xmlcatalog.c xmlIO.c xmlmemory.c xmlmodule.c xmlreader.c xmlregexp.c xmlsave.c xmlschemas.c \
	xmlschemastypes.c xmlstring.c xmlunicode.c xmlwriter.c xpath.c xpointer.c \

OBJ_LIST = $(addprefix $(OBJOUT_PATH)/,$(SRC_LIST:.c=.obj))

INCLUDS += -I$(LIBXML_SRC_PATH)/include -I$(LIBXML_SRC_PATH) -I../../include/libiconv


.PHONY: validatepath build


$(OBJOUT_PATH)/%.obj: $(LIBXML_SRC_PATH)/%.c
	$(CC) -c $< $(CPPFLAGS) $(INCLUDS) $(DEFINES) -Fo$@ -Fa$(@:.obj=.asm)


	
validatepath:
	createpath $(OBJOUT_PATH)
	createpath $(BINOUT_PATH)
	createpath $(LIBOUT_PATH)



$(LIBOUT_PATH)/$(OUTPUT_NAME).lib: $(OBJ_LIST)
	echo compile $(OUTPUT_NAME).....
	$(AR) $(ARFLAGS) -OUT:$@ $(OBJ_LIST)

	

build: validatepath $(LIBOUT_PATH)/$(OUTPUT_NAME).lib
	echo $(OUTPUT_NAME) done.....
	copyfile +src:src/libxml/$(LIBXML_SRC_PATH)/include/libxml/*.h +dest:include/libxml/ +Recursive:false

	


