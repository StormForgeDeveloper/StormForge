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

#if SF_PLATFORM == SF_PLATFORM_WINDOWS

namespace SF {



	/////////////////////////////////////////////////////////////////////////////
	//
	//	File
	//

	static INT ToWin32SeekMode[] = 
	{
		FILE_BEGIN,		// Begin,
		FILE_CURRENT,	// Current,
		FILE_END,		// End,
	};


	void File::IO_BUFFER::InitAIO()
	{
		if (AIOBuffer.hEvent != nullptr && AIOBuffer.hEvent != INVALID_HANDLE_VALUE)
			return;

		// set initial state to signaled. we are going to wait before request any file operation
		AIOBuffer.hEvent = CreateEvent(nullptr, TRUE, TRUE, nullptr);

	}

	void File::IO_BUFFER::WaitAIO()
	{
		if (AIOBuffer.hEvent == nullptr || AIOBuffer.hEvent == INVALID_HANDLE_VALUE)
			return;

		auto waited = WaitForSingleObject(AIOBuffer.hEvent, 10 * 1000);
		if (waited == WAIT_OBJECT_0)
		{
			if (FileOpenMode == OpenMode::Read)
			{
				DWORD dwOperationSize = 0;
				GetOverlappedResult(FileHandle, &AIOBuffer, &dwOperationSize, FALSE);
				//assert(dwOperationSize != 0); // just checking
				Buffer.resize(dwOperationSize);
			}
		}
		else
		{
			assert(false); // failed to wait!
		}
	}

	void File::IO_BUFFER::CleanAIO()
	{
		if (AIOBuffer.hEvent == nullptr || AIOBuffer.hEvent == INVALID_HANDLE_VALUE)
			return;

		WaitAIO();

		CloseHandle(AIOBuffer.hEvent);

		AIOBuffer.hEvent = nullptr;
	}


	Result File::Seek(SeekMode seekMode, int64_t offset)
	{
		if (m_FileHandle == INVALID_NATIVE_HANDLE_VALUE)
			return ResultCode::FAIL;

		LARGE_INTEGER lInt;
		lInt.QuadPart = offset;

		lInt.LowPart = SetFilePointer(m_FileHandle, lInt.LowPart, &lInt.HighPart, ToWin32SeekMode[(int)seekMode]);
		if (lInt.LowPart == INVALID_SET_FILE_POINTER)
		{
			return GetLastResultCode();
		}

		return ResultCode::SUCCESS;
	}

	size_t File::GetLocationRaw() const
	{
		if (m_FileHandle == INVALID_NATIVE_HANDLE_VALUE)
			return ResultCode::FAIL;

		LARGE_INTEGER lInt;
		lInt.QuadPart = 0;
		lInt.LowPart = SetFilePointer(m_FileHandle, 0, &lInt.HighPart, FILE_CURRENT);

		return (size_t)lInt.QuadPart;
	}

	size_t File::GetFileSize() const
	{
		if (m_FileHandle == INVALID_NATIVE_HANDLE_VALUE)
			return ResultCode::FAIL;

		LARGE_INTEGER szSize;
		if (GetFileSizeEx(m_FileHandle, &szSize) == INVALID_FILE_SIZE)
		{
			return 0;
		}
		return (size_t)szSize.QuadPart;
	}

	Result File::Open(const char* filePath, OpenMode openMode, SharingMode sharingMode)
	{
		Close();


		m_IOOffset = 0;

		DWORD accessMode = 0;
		DWORD shareMode = 0;
		DWORD creationDesc = 0;

		switch (openMode)
		{
		case OpenMode::Read:
			accessMode = GENERIC_READ;
			creationDesc = OPEN_EXISTING;
			break;
		case OpenMode::Create:
			accessMode = GENERIC_READ | GENERIC_WRITE;
			creationDesc = CREATE_ALWAYS;
			break;
		case OpenMode::Append:
			accessMode = GENERIC_READ | GENERIC_WRITE;
			creationDesc = OPEN_ALWAYS;
			break;
		default:
			return ResultCode::UNEXPECTED;
		}

		switch (sharingMode)
		{
		case SharingMode::Shared:
			shareMode = FILE_SHARE_READ | FILE_SHARE_WRITE;
			break;
		case SharingMode::ReadShared:
			shareMode = FILE_SHARE_READ;
			break;
		case SharingMode::WriteShared:
			shareMode = FILE_SHARE_WRITE;
			break;
		case SharingMode::Exclusive:
			shareMode = 0;
			break;
		default:
			return ResultCode::UNEXPECTED;
		}

		m_FileHandle = CreateFileA(
			filePath,
			accessMode,
			shareMode,
			nullptr,
			creationDesc,
			FILE_ATTRIBUTE_NORMAL
			| FILE_FLAG_SEQUENTIAL_SCAN,
			nullptr);

		if (m_FileHandle == INVALID_NATIVE_HANDLE_VALUE)
			return ResultCode::FAIL;

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

		CancelIo(m_FileHandle);
		CloseHandle(m_FileHandle);
		m_FileHandle = INVALID_NATIVE_HANDLE_VALUE;
	}


	Result File::ReadRaw(uint8_t* buffer, size_t bufferLen, IO_BUFFER* pIOBuffer, size_t &read)
	{
		if (!IsOpened())
			return ResultCode::NOT_OPENED;

		read = 0;

		if (pIOBuffer != nullptr && IsAIOEnabled())
		{
			pIOBuffer->WaitAIO();

			pIOBuffer->AIOBuffer.Pointer = (void*)m_IOOffset;

			ResetEvent(pIOBuffer->AIOBuffer.hEvent);

			if (ReadFile(m_FileHandle, buffer, (DWORD)bufferLen, &pIOBuffer->OperationSize, &pIOBuffer->AIOBuffer) == FALSE)
			{
				return GetLastResultCode();
			}
		}
		else
		{
			DWORD dwRead = 0;
			if (ReadFile(m_FileHandle, buffer, (DWORD)bufferLen, &dwRead, nullptr) == FALSE)
			{
				return GetLastResultCode();
			}

			read = dwRead;

			if (pIOBuffer != nullptr)
				pIOBuffer->OperationSize = dwRead;
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

			pIOBuffer->AIOBuffer.Pointer = (void*)m_IOOffset;

			ResetEvent(pIOBuffer->AIOBuffer.hEvent);

			if (WriteFile(m_FileHandle, buffer, (DWORD)bufferLen, &pIOBuffer->OperationSize, &pIOBuffer->AIOBuffer) == FALSE)
			{
				return GetLastResultCode();
			}

		}
		else
		{
			DWORD dwWritten = 0;
			if (WriteFile(m_FileHandle, buffer, (DWORD)bufferLen, &dwWritten, nullptr) == FALSE)
			{
				return GetLastResultCode();
			}
			written = dwWritten;

			if (pIOBuffer != nullptr)
				pIOBuffer->OperationSize = dwWritten;

		}


		m_IOOffset += bufferLen;

		return ResultCode::SUCCESS;
	}


}

#endif
