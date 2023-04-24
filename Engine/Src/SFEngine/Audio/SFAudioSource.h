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

        struct AudioDataBlock
        {
            size_t DataSize = 0;
            uint8_t Data[1];
        };


        AudioSource(uint numChannel, EAudioFormat dataFormat, uint samplesPerSec);
        AudioSource(const AudioBufferPtr& audioBuffer);
        virtual ~AudioSource();


        virtual void SetLocationNVelocity(const Vector4& location, const Vector4& velocity) = 0;

        virtual Result Play() = 0;
        virtual Result Stop() = 0;
        virtual Result Pause() = 0;

        uint GetNumChannels() const { return m_NumChannels; }
        EAudioFormat GetAudioFormat() const { return m_DataFormat; }
        uint GetSamplesPerSec() const { return m_SamplesPerSec; }
        EPlayState GetPlayState() const { return m_PlayState; }

        const AudioBufferPtr& CreateAudioBuffer(size_t bufferSize);
        const AudioBufferPtr& GetAudioBuffer() const { return m_AudioBufferPtr; }

    protected:
        void SetPlayState(EPlayState newState) { m_PlayState = newState; }

    private:

        uint m_NumChannels = 1;
        EAudioFormat m_DataFormat = EAudioFormat::Float;
        uint m_SamplesPerSec = 44100;
        // Audio play state
        EPlayState m_PlayState = EPlayState::Init;

        AudioBufferPtr m_AudioBufferPtr;
    };

    using AudioSourcePtr = SharedPointerT<AudioSource>;

}
