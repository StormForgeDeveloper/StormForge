
#pragma once

#include "UMTypedef.h"
#include "UMNodeContentComponent.h"


class UMVertexBufferContent;
class UMMaterialContent;

class UMMeshComponent : public UMNodeContentComponent
{
public:

	enum class PrimitiveType {
		LINES,
		POINT_SPRITES,
		TRIANGLES,
		TRIANGLESTRIP,
	};

	struct SubMesh
	{
		PrimitiveType	Primitive;
		UINT			NumberOfPolygon;		// Actually this is triangle count
		UINT			IndexBufferID;
		UMArray<UINT32>	Indexies;
		UMMaterialContent* Material;

		SubMesh()
			:Primitive(PrimitiveType::TRIANGLES)
			,NumberOfPolygon(0)
			,IndexBufferID(0)
			,Material(nullptr)
		{
		}
	};

	struct BoneNode
	{
		UMTransfoSFMatrix BindPose;  // World transfoSF
		UMNodeContent* pBone;
	};

private:

	UMVertexBufferContent *m_pVertexBuffer;

	UMArray<SubMesh*> m_SubMeshes;

	// Skinning bone targets
	UMArray<BoneNode> m_SkinBones;
	UMNodeContent* m_pRootBone;

public:

	UMMeshComponent( UMNodeContent& owner );
	virtual ~UMMeshComponent();

	// Initialize components after load/create
	virtual bool InitializeComponent();

	// Get vertex buffer
	UMVertexBufferContent *GetVertexBuffer();

	void TransfoSF( const UMTransfoSFMatrix& transfoSF );

	UINT GetSubMeshCount()														{ return m_SubMeshes.size(); }

	// Copy Submesh array
	void SetSubMeshes( const UMArray<SubMesh*>& subMeshes );

	// Iterate submeshes
	void ForeachSubMeshes( std::function<void(SubMesh*)> action );

	void SetRootBone(UMNodeContent* pRootBone)									{ m_pRootBone = pRootBone; }
	UMNodeContent* GetRootBone()												{ return m_pRootBone; }

	UINT GetBoneCount()															{ return m_SkinBones.size(); }
	UINT AddBone( UMNodeContent* pBone, const UMTransfoSFMatrix& bindPose );
	int FindBone( UMNodeContent* pBone );
	UMNodeContent* GetBone( UINT iBone )										{ return m_SkinBones[iBone].pBone; }
	void ForeachBones( std::function<void(const BoneNode&)> action );
};


