

###################################################

ifndef TARGET_PLATFORM
	%error TARGET_PLATFORM need to be defined
endif

ifndef BUILD_CONFIGURATION
	%error BUILD_CONFIGURATION need to be defined
endif

###################################################

OUTPUT_NAME = freetype
FREETYPE_SRC_PATH = freetype-2.5.5


include ../../build_config/make_config_$(TARGET_PLATFORM).mk


#from original makefile
LIBOBJECTS = src/autofit/autofit.c \
    src/bdf/bdf.c \
    src/cff/cff.c \
    src/base/ftbase.c \
    src/base/ftbitmap.c \
    src/base/ftfstype.c \
    src/base/ftgasp.c \
    src/base/ftglyph.c \
    src/base/ftinit.c \
    src/base/ftstroke.c \
    src/base/ftsystem.c \
    src/base/ftbbox.c \
    src/base/ftmm.c \
	src/base/ftpfr.c \
	src/base/ftsynth.c \
	src/base/fttype1.c \
	src/base/ftwinfnt.c \
	src/base/ftxf86.c \
	src/base/ftlcdfil.c \
    src/base/ftgxval.c \
    src/base/ftotval.c \
    src/base/ftpatent.c \
    src/cache/ftcache.c \
    src/gzip/ftgzip.c \
    src/lzw/ftlzw.c \
    src/smooth/smooth.c \
    src/pcf/pcf.c \
    src/pfr/pfr.c \
    src/psaux/psaux.c \
    src/pshinter/pshinter.c \
	src/psnames/psnames.c \
	src/raster/raster.c \
	src/sfnt/sfnt.c \
	src/truetype/truetype.c \
	src/type1/type1.c \
	src/cid/type1cid.c \
	src/type42/type42.c \
	src/winfonts/winfnt.c \
    builds/windows/ftdebug.c \


OBJ_LIST = $(LIBOBJECTS)


OBJS = $(addprefix $(OBJOUT_PATH)/,$(OBJ_LIST:.c=.obj))


DEFINES += -DFT2_BUILD_LIBRARY 
INCLUDS += -I$(FREETYPE_SRC_PATH)/include 


.PHONY: 



define buid_src
	createpath $(dir $(2))
	$(CC) -c $(1) $(CPPFLAGS) $(INCLUDS) $(DEFINES) -Fo$(2) -Fa$(2:.obj=.asm)
	
endef


	
$(OBJOUT_PATH)/builds/windows/%.obj: $(FREETYPE_SRC_PATH)/builds/windows/%.c
	$(call buid_src,$(<),$(@))

$(OBJOUT_PATH)/src/autofit/%.obj: $(FREETYPE_SRC_PATH)/src/autofit/%.c
	$(call buid_src,$(<),$(@))

	
$(OBJOUT_PATH)/src/bdf/%.obj: $(FREETYPE_SRC_PATH)/src/bdf/%.c
	$(call buid_src,$(<),$(@))

	
$(OBJOUT_PATH)/src/cff/%.obj: $(FREETYPE_SRC_PATH)/src/cff/%.c
	$(call buid_src,$(<),$(@))

	
$(OBJOUT_PATH)/src/base/%.obj: $(FREETYPE_SRC_PATH)/src/base/%.c
	$(call buid_src,$(<),$(@))

	
$(OBJOUT_PATH)/src/gzip/%.obj: $(FREETYPE_SRC_PATH)/src/gzip/%.c
	$(call buid_src,$(<),$(@))

	
$(OBJOUT_PATH)/src/lzw/%.obj: $(FREETYPE_SRC_PATH)/src/lzw/%.c
	$(call buid_src,$(<),$(@))

	
$(OBJOUT_PATH)/src/smooth/%.obj: $(FREETYPE_SRC_PATH)/src/smooth/%.c
	$(call buid_src,$(<),$(@))

	
$(OBJOUT_PATH)/src/pcf/%.obj: $(FREETYPE_SRC_PATH)/src/pcf/%.c
	$(call buid_src,$(<),$(@))

	
$(OBJOUT_PATH)/src/pfr/%.obj: $(FREETYPE_SRC_PATH)/src/pfr/%.c
	$(call buid_src,$(<),$(@))

	
$(OBJOUT_PATH)/src/psaux/%.obj: $(FREETYPE_SRC_PATH)/src/psaux/%.c
	$(call buid_src,$(<),$(@))

	
$(OBJOUT_PATH)/src/pshinter/%.obj: $(FREETYPE_SRC_PATH)/src/pshinter/%.c
	$(call buid_src,$(<),$(@))

	
$(OBJOUT_PATH)/src/psnames/%.obj: $(FREETYPE_SRC_PATH)/src/psnames/%.c
	$(call buid_src,$(<),$(@))

	
$(OBJOUT_PATH)/src/raster/%.obj: $(FREETYPE_SRC_PATH)/src/raster/%.c
	$(call buid_src,$(<),$(@))

	
$(OBJOUT_PATH)/src/sfnt/%.obj: $(FREETYPE_SRC_PATH)/src/sfnt/%.c
	$(call buid_src,$(<),$(@))

	
$(OBJOUT_PATH)/src/truetype/%.obj: $(FREETYPE_SRC_PATH)/src/truetype/%.c
	$(call buid_src,$(<),$(@))

	
$(OBJOUT_PATH)/src/type1/%.obj: $(FREETYPE_SRC_PATH)/src/type1/%.c
	$(call buid_src,$(<),$(@))

	
$(OBJOUT_PATH)/src/cid/%.obj: $(FREETYPE_SRC_PATH)/src/cid/%.c
	$(call buid_src,$(<),$(@))

	
$(OBJOUT_PATH)/src/type42/%.obj: $(FREETYPE_SRC_PATH)/src/type42/%.c
	$(call buid_src,$(<),$(@))

	
$(OBJOUT_PATH)/src/winfonts/%.obj: $(FREETYPE_SRC_PATH)/src/winfonts/%.c
	$(call buid_src,$(<),$(@))

	
$(OBJOUT_PATH)/src/cache/%.obj: $(FREETYPE_SRC_PATH)/src/cache/%.c
	$(call buid_src,$(<),$(@))

	


	
validatepath:
	createpath $(OBJOUT_PATH)
	createpath $(BINOUT_PATH)
	createpath $(LIBOUT_PATH)

	

$(LIBOUT_PATH)/$(OUTPUT_NAME).lib: $(OBJS)
	echo compile $(OUTPUT_NAME).....
	$(AR) $(ARFLAGS) -OUT:$@ $(OBJS)

	

build: validatepath $(LIBOUT_PATH)/$(OUTPUT_NAME).lib
	echo $(OUTPUT_NAME) done.....
	copyfile +src:src/freetype/$(FREETYPE_SRC_PATH)/include/*.h +dest:include/freetype/ +Recursive:false

	


