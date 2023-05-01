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
        Linear,
        InverseDistance,
        ExponentialDistance
    };

}
