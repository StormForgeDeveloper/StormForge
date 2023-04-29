////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Audio Source
//	
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "SFTypedefs.h"
#include "Audio/SFAudioBuffer.h"


namespace SF
{

    /////////////////////////////////////////////////////////////////////////////////////
    // 
    //	Audio Listener
    // 
    class AudioListener : public SharedObject
    {
    public:


        AudioListener();
        virtual ~AudioListener();

        const Vector4& GetLocation() const { return m_Location; }
        virtual void SetLocation(const Vector4& location) { m_Location = location; }

        const Vector4& GetVelocity() const { return m_Velocity; }
        virtual void SetVelocity(const Vector4& velocity) { m_Velocity = velocity; }

        const Vector4& GetLookDirection() const { return m_LookDirection; }
        virtual void SetLookDirection(const Vector4& lookDirection) { m_LookDirection = lookDirection; }

        float GetVolume() const { return m_Volume; }
        virtual void SetVolume(float volume) { m_Volume = volume; assert(volume > 0); }


    private:

        Vector4 m_Location = Vector4::Zero();
        Vector4 m_Velocity = Vector4::Zero();
        Vector4 m_LookDirection = Vector4::Zero();
        float m_Volume = 1.0;

        AudioBufferPtr m_AudioBufferPtr;
    };

    using AudioListenerPtr = SharedPointerT<AudioListener>;

}
