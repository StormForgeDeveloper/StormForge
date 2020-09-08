////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2018 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Asset Exporter
//
////////////////////////////////////////////////////////////////////////////////


#pragma once

#include "Resource/SFResource.h"
#include "Stream/SFStream.h"

namespace SF
{
	class AssetPackage;


	////////////////////////////////////////////////////////////////////
	//
	//	AssetExporter
	//
	class AssetExporter : public SharedObject
	{
	private:

		// Name of the exporter
		StringCrc64 m_Name;

		// Exporting type
		StringCrc64 m_ExportType;

		// heap for resource
		IHeap& m_Heap;

	public:
		AssetExporter(IHeap& heap, const StringCrc64& name, const StringCrc64& exportType);
		virtual ~AssetExporter();

		StringCrc64 GetName() const { return m_Name; }

		IHeap& GetHeap() { return m_Heap; }

		// It returns resource and clear pointer inside
		virtual Result Export(IOutputStream& stream, const ResourcePtr& pRes) = 0;
	};


	extern template class SharedPointerT<AssetExporter>;
	extern template class WeakPointerT<AssetExporter>;
	typedef SharedPointerT<AssetExporter> AssetExporterPtr;

}

