////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2018 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Vertex buffer
//
////////////////////////////////////////////////////////////////////////////////


#include "SFEnginePCH.h"
#include "Resource/SFVertexBuffer.h"


namespace SF
{
	template class SharedPointerT<VertexBuffer>;

	VertexBuffer::VertexBuffer(IHeap& heap, const FixedString& name)
		: GraphicBuffer(heap, name)
	{

	}

	VertexBuffer::~VertexBuffer()
	{

	}


}

