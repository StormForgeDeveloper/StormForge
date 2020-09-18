


include_directories(
	./
	jasper/src/libjasper/include
)


configure_file(
	"jasper/src/libjasper/include/jasper/jas_config.h.in"
	"jasper/src/libjasper/include/jasper/jas_config.h"
)



set(SRC_FILES
    jasper/src/libjasper/base/jas_cm.c 
    jasper/src/libjasper/base/jas_debug.c 
    jasper/src/libjasper/base/jas_getopt.c 
    jasper/src/libjasper/base/jas_icc.c 
    jasper/src/libjasper/base/jas_iccdata.c 
    jasper/src/libjasper/base/jas_image.c 
    jasper/src/libjasper/base/jas_init.c 
    jasper/src/libjasper/base/jas_malloc.c 
    jasper/src/libjasper/base/jas_seq.c 
    jasper/src/libjasper/base/jas_string.c 
    jasper/src/libjasper/base/jas_tmr.c 
    jasper/src/libjasper/base/jas_tvp.c 
    jasper/src/libjasper/base/jas_version.c 
    jasper/src/libjasper/bmp/bmp_cod.c 
    jasper/src/libjasper/bmp/bmp_dec.c 
    jasper/src/libjasper/bmp/bmp_enc.c 
    jasper/src/libjasper/jp2/jp2_cod.c 
    jasper/src/libjasper/jp2/jp2_dec.c 
    jasper/src/libjasper/jp2/jp2_enc.c 
    jasper/src/libjasper/jpc/jpc_bs.c 
    jasper/src/libjasper/jpc/jpc_cs.c 
    jasper/src/libjasper/jpc/jpc_dec.c 
    jasper/src/libjasper/jpc/jpc_enc.c 
    jasper/src/libjasper/jpc/jpc_math.c 
    jasper/src/libjasper/jpc/jpc_mct.c 
    jasper/src/libjasper/jpc/jpc_mqcod.c 
    jasper/src/libjasper/jpc/jpc_mqdec.c 
    jasper/src/libjasper/jpc/jpc_mqenc.c 
    jasper/src/libjasper/jpc/jpc_qmfb.c 
    jasper/src/libjasper/jpc/jpc_t1cod.c 
    jasper/src/libjasper/jpc/jpc_t1dec.c 
    jasper/src/libjasper/jpc/jpc_t1enc.c 
    jasper/src/libjasper/jpc/jpc_t2cod.c 
    jasper/src/libjasper/jpc/jpc_t2dec.c 
    jasper/src/libjasper/jpc/jpc_t2enc.c 
    jasper/src/libjasper/jpc/jpc_tagtree.c 
    jasper/src/libjasper/jpc/jpc_tsfb.c 
    jasper/src/libjasper/jpc/jpc_util.c 
    jasper/src/libjasper/jpg/jpg_dec.c 
    jasper/src/libjasper/jpg/jpg_dummy.c 
    jasper/src/libjasper/jpg/jpg_enc.c 
    jasper/src/libjasper/jpg/jpg_val.c 
    jasper/src/libjasper/mif/mif_cod.c 
    jasper/src/libjasper/pgx/pgx_cod.c 
    jasper/src/libjasper/pgx/pgx_dec.c 
    jasper/src/libjasper/pgx/pgx_enc.c 
    jasper/src/libjasper/pnm/pnm_cod.c 
    jasper/src/libjasper/pnm/pnm_dec.c 
    jasper/src/libjasper/pnm/pnm_enc.c 
    jasper/src/libjasper/ras/ras_cod.c 
    jasper/src/libjasper/ras/ras_dec.c 
    jasper/src/libjasper/ras/ras_enc.c 
)



add_library(jasper ${SRC_FILES})


install (TARGETS jasper
         ARCHIVE DESTINATION lib COMPONENT SF3rdParties
         LIBRARY DESTINATION lib COMPONENT SF3rdParties
         RUNTIME DESTINATION bin COMPONENT SF3rdParties)


