////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Audio player openal
//	
//
////////////////////////////////////////////////////////////////////////////////

#include "SFEnginePCH.h"
#include "Audio/SFAudioOpenAL.h"
#include "Audio/SFAudioListenerOpenAL.h"
#include <AL/al.h>

namespace SF
{
    AudioListenerOpenAL::AudioListenerOpenAL()
    {
    }

    AudioListenerOpenAL::~AudioListenerOpenAL()
    {
    }

    void AudioListenerOpenAL::Dispose()
    {
        super::Dispose();
    }

    void AudioListenerOpenAL::SetLocation(const Vector4& location)
    {
        super::SetLocation(location);
        m_UpdateSerial++;
    }

    void AudioListenerOpenAL::SetVelocity(const Vector4& velocity)
    {
        super::SetVelocity(velocity);
        m_UpdateSerial++;
    }

    void AudioListenerOpenAL::SetLookDirection(const Vector4& lookDirection)
    {
        super::SetLookDirection(lookDirection);
        m_UpdateSerial++;
    }

    void AudioListenerOpenAL::SetGain(float gain)
    {
        super::SetGain(gain);
        m_UpdateSerial++;
    }

    void AudioListenerOpenAL::TickUpdate()
    {
        if (m_UpdateSerial == m_SyncSerial)
            return;

        m_SyncSerial = m_UpdateSerial;

        alListenerf(AL_GAIN, GetGain());

        const Vector4& location = GetLocation();
        const Vector4& velocity = GetVelocity();
        alListener3f(AL_POSITION, location[0], location[1], location[2]);
        alListener3f(AL_VELOCITY, velocity[0], velocity[1], velocity[2]);

        const Vector4& lookdirection = GetLookDirection();
        float orientation[6] =
        {
            lookdirection[0], lookdirection[1], lookdirection[2],
            0, 1, 0 // Y up
        };
        alListenerfv(AL_ORIENTATION, orientation);

    }
}
