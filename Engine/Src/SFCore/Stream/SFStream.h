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
#include "Util/SFStringCrc32.h"
#include "Util/SFStringCrc64.h"
#include "Container/SFArray.h"
#include "Util/SFStrUtil.h"
#include "Util/SFString.h"

namespace SF
{
	class Result;



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
		virtual size_t size() const { return GetSize(); }
		Result Skip(size_t skipOffset) { return Seek(SeekMode::Current, skipOffset); }
		virtual Result Seek(SeekMode seekPos, int64_t offset) { unused(seekPos); unused(offset); return 0; }
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
		//virtual uint8_t* GetBufferPtr() { assert(false); return nullptr; }
		virtual const uint8_t* GetBufferPtr() const { assert(false); return nullptr; }

		virtual Result Read(void* buffer, size_t readSize) = 0;
		virtual Result Read(void* buffer, size_t readSize, size_t& outReadSize) { return ResultCode::NOT_IMPLEMENTED; }
		virtual Result ReadAppend(Array<char>& readBuffer);


		inline Result Read(bool& data) { return Read(&data, sizeof(data)); }
		inline Result Read(char& data) { return Read(&data, sizeof(data)); }
		inline Result Read(wchar_t& data) { return Read(&data, sizeof(data)); }
		inline Result Read(int8_t& data) { return Read(&data, sizeof(data)); }
		inline Result Read(uint8_t& data) { return Read(&data, sizeof(data)); }
		inline Result Read(int16_t& data) { return Read(&data, sizeof(data)); }
		inline Result Read(uint16_t& data) { return Read(&data, sizeof(data)); }
		inline Result Read(int32_t& data) { return Read(&data, sizeof(data)); }
		inline Result Read(uint32_t& data) { return Read(&data, sizeof(data)); }
		inline Result Read(int64_t& data) { return Read(&data, sizeof(data)); }
		inline Result Read(uint64_t& data) { return Read(&data, sizeof(data)); }
		inline Result Read(float& data) { return Read(&data, sizeof(data)); }
		inline Result Read(double& data) { return Read(&data, sizeof(data)); }

		Result Read(String& data);
		Result Read(WString& data);

		Result Read(std::string& data);
		Result Read(std::wstring& data);

		Result Read(char*& data);
		Result Read(wchar_t*& data);
		//Result Read(Result& data);
		//Result Read(StringCrc32& data);
		//Result Read(StringCrc64& data);
		//Result Read(RelayPlayerInfo& data);
		//Result Read(NetAddress& data);
		//Result Read(NetClass& data);
		//Result Read(ClusterID& data);
		//Result Read(DurationMS& data);
		//Result Read(DurationSec& data);
		//Result Read(sockaddr_in6& data);
		//Result Read(sockaddr_storage& data);
		//Result Read(TransactionID& data);
		//Result Read(EntityUID& data);
		//Result Read(RouteContext& data);
		//Result Read(RankingType& data);
		//Result Read(NotificationType& data);
		//Result Read(PlayerInformation& data);
		//Result Read(RankingPlayerInformation& data);
		//Result Read(FriendInformation& data);
		//Result Read(TotalRankingPlayerInformation& data);
		//Result Read(MatchingQueueTicket& data);

		//Result Read(VariableBox& data);
		//Result Read(NamedVariableBox& data);
		//Result Read(VariableTable& data);



		template<class DataType>
		inline Result Read(Array<DataType>& data)
		{
			uint16_t NumItems{};
			if (!Read(NumItems))
				return ResultCode::END_OF_STREAM;

			data.reserve(NumItems);

			for (uint32_t iItem = 0; iItem < NumItems; iItem++)
			{
				DataType Item{};
				auto Ret = (*this) >> Item;
				if (!Ret)
					return Ret;

				data.push_back(Item);
			}

			return ResultCode::SUCCESS;
		}

		Result ReadLink(const char*& pDst)
		{
			uint16_t readCount{};
			if (!Read(readCount))
				return ResultCode::END_OF_STREAM;

			auto readSize = readCount * sizeof(char);
			if (GetRemainSize() < readSize)
				return ResultCode::IO_BADPACKET_SIZE;// sizeCheck

			if (readSize > 0)
			{
				pDst = reinterpret_cast<const char*>(GetBufferPtr() + GetPosition());
				Skip(readSize);
			}
			else
				pDst = nullptr;

			return ResultCode::SUCCESS;
		}

