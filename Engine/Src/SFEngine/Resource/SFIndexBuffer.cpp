////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2018 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Index buffer
//
////////////////////////////////////////////////////////////////////////////////


#include "SFEnginePCH.h"
#include "Resource/SFIndexBuffer.h"


namespace SF
{
	template class SharedPointerT<IndexBuffer>;

	
	IndexBuffer::IndexBuffer(IHeap& heap, const StringCrc64& name)
		: GraphicBuffer(heap, name)
	{

	}

	IndexBuffer::~IndexBuffer()
	{

	}

}

