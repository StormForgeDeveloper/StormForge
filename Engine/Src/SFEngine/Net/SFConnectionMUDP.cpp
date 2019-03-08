////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2016 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Connection implementations
//	
//
////////////////////////////////////////////////////////////////////////////////

#include "SFEnginePCH.h"
#include "Thread/SFThread.h"
#include "SFAssert.h"
#include "ResultCode/SFResultCodeEngine.h"
#include "ResultCode/SFResultCodeLibrary.h"
#include "Util/SFLog.h"
#include "Util/SFTimeUtil.h"
#include "String/SFToString.h"
#include "String/SFHasher32.h"
#include "Protocol/SFProtocol.h"

#include "Net/SFConnectionMUDP.h"
#include "Net/SFNetDef.h"
#include "Net/SFNetSvrDef.h"
#include "Net/SFNetCtrl.h"
#include "Net/SFNetConst.h"
#include "Net/SFNetCtrl.h"
#include "Net/SFNetToString.h"



// define if emulate packet loss
//#ifdef _DEBUG
//#define UDP_PACKETLOS_EMULATE
//#endif


#ifdef UDP_PACKETLOS_EMULATE
	#define UDP_PACKETLOS_RATE	5
	#define UDP_PACKETLOS_BOUND	1
#endif // #ifdef UDP_PACKETLOS_EMULATE




namespace SF {
namespace Net {


	
	////////////////////////////////////////////////////////////////////////////////
	//
	//	Server Mobile UDP Network connection class
	//


	// Constructor
	ConnectionMUDP::ConnectionMUDP(IHeap& heap, SocketIO* ioHandler)
		: ConnectionUDPBase(heap, ioHandler)
	{
		// limit server net retry maximum
		SetMaxGuarantedRetry( Const::UDP_CLI_RETRY_ONETIME_MAX );
		SetUsePeerIDMap(true);

		SetNetCtrlAction(NetCtrlCode_Ack, &m_HandleAck);
		SetNetCtrlAction(NetCtrlCode_Nack, &m_HandleNack);
		SetNetCtrlAction(NetCtrlCode_HeartBit, &m_HandleHeartBit);
		SetNetCtrlAction(NetCtrlCode_TimeSync, &m_HandleTimeSync);
		SetNetCtrlAction(NetCtrlCode_Connect, &m_HandleConnect);
		SetNetCtrlAction(NetCtrlCode_Disconnect, &m_HandleDisconnect);

		AddStateAction(ConnectionState::CONNECTED, &m_ActSendReliableQueue);
		AddStateAction(ConnectionState::CONNECTED, &m_ActSendReliableRetry);
	}

	ConnectionMUDP::~ConnectionMUDP()
	{
	}

	
	// Make Ack packet and enqueue to SendNetCtrlqueue
	Result ConnectionMUDP::SendNetCtrl( uint uiCtrlCode, uint uiSequence, Message::MessageID msgID, uint64_t UID )
	{
		Result hr = ResultCode::SUCCESS, hrTem = ResultCode::SUCCESS;

		MsgMobileNetCtrl *pNetCtrl = nullptr;
		SharedPointerT<Message::MessageData> pMsg;

		netMem( pMsg = Message::MessageData::NewMessage(GetIOHeap(), uiCtrlCode, sizeof(MsgMobileNetCtrl) ) );

		pNetCtrl = (MsgMobileNetCtrl*)pMsg->GetMessageBuff();
		pNetCtrl->PeerID = UID == 0 ? GetLocalInfo().PeerID : UID;
		pNetCtrl->msgID.SetSequence(uiSequence);
		pNetCtrl->rtnMsgID = msgID;

		pMsg->GetMessageHeader()->msgID.IDs.Mobile = true;

		pMsg->UpdateChecksum();


		hrTem = SendRaw(pMsg);
		if( !(hrTem) )
		{
			SFLog(Net, Custom10, "NetCtrl Send failed : CID:{0}, msg:{1:X8}, seq:{2}, hr={3:X8}",
							GetCID(), 
							msgID.ID, 
							uiSequence, 
							hrTem );

			// ignore io send fail except connection closed
			if( hrTem == ((Result)ResultCode::IO_CONNECTION_CLOSED) )
			{
				goto Proc_End;
			}
		}

	Proc_End:

		if (!(hrTem))
		{
			SFLog(Net, Custom10, "NetCtrl Send failed : CID:{0}, msg:{1:X8}, seq:{2}, hr={3:X8}",
				GetCID(),
				msgID.ID,
				uiSequence,
				hrTem);
		}

		return hr;
	}

