////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Audio Buffer
//	
//
////////////////////////////////////////////////////////////////////////////////

#include "SFEnginePCH.h"
#include "Audio/SFAudioOpenAL.h"
#include <AL\al.h>
#include <AL\alext.h>
#include <AL\alc.h>


namespace SF
{

    ALCenum AudioOpenAL::GetAudioFormat(uint numChannel, EAudioFormat format)
    {
        ALCenum alFormat = AL_NONE;

        if (numChannel == 1)
        {
            switch (format)
            {
            case EAudioFormat::Int8:
                alFormat = AL_FORMAT_MONO8;
                break;
            case EAudioFormat::Int16:
                alFormat = AL_FORMAT_MONO16;
                break;
            case EAudioFormat::Float:
                alFormat = AL_FORMAT_MONO_FLOAT32;
                break;
            default:
                SFLog(System, Error, "AudioOpenAL::GetAudioFormat unknown format:{0}", int(format));
                return AL_NONE;
                break;
            }
        }
        else if (numChannel == 2)
        {
            switch (format)
            {
            case EAudioFormat::Int8:
                alFormat = AL_FORMAT_STEREO8;
                break;
            case EAudioFormat::Int16:
                alFormat = AL_FORMAT_STEREO16;
                break;
            case EAudioFormat::Float:
                alFormat = AL_FORMAT_STEREO_FLOAT32;
                break;
            default:
                SFLog(System, Error, "AudioOpenAL::GetAudioFormat unknown format:{0}", int(format));
                return AL_NONE;
                break;
            }
        }
        else
        {
            SFLog(System, Error, "Not supported audio format, channel:{0}, format:{1}", numChannel, int(format));
            return AL_NONE;
        }

        return alFormat;
    }

}
