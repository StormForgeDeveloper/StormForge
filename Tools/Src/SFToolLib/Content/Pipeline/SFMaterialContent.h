
#pragma once

#include "UMTypedef.h"
#include "UMNodeContentComponent.h"
#include "UMObject.h"


class UMTextureContent;

class UMMaterialContent : public UMObject
{
public:

	struct ColorChannel
	{
		ColorChannel()
			:Texture(nullptr)
		{
			Color[0] = 1.0f;
			Color[1] = 1.0f;
			Color[2] = 1.0f;
			Color[3] = 1.0f;
		}

		UMTextureContent*	Texture;
		UMColor				Color;
	};

	
	enum class CullingType
	{
		Off,
		CCW,
		CW
	};


private:
	
	CullingType m_CullingType;

	ColorChannel m_Emissive;
	ColorChannel m_Ambient;
	ColorChannel m_Diffuse;
	ColorChannel m_Specular;
	float m_Shinness;

	UINT m_ReferenceCountByMesh;

public:

	// Constructor
	UMMaterialContent();
	virtual ~UMMaterialContent();

	// Mesh reference count
	UINT GetReferenceCountByMesh()													{ return m_ReferenceCountByMesh; }
	void IncReferenceCountByMesh()													{ m_ReferenceCountByMesh++; }
	
	// Culling
	void SetCullingType( CullingType cullingType )									{ m_CullingType = cullingType; }
	CullingType GetCullingType()													{ return m_CullingType; }

	// Get colors
	const ColorChannel& GetEmissive()												{ return m_Emissive; }
	void SetEmissive( const ColorChannel& propertyValue )							{ m_Emissive = propertyValue; }

	const ColorChannel& GetAmbient()												{ return m_Ambient; }
	void SetAmbient( const ColorChannel& propertyValue )							{ m_Ambient = propertyValue; }

	const ColorChannel& GetDiffuse()												{ return m_Diffuse; }
	void SetDiffuse( const ColorChannel& propertyValue )							{ m_Diffuse = propertyValue; }

	const ColorChannel& GetSpecular()												{ return m_Specular; }
	void SetSpecular( const ColorChannel& propertyValue )							{ m_Specular = propertyValue; }

	float GetShinness()																{ return m_Shinness; }
	void SetShinness( float shinness )												{ m_Shinness = shinness; }

	// Create clone of material
	UMMaterialContent* Clone();
};