	// Process network control message
	Result ConnectionMUDP::ProcNetCtrl(const MsgNetCtrl* netCtrl)
	{
		//assert(ThisThread::GetThreadID() == GetRunningThreadID());

		const MsgMobileNetCtrl* pNetCtrl = (const MsgMobileNetCtrl*)netCtrl;
		Result hr = ResultCode::SUCCESS;
		ConnectionMessageAction* pAction = nullptr;

		if (pNetCtrl->msgID.IDs.Mobile == 0 || pNetCtrl->Length < sizeof(MsgMobileNetCtrl))
		{
			SFLog(Net, Info, "HackWarn : Invalid packet CID:{0}, Addr {1}", GetCID(), GetRemoteInfo().PeerAddress);
			netChk(Disconnect("Invalid packet"));
			netErr(ResultCode::IO_BADPACKET_NOTEXPECTED);
		}

		pAction = m_NetCtrlAction[pNetCtrl->msgID.IDs.MsgCode];
		if (pAction != nullptr)
		{
			return pAction->Run(pNetCtrl);
		}
		else
		{
			// Not handle or invalid
			SFLog(Net, Warning, "HackWarn : Not handled or Invalid net control packet CID:{0}, Addr {1}", GetCID(), GetRemoteInfo().PeerAddress);
			netChk(CloseConnection("Invalid net ctrl action"));
			netErr(ResultCode::UNEXPECTED);
		}


	Proc_End:


		return hr;
	}


	// called when incoming message occur
	Result ConnectionMUDP::OnRecv( uint uiBuffSize, const uint8_t* pBuff )
	{
		Result hr = ResultCode::SUCCESS;
		SharedPointerT<Message::MessageData> pMsg;
		Message::MobileMessageHeader * pMsgHeader = (Message::MobileMessageHeader*)pBuff;

		SFLog(Net, Debug3, "UDP Recv ip:{0}, msg:{1}, seq:{2}, len:{3}", GetRemoteInfo().PeerAddress, pMsgHeader->msgID, pMsgHeader->msgID.IDSeq.Sequence, uiBuffSize);

		if( uiBuffSize == 0 )
		{
			IncZeroRecvCount();

			if( GetZeroRecvCount() > (uint32_t)Const::CONNECTION_ZEROPACKET_MAX )
			{
				Disconnect("Too many zero packet");
			}
			return hr;
		}

		MutexScopeLock scopeLock(GetUpdateLock());

		while( uiBuffSize && GetConnectionState() != ConnectionState::DISCONNECTED)
		{
			pMsgHeader = (Message::MobileMessageHeader*)pBuff;
			if( uiBuffSize < sizeof(Message::MobileMessageHeader) || uiBuffSize < pMsgHeader->Length )
			{
				SFLog(Net, Error, "Unexpected packet buffer size:{0}, size in header:{1}", uiBuffSize, pMsgHeader->Length );
				netErr( ResultCode::IO_BADPACKET_SIZE );
			}

#ifdef UDP_PACKETLOS_EMULATE
			if( (Util::Random.Rand() % UDP_PACKETLOS_RATE) < UDP_PACKETLOS_BOUND )
				goto Proc_End;
#endif	// UDP_PACKETLOS_EMULATE

			ResetZeroRecvCount();

			if (pMsgHeader->msgID.IDs.Type == Message::MSGTYPE_NETCONTROL && pMsgHeader->msgID.IDs.Reliability == false) // if net control message then process immidiately
			{
				netChk(ProcNetCtrl((MsgNetCtrl*)pMsgHeader));
			}
			else
			{
				if (GetConnectionState() == ConnectionState::CONNECTED)
				{
					netMem( pMsg = Message::MessageData::NewMessage(GetHeap(), pMsgHeader->msgID.ID, pMsgHeader->Length, pBuff ) );

					hr = OnRecv( pMsg );
					netChk( hr );
				}
				else
				{
					if (GetConnectionState() != ConnectionState::CONNECTING)
					{
						// Sending normal message packet without connection process.
						// Disconnect them
						netChk(Disconnect("Invalid packet type"));
						netErr(ResultCode::IO_BADPACKET_NOTEXPECTED);
					}
				}
			}


			uiBuffSize -= pMsgHeader->Length;
			pBuff += pMsgHeader->Length;
			pMsg = nullptr;
		}

	Proc_End:

		pMsg = nullptr;

		SendFlush();

		return hr;
	}


