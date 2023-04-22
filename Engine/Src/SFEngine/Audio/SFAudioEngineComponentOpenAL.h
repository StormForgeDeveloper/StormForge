////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Audio Engine component
//	
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "SFTypedefs.h"
#include "Component/SFLibraryComponent.h"
//#include "Delegate/SFEventDelegate.h"
#include "Audio/SFAudioService.h"


namespace SF
{
    class AudioDeviceOpenAL;

	/////////////////////////////////////////////////////////////////////////////////////
	// 
	//	AudioEngineCmponent
	// 
	class AudioEngineComponentOpenAL : public LibraryComponent, public AudioService
	{
	public:

		using super = LibraryComponent;

        static constexpr StringCrc64 TypeName = "AudioEngineComponentOpenAL";

	public:

        AudioEngineComponentOpenAL();
		virtual ~AudioEngineComponentOpenAL();

        virtual const StringCrc64& GetTypeName() const override { return TypeName; }

        // Initialize component
        virtual Result InitializeComponent() override;
        // Terminate component
        virtual void DeinitializeComponent() override;

    private:

        UniquePtr<AudioDeviceOpenAL> m_Device;
	};

}