		template< class DataType >
		Result ReadLink(DataType*& pDst, size_t readCount)
		{
            size_t readSize{};
            if constexpr (std::is_scalar_v<DataType>)
            {
                readSize = readCount * sizeof(DataType);
                if (GetRemainSize() < readSize)
                	return ResultCode::IO_BADPACKET_SIZE;// sizeCheck

                if (readSize > 0)
                {
                    pDst = (DataType*)(GetBufferPtr() + GetPosition());
                    if (!Skip(readSize))
                        return ResultCode::IO_BADPACKET_SIZE;// sizeCheck
                }
                else
                    pDst = nullptr;
            }
            else
            {
                pDst = (DataType*)(GetBufferPtr() + GetPosition());
                for (uint iData = 0; iData < readCount; iData++)
                {
                    readSize = SerializedSizeOf(*pDst);
                    if (!Skip(readSize))
                        return ResultCode::IO_BADPACKET_SIZE;// sizeCheck
                }
            }

			return ResultCode::SUCCESS;
		}

		template< class DataType>
		Result ReadArrayLink(ArrayView<DataType>& data)
		{
			uint16_t NumItems{};
			if (!Read(NumItems))
				return ResultCode::END_OF_STREAM;

			DataType* pData = nullptr;
			auto ret = ReadLink(pData, NumItems);
			if (!ret)
				return ret;

			data.SetLinkedBuffer(NumItems, NumItems, pData);

			return ResultCode::SUCCESS;
		}

