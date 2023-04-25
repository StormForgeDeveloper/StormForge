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
#include "Object/SFSharedPointer.h"
#include "Audio/SFAudioDeviceOpenAL.h"
#include "Audio/SFAudioSourceOpenAL.h"


namespace SF
{

    /////////////////////////////////////////////////////////////////////////////////////
    // 
    //	Audio playback device
    // 

    AudioPlaybackDeviceOpenAL::AudioPlaybackDeviceOpenAL(const char* deviceName)
        : AudioPlaybackDevice(deviceName)
    {
        m_OALDeviceName.Format("{0}{1}", AudioOpenAL::OALDevicePrefix, deviceName);
    }

    AudioPlaybackDeviceOpenAL::~AudioPlaybackDeviceOpenAL()
    {
        Clear();
    }

    Result AudioPlaybackDeviceOpenAL::Initialize()
    {
        Result hr;

        if (m_pDevice)
            return hr;

        m_pDevice = alcOpenDevice(m_OALDeviceName);
        if (m_pDevice == nullptr)
            return ResultCode::UNEXPECTED;

        m_pContext = alcCreateContext(m_pDevice, nullptr);
        if (m_pContext == nullptr)
            return ResultCode::UNEXPECTED;

        return hr;
    }

    void AudioPlaybackDeviceOpenAL::Clear()
    {
        if (m_pContext)
        {
            if (m_pContext == alcGetCurrentContext())
            {
                alcMakeContextCurrent(nullptr);
            }
            alcDestroyContext(m_pContext);
        }

        if (m_pDevice)
        {
            alcCloseDevice(m_pDevice);
        }
    }

    void AudioPlaybackDeviceOpenAL::AddAudioSource(const AudioSourceOpenALPtr& audioSource)
    {
        if (audioSource != nullptr)
        {
            audioSource->DeviceListNode.RemoveFromList();
            audioSource->DeviceListNode.Data = audioSource;
            m_AudioSourceList.Add(&audioSource->DeviceListNode);
        }
    }

    void AudioPlaybackDeviceOpenAL::MakeCurrentContext()
    {
        if (m_pContext == nullptr)
            return;

        alcMakeContextCurrent(m_pContext);
    }

    void AudioPlaybackDeviceOpenAL::TickUpdate()
    {
        if (m_pContext == nullptr)
            return;


        for (auto itSource = m_AudioSourceList.begin(); itSource != m_AudioSourceList.end(); )
        {
            AudioSourceOpenALPtr audio = itSource->AsSharedPtr<AudioSourceOpenAL>();
            if (audio != nullptr)
            {
                audio->TickUpdate();
                ++itSource;
            }
            else
            {
                DoubleLinkedListStaticT<WeakPointerT<AudioSourceOpenAL>>::Node* pNode = itSource.GetNode();
                itSource = m_AudioSourceList.erase(itSource);
                pNode->Data.reset();
            }

        }
    }
}
