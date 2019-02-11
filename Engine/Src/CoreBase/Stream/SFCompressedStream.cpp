////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2017 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : SFFileOutputStream
//	
//
////////////////////////////////////////////////////////////////////////////////



#include "CoreBasePCH.h"
#include "SFTypedefs.h"
#include "Stream/SFCompressedStream.h"
#include "Util/SFUtility.h"
#include "zlib.h"



namespace SF {


	namespace ImplCompressedStream
	{
		// 
		void* alloc_func(voidpf opaque, uInt items, uInt size)
		{
			auto pHeap = (IHeap*)opaque;
			return pHeap->Alloc(items * size);
		}

		// 
		void free_func(voidpf opaque, voidpf address)
		{
			auto pHeap = (IHeap*)opaque;
			pHeap->Free(address);
		}

	}


	/////////////////////////////////////////////////////////////////////////////
	//
	//	CompressedInputStream
	//
	CompressedInputStream::CompressedInputStream(IHeap& heap, IInputStream& inputStream, size_t sourceSize, size_t decompressedSize)
		: m_Heap(heap)
		, m_Stream(inputStream)
		, m_CompressedSourceSize(sourceSize)
		, m_DecompressedSize(decompressedSize)
	{
		m_CompressionInfo = (z_stream*)m_StreamStructBuffer;
		memset(m_CompressionInfo, 0, sizeof(z_stream));
		m_CompressionInfo->zalloc = ImplCompressedStream::alloc_func;
		m_CompressionInfo->zfree = ImplCompressedStream::free_func;
		m_CompressionInfo->opaque = &m_Heap;

		m_InputStartPosition = inputStream.GetPosition();

		inflateInit(m_CompressionInfo);
	}

	CompressedInputStream::~CompressedInputStream()
	{
		CloseCompressionStream();
	}

	void CompressedInputStream::CloseCompressionStream()
	{
		if (m_CompressionInfo != nullptr)
			inflateEnd(m_CompressionInfo);
		m_CompressionInfo = nullptr;
	}

	size_t CompressedInputStream::Seek(SeekMode seekPos, int64_t offset)
	{
		if (seekPos != SeekMode::Current)
		{
			Assert(false); // not supported
			return GetPosition();
		}

		uint8_t decompressBuffer[128];

		while (offset > 0)
		{
			auto readSize = Util::Min(offset, (int64_t)sizeof(decompressBuffer));
			Read(decompressBuffer, static_cast<size_t>(readSize));
			offset -= readSize;
		}
		return GetPosition();
	}

	// Read data
	Result CompressedInputStream::Read(void* buffer, size_t readSize)
	{
		auto remainOutputSize = m_DecompressedSize - m_Position;
		if (remainOutputSize < readSize)
		{
			readSize = remainOutputSize;
		}

		if (readSize == 0)
			return ResultCode::FAIL;

		m_CompressionInfo->next_out = (Bytef*)buffer;
		m_CompressionInfo->avail_out = (uint)readSize;

		while (m_CompressionInfo->avail_out > 0)
		{
			if (m_CompressionInfo->avail_in == 0)
			{
				auto remainInputSize = m_Stream.GetPosition() - m_InputStartPosition;
				auto readSize = sizeof(m_DecompressBuffer);
				if (remainInputSize < readSize)
				{
					readSize = remainInputSize;
				}

				if (readSize == 0)
					return ResultCode::END_OF_STREAM;

				Result result = m_Stream.Read(m_DecompressBuffer, readSize);
				if (!result)
					return result;

				m_CompressionInfo->avail_in = (uint)readSize;
				m_CompressionInfo->next_in = m_DecompressBuffer;
			}

			auto zError = inflate(m_CompressionInfo, Z_NO_FLUSH);
			switch (zError)
			{
			case Z_NEED_DICT:
				zError = Z_DATA_ERROR;
			case Z_DATA_ERROR:
			case Z_STREAM_ERROR:
				CloseCompressionStream();
				return ResultCode::INVALID_FORMAT;
			case Z_MEM_ERROR:
				CloseCompressionStream();
				return ResultCode::OUT_OF_MEMORY;
			}
		}

		m_Position += readSize;

		return ResultCode::SUCCESS;
	}





