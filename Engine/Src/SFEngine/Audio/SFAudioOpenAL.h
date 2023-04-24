////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Audio Device OpenAL
//	
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "SFTypedefs.h"
#include "Audio/SFAudioService.h"
#include <AL\alc.h>


namespace SF
{
    class AudioOpenAL
    {
    public:
        static constexpr char OALDevicePrefix[] = "OpenAL Soft on ";
        static constexpr int OALDevicePrefixLen = (int)countof(OALDevicePrefix) - 1;

        static ALCenum GetAudioFormat(uint numChannel, EAudioFormat format);
    };


}
