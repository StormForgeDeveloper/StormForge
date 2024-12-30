////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Audio Player WSAPI
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
    class AudioPlayerWSAPI : public AudioPlayer
    {
    public:
        AudioPlayerWSAPI();
        virtual ~AudioPlayerWSAPI();

        virtual Result Play() override;
        virtual Result Stop() override;
        virtual Result Pause() override;

    };


}
