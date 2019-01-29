////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2018 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Vertex buffer
//
////////////////////////////////////////////////////////////////////////////////


#pragma once

#include "Resource/SFGraphicBuffer.h"

namespace SF
{

	////////////////////////////////////////////////////////////////////
	//
	//	Resource
	//
	class VertexBuffer : public GraphicBuffer
	{
	private:

	public:
		VertexBuffer(IHeap& heap, const FixedString& name);
		virtual ~VertexBuffer();


	};


	typedef SharedPointerT<VertexBuffer> VertexBufferPtr;
	extern template class SharedPointerT<VertexBuffer>;

}

