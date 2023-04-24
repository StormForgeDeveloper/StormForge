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
        m_UpdateSerial++;
        super::SetLocation(location);
    }

    void AudioListenerOpenAL::SetVelocity(const Vector4& velocity)
    {
        m_UpdateSerial++;
        super::SetVelocity(velocity);
    }

    void AudioListenerOpenAL::SetLookDirection(const Vector4& lookDirection)
    {
        m_UpdateSerial++;
        super::SetLookDirection(lookDirection);
    }

    void AudioListenerOpenAL::SetGain(float gain)
    {
        m_UpdateSerial++;
        super::SetGain(gain);
    }

    void AudioListenerOpenAL::TickUpdate()
    {
        if (m_UpdateSerial == m_SyncSerial)
            return;

        m_UpdateSerial = m_SyncSerial;

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
