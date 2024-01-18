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
        Log = Info,

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
        CustomMax = Custom10,

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

	const char* ToString(LogOutputType logOutputType);

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

        bool operator ==(const LogOutputMask& op2) const
        {
            return Composited == op2.Composited;
        }
	};

    class LogService;

	//////////////////////////////////////////////////////////////////////////////////////////
	//
	//	class LogService
	//
	namespace Log
	{
		class LogOutputHandler;


        // Log channel description
		class LogChannel
		{
        private:
            // Next channel
            LogChannel* m_pNextChannel{};

            // Channel name in string crc
            StringCrc32 m_ChannelName;

            // Channel name
            char m_ChannelNameString[128]{};

            // Channel mask
            LogOutputMask m_ChannelMask{};

            friend class SF::LogService;

        public: // used to be a structure, and allow access until we update all access


            LogChannel(const char* channelName, LogOutputType defaultLogLevel);
            LogChannel(const char* channelName, uint32_t channelMask);

            const LogOutputMask& GetChannelLogMask() const { return m_ChannelMask; }

            const char* GetChannelNameString() const { return m_ChannelNameString; }
            StringCrc32 GetChannelName() const { return m_ChannelName; }

            void SetChannelLogLevel(LogOutputType logLevel);
            void SetChannelLogMask(uint32_t logMask);
            void SetChannelLogMask(const LogOutputMask& logMask);

			LogChannel& operator = (const LogChannel& src)
			{
                m_ChannelMask = src.m_ChannelMask;
				return *this;
			}

			void EnableChannel(LogOutputType subChannel, bool enable)
			{
				auto channelMask = 1 << static_cast<uint32_t>(subChannel);
				if (enable)
                    m_ChannelMask.Composited |= channelMask;
				else
                    m_ChannelMask.Composited &= (~channelMask);
			}

        private:

            void Init(const char* channelName, uint32_t channelMask);
            void AddToChannelList();
        };



		constexpr LogOutputType Error = LogOutputType::Error;
		constexpr LogOutputType Warning = LogOutputType::Warning;
		constexpr LogOutputType Factal = LogOutputType::Factal;
		constexpr LogOutputType Info = LogOutputType::Info;
        constexpr LogOutputType Log = LogOutputType::Log;

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
		extern LogChannel Global;
        extern LogChannel System;
        extern LogChannel Net;
		extern LogChannel IO;
		extern LogChannel ThirdParty;
		extern LogChannel Engine;
		extern LogChannel Protocol;
		extern LogChannel Editor;
		extern LogChannel Game;



		//Structure for Spin Buffer
		struct LogItem
		{
			LogChannel* Channel{};
			LogOutputType		OutputType{};
			LogOutputMask		OutputMask{}; // GlobalMask & LogChannelMask
			SystemTimeStampMS	TimeStamp{};
			size_t LogStringSize = 0;
			char	LogBuff[3 * 1024]{};
		};

	}


	class LogService
	{
	private:

        // Log channel list. not thread safe for addition. should be initialized during global initialization section
        static Log::LogChannel* stm_ChannelList;

        // Log file name
        char m_LogFileName[1024]{};

	public:

		LogService(const LogOutputMask& logMask = LogOutputMask())
		{
            SF::Log::Global.SetChannelLogMask(logMask);
		}
		virtual ~LogService() {}

        const char* GetLogFileName() const { return m_LogFileName; }
        void SetLogFileName(const char* logFileName);

		// Check input mask
		bool ShouldPrint(const LogOutputMask& mainChannelMask, const LogOutputMask& channelMask)
		{
			uint32_t filterMask = mainChannelMask.Composited & SF::Log::Global.GetChannelLogMask().Composited;
			return filterMask & channelMask.Composited;
		}

		LogOutputMask ToChannelMask(const Log::LogChannel& mainChannel)
		{
			return mainChannel.GetChannelLogMask();
		}

		static LogOutputMask ToChannelMask(LogOutputType subChannel)
		{
			LogOutputMask channelMask;
			channelMask.Composited = (((uint32_t)1) << (int)subChannel);
			return channelMask;
		}

		void SetGlobalOutputMask(const LogOutputMask& outputMask) { SF::Log::Global.SetChannelLogMask(outputMask); }

		// output handler
		virtual void RegisterOutputHandler(Log::LogOutputHandler* output) {}
		virtual void UnregisterOutputHandler(Log::LogOutputHandler* output) {}

		// Reserve write buffer
		virtual void* ReserveWriteBuffer() { return nullptr; }
		virtual void ReleaseWriteBuffer(void* block, size_t messageSize) {}
		virtual size_t WriteTimeTag(Log::LogItem* pLogItem) { unused(pLogItem); return 0; }

		// Flush log queue
		virtual void Flush() {}

        // Find log channel with name
        static Log::LogChannel* FindLogChannel(const StringCrc32 channelName);
        static Log::LogChannel* FindLogChannelString(const char* channelName);

    private: // internal use
        friend class Log::LogChannel;
        static void AddToChannelList(Log::LogChannel* pLogChannel);
        static void RemoveFromChannelList(Log::LogChannel* pLogChannel);
	};

} // namespace SF
