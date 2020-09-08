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
#include "Asset/Importer/SFAssetImporter.h"
#include "String/SFStrUtil.h"

namespace SF
{

	AssetImporter::AssetImporter(IHeap& heap, const StringCrc64& name)
		: m_Name(name)
		, m_Heap(heap)
		, m_AssetTypes(heap)
	{
	}

	AssetImporter::~AssetImporter()
	{
	}

	// Add Asset type 
	void AssetImporter::AddAssetType(const char* pAssetType)
	{
		if (pAssetType == nullptr)
			return;

		char stringBuff[128];
		int strBufLen = 128;
		char* pStrBuff = stringBuff;
		StrUtil::StringLower(pStrBuff, strBufLen, pAssetType);

		m_AssetTypes.push_back(stringBuff);
	}



}

