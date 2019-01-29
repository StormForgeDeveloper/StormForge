////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2018 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Resource Mesh
//
////////////////////////////////////////////////////////////////////////////////


#pragma once

#include "Resource/SFResource.h"
#include "Resource/SFDeviceMesh.h"


namespace SF
{

	enum class MeshChannelFormat : uint8_t
	{
		Invalid,
		Bool,
		Int8,
		Int16,
		Int32,
		Float,
		Vector2,
		Vector3,
		Vector4,
		Image,
	};


	struct MeshInitParameter
	{
		int dummy;
	};

	////////////////////////////////////////////////////////////////////
	//
	//	Mesh
	//

	class Mesh : public Resource
	{
	public:


#pragma pack(push,1)
		struct ChannelDescription
		{
			// Animation format
			MeshChannelFormat Format;

			// Dummy
			uint8_t Dummy[3];

			// Animation frame data size
			uint32_t FrameSize;
		};
#pragma pack(pop)

		////////////////////////////////////////////////////////////////////
		//
		//	Type definitions
		//

		// Image data lock manager. help for unlock imagedata
		class LockedMeshData
		{
		private:
			Mesh *m_pMesh = nullptr;
			uint8_t* m_pData = nullptr;

		private:
			LockedMeshData(Mesh *pMesh, uint8_t* pImgData);

			friend class Mesh;

		public:
			LockedMeshData() {}
			LockedMeshData(const LockedMeshData& src);
			~LockedMeshData();

			// Unlock
			void Unlock();

			operator uint8_t*()
			{
				return m_pData;
			}
		};


		enum class BlackState : short
		{
			None,
			Loading,
			Loaded,
			Uploaded
		};



#pragma pack(push)
#pragma pack(2)
		struct BlockData
		{
			int Width		: 16;
			int Height		: 16;
			int Depth		: 16;
			BlackState State;

			
		};
#pragma pack(pop)

	private:

		// element format
		DynamicArray<ChannelDescription> m_ChannelDescriptors;

		uint8_t *m_Data = nullptr;

		DeviceMeshPtr m_DeviceMesh;

	private:


	public:
		Mesh(IHeap& heap, const CallTrack& callTrack = CallTrack());
		virtual ~Mesh();

		// Clear resource
		void ClearResource();

		// Dispose
		virtual void Dispose() override;

		// Init
		Result Init(const MeshInitParameter& initParameters);

		// Returns image data ptr
		// If system texture management trait doesn't have in-memory storage flag, it will be nullptr
		LockedMeshData LockData();
		void UnlockData();



		// Get device texture instance
		DeviceMesh* GetDeviceMesh() { return *m_DeviceMesh; }

	};


	typedef SharedPointerT<Mesh> MeshPtr;
	extern template class SharedPointerT<Mesh>;

}

