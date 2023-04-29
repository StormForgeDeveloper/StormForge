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
    //	Audio source
    // 
    class AudioSource : public SharedObject
    {
    public:

        enum class EPlayState : uint32_t
        {
            Init,
            Play,
            Stopped,
            Paused
        };


        AudioSource(uint numChannel, EAudioFormat dataFormat, uint samplesPerSec);
        AudioSource(const AudioBufferPtr& audioBuffer);
        virtual ~AudioSource();


        const Vector4& GetLocation() const { return m_Location; }
        virtual void SetLocation(const Vector4& location) { m_Location = location; }

        const Vector4& GetVelocity() const { return m_Velocity; }
        virtual void SetVelocity(const Vector4& velocity) { m_Velocity = velocity; }

        virtual Result Play() = 0;
        virtual Result Stop() = 0;
        virtual Result Pause() = 0;

        uint GetNumChannels() const { return m_NumChannels; }
        EAudioFormat GetAudioFormat() const { return m_DataFormat; }
        uint GetSamplesPerSec() const { return m_SamplesPerSec; }
        EPlayState GetPlayState() const { return m_PlayState; }

        float GetPitch() const { return m_Pitch; }
        virtual void SetPitch(float pitch) { m_Pitch = pitch; assert(pitch > 0); }

        float GetVolume() const { return m_Volume; }
        virtual void SetVolume(float volume) { m_Volume = volume; assert(volume >= 0); }

        const AudioBufferPtr& CreateAudioBuffer(size_t bufferSize);
        const AudioBufferPtr& GetAudioBuffer() const { return m_AudioBufferPtr; }

    protected:
        void SetPlayState(EPlayState newState) { m_PlayState = newState; }

    private:

        Vector4 m_Location = Vector4::Zero();
        Vector4 m_Velocity = Vector4::Zero();

        uint m_NumChannels = 1;
        EAudioFormat m_DataFormat = EAudioFormat::Float;
        uint m_SamplesPerSec = 44100;
        // Audio play state
        EPlayState m_PlayState = EPlayState::Init;

        float m_Pitch = 1.f;
        float m_Volume = 1.0;

        AudioBufferPtr m_AudioBufferPtr;
    };

    using AudioSourcePtr = SharedPointerT<AudioSource>;

}
