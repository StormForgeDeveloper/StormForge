////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2016 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Rendering thread
//
////////////////////////////////////////////////////////////////////////////////


#pragma once

#include "Resource/SFDeviceResource.h"
#include "Resource/SFDeviceResource.h"


namespace SF
{
	class GraphicDevice;


	////////////////////////////////////////////////////////////////////
	//
	//	Render target chain - Render buffers with present
	//

	class RenderTargetChain : public DeviceResource
	{
	private:

		IHeap& m_Heap;
		GraphicDevice* m_pGraphicDevice;

		// Number of render chain
		int m_NumberOfChain;



	protected:

		void SetNumberOfChain(int numChain) { m_NumberOfChain = numChain; }

	public:
		RenderTargetChain(IHeap& heap, GraphicDevice* pDevice);
		virtual ~RenderTargetChain();

		IHeap& GetHeap() { return m_Heap; }
		GraphicDevice* GetGraphicDevice() { return m_pGraphicDevice; }

		// Get number of chain
		int GetNumberOfChain() { return m_NumberOfChain; }

		// Initialize Render target chain
		virtual Result Initialize(int numChain, bool vsync = false) = 0;
	};




}

