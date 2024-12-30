////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Audio Recorder WSAPI
//	
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "SFTypedefs.h"
#include "Audio/SFAudioService.h"

#include "AL/alc.h"
#include "AL/al.h"
#include "AL/alext.h"

namespace SF
{

    /////////////////////////////////////////////////////////////////////////////////////
    // 
    //	Audio recorder
    // 
    class AudioRecorderWSAPI : public AudioRecorder
    {
    public:
        using super = AudioRecorder;

        AudioRecorderWSAPI(const char* deviceName);
        virtual ~AudioRecorderWSAPI();

        virtual Result Initialize(uint numChannel, EAudioFormat format, uint samplesPerSec, int bufferingDurationSec = 10) override;

        virtual Result StartRecording() override;
        virtual Result StopRecording() override;

        virtual size_t GetAvailableSampleCount() override;
        virtual Result ReadSamples(Array<uint8_t>& outBuffer) override;

    private:
        String m_OALDeviceName;

        ALCdevice* m_pDevice{};
        ALCenum m_Format = AL_NONE;
    };


}