	/////////////////////////////////////////////////////////////////////////////////////////
	//
	// compressed Output stream class
	//


	CompressedOutputStream::CompressedOutputStream(IHeap& heap, IOutputStream& stream)
		: m_Heap(heap)
		, m_Stream(stream)
	{
		m_CompressionInfo = (z_stream*)m_StreamStructBuffer;
		memset(m_CompressionInfo, 0, sizeof(z_stream));
		m_CompressionInfo->zalloc = ImplCompressedStream::alloc_func;
		m_CompressionInfo->zfree = ImplCompressedStream::free_func;
		m_CompressionInfo->opaque = &m_Heap;

		deflateInit(m_CompressionInfo, Z_DEFAULT_COMPRESSION);
	}

	CompressedOutputStream::~CompressedOutputStream()
	{
		CloseCompressionStream();
	}

	void CompressedOutputStream::CloseCompressionStream()
	{
		if (m_CompressionInfo != nullptr)
			deflateEnd(m_CompressionInfo);
		m_CompressionInfo = nullptr;
	}

	// flush pending output
	Result CompressedOutputStream::Flush()
	{
		if (m_CompressionInfo == nullptr)
			return ResultCode::SUCCESS;

		while(true)
		{
			if (m_CompressionInfo->avail_out == 0)
			{
				m_CompressedOutputSize += sizeof(m_CompressBuffer);
				Result result = m_Stream.Write(m_CompressBuffer, sizeof(m_CompressBuffer));
				if (!result)
					return result;

				m_CompressionInfo->avail_out = sizeof(m_CompressBuffer);
				m_CompressionInfo->next_out = m_CompressBuffer;
			}


			auto zError = deflate(m_CompressionInfo, Z_FULL_FLUSH);
			switch (zError)
			{
			case Z_NEED_DICT:
				zError = Z_DATA_ERROR;
			case Z_DATA_ERROR:
			case Z_STREAM_ERROR:
				CloseCompressionStream();
				return ResultCode::FAIL;
			case Z_MEM_ERROR:
				CloseCompressionStream();
				return ResultCode::FAIL;
			case Z_STREAM_END:
				m_CompressedOutputSize += sizeof(m_CompressBuffer) - m_CompressionInfo->avail_out;
				return ResultCode::SUCCESS;
			}
		}

	}

	size_t CompressedOutputStream::GetCompressedSize() const
	{
		if (m_CompressionInfo == nullptr)
			return m_CompressedOutputSize;
		else
			return m_CompressedOutputSize + sizeof(m_CompressBuffer) - m_CompressionInfo->avail_out;
	}

	// Write data
	Result CompressedOutputStream::Write(const void* buffer, size_t writeSize)
	{
		m_CompressionInfo->next_in = (Bytef*)buffer;
		m_CompressionInfo->avail_in = (uint)writeSize;

		while (m_CompressionInfo->avail_in > 0)
		{
			if (m_CompressionInfo->avail_out == 0)
			{
				m_CompressedOutputSize += sizeof(m_CompressBuffer);
				Result result = m_Stream.Write(m_CompressBuffer, sizeof(m_CompressBuffer));
				if (!result)
					return result;

				m_CompressionInfo->avail_out = sizeof(m_CompressBuffer);
				m_CompressionInfo->next_out = m_CompressBuffer;
			}


			auto zError = deflate(m_CompressionInfo, Z_NO_FLUSH);
			switch (zError)
			{
			case Z_NEED_DICT:
				zError = Z_DATA_ERROR;
			case Z_DATA_ERROR:
			case Z_STREAM_ERROR:
				CloseCompressionStream();
				return ResultCode::INVALID_FORMAT;
			case Z_MEM_ERROR:
				CloseCompressionStream();
				return ResultCode::OUT_OF_MEMORY;
			}
		}

		m_Position += writeSize;

		return ResultCode::SUCCESS;
	}


}

