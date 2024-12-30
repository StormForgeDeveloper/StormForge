////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Audio Device WSAPI
//	
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "SFTypedefs.h"
#include "Audio/SFAudioService.h"
#include "AL/alc.h"


namespace SF
{
    class AudioWSAPI
    {
    public:
        static constexpr char OALDevicePrefix[] = "WSAPI Soft on ";
        static constexpr int OALDevicePrefixLen = (int)countof(OALDevicePrefix) - 1;

        static ALCenum GetAudioFormat(uint numChannel, EAudioFormat format);

        // Clear AL error state
        static void ClearALError();

        // Get AL error in Reulst code
        static Result GetALError();
    };


}
