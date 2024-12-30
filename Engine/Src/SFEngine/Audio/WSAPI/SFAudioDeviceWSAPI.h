////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Audio Device WSAPI
//	
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "SFTypedefs.h"
#include "Audio/SFAudioService.h"


#include "Audio/WSAPI/SFAudioWSAPI.h"
#include "Audio/WSAPI/SFAudioSourceWSAPI.h"
#include "Container/SFDoubleLinkedList.h"
#include "AL/alc.h"


namespace SF
{
    class AudioSourceWSAPI;

    /////////////////////////////////////////////////////////////////////////////////////
    // 
    //	Audio playback device
    // 
    class AudioPlaybackDeviceWSAPI : public AudioPlaybackDevice
    {
    public:


        AudioPlaybackDeviceWSAPI(const char* deviceName);
        ~AudioPlaybackDeviceWSAPI();

        const String& GetOALDeviceName() const { return m_OALDeviceName; }

        // Initialize
        Result Initialize();

        virtual void Dispose() { Clear(); }

        // clear
        void Clear();

        void AddAudioSource(const AudioSourceWSAPIPtr& audioSource);

        void MakeCurrentContext();
        void TickUpdate();


    private:
        String m_OALDeviceName;

        ALCdevice* m_pDevice{};
        ALCcontext* m_pContext{};

        // Only audio thread can add/remove
        using AudioSourceList = DoubleLinkedListStaticT<WeakPointerT<AudioSourceWSAPI>, ThreadSyncTraitNone>;
        AudioSourceList m_AudioSourceList;
    };

    using AudioPlaybackDeviceWSAPIPtr = SharedPointerT<AudioPlaybackDeviceWSAPI>;

}
