////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2016 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : EngineObject manager
//
////////////////////////////////////////////////////////////////////////////////


#pragma once 

#include "SFTypedefs.h"



namespace SF {


	//////////////////////////////////////////////////////////////////////////////////////////
	//
	//	class LogService
	//
	namespace Log
	{
		class LogOutputHandler;
	}


	// Main channel
	enum class LogMainChannelType : uint32_t
	{
		System,
		Net,
		IO,
		ThirdParty,
		Engine,
		DB,
		Protocol,
		Svr,
		Editor,
		Game,

		Custom,
		Max,
	};

	namespace LogMainChannels
	{
		constexpr LogMainChannelType System			= LogMainChannelType::System;
		constexpr LogMainChannelType Net			= LogMainChannelType::Net;
		constexpr LogMainChannelType IO				= LogMainChannelType::IO;
		constexpr LogMainChannelType ThirdParty		= LogMainChannelType::ThirdParty;
		constexpr LogMainChannelType Engine			= LogMainChannelType::Engine;
		constexpr LogMainChannelType DB				= LogMainChannelType::DB;
		constexpr LogMainChannelType Protocol		= LogMainChannelType::Protocol;
		constexpr LogMainChannelType Svr			= LogMainChannelType::Svr;
		constexpr LogMainChannelType Editor			= LogMainChannelType::Editor;
		constexpr LogMainChannelType Game			= LogMainChannelType::Game;

		constexpr LogMainChannelType Custom			= LogMainChannelType::Custom;
	}

	// sub channel
	enum class LogSubChannelType : uint32_t
	{
		// Generic trace
		Error,
		Warning,
		Assert,
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

	namespace LogSubChannels
	{
		constexpr LogSubChannelType Error		= LogSubChannelType::Error;
		constexpr LogSubChannelType Warning		= LogSubChannelType::Warning;
		constexpr LogSubChannelType Assert		= LogSubChannelType::Assert;
		constexpr LogSubChannelType Info		= LogSubChannelType::Info;

		// Module additional traces
		constexpr LogSubChannelType Custom1		= LogSubChannelType::Custom1;
		constexpr LogSubChannelType Custom2		= LogSubChannelType::Custom2;
		constexpr LogSubChannelType Custom3		= LogSubChannelType::Custom3;
		constexpr LogSubChannelType Custom4		= LogSubChannelType::Custom4;
		constexpr LogSubChannelType Custom5		= LogSubChannelType::Custom5;
		constexpr LogSubChannelType Custom6		= LogSubChannelType::Custom6;
		constexpr LogSubChannelType Custom7		= LogSubChannelType::Custom7;
		constexpr LogSubChannelType Custom8		= LogSubChannelType::Custom8;
		constexpr LogSubChannelType Custom9		= LogSubChannelType::Custom9;
		constexpr LogSubChannelType Custom10	= LogSubChannelType::Custom10;

		constexpr LogSubChannelType Debug = LogSubChannelType::Debug;
		constexpr LogSubChannelType Debug1 = LogSubChannelType::Debug1;
		constexpr LogSubChannelType Debug2 = LogSubChannelType::Debug2;
		constexpr LogSubChannelType Debug3 = LogSubChannelType::Debug3;
		constexpr LogSubChannelType Debug4 = LogSubChannelType::Debug4;
		constexpr LogSubChannelType Debug5 = LogSubChannelType::Debug5;
		constexpr LogSubChannelType Debug6 = LogSubChannelType::Debug6;
		constexpr LogSubChannelType Debug7 = LogSubChannelType::Debug7;
		constexpr LogSubChannelType Debug8 = LogSubChannelType::Debug8;

	}

	union LogChannelMask
	{
		struct
		{
			// Generic trace
			uint32_t Error : 1;
			uint32_t Warning : 1;
			uint32_t Assert : 1;
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

		LogChannelMask() {}
		LogChannelMask(uint32_t composited) :Composited(composited) {}
	};


	union LogMainChannelMask
	{
		struct
		{
			uint32_t System : 1;
			uint32_t Net : 1;
			uint32_t IO : 1;
			uint32_t ThirdParty : 1;
			uint32_t Engine : 1;
			uint32_t DB : 1;
			uint32_t Protocol : 1;
			uint32_t Svr : 1;
			uint32_t Editor : 1;
			uint32_t Game : 1;

			uint32_t Custom : 1;
			uint32_t : 0;
		};
		uint32_t Composited = std::numeric_limits<uint32_t>::max();


	};



#pragma pack(push, 4)

	struct LogChannelParameter
	{
		LogChannelMask MainChannelMasks[(int)LogMainChannelType::Max];
		LogChannelMask SubChannelMask;
	};

#pragma pack(pop)

	class LogService
	{
	protected:

		LogChannelParameter m_PrintParameter;

	public:

		LogService(const LogChannelParameter& logMask = LogChannelParameter()) { m_PrintParameter = logMask; }
		virtual ~LogService() {}

		// Check input mask

		// Check input mask
		bool ShouldPrint(const LogChannelMask& mainChannelMask, const LogChannelMask& channelMask)
		{
			auto filterMask = mainChannelMask.Composited & m_PrintParameter.SubChannelMask.Composited;
			return (filterMask & channelMask.Composited) == channelMask.Composited;
		}

		LogChannelMask ToChannelMask(LogMainChannelType mainChannel)
		{
			return m_PrintParameter.MainChannelMasks[(int)mainChannel];
		}

		static LogChannelMask ToChannelMask(LogSubChannelType subChannel)
		{
			LogChannelMask channelMask;
			channelMask.Composited = (((uint32_t)1) << (int)subChannel);
			return channelMask;
		}

		void SetPrintParameter(const LogChannelParameter& parameter) { m_PrintParameter = parameter; }

		// enable channel
		virtual void EnableChannel(LogMainChannelType mainChannel, LogSubChannelType subChannel, bool enable) {}
		virtual void EnableChannel(LogSubChannelType subChannel, bool enable) {}

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

}; // namespace SF

