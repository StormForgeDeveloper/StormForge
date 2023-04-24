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

#include "SFEnginePCH.h"
#include "Audio/SFAudioSource.h"

namespace SF
{
    AudioSource::AudioSource(uint numChannel, EAudioFormat dataFormat, uint samplesPerSec)
        : m_NumChannels(numChannel)
        , m_DataFormat(dataFormat)
        , m_SamplesPerSec(samplesPerSec)
    {

    }

    AudioSource::AudioSource(const AudioBufferPtr& audioBuffer)
        : m_AudioBufferPtr(audioBuffer)
    {
        if (m_AudioBufferPtr.IsValid())
        {
            m_NumChannels = m_AudioBufferPtr->GetNumChannels();
            m_DataFormat = m_AudioBufferPtr->GetAudioFormat();
            m_SamplesPerSec = m_AudioBufferPtr->GetSamplesPerSec();
        }
    }

    AudioSource::~AudioSource()
    {

    }

    const AudioBufferPtr& AudioSource::CreateAudioBuffer(size_t bufferSize)
    {
        m_AudioBufferPtr = new(GetSystemHeap()) AudioBuffer(GetNumChannels(), GetAudioFormat(), GetSamplesPerSec(), bufferSize);
        return m_AudioBufferPtr;
    }
}
