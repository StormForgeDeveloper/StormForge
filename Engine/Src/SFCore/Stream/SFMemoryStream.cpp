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



#include "SFCorePCH.h"
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
		: m_BufferView(memoryBuffer.size(), memoryBuffer.data())
	{
	}

	InputMemoryStream::InputMemoryStream(const Array<const uint8_t>& memoryBuffer)
		: m_BufferView(memoryBuffer.size(), memoryBuffer.data())
	{
	}

	// Reset position to begin
	void InputMemoryStream::Reset()
	{
		m_Position = 0;
	}

	Result InputMemoryStream::Seek(SeekMode seekPos, int64_t offset)
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
		default:
			return ResultCode::INVALID_ARG;
		}

		if (newPos > (int64_t)GetSize()) newPos = GetSize();
		if (newPos < 0) newPos = 0;
		m_Position = static_cast<size_t>(newPos);

		return ResultCode::SUCCESS;
	}

	Result InputMemoryStream::Read(void* buffer, size_t readSize)
	{
		if (buffer == nullptr)
			return ResultCode::INVALID_ARG;

		if (readSize == 0)
			return ResultCode::SUCCESS;

		if (m_BufferView.size() <= m_Position)
			return ResultCode::END_OF_STREAM;

		auto actualReadSize = std::min(m_BufferView.size() - m_Position, readSize);

		memcpy(buffer, m_BufferView.data() + m_Position, actualReadSize);
		m_Position += actualReadSize;

		return actualReadSize == readSize ? ResultCode::SUCCESS : ResultCode::END_OF_STREAM;
	}





	/////////////////////////////////////////////////////////////////////////////
	//
	//	OutputMemoryStream
	//

	OutputMemoryStream::OutputMemoryStream()
		: m_IsBufferOwner(true)
		, m_IsBufferResizeAllowed(true)
	{
		m_Buffer = new DynamicArray<uint8_t>;
	}

	OutputMemoryStream::OutputMemoryStream(Array<uint8_t>& memorySource, bool bAllowResize)
		: m_IsBufferOwner(false)
		, m_IsBufferResizeAllowed(bAllowResize)
		, m_Buffer(&memorySource)
	{
	}

	OutputMemoryStream::~OutputMemoryStream()
	{
		if (m_IsBufferOwner)
			delete (m_Buffer);
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

