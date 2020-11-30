////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2018 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Asset Package
//
////////////////////////////////////////////////////////////////////////////////


#pragma once

#include "Resource/SFResource.h"
#include "Container/SFSortedArray.h"

namespace SF
{

	////////////////////////////////////////////////////////////////////
	//
	//	AssetPackage
	//		Package of resource
	//
	class AssetPackage : public SharedObject
	{
	public:

		typedef SortedArray<StringCrc64, ResourcePtr, true, false> AssetList;

		typedef SortedArray<StringCrc64, SharedPointerT<AssetPackage>, true, false> AssetPackageList;

	private:

		// Name of the exporter
		StringCrc64 m_Name;

		// heap for resource
		Heap m_Heap;

		// Asset list
		AssetList m_Assets;

		// Asset references to other package
		// If a asset referencing  external package. they need to be listed here
		// Same package can be referenced multiple times.
		AssetPackageList m_References;

	public:
		AssetPackage(IHeap& heap, const StringCrc64& name);
		virtual ~AssetPackage();

		virtual void Dispose() override;

		// Heap for this package
		IHeap& GetHeap() { return *m_Heap.get(); }

		// Get name
		StringCrc64 GetName() const { return m_Name; }

		// Add asset to the package
		// Package will hold 1 reference counter from the resource
		Result AddAsset(const SharedPointerT<Resource>& asset);

		// Remove Asset from the package
		Result RemoveAsset(const SharedPointerT<Resource>& asset);

		// Find an resource asset
		SharedPointerT<Resource> FindAsset(StringCrc64 assetName);

		// Get asset list
		AssetList& GetAssetList() { return m_Assets; }
		const AssetList& GetAssetList() const { return m_Assets; }

		AssetPackageList& GetDependencies() { return m_References; }
	};


	extern template class SharedPointerT<AssetPackage>;
	extern template class WeakPointerT<AssetPackage>;
	typedef SharedPointerT<AssetPackage> AssetPackagePtr;

}

