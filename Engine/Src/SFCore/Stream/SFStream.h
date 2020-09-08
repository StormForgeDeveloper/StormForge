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

		virtual Result Read(void* buffer, size_t readSize) = 0;

		template<class DataType>
		inline Result Read(DataType& data)
		{
			return Read(&data, sizeof(data));
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

		virtual Result Write(const void* buffer, size_t readSize) = 0;

		template<class DataType>
		inline Result Write(const DataType& data)
		{
			return Write(&data, sizeof(data));
		}
	};

} // namespace SF

