////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2016 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : File
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "SFTypedefs.h"
#include "Task/SFTask.h"
#include "Stream/SFMemoryStream.h"


namespace SF {



	/////////////////////////////////////////////////////////////////////////////
	//
	//	File
	//

	class File
	{
	public:

		enum class OpenMode
		{
			Read,
			Create,
			Append,
		};

		enum class SharingMode
		{
			Shared,
			ReadShared,
			WriteShared,
			Exclusive,
		};


		static constexpr int BUFFERING_COUNT = 3;
#if defined(_DEBUG)
		static constexpr int BUFFERING_SIZE = 512;
#else
		static constexpr int BUFFERING_SIZE = 2048;
#endif


	private:
		// Access mode
		NativeHandle m_FileHandle;
		OpenMode m_OpenMode;
		SharingMode m_SharingMode;

		// multiple Buffering
		struct IO_BUFFER
		{
			NativeHandle& FileHandle;
			OpenMode& FileOpenMode;
			StaticArray<uint8_t, BUFFERING_SIZE> Buffer;
			OutputMemoryStream OutputStream;
			InputMemoryStream InputStream;

#if SF_PLATFORM == SF_PLATFORM_WINDOWS
			DWORD OperationSize = 0;
			OVERLAPPED AIOBuffer;
#elif SF_PLATFORM == SF_PLATFORM_LINUX
			size_t OperationSize = 0;
			aiocb AIOBuffer;
#else
			// TODO:
			// just dummy for compatibility
			size_t OperationSize = 0;
			struct {
				void* Dummy;
			} AIOBuffer;
#endif
			bool bPending = false;


			IO_BUFFER(IHeap& memoryManager, NativeHandle& fileHandle, OpenMode& fileOpenMode)
				: FileHandle(fileHandle)
				, FileOpenMode(fileOpenMode)
				, Buffer(memoryManager)
				, OutputStream(Buffer)
				//, InputStream(ArrayView<const uint8_t>(Buffer.capacity(), Buffer.data()))
			{
				memset(&AIOBuffer, 0, sizeof(AIOBuffer));
				InitAIO();
			}

			~IO_BUFFER()
			{
				CleanAIO();
			}

			void InitAIO();
			void WaitAIO();
			void CleanAIO();
			void Reset();
		};

		size_t m_IOOffset = 0;
		size_t m_BufferIndex = 0;
		IO_BUFFER* m_IOBuffers[BUFFERING_COUNT];
		//uint8_t m



	public:
		File();
		~File();

		bool IsOpened();

		static constexpr bool IsAIOEnabled()
		{
#if SF_PLATFORM == SF_PLATFORM_WINDOWS || SF_PLATFORM == SF_PLATFORM_LINUX
			return true;
#else
			return false;
#endif
		}

		// seek
		Result Seek(SeekMode seekMode, int64_t offset = 0);

		size_t GetPosition() const;
		size_t GetFileSize() const;

		Result Open(const char* filePath, OpenMode openMode, SharingMode sharingMode = SharingMode::Shared);
		void Close();

		// flush pending write
		void Flush();

		// Sometimes we would like to use direct api than buffered one
		Result ReadRaw(uint8_t* buffer, size_t bufferLen, IO_BUFFER* pIOBuffer, size_t &read);
		Result WriteRaw(const uint8_t* buffer, size_t bufferLen, IO_BUFFER* pIOBuffer, size_t &written);
		size_t GetLocationRaw() const;

		Result Read(uint8_t* buffer, size_t bufferLen, size_t &read);
		Result Write(const uint8_t* buffer, size_t bufferLen, size_t &written);

	};




}
