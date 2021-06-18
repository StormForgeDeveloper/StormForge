////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2016 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : File
//
////////////////////////////////////////////////////////////////////////////////


#include "SFCorePCH.h"
#include "SFTypedefs.h"
#include "IO/SFFile.h"
#include "ResultCode/SFResultCodeSystem.h"


#if SF_PLATFORM == SF_PLATFORM_LINUX || SF_PLATFORM == SF_PLATFORM_ANDROID || SF_PLATFORM == SF_PLATFORM_IOS



namespace SF {




	/////////////////////////////////////////////////////////////////////////////
	//
	//	File
	//

	static INT ToOSSeekMode[] =
	{
		SEEK_SET,		// Begin,
		SEEK_CUR,	// Current,
		SEEK_END,		// End,
	};



	void File::IO_BUFFER::InitAIO()
	{
#if SF_PLATFORM == SF_PLATFORM_LINUX
		if (AIOBuffer.aio_fildes != 0)
			return;
#endif
	}

	void File::IO_BUFFER::WaitAIO()
	{
#if SF_PLATFORM == SF_PLATFORM_LINUX
		if (AIOBuffer.aio_fildes == 0)
			return;

		aiocb* aiBufferList[] = { &AIOBuffer };
		aio_suspend(aiBufferList, 1, 0);
		if(OperationSize == 0)
			OperationSize = aio_return(&AIOBuffer);

		if (FileOpenMode == OpenMode::Read)
		{
			//assert(OperationSize > 0); // just checking
			Buffer.resize(OperationSize);
		}

#endif
	}

	void File::IO_BUFFER::CleanAIO()
	{
#if SF_PLATFORM == SF_PLATFORM_LINUX
		if (AIOBuffer.aio_fildes == 0)
			return;

		WaitAIO();

		AIOBuffer.aio_fildes = 0;
#endif
	}

/*
	Result File::Seek(SeekMode seekMode, int64_t offset)
	{
		if (m_FileHandle == INVALID_NATIVE_HANDLE_VALUE)
			return ResultCode::FAIL;

		lseek((int)(int64_t)m_FileHandle, offset, ToOSSeekMode[(int)seekMode]);

		return ResultCode::SUCCESS;
	}
*/
	size_t File::GetLocationRaw() const
	{
		if (m_FileHandle == INVALID_NATIVE_HANDLE_VALUE)
			return ResultCode::FAIL;

		return static_cast<size_t>(lseek((int)(int64_t)m_FileHandle, 0, SEEK_CUR));
	}

	size_t File::GetFileSize() const
	{
		if (m_FileHandle == INVALID_NATIVE_HANDLE_VALUE)
			return ResultCode::FAIL;

		struct stat buf;
		fstat((int)(int64_t)m_FileHandle, &buf);
		return static_cast<size_t>(buf.st_size);
	}

	Result File::Open(const char* filePath, OpenMode openMode, SharingMode sharingMode)
	{
		Close();

		m_IOOffset = 0;

		uint uiOpenMode = 0;
		uint uiSharingMode = 0;

		switch (openMode)
		{
		case OpenMode::Read:
			uiOpenMode = O_RDONLY;
			break;
		case OpenMode::Create:
			uiOpenMode = O_RDWR | O_CREAT | O_TRUNC;
			break;
		case OpenMode::Append:
			uiOpenMode = O_RDWR | O_CREAT | O_APPEND;
			break;
		default:
			return ResultCode::UNEXPECTED;
		}

		switch (sharingMode)
		{
		case SharingMode::Shared:
		default:
			uiSharingMode = S_IRWXU | S_IRWXG | S_IRWXO;
			break;
		case SharingMode::ReadShared:
			uiSharingMode = S_IRWXU | S_IRGRP | S_IROTH;
			break;
		case SharingMode::WriteShared:
			uiSharingMode = S_IRWXU | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH;
			break;
		case SharingMode::Exclusive:
			uiSharingMode = S_IRWXU;
			break;
		}


		m_FileHandle = (NativeHandle)(int64_t)open(
			filePath,
			uiOpenMode, uiSharingMode);

		if (m_FileHandle <= 0)
		{
			m_FileHandle = INVALID_NATIVE_HANDLE_VALUE;
			return GetLastResultCode();
		}

		struct flock fl;
		fl.l_whence = SEEK_SET; /* SEEK_SET, SEEK_CUR, SEEK_END */
		fl.l_start = 0;        /* Offset from l_whence         */
		fl.l_len = 0;        /* length, 0 = to EOF           */
		fl.l_pid = getpid(); /* our PID                      */
		switch (sharingMode)
		{
		case SharingMode::Shared:
			fl.l_type = F_UNLCK;  /* F_RDLCK, F_WRLCK, F_UNLCK    */
			break;
		case SharingMode::ReadShared:
			fl.l_type = F_WRLCK;  /* F_RDLCK, F_WRLCK, F_UNLCK    */
			fcntl((int)(int64_t)m_FileHandle, F_SETLK, &fl);
			break;
		case SharingMode::WriteShared:
			fl.l_type = F_RDLCK;  /* F_RDLCK, F_WRLCK, F_UNLCK    */
			fcntl((int)(int64_t)m_FileHandle, F_SETLK, &fl);
			break;
		case SharingMode::Exclusive:
			fl.l_type = F_RDLCK | F_WRLCK;  /* F_RDLCK, F_WRLCK, F_UNLCK    */
			fcntl((int)(int64_t)m_FileHandle, F_SETLK, &fl);
			break;
		default:
			return ResultCode::UNEXPECTED;
		}

		m_OpenMode = openMode;
		m_SharingMode = sharingMode;
		m_BufferIndex = 0;

		// When read mode request the first read
		if (m_OpenMode == OpenMode::Read && IsAIOEnabled())
		{
			auto pIOBuffer = m_IOBuffers[m_BufferIndex];
			size_t read = 0;
			ReadRaw(pIOBuffer->Buffer.data(), pIOBuffer->Buffer.GetAllocatedSize(), pIOBuffer, read);
		}

		return ResultCode::SUCCESS;

	}

