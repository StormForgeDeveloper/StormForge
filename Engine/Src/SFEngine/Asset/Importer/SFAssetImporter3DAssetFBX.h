////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2018 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : FBX asset Importer
//
////////////////////////////////////////////////////////////////////////////////


#pragma once

#include "Asset/Importer/SFAssetImporter3DAsset.h"

#if SF_PLATFORM == SF_PLATFORM_WINDOWS

namespace fbxsdk
{
	class FbxManager;
	class FbxScene;
	class FbxDocument;
}

namespace SF
{


	////////////////////////////////////////////////////////////////////
	//
	//	AssetImporter
	//
	class AssetImporter3DAssetFBX : public AssetImporter3DAsset
	{
	private:

		// FBX sdk manager
		fbxsdk::FbxManager* m_pSdkManager = nullptr;



	private:

		void InitializeSDKManager();
		Result LoadScene(fbxsdk::FbxDocument* pScene, IInputStream& stream);

	public:
		AssetImporter3DAssetFBX(IHeap& heap);
		virtual ~AssetImporter3DAssetFBX();


		// It returns resource and clear pointer inside
		virtual Result Import(AssetImportContext& context, Array<ResourcePtr>& resources);
	};


}

#endif