		template< class DataType >
		Result ReadArrayLink(DynamicArray<DataType>& data)
		{
			uint16_t NumItems{};
			if (!Read(NumItems))
				return ResultCode::END_OF_STREAM;

			data.reserve(NumItems);

			for (uint32_t iItem = 0; iItem < NumItems; iItem++)
			{
				DataType Item;
				auto Ret = ReadLink(Item);
				if (!Ret)
					return Ret;

				data.push_back(Item);
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


		inline Result Write(const bool& data) { return Write(&data, sizeof(data)); }
		inline Result Write(const char& data) { return Write(&data, sizeof(data)); }
		inline Result Write(const wchar_t& data) { return Write(&data, sizeof(data)); }
		inline Result Write(const int8_t& data) { return Write(&data, sizeof(data)); }
		inline Result Write(const uint8_t& data) { return Write(&data, sizeof(data)); }
		inline Result Write(const int16_t& data) { return Write(&data, sizeof(data)); }
		inline Result Write(const uint16_t& data) { return Write(&data, sizeof(data)); }
		inline Result Write(const int32_t& data) { return Write(&data, sizeof(data)); }
		inline Result Write(const uint32_t& data) { return Write(&data, sizeof(data)); }
		inline Result Write(const int64_t& data) { return Write(&data, sizeof(data)); }
		inline Result Write(const uint64_t& data) { return Write(&data, sizeof(data)); }
		inline Result Write(const float& data) { return Write(&data, sizeof(data)); }
		inline Result Write(const double& data) { return Write(&data, sizeof(data)); }

		Result Write(const char* data);
		Result Write(const wchar_t* data);

		Result Write(const String& data);
		Result Write(const WString& data);

		Result Write(const std::string& data);
		Result Write(const std::wstring& data);


		template<class DataType>
		inline Result Write(const Array<DataType>& data)
		{
			uint16_t NumItems = static_cast<uint16_t>(data.size());
			if (!Write(NumItems))
				return ResultCode::END_OF_STREAM;

			for (uint32_t iItem = 0; iItem < NumItems; iItem++)
			{
				auto Ret = (*this) << data[iItem];
				if (!Ret)
					return Ret;
			}

			return ResultCode::SUCCESS;
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

		virtual Result Seek(SeekMode seekPos, int64_t offset) override
		{
			switch (seekPos)
			{
			case SeekMode::Begin: OutputSize = offset; break;
			case SeekMode::Current: OutputSize += offset; break;
			case SeekMode::End: OutputSize += offset; break;
			default:
				return ResultCode::INVALID_ARG;
			}

			return ResultCode::SUCCESS;
		}

		// return true if the stream is valid and able to be written
		virtual bool CanWrite() override { return true; }

		virtual Result Write(const void* buffer, size_t writeSize)  override { OutputSize += writeSize; return ResultCode::SUCCESS; }
	};




	/////////////////////////////////////////////////////////////////////////////////////////
	// Serialization operators

	inline Result operator >> (IInputStream& input, const char* data) { assert(false); return ResultCode::NOT_SUPPORTED; }
	inline Result operator >> (IInputStream& input, const wchar_t* data) { assert(false); return ResultCode::NOT_SUPPORTED; }

	inline size_t SerializedSizeOf(const void*& data) { return 0; }

	inline Result operator << (IOutputStream& input, void* data) { assert(false); return ResultCode::NOT_SUPPORTED; }
	inline Result operator << (IOutputStream& input, const void* data) { assert(false); return ResultCode::NOT_SUPPORTED; }
	inline Result operator >> (IInputStream& input, void* data) { assert(false); return ResultCode::NOT_SUPPORTED; }
	inline Result operator >> (IInputStream& input, const void* data) { assert(false); return ResultCode::NOT_SUPPORTED; }

	inline size_t SerializedSizeOf(const bool& Value) { return sizeof(Value); }
	inline Result operator >> (IInputStream& input, bool& data) { return input.Read(data); }
	inline Result operator << (IOutputStream& output, const bool& data) { return output.Write(data); }

	inline size_t SerializedSizeOf(const char& Value) { return sizeof(Value); }
	inline Result operator >> (IInputStream& input, char& data) { return input.Read(data); }
	inline Result operator << (IOutputStream& output, const char& data) { return output.Write(data); }

	inline size_t SerializedSizeOf(const wchar_t& Value) { return sizeof(Value); }
	inline Result operator >> (IInputStream& input, wchar_t& data) { return input.Read(data); }
	inline Result operator << (IOutputStream& output, const wchar_t& data) { return output.Write(data); }

	inline size_t SerializedSizeOf(const int8_t& Value) { return sizeof(Value); }
	inline Result operator >> (IInputStream& input, int8_t& data) { return input.Read(data); }
	inline Result operator << (IOutputStream& output, const int8_t& data) { return output.Write(data); }

	inline size_t SerializedSizeOf(const uint8_t& Value) { return sizeof(Value); }
	inline Result operator >> (IInputStream& input, uint8_t& data) { return input.Read(data); }
	inline Result operator << (IOutputStream& output, const uint8_t& data) { return output.Write(data); }

	inline size_t SerializedSizeOf(const int16_t& Value) { return sizeof(Value); }
	inline Result operator >> (IInputStream& input, int16_t& data) { return input.Read(data); }
	inline Result operator << (IOutputStream& output, const int16_t& data) { return output.Write(data); }

	inline size_t SerializedSizeOf(const uint16_t& Value) { return sizeof(Value); }
	inline Result operator >> (IInputStream& input, uint16_t& data) { return input.Read(data); }
	inline Result operator << (IOutputStream& output, const uint16_t& data) { return output.Write(data); }

	inline size_t SerializedSizeOf(const int32_t& Value) { return sizeof(Value); }
	inline Result operator >> (IInputStream& input, int32_t& data) { return input.Read(data); }
	inline Result operator << (IOutputStream& output, const int32_t& data) { return output.Write(data); }

	inline size_t SerializedSizeOf(const uint32_t& Value) { return sizeof(Value); }
	inline Result operator >> (IInputStream& input, uint32_t& data) { return input.Read(data); }
	inline Result operator << (IOutputStream& output, const uint32_t& data) { return output.Write(data); }

	inline size_t SerializedSizeOf(const int64_t& Value) { return sizeof(Value); }
	inline Result operator >> (IInputStream& input, int64_t& data) { return input.Read(data); }
	inline Result operator << (IOutputStream& output, const int64_t& data) { return output.Write(data); }

	inline size_t SerializedSizeOf(const uint64_t& Value) { return sizeof(Value); }
	inline Result operator >> (IInputStream& input, uint64_t& data) { return input.Read(data); }
	inline Result operator << (IOutputStream& output, const uint64_t& data) { return output.Write(data); }

	inline size_t SerializedSizeOf(const float& Value) { return sizeof(Value); }
	inline Result operator >> (IInputStream& input, float& data) { return input.Read(data); }
	inline Result operator << (IOutputStream& output, const float& data) { return output.Write(data); }

	inline size_t SerializedSizeOf(const double& Value) { return sizeof(Value); }
	inline Result operator >> (IInputStream& input, double& data) { return input.Read(data); }
	inline Result operator << (IOutputStream& output, const double& data) { return output.Write(data); }

	inline size_t SerializedSizeOf(const char* Value) { return sizeof(uint16_t) + (StrUtil::StringLen(Value) + 1) * sizeof(char); }
	inline Result operator >> (IInputStream& input, char*& data) { return input.Read(data); }
	inline Result operator << (IOutputStream& output, const char* data) { return output.Write(data); }

	inline size_t SerializedSizeOf(const wchar_t* Value) { return sizeof(uint16_t) + (StrUtil::StringLen(Value) + 1) * sizeof(wchar_t); }
	inline Result operator >> (IInputStream& input, wchar_t*& data) { return input.Read(data); }
	inline Result operator << (IOutputStream& output, const wchar_t* data) { return output.Write(data); }

	inline size_t SerializedSizeOf(const String& Value) { return sizeof(uint16_t) + (Value.length() + 1) * sizeof(char); }
	inline Result operator >> (IInputStream& input, String& data) { return input.Read(data); }
	inline Result operator << (IOutputStream& output, const String& data) { return output.Write(data); }

	inline size_t SerializedSizeOf(const WString& Value) { return sizeof(uint16_t) + (Value.length() + 1) * sizeof(wchar_t); }
	inline Result operator >> (IInputStream& input, WString& data) { return input.Read(data); }
	inline Result operator << (IOutputStream& output, const WString& data) { return output.Write(data); }

	inline size_t SerializedSizeOf(const Result& Value) { return sizeof(Value); }
	inline Result operator >> (IInputStream& input, Result& data) { return input.Read(&data, sizeof(data)); }
	inline Result operator << (IOutputStream& output, const Result& data) { return output.Write(&data, sizeof(data)); }

	inline size_t SerializedSizeOf(const StringCrc32& Value) { return sizeof(Value); }
	inline Result operator >> (IInputStream& input, StringCrc32& data) { return input.Read(&data, sizeof(data)); }
	inline Result operator << (IOutputStream& output, const StringCrc32& data) { return output.Write(&data, sizeof(data)); }

	inline size_t SerializedSizeOf(const StringCrc64& Value) { return sizeof(Value); }
	inline Result operator >> (IInputStream& input, StringCrc64& data) { return input.Read(&data, sizeof(data)); }
	inline Result operator << (IOutputStream& output, const StringCrc64& data) { return output.Write(&data, sizeof(data)); }

	inline size_t SerializedSizeOf(const sockaddr_storage& Value) { return sizeof(Value); }
	inline Result operator >> (IInputStream& input, sockaddr_storage& data) { return input.Read(&data, sizeof(data)); }
	inline Result operator << (IOutputStream& output, const sockaddr_storage& data) { return output.Write(&data, sizeof(data)); }

	inline size_t SerializedSizeOf(const sockaddr_in& Value) { return sizeof(Value); }
	inline Result operator >> (IInputStream& input, sockaddr_in& data) { return input.Read(&data, sizeof(data)); }
	inline Result operator << (IOutputStream& output, const sockaddr_in& data) { return output.Write(&data, sizeof(data)); }

	inline size_t SerializedSizeOf(const sockaddr_in6& Value) { return sizeof(Value); }
	inline Result operator >> (IInputStream& input, sockaddr_in6& data) { return input.Read(&data, sizeof(data)); }
	inline Result operator << (IOutputStream& output, const sockaddr_in6& data) { return output.Write(&data, sizeof(data)); }

	inline size_t SerializedSizeOf(const DurationMS& Value) { return sizeof(Value); }
	inline Result operator >> (IInputStream& input, DurationMS& data) { return input.Read(&data, sizeof(data)); }
	inline Result operator << (IOutputStream& output, const DurationMS& data) { return output.Write(&data, sizeof(data)); }

	inline size_t SerializedSizeOf(const TimeStampMS& Value) { return sizeof(Value); }
	inline Result operator >> (IInputStream& input, TimeStampMS& data) { return input.Read(&data, sizeof(data)); }
	inline Result operator << (IOutputStream& output, const TimeStampMS& data) { return output.Write(&data, sizeof(data)); }

	inline size_t SerializedSizeOf(const DurationSec& Value) { return sizeof(Value); }
	inline Result operator >> (IInputStream& input, DurationSec& data) { return input.Read(&data, sizeof(data)); }
	inline Result operator << (IOutputStream& output, const DurationSec& data) { return output.Write(&data, sizeof(data)); }

	inline size_t SerializedSizeOf(const TimeStampSec& Value) { return sizeof(Value); }
	inline Result operator >> (IInputStream& input, TimeStampSec& data) { return input.Read(&data, sizeof(data)); }
	inline Result operator << (IOutputStream& output, const TimeStampSec& data) { return output.Write(&data, sizeof(data)); }

	inline size_t SerializedSizeOf(const UTCTimeStampMS& Value) { return sizeof(Value); }
	inline Result operator >> (IInputStream& input, UTCTimeStampMS& data) { return input.Read(&data, sizeof(data)); }
	inline Result operator << (IOutputStream& output, const UTCTimeStampMS& data) { return output.Write(&data, sizeof(data)); }

	inline size_t SerializedSizeOf(const UTCTimeStampSec& Value) { return sizeof(Value); }
	inline Result operator >> (IInputStream& input, UTCTimeStampSec& data) { return input.Read(&data, sizeof(data)); }
	inline Result operator << (IOutputStream& output, const UTCTimeStampSec& data) { return output.Write(&data, sizeof(data)); }

	inline size_t SerializedSizeOf(const NetAddress& Value) { return sizeof(Value); }
	inline Result operator >> (IInputStream& input, NetAddress& data) { return input.Read(&data, sizeof(data)); }
	inline Result operator << (IOutputStream& output, const NetAddress& data) { return output.Write(&data, sizeof(data)); }

#if SF_PLATFORM == SF_PLATFORM_WINDOWS
	inline size_t SerializedSizeOf(const long& Value) { return sizeof(Value); }
	inline Result operator >> (IInputStream& input, long& data) { return input.Read(&data, sizeof(data)); }
	inline Result operator << (IOutputStream& output, const long& data) { return output.Write(&data, sizeof(data)); }

	inline size_t SerializedSizeOf(const unsigned long& Value) { return sizeof(Value); }
	inline Result operator >> (IInputStream& input, unsigned long& data) { return input.Read(&data, sizeof(data)); }
	inline Result operator << (IOutputStream& output, const unsigned long& data) { return output.Write(&data, sizeof(data)); }
#endif

	//inline Result operator >> (IInputStream& input, long long& data) { return input.Read(&data, sizeof(data)); }
	//inline Result operator << (IOutputStream& output, const long long& data) { return output.Write(&data, sizeof(data)); }

	//inline Result operator >> (IInputStream& input, unsigned long long& data) { return input.Read(&data, sizeof(data)); }
	//inline Result operator << (IOutputStream& output, const unsigned long long& data) { return output.Write(&data, sizeof(data)); }

	inline size_t SerializedSizeOf(const std::string& Value) { return sizeof(uint16_t) + (Value.length() + 1) * sizeof(char); }
	inline Result operator >> (IInputStream& input, std::string& data) { return input.Read(data); }
	inline Result operator << (IOutputStream& output, const std::string& data) { return output.Write(data); }

	inline size_t SerializedSizeOf(const std::wstring& Value) { return sizeof(uint16_t) + (Value.length() + 1) * sizeof(wchar_t); }
	inline Result operator >> (IInputStream& input, std::wstring& data) { return input.Read(data); }
	inline Result operator << (IOutputStream& output, const std::wstring& data) { return output.Write(data); }

	inline size_t SerializedSizeOf(const NetClass& Value) { return sizeof(Value); }
	inline Result operator >> (IInputStream& input, NetClass& data) { return input.Read(&data, sizeof(data)); }
	inline Result operator << (IOutputStream& output, const NetClass& data) { return output.Write(&data, sizeof(data)); }


	template<typename DataType>
	inline Result operator >> (IInputStream& input, Array<DataType>& data) { return input.Read(data); }

	template<typename DataType>
	inline Result operator << (IOutputStream& output, const Array<DataType>& data) { return output.Write(data); }

} // namespace SF

