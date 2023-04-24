////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Audio Player OpenAL
//	
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "SFTypedefs.h"
#include "Audio/SFAudioService.h"


namespace SF
{

    /////////////////////////////////////////////////////////////////////////////////////
    // 
    //	Audio player
    // 
    class AudioPlayerOpenAL : public AudioPlayer
    {
    public:
        AudioPlayerOpenAL();
        virtual ~AudioPlayerOpenAL();

        virtual Result Play() override;
        virtual Result Stop() override;
        virtual Result Pause() override;

    };


}
