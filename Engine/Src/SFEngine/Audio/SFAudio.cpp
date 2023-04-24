////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Audio
//	
//
////////////////////////////////////////////////////////////////////////////////

#include "SFEnginePCH.h"
#include "Audio/SFAudio.h"


namespace SF
{

    size_t Audio::GetBitsPerSample(uint numChannel, EAudioFormat format)
    {
        uint bitsPerData = 0;
        switch (format)
        {
        case EAudioFormat::Int8:
            bitsPerData = 8;
            break;
        case EAudioFormat::Int16:
            bitsPerData = 16;
            break;
        case EAudioFormat::Float:
            bitsPerData = 32;
            break;
        default:
            SFLog(System, Error, "Audio::GetBitsPerFrame: Unknown audio format:{0}", int(format))
            return 0;
        }

        return bitsPerData * numChannel;
    }

    size_t Audio::GetBytesPerSample(uint numChannel, EAudioFormat format)
    {
        size_t bitsPerSample = GetBitsPerSample(numChannel, format);

        return bitsPerSample / 8;
    }
}
