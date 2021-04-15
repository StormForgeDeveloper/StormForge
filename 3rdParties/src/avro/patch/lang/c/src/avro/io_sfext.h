////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) The Braves
// 
// Author : KyungKun Ko
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#ifdef __cplusplus
extern "C" {
#define CLOSE_EXTERN }
#else
#define CLOSE_EXTERN
#endif

#include <avro/platform.h>

#include <avro/basics.h>
#include <avro/legacy.h>
#include <avro/schema.h>
#include <avro/value.h>

typedef struct avro_reader_t_ *avro_reader_t;
typedef struct avro_writer_t_ *avro_writer_t;

/* File object container */
typedef struct avro_file_reader_t_ *avro_file_reader_t;
typedef struct avro_file_writer_t_ *avro_file_writer_t;

// extended interface with generic reader interface

int avro_file_writer_create_with_codec_writer(avro_writer_t file_writer,
				avro_schema_t schema, avro_file_writer_t * writer,
				const char *codec, size_t block_size);

int avro_file_reader_reader(avro_reader_t file_reader, avro_file_reader_t * reader);



CLOSE_EXTERN
