////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Policy Definitions
//	
//
////////////////////////////////////////////////////////////////////////////////



#pragma once


#include "SFTypedefs.h"
#include "Object/SFSharedObject.h"
#include "Object/SFSharedPointer.h"
#include "Net/SFMessageData.h"


namespace SF
{
	
	extern const uint32_t SF_PROTOCOL_VERSION;

    namespace MessageProtocol
    {
        constexpr uint None = 0;
        constexpr uint Generic = 1;

        constexpr uint Login = 3;
        constexpr uint Game = 4;
        constexpr uint PlayInstance = 5;
        constexpr uint Telemetry = 6;
        constexpr uint Relay = 7;

        constexpr uint GameCustomStart = 15;
        // TODO: separate
        //constexpr uint FishingGame = 12;
        //constexpr uint FishingPlayInstance = 13;

        constexpr uint ClientMax = 50;
        constexpr uint Max = 1 << NET_PROTOCOL_BITS;
    }


	class IVariableMapBuilder;
	typedef Result(*MessageHandlingFunction)(const char* prefix, const MessageHeader* pHeader);
	typedef Result(*HandleParseMessageTo)(const MessageHeader*, IVariableMapBuilder &);
	typedef Result(*HandleParseMessageToMessageBase)(IHeap& memoryManager, const MessageHeader*, MessageBase * &);
	
	

	namespace Protocol
	{
		//TODO: to library object
		void PrintDebugMessage(const char* preFix, const MessageHeader* pHeader);

		Result ParseMessage(const MessageHeader* pHeader, IVariableMapBuilder& variableMap);
		Result ParseMessage(IHeap& memoryManager, const MessageHeader* pHeader, MessageBase * &pMsgBase);
	}

	
} // namespace SF



