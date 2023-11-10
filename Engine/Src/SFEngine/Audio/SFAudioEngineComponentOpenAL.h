////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Audio Engine component
//	
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "SFTypedefs.h"
#include "Component/SFLibraryComponent.h"
#include "Audio/SFAudioService.h"
#include "Audio/SFAudioDeviceOpenAL.h"
#include "Container/SFCircularPageQueue.h"
#include "Container/SFDoubleLinkedList.h"


namespace SF
{
    class AudioDeviceOpenAL;

	/////////////////////////////////////////////////////////////////////////////////////
	// 
	//	AudioEngineCmponent
	// 
	class AudioEngineComponentOpenAL : public LibraryComponent, public AudioService
	{
	public:

		using super = LibraryComponent;

        static constexpr StringCrc64 TypeName = "AudioEngineComponentOpenAL";

	public:

        AudioEngineComponentOpenAL();
		virtual ~AudioEngineComponentOpenAL();

        virtual const StringCrc64& GetTypeName() const override { return TypeName; }

        // Initialize component
        virtual Result InitializeComponent() override;
        // Terminate component
        virtual void DeinitializeComponent() override;


        // Implementation
        virtual Result GetDeviceList(bool bPlaybackDevice, Array<String>& outDevices) override;
        virtual const char* GetDefaultDeviceName(bool bPlaybackDevice) override;

        virtual Result SetPlaybackDevice(const char* deviceName) override;

        // Create audio buffer
        virtual AudioBufferPtr CreateBuffer(uint numChannels, EAudioFormat format, uint samplesPerSec, size_t bufferSize) override;

        // Create audio play source
        virtual AudioSourcePtr CreateSource(uint numChannels, EAudioFormat format, uint samplesPerSec) override;
        virtual AudioSourcePtr CreateSource(const AudioBufferPtr& buffer) override;

        // Create audio recorder
        virtual AudioRecorderPtr CreateRecorder(const char* deviceName) override;

        // Get device with the name
        virtual const AudioPlaybackDevicePtr GetPlaybackDevice() override { return m_PlaybackDevice.StaticCast<AudioPlaybackDevice>(); }

        // Get Listener
        virtual AudioListenerPtr GetListener() override;

        virtual void SetMasterPlaybackVolume(float volume) override;
        virtual float GetMasterPlaybackVolume() override { return m_MasterPlaybackVolume; }

        virtual void RunOnAudioThread(std::function<void()>&& task) override;
        virtual void RunOnAudioThread(const std::function<void()>& task) override;


    private:

        void TickUpdate();

    private:

        // Playback device
        AudioPlaybackDeviceOpenALPtr m_PlaybackDevice;

        // Listener
        AudioListenerPtr m_Listener;

        // Audio thread
        SFUniquePtr<Thread> m_AudioThread;

        CriticalSection m_RequestLock;
        CircularPageQueue<std::function<void()>> m_Requests;

        // Master playback volume
        float m_MasterPlaybackVolume = 1;
	};

}
