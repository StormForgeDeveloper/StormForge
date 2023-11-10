////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : AudioEngineComponentOpenAL
//	
//
////////////////////////////////////////////////////////////////////////////////

#include "SFEnginePCH.h"
#include "Audio/SFAudioEngineComponentOpenAL.h"
#include "Audio/SFAudioDeviceOpenAL.h"
#include "Audio/SFAudioListenerOpenAL.h"
#include "Audio/SFAudioSourceOpenAL.h"
#include "Audio/SFAudioRecorderOpenAL.h"
#include "Audio/SFAudioBuffer.h"

enum class LogLevel;
extern LogLevel gLogLevel;

namespace SF
{

    AudioEngineComponentOpenAL::AudioEngineComponentOpenAL()
        : LibraryComponent(TypeName)
        , m_Requests(GetSystemHeap(), 32)
    {
        Service::Audio = this;
    }

    AudioEngineComponentOpenAL::~AudioEngineComponentOpenAL()
    {
        Service::Audio = nullptr;
    }

    // Initialize component
    Result AudioEngineComponentOpenAL::InitializeComponent()
    {
        Result hr;

        super::InitializeComponent();

#if SF_PLATFORM == SF_PLATFORM_WINDOWS
        // Hacky OpenAL log kill
        gLogLevel = (LogLevel)0;
#endif

        SetPlaybackDevice(GetDefaultDeviceName(true));

        m_Listener = new(GetSystemHeap()) AudioListenerOpenAL;

        m_AudioThread.reset(
            new(GetSystemHeap()) FunctorTickThread([&](Thread* pThisThread)->bool
                {
                    TickUpdate();
                    return true;
                })
        );

        m_AudioThread->SetTickInterval(DurationMS(60));
        m_AudioThread->Start();

        return hr;
    }

    // Terminate component
    void AudioEngineComponentOpenAL::DeinitializeComponent()
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

    Result AudioEngineComponentOpenAL::GetDeviceList(bool bPlaybackDevice, Array<String>& outDevices)
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
            if (StrUtil::StringCompair(AudioOpenAL::OALDevicePrefix, curName, AudioOpenAL::OALDevicePrefixLen))
            {
                curName += AudioOpenAL::OALDevicePrefixLen;
            }

            outDevices.push_back(curName);
        }

        return hr;
    }

    const char* AudioEngineComponentOpenAL::GetDefaultDeviceName(bool bPlaybackDevice)
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

        if (StrUtil::StringCompair(AudioOpenAL::OALDevicePrefix, defaultDeviceName, AudioOpenAL::OALDevicePrefixLen))
        {
            defaultDeviceName += AudioOpenAL::OALDevicePrefixLen;
        }

        return defaultDeviceName;
    }

    Result AudioEngineComponentOpenAL::SetPlaybackDevice(const char* deviceName)
    {
        if (deviceName == nullptr)
        {
            deviceName = GetDefaultDeviceName(true);
        }

        if (m_PlaybackDevice.IsValid() && m_PlaybackDevice->GetDeviceName() == deviceName)
        {
            return ResultCode::SUCCESS;
        }

        Result hr;
        auto* pDevice = new(GetSystemHeap()) AudioPlaybackDeviceOpenAL(deviceName);

        defCheck(pDevice->Initialize());

        m_PlaybackDevice = pDevice;

        OnPlaybackDeviceChanged.Invoke(pDevice);

        return hr;
    }


    AudioRecorderPtr AudioEngineComponentOpenAL::CreateRecorder(const char* deviceName)
    {
        if (deviceName == nullptr)
        {
            deviceName = GetDefaultDeviceName(false);
        }

        return new(GetSystemHeap()) AudioRecorderOpenAL(deviceName);
    }

    AudioBufferPtr AudioEngineComponentOpenAL::CreateBuffer(uint numChannels, EAudioFormat format, uint samplesPerSec, size_t bufferSize)
    {
        AudioBuffer* newBuffer = new(GetSystemHeap()) AudioBuffer(numChannels, format, samplesPerSec, bufferSize);

        return newBuffer;
    }

    AudioSourcePtr AudioEngineComponentOpenAL::CreateSource(uint numChannels, EAudioFormat format, uint samplesPerSec)
    {
        if (!m_PlaybackDevice.IsValid())
        {
            SFLog(System, Error, "Audio system hans't initialized");
            return nullptr;
        }

        AudioSourceOpenAL* newPlayer = new(GetSystemHeap()) AudioSourceOpenAL(numChannels, format, samplesPerSec);

        WeakPointerT<AudioSourceOpenAL> audioSourceWeakPtr = newPlayer;
        RunOnAudioThread([this, audioSourceWeakPtr]()
            {
                AudioSourceOpenALPtr audioSourcePtr = audioSourceWeakPtr.AsSharedPtr<AudioSourceOpenAL>();
                if (audioSourcePtr != nullptr)
                {
                    m_PlaybackDevice->AddAudioSource(audioSourcePtr.get());
                }
            });


        return newPlayer;
    }

    AudioSourcePtr AudioEngineComponentOpenAL::CreateSource(const AudioBufferPtr& buffer)
    {
        if (!m_PlaybackDevice.IsValid())
        {
            SFLog(System, Error, "Audio system hans't initialized");
            return nullptr;
        }

        AudioSourceOpenAL* newPlayer = new(GetSystemHeap()) AudioSourceOpenAL(buffer);

        WeakPointerT<AudioSourceOpenAL> audioSourceWeakPtr = newPlayer;
        RunOnAudioThread([this, audioSourceWeakPtr]()
            {
                AudioSourceOpenALPtr audioSourcePtr = audioSourceWeakPtr.AsSharedPtr<AudioSourceOpenAL>();
                if (audioSourcePtr != nullptr)
                {
                    m_PlaybackDevice->AddAudioSource(audioSourcePtr.get());
                }
            });


        return newPlayer;
    }

    AudioListenerPtr AudioEngineComponentOpenAL::GetListener()
    {
        return m_Listener;
    }

    void AudioEngineComponentOpenAL::SetMasterPlaybackVolume(float volume)
    {
        m_MasterPlaybackVolume = volume;
        alListenerf(AL_GAIN, volume);
    }

    void AudioEngineComponentOpenAL::RunOnAudioThread(std::function<void()>&& task)
    {
        MutexScopeLock lock(m_RequestLock);
        m_Requests.Enqueue(Forward<std::function<void()>>(task));
    }

    void AudioEngineComponentOpenAL::RunOnAudioThread(const std::function<void()>& task)
    {
        MutexScopeLock lock(m_RequestLock);
        m_Requests.Enqueue(task);
    }


    void AudioEngineComponentOpenAL::TickUpdate()
    {
        auto playbackDevice = m_PlaybackDevice.get();
        if (playbackDevice == nullptr)
            return;

        playbackDevice->MakeCurrentContext();

        auto* pListener = static_cast<AudioListenerOpenAL*>(m_Listener.get());
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
