



include_directories(AFTER 
	xz-5.2.5/src/common/
	xz-5.2.5/src/liblzma/common/
	xz-5.2.5/src/liblzma/api/
	xz-5.2.5/src/liblzma/check/
	xz-5.2.5/src/liblzma/lzma/
	xz-5.2.5/src/liblzma/lz/
	xz-5.2.5/src/liblzma/simple
	xz-5.2.5/src/liblzma/delta
	xz-5.2.5/src/liblzma/rangecoder
	./
)


add_definitions(-DHAVE_CONFIG_H=1)


set(SRC_FILES
	xz-5.2.5/src/common/tuklib_cpucores.c
	xz-5.2.5/src/common/tuklib_physmem.c
	xz-5.2.5/src/liblzma/check/check.c
	xz-5.2.5/src/liblzma/check/crc32_fast.c
	xz-5.2.5/src/liblzma/check/crc32_table.c
	xz-5.2.5/src/liblzma/check/crc64_fast.c
	xz-5.2.5/src/liblzma/check/crc64_table.c
	xz-5.2.5/src/liblzma/check/sha256.c
	xz-5.2.5/src/liblzma/common/alone_decoder.c
	xz-5.2.5/src/liblzma/common/alone_encoder.c
	xz-5.2.5/src/liblzma/common/auto_decoder.c
	xz-5.2.5/src/liblzma/common/block_buffer_decoder.c
	xz-5.2.5/src/liblzma/common/block_buffer_encoder.c
	xz-5.2.5/src/liblzma/common/block_decoder.c
	xz-5.2.5/src/liblzma/common/block_encoder.c
	xz-5.2.5/src/liblzma/common/block_header_decoder.c
	xz-5.2.5/src/liblzma/common/block_header_encoder.c
	xz-5.2.5/src/liblzma/common/block_util.c
	xz-5.2.5/src/liblzma/common/common.c
	xz-5.2.5/src/liblzma/common/easy_buffer_encoder.c
	xz-5.2.5/src/liblzma/common/easy_decoder_memusage.c
	xz-5.2.5/src/liblzma/common/easy_encoder.c
	xz-5.2.5/src/liblzma/common/easy_encoder_memusage.c
	xz-5.2.5/src/liblzma/common/easy_preset.c
	xz-5.2.5/src/liblzma/common/filter_buffer_decoder.c
	xz-5.2.5/src/liblzma/common/filter_buffer_encoder.c
	xz-5.2.5/src/liblzma/common/filter_common.c
	xz-5.2.5/src/liblzma/common/filter_decoder.c
	xz-5.2.5/src/liblzma/common/filter_encoder.c
	xz-5.2.5/src/liblzma/common/filter_flags_decoder.c
	xz-5.2.5/src/liblzma/common/filter_flags_encoder.c
	xz-5.2.5/src/liblzma/common/hardware_cputhreads.c
	xz-5.2.5/src/liblzma/common/hardware_physmem.c
	xz-5.2.5/src/liblzma/common/index.c
	xz-5.2.5/src/liblzma/common/index_decoder.c
	xz-5.2.5/src/liblzma/common/index_encoder.c
	xz-5.2.5/src/liblzma/common/index_hash.c
	xz-5.2.5/src/liblzma/common/outqueue.c
	xz-5.2.5/src/liblzma/common/stream_buffer_decoder.c
	xz-5.2.5/src/liblzma/common/stream_buffer_encoder.c
	xz-5.2.5/src/liblzma/common/stream_decoder.c
	xz-5.2.5/src/liblzma/common/stream_encoder.c
	xz-5.2.5/src/liblzma/common/stream_encoder_mt.c
	xz-5.2.5/src/liblzma/common/stream_flags_common.c
	xz-5.2.5/src/liblzma/common/stream_flags_decoder.c
	xz-5.2.5/src/liblzma/common/stream_flags_encoder.c
	xz-5.2.5/src/liblzma/common/vli_decoder.c
	xz-5.2.5/src/liblzma/common/vli_encoder.c
	xz-5.2.5/src/liblzma/common/vli_size.c
	xz-5.2.5/src/liblzma/delta/delta_common.c
	xz-5.2.5/src/liblzma/delta/delta_decoder.c
	xz-5.2.5/src/liblzma/delta/delta_encoder.c
	xz-5.2.5/src/liblzma/lzma/fastpos_table.c
	xz-5.2.5/src/liblzma/lzma/lzma2_decoder.c
	xz-5.2.5/src/liblzma/lzma/lzma2_encoder.c
	xz-5.2.5/src/liblzma/lzma/lzma_decoder.c
	xz-5.2.5/src/liblzma/lzma/lzma_encoder.c
	xz-5.2.5/src/liblzma/lzma/lzma_encoder_optimum_fast.c
	xz-5.2.5/src/liblzma/lzma/lzma_encoder_optimum_normal.c
	xz-5.2.5/src/liblzma/lzma/lzma_encoder_presets.c
	xz-5.2.5/src/liblzma/lz/lz_decoder.c
	xz-5.2.5/src/liblzma/lz/lz_encoder.c
	xz-5.2.5/src/liblzma/lz/lz_encoder_mf.c
	xz-5.2.5/src/liblzma/rangecoder/price_table.c
	xz-5.2.5/src/liblzma/simple/arm.c
	xz-5.2.5/src/liblzma/simple/armthumb.c
	xz-5.2.5/src/liblzma/simple/ia64.c
	xz-5.2.5/src/liblzma/simple/powerpc.c
	xz-5.2.5/src/liblzma/simple/simple_coder.c
	xz-5.2.5/src/liblzma/simple/simple_decoder.c
	xz-5.2.5/src/liblzma/simple/simple_encoder.c
	xz-5.2.5/src/liblzma/simple/sparc.c
	xz-5.2.5/src/liblzma/simple/x86.c
	xz-5.2.5/src/common/mythread.h
	xz-5.2.5/src/common/sysdefs.h
	xz-5.2.5/src/common/tuklib_common.h
	xz-5.2.5/src/common/tuklib_config.h
	xz-5.2.5/src/common/tuklib_cpucores.h
	xz-5.2.5/src/common/tuklib_integer.h
	xz-5.2.5/src/common/tuklib_physmem.h
	xz-5.2.5/src/liblzma/api/lzma.h
	xz-5.2.5/src/liblzma/api/lzma/base.h
	xz-5.2.5/src/liblzma/api/lzma/bcj.h
	xz-5.2.5/src/liblzma/api/lzma/block.h
	xz-5.2.5/src/liblzma/api/lzma/check.h
	xz-5.2.5/src/liblzma/api/lzma/container.h
	xz-5.2.5/src/liblzma/api/lzma/delta.h
	xz-5.2.5/src/liblzma/api/lzma/filter.h
	xz-5.2.5/src/liblzma/api/lzma/hardware.h
	xz-5.2.5/src/liblzma/api/lzma/index.h
	xz-5.2.5/src/liblzma/api/lzma/index_hash.h
	xz-5.2.5/src/liblzma/api/lzma/lzma12.h
	xz-5.2.5/src/liblzma/api/lzma/stream_flags.h
	xz-5.2.5/src/liblzma/api/lzma/version.h
	xz-5.2.5/src/liblzma/api/lzma/vli.h
	xz-5.2.5/src/liblzma/check/check.h
	xz-5.2.5/src/liblzma/check/crc32_table_be.h
	xz-5.2.5/src/liblzma/check/crc32_table_le.h
	xz-5.2.5/src/liblzma/check/crc64_table_be.h
	xz-5.2.5/src/liblzma/check/crc64_table_le.h
	xz-5.2.5/src/liblzma/check/crc_macros.h
	xz-5.2.5/src/liblzma/common/alone_decoder.h
	xz-5.2.5/src/liblzma/common/block_buffer_encoder.h
	xz-5.2.5/src/liblzma/common/block_decoder.h
	xz-5.2.5/src/liblzma/common/block_encoder.h
	xz-5.2.5/src/liblzma/common/common.h
	xz-5.2.5/src/liblzma/common/easy_preset.h
	xz-5.2.5/src/liblzma/common/filter_common.h
	xz-5.2.5/src/liblzma/common/filter_decoder.h
	xz-5.2.5/src/liblzma/common/filter_encoder.h
	xz-5.2.5/src/liblzma/common/index.h
	xz-5.2.5/src/liblzma/common/index_encoder.h
	xz-5.2.5/src/liblzma/common/memcmplen.h
	xz-5.2.5/src/liblzma/common/outqueue.h
	xz-5.2.5/src/liblzma/common/stream_decoder.h
	xz-5.2.5/src/liblzma/common/stream_flags_common.h
	xz-5.2.5/src/liblzma/delta/delta_common.h
	xz-5.2.5/src/liblzma/delta/delta_decoder.h
	xz-5.2.5/src/liblzma/delta/delta_encoder.h
	xz-5.2.5/src/liblzma/delta/delta_private.h
	xz-5.2.5/src/liblzma/lzma/fastpos.h
	xz-5.2.5/src/liblzma/lzma/lzma2_decoder.h
	xz-5.2.5/src/liblzma/lzma/lzma2_encoder.h
	xz-5.2.5/src/liblzma/lzma/lzma_common.h
	xz-5.2.5/src/liblzma/lzma/lzma_decoder.h
	xz-5.2.5/src/liblzma/lzma/lzma_encoder.h
	xz-5.2.5/src/liblzma/lzma/lzma_encoder_private.h
	xz-5.2.5/src/liblzma/lz/lz_decoder.h
	xz-5.2.5/src/liblzma/lz/lz_encoder.h
	xz-5.2.5/src/liblzma/lz/lz_encoder_hash.h
	xz-5.2.5/src/liblzma/lz/lz_encoder_hash_table.h
	xz-5.2.5/src/liblzma/rangecoder/price.h
	xz-5.2.5/src/liblzma/rangecoder/range_common.h
	xz-5.2.5/src/liblzma/rangecoder/range_decoder.h
	xz-5.2.5/src/liblzma/rangecoder/range_encoder.h
	xz-5.2.5/src/liblzma/simple/simple_coder.h
	xz-5.2.5/src/liblzma/simple/simple_decoder.h
	xz-5.2.5/src/liblzma/simple/simple_encoder.h
	xz-5.2.5/src/liblzma/simple/simple_private.h
	xz_config.h
)



add_library(lzma ${SRC_FILES})

install (TARGETS lzma
         ARCHIVE DESTINATION lib COMPONENT SF3rdParties
         LIBRARY DESTINATION lib COMPONENT SF3rdParties
         RUNTIME DESTINATION bin COMPONENT SF3rdParties)



