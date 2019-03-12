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
#include "ResultCode/SFResultCodeSystem.h"



namespace SF
{
	////////////////////////////////////////////////////////////////////////////////
	// 
	//	SharedMemory class
	// 
#if SF_PLATFORM != SF_PLATFORM_WINDOWS && SF_PLATFORM != SF_PLATFORM_LINUX

	SharedMemory::SharedMemory(IHeap& heap)
		: m_MemoryName(heap)
	{
		unused(m_hMemory);
		unused(m_MemoryName);
	}

	SharedMemory::~SharedMemory()
	{

	}

	// Create Memory mapped file
	Result SharedMemory::Create(const char* memoryName, uint memorySize)
	{
		return ResultCode::NOT_IMPLEMENTED;
	}

	// Open Memory mapped file
	Result SharedMemory::Open(const char* memoryName, uint mappingSize)
	{
		return ResultCode::NOT_IMPLEMENTED;
	}

	// Close mapped file
	void SharedMemory::Close()
	{
	}

#endif

}

