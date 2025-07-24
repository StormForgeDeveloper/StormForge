////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2016 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Resource Texture
//
////////////////////////////////////////////////////////////////////////////////


#include "SFEnginePCH.h"
#include "Resource/SFTexture.h"
#include "Resource/SFTextureFormatDescription.h"
#include "Service/SFEngineService.h"


namespace SF
{

	template class SharedPointerT<Texture>;



	Texture::LockedData::LockedData(Texture *pTexture, uint8_t* pImgData)
		: m_pTexture(pTexture)
		, m_pImageData(pImgData)
	{
	}

	Texture::LockedData::LockedData(LockedData&& src)
		: m_pTexture(src.m_pTexture)
		, m_pImageData(src.m_pImageData)
	{
		src.m_pTexture = nullptr;
		src.m_pImageData = nullptr;
	}

	Texture::LockedData::~LockedData()
	{
		Unlock();
	}

	void Texture::LockedData::Unlock()
	{
		if (m_pTexture == nullptr || m_pImageData == nullptr)
			return;

		m_pTexture->UnlockImageData();
		m_pTexture = nullptr;
		m_pImageData = nullptr;
	}

	Texture::LockedData& Texture::LockedData::operator =(LockedData&& src)
	{
		Unlock();

		m_pTexture = src.m_pTexture;
		m_pImageData = src.m_pImageData;
		src.m_pTexture = nullptr;
		src.m_pImageData = nullptr;

		return *this;
	}




	Texture::Texture(const CallTrack& callTrack)
		: Resource("Texture", callTrack)
		, m_Format(TextureFormat::INVALID)
	{
	}

	Texture::~Texture()
	{
		ClearResource();
	}

	void Texture::ClearResource()
	{
		delete[] (m_ImageData);
		m_ImageData = nullptr;
	}

	void Texture::Dispose()
	{
		ClearResource();
		Resource::Dispose();
	}

	Texture::LockedData Texture::LockImageData()
	{
		// TODO: Need to handle device memory
		return LockedData(this,m_ImageData);
	}

	Texture::LockedData Texture::LockImageData(int iFace, int iMipmap)
	{
		if (m_ImageData == nullptr)
			return LockedData();

		if (iFace < 0 || iMipmap < 0)
			return LockedData();

		int width = m_Width;
		int height = m_Height;
		int iCurMipmap = 0;
		auto bpp = GetBytePerPixel();
		auto widthAlign = GetWidthAlign();

		auto pFace = m_ImageData + m_ImageFaceSize * iFace;
		size_t imageOffset = 0;
		for (; width >= 1 || height >= 1; width >>= 1, height >>= 1, iCurMipmap++)
		{
			if (width == 0) width = 1;
			if (height == 0) height = 1;
			if (iCurMipmap == iMipmap)
				break;

			auto widthSize = width * bpp;
			widthSize = AlignUp(widthSize, widthAlign);
			imageOffset += widthSize * height;
		}

		return LockedData(this, pFace + imageOffset);
	}

	void Texture::UnlockImageData()
	{
		// flush image data to device
	}

	// Create device texture
	Result Texture::CreateDeviceTexture(const TextureInitParameter& initParameter)
	{
		m_DeviceTexture = Service::GraphicDevice->CreateTexture(initParameter);
		if (m_DeviceTexture == nullptr)
			return ResultCode::OUT_OF_MEMORY;

		//m_DeviceTexture->

		return ResultCode::SUCCESS;
	}

	Result Texture::Init(const TextureInitParameter& initParameters)
	{
		ClearResource();

		auto pDesc = TextureFormatDescription::GetDescriptor(initParameters.Format);
		if (pDesc == nullptr)
			return ResultCode::NOT_SUPPORTED_FORMAT;

		if (initParameters.Width <= 0 || initParameters.Height <= 0 || initParameters.FaceCount <= 0)
			return ResultCode::INVALID_ARG;

		auto bpp = pDesc->BytesPerPixel;
		auto widthAlign = pDesc->WidthAlignment;
		size_t imageSize = 0;
		int numMipmap = 0;

		m_pFormatDesc = pDesc;
		m_Width = initParameters.Width;
		m_Height = initParameters.Height;
		m_Depth = 1;
		m_FaceCount = initParameters.FaceCount;
		m_Usage = initParameters.Usage;

		int width = initParameters.Width;
		int height = initParameters.Height;

		if (initParameters.UseMipmap)
		{
			for (; width >= 1 || height >= 1; width >>= 1, height >>= 1, numMipmap++)
			{
				if (width == 0) width = 1;
				if (height == 0) height = 1;

				auto widthSize = width * bpp;
				widthSize = AlignUp(widthSize, widthAlign);
				imageSize += widthSize * height;
			}
		}
		else
		{
			auto widthSize = width * bpp;
			widthSize = AlignUp(widthSize, widthAlign);
			imageSize += widthSize * height;
		}
		m_ImageFaceSize = imageSize * m_Depth;
		m_MipmapCount = numMipmap;

		m_ImageData = new uint8_t[m_ImageFaceSize * m_FaceCount];


		return CreateDeviceTexture(initParameters);
	}

	// Calculate whole image data size
	size_t Texture::CalculateImageDataSize()
	{
		auto width = m_Width;
		auto height = m_Height;
		size_t imageSize = 0;
		for (int iMipmap = 0; iMipmap < m_MipmapCount && (width >= 1 || height >= 1); width >>= 1, height >>= 1, iMipmap++)
		{
			if (width == 0) width = 1;
			if (height == 0) height = 1;

			auto widthSize = GetWidthScanlineSize(width);
			imageSize += widthSize * height;
		}

		imageSize *= m_Depth * m_FaceCount;

		return imageSize;
	}


	size_t Texture::GetBytePerPixel() const
	{
		if (m_pFormatDesc == nullptr)
			return 0;

		return m_pFormatDesc->BytesPerPixel;
	}

	size_t Texture::GetWidthAlign() const
	{
		if (m_pFormatDesc == nullptr)
			return 0;

		return m_pFormatDesc->WidthAlignment;
	}

	size_t Texture::GetWidthScanlineSize(int iWidth) const
	{
		if (m_pFormatDesc == nullptr)
			return 0;

		auto widthSize = m_pFormatDesc->BytesPerPixel * iWidth;
		widthSize = AlignUp(widthSize,m_pFormatDesc->WidthAlignment);

		return widthSize;
	}


	void Texture::GetBlockSize(int levelWidth, int levelHeight, int& blockWidth, int& blockHeight)
	{

	}



}

