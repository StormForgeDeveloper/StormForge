////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2018 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Compressed stream
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "SFTypedefs.h"
#include "Stream/SFStream.h"
#include "Container/SFArray.h"


typedef struct z_stream_s z_stream;

namespace SF
{

	/////////////////////////////////////////////////////////////////////////////////////////
	//
	// Compressed Input stream class
	//

	class CompressedInputStream : public IInputStream
	{
	public:

		uint8_t m_StreamStructBuffer[1024];
		uint8_t m_DecompressBuffer[4096];

		IHeap& m_Heap;
		IInputStream& m_Stream;

		z_stream* m_CompressionInfo = nullptr;

		size_t m_CompressedSourceSize = 0;
		size_t m_DecompressedSize = 0;
		size_t m_InputStartPosition = 0;
		size_t m_Position = 0;


	private:

		void CloseCompressionStream();

	public:

		CompressedInputStream(IHeap& heap, IInputStream& inputStream, size_t sourceSize, size_t decompressedSize);
		virtual ~CompressedInputStream();
		
		size_t GetCompressedSize() const { return m_Stream.GetSize(); }

		// return true if the stream is valid and have something read
		virtual bool CanRead() override { return m_Stream.CanRead() || m_DecompressedSize > m_Position; }

		virtual Result Seek(SeekMode seekPos, int64_t offset) override;

		virtual size_t GetPosition() const override { return m_Position; }

		virtual size_t GetSize() const override { return m_DecompressedSize; }

		// Read data
		virtual Result Read(void* buffer, size_t readSize) override;
	};


	/////////////////////////////////////////////////////////////////////////////////////////
	//
	// compressed Output stream class
	//

	class CompressedOutputStream : public IOutputStream
	{
	private:

		uint8_t m_StreamStructBuffer[1024];
		uint8_t m_CompressBuffer[4096];

		IHeap& m_Heap;
		IOutputStream& m_Stream;

		z_stream* m_CompressionInfo = nullptr;

		size_t m_CompressedOutputSize = 0;
		size_t m_Position = 0;

	public:

		CompressedOutputStream(IHeap& heap, IOutputStream& stream);
		virtual ~CompressedOutputStream();

		// close compression stream
		void CloseCompressionStream();

		// Get compressed size
		size_t GetCompressedSize() const;

		// flush pending output
		Result Flush();

		// return true if the stream is valid and able to be written
		virtual bool CanWrite() override { return m_Stream.CanWrite(); }
		virtual size_t GetPosition() const override { return m_Position; }
		virtual size_t GetSize() const override { return m_Position; }

		// Write data
		virtual Result Write(const void* buffer, size_t writeSize) override;
	};


} // namespace SF

