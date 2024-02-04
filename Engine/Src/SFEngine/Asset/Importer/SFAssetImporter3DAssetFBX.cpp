////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2018 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : FBX asset Importer
//
////////////////////////////////////////////////////////////////////////////////


#include "SFEnginePCH.h"
#include "ResultCode/SFResultCodeSystem.h"
#include "ResultCode/SFResultCodeLibrary.h"
#include "Asset/Importer/SFAssetImporter3DAssetFBX.h"
#include "Resource/SFMesh.h"
#include "Resource/SFAnimation.h"
#include "Stream/SFMemoryStream.h"

#if SF_USE_FBX

#define FBXSDK_SHARED
#include "fbxsdk.h"



namespace SF
{

	namespace ImplFBX
	{

		// stream class wrapper
		class FBXStreamWrapper : public fbxsdk::FbxStream
		{
		private:

			int64_t m_StartPosition = 0;
			IInputStream& m_Stream;

		public:

			FBXStreamWrapper(IInputStream& steam)
				: m_Stream(steam)
			{
				m_StartPosition = m_Stream.GetPosition();
			}

			/** Query the current state of the stream. */
			virtual EState GetState()
			{
				if (m_Stream.CanRead())
				{
					return EState::eOpen;
				}
				else
				{
					return EState::eClosed;
				}
			}

			/** Open the stream.
			* \return True if successful.
			* \remark Each time the stream is open or closed, the stream position must be reset to zero. */
			virtual bool Open(void* pStreamData)
			{
				unused(pStreamData);
				m_Stream.Seek(SeekMode::Begin, 0);
				return true;
			}

			/** Close the stream.
			* \return True if successful.
			* \remark Each time the stream is open or closed, the stream position must be reset to zero. */
			virtual bool Close()
			{
				return true;
			}

			/** Empties the internal data of the stream.
			* \return True if successful. */
			virtual bool Flush()
			{
				return true;
			}

			/** Writes a memory block.
			* \param pData Pointer to the memory block to write.
			* \param pSize Size (in bytes) of the memory block to write.
			* \return The number of bytes written in the stream. */
			virtual int Write(const void* /*pData*/, int /*pSize*/)
			{
				return 0;
			}

			/** Read bytes from the stream and store them in the memory block.
			* \param pData Pointer to the memory block where the read bytes are stored.
			* \param pSize Number of bytes read from the stream.
			* \return The actual number of bytes successfully read from the stream. */
			virtual int Read(void* pData, int pSize) const
			{
				if (m_Stream.Read(pData, pSize))
					return pSize;

				return -1;
			}

			/** If not specified by KFbxImporter::Initialize(), the importer will ask
			* the stream to select an appropriate reader ID to associate with the stream.
			* FbxIOPluginRegistry can be used to locate id by extension or description.
			* Return -1 to allow FBX to select an appropriate default. */
			virtual int GetReaderID() const
			{
				return -1;
			}

			/** If not specified by KFbxExporter::Initialize(), the exporter will ask
			* the stream to select an appropriate writer ID to associate with the stream.
			* KFbxIOPluginRegistry can be used to locate id by extension or description.
			* Return -1 to allow FBX to select an appropriate default. */
			virtual int GetWriterID() const
			{
				return -1;
			}

			/** Adjust the current stream position.
			* \param pSeekPos Pre-defined position where offset is added (FbxFile::eBegin, FbxFile::eCurrent:, FbxFile::eEnd)
			* \param pOffset Number of bytes to offset from pSeekPos. */
			virtual void Seek(const FbxInt64& pOffset, const FbxFile::ESeekPos& pSeekPos)
			{
				static const SeekMode ToSFSeekPos[] =
				{
					SeekMode::Begin,
					SeekMode::Current,
					SeekMode::End
				};

				m_Stream.Seek(ToSFSeekPos[pSeekPos], pOffset);
			}

			/** Get the current stream position.
			* \return Current number of bytes from the beginning of the stream. */
			virtual long GetPosition() const
			{
				return (long)(m_Stream.GetPosition() - m_StartPosition);
			}

