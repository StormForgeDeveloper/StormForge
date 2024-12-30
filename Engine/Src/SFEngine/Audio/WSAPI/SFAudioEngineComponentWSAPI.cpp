////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : AudioEngineComponent WSAPI
//	
//
////////////////////////////////////////////////////////////////////////////////

#include "SFEnginePCH.h"


#include "Audio/WSAPI/SFAudioEngineComponentWSAPI.h"
#include "Audio/WSAPI/SFAudioDeviceWSAPI.h"
#include "Audio/WSAPI/SFAudioListenerWSAPI.h"
#include "Audio/WSAPI/SFAudioSourceWSAPI.h"
#include "Audio/WSAPI/SFAudioRecorderWSAPI.h"
#include "Audio/SFAudioBuffer.h"

enum class LogLevel;
extern LogLevel gLogLevel;

namespace SF
{

    AudioEngineComponentWSAPI::AudioEngineComponentWSAPI()
        : LibraryComponent(TypeName)
        , m_Requests(GetSystemHeap(), 32)
    {
        Service::Audio = this;
    }

    AudioEngineComponentWSAPI::~AudioEngineComponentWSAPI()
    {
        Service::Audio = nullptr;
    }

    // Initialize component
    Result AudioEngineComponentWSAPI::InitializeComponent()
    {
        Result hr;

        super::InitializeComponent();

#if SF_PLATFORM == SF_PLATFORM_WINDOWS
        // Hacky WSAPI log kill
        gLogLevel = (LogLevel)0;
#endif

        SetPlaybackDevice(GetDefaultDeviceName(true));

        m_Listener = new(GetSystemHeap()) AudioListenerWSAPI;

        m_AudioThread.reset(
            new(GetSystemHeap()) FunctorTickThread([&](Thread* pThisThread)->bool
                {
                    AudioTickUpdate();
                    return true;
                })
        );

        m_AudioThread->SetTickInterval(DurationMS(60));
        m_AudioThread->Start();

        return hr;
    }

    // Terminate component
    void AudioEngineComponentWSAPI::DeinitializeComponent()
    {
        if (m_AudioThread)
        {
            m_AudioThread->Stop(true);
            m_AudioThread.reset();
        }

        m_Requests.Reset();

        if (m_Listener.IsValid())
        {
            m_Listener->Dispose();
            m_Listener = nullptr;
        }

        if (m_PlaybackDevice.IsValid())
        {
            m_PlaybackDevice->Dispose();
            m_PlaybackDevice = nullptr;
        }

        super::DeinitializeComponent();
    }

    Result AudioEngineComponentWSAPI::GetDeviceList(bool bPlaybackDevice, Array<String>& outDevices)
    {
        Result hr;

        if (!alcIsExtensionPresent(nullptr, "ALC_enumerate_all_EXT"))
        {
            // no device enumeration is supported. just default device
            outDevices.push_back(GetDefaultDeviceName(bPlaybackDevice));
            return ResultCode::SUCCESS;
        }

        const ALCchar* deviceNames{};

        // Pass in NULL device handle to get list of *all* devices
        if (bPlaybackDevice)
        {
            deviceNames = alcGetString(nullptr, ALC_ALL_DEVICES_SPECIFIER);
        }
        else
        {
            deviceNames = alcGetString(nullptr, ALC_CAPTURE_DEVICE_SPECIFIER);
        }

        const char* curName = deviceNames;
        for (;curName[0] != '\0'; curName += strlen(curName) + 1)
        {
            if (StrUtil::StringCompair(AudioWSAPI::OALDevicePrefix, curName, AudioWSAPI::OALDevicePrefixLen))
            {
                curName += AudioWSAPI::OALDevicePrefixLen;
            }

            outDevices.push_back(curName);
        }

        return hr;
    }

    const char* AudioEngineComponentWSAPI::GetDefaultDeviceName(bool bPlaybackDevice)
    {
        const ALCchar* defaultDeviceName{};
        if (bPlaybackDevice)
        {
            defaultDeviceName = alcGetString(nullptr, ALC_DEFAULT_ALL_DEVICES_SPECIFIER);
        }
        else
        {
            defaultDeviceName = alcGetString(nullptr, ALC_CAPTURE_DEFAULT_DEVICE_SPECIFIER);
        }

        if (StrUtil::StringCompair(AudioWSAPI::OALDevicePrefix, defaultDeviceName, AudioWSAPI::OALDevicePrefixLen))
        {
            defaultDeviceName += AudioWSAPI::OALDevicePrefixLen;
        }

        return defaultDeviceName;
    }

