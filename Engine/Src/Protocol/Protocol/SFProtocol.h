////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2016 Kyungkun Ko
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

	//namespace Message {
	//	class MessageData;
	//	class MessageBase;
	//}

	enum {
		SF_PROTOCOL_VERSION = 10
	};


	enum ProtocolID
	{
		// Policy 
		PROTOCOLID_NONE						= 0,			// Not defined policy

		PROTOCOLID_LOGIN					,
		PROTOCOLID_SVR_LOGIN				,

		PROTOCOLID_GAME						,				// Game policy
		PROTOCOLID_SVR_GAME					,				// Game policy

		PROTOCOLID_SERVER					,				// server generic policy
		PROTOCOLID_SVR_SERVER				,				// server generic policy

		PROTOCOLID_LOGINSERVER				,
		PROTOCOLID_SVR_LOGINSERVER			,

		PROTOCOLID_GAMESERVER				,				// Game server policy
		PROTOCOLID_SVR_GAMESERVER			,				// Game server policy

		PROTOCOLID_GAMEPARTY				,				// Game party server policy
		PROTOCOLID_SVR_GAMEPARTY			,				// Game party server policy

		PROTOCOLID_CLUSTERSERVER			,
		PROTOCOLID_SVR_CLUSTERSERVER		,

		PROTOCOLID_MONITORING,
		PROTOCOLID_SVR_MONITORING,

		PROTOCOLID_CHARACTERDATASERVER,
		PROTOCOLID_SVR_CHARACTERDATASERVER,

		//////////////////////////////////////////////////////////////////////////
		//
		//	Game cluster
		//

		PROTOCOLID_ENTITYSERVER				,				// entity server policy
		PROTOCOLID_SVR_ENTITYSERVER			,				// entity server policy

		PROTOCOLID_PARTYMATCHING			,
		PROTOCOLID_SVR_PARTYMATCHING		,

		PROTOCOLID_PARTYMATCHINGQUEUE		,
		PROTOCOLID_SVR_PARTYMATCHINGQUEUE	,

		PROTOCOLID_GAMEINSTANCE				,
		PROTOCOLID_SVR_GAMEINSTANCE			,

		PROTOCOLID_GAMEINSTANCEMANAGER		,
		PROTOCOLID_SVR_GAMEINSTANCEMANAGER	,

		PROTOCOLID_GAMEPARTYMANAGER			,
		PROTOCOLID_SVR_GAMEPARTYMANAGER		,

		PROTOCOLID_RANKING,
		PROTOCOLID_RANKINGSERVER,

		PROTOCOLID_CHATCHANNEL,
		PROTOCOLID_SVR_CHATCHANNEL,

		PROTOCOLID_CHATCHANNELMANAGER,
		PROTOCOLID_SVR_CHATCHANNELMANAGER,

		PROTOCOLID_RELAY,
		PROTOCOLID_RELAYSERVER,

		PROTOCOLID_NETMAX					,				// Max Network policy value
		PROTOCOLID_CLIENTNETMAX = PROTOCOLID_SVR_GAME+1,

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

	
}; // namespace SF



