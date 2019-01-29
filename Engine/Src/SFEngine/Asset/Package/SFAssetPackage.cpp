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
#include "Asset/Package/SFAssetPackage.h"


namespace SF
{
	template class SharedPointerT<AssetPackage>;
	template class WeakPointerT<AssetPackage>;


	AssetPackage::AssetPackage(IHeap& heap, const FixedString& name)
		: m_Name(name)
		, m_Heap("name", heap)
		, m_Assets(m_Heap)
		, m_References(m_Heap)
	{
	}

	AssetPackage::~AssetPackage()
	{

	}

	void AssetPackage::Dispose()
	{
		// TODO: release all
		m_Assets.Clear();
		m_References.Clear();
	}

	// It returns resource and clear pointer inside
	Result AssetPackage::AddAsset(const SharedPointerT<Resource>& asset)
	{
		if (asset == nullptr)
			return ResultCode::INVALID_ARG;

		return m_Assets.Insert(asset->GetName(), asset);
	}

	Result AssetPackage::RemoveAsset(const SharedPointerT<Resource>& asset)
	{
		if (asset == nullptr)
			return ResultCode::INVALID_ARG;

		ResourcePtr removed;
		auto result = m_Assets.Remove(asset->GetName(), removed);

		if (result && removed != asset)
		{
			Assert(false);
			return ResultCode::UNEXPECTED;
		}

		return result;
	}

	SharedPointerT<Resource> AssetPackage::FindAsset(FixedString assetName)
	{
		ResourcePtr found;
		m_Assets.Find(assetName, found);
		return found;
	}



}

