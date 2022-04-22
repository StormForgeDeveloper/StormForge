////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : BSON warper
//	
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "SFTypedefs.h"
#include "Util/SFStringCrc32.h"
#include "Util/SFString.h"
#include "MemoryManager/SFHeapMemory.h"

#include <bson/bson.h>


typedef struct _bson_t bson_t;

namespace SF
{


	// SF deleter
	struct BsonDeleter {
		constexpr BsonDeleter() noexcept = default;
		void operator()(bson_t* _Ptr) const noexcept;
	};
	using BsonUniquePtr = std::unique_ptr<bson_t, BsonDeleter>;


	class ScopeBsonHeap : public bson_mem_vtable_t
	{
	public:

		ScopeBsonHeap(IHeap& parent);

		~ScopeBsonHeap();

	private:

		IHeap& m_Heap;
	};


	template<size_t StaticMemorySize>
	class ScopeBsonHeapT : public ScopeBsonHeap
	{
	public:

		ScopeBsonHeapT(StringCrc64 nameCrc, IHeap& parent)
			: ScopeBsonHeap(m_LocalHeapMemory)
			, m_LocalHeapMemory(nameCrc, parent)
		{}

		~ScopeBsonHeapT() = default;

	private:

		StaticMemoryAllocatorT<StaticMemorySize> m_LocalHeapMemory;

	};

}


