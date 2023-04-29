////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Audio buffer
//	
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "SFTypedefs.h"
//#include "Container/SFCircularBuffer.h"
#include "MemoryManager/SFCircularHeap.h"
#include "Container/SFCircularPageQueue.h"
#include "Audio/SFAudioTypes.h"


namespace SF
{
    // Audio data block definition
    struct AudioDataBlock
    {
        size_t DataSize = 0;
        uint8_t Data[1];
    };

    class IOutputStream;
    IOutputStream& operator << (IOutputStream& stream, const AudioDataBlock& block);

	/////////////////////////////////////////////////////////////////////////////////////
	// 
	//	Audio buffer
	// 
	class AudioBuffer : public SharedObject
	{
	public:


        AudioBuffer(uint numChannels, EAudioFormat dataFormat, uint samplesPerSec, size_t streamingBufferSize);
        virtual ~AudioBuffer();

        virtual void Dispose() override;

        void Clear();

        bool HasFinished() const { return m_bFinished; }
        void SetFinished(bool bFinished) { m_bFinished = bFinished; }
        uint GetNumChannels() const { return m_NumChannels; }
        EAudioFormat GetAudioFormat() const { return m_DataFormat; }
        uint GetSamplesPerSec() const { return m_SamplesPerSec; }


        // returns available block count
        size_t GetAvailableBlockCount() const { return m_DataQueue.size(); }

        // push a block data
        Result EnqueueBlock(const Array<uint8_t>& blockData);
        // Pop a block from front. If IsStream=true popped block will be removed from the stream
        AudioDataBlock* DequeueBlock();

    private:

        bool m_bFinished = false;
        uint m_NumChannels = 1;
        EAudioFormat m_DataFormat = EAudioFormat::Float;
        size_t m_BytesPerSample = 0;
        // guide value for audio source
        uint m_SamplesPerSec = 44100;

        SharedPointerT<CircularHeap> m_HeapPtr;
        CircularPageQueue<AudioDataBlock*> m_DataQueue;
    };

    using AudioBufferPtr = SharedPointerT<AudioBuffer>;

}
