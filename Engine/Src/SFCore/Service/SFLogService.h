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
	enum class ELogLevel : uint32_t
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

	const char* ToString(ELogLevel logOutputType);

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


            LogChannel(const char* channelName, ELogLevel defaultLogLevel);
            LogChannel(const char* channelName, uint32_t channelMask);

            const LogOutputMask& GetChannelLogMask() const { return m_ChannelMask; }

            const char* GetChannelNameString() const { return m_ChannelNameString; }
            StringCrc32 GetChannelName() const { return m_ChannelName; }

            void SetChannelLogLevel(ELogLevel logLevel);
            void SetChannelLogMask(uint32_t logMask);
            void SetChannelLogMask(const LogOutputMask& logMask);

			LogChannel& operator = (const LogChannel& src)
			{
                m_ChannelMask = src.m_ChannelMask;
				return *this;
			}

			void EnableChannel(ELogLevel subChannel, bool enable)
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



		constexpr ELogLevel Error = ELogLevel::Error;
		constexpr ELogLevel Warning = ELogLevel::Warning;
		constexpr ELogLevel Factal = ELogLevel::Factal;
		constexpr ELogLevel Info = ELogLevel::Info;
        constexpr ELogLevel Log = ELogLevel::Log;

		// Module additional traces
		constexpr ELogLevel Custom1 = ELogLevel::Custom1;
		constexpr ELogLevel Custom2 = ELogLevel::Custom2;
		constexpr ELogLevel Custom3 = ELogLevel::Custom3;
		constexpr ELogLevel Custom4 = ELogLevel::Custom4;
		constexpr ELogLevel Custom5 = ELogLevel::Custom5;
		constexpr ELogLevel Custom6 = ELogLevel::Custom6;
		constexpr ELogLevel Custom7 = ELogLevel::Custom7;
		constexpr ELogLevel Custom8 = ELogLevel::Custom8;
		constexpr ELogLevel Custom9 = ELogLevel::Custom9;
		constexpr ELogLevel Custom10 = ELogLevel::Custom10;

		constexpr ELogLevel Debug = ELogLevel::Debug;
		constexpr ELogLevel Debug1 = ELogLevel::Debug1;
		constexpr ELogLevel Debug2 = ELogLevel::Debug2;
		constexpr ELogLevel Debug3 = ELogLevel::Debug3;
		constexpr ELogLevel Debug4 = ELogLevel::Debug4;
		constexpr ELogLevel Debug5 = ELogLevel::Debug5;
		constexpr ELogLevel Debug6 = ELogLevel::Debug6;
		constexpr ELogLevel Debug7 = ELogLevel::Debug7;
		constexpr ELogLevel Debug8 = ELogLevel::Debug8;

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
			ELogLevel		OutputType{};
			LogOutputMask		OutputMask{}; // GlobalMask & LogChannelMask
            UTCTimeStampMS	TimeStamp{};
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

		static LogOutputMask ToChannelMask(ELogLevel subChannel)
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