			/** Set the current stream position.
			* \param pPosition Number of bytes from the beginning of the stream to seek to. */
			virtual void SetPosition(long pPosition)
			{
				m_Stream.Seek(SeekMode::Begin, pPosition - m_StartPosition);
			}

			/** Return 0 if no errors occurred. Otherwise, return 1 to indicate
			* an error. This method will be invoked whenever FBX needs to verify
			* that the last operation succeeded. */
			virtual int GetError() const
			{
				return 0;
			}

			/** Clear current error condition by setting the current error value to 0. */
			virtual void ClearError()
			{
			}

		};



		void ExtractContent(FbxScene* pScene);
		void ExtractContent(FbxNode* pNode);
		void ExtractTarget(FbxNode* pNode);
		void ExtractMarker(FbxNode* pNode);
		void ExtractTransformPropagation(FbxNode* pNode);
		void ExtractGeometricTransform(FbxNode* pNode);
		void ExtractMetaData(FbxScene* pScene);

		void ExtractContent(FbxScene* pScene)
		{
			int i;
			FbxNode* lNode = pScene->GetRootNode();

			if (lNode)
			{
				for (i = 0; i < lNode->GetChildCount(); i++)
				{
					ExtractContent(lNode->GetChild(i));
				}
			}
		}

		void ExtractContent(FbxNode* pNode)
		{
			FbxNodeAttribute::EType lAttributeType;
			int i;

			if (pNode->GetNodeAttribute() == NULL)
			{
				FBXSDK_printf("NULL Node Attribute\n\n");
			}
			else
			{
				lAttributeType = (pNode->GetNodeAttribute()->GetAttributeType());

				switch (lAttributeType)
				{
				default:
					break;
				case FbxNodeAttribute::eMarker:
					//ExtractMarker(pNode);
					break;

				case FbxNodeAttribute::eSkeleton:
					//DisplaySkeleton(pNode);
					break;

				case FbxNodeAttribute::eMesh:
					//DisplayMesh(pNode);
					break;

				case FbxNodeAttribute::eNurbs:
					//DisplayNurb(pNode);
					break;

				case FbxNodeAttribute::ePatch:
					//DisplayPatch(pNode);
					break;

				case FbxNodeAttribute::eCamera:
					//DisplayCamera(pNode);
					break;

				case FbxNodeAttribute::eLight:
					//DisplayLight(pNode);
					break;

				case FbxNodeAttribute::eLODGroup:
					//DisplayLodGroup(pNode);
					break;
				}
			}

			//DisplayUserProperties(pNode);
			ExtractTarget(pNode);
			//DisplayPivotsAndLimits(pNode);
			ExtractTransformPropagation(pNode);
			ExtractGeometricTransform(pNode);

			for (i = 0; i < pNode->GetChildCount(); i++)
			{
				ExtractContent(pNode->GetChild(i));
			}
		}

		void ExtractMarker(FbxNode* pNode)
		{
			//pNode->GetMar
		}

		void ExtractTarget(FbxNode* pNode)
		{
			if (pNode->GetTarget() != NULL)
			{
				//DisplayString("    Target Name: ", (char *)pNode->GetTarget()->GetName());
			}
		}

		void ExtractTransformPropagation(FbxNode* pNode)
		{
			FBXSDK_printf("    Transformation Propagation\n");

			// 
			// Rotation Space
			//
			EFbxRotationOrder lRotationOrder;
			pNode->GetRotationOrder(FbxNode::eSourcePivot, lRotationOrder);

			FBXSDK_printf("        Rotation Space: ");

			switch (lRotationOrder)
			{
			case eEulerXYZ:
				FBXSDK_printf("Euler XYZ\n");
				break;
			case eEulerXZY:
				FBXSDK_printf("Euler XZY\n");
				break;
			case eEulerYZX:
				FBXSDK_printf("Euler YZX\n");
				break;
			case eEulerYXZ:
				FBXSDK_printf("Euler YXZ\n");
				break;
			case eEulerZXY:
				FBXSDK_printf("Euler ZXY\n");
				break;
			case eEulerZYX:
				FBXSDK_printf("Euler ZYX\n");
				break;
			case eSphericXYZ:
				FBXSDK_printf("Spheric XYZ\n");
				break;
			}

			//
			// Use the Rotation space only for the limits
			// (keep using eEulerXYZ for the rest)
			//
			FBXSDK_printf("        Use the Rotation Space for Limit specification only: %s\n",
				pNode->GetUseRotationSpaceForLimitOnly(FbxNode::eSourcePivot) ? "Yes" : "No");


			//
			// Inherit Type
			//
			FbxTransform::EInheritType lInheritType;
			pNode->GetTransformationInheritType(lInheritType);

			FBXSDK_printf("        Transformation Inheritance: ");

			switch (lInheritType)
			{
			case FbxTransform::eInheritRrSs:
				FBXSDK_printf("RrSs\n");
				break;
			case FbxTransform::eInheritRSrs:
				FBXSDK_printf("RSrs\n");
				break;
			case FbxTransform::eInheritRrs:
				FBXSDK_printf("Rrs\n");
				break;
			}
		}

