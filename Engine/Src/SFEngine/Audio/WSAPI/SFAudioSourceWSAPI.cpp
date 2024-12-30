////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Audio player WSAPI
//	
//
////////////////////////////////////////////////////////////////////////////////

#include "SFEnginePCH.h"
#include "Audio/WSAPI/SFAudioWSAPI.h"
#include "Audio/WSAPI/SFAudioSourceWSAPI.h"
#include "Util/SFStrFormat.h"
#include "Util/SFToStringEngineTypes.h"
#include "Math/SF3DMathSerialization.h"
#include "Util/SFGuidHelper.h"

#include <AL/al.h>

namespace SF
{
    // For empty sound, for maximum audio sampling size
    constexpr int DummyNumChannel = 2;
    constexpr int DummySamplesPerSec = 48000 / 2; // only for half seconds
    uint8_t AudioSourceWSAPI_DummyDataBlockBuffer[sizeof(AudioDataBlock) + sizeof(float) * DummyNumChannel * DummySamplesPerSec]{};


    AudioSourceWSAPI::AudioSourceWSAPI(uint numChannel, EAudioFormat dataFormat, uint samplesPerSec)
        : super(numChannel, dataFormat, samplesPerSec)
    {
        m_ALFormat = AudioWSAPI::GetAudioFormat(GetNumChannels(), GetAudioFormat());
    }

    AudioSourceWSAPI::AudioSourceWSAPI(const AudioBufferPtr& audioBuffer)
        : super(audioBuffer)
    {
        m_ALFormat = AudioWSAPI::GetAudioFormat(GetNumChannels(), GetAudioFormat());
    }

    AudioSourceWSAPI::~AudioSourceWSAPI()
    {
    }

    void AudioSourceWSAPI::Dispose()
    {
        if (m_ALSource != 0)
        {
            alDeleteSources(1, &m_ALSource);
            m_ALSource = 0;
        }
        super::Dispose();
    }

    void AudioSourceWSAPI::SetLocation(const Vector4& location)
    {
        super::SetLocation(location);
        m_LocationSerial++;
    }

    void AudioSourceWSAPI::SetVelocity(const Vector4& velocity)
    {
        super::SetVelocity(velocity);
        m_LocationSerial++;
    }

    void AudioSourceWSAPI::SetPitch(float pitch)
    {
        super::SetPitch(pitch);
        m_SettingSerial++;
    }

    void AudioSourceWSAPI::SetVolume(float volume)
    {
        super::SetVolume(volume);
        m_SettingSerial++;
    }

    void AudioSourceWSAPI::SetAttenuationModel(EAudioSourceAttenuation attenuationModel)
    {
        super::SetAttenuationModel(attenuationModel);
        m_SettingSerial++;
    }

    void AudioSourceWSAPI::SetReferenceDistance(float referenceDistance)
    {
        super::SetReferenceDistance(referenceDistance);
        m_SettingSerial++;
    }

    void AudioSourceWSAPI::SetMaxDistance(float maxDistance)
    {
        super::SetMaxDistance(maxDistance);
        m_SettingSerial++;
    }

    void AudioSourceWSAPI::SetRolloffFactor(float rolloffFactor)
    {
        super::SetRolloffFactor(rolloffFactor);
        m_SettingSerial++;
    }

    Result AudioSourceWSAPI::Play()
    {
        Result hr;

        WeakPointerT<AudioSourceWSAPI> audioSourceWeakPtr = this;
        Service::Audio->RunOnAudioThread([this, audioSourceWeakPtr]()
            {
                AudioSourceWSAPIPtr audioSourcePtr = audioSourceWeakPtr.AsSharedPtr<AudioSourceWSAPI>();
                if (audioSourcePtr != nullptr)
                {
                    audioSourcePtr->PlayInternal();
                }
            });

        return hr;
    }

    Result AudioSourceWSAPI::Stop()
    {
        Result hr;

        return hr;
    }

    Result AudioSourceWSAPI::Pause()
    {
        Result hr;

        return hr;
    }

