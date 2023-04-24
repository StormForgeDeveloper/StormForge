////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Audio recorder OpenAL
//	
//
////////////////////////////////////////////////////////////////////////////////

#include "SFEnginePCH.h"
#include "Audio/SFAudioDeviceOpenAL.h"
#include "Audio/SFAudioRecorderOpenAL.h"

namespace SF
{
    AudioRecorderOpenAL::AudioRecorderOpenAL(const char* deviceName)
        : AudioRecorder(deviceName)
    {
        m_OALDeviceName.Format("{0}{1}", AudioOpenAL::OALDevicePrefix, deviceName);
    }

    AudioRecorderOpenAL::~AudioRecorderOpenAL()
    {
        if (m_pDevice)
        {
            alcCaptureCloseDevice(m_pDevice);
            m_pDevice = nullptr;
        }
    }

    Result AudioRecorderOpenAL::Initialize(uint numChannel, EAudioFormat format, uint samplesPerSec, int bufferingDurationSec)
    {
        Result hr;

        defCheck(super::Initialize(numChannel, format, samplesPerSec, bufferingDurationSec));

        m_Format = AudioOpenAL::GetAudioFormat(GetNumChannels(), GetFormat());
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

    Result AudioRecorderOpenAL::StartRecording()
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

    Result AudioRecorderOpenAL::StopRecording()
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

    size_t AudioRecorderOpenAL::GetAvailableSampleCount()
    {
        if (m_pDevice == nullptr)
        {
            return 0;
        }

        ALCint availableSampleCount = 0;
        alcGetIntegerv(m_pDevice, ALC_CAPTURE_SAMPLES, 1, &availableSampleCount);

        return availableSampleCount;
    }

    Result AudioRecorderOpenAL::ReadSamples(Array<uint8_t>& outBuffer)
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

        size_t maxFramesReadCanRead = outBuffer.capacity() / GetSampleFrameSize();

        size_t sampleCount = Math::Min<size_t>(maxFramesReadCanRead, availableSampleCount);

        size_t curBufferPos = outBuffer.size();
        outBuffer.resize(curBufferPos + sampleCount * GetSampleFrameSize());

        alcCaptureSamples(m_pDevice, outBuffer.data() + curBufferPos, ALCsizei(sampleCount));
        err = alcGetError(m_pDevice);
        if (err != ALC_NO_ERROR)
        {
            SFLog(System, Error, "alcCaptureSamples fail:{0}", int(err));
            return ResultCode::UNEXPECTED;
        }
        else
        {
            return ResultCode::SUCCESS;
        }
    }

}