	Result ConnectionMUDP::OnRecv(SharedPointerT<Message::MessageData>& pMsg )
	{
		Result hr = ResultCode::SUCCESS;
		Message::MessageHeader* pMsgHeader = pMsg->GetMessageHeader();

		if (GetConnectionState() != ConnectionState::CONNECTED)
		{
			goto Proc_End;
		}

		netChk( pMsg->ValidateChecksumNDecrypt() );

		if( pMsgHeader->msgID.IDs.Reliability )
		{
			Assert( !pMsgHeader->msgID.IDs.Encrypted );

			SFLog(Net, Debug2, "RECVGua    : CID:{0} msg:{1}, seq:{2}, len:{3}",
				GetCID(), 
				pMsg->GetMessageHeader()->msgID,
				pMsg->GetMessageHeader()->msgID.IDSeq.Sequence,
				pMsg->GetMessageHeader()->Length);

			netChk(OnGuarrentedMessageRecv(pMsg));
			pMsg = nullptr;
		}
		else
		{
			hr = ConnectionUDPBase::OnRecv(pMsg);
			pMsg = nullptr;
			netChk( hr );
		}


	Proc_End:

		pMsg = nullptr;

		if( !( hr ) )
		{
			CloseConnection("OnRecv is failed");
		}

		return hr;
	}
	

	// gathering
	Result ConnectionMUDP::SendPending( uint uiCtrlCode, uint uiSequence, Message::MessageID msgID, uint64_t UID )
	{
		Result hr = ResultCode::SUCCESS;

		MsgMobileNetCtrl *pNetCtrlMsg = nullptr;

		netChk( PrepareGatheringBuffer(sizeof(MsgNetCtrlBuffer)) );

		pNetCtrlMsg = (MsgMobileNetCtrl*)(m_pGatheringBuffer+m_uiGatheredSize);
		pNetCtrlMsg->msgID.ID = uiCtrlCode;
		pNetCtrlMsg->msgID.SetSequence(uiSequence);
		pNetCtrlMsg->rtnMsgID = msgID;
		pNetCtrlMsg->PeerID = UID == 0 ? GetLocalInfo().PeerID : UID;

		pNetCtrlMsg->msgID.IDs.Mobile = true;
		pNetCtrlMsg->Length = sizeof(MsgMobileNetCtrl);

		pNetCtrlMsg->Crc32 = Hasher_Crc32().Crc32( 0, (uint8_t*)pNetCtrlMsg + sizeof(Message::MobileMessageHeader) , sizeof(MsgMobileNetCtrl) - sizeof(Message::MobileMessageHeader));
		if( pNetCtrlMsg->Crc32 == 0 ) pNetCtrlMsg->Crc32 = ~pNetCtrlMsg->Crc32;

		m_uiGatheredSize += pNetCtrlMsg->Length;


	Proc_End:

		return hr;
	}