    void AudioSourceWSAPI::PlayInternal()
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
            alSource3f(m_ALSource, AL_POSITION, m_Position[0], m_Position[1], m_Position[2]);
            alSource3f(m_ALSource, AL_VELOCITY, m_Velocity[0], m_Velocity[1], m_Velocity[2]);
            // this is for static buffer mode. need to use alSourceQueueBuffers for stream mode begin
            //alSourcei(m_ALSource, AL_BUFFER, m_Buffer);
        }

        ApplySettingInternal();

        m_QueuedALBufferCount = 0;
        m_QueuedBufferSerial = 0;
        if (m_ALBuffers[0] == 0)
        {
            alGenBuffers(NumBuffer, m_ALBuffers);
        }
    }

    void AudioSourceWSAPI::StopInternal()
    {
        SetPlayState(AudioSource::EPlayState::Stopped);
        if (m_ALSource != 0)
        {
            alSourceStop(m_ALSource);
            // reset buffer status
            alSourcei(m_ALSource, AL_BUFFER, 0);
        }
    }

    void AudioSourceWSAPI::PauseInternal()
    {
        if (m_ALSource != 0)
        {
            SetPlayState(AudioSource::EPlayState::Paused);
            alSourcePause(m_ALSource);
        }
    }

    void AudioSourceWSAPI::ApplySettingInternal()
    {
        m_SettingSync = m_SettingSerial;
        alSourcef(m_ALSource, AL_PITCH, GetPitch());
        alSourcef(m_ALSource, AL_GAIN, GetVolume());
        alSourcef(m_ALSource, AL_MIN_GAIN, 0);
        alSourcef(m_ALSource, AL_MAX_GAIN, 2); // increase Volume cap
        alSourcei(m_ALSource, AL_LOOPING, m_LoopSound);

        switch (GetAttenuationModel())
        {
        default:
        case EAudioSourceAttenuation::None:
            alDistanceModel(AL_NONE);
            break;
        case EAudioSourceAttenuation::Linear:
            //distance = max(distance, AL_REFERENCE_DISTANCE) 
            // distance = min(distance, AL_MAX_DISTANCE)
            //  gain = (1 – AL_ROLLOFF_FACTOR * (distance – AL_REFERENCE_DISTANCE) / (AL_MAX_DISTANCE – AL_REFERENCE_DISTANCE))
            alDistanceModel(AL_LINEAR_DISTANCE_CLAMPED);
            alSourcef(m_ALSource, AL_MAX_DISTANCE, GetMaxDistance());
            alSourcef(m_ALSource, AL_ROLLOFF_FACTOR, GetRolloffFactor());
            alSourcef(m_ALSource, AL_REFERENCE_DISTANCE, GetReferenceDistance());
            break;
        case EAudioSourceAttenuation::InverseDistance:
            // distance = max(distance,AL_REFERENCE_DISTANCE); 
            // distance = min(distance, AL_MAX_DISTANCE);
            // gain = AL_REFERENCE_DISTANCE / (AL_REFERENCE_DISTANCE + AL_ROLLOFF_FACTOR * (distance – AL_REFERENCE_DISTANCE));
            alDistanceModel(AL_INVERSE_DISTANCE_CLAMPED);
            alSourcef(m_ALSource, AL_MAX_DISTANCE, GetMaxDistance());
            alSourcef(m_ALSource, AL_ROLLOFF_FACTOR, GetRolloffFactor());
            alSourcef(m_ALSource, AL_REFERENCE_DISTANCE, GetReferenceDistance());
            break;
        case EAudioSourceAttenuation::ExponentialDistance:
            // distance = max(distance, AL_REFERENCE_DISTANCE) 
            // distance = min(distance, AL_MAX_DISTANCE)
            // gain = (distance / AL_REFERENCE_DISTANCE) ^ (-AL_ROLLOFF_FACTOR)
            alDistanceModel(AL_EXPONENT_DISTANCE_CLAMPED);
            alSourcef(m_ALSource, AL_MAX_DISTANCE, GetMaxDistance());
            alSourcef(m_ALSource, AL_ROLLOFF_FACTOR, GetRolloffFactor());
            alSourcef(m_ALSource, AL_REFERENCE_DISTANCE, GetReferenceDistance());
            break;
        }

        AudioWSAPI::ClearALError();
    }

    void AudioSourceWSAPI::ApplyLocationInternal()
    {
        m_LocationSync = m_LocationSerial;

        const Vector4& location = GetLocation();
        const Vector4& velocity = GetVelocity();

        //SFLog(System, Info, "Source:{0}", location);
        alSource3f(m_ALSource, AL_POSITION, location[0], location[1], location[2]);
        ALenum alError = alGetError();
        if (alError != AL_NO_ERROR)
        {
            SFLog(System, Error, "Error alSource3f. error:{0}", int(alError));
        }

        alSource3f(m_ALSource, AL_VELOCITY, velocity[0], velocity[1], velocity[2]);
        alError = alGetError();
        if (alError != AL_NO_ERROR)
        {
            SFLog(System, Error, "Error alSource3f. error:{0}", int(alError));
        }
    }

    void AudioSourceWSAPI::QueueDataBlock(AudioDataBlock* dataBlock)
    {
        ALuint bufferId = m_ALBuffers[m_QueuedBufferSerial % NumBuffer];
        m_QueuedBufferSerial++;
        m_QueuedALBufferCount++;

        alBufferData(bufferId, m_ALFormat, dataBlock->Data, (ALsizei)dataBlock->DataSize, (ALsizei)GetSamplesPerSec());
        Result hr = AudioWSAPI::GetALError();
        if (!hr.IsSuccess())
        {
            SFLog(System, Error, "Error alBufferData. error:{0}", hr);
        }

        alSourceQueueBuffers(m_ALSource, 1, &bufferId);
        hr = AudioWSAPI::GetALError();
        if (!hr.IsSuccess())
        {
            SFLog(System, Error, "Error alSourceQueueBuffers. error:{0}", hr);
        }
    }

    void AudioSourceWSAPI::QueueZeroSoundBlock(float duration)
    {
        uint samplesPerHalfSec = GetSamplesPerSec() / 2;
        size_t sampleFrameSize = Audio::GetBytesPerSample(GetNumChannels(), GetAudioFormat());
        size_t dataSizePerSec = samplesPerHalfSec * sampleFrameSize;
        size_t dataSizeToAdd = size_t(double(duration) * dataSizePerSec);

        assert((sizeof(AudioDataBlock) + dataSizeToAdd) <= sizeof(AudioSourceWSAPI_DummyDataBlockBuffer));
        AudioDataBlock* DummyBlock = reinterpret_cast<AudioDataBlock*>(AudioSourceWSAPI_DummyDataBlockBuffer);
        DummyBlock->DataSize = dataSizeToAdd;

        for ( ; duration > 0; duration -= 0.5f)
        {
            QueueDataBlock(DummyBlock);

        }
    }

    void AudioSourceWSAPI::TickUpdate()
    {
        const AudioBufferPtr& audioBuffer = GetAudioBuffer();

        if (m_ALSource == 0 || audioBuffer == nullptr)
            return;

        AudioWSAPI::ClearALError();

        ALint processed{}, state{};

        alGetSourcei(m_ALSource, AL_SOURCE_STATE, &state);
        ALenum alError = alGetError();
        if (alError != AL_NO_ERROR)
        {
            SFLog(System, Error, "Error alGetSourcei AL_SOURCE_STATE. error:{0}", int(alError));
            return;
        }


        alGetSourcei(m_ALSource, AL_BUFFERS_PROCESSED, &processed);
        alError = alGetError();
        if (alError != AL_NO_ERROR)
        {
            SFLog(System, Error, "Error alGetSourcei AL_BUFFERS_PROCESSED. error:{0}", int(alError));
            return;
        }

        //SFLog(System, Info, "source state:{0}, processed:{1}", state, processed);

        if (GetPlayState() != AudioSource::EPlayState::Play || audioBuffer->GetAvailableBlockCount() == 0)
            return;

        if (m_SettingSerial != m_SettingSync)
        {
            ApplySettingInternal();
        }

        if (m_LocationSerial != m_LocationSync)
        {
            ApplyLocationInternal();
        }

        ALuint processedBufferIds[NumBuffer]{};
        if (processed > 0)
        {
            assert(processed <= NumBuffer);
            alSourceUnqueueBuffers(m_ALSource, processed, processedBufferIds);
            alError = alGetError();
            if (alError != AL_NO_ERROR)
            {
                SFLog(System, Error, "Error alSourceUnqueueBuffers:{0}", int(alError));
            }

            m_QueuedALBufferCount -= processed;
        }

        if (m_QueuedALBufferCount < NumBuffer)
        {
            int buffersToQueue = Math::Min<int>(NumBuffer - m_QueuedALBufferCount, (int)audioBuffer->GetAvailableBlockCount());
            for (int iBuffer = 0; iBuffer < buffersToQueue; iBuffer++)
            {
                SFUniquePtr<AudioDataBlock> dataBlock(audioBuffer->DequeueBlock());
                QueueDataBlock(dataBlock.get());
            }
        }

        if (state != AL_PLAYING)
        {
            alSourcePlay(m_ALSource);
            alError = alGetError();
            if (alError != AL_NO_ERROR)
            {
                SFLog(System, Error, "Error alSourcePlay:{0}", int(alError));
            }
        }
    }
}
