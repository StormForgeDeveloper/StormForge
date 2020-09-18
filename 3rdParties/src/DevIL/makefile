

###################################################

ifndef TARGET_PLATFORM
	%error TARGET_PLATFORM need to be defined
endif

ifndef BUILD_CONFIGURATION
	%error BUILD_CONFIGURATION need to be defined
endif

###################################################

OUTPUT_NAME = devil
LIB_SRC_PATH = devil-1.7.8


include ../../build_config/make_config_$(TARGET_PLATFORM).mk


#from original makefile
LIBOBJECTS_IL = src-IL/src/altivec_common.c \
    src-IL/src/altivec_typeconversion.c \
    src-IL/src/il_alloc.c \
    src-IL/src/il_bits.c \
    src-IL/src/il_convbuff.c \
    src-IL/src/il_convert.c \
    src-IL/src/il_devil.c \
    src-IL/src/il_endian.c \
    src-IL/src/il_error.c \
    src-IL/src/il_fastconv.c \
    src-IL/src/il_files.c \
    src-IL/src/il_header.c \
    src-IL/src/il_icns.c \
    src-IL/src/il_icon.c \
    src-IL/src/il_internal.c \
    src-IL/src/il_io.c \
    src-IL/src/il_manip.c \
    src-IL/src/il_neuquant.c \
    src-IL/src/il_nvidia.cpp \
    src-IL/src/il_profiles.c \
    src-IL/src/il_quantizer.c \
    src-IL/src/il_register.c \
    src-IL/src/il_rle.c \
    src-IL/src/il_size.c \
    src-IL/src/il_squish.cpp \
    src-IL/src/il_stack.c \
    src-IL/src/il_states.c \
    src-IL/src/il_utility.c \
    src-IL/src/il_blp.c \
    src-IL/src/il_bmp.c \
    src-IL/src/il_cut.c \
    src-IL/src/il_dcx.c \
    src-IL/src/il_dds-save.c \
    src-IL/src/il_dds.c \
    src-IL/src/il_dicom.c \
    src-IL/src/il_doom.c \
    src-IL/src/il_dpx.c \
    src-IL/src/il_exr.cpp \
    src-IL/src/il_fits.c \
    src-IL/src/il_ftx.c \
    src-IL/src/il_gif.c \
    src-IL/src/il_hdr.c \
    src-IL/src/il_iff.c \
    src-IL/src/il_ilbm.c \
    src-IL/src/il_iwi.c \
    src-IL/src/il_jp2.c \
    src-IL/src/il_jpeg.c \
    src-IL/src/il_lif.c \
    src-IL/src/il_mdl.c \
    src-IL/src/il_mng.c \
    src-IL/src/il_mp3.c \
    src-IL/src/il_pal.c \
    src-IL/src/il_pcd.c \
    src-IL/src/il_pcx.c \
    src-IL/src/il_pic.c \
    src-IL/src/il_pix.c \
    src-IL/src/il_png.c \
    src-IL/src/il_pnm.c \
    src-IL/src/il_psd.c \
    src-IL/src/il_psp.c \
    src-IL/src/il_pxr.c \
    src-IL/src/il_raw.c \
    src-IL/src/il_rawdata.c \
    src-IL/src/il_rot.c \
    src-IL/src/il_sgi.c \
    src-IL/src/il_sun.c \
    src-IL/src/il_targa.c \
    src-IL/src/il_texture.c \
    src-IL/src/il_tiff.c \
    src-IL/src/il_tpl.c \
    src-IL/src/il_utx.cpp \
    src-IL/src/il_vtf.c \
    src-IL/src/il_wal.c \
    src-IL/src/il_wbmp.c \
    src-IL/src/il_wdp.c \
    src-IL/src/il_xpm.c \

 #   src-IL/src/il_main.c \


LIBOBJECTS_ILU = src-ILU/src/ilu_error.c \
	src-ILU/src/ilu_filter.c \
	src-ILU/src/ilu_filter_rcg.c \
	src-ILU/src/ilu_internal.c \
	src-ILU/src/ilu_manip.c \
	src-ILU/src/ilu_mipmap.c \
	src-ILU/src/ilu_noise.c \
	src-ILU/src/ilu_region.c \
	src-ILU/src/ilu_rotate.c \
	src-ILU/src/ilu_scale.c \
	src-ILU/src/ilu_scale2d.c \
	src-ILU/src/ilu_scale3d.c \
	src-ILU/src/ilu_states.c \
	src-ILU/src/ilu_utilities.c \

	#src-ILU/src/ilu_main.c \

LIBOBJECTS = $(LIBOBJECTS_IL) $(LIBOBJECTS_ILU)


OBJ_LIST = $(LIBOBJECTS)

OBJS_TEMP = $(OBJ_LIST:.cpp=.obj)
OBJS = $(addprefix $(OBJOUT_PATH)/,$(OBJS_TEMP:.c=.obj))


DEFINES += -DFT2_BUILD_LIBRARY 
INCLUDS += -I$(LIB_SRC_PATH)/include -I$(LIB_SRC_PATH)/src-IL/include -I$(LIB_SRC_PATH)/src-ILU/include -I../../include -I../../include/libpng -I../../include/lcms -I../../include/jpeg  -I../../include/libmng  -I../../include/zlib  -I../../include/libtiff


.PHONY: 



define buid_src
	createpath $(dir $(2))
	$(CC) -c $(1) $(CPPFLAGS) $(INCLUDS) $(DEFINES) -Fo$(2) -Fa$(2:.obj=.asm)
	
endef



$(OBJOUT_PATH)/src-IL/src/%.obj: $(LIB_SRC_PATH)/src-IL/src/%.cpp
	$(call buid_src,$(<),$(@))


$(OBJOUT_PATH)/src-IL/src/%.obj: $(LIB_SRC_PATH)/src-IL/src/%.c
	$(call buid_src,$(<),$(@))


$(OBJOUT_PATH)/src-ILU/src/%.obj: $(LIB_SRC_PATH)/src-ILU/src/%.c
	$(call buid_src,$(<),$(@))




$(LIB_SRC_PATH)/include/IL/config.h:
	copyfile +src:src/devil/config_win/*.h +dest:src/devil/$(LIB_SRC_PATH)/ +Recursive:true


validatepath:
	createpath $(OBJOUT_PATH)
	createpath $(BINOUT_PATH)
	createpath $(LIBOUT_PATH)



$(LIBOUT_PATH)/$(OUTPUT_NAME).lib: $(LIB_SRC_PATH)/include/IL/config.h $(OBJS)
	echo compile $(OUTPUT_NAME).....
	$(AR) $(ARFLAGS) -OUT:$@ $(OBJS)



build: validatepath $(LIBOUT_PATH)/$(OUTPUT_NAME).lib
	echo $(OUTPUT_NAME) done.....
	copyfile +src:src/DevIL/$(LIB_SRC_PATH)/include/*.h +dest:include/DevIL/ +Recursive:false




