////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Audio service
//	
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "SFTypedefs.h"
#include "Service/SFService.h"
#include "Object/SFSharedObject.h"
#include "Object/SFSharedPointer.h"
#include "Delegate/SFEventDelegate.h"
#include "Audio/SFAudioTypes.h"
#include "Audio/SFAudioSource.h"
#include "Audio/SFAudioListener.h"
#include "Audio/SFAudio.h"

namespace SF
{
   
    // base classes
    class AudioPlaybackDevice : public SharedObject
    {
    public:
        AudioPlaybackDevice(const char* deviceName)
            : m_DeviceName(deviceName)
        {
        }

        virtual ~AudioPlaybackDevice() = default;

        const String& GetDeviceName() const { return m_DeviceName; }

    private:

        String m_DeviceName;
    };
    using AudioPlaybackDevicePtr = SharedPointerT<AudioPlaybackDevice>;


    class AudioRecorder : public SharedObject
    {
    public:
        AudioRecorder(const char* deviceName)
            : m_DeviceName(deviceName)
        {}
        virtual ~AudioRecorder() = default;

        SF_FORCEINLINE uint GetNumChannels() const { return m_Channels; }
        SF_FORCEINLINE EAudioFormat GetFormat() const { return m_Format; }
        SF_FORCEINLINE uint GetSamplesPerSec() const { return m_SamplesPerSec; }
        SF_FORCEINLINE uint GetSampleFrameSize() const { return m_SampleFrameSize; }
        SF_FORCEINLINE uint GetRecordingBufferSize() { return m_RecordingBufferSize; }
        SF_FORCEINLINE bool IsRecording() const { return m_IsRecording; }

        virtual Result Initialize(uint numChannel, EAudioFormat format, uint samplesPerSec, int bufferingDurationSec = 10);

        virtual Result StartRecording() = 0;
        virtual Result StopRecording() = 0;

        virtual size_t GetAvailableSampleCount() = 0;
        virtual Result ReadSamples(Array<uint8_t>& outBuffer) = 0;

    protected:

        String m_DeviceName;

        uint m_Channels = 1;
        EAudioFormat m_Format = EAudioFormat::Float;
        uint m_SamplesPerSec = 44100;
        uint m_SampleFrameSize{};
        uint m_RecordingBufferSize{};
        bool m_IsRecording = false;

    };
    using AudioRecorderPtr = SharedPointerT<AudioRecorder>;


    class AudioPlayer : public SharedObject
    {
    public:
        AudioPlayer() = default;
        virtual ~AudioPlayer() = default;

        virtual Result Play() = 0;
        virtual Result Stop() = 0;
        virtual Result Pause() = 0;
    };
    using AudioPlayerPtr = SharedPointerT<AudioPlayer>;



    // Audio service interface
    class AudioService
    {
    public:
        AudioService();
        virtual ~AudioService() {}

        virtual Result GetDeviceList(bool bPlaybackDevice, Array<String>& outDevices) { return ResultCode::NOT_IMPLEMENTED; }
        virtual String GetDefaultDeviceName(bool bPlaybackDevice) { return nullptr; }

        virtual Result SetPlaybackDevice(const char* deviceName) { return ResultCode::NOT_IMPLEMENTED; }

        // Get device with the name
        virtual const AudioPlaybackDevicePtr GetPlaybackDevice() { return nullptr; }

        // Create audio buffer
        virtual AudioBufferPtr CreateBuffer(uint numChannels, EAudioFormat format, uint samplesPerSec, size_t bufferSize) { return nullptr; }

        // Create audio play source
        virtual AudioSourcePtr CreateSource(uint numChannels, EAudioFormat format, uint samplesPerSec) { return nullptr; }
        virtual AudioSourcePtr CreateSource(const AudioBufferPtr& buffer) { return nullptr; }

        // Create audio recorder
        virtual AudioRecorderPtr CreateRecorder(const char* deviceName) { return nullptr; }

        virtual AudioListenerPtr GetListener() { return nullptr; }


        // Queue actor to audio thread
        virtual void RunOnAudioThread(std::function<void()>&& task) {}
        virtual void RunOnAudioThread(const std::function<void()>& task) {}

        // Event functions
        EventDelegateList<const AudioPlaybackDevicePtr&> OnPlaybackDeviceChanged;
    };



    namespace Service
    {
        extern ServiceInstance<AudioService> Audio;
    }
}
