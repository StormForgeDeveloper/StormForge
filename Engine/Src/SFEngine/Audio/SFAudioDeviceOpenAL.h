////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Audio Device OpenAL
//	
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "SFTypedefs.h"
#include "Audio/SFAudioService.h"
#include "Audio/SFAudioOpenAL.h"
#include "Container/SFDoubleLinkedList.h"
#include <AL\alc.h>


namespace SF
{
    class AudioSourceOpenAL;

    /////////////////////////////////////////////////////////////////////////////////////
    // 
    //	Audio playback device
    // 
    class AudioPlaybackDeviceOpenAL : public AudioPlaybackDevice
    {
    public:


        AudioPlaybackDeviceOpenAL(const char* deviceName);
        ~AudioPlaybackDeviceOpenAL();

        const String& GetOALDeviceName() const { return m_OALDeviceName; }

        // Initialize
        Result Initialize();

        virtual void Dispose() { Clear(); }

        // clear
        void Clear();

        void AddAudioSource(AudioSourceOpenAL* audioSource);

        void MakeCurrentContext();
        void TickUpdate();


    private:
        String m_OALDeviceName;

        ALCdevice* m_pDevice{};
        ALCcontext* m_pContext{};

        // Only audio thread can add/remove
        using AudioSourceList = DoubleLinkedListStaticT<WeakPointerT<AudioSourceOpenAL>, ThreadSyncTraitNone>;
        AudioSourceList m_AudioSourceList;
    };

    using AudioPlaybackDeviceOpenALPtr = SharedPointerT<AudioPlaybackDeviceOpenAL>;

}
