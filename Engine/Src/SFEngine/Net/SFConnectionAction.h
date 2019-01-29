////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2017 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Net connection action. 
//	
//
////////////////////////////////////////////////////////////////////////////////


#pragma once

#include "Net/SFNetDef.h"
#include "Net/SFNetCtrl.h"
#include "Net/SFNetUtil.h"
#include "Net/SFNetSystem.h"
#include "ResultCode/SFResultCodeEngine.h"
#include "Container/SFDoubleLinkedList.h"

namespace SF {

	namespace Message {
		struct MessageHeader;
	}

namespace Net {


	class Connection;


	////////////////////////////////////////////////////////////////////////////////
	//
	//	connection Action
	//

	class ConnectionActionBase
	{
	private:

		Connection* m_pConnection;

	private:

		void SetConnection(Connection* pConnection) { m_pConnection = pConnection; }

		friend class Connection;

	public:

		ConnectionActionBase();
		virtual ~ConnectionActionBase();

		Connection* GetConnection() { return m_pConnection; }

		// Get Connection info
		const PeerInfo& GetLocalInfo() const;
		const PeerInfo& GetRemoteInfo() const;

		// Get Connection ID
		uint64_t GetCID() const;

		// Get connection state
		const ConnectionState GetConnectionState() const;

		TimeStampMS GetNetCtrlTime();
		TimeStampMS GetNetCtrlTryTime();
		void UpdateNetCtrlTryTime();


		Result SendNetCtrl(uint uiCtrlCode, uint uiSequence, Message::MessageID msgID, uint64_t UID);

		Result Disconnect(const char* reason);
		Result CloseConnection(const char* reason);
	};



	class ConnectionAction : public ConnectionActionBase
	{
	public:


		virtual Result Run() = 0;
	};


	class ConnectionMessageAction : public ConnectionActionBase
	{
	public:

		void OnConnectionResult(Result hrConnect);

		virtual Result Run(const Message::MessageHeader* netCtrlMsg) = 0;
	};


/*
	class ConnectionStateAction : public ConnectionActionBase
	{
	public:

		TimeStampMS GetNetCtrlTime();
		TimeStampMS GetNetCtrlTryTime();
		TimeStampMS UpdateNetCtrlTryTime();

		virtual Result Run() = 0;
	};
*/



}  // namespace Net
} // namespace SF



