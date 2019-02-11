////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2017 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : SFFileOutputStream
//	
//
////////////////////////////////////////////////////////////////////////////////



#include "CoreBasePCH.h"
#include "SFTypedefs.h"
#include "Stream/SFMemoryStream.h"




namespace SF {


	/////////////////////////////////////////////////////////////////////////////
	//
	//	InputMemoryStream
	//

	InputMemoryStream::InputMemoryStream()
	{

	}

	InputMemoryStream::InputMemoryStream(const Array<uint8_t>& memoryBuffer)
		: m_Buffer(&memoryBuffer)
	{
	}

	// Reset position to begin
	void InputMemoryStream::Reset()
	{
		m_Position = 0;
	}

	size_t InputMemoryStream::Seek(SeekMode seekPos, int64_t offset)
	{
		int64_t newPos;
		switch (seekPos)
		{
		case SeekMode::Begin:
			newPos = offset;
			break;
		case SeekMode::Current:
			newPos = m_Position + offset;
			break;
		case SeekMode::End:
			newPos = (int64_t)GetSize() - offset;
			break;
		}

		if (newPos > (int64_t)GetSize()) newPos = GetSize();
		if (newPos < 0) newPos = 0;
		m_Position = static_cast<size_t>(newPos);

		return m_Position;
	}

	Result InputMemoryStream::Read(void* buffer, size_t readSize)
	{
		if (m_Buffer == nullptr)
			return ResultCode::INVALID_STATE;

		if (buffer == nullptr)
			return ResultCode::INVALID_ARG;

		if (readSize == 0)
			return ResultCode::SUCCESS;

		if (m_Buffer->size() <= m_Position)
			return ResultCode::END_OF_STREAM;

		auto actualReadSize = std::min(m_Buffer->size() - m_Position, readSize);

		memcpy(buffer, m_Buffer->data() + m_Position, actualReadSize);
		m_Position += actualReadSize;

		return actualReadSize == readSize ? ResultCode::SUCCESS : ResultCode::END_OF_STREAM;
	}





	/////////////////////////////////////////////////////////////////////////////
	//
	//	OutputMemoryStream
	//

	OutputMemoryStream::OutputMemoryStream(IHeap& heap)
		: m_IsBufferOwner(true)
		, m_IsBufferResizeAllowed(true)
	{
		m_Buffer = new(heap) DynamicArray<uint8_t>(heap);
	}

	OutputMemoryStream::OutputMemoryStream(Array<uint8_t>& memorySource)
		: m_IsBufferOwner(false)
		, m_IsBufferResizeAllowed(false)
		, m_Buffer(&memorySource)
	{
	}

	OutputMemoryStream::~OutputMemoryStream()
	{
		if (m_IsBufferOwner)
			IHeap::Delete(m_Buffer);
		m_Buffer = nullptr;
	}

	void OutputMemoryStream::Reset()
	{
		m_Buffer->resize(0);
	}

	Result OutputMemoryStream::Write(const void* buffer, size_t writeSize)
	{
		auto requiredSize = m_Buffer->size() + writeSize;
		if (m_IsBufferResizeAllowed)
		{
			if (m_Buffer->GetAllocatedSize() < requiredSize)
				m_Buffer->reserve(requiredSize);
		}
		else
		{
			if (m_Buffer->GetAllocatedSize() < requiredSize)
				return ResultCode::OUT_OF_RESERVED_MEMORY;
		}

		auto offset = m_Buffer->size();
		m_Buffer->resize(m_Buffer->size() + writeSize);
		memcpy(m_Buffer->data() + offset, buffer, writeSize);

		return ResultCode::SUCCESS;
	}

}

