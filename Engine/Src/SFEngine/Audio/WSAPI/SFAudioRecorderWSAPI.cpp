////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Audio recorder WSAPI
//	
//
////////////////////////////////////////////////////////////////////////////////

#include "SFEnginePCH.h"

#include "Audio/WSAPI/SFAudioDeviceWSAPI.h"
#include "Audio/WSAPI/SFAudioRecorderWSAPI.h"

namespace SF
{
    AudioRecorderWSAPI::AudioRecorderWSAPI(const char* deviceName)
        : AudioRecorder(deviceName)
    {
        m_OALDeviceName.Format("{0}{1}", AudioWSAPI::OALDevicePrefix, deviceName);
    }

    AudioRecorderWSAPI::~AudioRecorderWSAPI()
    {
        if (m_pDevice)
        {
            alcCaptureCloseDevice(m_pDevice);
            m_pDevice = nullptr;
        }
    }

    Result AudioRecorderWSAPI::Initialize(uint numChannel, EAudioFormat format, uint samplesPerSec, int bufferingDurationSec)
    {
        Result hr;

        defCheck(super::Initialize(numChannel, format, samplesPerSec, bufferingDurationSec));

        m_Format = AudioWSAPI::GetAudioFormat(GetNumChannels(), GetFormat());
        if (m_Format == AL_NONE)
        {
            return ResultCode::NOT_SUPPORTED_FORMAT;
        }

        m_pDevice = alcCaptureOpenDevice(m_OALDeviceName, GetSamplesPerSec(), m_Format, GetRecordingBufferSize());
        if (m_pDevice == nullptr)
        {
            SFLog(System, Error, "Failed to open {0}, format:{1}, bufferSize:{2}",
                m_OALDeviceName,
                int(m_Format),
                GetRecordingBufferSize()
            );
            return ResultCode::UNEXPECTED;
        }

        return hr;
    }

    Result AudioRecorderWSAPI::StartRecording()
    {
        Result hr;

        if (m_pDevice == nullptr)
        {
            return ResultCode::NOT_INITIALIZED;
        }

        if (m_IsRecording)
        {
            return ResultCode::SUCCESS_FALSE;
        }

        m_IsRecording = true;

        alcCaptureStart(m_pDevice);

        return hr;
    }

    Result AudioRecorderWSAPI::StopRecording()
    {
        Result hr;

        if (!m_IsRecording)
        {
            return ResultCode::SUCCESS_FALSE;
        }

        m_IsRecording = false;

        if (m_pDevice == nullptr)
        {
            return ResultCode::NOT_INITIALIZED;
        }

        alcCaptureStop(m_pDevice);

        return hr;
    }

    size_t AudioRecorderWSAPI::GetAvailableSampleCount()
    {
        if (m_pDevice == nullptr)
        {
            return 0;
        }

        ALCint availableSampleCount = 0;
        alcGetIntegerv(m_pDevice, ALC_CAPTURE_SAMPLES, 1, &availableSampleCount);

        return availableSampleCount;
    }

    Result AudioRecorderWSAPI::ReadSamples(Array<uint8_t>& outBuffer)
    {
        if (m_pDevice == nullptr)
        {
            return ResultCode::NOT_INITIALIZED;
        }

        ALCint availableSampleCount = 0;
        alcGetIntegerv(m_pDevice, ALC_CAPTURE_SAMPLES, 1, &availableSampleCount);
        ALCenum err = alcGetError(m_pDevice);
        if (err != ALC_NO_ERROR)
        {
            SFLog(System, Error, "alcGetIntegerv ALC_CAPTURE_SAMPLES fail:{0}", int(err));
            return ResultCode::UNEXPECTED;
        }

        size_t curBufferPos = outBuffer.size();
        size_t maxFramesCanRead = (outBuffer.capacity() - curBufferPos) / GetSampleFrameSize();
        if (maxFramesCanRead == 0)
        {
            SFLog(System, Error, "AudioRecorderWSAPI::ReadSamples fail, read bffersize:{0}, maxFramesCanRead:{1}, availableSampleCount:{2}", outBuffer.size(), maxFramesCanRead, availableSampleCount);
            return ResultCode::OUT_OF_MEMORY;
        }

        size_t sampleCount = Math::Min<size_t>(maxFramesCanRead, availableSampleCount);

        assert((curBufferPos + sampleCount * GetSampleFrameSize()) <= outBuffer.capacity());
        outBuffer.resize(curBufferPos + sampleCount * GetSampleFrameSize());

        alcCaptureSamples(m_pDevice, outBuffer.data() + curBufferPos, ALCsizei(sampleCount));
        err = alcGetError(m_pDevice);
        if (err != ALC_NO_ERROR)
        {
            SFLog(System, Error, "alcCaptureSamples fail:{0}, sampleCount:{1}, availableSampleCount:{2}", int(err), sampleCount, availableSampleCount);
            return ResultCode::UNEXPECTED;
        }
        else
        {
            return ResultCode::SUCCESS;
        }
    }
}

