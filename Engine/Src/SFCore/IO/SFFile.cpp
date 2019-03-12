////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2016 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : File
//
////////////////////////////////////////////////////////////////////////////////


#include "SFCorePCH.h"
#include "SFTypedefs.h"
#include "IO/SFFile.h"
#include "ResultCode/SFResultCodeSystem.h"



namespace SF {


	constexpr int File::BUFFERING_COUNT;
	constexpr int File::BUFFERING_SIZE;

	File::File()
		: m_FileHandle(INVALID_NATIVE_HANDLE_VALUE)
	{
		memset(m_IOBuffers, 0, sizeof(m_IOBuffers));
		if (IsAIOEnabled())
		{
			auto& memoryManager = GetSystemHeap();
			for (auto& ioBuffer : m_IOBuffers)
			{
				ioBuffer = new(memoryManager) IO_BUFFER(memoryManager, m_FileHandle, m_OpenMode);
			}
		}
	}

	File::~File()
	{
		Close();

		for (auto& ioBuffer : m_IOBuffers)
		{
			IHeap::Delete(ioBuffer);
		}

	}

	bool File::IsOpened()
	{
		return m_FileHandle != INVALID_NATIVE_HANDLE_VALUE;
	}


	// flush pending write
	void File::Flush()
	{
		if (!IsOpened())
			return;

		if (m_OpenMode == OpenMode::Read)
		{
			// TODO:
		}
		else
		{
			auto pIOBuffer = m_IOBuffers[m_BufferIndex];
			auto& stream = pIOBuffer->OutputStream;
			size_t write;
			if (stream.GetSize() > 0)
			{
				WriteRaw(pIOBuffer->Buffer.data(), stream.GetSize(), pIOBuffer, write);
			}
		}

		for (auto& ioBuffer : m_IOBuffers)
		{
			ioBuffer->WaitAIO();
			ioBuffer->InputStream.Reset();
			ioBuffer->OutputStream.Reset();
		}
	}

	size_t File::GetPosition() const
	{
		// current remain size
		auto pIOBuffer = m_IOBuffers[m_BufferIndex];
		auto& stream = pIOBuffer->InputStream;

		// We need stream is updated to access
		//pIOBuffer->WaitAIO();
		auto remainSize = pIOBuffer->Buffer.capacity() - stream.GetPosition();

		// add next buffer size
		auto nextBufferIndex = (m_BufferIndex + 1) % BUFFERING_COUNT;
		auto pNextIOBuffer = m_IOBuffers[nextBufferIndex];
		//auto& nextStream = pIOBuffer->InputStream;
		if (stream.GetPosition() > 0) // if something is read then next buffer is on the way
			remainSize += pNextIOBuffer->Buffer.capacity();

		return GetLocationRaw() - remainSize;
	}

	Result File::Read(uint8_t* buffer, size_t bufferLen, size_t &read)
	{
		size_t readRaw = 0;
		read = 0;

		if (!IsOpened())
			return ResultCode::NOT_OPENED;

		if (bufferLen == 0)
			return ResultCode::SUCCESS;

		if (true)
		{
			while (bufferLen > 0)
			{
				// pick current buffer
				auto pIOBuffer = m_IOBuffers[m_BufferIndex];
				auto& stream = pIOBuffer->InputStream;

				// If reading is going on, we need to wait
				pIOBuffer->WaitAIO();

				if (pIOBuffer->OperationSize == 0)
					return ResultCode::END_OF_FILE;

				auto remainSize = stream.GetSize() - stream.GetPosition();
				if (remainSize == 0)
				{
					stream.Reset();

					// Move to next buffer
					m_BufferIndex = (m_BufferIndex + 1) % BUFFERING_COUNT;
				}
				else
				{
					// If new block start being accessed, start loading next block
					if (stream.GetPosition() == 0)
					{
						auto nextBlock = (m_BufferIndex + 1) % BUFFERING_COUNT;
						auto pNextIOBuffer = m_IOBuffers[nextBlock];
						ReadRaw(pNextIOBuffer->Buffer.data(), pNextIOBuffer->Buffer.capacity(), pNextIOBuffer, readRaw);
					}

					auto opSize = std::min(remainSize, bufferLen);
					stream.Read(buffer, opSize);

					buffer += opSize;
					bufferLen -= opSize;
					read += opSize;
				}
			}

		}
		else
		{
			ReadRaw(buffer, bufferLen, nullptr, read);
		}


		return ResultCode::SUCCESS;
	}

	Result File::Write(const uint8_t* buffer, size_t bufferLen, size_t &write)
	{
		Result result;
		if (!IsOpened())
			return ResultCode::NOT_OPENED;

		//if (true)
		{
			while (bufferLen > 0)
			{
				// pick current buffer
				auto pIOBuffer = m_IOBuffers[m_BufferIndex];
				auto& stream = pIOBuffer->OutputStream;
				
				auto remainSize = stream.capacity() - stream.GetPosition();
				if (remainSize == 0) // the buffer filled and requested to be written. Wait operation and reset
				{
					pIOBuffer->WaitAIO();
					stream.Reset();
				}

				auto operationSize = std::min(remainSize, bufferLen);

				result = stream.Write(buffer, operationSize);
				if (!result)
					return result;

				bufferLen -= operationSize;
				remainSize -= operationSize;
				buffer += operationSize;

				if (remainSize == 0)
				{
					result = WriteRaw(pIOBuffer->Buffer.data(), pIOBuffer->Buffer.size(), pIOBuffer, write);
					if (!result)
						return result;

					m_BufferIndex = (m_BufferIndex + 1) % BUFFERING_COUNT;
				}
			}
		}
		//else
		//{
		//	WriteRaw(buffer, bufferLen, nullptr, write);
		//}


		return ResultCode::SUCCESS;
	}


}
