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
#include "Resource/SFDeviceTexture.h"
#include "Resource/SFTexture.h"


namespace SF
{
	template class SharedPointerT<DeviceTexture>;

	DeviceTexture::DeviceTexture(IHeap& heap, GraphicDevice* pDevice, Texture* sourceResource)
		: DeviceResource(heap, pDevice, sourceResource)

	{

	}

	DeviceTexture::~DeviceTexture()
	{

	}

}

