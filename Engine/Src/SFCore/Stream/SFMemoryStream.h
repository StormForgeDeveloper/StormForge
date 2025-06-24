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

		ArrayView<const uint8_t> m_BufferView;

		size_t m_Position = 0;


	public:

		InputMemoryStream();
		InputMemoryStream(const Array<uint8_t>& memoryBuffer);
		InputMemoryStream(const Array<const uint8_t>& memoryBuffer);
		virtual ~InputMemoryStream() {}

		// Reset position to begin
		void Reset();

		// reset buffer contents
		void ResetBuffer() { m_Position = 0; m_BufferView.Reset(); }
		void ResetBuffer(const Array<const uint8_t>& memoryBuffer)
		{
			m_Position = 0;
			m_BufferView.SetLinkedBuffer(memoryBuffer);
		}

		size_t GetBufferSize() const { return m_BufferView.GetAllocatedSize(); }

		// return true if the stream is valid and have something read
		virtual bool CanRead() override { return m_Position < m_BufferView.size(); }

		//virtual uint8_t* GetBufferPtr() override { return const_cast<uint8_t*>(m_BufferView.data()); }
		virtual const uint8_t* GetBufferPtr() const override { return m_BufferView.data(); }

		virtual Result Seek(SeekMode seekPos, int64_t offset) override;

		virtual size_t GetPosition() const override { return m_Position; }

		virtual size_t GetSize() const override { return m_BufferView.size(); }

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
		OutputMemoryStream(Array<uint8_t>& memorySource, bool bAllowResize = false);
		virtual ~OutputMemoryStream();

		// Reset position to begin
		void Reset();

		bool IsBufferResizeAllowed() const { return m_IsBufferResizeAllowed; }
		void EnableBufferResize(bool bEnable) { m_IsBufferResizeAllowed = bEnable; }

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


    class InputMemoryStreamView
    {
        struct membuf : std::streambuf
        {
            membuf(uint8_t const* base, size_t size)
            {
                char* p(const_cast<char*>(reinterpret_cast<const char*>(base)));
                this->setg(p, p, p + size);
            }
        };

        membuf m_memoryBuff;
        std::istream m_stream;

    public:
        InputMemoryStreamView(uint8_t const* base, size_t size)
            : m_memoryBuff(base, size)
            , m_stream(&m_memoryBuff)
        {
        }

        InputMemoryStreamView(const Array<const uint8_t>& content)
            : m_memoryBuff(content.data(), content.size())
            , m_stream(&m_memoryBuff)
        {
        }

        operator std::istream&()
        {
            return m_stream;
        }
    };




    

} // namespace SF

