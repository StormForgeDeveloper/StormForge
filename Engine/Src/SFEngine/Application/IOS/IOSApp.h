////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2017 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Basic IOS application
//	
//
////////////////////////////////////////////////////////////////////////////////


#pragma once

#if SF_PLATFORM == SF_PLATFORM_IOS

#include "Application/SFApplicationBase.h"
#include "EngineObject/SFEngineTask.h"



namespace SF
{
	class EngineTask;

	class IOSApp : public ApplicationBase
	{
	public:
		static constexpr FixedString TypeName = "IOSApp";

	private:


	public:
		IOSApp();
		~IOSApp();

		virtual const FixedString& GetTypeName() override { return TypeName; }

		virtual Result InitializeComponent() override;
		virtual void DeinitializeComponent() override;


	public:


	};




}

#endif


