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
#include "Util/SFLog.h"



#if SF_PLATFORM == SF_PLATFORM_LINUX 

#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>


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

	// Create Memory mapped file
	Result SharedMemory::Create(const char* memoryName, uint memorySize)
	{
		if (m_hMemory != INVALID_NATIVE_HANDLE_VALUE)
			return ResultCode::INVALID_STATE;

		auto shm_fd = shm_open(memoryName, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
		if (shm_fd == -1)
		{
			auto result = GetLastResultCode();
			SFLog(System, Error, "SharedMemory creation is failed hr:{0}", result);
			return result;
		}

		auto iRes = ftruncate(shm_fd, memorySize);
		if (iRes == -1)
		{
			auto result = GetLastResultCode();
			SFLog(System, Error, "SharedMemory truncate is failed hr:{0}", result);
			shm_unlink(memoryName);
			return result;
		}

		m_hMemory = shm_fd;

		m_pMemory = mmap(0, memorySize, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
		if (m_pMemory == nullptr)
		{
			shm_unlink(memoryName);
			m_hMemory = INVALID_NATIVE_HANDLE_VALUE;
			return GetLastResultCode();
		}

		m_MemorySize = memorySize;
		m_MemoryName = memoryName;

		return ResultCode::SUCCESS;
	}

	// Open Memory mapped file
	Result SharedMemory::Open(const char* memoryName, uint memorySize)
	{
		if (m_hMemory != INVALID_NATIVE_HANDLE_VALUE)
			return ResultCode::INVALID_STATE;


		auto shm_fd = shm_open(memoryName, O_RDWR, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
		if (shm_fd == -1)
		{
			auto result = GetLastResultCode();
			SFLog(System, Error, "SharedMemory creation is failed hr:{0}", result);
			return result;
		}

		m_hMemory = shm_fd;

		m_pMemory = mmap(0, memorySize, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
		if (m_pMemory == nullptr)
		{
			shm_unlink(memoryName);
			m_hMemory = INVALID_NATIVE_HANDLE_VALUE;
			return GetLastResultCode();
		}


		m_MemorySize = memorySize;
		m_MemoryName = memoryName;

		return ResultCode::SUCCESS;
	}

	// Close mapped file
	void SharedMemory::Close()
	{
		if (m_hMemory == INVALID_NATIVE_HANDLE_VALUE)
			return;

		munmap(m_pMemory, m_MemorySize);

		shm_unlink(m_MemoryName);

		m_hMemory = INVALID_NATIVE_HANDLE_VALUE;
		m_MemorySize = 0;
		m_pMemory = nullptr;
	}

}

#endif
