////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2018 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Device texture
//
////////////////////////////////////////////////////////////////////////////////


#pragma once

#include "Resource/SFTextureFormat.h"
#include "Resource/SFDeviceResource.h"
#include "Container/SFCircularPageQueue.h"

namespace SF
{
	class Texture;




	////////////////////////////////////////////////////////////////////
	//
	//	DeviceTexture
	//
	class DeviceTexture : public DeviceResource
	{
	public:


	private:

		uint32_t m_SystemFormat;	// 
		int m_BlockWidth;			// Width
		int m_BlockHeight;			// Height
		int m_BlockDepth;			// Depth

	public:
		DeviceTexture(IHeap& heap, GraphicDevice* pDevice, Texture* sourceResource);
		virtual ~DeviceTexture();

		void UploadBlock(uint8_t* blockData, int blockX, int blockY, int blockZ);

		// GetDevice Texture format
		// This function made best guess for the texture
		static uint32_t GetDeviceFormatFor(TextureFormat format);
	};


	typedef SharedPointerT<DeviceTexture> DeviceTexturePtr;
	extern template class SharedPointerT<DeviceTexture>;

}

