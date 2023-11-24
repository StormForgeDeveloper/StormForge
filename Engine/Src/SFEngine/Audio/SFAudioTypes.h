////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Audio types
//	
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "SFTypedefs.h"


namespace SF
{
    // Audio format
    enum class EAudioFormat : uint8_t
    {
        Int8,
        Int16,
        Float
    };

    // Audio source attenuation model
    enum class EAudioSourceAttenuation : uint8_t
    {
        None,
        // (1 – AL_ROLLOFF_FACTOR * (distance – AL_REFERENCE_DISTANCE) / (AL_MAX_DISTANCE – AL_REFERENCE_DISTANCE))
        Linear,
        // gain = AL_REFERENCE_DISTANCE / (AL_REFERENCE_DISTANCE + AL_ROLLOFF_FACTOR*(distance – AL_REFERENCE_DISTANCE));
        InverseDistance,
        // gain = (distance / AL_REFERENCE_DISTANCE) ^ (-AL_ROLLOFF_FACTOR)
        ExponentialDistance
    };

}
