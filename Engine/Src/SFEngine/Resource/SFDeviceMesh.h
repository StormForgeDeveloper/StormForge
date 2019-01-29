////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2018 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Device Mesh
//
////////////////////////////////////////////////////////////////////////////////


#pragma once

#include "Resource/SFDeviceResource.h"


namespace SF
{
	class Mesh;


	////////////////////////////////////////////////////////////////////
	//
	//	DeviceMesh
	//
	class DeviceMesh : public DeviceResource
	{
	public:


	private:

		uint32_t m_SystemFormat;
		int m_BlockWidth;			// Width
		int m_BlockHeight;			// Height
		int m_BlockDepth;			// Depth

	public:
		DeviceMesh(IHeap& heap, GraphicDevice* pDevice, Mesh* sourceResource);
		virtual ~DeviceMesh();

		void UploadBlock(uint8_t* blockData, int blockX, int blockY, int blockZ);

	};


	typedef SharedPointerT<DeviceMesh> DeviceMeshPtr;
	extern template class SharedPointerT<DeviceMesh>;

}

