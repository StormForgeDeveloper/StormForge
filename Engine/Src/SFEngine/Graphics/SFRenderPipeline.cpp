////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2017 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Render Pipeline
//
////////////////////////////////////////////////////////////////////////////////


#include "SFEnginePCH.h"
#include "Graphics/SFRenderPipeline.h"


namespace SF
{

	RenderPipeline::RenderPipeline(IHeap& heap)
		: m_Heap(heap)
		, m_Stages(heap)
	{

	}

	RenderPipeline::~RenderPipeline()
	{

	}


}

