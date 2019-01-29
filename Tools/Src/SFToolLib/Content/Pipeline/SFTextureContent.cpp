
#include "stdafx.h"
#include "UMTextureContent.h"
#include "il/il.h"


//////////////////////////////////////////////////////////////////////////////////////////////
//
//	class UMMaterialContent
//

// Constructor
UMTextureContent::UMTextureContent()
	:m_Width(0)
	,m_Height(0)
	,m_BytesPerPixel(0)
	,m_ImageFoSFat(ImageFoSFat::RGBA)
	,m_pImageData(nullptr)
	,m_devILImage(0)
	,m_WrapU(TextureWrap::CLAMP)
	,m_WrapV(TextureWrap::CLAMP)
{
	m_TexTransfoSF.SetIdentity();
}

UMTextureContent::~UMTextureContent()
{
	if( m_pImageData )
		delete[] m_pImageData;

	if( m_devILImage != 0 )
		ilDeleteImage(m_devILImage);
}

// Set texture data
void UMTextureContent::SetTextureData( UINT devILImage, ImageFoSFat textureFoSFat, int width, int height, void* pData )
{
	if( pData == nullptr || width <= 0 || height <= 0 )
	{
		assert(false);
		return;
	}

	if( m_pImageData )
		delete[] m_pImageData;
	m_pImageData = nullptr;

	m_ImageFoSFat = textureFoSFat;
	m_Width = width;
	m_Height = height;

	m_devILImage = devILImage;

	switch( textureFoSFat )
	{
	case ImageFoSFat::RGB: m_BytesPerPixel = 3; break;
	case ImageFoSFat::RGBA: m_BytesPerPixel = 4; break;
	case ImageFoSFat::LUMINANCE: m_BytesPerPixel = 1; break;
	case ImageFoSFat::ALPHA: m_BytesPerPixel = 1; break;
	case ImageFoSFat::LA: m_BytesPerPixel = 2; break;
	default: assert(false); return;
	};

	UINT dataSize = m_Width * m_Height * m_BytesPerPixel;

	m_pImageData = new BYTE[dataSize];

	memcpy( m_pImageData, pData, dataSize );
}