	void File::Close()
	{
		if (m_FileHandle == INVALID_NATIVE_HANDLE_VALUE)
			return;

		Flush();

		close((int)(int64_t)m_FileHandle);
		m_FileHandle = INVALID_NATIVE_HANDLE_VALUE;
	}

	Result File::Seek(SeekMode seekMode, int64_t offset)
	{
		if (m_FileHandle == INVALID_NATIVE_HANDLE_VALUE)
			return ResultCode::FAIL;

		auto result = lseek(m_FileHandle, offset, ToOSSeekMode[(int)seekMode]);
		if (result < 0)
		{
			return GetLastResultCode();
		}

		return ResultCode::SUCCESS;
	}

	Result File::ReadRaw(uint8_t* buffer, size_t bufferLen, IO_BUFFER* pIOBuffer, size_t &readSize)
	{
		if (!IsOpened())
			return ResultCode::NOT_OPENED;

		if (pIOBuffer != nullptr && IsAIOEnabled())
		{
			pIOBuffer->WaitAIO();
#if SF_PLATFORM == SF_PLATFORM_LINUX
			pIOBuffer->OperationSize = 0;
			pIOBuffer->AIOBuffer.aio_fildes = (int)(int64_t)m_FileHandle;
			pIOBuffer->AIOBuffer.aio_buf = buffer;
			pIOBuffer->AIOBuffer.aio_nbytes = bufferLen;
			pIOBuffer->AIOBuffer.aio_offset = m_IOOffset;
			pIOBuffer->AIOBuffer.aio_sigevent.sigev_notify = SIGEV_NONE;
			aio_read(&pIOBuffer->AIOBuffer);
#endif
		}
		else
		{
			size_t dwRead = 0;
			dwRead = read((int)(int64_t)m_FileHandle, buffer, bufferLen);
			if (dwRead < bufferLen)
			{
				return ResultCode::FAIL;
			}

			readSize = dwRead;
			if (pIOBuffer != nullptr)
				pIOBuffer->OperationSize = readSize;
		}


		m_IOOffset += bufferLen;

		return ResultCode::SUCCESS;
	}

	Result File::WriteRaw(const uint8_t* buffer, size_t bufferLen, IO_BUFFER* pIOBuffer, size_t &written)
	{
		if (!IsOpened())
			return ResultCode::NOT_OPENED;

		if (pIOBuffer != nullptr && IsAIOEnabled())
		{
			pIOBuffer->WaitAIO();
#if SF_PLATFORM == SF_PLATFORM_LINUX
			pIOBuffer->OperationSize = 0;
			pIOBuffer->AIOBuffer.aio_fildes = (int)(int64_t)m_FileHandle;
			pIOBuffer->AIOBuffer.aio_buf = (void*)buffer;
			pIOBuffer->AIOBuffer.aio_nbytes = bufferLen;
			pIOBuffer->AIOBuffer.aio_offset = m_IOOffset;
			pIOBuffer->AIOBuffer.aio_sigevent.sigev_notify = SIGEV_NONE;

			aio_write(&pIOBuffer->AIOBuffer);
#endif
		}
		else
		{
			size_t dwWritten = write((int)(int64_t)m_FileHandle, buffer, bufferLen);
			if (dwWritten < bufferLen)
			{
				return ResultCode::FAIL;
			}

			written = dwWritten;
			if (pIOBuffer != nullptr)
				pIOBuffer->OperationSize = written;
		}

		m_IOOffset += bufferLen;

		return ResultCode::SUCCESS;
	}






}
#else

void Dummy_BRFile_Linux() {}

#endif
