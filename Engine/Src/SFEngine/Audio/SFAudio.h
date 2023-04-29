////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Audio
//	
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "SFTypedefs.h"
#include "Audio/SFAudioTypes.h"

namespace SF
{

    class Audio
    {
    public:
        // Default samples per sec for voice 
        static constexpr int Default_SamplesPerSec_Voice = 24000;
        static constexpr EAudioFormat Default_AudioFormat_Voice = EAudioFormat::Int16;

        // Calculate bits per sample
        static size_t GetBitsPerSample(uint numChannel, EAudioFormat format);

        // Calculate byptes per sample
        static size_t GetBytesPerSample(uint numChannel, EAudioFormat format);
    };


}
