////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Audio service interface
//	
//
////////////////////////////////////////////////////////////////////////////////

#include "SFEnginePCH.h"
#include "Audio/SFAudioService.h"

namespace SF
{
    Result AudioRecorder::Initialize(uint numChannel, EAudioFormat format, uint samplesPerSec, int bufferingDurationSec)
    {
        Result hr;

        m_Channels = numChannel;
        m_Format = format;
        m_SamplesPerSec = samplesPerSec;
        m_SampleFrameSize = static_cast<uint>(Audio::GetBytesPerSample(m_Channels, m_Format));
        m_RecordingBufferSize = m_SampleFrameSize * m_SamplesPerSec * bufferingDurationSec;

        return hr;
    }



    AudioService::AudioService()
    {
    }

    namespace Service
    {
        ServiceInstance<AudioService> Audio;
    }

}