		void ExtractGeometricTransform(FbxNode* pNode)
		{
			FbxVector4 lTmpVector;

			lTmpVector = pNode->GetGeometricTranslation(FbxNode::eSourcePivot);
			lTmpVector = pNode->GetGeometricRotation(FbxNode::eSourcePivot);
			lTmpVector = pNode->GetGeometricScaling(FbxNode::eSourcePivot);
		}


		void ExtractMetaData(FbxScene* pScene)
		{
			FbxDocumentInfo* sceneInfo = pScene->GetSceneInfo();
			if (sceneInfo)
			{
				FBXSDK_printf("\n\n--------------------\nMeta-Data\n--------------------\n\n");
				FBXSDK_printf("    Title: %s\n", sceneInfo->mTitle.Buffer());
				FBXSDK_printf("    Subject: %s\n", sceneInfo->mSubject.Buffer());
				FBXSDK_printf("    Author: %s\n", sceneInfo->mAuthor.Buffer());
				FBXSDK_printf("    Keywords: %s\n", sceneInfo->mKeywords.Buffer());
				FBXSDK_printf("    Revision: %s\n", sceneInfo->mRevision.Buffer());
				FBXSDK_printf("    Comment: %s\n", sceneInfo->mComment.Buffer());
			}
		}

	}


	AssetImporter3DAssetFBX::AssetImporter3DAssetFBX(IHeap& heap)
		: AssetImporter3DAsset(heap, "AssetImporter3DAssetFBX")
	{
		AddAssetType("fbx");

		InitializeSDKManager();
	}


	void AssetImporter3DAssetFBX::InitializeSDKManager()
	{
		if (m_pSdkManager != nullptr)
			return;

		//The first thing to do is to create the FBX Manager which is the object allocator for almost all the classes in the SDK
		m_pSdkManager = fbxsdk::FbxManager::Create();
		if (m_pSdkManager == nullptr)
			return;
		
		SFLog(System, Info, "FBX SDK manager initialized, SDK version {0}", m_pSdkManager->GetVersion());

		//Create an IOSettings object. This object holds all import/export settings.
		fbxsdk::FbxIOSettings* ios = fbxsdk::FbxIOSettings::Create(m_pSdkManager, IOSROOT);
		m_pSdkManager->SetIOSettings(ios);

		//Load plugins from the executable directory (optional)
		fbxsdk::FbxString lPath = fbxsdk::FbxGetApplicationDirectory();
		m_pSdkManager->LoadPluginsDirectory(lPath.Buffer());

		// Set the import states. By default, the import states are always set to 
		// true. The code below shows how to change these states.
		auto iosSetting = m_pSdkManager->GetIOSettings();
		iosSetting->SetBoolProp(IMP_FBX_MATERIAL, true);
		iosSetting->SetBoolProp(IMP_FBX_TEXTURE, true);
		iosSetting->SetBoolProp(IMP_FBX_LINK, true);
		iosSetting->SetBoolProp(IMP_FBX_SHAPE, true);
		iosSetting->SetBoolProp(IMP_FBX_GOBO, true);
		iosSetting->SetBoolProp(IMP_FBX_ANIMATION, true);
		iosSetting->SetBoolProp(IMP_FBX_GLOBAL_SETTINGS, true);
	}

