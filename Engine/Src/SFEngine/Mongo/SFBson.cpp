////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c)  Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : BSON
//	
//
////////////////////////////////////////////////////////////////////////////////

#include "SFEnginePCH.h"

#include "Mongo/SFBson.h"
#include "Util/SFStringFormat.h"


#include <bson/bson.h>



namespace SF
{

	void BsonDeleter::operator()(bson_t* _Ptr) const noexcept
	{
		if (_Ptr) bson_destroy(_Ptr);
	}


	ScopeBsonHeap::ScopeBsonHeap(IHeap& parent)
		: m_Heap(parent)
	{
		memset(static_cast<bson_mem_vtable_t*>(this), 0, sizeof(bson_mem_vtable_t));

		// TODO:
		//void* (*malloc) (size_t num_bytes);
		//void* (*calloc) (size_t n_members, size_t num_bytes);
		//void* (*realloc) (void* mem, size_t num_bytes);
		//void (*free) (void* mem);

		bson_mem_set_vtable(this);
	}

	ScopeBsonHeap::~ScopeBsonHeap()
	{
		bson_mem_restore_vtable();
	}

}


