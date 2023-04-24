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
#include "Audio/SFAudioSourceOpenAL.h"
#include <AL/al.h>

namespace SF
{
    AudioSourceOpenAL::AudioSourceOpenAL(uint numChannel, EAudioFormat dataFormat, uint samplesPerSec)
        : super(numChannel, dataFormat, samplesPerSec)
    {
        m_ALFormat = AudioOpenAL::GetAudioFormat(GetNumChannels(), GetAudioFormat());
    }

    AudioSourceOpenAL::AudioSourceOpenAL(const AudioBufferPtr& audioBuffer)
        : super(audioBuffer)
    {
        m_ALFormat = AudioOpenAL::GetAudioFormat(GetNumChannels(), GetAudioFormat());
    }

    AudioSourceOpenAL::~AudioSourceOpenAL()
    {
    }

    void AudioSourceOpenAL::Dispose()
    {
        if (m_ALSource != 0)
        {
            alDeleteSources(1, &m_ALSource);
            m_ALSource = 0;
        }
        super::Dispose();
    }

    void AudioSourceOpenAL::SetLocationNVelocity(const Vector4& location, const Vector4& velocity)
    {
        WeakPointerT<AudioSourceOpenAL> audioSourceWeakPtr = this;
        Service::Audio->RunOnAudioThread([audioSourceWeakPtr, location, velocity]()
            {
                AudioSourceOpenALPtr audioSourcePtr = audioSourceWeakPtr.AsSharedPtr<AudioSourceOpenAL>();
                if (audioSourcePtr != nullptr && audioSourcePtr->m_ALSource != 0)
                {
                    audioSourcePtr->m_Position = location;
                    audioSourcePtr->m_Velocity = velocity;
                    alSource3f(audioSourcePtr->m_ALSource, AL_POSITION, location[0], location[1], location[2]);
                    alSource3f(audioSourcePtr->m_ALSource, AL_VELOCITY, velocity[0], velocity[1], velocity[2]);
                }
            });

    }

    Result AudioSourceOpenAL::Play()
    {
        Result hr;

        WeakPointerT<AudioSourceOpenAL> audioSourceWeakPtr = this;
        Service::Audio->RunOnAudioThread([this, audioSourceWeakPtr]()
            {
                AudioSourceOpenALPtr audioSourcePtr = audioSourceWeakPtr.AsSharedPtr<AudioSourceOpenAL>();
                if (audioSourcePtr != nullptr)
                {
                    audioSourcePtr->PlayInternal();
                }
            });

        return hr;
    }

    Result AudioSourceOpenAL::Stop()
    {
        Result hr;

        return hr;
    }

    Result AudioSourceOpenAL::Pause()
    {
        Result hr;

        return hr;
    }

    void AudioSourceOpenAL::PlayInternal()
    {
        SetPlayState(AudioSource::EPlayState::Play);
        if (m_ALSource != 0)
        {
            alSourceRewind(m_ALSource);
            // reset buffer status
            alSourcei(m_ALSource, AL_BUFFER, 0);
        }
        else
        {
            alGenSources(1, &m_ALSource);
            alSourcef(m_ALSource, AL_PITCH, m_Pitch);
            alSourcef(m_ALSource, AL_GAIN, m_Gain);
            alSource3f(m_ALSource, AL_POSITION, m_Position[0], m_Position[1], m_Position[2]);
            alSource3f(m_ALSource, AL_VELOCITY, m_Velocity[0], m_Velocity[1], m_Velocity[2]);
            alSourcei(m_ALSource, AL_LOOPING, m_LoopSound);
            // this is for static buffer mode. need to use alSourceQueueBuffers for stream mode begin
            //alSourcei(m_ALSource, AL_BUFFER, m_Buffer);
        }

        m_QueuedALBufferCount = 0;
        if (m_ALBuffers[0] == 0)
        {
            alGenBuffers(NumBuffer, m_ALBuffers);
        }
    }

    void AudioSourceOpenAL::StopInternal()
    {
        SetPlayState(AudioSource::EPlayState::Stopped);
        if (m_ALSource != 0)
        {
            alSourceStop(m_ALSource);
            // reset buffer status
            alSourcei(m_ALSource, AL_BUFFER, 0);
        }
    }

    void AudioSourceOpenAL::PauseInternal()
    {
        if (m_ALSource != 0)
        {
            SetPlayState(AudioSource::EPlayState::Paused);
            alSourcePause(m_ALSource);
        }
    }

    void AudioSourceOpenAL::QueueBuffer(ALuint alBuffer, AudioBuffer::AudioDataBlock* dataBlock)
    {
        alBufferData(alBuffer, m_ALFormat, dataBlock->Data, (ALsizei)dataBlock->DataSize, (ALsizei)GetSamplesPerSec());
        alSourceQueueBuffers(m_ALSource, 1, &alBuffer);
    }


    void AudioSourceOpenAL::TickUpdate()
    {
        const AudioBufferPtr& audioBuffer = GetAudioBuffer();

        if (m_ALSource == 0 || audioBuffer == nullptr)
            return;

        ALint processed, state;

        alGetSourcei(m_ALSource, AL_SOURCE_STATE, &state);
        alGetSourcei(m_ALSource, AL_BUFFERS_PROCESSED, &processed);
        SFLog(System, Info, "source state:{0}, processed:{1}", state, processed);
        if (alGetError() != AL_NO_ERROR)
        {
            SFLog(System, Error, "Error checking source state:{0}", state);
            return;
        }

        if (GetPlayState() != AudioSource::EPlayState::Play || audioBuffer->GetAvailableBlockCount() == 0)
            return;

        if (m_QueuedALBufferCount < NumBuffer)
        {
            int buffersToQueue = Math::Min<int>(NumBuffer - m_QueuedALBufferCount, (int)audioBuffer->GetAvailableBlockCount());
            for (int iBuffer = 0; iBuffer < buffersToQueue; iBuffer++)
            {
                auto bufferId = m_ALBuffers[m_QueuedALBufferCount];
                m_QueuedALBufferCount++;

                AudioBuffer::AudioDataBlock* dataBlock = audioBuffer->DequeueBlock();
                QueueBuffer(bufferId, dataBlock);
            }
        }
        else if (processed > 0)
        {
            ALuint bufferId{};
            alSourceUnqueueBuffers(m_ALSource, 1, &bufferId);

            AudioBuffer::AudioDataBlock* dataBlock = audioBuffer->DequeueBlock();
            QueueBuffer(bufferId, dataBlock);

        }

        if (state != AL_PLAYING)
        {
            alSourcePlay(m_ALSource);
        }
    }
}
