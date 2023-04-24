////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Audio Data
//	
//
////////////////////////////////////////////////////////////////////////////////

#include "SFEnginePCH.h"
#include "Audio/SFAudioBuffer.h"
#include "Audio/SFAudio.h"


namespace SF
{

    AudioBuffer::AudioBuffer(uint numChannels, EAudioFormat dataFormat, uint samplesPerSec, size_t streamingBufferSize)
        : m_NumChannels(numChannels)
        , m_DataFormat(dataFormat)
        , m_BytesPerSample(Audio::GetBytesPerSample(numChannels, dataFormat))
        , m_SamplesPerSec(samplesPerSec)
        , m_DataQueue(GetSystemHeap(), 8)
    {
        m_HeapPtr = new CircularHeap(GetSystemHeap(), streamingBufferSize);
    }

    AudioBuffer::~AudioBuffer()
    {
        Clear();
    }

    void AudioBuffer::Dispose()
    {
        Clear();
        m_HeapPtr = nullptr;
    }

    void AudioBuffer::Clear()
    {
        AudioDataBlock* block{};
        while (m_DataQueue.Dequeue(block))
        {
            if (m_HeapPtr.IsValid())
            {
                m_HeapPtr->Free(block);
            }
            else
            {
                IHeap::Delete(block);
            }
        }
    }

    Result AudioBuffer::EnqueueBlock(const Array<uint8_t>& blockData)
    {
        size_t remain = blockData.size() % m_BytesPerSample;
        if (remain != 0)
        {
            SFLog(System, Warning, "Pushed block isn't aligned to bytes per sample");
        }

        AudioDataBlock* dataPtr{};

        if (m_HeapPtr != nullptr)
        {
            dataPtr = (AudioDataBlock*)m_HeapPtr->Alloc(sizeof(AudioDataBlock) + blockData.size());
        }
        else
        {
            dataPtr = (AudioDataBlock*)GetSystemHeap().Alloc(sizeof(AudioDataBlock) + blockData.size());
        }

        memset(dataPtr, 0, sizeof(AudioDataBlock));
        dataPtr->DataSize = blockData.size();
        memcpy(dataPtr->Data, blockData.data(), blockData.size());

        return m_DataQueue.Enqueue(dataPtr);
    }

    // Pop a block from front. If IsStream=true popped block will be removed from the stream
    AudioBuffer::AudioDataBlock* AudioBuffer::DequeueBlock()
    {
        AudioDataBlock* block{};

        m_DataQueue.Dequeue(block);

        return block;
    }




}
