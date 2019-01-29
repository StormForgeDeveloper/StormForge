////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2018 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Resource Mesh
//
////////////////////////////////////////////////////////////////////////////////


#include "SFEnginePCH.h"
#include "Resource/SFMesh.h"
#include "Service/SFEngineService.h"


namespace SF
{

	template class SharedPointerT<Mesh>;



	Mesh::LockedMeshData::LockedMeshData(Mesh *pMesh, uint8_t* pImgData)
		: m_pMesh(pMesh)
		, m_pData(pImgData)
	{
	}

	Mesh::LockedMeshData::LockedMeshData(const LockedMeshData& src)
		: m_pMesh(src.m_pMesh)
		, m_pData(src.m_pData)
	{

	}

	Mesh::LockedMeshData::~LockedMeshData()
	{
		Unlock();
	}

	void Mesh::LockedMeshData::Unlock()
	{
		if (m_pMesh == nullptr || m_pData == nullptr)
			return;

		m_pMesh->UnlockData();
		m_pMesh = nullptr;
		m_pData = nullptr;
	}




	Mesh::Mesh(IHeap& heap, const CallTrack& callTrack)
		: Resource(heap, "Mesh", callTrack)
		, m_ChannelDescriptors(heap)
	{
	}

	Mesh::~Mesh()
	{
		ClearResource();
	}

	void Mesh::ClearResource()
	{
		IHeap::Delete(m_Data);
		m_Data = nullptr;
	}

	void Mesh::Dispose()
	{
		ClearResource();
		Resource::Dispose();
	}

	Mesh::LockedMeshData Mesh::LockData()
	{
		if (m_Data == nullptr)
			return LockedMeshData();

		// TODO:
		return LockedMeshData();
	}

	void Mesh::UnlockData()
	{
		// flush image data to device
	}

	Result Mesh::Init(const MeshInitParameter& initParameters)
	{
		ClearResource();


		return ResultCode::SUCCESS;
	}




}

