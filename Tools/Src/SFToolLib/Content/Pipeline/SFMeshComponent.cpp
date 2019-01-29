
#include "stdafx.h"
#include "UMMeshComponent.h"
#include "UMNodeContent.h"
#include "UMVertexBufferContent.h"


UMMeshComponent::UMMeshComponent( UMNodeContent& owner )
	:UMNodeContentComponent(owner)
	,m_pVertexBuffer(nullptr)
	,m_pRootBone(nullptr)
{
	if( m_pVertexBuffer == nullptr )
		m_pVertexBuffer = new UMVertexBufferContent;
}

UMMeshComponent::~UMMeshComponent()
{
	if( m_pRootBone != nullptr )
		delete m_pRootBone;

	delete m_pVertexBuffer;
}

// Initialize components after load/create
bool UMMeshComponent::InitializeComponent()
{

	return true;
}


// Get vertex buffer
UMVertexBufferContent *UMMeshComponent::GetVertexBuffer()
{
	return m_pVertexBuffer;
}

void UMMeshComponent::TransfoSF( const UMTransfoSFMatrix& transfoSF )
{
	if( m_pVertexBuffer == nullptr || m_pVertexBuffer->GetNumberOfVertex() == 0 )
		return;

	auto positionChannel = m_pVertexBuffer->GetVertexChannel( UMVertexBufferContent::StreamChannelType::POSITION );

	if( positionChannel != nullptr )
	{
		auto positions = positionChannel->GetArrayData<float>();
		for( UINT iVert = 0 ; iVert < m_pVertexBuffer->GetNumberOfVertex(); iVert++ )
		{
			auto pCur = &positions[iVert*positionChannel->NumElement + 0];
			UMVector4 pos(	pCur[0], pCur[1], pCur[2] );
			pos = transfoSF.MultT( pos );
			pCur[0] = (float)pos[0];
			pCur[1] = (float)pos[1];
			pCur[2] = (float)pos[2];
		}
	}

	auto noSFalChannel = m_pVertexBuffer->GetVertexChannel( UMVertexBufferContent::StreamChannelType::NOSFAL );
	if( noSFalChannel != nullptr )
	{
		UMTransfoSFMatrix noSFalTransfoSF = transfoSF;
		noSFalTransfoSF.SetTOnly(UMVector4(0,0,0));

		auto noSFals = noSFalChannel->GetArrayData<float>();
		for( UINT iVert = 0 ; iVert < m_pVertexBuffer->GetNumberOfVertex(); iVert++ )
		{
			auto pCur = &noSFals[iVert*noSFalChannel->NumElement + 0];
			UMVector4 pos(	pCur[0], pCur[1], pCur[2] );
			pos = noSFalTransfoSF.MultT( pos );
			pos.NoSFalize();
			pCur[0] = (float)pos[0];
			pCur[1] = (float)pos[1];
			pCur[2] = (float)pos[2];
		}
	}
}

// Copy Submesh array
void UMMeshComponent::SetSubMeshes( const UMArray<SubMesh*>& subMeshes )
{
	std::for_each(m_SubMeshes.begin(), m_SubMeshes.end(), [](SubMesh*pSubMesh)
	{
		delete pSubMesh;
	});
	m_SubMeshes.clear();

	m_SubMeshes = subMeshes;
}

void UMMeshComponent::ForeachSubMeshes( std::function<void(SubMesh*)> action )
{
	std::for_each(m_SubMeshes.begin(), m_SubMeshes.end(), action);
}


UINT UMMeshComponent::AddBone( UMNodeContent* pBone, const UMTransfoSFMatrix& bindPose )
{
	int index = FindBone(pBone);
	if( index >= 0 )
		return index;

	BoneNode boneNode;
	boneNode.BindPose = bindPose;
	boneNode.pBone = pBone;

	m_SkinBones.push_back(boneNode);
	return m_SkinBones.size() -1;
}

int UMMeshComponent::FindBone( UMNodeContent* pBone )
{
	for(int index = 0; index < (int)m_SkinBones.size(); index++ )
	{
		if( m_SkinBones[index].pBone == pBone )
			return index;
	}

	return -1;
}

void UMMeshComponent::ForeachBones( std::function<void(const BoneNode&)> action )
{
	std::for_each(m_SkinBones.begin(), m_SkinBones.end(), action);
}




