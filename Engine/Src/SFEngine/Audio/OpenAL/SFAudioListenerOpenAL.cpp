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
#include "Util/SFStrFormat.h"
#include "Util/SFToStringEngineTypes.h"
#include "Math/SF3DMathSerialization.h"
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

    void AudioListenerOpenAL::SetVolume(float volume)
    {
        super::SetVolume(volume);
        m_UpdateSerial++;
    }

    void AudioListenerOpenAL::TickUpdate()
    {
        if (m_UpdateSerial == m_SyncSerial)
            return;

        m_SyncSerial = m_UpdateSerial;

        alListenerf(AL_GAIN, GetVolume());

        const Vector4& location = GetLocation();
        const Vector4& velocity = GetVelocity();
        //SFLog(System, Info, "Listener:{0}", location);
        alListener3f(AL_POSITION, location[0], location[1], location[2]);
        alListener3f(AL_VELOCITY, velocity[0], velocity[1], velocity[2]);

        Vector4 lookdirection = GetLookDirection();
        float lookDirSqLen = lookdirection.SquareLength3();
        if (lookDirSqLen < 0.1f)
        {
            lookdirection = Vector4(1, 0, 0);
        }
        else if (Math::Abs(1 - lookDirSqLen) > 0.05f)
        {
            lookdirection.Normalize3Hi();
        }

        float orientation[6] =
        {
            lookdirection[0], lookdirection[1], lookdirection[2],
            0, 1, 0 // Y up
        };
        alListenerfv(AL_ORIENTATION, orientation);

    }
}
