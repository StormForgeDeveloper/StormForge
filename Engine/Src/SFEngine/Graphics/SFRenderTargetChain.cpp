////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2017 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Render target chain
//
////////////////////////////////////////////////////////////////////////////////


#include "SFEnginePCH.h"
#include "Graphics/SFRenderTargetChain.h"


namespace SF
{

	RenderTargetChain::RenderTargetChain(IHeap& heap, GraphicDevice* pDevice)
		: DeviceResource(heap, pDevice, nullptr)
		, m_Heap(heap)
		, m_pGraphicDevice(pDevice)
		, m_NumberOfChain(0)
	{
	}

	RenderTargetChain::~RenderTargetChain()
	{
	}

}

