////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2016 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Resource base
//
////////////////////////////////////////////////////////////////////////////////


#include "SFEnginePCH.h"
#include "Resource/SFResource.h"


namespace SF
{
	template class SharedPointerT<Resource>;
	template class WeakPointerT<Resource>;

	Resource::Resource(IHeap& heap, StringCrc64 resType, const CallTrack& callTrack)
		: m_Name("")
		, m_ResourceType(resType)
		, m_Heap(heap)
		, m_CallTrack(callTrack)
	{

	}

	Resource::~Resource()
	{

	}


}

