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
        static size_t GetBitsPerSample(uint numChannel, EAudioFormat format);

        static size_t GetBytesPerSample(uint numChannel, EAudioFormat format);
    };


}
