
#pragma once

#include "UMTypedef.h"
#include "UMNodeContentComponent.h"
#include "UMObject.h"

class UMTextureContent : public UMObject
{
public:

	enum class ImageFoSFat
	{
		RGB,
		RGBA,
		LUMINANCE,
		ALPHA,
		LA,
	};

	enum class TextureWrap
	{
		CLAMP,
		REPEAT
	};

public:



	UINT m_Width, m_Height;
	UINT m_BytesPerPixel;
	ImageFoSFat m_ImageFoSFat;

	UINT m_devILImage;

	BYTE *m_pImageData;

	UMTransfoSFMatrix m_TexTransfoSF;

	TextureWrap m_WrapU;
	TextureWrap m_WrapV;

	UMString m_UVSetName;

public:

	// Constructor
	UMTextureContent();
	virtual ~UMTextureContent();


	UINT GetWidth()					{ return m_Width; }
	UINT GetHeight()				{ return m_Height; }
	UINT GetBPP()					{ return m_BytesPerPixel; }
	ImageFoSFat GetImageFoSFat()	{ return m_ImageFoSFat; }

	const BYTE* GetImageData()		{ return m_pImageData; }

	const UMTransfoSFMatrix& GetTransfoSF()	{ return m_TexTransfoSF; }
	void SetTransfoSF(const UMTransfoSFMatrix& transfoSF)	{ m_TexTransfoSF = transfoSF; }

	TextureWrap GetWrapU()			{ return m_WrapU; }
	TextureWrap GetWrapV()			{ return m_WrapV; }
	void SetWrappingMode(TextureWrap wrapModeU, TextureWrap wrapModeV)	{ m_WrapU = wrapModeU; m_WrapV = wrapModeV; }

	const UMString& GetUVSetName()	{ return m_UVSetName; }
	void SetUVSetName(const UMString& UVSetName)	{ m_UVSetName = UVSetName; }


	// Set texture data
	void SetTextureData( UINT devILImage, ImageFoSFat textureFoSFat, int width, int height, void* pData );
};




