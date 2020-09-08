////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2016 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Basic windows application
//	
//
////////////////////////////////////////////////////////////////////////////////


#pragma once

#if SF_PLATFORM == SF_PLATFORM_WINDOWS


#include "Application/SFApplicationBase.h"
#include "EngineObject/SFEngineTask.h"





namespace SF
{
	class EngineTask;

	class WindowsApp : public ApplicationBase
	{
	public:
		static constexpr StringCrc64 TypeName = "WindowsApp";

	private:

	public:
		WindowsApp();
		~WindowsApp();

		virtual const StringCrc64& GetTypeName() override { return TypeName; }

		virtual Result InitializeComponent() override;
		virtual void DeinitializeComponent() override;


		///////////////////////////////////////////////////////////////
		//
		//	Process handler
		//
		void ProcessInput();
		void ProcessSensor();

	
	};




}

#endif
