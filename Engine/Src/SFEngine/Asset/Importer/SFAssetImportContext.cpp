////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2018 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Asset Importer
//
////////////////////////////////////////////////////////////////////////////////


#include "SFEnginePCH.h"
#include "ResultCode/SFResultCodeSystem.h"
#include "Asset/Importer//SFAssetImportContext.h"


namespace SF
{


	////////////////////////////////////////////////////////////////////
	//
	//	AssetImportContext
	//


	AssetImportContext::AssetImportContext(IInputStream& inputStream, const String& source)
		: m_InputStream(inputStream)
		, m_Source(source)
	{
	}

	AssetImportContext::~AssetImportContext()
	{
	}





}

