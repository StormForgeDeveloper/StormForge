////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Audio Listener
//	
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "SFTypedefs.h"
#include "Audio/SFAudioListener.h"
#include <AL/al.h>

namespace SF
{

    /////////////////////////////////////////////////////////////////////////////////////
    // 
    //	Audio Listener
    // 
    class AudioListenerOpenAL : public AudioListener
    {
    public:

        using super = AudioListener;

        AudioListenerOpenAL();
        virtual ~AudioListenerOpenAL();

        virtual void Dispose() override;

        virtual void SetLocation(const Vector4& location) override;
        virtual void SetVelocity(const Vector4& velocity) override;
        virtual void SetLookDirection(const Vector4& lookDirection) override;
        virtual void SetGain(float gain) override;

        void TickUpdate();

    private:

        uint m_UpdateSerial = 0;
        uint m_SyncSerial = 0;
    };

    using AudioListenerOpenALPtr = SharedPointerT<AudioListenerOpenAL>;

}