	Result ConnectionMUDP::SendSync( uint uiSequence, uint64_t uiSyncMask )
	{
		Result hr = ResultCode::SUCCESS;
		MsgMobileNetCtrlSync *pNetCtrlMsg = NULL;

		netChk( PrepareGatheringBuffer(sizeof(MsgMobileNetCtrlSync)) );

		pNetCtrlMsg = (MsgMobileNetCtrlSync*)(m_pGatheringBuffer+m_uiGatheredSize);
		pNetCtrlMsg->msgID = PACKET_NETCTRL_SYNCRELIABLE;
		pNetCtrlMsg->msgID.SetSequence(uiSequence);
		pNetCtrlMsg->MessageMask = uiSyncMask;
		pNetCtrlMsg->PeerID = GetLocalInfo().PeerID;

		pNetCtrlMsg->msgID.IDs.Mobile = true;
		pNetCtrlMsg->Length = sizeof(MsgMobileNetCtrlSync);

		pNetCtrlMsg->Crc32 = Hasher_Crc32().Crc32(0, (uint8_t*)pNetCtrlMsg + sizeof(Message::MobileMessageHeader), sizeof(MsgMobileNetCtrlSync) - sizeof(Message::MobileMessageHeader));
		if( pNetCtrlMsg->Crc32 == 0 ) pNetCtrlMsg->Crc32 = ~pNetCtrlMsg->Crc32;

		//AssertRel(m_RecvReliableWindow.GetBaseSequence() != 1 && uiSequence != 1 || uiSyncMask == 0);
		SFLog(Net, Custom10, "NetCtrl Send MyRecvMask : CID:{0} mySeq:{1}, mask:{2:X8}",
			GetCID(), uiSequence, uiSyncMask);

		m_uiGatheredSize += pNetCtrlMsg->Length;


	Proc_End:

		return hr;
	}



	Result ConnectionMUDP::OnGuarrentedMessageRecv(SharedPointerT<Message::MessageData>& pIMsg)
	{
		Result hr = ResultCode::SUCCESS;

		auto msgID = pIMsg->GetMessageHeader()->msgID;
		auto seq = pIMsg->GetMessageHeader()->msgID.IDSeq.Sequence;
		auto len = pIMsg->GetMessageHeader()->Length;

		Result hrTem = m_RecvReliableWindow.AddMsg(pIMsg);

		SFLog(Net, Debug2, "RECVGuaAdd : CID:{0} BaseSeq:{1}, msg:{2}, seq:{3}, len:%4%, hr={5:X8}",
			GetCID(), m_RecvReliableWindow.GetBaseSequence(),
			msgID,
			seq,
			len,
			hrTem);

		if (hrTem == Result(ResultCode::SUCCESS_IO_PROCESSED_SEQUENCE))
		{
			pIMsg = nullptr;
			return hr;
		}
		else if (hrTem == Result(ResultCode::IO_INVALID_SEQUENCE) || hrTem == Result(ResultCode::IO_SEQUENCE_OVERFLOW))
		{
			// out of window, we are going to receive this message again
			pIMsg = nullptr;
			return hr;
		}
		else
		{
			netChk(hrTem);
			// Added to msg window just send ACK
			pIMsg = nullptr;

			SharedPointerT<Message::MessageData> pPopMsg;
			while (m_RecvReliableWindow.PopMsg(pPopMsg))
			{
				hr = ConnectionUDPBase::OnRecv(pPopMsg);
			}

			if (GetEventHandler() != nullptr)
			{
				GetEventHandler()->OnRecvMessage(this, MessageDataPtr());
			}
		}

	Proc_End:

		pIMsg = nullptr;

		return hr;
	}


	// Update net control, process connection heart bit, ... etc
	Result ConnectionMUDP::TickUpdate()
	{
		Result hr = ResultCode::SUCCESS;
		Message::MessageID msgIDTem;

		MutexScopeLock scopeLock(GetUpdateLock());

		hr = ProcConnectionStateAction();
		if( !(hr) )
		{
			SFLog(Net, Info, "Process Connection state failed {0:X8}", hr );
		}


	//Proc_End:

		SendFlush();

		return hr;
	}






} // namespace Net
} // namespace SF


