////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2017 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : SharedMemory
//
////////////////////////////////////////////////////////////////////////////////


#include "SFCorePCH.h"
#include "SFTypedefs.h"
#include "IO/SharedMemory/SFSharedMemory.h"
#include "ResultCode/SFResultCodeLibrary.h"


#if SF_PLATFORM == SF_PLATFORM_WINDOWS

namespace SF
{
	////////////////////////////////////////////////////////////////////////////////
	// 
	//	SharedMemory class
	// 


	SharedMemory::SharedMemory(IHeap& heap)
		: m_MemoryName(heap)
	{

	}

	SharedMemory::~SharedMemory()
	{

	}

	// Open Memory mapped file, it will try to create if not exists
	Result SharedMemory::Create(const char* memoryName, uint memorySize)
	{
		if (m_hMemory != INVALID_NATIVE_HANDLE_VALUE)
			return ResultCode::INVALID_STATE;


		m_hMemory = CreateFileMappingA(INVALID_NATIVE_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, memorySize, memoryName);
		if (m_hMemory == INVALID_NATIVE_HANDLE_VALUE || m_hMemory == nullptr)
		{
			m_hMemory = INVALID_NATIVE_HANDLE_VALUE;
			return GetLastResultCode();
		}

		m_pMemory = MapViewOfFile(m_hMemory,
			FILE_MAP_ALL_ACCESS, // read/write permission
			0,
			0,
			memorySize);
		if (m_pMemory == nullptr)
		{
			CloseHandle(m_hMemory);
			m_hMemory = INVALID_NATIVE_HANDLE_VALUE;
			return GetLastResultCode();
		}

		m_MemorySize = memorySize;

		return ResultCode::SUCCESS;
	}

	// Open Memory mapped file, it will try to create if not exists
	Result SharedMemory::Open(const char* memoryName, uint mappingSize)
	{
		if (m_hMemory != INVALID_NATIVE_HANDLE_VALUE)
			return ResultCode::INVALID_STATE;


		m_hMemory = OpenFileMappingA(FILE_MAP_ALL_ACCESS, FALSE, memoryName);
		if (m_hMemory == INVALID_NATIVE_HANDLE_VALUE || m_hMemory == nullptr)
		{
			m_hMemory = INVALID_NATIVE_HANDLE_VALUE;
			return GetLastResultCode();
		}

		m_pMemory = MapViewOfFile(m_hMemory,
			FILE_MAP_ALL_ACCESS, // read/write permission
			0,
			0,
			mappingSize);
		if (m_pMemory == nullptr)
		{
			CloseHandle(m_hMemory);
			m_hMemory = INVALID_NATIVE_HANDLE_VALUE;
			return GetLastResultCode();
		}

		m_MemorySize = mappingSize;

		return ResultCode::SUCCESS;
	}

	// Close mapped file
	void SharedMemory::Close()
	{
		if (m_hMemory = INVALID_NATIVE_HANDLE_VALUE)
			return;

		UnmapViewOfFile(m_pMemory);

		CloseHandle(m_hMemory);

		m_hMemory = INVALID_NATIVE_HANDLE_VALUE;
		m_MemorySize = 0;
		m_pMemory = nullptr;
	}


}

#endif

