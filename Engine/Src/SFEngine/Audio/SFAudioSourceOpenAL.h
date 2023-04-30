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
#include "Audio/SFAudioSource.h"
#include "Audio/SFAudioBuffer.h"
#include "Container/SFDoubleLinkedListBase.h"
#include <AL/al.h>

namespace SF
{

    /////////////////////////////////////////////////////////////////////////////////////
    // 
    //	Audio source
    // 
    class AudioSourceOpenAL : public AudioSource
    {
    public:

        using super = AudioSource;

        AudioSourceOpenAL(uint numChannel, EAudioFormat dataFormat, uint samplesPerSec);
        AudioSourceOpenAL(const AudioBufferPtr& audioBuffer);
        virtual ~AudioSourceOpenAL();

        virtual void Dispose() override;

        virtual void SetLocation(const Vector4& location) override;
        virtual void SetVelocity(const Vector4& velocity) override;
        virtual void SetPitch(float pitch) override;
        virtual void SetVolume(float gain) override;

        virtual Result Play() override;
        virtual Result Stop() override;
        virtual Result Pause() override;


        // for internal access

        void QueueBuffer(ALuint alBuffer, AudioDataBlock* dataBlock);


        void TickUpdate();

        DoubleLinkedListNodeDataT<WeakPointerT<AudioSourceOpenAL>> DeviceListNode{};

    private:
        void PlayInternal();
        void StopInternal();
        void PauseInternal();
        void ApplySettingInternal();
        void ApplyLocationInternal();


    private:

        static constexpr int NumBuffer = 8;

        ALuint m_ALSource{};
        ALuint m_ALBuffers[NumBuffer]{};
        ALenum m_ALFormat = AL_NONE;

        int m_QueuedALBufferCount = 0;

        Vector4 m_Position = Vector4::Zero();
        Vector4 m_Velocity = Vector4::Zero();
        bool m_LoopSound = false;

        uint m_LocationSerial = 0, m_LocationSync = 0;
        uint m_SettingSerial = 0, m_SettingSync = 0;
    };

    using AudioSourceOpenALPtr = SharedPointerT<AudioSourceOpenAL>;

}
