
#include "stdafx.h"
#include "UMMaterialContent.h"



//////////////////////////////////////////////////////////////////////////////////////////////
//
//	class UMMaterialContent
//

// Constructor
UMMaterialContent::UMMaterialContent()
	:m_CullingType(CullingType::Off)
	,m_ReferenceCountByMesh(0)
	,m_Shinness(1)
{
}

UMMaterialContent::~UMMaterialContent()
{
}

// Create clone of material
UMMaterialContent* UMMaterialContent::Clone()
{
	UMMaterialContent* newMaterial = new UMMaterialContent;

	newMaterial->m_CullingType = m_CullingType;
	newMaterial->m_Emissive = m_Emissive;
	newMaterial->m_Ambient = m_Ambient;
	newMaterial->m_Diffuse = m_Diffuse;
	newMaterial->m_Specular = m_Specular;
	newMaterial->m_Shinness = m_Shinness;

	return newMaterial;
}

