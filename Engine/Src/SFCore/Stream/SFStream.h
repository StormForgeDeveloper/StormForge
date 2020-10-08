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
#include "String/SFStringCrc32.h"
#include "String/SFStringCrc64.h"
#include "Container/SFArray.h"
#include "String/SFStrUtil.h"
#include "String/SFString.h"

namespace SF
{
	class Result;

	//enum class RankingType : uint8_t;
	//enum class NotificationType : uint16_t;
	//enum class ClusterType : uint32_t;
	//enum class ClusterMembership : uint32_t;
	//enum class ClusterID : uint32_t;
	//enum class NetClass : uint32_t;
	//union TransactionID;
	//union EntityUID;
	//union RouteContext;
	//struct PlayerInformation;
	//struct RankingPlayerInformation;
	//struct FriendInformation;
	//struct TotalRankingPlayerInformation;
	//struct MatchingQueueTicket;
	//class StringCrc32;
	//class StringCrc64;
	//struct NetAddress;
	//struct RelayPlayerInfo;

	//class VariableBox;
	//class NamedVariableBox;
	//class VariableTable;



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
		virtual uint8_t* GetBufferPtr() { assert(false); return nullptr; }
		virtual const uint8_t* GetBufferPtr() const { assert(false); return nullptr; }

		virtual Result Read(void* buffer, size_t readSize) = 0;


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
		Result Read(StringW& data);

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
		//Result Read(ClusterMembership& data);
		//Result Read(ClusterType& data);

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
				DataType Item;
				auto Ret = (*this) >> Item;
				if (!Ret)
					return Ret;

