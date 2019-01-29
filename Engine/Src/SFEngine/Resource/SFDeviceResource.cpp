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
#include "Resource/SFDeviceResource.h"
#include "Graphics/SFGraphicDevice.h"


namespace SF
{
	template class SharedPointerT<DeviceResource>;
	template class WeakPointerT<DeviceResource>;


	DeviceResource::DeviceResource(IHeap& heap, GraphicDevice* pDevice, Resource* sourceResource)
		: m_Heap(heap)
		, m_GraphicDevice(pDevice)
		, m_SourceResource(sourceResource)
	{
		m_ListNodeForDevice.Data = this;

		pDevice->RegisterSharedObject(this);
	}

	DeviceResource::~DeviceResource()
	{

	}

}

