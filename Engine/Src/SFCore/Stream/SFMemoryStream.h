////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2016 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Memory manager
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "SFTypedefs.h"
#include "Stream/SFStream.h"
#include "Container/SFArray.h"


namespace SF
{

	/////////////////////////////////////////////////////////////////////////////////////////
	//
	// Input memory stream class
	//

	class InputMemoryStream : public IInputStream
	{
	protected:

		const Array<uint8_t>* m_Buffer = nullptr;

		size_t m_Position = 0;


	public:

		InputMemoryStream();
		InputMemoryStream(const Array<uint8_t>& memoryBuffer);
		virtual ~InputMemoryStream() {}

		// Reset position to begin
		void Reset();

		size_t GetBufferSize() const { return m_Buffer == nullptr ? 0 : m_Buffer->GetAllocatedSize(); }

		// return true if the stream is valid and have something read
		virtual bool CanRead() override { return m_Buffer != nullptr && m_Position < m_Buffer->size(); }

		virtual uint8_t* GetBufferPtr() override { return const_cast<uint8_t*>(m_Buffer->data()); }
		virtual const uint8_t* GetBufferPtr() const override { return m_Buffer->data(); }

		virtual size_t Seek(SeekMode seekPos, int64_t offset) override;

		virtual size_t GetPosition() const override { return m_Position; }

		virtual size_t GetSize() const override { return m_Buffer == nullptr ? 0 : m_Buffer->size(); }

		// Read data
		virtual Result Read(void* buffer, size_t readSize) override;
	};


	/////////////////////////////////////////////////////////////////////////////////////////
	//
	// Output memory stream class
	//

	class OutputMemoryStream : public IOutputStream
	{
	private:
		bool m_IsBufferOwner = true;
		bool m_IsBufferResizeAllowed = true;
		Array<uint8_t>* m_Buffer = nullptr;

	public:

		OutputMemoryStream(IHeap& memoryManager);
		OutputMemoryStream(Array<uint8_t>& memorySource);
		virtual ~OutputMemoryStream();

		// Reset position to begin
		void Reset();

		size_t capacity() const { return m_Buffer == nullptr ? 0 : m_Buffer->GetAllocatedSize(); }
		Array<uint8_t>& GetBuffer() const { return *m_Buffer; }
		const uint8_t* data() const { return m_Buffer->data(); }

		// return true if the stream is valid and able to be written
		virtual bool CanWrite() override { return m_Buffer != nullptr && (m_IsBufferOwner || m_Buffer->capacity() > m_Buffer->size()); }
		virtual size_t GetPosition() const override { return m_Buffer == nullptr ? 0 : m_Buffer->size(); }
		virtual size_t GetSize() const override { return m_Buffer == nullptr ? 0 : m_Buffer->size(); }

		// Write data
		virtual Result Write(const void* buffer, size_t writeSize) override;
	};


	template<size_t StaticBufferSize>
	class StaticOutputMemoryStream : public OutputMemoryStream
	{
	private:
		StaticArray<uint8_t, StaticBufferSize> m_Buffer;
	public:
		StaticOutputMemoryStream(IHeap& overflowHeap)
			: OutputMemoryStream(m_Buffer)
			, m_Buffer(overflowHeap)
		{}
	};


} // namespace SF