				data.push_back(Item);
			}

			return ResultCode::SUCCESS;
		}


		template< class DataType >
		Result ReadLink(DataType*& pDst, size_t readCount)
		{
			auto readSize = readCount * sizeof(DataType);
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
		Result ReadLink(ArrayView<DataType>& data)
		{
			uint16_t NumItems{};
			if (!Read(NumItems))
				return ResultCode::END_OF_STREAM;

			DataType* pData = nullptr;
			auto ret = ReadLink(pData, NumItems);
			if (!ret)
				return ret;

			data.SetLinkedBuffer(NumItems, NumItems, pData);

			int32_t SizeRemain = -static_cast<int32_t>(NumItems * sizeof(DataType));
			for (auto& itData : data)
			{
				SizeRemain += static_cast<int32_t>(SerializedSizeOf(itData));
			}

			if (SizeRemain > 0)
				Skip(SizeRemain);

			return ResultCode::SUCCESS;
		}

		template< class DataType >
		Result ReadLink(Array<std::decay_t<DataType>*>& data)
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

		Result Write(const CharPtr& data);
		Result Write(const WCharPtr& data);

		Result Write(const String& data);
		Result Write(const StringW& data);

		Result Write(const std::string& data);
		Result Write(const std::wstring& data);

		//Result Write(const DurationMS& data);
		//Result Write(const DurationSec& data);
		//Result Write(const sockaddr_in6& data);
		//Result Write(const sockaddr_storage& data);
		//Result Write(const TransactionID& data);
		//Result Write(const EntityUID& data);
		//Result Write(const RouteContext& data);
		//Result Write(const RankingType& data);
		//Result Write(const NotificationType& data);
		//Result Write(const PlayerInformation& data);
		//Result Write(const RankingPlayerInformation& data);
		//Result Write(const FriendInformation& data);
		//Result Write(const TotalRankingPlayerInformation& data);
		//Result Write(const MatchingQueueTicket& data);
		//Result Write(const ClusterMembership& data);
		//Result Write(const ClusterType& data);
		//Result Write(const Result& data);
		//Result Write(const StringCrc32& data);
		//Result Write(const StringCrc64& data);
		//Result Write(const ClusterID& data);
		//Result Write(const NetClass& data);
		//Result Write(const NetAddress& data);
		//Result Write(const RelayPlayerInfo& data);

		//Result Write(const VariableBox& data);
		//Result Write(const NamedVariableBox& data);
		//Result Write(const VariableTable& data);

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
	inline Result operator >> (IInputStream& input, void* data) { assert(false); return ResultCode::NOT_SUPPORTED; }
	inline Result operator >> (IInputStream& input, const void* data) { assert(false); return ResultCode::NOT_SUPPORTED; }


	inline Result operator >> (IInputStream& input, bool& data) { return input.Read(data); }
	inline Result operator << (IOutputStream& output, const bool& data) { return output.Write(data); }

	inline Result operator >> (IInputStream& input, char& data) { return input.Read(data); }
	inline Result operator << (IOutputStream& output, const char& data) { return output.Write(data); }

	inline Result operator >> (IInputStream& input, wchar_t& data) { return input.Read(data); }
	inline Result operator << (IOutputStream& output, const wchar_t& data) { return output.Write(data); }

	inline Result operator >> (IInputStream& input, int8_t& data) { return input.Read(data); }
	inline Result operator << (IOutputStream& output, const int8_t& data) { return output.Write(data); }

	inline Result operator >> (IInputStream& input, uint8_t& data) { return input.Read(data); }
	inline Result operator << (IOutputStream& output, const uint8_t& data) { return output.Write(data); }

	inline Result operator >> (IInputStream& input, int16_t& data) { return input.Read(data); }
	inline Result operator << (IOutputStream& output, const int16_t& data) { return output.Write(data); }

	inline Result operator >> (IInputStream& input, uint16_t& data) { return input.Read(data); }
	inline Result operator << (IOutputStream& output, const uint16_t& data) { return output.Write(data); }

	inline Result operator >> (IInputStream& input, int32_t& data) { return input.Read(data); }
	inline Result operator << (IOutputStream& output, const int32_t& data) { return output.Write(data); }

	inline Result operator >> (IInputStream& input, uint32_t& data) { return input.Read(data); }
	inline Result operator << (IOutputStream& output, const uint32_t& data) { return output.Write(data); }

	inline Result operator >> (IInputStream& input, int64_t& data) { return input.Read(data); }
	inline Result operator << (IOutputStream& output, const int64_t& data) { return output.Write(data); }

	inline Result operator >> (IInputStream& input, uint64_t& data) { return input.Read(data); }
	inline Result operator << (IOutputStream& output, const uint64_t& data) { return output.Write(data); }

	inline Result operator >> (IInputStream& input, float& data) { return input.Read(data); }
	inline Result operator << (IOutputStream& output, const float& data) { return output.Write(data); }

	inline Result operator >> (IInputStream& input, double& data) { return input.Read(data); }
	inline Result operator << (IOutputStream& output, const double& data) { return output.Write(data); }

	inline Result operator >> (IInputStream& input, CharPtr& data) { return input.Read(data); }
	inline Result operator << (IOutputStream& output, const CharPtr& data) { return output.Write(data); }

	
	inline Result operator >> (IInputStream& input, WCharPtr& data) { return input.Read(data); }
	inline Result operator << (IOutputStream& output, const WCharPtr& data) { return output.Write(data); }

	inline Result operator >> (IInputStream& input, String& data) { return input.Read(data); }
	inline Result operator << (IOutputStream& output, const String& data) { return output.Write(data); }

	inline Result operator >> (IInputStream& input, StringW& data) { return input.Read(data); }
	inline Result operator << (IOutputStream& output, const StringW& data) { return output.Write(data); }

	inline Result operator >> (IInputStream& input, Result& data) { return input.Read(&data, sizeof(data)); }
	inline Result operator << (IOutputStream& output, const Result& data) { return output.Write(&data, sizeof(data)); }

	inline Result operator >> (IInputStream& input, StringCrc32& data) { return input.Read(&data, sizeof(data)); }
	inline Result operator << (IOutputStream& output, const StringCrc32& data) { return output.Write(&data, sizeof(data)); }

	inline Result operator >> (IInputStream& input, StringCrc64& data) { return input.Read(&data, sizeof(data)); }
	inline Result operator << (IOutputStream& output, const StringCrc64& data) { return output.Write(&data, sizeof(data)); }

	inline Result operator >> (IInputStream& input, sockaddr_storage& data) { return input.Read(&data, sizeof(data)); }
	inline Result operator << (IOutputStream& output, const sockaddr_storage& data) { return output.Write(&data, sizeof(data)); }

	inline Result operator >> (IInputStream& input, sockaddr_in& data) { return input.Read(&data, sizeof(data)); }
	inline Result operator << (IOutputStream& output, const sockaddr_in& data) { return output.Write(&data, sizeof(data)); }

	inline Result operator >> (IInputStream& input, sockaddr_in6& data) { return input.Read(&data, sizeof(data)); }
	inline Result operator << (IOutputStream& output, const sockaddr_in6& data) { return output.Write(&data, sizeof(data)); }

	inline Result operator >> (IInputStream& input, DurationMS& data) { return input.Read(&data, sizeof(data)); }
	inline Result operator << (IOutputStream& output, const DurationMS& data) { return output.Write(&data, sizeof(data)); }

	inline Result operator >> (IInputStream& input, TimeStampMS& data) { return input.Read(&data, sizeof(data)); }
	inline Result operator << (IOutputStream& output, const TimeStampMS& data) { return output.Write(&data, sizeof(data)); }

	inline Result operator >> (IInputStream& input, DurationSec& data) { return input.Read(&data, sizeof(data)); }
	inline Result operator << (IOutputStream& output, const DurationSec& data) { return output.Write(&data, sizeof(data)); }

	inline Result operator >> (IInputStream& input, TimeStampSec& data) { return input.Read(&data, sizeof(data)); }
	inline Result operator << (IOutputStream& output, const TimeStampSec& data) { return output.Write(&data, sizeof(data)); }

	inline Result operator >> (IInputStream& input, UTCTimeStampMS& data) { return input.Read(&data, sizeof(data)); }
	inline Result operator << (IOutputStream& output, const UTCTimeStampMS& data) { return output.Write(&data, sizeof(data)); }

	inline Result operator >> (IInputStream& input, UTCTimeStampSec& data) { return input.Read(&data, sizeof(data)); }
	inline Result operator << (IOutputStream& output, const UTCTimeStampSec& data) { return output.Write(&data, sizeof(data)); }

	inline Result operator >> (IInputStream& input, NetAddress& data) { return input.Read(&data, sizeof(data)); }
	inline Result operator << (IOutputStream& output, const NetAddress& data) { return output.Write(&data, sizeof(data)); }

#if SF_PLATFORM == SF_PLATFORM_WINDOWS
	inline Result operator >> (IInputStream& input, long& data) { return input.Read(&data, sizeof(data)); }
	inline Result operator << (IOutputStream& output, const long& data) { return output.Write(&data, sizeof(data)); }

	inline Result operator >> (IInputStream& input, unsigned long& data) { return input.Read(&data, sizeof(data)); }
	inline Result operator << (IOutputStream& output, const unsigned long& data) { return output.Write(&data, sizeof(data)); }
#endif

	//inline Result operator >> (IInputStream& input, long long& data) { return input.Read(&data, sizeof(data)); }
	//inline Result operator << (IOutputStream& output, const long long& data) { return output.Write(&data, sizeof(data)); }

	//inline Result operator >> (IInputStream& input, unsigned long long& data) { return input.Read(&data, sizeof(data)); }
	//inline Result operator << (IOutputStream& output, const unsigned long long& data) { return output.Write(&data, sizeof(data)); }

	inline Result operator >> (IInputStream& input, std::string& data) { return input.Read(data); }
	inline Result operator << (IOutputStream& output, const std::string& data) { return output.Write(data); }

	inline Result operator >> (IInputStream& input, std::wstring& data) { return input.Read(data); }
	inline Result operator << (IOutputStream& output, const std::wstring& data) { return output.Write(data); }

	inline Result operator >> (IInputStream& input, NetClass& data) { return input.Read(&data, sizeof(data)); }
	inline Result operator << (IOutputStream& output, const NetClass& data) { return output.Write(&data, sizeof(data)); }


	template<typename DataType>
	inline Result operator >> (IInputStream& input, Array<DataType>& data) { return input.Read(data); }

	template<typename DataType>
	inline Result operator << (IOutputStream& output, const Array<DataType>& data) { return output.Write(data); }

} // namespace SF

