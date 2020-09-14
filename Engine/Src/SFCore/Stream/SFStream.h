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
#include "Object/SFSharedObject.h"
#include "String/SFStringCrc64.h"
#include "Container/SFArray.h"

namespace SF
{
	// Seek position
	enum class SeekMode
	{
		Begin,
		Current,
		End
	};


	/////////////////////////////////////////////////////////////////////////////////////////
	//
	// base stream class
	//
	class IStream
	{
	public:

	private:

		// Name of stream
		StringCrc64 m_Name;
		// Source name of the stream such as file name
		StringCrc64 m_SourceName;

	public:

		IStream() {}
		virtual ~IStream() {}

		// Set name
		void SetName(StringCrc64 name) { m_Name = name; }
		// Get name
		StringCrc64 GetName() const { return m_Name; }

		// Set name
		void SetSourceName(StringCrc64 name) { m_Name = name; }
		// Get name
		StringCrc64 GetSourceName() const { return m_Name; }

		virtual class IInputStream* ToInputStream() { return nullptr; }
		virtual class IOutputStream* ToOutputStream() { return nullptr; }

		virtual size_t GetPosition() const = 0;
		virtual size_t GetSize() const = 0;
		void Skip(size_t skipOffset) { Seek(SeekMode::Current, skipOffset); }
		virtual size_t Seek(SeekMode seekPos, int64_t offset) { unused(seekPos); unused(offset); return 0; }
	};


	/////////////////////////////////////////////////////////////////////////////////////////
	//
	// Input stream class
	//
	class IInputStream : public IStream
	{
	public:
		virtual class IInputStream* ToInputStream() override { return this; }

		// return true if the stream is valid and have something read
		virtual bool CanRead() = 0;

		virtual size_t GetRemainSize() const { return GetSize() - GetPosition(); }

		// returns buffer pointer if it supports
		virtual uint8_t* GetBufferPtr() { assert(false); return nullptr; }
		virtual const uint8_t* GetBufferPtr() const { assert(false); return nullptr; }

		virtual Result Read(void* buffer, size_t readSize) = 0;

		template<class DataType>
		inline Result Read(DataType& data)
		{
			return Read(&data, sizeof(data));
		}

		template<class DataType>
		inline Result Read(Array<DataType>& data)
		{
			uint16_t NumItems{};
			if (!Read(NumItems))
				return ResultCode::END_OF_STREAM;

			data.reserve(NumItems);

			for (uint32_t iItem = 0; iItem < NumItems; iItem++)
			{
				DataType Item;
				auto Ret = Read(Item);
				if (!Ret)
					return Ret;

				data.push_back(Item);
			}

			return ResultCode::SUCCESS;
		}


		template< class DataType >
		Result ReadLink(DataType*& pDst, size_t readSize)
		{
			if (GetRemainSize() < readSize)
				return ResultCode::IO_BADPACKET_SIZE;// sizeCheck

			if (readSize > 0)
			{
				pDst = reinterpret_cast<DataType*>(GetBufferPtr() + GetPosition());
				Skip(readSize);
			}
			else
				pDst = nullptr;

			return ResultCode::SUCCESS;
		}

		template< class DataType >
		Result ReadLink(Array<std::decay_t<DataType>*>& data, size_t readSize)
		{
			uint16_t NumItems{};
			if (!Read(NumItems))
				return ResultCode::END_OF_STREAM;

			data.reserve(NumItems);

			for (uint32_t iItem = 0; iItem < NumItems; iItem++)
			{
				DataType* Item;
				auto Ret = ReadLink(Item);
				if (!Ret)
					return Ret;

				data.push_back(Item);

				// if variable size data. the data should be bigger than type size
				auto expectedSize = SerializedSizeOf(*Item);
				assert(expectedSize >= sizeof(DataType));
				if (expectedSize > sizeof(DataType))
				{
					Skip(expectedSize - sizeof(DataType));
				}
			}

			return ResultCode::SUCCESS;
		}

	};


	/////////////////////////////////////////////////////////////////////////////////////////
	//
	// Output stream class
	//
	class IOutputStream : public IStream
	{
	public:

		virtual class IOutputStream* ToOutputStream() override { return this; }

		// return true if the stream is valid and able to be written
		virtual bool CanWrite() = 0;

		virtual Result Write(const void* buffer, size_t writeSize) = 0;

		template<class DataType>
		inline Result Write(const DataType& data)
		{
			return Write(&data, sizeof(data));
		}
	};


	/////////////////////////////////////////////////////////////////////////////////////////
	// Null output stream. only calculate output size
	class NullOutputStream : public IOutputStream
	{
	private:

		size_t OutputSize = 0;

	public:

		NullOutputStream() = default;
		virtual ~NullOutputStream() = default;

		virtual size_t GetPosition() const override { return OutputSize; }
		virtual size_t GetSize() const override { return OutputSize; }

		virtual size_t Seek(SeekMode seekPos, int64_t offset)
		{
			switch (seekPos)
			{
			case SeekMode::Begin: OutputSize = offset; break;
			case SeekMode::Current: OutputSize += offset; break;
			case SeekMode::End: OutputSize += offset; break;
			}
		}

		// return true if the stream is valid and able to be written
		virtual bool CanWrite() override { return true; }

		virtual Result Write(const void* buffer, size_t writeSize)  override { OutputSize += writeSize; }
	};

} // namespace SF

