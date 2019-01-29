////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2018 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Index buffer
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
	class IndexBuffer : public GraphicBuffer
	{
	private:

	public:
		IndexBuffer(IHeap& heap, const FixedString& name);
		virtual ~IndexBuffer();


	};


	typedef SharedPointerT<IndexBuffer> IndexBufferPtr;
	extern template class SharedPointerT<IndexBuffer>;

}

