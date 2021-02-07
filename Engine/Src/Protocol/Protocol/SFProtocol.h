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
	
	extern const int SF_PROTOCOL_VERSION;

	enum ProtocolID
	{
		// Policy 
		PROTOCOLID_NONE						= 0,			// Not defined policy

		PROTOCOLID_LOGIN					,
		PROTOCOLID_GAME						,				// Game policy
		PROTOCOLID_PLAYINSTANCE,							// Play instance

		PROTOCOLID_SERVER					,				// server generic policy

		PROTOCOLID_LOGINSERVER				,
		PROTOCOLID_GAMESERVER				,				// Game server policy
		PROTOCOLID_GAMEPARTY				,				// Game party server policy

		PROTOCOLID_CHARACTERDATASERVER,

		//////////////////////////////////////////////////////////////////////////
		//
		//	Game cluster
		//

		PROTOCOLID_PARTYMATCHING			,
		PROTOCOLID_PARTYMATCHINGQUEUE		,
		PROTOCOLID_GAMEINSTANCE				,
		PROTOCOLID_GAMEINSTANCEMANAGER		,
		PROTOCOLID_GAMEPARTYMANAGER			,
		PROTOCOLID_RANKINGSERVER,
		PROTOCOLID_CHATCHANNEL,
		PROTOCOLID_CHATCHANNELMANAGER,

		// 
		PROTOCOLID_RELAY,
		PROTOCOLID_RELAYSERVER,

		// deprecated
		PROTOCOLID_CLUSTERSERVER,
		PROTOCOLID_MONITORING,

		PROTOCOLID_NETMAX					,				// Max Network policy value
	};


	class IVariableMapBuilder;
	typedef Result(*MessageHandlingFunction)(const char* prefix, const SharedPointerT<Message::MessageData>& pMsg);
	typedef Result(*HandleParseMessageTo)(SharedPointerT<Message::MessageData>&, IVariableMapBuilder &);
	typedef Result(*HandleParseMessageToMessageBase)(IHeap& memoryManager, SharedPointerT<Message::MessageData>&&, Message::MessageBase * &);
	
	

	namespace Protocol
	{
		void RegisterConnectionDebugMessage();
		void RegisterMessageParser();
		
		//TODO: to library object
		void PrintDebugMessage(const char* preFix, const SharedPointerT<Message::MessageData>& pMsg);
		Result ParseMessage(SharedPointerT<Message::MessageData>& pMsg, IVariableMapBuilder& variableMap);
		Result ParseMessage(IHeap& memoryManager, SharedPointerT<Message::MessageData>&& Msg, Message::MessageBase * &pMsgBase);
	}

	
} // namespace SF



