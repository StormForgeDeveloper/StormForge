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

#include "Object/SFSharedPointer.h"
#include "Audio/WSAPI/SFAudioDeviceWSAPI.h"
#include "Audio/WSAPI/SFAudioSourceWSAPI.h"


namespace SF
{

    /////////////////////////////////////////////////////////////////////////////////////
    // 
    //	Audio playback device
    // 

    AudioPlaybackDeviceWSAPI::AudioPlaybackDeviceWSAPI(const char* deviceName)
        : AudioPlaybackDevice(deviceName)
    {
        m_OALDeviceName.Format("{0}{1}", AudioWSAPI::OALDevicePrefix, deviceName);
    }

    AudioPlaybackDeviceWSAPI::~AudioPlaybackDeviceWSAPI()
    {
        Clear();
    }

    Result AudioPlaybackDeviceWSAPI::Initialize()
    {
        Result hr;

        if (m_pDevice)
            return hr;

        m_pDevice = alcOpenDevice(m_OALDeviceName);
        if (m_pDevice == nullptr)
            return ResultCode::INVALID_DEVICE;

        m_pContext = alcCreateContext(m_pDevice, nullptr);
        if (m_pContext == nullptr)
            return ResultCode::UNEXPECTED;

        return hr;
    }

    void AudioPlaybackDeviceWSAPI::Clear()
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

    void AudioPlaybackDeviceWSAPI::AddAudioSource(const AudioSourceWSAPIPtr& audioSource)
    {
        if (audioSource != nullptr)
        {
            audioSource->DeviceListNode.RemoveFromList();
            audioSource->DeviceListNode.Data = audioSource;
            m_AudioSourceList.Add(&audioSource->DeviceListNode);
        }
    }

    void AudioPlaybackDeviceWSAPI::MakeCurrentContext()
    {
        if (m_pContext == nullptr)
            return;

        alcMakeContextCurrent(m_pContext);
    }

    void AudioPlaybackDeviceWSAPI::TickUpdate()
    {
        if (m_pContext == nullptr)
            return;


        for (auto itSource = m_AudioSourceList.begin(); itSource != m_AudioSourceList.end(); )
        {
            AudioSourceWSAPIPtr audio = itSource->AsSharedPtr<AudioSourceWSAPI>();
            if (audio != nullptr)
            {
                audio->TickUpdate();
                ++itSource;
            }
            else
            {
                DoubleLinkedListStaticT<WeakPointerT<AudioSourceWSAPI>>::Node* pNode = itSource.GetNode();
                itSource = m_AudioSourceList.erase(itSource);
                pNode->Data.reset();
            }

        }
    }
}
