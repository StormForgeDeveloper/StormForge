////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Audio Buffer WSAPI
//	
//
////////////////////////////////////////////////////////////////////////////////

#include "SFEnginePCH.h"


#include "Audio/WSAPI/SFAudioWSAPI.h"
#include "AL/al.h"
#include "AL/alext.h"
#include "AL/alc.h"


namespace SF
{

    ALCenum AudioWSAPI::GetAudioFormat(uint numChannel, EAudioFormat format)
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
                SFLog(System, Error, "AudioWSAPI::GetAudioFormat unknown format:{0}", int(format));
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
                SFLog(System, Error, "AudioWSAPI::GetAudioFormat unknown format:{0}", int(format));
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


    void AudioWSAPI::ClearALError()
    {
        ALenum alError = alGetError();
        // if there is not current context, it will return AL_INVALID_OPERATION always.
        while (alError != AL_NO_ERROR && alError != AL_INVALID_OPERATION)
        {
            alError = alGetError();
        }
    }

    Result AudioWSAPI::GetALError()
    {
        ALenum alError = alGetError();
        switch (alError)
        {
        case AL_NO_ERROR: return ResultCode::SUCCESS;
        case AL_INVALID_NAME: return ResultCode::INVALID_NAME;
        case AL_INVALID_ENUM: return ResultCode::INVALID_ENUM;
        case AL_INVALID_VALUE: return ResultCode::INVALID_ARG;
        case AL_INVALID_OPERATION: return ResultCode::INVALID_STATE;
        case AL_OUT_OF_MEMORY: return ResultCode::OUT_OF_MEMORY;
        default:
            return ResultCode::UNEXPECTED;
        }
    }
}
