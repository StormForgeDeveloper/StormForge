////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2019 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Transform component
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "SFTypedefs.h"
#include "SFNodeContentComponent.h"


namespace SF
{
		
	class TransformComponent : public UMNodeContentComponent
	{
	private:

		UMVector4 m_Translation;

		UMVector4 m_Scale;

		UMVector4 m_Rotation;

	public:

		TransformComponent( UMNodeContent& owner );
		virtual ~TransformComponent();

		// Initialize components after load/create
		virtual bool InitializeComponent();

		// Translation
		const UMVector4& GetTranslation()						{ return m_Translation; }
		void GetTranslation( const UMVector4& translation )		{ m_Translation = translation; }

		// scale
		const UMVector4& GetScale()								{ return m_Scale; }
		void GetScale( const UMVector4& scale )					{ m_Scale = scale; }

		// rotation
		const UMVector4& GetRotation()							{ return m_Rotation; }
		void GetRotation( const UMVector4& rotation )			{ m_Rotation = rotation; }

	};

} // namespace


