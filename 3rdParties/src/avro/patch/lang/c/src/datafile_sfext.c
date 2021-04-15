////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) The Braves
// 
// Author : KyungKun Ko
//
////////////////////////////////////////////////////////////////////////////////

// will be inline included

static int file_writer_create_writer(avro_writer_t file_writer, avro_schema_t schema, avro_file_writer_t w, size_t block_size)
{
	w->block_count = 0;
	w->writer = file_writer;
	if (w->writer == NULL)
	{
		avro_set_error("Invalid file writer\n");
		avro_writer_free(w->writer);
		return ENOMEM;
	}

	w->datum_buffer_size = block_size;
	w->datum_buffer = (char*)avro_malloc(w->datum_buffer_size);

	if (!w->datum_buffer) {
		avro_set_error("Could not allocate datum buffer\n");
		avro_writer_free(w->writer);
		return ENOMEM;
	}

	w->datum_writer =
		avro_writer_memory(w->datum_buffer, w->datum_buffer_size);
	if (!w->datum_writer) {
		avro_set_error("Cannot create datum writer for file writer");
		avro_writer_free(w->writer);
		avro_free(w->datum_buffer, w->datum_buffer_size);
		return ENOMEM;
	}

	w->writers_schema = avro_schema_incref(schema);
	return write_header(w);
}

int avro_file_writer_create_with_codec_reader(avro_writer_t file_writer,
	avro_schema_t schema, avro_file_writer_t* writer,
	const char* codec, size_t block_size)
{
	avro_file_writer_t w;
	int rval;
	check_param(EINVAL, file_writer, "file_writer");
	check_param(EINVAL, is_avro_schema(schema), "schema");
	check_param(EINVAL, writer, "writer");
	check_param(EINVAL, codec, "codec");

	if (block_size == 0) {
		block_size = DEFAULT_BLOCK_SIZE;
	}

	w = (avro_file_writer_t)avro_new(struct avro_file_writer_t_);
	if (!w) {
		avro_set_error("Cannot allocate new file writer");
		return ENOMEM;
	}
	w->codec = (avro_codec_t)avro_new(struct avro_codec_t_);
	if (!w->codec) {
		avro_set_error("Cannot allocate new codec");
		avro_freet(struct avro_file_writer_t_, w);
		return ENOMEM;
	}
	rval = avro_codec(w->codec, codec);
	if (rval) {
		avro_codec_reset(w->codec);
		avro_freet(struct avro_codec_t_, w->codec);
		avro_freet(struct avro_file_writer_t_, w);
		return rval;
	}
	rval = file_writer_create_writer(file_writer, schema, w, block_size);
	if (rval) {
		avro_codec_reset(w->codec);
		avro_freet(struct avro_codec_t_, w->codec);
		avro_freet(struct avro_file_writer_t_, w);
		return rval;
	}
	*writer = w;

	return 0;
}


int avro_file_reader_reader(avro_reader_t file_reader, avro_file_reader_t* reader)
{
	int rval;
	avro_file_reader_t r = (avro_file_reader_t)avro_new(struct avro_file_reader_t_);
	if (!r) {
		avro_set_error("Cannot allocate file reader");
		return ENOMEM;
	}

	r->reader = file_reader;
	if (!r->reader) {
		avro_set_error("Cannot allocate reader for file reader");
		avro_freet(struct avro_file_reader_t_, r);
		return ENOMEM;
	}
	r->block_reader = avro_reader_memory(0, 0);
	if (!r->block_reader) {
		avro_set_error("Cannot allocate block reader for file reader");
		avro_reader_free(r->reader);
		avro_freet(struct avro_file_reader_t_, r);
		return ENOMEM;
	}

	r->codec = (avro_codec_t)avro_new(struct avro_codec_t_);
	if (!r->codec) {
		avro_set_error("Could not allocate codec for file reader");
		avro_reader_free(r->reader);
		avro_freet(struct avro_file_reader_t_, r);
		return ENOMEM;
	}
	avro_codec(r->codec, NULL);

	rval = file_read_header(r->reader, &r->writers_schema, r->codec,
		r->sync, sizeof(r->sync));
	if (rval) {
		avro_reader_free(r->reader);
		avro_codec_reset(r->codec);
		avro_freet(struct avro_codec_t_, r->codec);
		avro_freet(struct avro_file_reader_t_, r);
		return rval;
	}

	r->current_blockdata = NULL;
	r->current_blocklen = 0;

	rval = file_read_block_count(r);
	if (rval == EOF) {
		r->blocks_total = 0;
	}
	else if (rval) {
		avro_reader_free(r->reader);
		avro_codec_reset(r->codec);
		avro_freet(struct avro_codec_t_, r->codec);
		avro_freet(struct avro_file_reader_t_, r);
		return rval;
	}

	*reader = r;
	return 0;
}