    Result AudioEngineComponentWSAPI::SetPlaybackDevice(const char* deviceName)
    {
        if (deviceName == nullptr)
        {
            deviceName = GetDefaultDeviceName(true);
        }

        if (m_PlaybackDevice.IsValid())
        {
            if (m_PlaybackDevice->GetDeviceName() == deviceName)
            {
                return ResultCode::SUCCESS;
            }
            else
            {
                m_PlaybackDevice->Dispose();
                m_PlaybackDevice.reset();
            }
        }


        Result hr;
        auto* pDevice = new(GetSystemHeap()) AudioPlaybackDeviceWSAPI(deviceName);

        defCheck(pDevice->Initialize());

        m_PlaybackDevice = pDevice;

        OnPlaybackDeviceChanged.Invoke(pDevice);

        return hr;
    }


    AudioRecorderPtr AudioEngineComponentWSAPI::CreateRecorder(const char* deviceName)
    {
        if (deviceName == nullptr)
        {
            deviceName = GetDefaultDeviceName(false);
        }

        return new(GetSystemHeap()) AudioRecorderWSAPI(deviceName);
    }

    AudioBufferPtr AudioEngineComponentWSAPI::CreateBuffer(uint numChannels, EAudioFormat format, uint samplesPerSec, size_t bufferSize)
    {
        AudioBuffer* newBuffer = new(GetSystemHeap()) AudioBuffer(numChannels, format, samplesPerSec, bufferSize);

        return newBuffer;
    }

    AudioSourcePtr AudioEngineComponentWSAPI::CreateSource(uint numChannels, EAudioFormat format, uint samplesPerSec)
    {
        if (!m_PlaybackDevice.IsValid())
        {
            SFLog(System, Error, "Audio system hans't initialized");
            return nullptr;
        }

        AudioSourceWSAPI* newPlayer = new(GetSystemHeap()) AudioSourceWSAPI(numChannels, format, samplesPerSec);

        WeakPointerT<AudioSourceWSAPI> audioSourceWeakPtr = newPlayer;
        RunOnAudioThread([this, audioSourceWeakPtr]()
            {
                AudioSourceWSAPIPtr audioSourcePtr = audioSourceWeakPtr.AsSharedPtr<AudioSourceWSAPI>();
                if (audioSourcePtr != nullptr)
                {
                    m_PlaybackDevice->AddAudioSource(audioSourcePtr.get());
                }
            });


        return newPlayer;
    }

    AudioSourcePtr AudioEngineComponentWSAPI::CreateSource(const AudioBufferPtr& buffer)
    {
        if (!m_PlaybackDevice.IsValid())
        {
            SFLog(System, Error, "Audio system hans't initialized");
            return nullptr;
        }

        AudioSourceWSAPI* newPlayer = new(GetSystemHeap()) AudioSourceWSAPI(buffer);

        WeakPointerT<AudioSourceWSAPI> audioSourceWeakPtr = newPlayer;
        RunOnAudioThread([this, audioSourceWeakPtr]()
            {
                AudioSourceWSAPIPtr audioSourcePtr = audioSourceWeakPtr.AsSharedPtr<AudioSourceWSAPI>();
                if (audioSourcePtr != nullptr)
                {
                    m_PlaybackDevice->AddAudioSource(audioSourcePtr.get());
                }
            });


        return newPlayer;
    }

    AudioListenerPtr AudioEngineComponentWSAPI::GetListener()
    {
        return m_Listener;
    }

    void AudioEngineComponentWSAPI::SetMasterPlaybackVolume(float volume)
    {
        m_MasterPlaybackVolume = volume;
        alListenerf(AL_GAIN, volume);
    }

    void AudioEngineComponentWSAPI::RunOnAudioThread(std::function<void()>&& task)
    {
        MutexScopeLock lock(m_RequestLock);
        m_Requests.Enqueue(Forward<std::function<void()>>(task));
    }

    void AudioEngineComponentWSAPI::RunOnAudioThread(const std::function<void()>& task)
    {
        MutexScopeLock lock(m_RequestLock);
        m_Requests.Enqueue(task);
    }


    void AudioEngineComponentWSAPI::AudioTickUpdate()
    {
        auto playbackDevice = m_PlaybackDevice.get();
        if (playbackDevice == nullptr)
            return;

        playbackDevice->MakeCurrentContext();

        auto* pListener = static_cast<AudioListenerWSAPI*>(m_Listener.get());
        if (pListener)
        {
            pListener->TickUpdate();
        }

        {
            //MutexScopeLock lock(m_RequestLock);
            std::function<void()> request;
            while (m_Requests.Dequeue(request))
            {
                request();
            }
        }

        playbackDevice->TickUpdate();
    }
}
