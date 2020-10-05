////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2016 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Resource Texture
//
////////////////////////////////////////////////////////////////////////////////


#pragma once

#include "Resource/SFResource.h"
#include "Resource/SFDeviceTexture.h"
#include "Resource/SFTextureFormatDescription.h"

namespace SF
{


	////////////////////////////////////////////////////////////////////
	//
	//	Texture
	//

	class Texture : public Resource
	{
	public:


		////////////////////////////////////////////////////////////////////
		//
		//	Type definitions
		//

		// Image data lock manager. help for unlock imagedata
		class LockedData
		{
		private:
			Texture *m_pTexture = nullptr;
			uint8_t* m_pImageData = nullptr;

		private:
			LockedData(Texture *pTexture, uint8_t* pImgData);

			friend class Texture;

		public:
			LockedData() {}
			LockedData(LockedData&& src);
			~LockedData();

			// Unlock
			void Unlock();

			operator uint8_t*()
			{
				return m_pImageData;
			}

			LockedData& operator =(LockedData&& src);
		};


		enum class BlackState : short
		{
			None,
			Loading,
			Loaded,
			Uploaded
		};



#pragma pack(push, 2)
		struct BlockData
		{
			int Width		: 16;
			int Height		: 16;
			int Depth		: 16;
			BlackState State;

			
		};
#pragma pack(pop)

	private:

		// element format
		TextureFormat m_Format;

		int m_Width = 0;			// Width(x)
		int m_Height = 0;			// Height(y)
		int m_Depth = 1;			// Depth(z)
		int m_FaceCount = 1;		// Faces, ex) 1 for regular 2d texture, 6 for cubemap
		int m_MipmapCount = 1;		// Mipmap level
		TextureUsage m_Usage = TextureUsage::Transient;
		size_t m_ImageFaceSize = 0;

		const TextureFormatDescription* m_pFormatDesc = nullptr;

		uint8_t *m_ImageData = nullptr;

		DeviceTexturePtr m_DeviceTexture;

	private:

		// Create device texture
		Result CreateDeviceTexture(const TextureInitParameter& initParameters);

	public:
		Texture(IHeap& heap, const CallTrack& callTrack = CallTrack());
		virtual ~Texture();

		// Clear resource
		void ClearResource();

		// Dispose
		virtual void Dispose() override;

		// Init
		Result Init(const TextureInitParameter& initParameters);

		// Calculate whole image data size
		size_t CalculateImageDataSize();

		// Returns image data ptr
		// If system texture management trait doesn't have in-memory storage flag, it will be nullptr
		LockedData LockImageData();
		LockedData LockImageData(int iFace, int iMipmap);
		void UnlockImageData();

		TextureFormat GetFormat() const { return m_Format; }
		size_t GetBytePerPixel() const;
		size_t GetWidthAlign() const;
		size_t GetWidthScanlineSize(int iWidth) const;

		int GetWidth() { return m_Width; }
		int GetHeight() { return m_Height; }
		int GetDepth() { return m_Depth; }
		int GetFaceCount() { return m_FaceCount; }
		int GetMipmapCount() { return m_MipmapCount; }


		// Get device texture instance
		DeviceTexture* GetDeviceTexture() { return *m_DeviceTexture; }

		void GetBlockSize(int levelWidth, int levelHeight, int& blockWidth, int& blockHeight);
	};


	typedef SharedPointerT<Texture> TexturePtr;
	extern template class SharedPointerT<Texture>;

}

