////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2018 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Asset Exporter
//
////////////////////////////////////////////////////////////////////////////////


#include "SFEnginePCH.h"
#include "ResultCode/SFResultCodeSystem.h"
#include "Asset/Exporter//SFAssetExporter.h"


namespace SF
{
	template class SharedPointerT<AssetExporter>;
	template class WeakPointerT<AssetExporter>;




	AssetExporter::AssetExporter(IHeap& heap, const FixedString& name, const FixedString& exportType)
		: m_Name(name)
		, m_ExportType(exportType)
		, m_Heap(heap)
	{

	}

	AssetExporter::~AssetExporter()
	{

	}





}

