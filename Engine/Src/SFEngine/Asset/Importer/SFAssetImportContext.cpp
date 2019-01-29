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


	AssetImportContext::AssetImportContext(IHeap& heap, IInputStream& inputStream, const String& source)
		: m_Heap(heap)
		, m_InputStream(inputStream)
		, m_Source(source)
		, m_Variables(heap)
	{
	}

	AssetImportContext::~AssetImportContext()
	{
	}





}

