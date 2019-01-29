////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2018 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Device mesh
//
////////////////////////////////////////////////////////////////////////////////


#include "SFEnginePCH.h"
#include "Resource/SFDeviceMesh.h"
#include "Resource/SFMesh.h"


namespace SF
{
	template class SharedPointerT<DeviceMesh>;

	DeviceMesh::DeviceMesh(IHeap& heap, GraphicDevice* pDevice, Mesh* sourceResource)
		: DeviceResource(heap, pDevice, sourceResource)

	{

	}

	DeviceMesh::~DeviceMesh()
	{

	}

}