	AssetImporter3DAssetFBX::~AssetImporter3DAssetFBX()
	{
		if (m_pSdkManager != nullptr)
			m_pSdkManager->Destroy();
	}


	Result AssetImporter3DAssetFBX::LoadScene(fbxsdk::FbxDocument* pScene, IInputStream& stream)
	{
		int lFileMajor, lFileMinor, lFileRevision;
		int lSDKMajor, lSDKMinor, lSDKRevision;
		//int lFileFormat = -1;
		bool lStatus;

		// Get the file version number generate by the FBX SDK.
		fbxsdk::FbxManager::GetFileFormatVersion(lSDKMajor, lSDKMinor, lSDKRevision);

		// Create an importer.
		fbxsdk::FbxImporter* pImporter = fbxsdk::FbxImporter::Create(m_pSdkManager, "");

		ImplFBX::FBXStreamWrapper fbxStream(stream);

		// Initialize the importer.
		//pImporter->FileOpen(&fbxStream);
		const bool lImportStatus = pImporter->Initialize(&fbxStream, nullptr, -1, m_pSdkManager->GetIOSettings());
		pImporter->GetFileVersion(lFileMajor, lFileMinor, lFileRevision);

		if (!lImportStatus)
		{
			fbxsdk::FbxString error = pImporter->GetStatus().GetErrorString();
			SFLog(System, Info,"FBX failed to load, error:{0}", error.Buffer());

			if (pImporter->GetStatus().GetCode() == fbxsdk::FbxStatus::eInvalidFileVersion)
			{
				SFLog(System, Info, "FBX Version not supported file version:{0}.{1}.{2}", lFileMajor, lFileMinor, lFileRevision);
			}

			return false;
		}

		if (!pImporter->IsFBX())
			return ResultCode::INVALID_FORMAT;

		{
			//FBXSDK_printf("Animation Stack Information\n");

			//lAnimStackCount = pImporter->GetAnimStackCount();

			//FBXSDK_printf("    Number of Animation Stacks: %d\n", lAnimStackCount);
			//FBXSDK_printf("    Current Animation Stack: \"%s\"\n", pImporter->GetActiveAnimStackName().Buffer());
			//FBXSDK_printf("\n");

			//for (i = 0; i < lAnimStackCount; i++)
			//{
			//	fbxsdk::FbxTakeInfo* lTakeInfo = pImporter->GetTakeInfo(i);

			//	FBXSDK_printf("    Animation Stack %d\n", i);
			//	FBXSDK_printf("         Name: \"%s\"\n", lTakeInfo->mName.Buffer());
			//	FBXSDK_printf("         Description: \"%s\"\n", lTakeInfo->mDescription.Buffer());

			//	// Change the value of the import name if the animation stack should be imported 
			//	// under a different name.
			//	FBXSDK_printf("         Import Name: \"%s\"\n", lTakeInfo->mImportName.Buffer());

			//	// Set the value of the import state to false if the animation stack should be not
			//	// be imported. 
			//	FBXSDK_printf("         Import State: %s\n", lTakeInfo->mSelect ? "true" : "false");
			//	FBXSDK_printf("\n");
			//}
		}

		// Import the scene.
		lStatus = pImporter->Import(pScene);
		if (lStatus == false && pImporter->GetStatus().GetCode() == fbxsdk::FbxStatus::ePasswordError)
		{
			return ResultCode::INVALID_PASSWORD;
		}


		
		

		// Destroy the importer.
		pImporter->Destroy();

		return lStatus;
	}


	// It returns resource and clear pointer inside
	Result AssetImporter3DAssetFBX::Import(AssetImportContext& context, Array<ResourcePtr>& resources)
	{
		FbxScene* pScene = nullptr;

		if (m_pSdkManager == nullptr)
			return ResultCode::NOT_INITIALIZED;

		pScene = fbxsdk::FbxScene::Create(m_pSdkManager, "My Scene");
		if (pScene == nullptr)
			return ResultCode::OUT_OF_MEMORY;

		auto result = LoadScene(pScene, context.GetStream());
		if (!result)
			return result;

		//pScene->


		return ResultCode::SUCCESS;
	}

}

#else
int dummyImporter3DAssetFBX = 0;
#endif

