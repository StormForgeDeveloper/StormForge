////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2017 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Shared memory
//
////////////////////////////////////////////////////////////////////////////////

#pragma once


#include "String/SFString.h"


namespace SF
{
	////////////////////////////////////////////////////////////////////////////////
	// 
	//	SharedMemory class
	//		- Wrapper of memory mapped file which is inter-process shared memory
	//

	class SharedMemory
	{
	private:

		// Native file handle
		NativeHandle m_hMemory = INVALID_NATIVE_HANDLE_VALUE;

		// Shared memory name
		String m_MemoryName;

		// Shared memory size
		uint m_MemorySize = 0;

		// Mapped memory pointer
		void* m_pMemory = nullptr;

	public:

		SharedMemory(IHeap& heap);
		virtual ~SharedMemory();

		NativeHandle GetMemoryHandle() const { return m_hMemory; }
		const String& GetMemoryName() const { return m_MemoryName; }
		uint GetMemorySize() const { return m_MemorySize; }

		// Create Memory mapped file
		//@memoryName: Shared memory name.
		//@memorySize: Shared memory size.
		Result Create(const char* memoryName, uint memorySize);

		// Open Memory mapped file
		//@memoryName: Shared memory name.
		//@memorySize: Shared memory size.
		Result Open(const char* memoryName, uint mappingSize);

		// Close mapped file
		void Close();

		// Get mapped pointer
		void* GetPointer() { return m_pMemory; }
	};
}


