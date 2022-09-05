////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2016 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Basic android application
//	
//
////////////////////////////////////////////////////////////////////////////////


#pragma once

#if SF_PLATFORM == SF_PLATFORM_LINUX

#include "Application/SFApplicationBase.h"
#include "EngineObject/SFEngineTask.h"




struct ANativeActivity;
struct AConfiguration;

namespace SF
{
	class EngineTask;

	class LinuxApp : public ApplicationBase
	{
	public:

		static constexpr StringCrc64 TypeName = "LinuxApp";


	private:


	public:
		LinuxApp();
		~LinuxApp();

		virtual const StringCrc64& GetTypeName() const override { return TypeName; }

		virtual Result InitializeComponent() override;
		virtual void DeinitializeComponent() override;



		//void StartTestTask();

		///////////////////////////////////////////////////////////////
		//
		//	Process handler
		//
		void ProcessInput();


		//////////////////////////////////////////////////////////////////
		//
		//	Accessors
		//



	public:


	};

}

#endif


