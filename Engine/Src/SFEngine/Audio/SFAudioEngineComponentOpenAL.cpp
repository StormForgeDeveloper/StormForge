////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : AudioEngineComponentOpenAL
//	
//
////////////////////////////////////////////////////////////////////////////////

#include "SFEnginePCH.h"
#include "Audio/SFAudioEngineComponentOpenAL.h"
#include "Audio/SFAudioDeviceOpenAL.h"
#include "Audio/SFAudioPlayerOpenAL.h"
#include "Audio/SFAudioRecorderOpenAL.h"
#include "Audio/SFAudioBuffer.h"


namespace SF
{

    AudioEngineComponentOpenAL::AudioEngineComponentOpenAL()
        : LibraryComponent(TypeName)
    {
        Service::Audio = this;
    }

    AudioEngineComponentOpenAL::~AudioEngineComponentOpenAL()
    {
        Service::Audio = nullptr;
    }

    // Initialize component
    Result AudioEngineComponentOpenAL::InitializeComponent()
    {
        Result hr;

        super::InitializeComponent();

        //m_Device

        return hr;
    }

    // Terminate component
    void AudioEngineComponentOpenAL::DeinitializeComponent()
    {
        super::DeinitializeComponent();
    }

}
