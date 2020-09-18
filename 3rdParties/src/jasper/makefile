

###################################################

ifndef TARGET_PLATFORM
	%error TARGET_PLATFORM need to be defined
endif

ifndef BUILD_CONFIGURATION
	%error BUILD_CONFIGURATION need to be defined
endif

###################################################

OUTPUT_NAME = libjasper
JASPER_SRC_PATH = jasper-1.900.1/src/libjasper


include ../../build_config/make_config_$(TARGET_PLATFORM).mk


#from original makefile

LIBOBJECTS	= \
	bmp/bmp_cod.c \
	bmp/bmp_dec.c \
	bmp/bmp_enc.c \
	base/jas_cm.c \
	base/jas_debug.c \
	base/jas_getopt.c \
	base/jas_icc.c \
	base/jas_iccdata.c \
	base/jas_image.c \
	base/jas_init.c \
	base/jas_malloc.c \
	base/jas_seq.c \
	base/jas_stream.c \
	base/jas_string.c \
	base/jas_tmr.c \
	base/jas_tvp.c \
	base/jas_version.c \
	jp2/jp2_cod.c \
	jp2/jp2_dec.c \
	jp2/jp2_enc.c \
	jpc/jpc_bs.c \
	jpc/jpc_cs.c \
	jpc/jpc_dec.c \
	jpc/jpc_enc.c \
	jpc/jpc_math.c \
	jpc/jpc_mct.c \
	jpc/jpc_mqcod.c \
	jpc/jpc_mqdec.c \
	jpc/jpc_mqenc.c \
	jpc/jpc_qmfb.c \
	jpc/jpc_t1cod.c \
	jpc/jpc_t1dec.c \
	jpc/jpc_t1enc.c \
	jpc/jpc_t2cod.c \
	jpc/jpc_t2dec.c \
	jpc/jpc_t2enc.c \
	jpc/jpc_tagtree.c \
	jpc/jpc_tsfb.c \
	jpc/jpc_util.c \
	jpg/jpg_dummy.c \
	jpg/jpg_val.c \
	mif/mif_cod.c \
	pgx/pgx_cod.c \
	pgx/pgx_dec.c \
	pgx/pgx_enc.c \
	pnm/pnm_cod.c \
	pnm/pnm_dec.c \
	pnm/pnm_enc.c \
	ras/ras_cod.c \
	ras/ras_dec.c \
	ras/ras_enc.c \

# These objectfiles are included in libjpeg.lib
OBJ_LIST = $(LIBOBJECTS)


OBJS = $(addprefix $(OBJOUT_PATH)/,$(OBJ_LIST:.c=.obj))

INCLUDS += -I$(JASPER_SRC_PATH)/include 


.PHONY: 

define buid_src
	createpath $(dir $(2))
	$(CC) -c $(1) $(CPPFLAGS) $(INCLUDS) $(DEFINES) -Fo$(2) -Fa$(2:.obj=.asm)
	
endef



$(OBJOUT_PATH)/base/%.obj: $(JASPER_SRC_PATH)/base/%.c
	$(call buid_src,$(<),$(@))


$(OBJOUT_PATH)/bmp/%.obj: $(JASPER_SRC_PATH)/bmp/%.c
	$(call buid_src,$(<),$(@))


$(OBJOUT_PATH)/jp2/%.obj: $(JASPER_SRC_PATH)/jp2/%.c
	$(call buid_src,$(<),$(@))


$(OBJOUT_PATH)/jpc/%.obj: $(JASPER_SRC_PATH)/jpc/%.c
	$(call buid_src,$(<),$(@))


$(OBJOUT_PATH)/jpg/%.obj: $(JASPER_SRC_PATH)/jpg/%.c
	$(call buid_src,$(<),$(@))


$(OBJOUT_PATH)/mig/%.obj: $(JASPER_SRC_PATH)/mig/%.c
	$(call buid_src,$(<),$(@))


$(OBJOUT_PATH)/pgx/%.obj: $(JASPER_SRC_PATH)/pgx/%.c
	$(call buid_src,$(<),$(@))


$(OBJOUT_PATH)/pnm/%.obj: $(JASPER_SRC_PATH)/pnm/%.c
	$(call buid_src,$(<),$(@))


$(OBJOUT_PATH)/ras/%.obj: $(JASPER_SRC_PATH)/ras/%.c
	$(call buid_src,$(<),$(@))


$(OBJOUT_PATH)/mif/%.obj: $(JASPER_SRC_PATH)/mif/%.c
	$(call buid_src,$(<),$(@))


$(JASPER_SRC_PATH)/include/jasper/jas_config.h: config_win/src/libjasper/include/jasper/jas_config.h
	copyfile +src:src/jasper/config_win/src/libjasper/*.h +dest:src/jasper/$(JASPER_SRC_PATH) +Recursive:true

	
	
validatepath:
	createpath $(OBJOUT_PATH)
	createpath $(BINOUT_PATH)
	createpath $(LIBOUT_PATH)

	

$(LIBOUT_PATH)/$(OUTPUT_NAME).lib: $(OBJS)
	echo compile $(OUTPUT_NAME).....
	$(AR) $(ARFLAGS) -OUT:$@ $(OBJS)

	

build: validatepath $(JASPER_SRC_PATH)/include/jasper/jas_config.h  $(LIBOUT_PATH)/$(OUTPUT_NAME).lib
	echo $(OUTPUT_NAME) done.....
	copyfile +src:src/jasper/$(JASPER_SRC_PATH)/include/*.h +dest:include/ +Recursive:true

	


