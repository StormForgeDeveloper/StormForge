////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Log service
//
////////////////////////////////////////////////////////////////////////////////


#pragma once 

#include "SFTypedefs.h"
#include "Util/SFStringCrc32.h"
#include "Util/SFStrUtil.h"

namespace SF {

	//////////////////////////////////////////////////////////////////////////
	// sub channel
	enum class LogOutputType : uint32_t
	{
		// Generic trace
		Error,
		Warning,
		Factal,
		Info,

		// Module additional traces
		Custom1,
		Custom2,
		Custom3,
		Custom4,
		Custom5,
		Custom6,
		Custom7,
		Custom8,
		Custom9,
		Custom10,

		Debug,
		Debug1,
		Debug2,
		Debug3,
		Debug4,
		Debug5,
		Debug6,
		Debug7,
		Debug8,

		Max,
	};


	union LogOutputMask
	{
		struct
		{
			// Generic trace
			uint32_t Factal : 1;
			uint32_t Error : 1;
			uint32_t Warning : 1;
			uint32_t Info : 1;

			// Module additional traces
			uint32_t Custom1 : 1;
			uint32_t Custom2 : 1;
			uint32_t Custom3 : 1;
			uint32_t Custom4 : 1;
			uint32_t Custom5 : 1;
			uint32_t Custom6 : 1;
			uint32_t Custom7 : 1;
			uint32_t Custom8 : 1;
			uint32_t Custom9 : 1;
			uint32_t Custom10 : 1;

			uint32_t Debug : 1;
			uint32_t Debug1 : 1;
			uint32_t Debug2 : 1;
			uint32_t Debug3 : 1;
			uint32_t Debug4 : 1;
			uint32_t Debug5 : 1;
			uint32_t Debug6 : 1;
			uint32_t Debug7 : 1;
			uint32_t Debug8 : 1;

			uint32_t : 0;
		};
		uint32_t Composited = std::numeric_limits<uint32_t>::max();

		LogOutputMask() = default;
		LogOutputMask(uint32_t composited) :Composited(composited) {}

		LogOutputMask operator &(const LogOutputMask& op2) const
		{
			return LogOutputMask(Composited & op2.Composited);
		}

		LogOutputMask operator |(const LogOutputMask& op2) const
		{
			return LogOutputMask(Composited | op2.Composited);
		}
	};

	//////////////////////////////////////////////////////////////////////////////////////////
	//
	//	class LogService
	//
	namespace Log
	{
		class LogOutputHandler;


		struct LogChannel
		{
			char ChannelName[128]{};
			LogOutputMask ChannelMask{};

			LogChannel(const char* channelName, LogOutputType defaultLogLevel)
			{
				StrUtil::StringCopy(ChannelName, channelName);
				ChannelMask.Composited = static_cast<uint32_t>((1 << (static_cast<uint32_t>(defaultLogLevel) + 1)) - 1);
			}
			LogChannel(const char* channelName, uint32_t channelMask)
			{
				StrUtil::StringCopy(ChannelName, channelName);
				ChannelMask.Composited = channelMask;
			}

			LogChannel& operator = (const LogChannel& src)
			{
				ChannelMask = src.ChannelMask;
				return *this;
			}

			void EnableChannel(LogOutputType subChannel, bool enable)
			{
				auto channelMask = 1 << static_cast<uint32_t>(subChannel);
				if (enable)
					ChannelMask.Composited |= channelMask;
				else
					ChannelMask.Composited &= (~channelMask);
			}
		};



		constexpr LogOutputType Error = LogOutputType::Error;
		constexpr LogOutputType Warning = LogOutputType::Warning;
		constexpr LogOutputType Factal = LogOutputType::Factal;
		constexpr LogOutputType Info = LogOutputType::Info;

		// Module additional traces
		constexpr LogOutputType Custom1 = LogOutputType::Custom1;
		constexpr LogOutputType Custom2 = LogOutputType::Custom2;
		constexpr LogOutputType Custom3 = LogOutputType::Custom3;
		constexpr LogOutputType Custom4 = LogOutputType::Custom4;
		constexpr LogOutputType Custom5 = LogOutputType::Custom5;
		constexpr LogOutputType Custom6 = LogOutputType::Custom6;
		constexpr LogOutputType Custom7 = LogOutputType::Custom7;
		constexpr LogOutputType Custom8 = LogOutputType::Custom8;
		constexpr LogOutputType Custom9 = LogOutputType::Custom9;
		constexpr LogOutputType Custom10 = LogOutputType::Custom10;

		constexpr LogOutputType Debug = LogOutputType::Debug;
		constexpr LogOutputType Debug1 = LogOutputType::Debug1;
		constexpr LogOutputType Debug2 = LogOutputType::Debug2;
		constexpr LogOutputType Debug3 = LogOutputType::Debug3;
		constexpr LogOutputType Debug4 = LogOutputType::Debug4;
		constexpr LogOutputType Debug5 = LogOutputType::Debug5;
		constexpr LogOutputType Debug6 = LogOutputType::Debug6;
		constexpr LogOutputType Debug7 = LogOutputType::Debug7;
		constexpr LogOutputType Debug8 = LogOutputType::Debug8;

		// Predefined Log channels
		extern LogChannel System;
		extern LogChannel Net;
		extern LogChannel IO;
		extern LogChannel ThirdParty;
		extern LogChannel Engine;
		extern LogChannel Protocol;
		extern LogChannel Editor;
		extern LogChannel Game;
	}


	class LogService
	{
	protected:

		LogOutputMask m_GlobalOutputMask;

	public:

		LogService(const LogOutputMask& logMask = LogOutputMask())
		{
			m_GlobalOutputMask = logMask;
		}
		virtual ~LogService() {}

		// Check input mask
		bool ShouldPrint(const LogOutputMask& mainChannelMask, const LogOutputMask& channelMask)
		{
			auto filterMask = mainChannelMask.Composited & m_GlobalOutputMask.Composited;
			return filterMask & channelMask.Composited;
		}

		LogOutputMask ToChannelMask(const Log::LogChannel& mainChannel)
		{
			return mainChannel.ChannelMask;
		}

		static LogOutputMask ToChannelMask(LogOutputType subChannel)
		{
			LogOutputMask channelMask;
			channelMask.Composited = (((uint32_t)1) << (int)subChannel);
			return channelMask;
		}

		void SetGlobalOutputMask(const LogOutputMask& outputMask) { m_GlobalOutputMask = outputMask; }

		// output handler
		virtual void RegisterOutputHandler(Log::LogOutputHandler* output) {}
		virtual void UnregisterOutputHandler(Log::LogOutputHandler* output) {}

		// Reserve write buffer
		virtual void* ReserveWriteBuffer() { return nullptr; }
		virtual void ReleaseWriteBuffer(void* block, size_t messageSize) {}
		virtual size_t WriteTimeTag(void* pLogItem) { unused(pLogItem); return 0; }

		// Flush log queue
		virtual void Flush() {}
	};

} // namespace SF

