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
#include "Net/SFConnectionAction.h"
#include "ResultCode/SFResultCodeEngine.h"



namespace SF {
namespace Net {


	class Connection;


	////////////////////////////////////////////////////////////////////////////////
	//
	//	net control connection Action
	//



	class ConnectionMessageAction_MUDPHandleAck : public ConnectionMessageAction
	{
	public:
		virtual Result Run(const Message::MessageHeader* netCtrlMsg) override;
	};


	class ConnectionMessageAction_MUDPHandleNack : public ConnectionMessageAction
	{
	public:
		virtual Result Run(const Message::MessageHeader* netCtrlMsg) override;
	};


	class ConnectionMessageAction_HandleHeartBit : public ConnectionMessageAction
	{
	public:
		virtual Result Run(const Message::MessageHeader* netCtrlMsg) override;
	};


	class ConnectionMessageAction_HandleTimeSync : public ConnectionMessageAction
	{
	public:
		virtual Result Run(const Message::MessageHeader* netCtrlMsg) override;
	};

	class ConnectionMessageAction_HandleTimeSyncRtn : public ConnectionMessageAction
	{
	public:
		virtual Result Run(const Message::MessageHeader* netCtrlMsg) override;
	};

	class ConnectionMessageAction_MUDPHandleSyncReliableServer : public ConnectionMessageAction
	{
	public:
		virtual Result Run(const Message::MessageHeader* netCtrlMsg) override;
	};


	class ConnectionMessageAction_MUDPHandleSyncReliableClient : public ConnectionMessageAction
	{
	public:
		virtual Result Run(const Message::MessageHeader* netCtrlMsg) override;
	};



	class ConnectionMessageAction_MUDPHandleConnect : public ConnectionMessageAction
	{
	public:
		virtual Result Run(const Message::MessageHeader* netCtrlMsg) override;
	};


	class ConnectionMessageAction_UDPHandleDisconnect : public ConnectionMessageAction
	{
	public:
		virtual Result Run(const Message::MessageHeader* netCtrlMsg) override;
	};



	////////////////////////////////////////////////////////////////////////////////
	//
	//	connection state Action
	//

	class ConnectionStateAction_DisposeOnExpire : public ConnectionAction
	{
	private:
		TimeStampMS m_Start;

	public:

		void Start() { m_Start = Util::Time.GetTimeMs(); }

		virtual Result Run() override;
	};

	class ConnectionStateAction_SendConnect : public ConnectionAction
	{
	public:
		virtual Result Run() override;
	};


	class ConnectionStateAction_SendHeartBit : public ConnectionAction
	{
	public:
		virtual Result Run() override;
	};

	class ConnectionStateAction_SendDisconnect : public ConnectionAction
	{
	public:
		virtual Result Run() override;
	};


	class ConnectionStateAction_SendSync : public ConnectionActionMUDP
	{
	private:

		TimeStampMS m_ReliableSyncTime = TimeStampMS(DurationMS_Zero);

	public:
		virtual Result Run() override;
	};

	class ConnectionStateAction_SendReliableQueue : public ConnectionActionMUDP
	{
	public:
		virtual Result Run() override;
	};

	class ConnectionStateAction_SendReliableRetry : public ConnectionActionMUDP
	{
	public:
		virtual Result Run() override;
	};


}  // namespace Net
} // namespace SF



