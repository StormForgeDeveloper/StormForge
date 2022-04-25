////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Connection implementations
//	
//
////////////////////////////////////////////////////////////////////////////////

#include "SFEnginePCH.h"
#include "Multithread/SFThread.h"
#include "SFAssert.h"
#include "ResultCode/SFResultCodeEngine.h"
#include "ResultCode/SFResultCodeLibrary.h"
#include "Util/SFLog.h"
#include "Util/SFTimeUtil.h"
#include "Util/SFToString.h"
#include "Protocol/SFProtocol.h"

#include "Net/SFNetToString.h"
#include "Net/SFConnectionUDPBase.h"
#include "Net/SFConnectionUDP.h"
#include "Net/SFNetDef.h"
#include "Net/SFNetSvrDef.h"
#include "Net/SFNetCtrl.h"
#include "Net/SFNetConst.h"
#include "Net/SFNetCtrl.h"



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
	//	UDP Network connection class
	//


	// Constructor
	ConnectionUDPBase::ConnectionUDPBase(IHeap& heap, SocketIO* ioHandler)
		: Connection(heap, ioHandler)
		, m_RecvReliableWindow(GetHeap())
		, m_SendReliableWindow(GetHeap())
		, m_uiMaxGuarantedRetryAtOnce(Const::UDP_SVR_RETRY_ONETIME_MAX)
		, m_uiGatheredSize(0)
		, m_pGatheringBuffer(nullptr)
		, m_pWriteQueuesUDP(nullptr)
	{
		SetHeartbeatTry( Const::UDP_HEARTBEAT_TIME);

		SetWriteQueueUDP(Service::NetSystem->GetWriteBufferQueue());
		SetUseAddressMap(true);

		SetNetCtrlAction(NetCtrlCode_Ack, &m_HandleAck);
		SetNetCtrlAction(NetCtrlCode_Nack, &m_HandleNack);
		SetNetCtrlAction(NetCtrlCode_Heartbeat, &m_HandleHeartbeat);
		SetNetCtrlAction(NetCtrlCode_TimeSync, &m_HandleTimeSync);
		SetNetCtrlAction(NetCtrlCode_Connect, &m_HandleConnect);
		SetNetCtrlAction(NetCtrlCode_Disconnect, &m_HandleDisconnect);

		AddStateAction(ConnectionState::CONNECTED, &m_ActSendReliableQueue);
		AddStateAction(ConnectionState::CONNECTED, &m_ActSendReliableRetry);
	}

	ConnectionUDPBase::~ConnectionUDPBase()
	{
		m_RecvReliableWindow.ClearWindow();
		m_SendReliableWindow.ClearWindow();


		if(m_pGatheringBuffer != nullptr)
			IHeap::Delete(m_pGatheringBuffer);
		m_pGatheringBuffer = nullptr;

		m_SubFrameMessage = nullptr;
	}

	void ConnectionUDPBase::SetWriteQueueUDP(WriteBufferQueue* writeQueue)
	{
		Assert(NetSystem::IsProactorSystem() || writeQueue != nullptr);

		m_pWriteQueuesUDP = writeQueue;
	}




	// Update Send buffer Queue, TCP and UDP client connection
	Result ConnectionUDPBase::UpdateSendBufferQueue()
	{
		Assert(false);
		return ResultCode::NOT_IMPLEMENTED;
	}

	Result ConnectionUDPBase::UpdateSendQueue()
	{
		Result hr;
		if (GetConnectionState() == ConnectionState::DISCONNECTED)
			return ResultCode::SUCCESS;

		MutexScopeLock localLock(GetUpdateLock());

		// Force update send
		m_ActSendReliableQueue.Run();
		m_ActSendReliableRetry.Run();

		// Flush sync message asap
		SendFlush();

		return hr;
	}

	// gathering
	Result ConnectionUDPBase::SendPending( uint uiCtrlCode, uint uiSequence, Message::MessageID msgID, uint64_t UID )
	{
		Result hr = ResultCode::SUCCESS;

		MsgNetCtrl *pNetCtrlMsg = NULL;

		netChk( PrepareGatheringBuffer(sizeof(MsgNetCtrlBuffer)) );

		pNetCtrlMsg = (MsgNetCtrl*)(m_pGatheringBuffer+m_uiGatheredSize);
		pNetCtrlMsg->msgID.ID = uiCtrlCode;
		pNetCtrlMsg->msgID.SetSequence(uiSequence);
		pNetCtrlMsg->rtnMsgID = msgID;

		if( UID != 0 )
		{
			MsgNetCtrlConnect *pNetCtrlCon = (MsgNetCtrlConnect*)pNetCtrlMsg;
			pNetCtrlCon->Peer = GetLocalInfo();
			pNetCtrlMsg->Length = sizeof(MsgNetCtrlConnect);
		}
		else
		{
			pNetCtrlMsg->Length = sizeof(MsgNetCtrl);
		}
		m_uiGatheredSize += pNetCtrlMsg->Length;


	Proc_End:

		return hr;
	}

	Result ConnectionUDPBase::SendPending(SharedPointerT<Message::MessageData>& pMsg )
	{
		Result hr = ResultCode::SUCCESS;

		netCheckPtr( pMsg );

		if( pMsg->GetMessageSize() > (uint)Const::INTER_PACKET_SIZE_MAX )
		{
			netCheck( ResultCode::IO_BADPACKET_TOOBIG );
		}

		if( !(PrepareGatheringBuffer(pMsg->GetMessageSize()) ) )
		{
			return Send(pMsg);
		}

		memcpy( m_pGatheringBuffer+m_uiGatheredSize, pMsg->GetMessageBuff(), pMsg->GetMessageSize() );

		m_uiGatheredSize += pMsg->GetMessageSize();

		return hr;
	}

	Result ConnectionUDPBase::SendFlush()
	{
		Result hr = ResultCode::SUCCESS;
		IOBUFFER_WRITE *pSendBuffer = nullptr;

		// Send Flush and PrepareGathering should be called on the same thread
		//AssertRel(GetRunningThreadID() == ThisThread::GetThreadID());


		auto pIOHandler = GetNetIOHandler();
		if (pIOHandler != nullptr)
		{
			if (pIOHandler->GetIsIORegistered() && GetConnectionState() != ConnectionState::DISCONNECTED
				&& m_uiGatheredSize && m_pGatheringBuffer)
			{
				uint GatherSize = m_uiGatheredSize;
				uint8_t* pGatherBuff = m_pGatheringBuffer;

				m_uiGatheredSize = 0;
				m_pGatheringBuffer = nullptr;

				pIOHandler->IncPendingSendCount();

				netMem(pSendBuffer = new(GetIOHeap()) IOBUFFER_WRITE);
				pSendBuffer->SetupSendUDP(GetSocket(), GetRemoteSockAddr(), GatherSize, pGatherBuff);

				if (NetSystem::IsProactorSystem())
				{
					if (GetNetIOHandler() != nullptr)
					{
						netChk(GetNetIOHandler()->WriteBuffer(pSendBuffer));
					}
				}
				else
				{
					netChk(EnqueueBufferUDP(pSendBuffer));
				}

				pSendBuffer = nullptr;
			}

		}


	Proc_End:

		if(!hr && pIOHandler != nullptr)
			pIOHandler->DecPendingSendCount();


		m_uiGatheredSize = 0;
		if( m_pGatheringBuffer != nullptr )
			IHeap::Delete(m_pGatheringBuffer);

		if (pSendBuffer != nullptr)
			IHeap::Delete(pSendBuffer);

		m_pGatheringBuffer = nullptr;


		return hr;
	}

	// Prepare gathering buffer
	Result ConnectionUDPBase::PrepareGatheringBuffer( uint uiRequiredSize )
	{
		Result hr = ResultCode::SUCCESS;

		// You tried to use this method in a wrong way
		if( uiRequiredSize > Const::PACKET_GATHER_SIZE_MAX )
		{
			return ResultCode::FAIL;
		}

		//AssertRel(GetRunningThreadID() == ThisThread::GetThreadID());

		if( (m_uiGatheredSize + uiRequiredSize) > (uint)Const::PACKET_GATHER_SIZE_MAX )
		{
			hr = SendFlush();
			if (!hr) return hr;
			Assert(m_uiGatheredSize == 0);
		}

		if( m_pGatheringBuffer == nullptr )
		{
			m_pGatheringBuffer = new(GetIOHeap()) uint8_t[Const::PACKET_GATHER_SIZE_MAX];
			if (m_pGatheringBuffer == nullptr)
				return ResultCode::OUT_OF_MEMORY;
		}

		return hr;
	}


	// frame sequence
	Result ConnectionUDPBase::SendFrameSequenceMessage(const SharedPointerT<Message::MessageData>& pMsg)
	{
		Result hr = ResultCode::SUCCESS;
		TimeStampMS ulTimeCur = Util::Time.GetTimeMs();
		auto pSrcMsgHeader = pMsg->GetMessageHeader();
		auto remainSize = pSrcMsgHeader->Length;
		unsigned offset = 0;

		assert(pMsg->GetMessageHeader()->msgID.IDSeq.Sequence == 0);

		SFLog(Net, Debug2, "SEND Spliting : CID:{0}, seq:{1}, msg:{2}, len:{3}",
			GetCID(),
			pMsg->GetMessageHeader()->msgID.IDSeq.Sequence,
			pMsg->GetMessageHeader()->msgID,
			pMsg->GetMessageHeader()->Length);

		const uint8_t* pCurSrc = pMsg->GetMessageBuff();
		for (uint iSequence = 0; remainSize > 0; iSequence++)
		{
			auto frameSize = Math::Min(remainSize, (uint)Message::MAX_SUBFRAME_SIZE);

			MsgNetCtrlSequenceFrame* pCurrentFrame = nullptr;
			SharedPointerT<Message::MessageData> pSubframeMessage;

			netCheckPtr(pSubframeMessage = Message::MessageData::NewMessage(GetHeap(), PACKET_NETCTRL_SEQUENCE_FRAME, uint(sizeof(Message::MessageHeader) + sizeof(MsgNetCtrlSequenceFrame) + frameSize)));

			// fill up frame header
			pCurrentFrame = (MsgNetCtrlSequenceFrame*)pSubframeMessage->GetMessageData();
			pCurrentFrame->Offset = uint16_t(offset);
			pCurrentFrame->ChunkSize = uint16_t(frameSize);
			pCurrentFrame->TotalSize = uint16_t(pSrcMsgHeader->Length);

			// copy frame size
			memcpy(pCurrentFrame + 1, pCurSrc, frameSize);

			SFLog(Net, Debug3, "Send subframe: CID:{0}, seq:{1}, msg:{2}, len:{3}",
				GetCID(),
				pSubframeMessage->GetMessageHeader()->msgID.IDSeq.Sequence,
				pSubframeMessage->GetMessageHeader()->msgID,
				pSubframeMessage->GetMessageHeader()->Length);

			pSubframeMessage->UpdateChecksumNEncrypt();

			netCheck(m_SendGuaQueue.Enqueue(pSubframeMessage));

			remainSize -= frameSize;
			offset += frameSize;
			pCurSrc += frameSize;
		}

		return hr;
	}

	Result ConnectionUDPBase::OnFrameSequenceMessage(SharedPointerT<Message::MessageData>& pMsg, const std::function<void(SharedPointerT<Message::MessageData>& pMsgData)>& action)
	{
		Result hr = ResultCode::SUCCESS;
		if (pMsg == nullptr)
			return ResultCode::INVALID_POINTER;

		auto pCurrentFrame = reinterpret_cast<MsgNetCtrlSequenceFrame*>(pMsg->GetMessageData());

		auto* dataPtr = reinterpret_cast<const uint8_t*>(pCurrentFrame + 1);

		if (pCurrentFrame->ChunkSize > Message::MAX_SUBFRAME_SIZE)
		{
			netCheck(ResultCode::IO_BADPACKET_NOTEXPECTED);
		}

		if (pCurrentFrame->Offset == 0) // first frame
		{
			m_SubFrameMessage = nullptr;

			uint dummyID = PACKET_NETCTRL_SEQUENCE_FRAME;

			netCheckPtr(m_SubFrameMessage = Message::MessageData::NewMessage(GetHeap(), dummyID, pCurrentFrame->TotalSize));

			memcpy(m_SubFrameMessage->GetMessageBuff(), dataPtr, pCurrentFrame->ChunkSize);
		}
		else
		{
			if (m_SubFrameMessage == nullptr)
			{
				Assert(m_SubFrameMessage != nullptr);
				netCheck(ResultCode::IO_BADPACKET_NOTEXPECTED);
			}

			if (m_SubFrameMessage->GetMessageHeader()->Length != pCurrentFrame->TotalSize)
			{
				Assert(false);
				netCheck(ResultCode::IO_BADPACKET_NOTEXPECTED);
			}

			memcpy(m_SubFrameMessage->GetMessageBuff() + pCurrentFrame->Offset, dataPtr, pCurrentFrame->ChunkSize);
		}

		auto receivedSize = pCurrentFrame->Offset + pCurrentFrame->ChunkSize;
		if (receivedSize > pCurrentFrame->TotalSize)
		{
			netCheck(ResultCode::IO_BADPACKET_NOTEXPECTED);
		}
		else if (receivedSize == pCurrentFrame->TotalSize)
		{
			// done
			//netCheck(m_SubFrameMessage->ValidateChecksumNDecrypt());
			action(m_SubFrameMessage);
			m_SubFrameMessage = nullptr;
		}

		return hr;
	}

	// Initialize connection
	Result ConnectionUDPBase::InitConnection(const PeerInfo &local, const PeerInfo &remote)
	{
		Result hr = ResultCode::SUCCESS;

		m_uiGatheredSize = 0;

		//m_RecvGuaQueue.ClearQueue();

		netCheck(Connection::InitConnection( local, remote ) );

		netCheck( ClearQueues() );

		m_SubFrameMessage = nullptr;

		return hr;
	}

	// Close connection
	Result ConnectionUDPBase::CloseConnection(const char* reason)
	{
		Result hr = ResultCode::SUCCESS;

		if (GetConnectionState() == ConnectionState::CONNECTED)
			Disconnect(reason);

		hr = Connection::CloseConnection(reason);

		m_SubFrameMessage = nullptr;

		return hr;
	}

	// Clear Queue
	Result ConnectionUDPBase::ClearQueues()
	{
		Connection::ClearQueues();

		m_RecvReliableWindow.ClearWindow();
		m_SendReliableWindow.ClearWindow();

		m_SubFrameMessage = nullptr;

		return ResultCode::SUCCESS;
	}

	// Disconnect connection
	Result ConnectionUDPBase::Disconnect(const char* reason)
	{
		if (GetConnectionState() != ConnectionState::CONNECTED)
		{
			// Send disconnect signal
			Message::MessageID msgIDTem;

			msgIDTem.ID = PACKET_NETCTRL_NONE;
			SendNetCtrl(PACKET_NETCTRL_DISCONNECT, 0, msgIDTem);
		}

		return Connection::Disconnect(reason);
	}

	Result ConnectionUDPBase::EnqueueBufferUDP(IOBUFFER_WRITE *pSendBuffer)
	{
		if (GetWriteQueueUDP() == nullptr)
		{
			Assert(false);
			return ResultCode::UNEXPECTED;
		}

		return GetWriteQueueUDP()->Enqueue(pSendBuffer);
	}

	Result ConnectionUDPBase::SendRaw(const SharedPointerT<Message::MessageData> &pMsg)
	{
		SFUniquePtr<IOBUFFER_WRITE> pSendBuffer;
		auto pIOHandler = GetNetIOHandler();
		if (pIOHandler == nullptr || !pIOHandler->GetIsIORegistered())
			return ResultCode::SUCCESS_FALSE;

		ScopeContext hr([this, &pIOHandler](Result hr)
			{
				if (!hr)
					pIOHandler->DecPendingSendCount();
			});


		pIOHandler->IncPendingSendCount();

		netCheckPtr(pMsg);

		if (pMsg->GetDataLength() != 0 && pMsg->GetMessageHeader()->Crc32 == 0 && pMsg->GetMessageHeader()->msgID.IDs.Policy != PROTOCOLID_NONE)
		{
			Assert(pMsg->GetDataLength() == 0 || pMsg->GetMessageHeader()->Crc32 != 0 || pMsg->GetMessageHeader()->msgID.IDs.Policy == PROTOCOLID_NONE);
			netCheck(ResultCode::FAIL);
		}

		pSendBuffer.reset(new(GetIOHeap()) IOBUFFER_WRITE);
		netCheckMem(pSendBuffer);

		pSendBuffer->SetupSendUDP(GetSocket(), GetRemoteSockAddr(), SharedPointerT<Message::MessageData>(pMsg));

		if (NetSystem::IsProactorSystem())
		{
			if (GetNetIOHandler() != nullptr)
			{
				netCheck(GetNetIOHandler()->WriteBuffer(pSendBuffer.get()));
			}
		}
		else
		{
			netCheck(EnqueueBufferUDP(pSendBuffer.get()));
		}

		pSendBuffer.release();

		return hr;
	}

	// Process network control message
	Result ConnectionUDPBase::ProcNetCtrl(const MsgNetCtrl* pNetCtrl)
	{
		//assert(ThisThread::GetThreadID() == GetRunningThreadID());

		Result hr = ResultCode::SUCCESS;
		ConnectionMessageAction* pAction = nullptr;

		if (pNetCtrl->Length < sizeof(MsgNetCtrl))
		{
			SFLog(Net, Info, "HackWarn : Invalid packet CID:{0}, Addr {1}", GetCID(), GetRemoteInfo().PeerAddress);
			netCheck(Disconnect("Invalid packet"));
			netCheck(ResultCode::IO_BADPACKET_NOTEXPECTED);
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
			netCheck(CloseConnection("Invalid net ctrl action"));
			netCheck(ResultCode::UNEXPECTED);
		}

		return hr;
	}

	Result ConnectionUDPBase::OnGuaranteedMessageRecv(SharedPointerT<Message::MessageData>& pIMsg)
	{
		Result hr = ResultCode::SUCCESS;

		auto pHeader = pIMsg->GetMessageHeader();
		auto msgID = pHeader->msgID;
		auto seq = pHeader->msgID.IDSeq.Sequence;
		auto len = pHeader->Length;

		Result hrTem = m_RecvReliableWindow.AddMsg(pIMsg);

		SFLog(Net, Debug2, "RECVGuaAdd : CID:{0} msgId:{1}, seq:{2}, len:{3}, hr:{4}, Window base:{5}, msgCount:{6}, syncMask:{7}",
			GetCID(), 
			msgID, seq, len, hrTem,
			m_RecvReliableWindow.GetBaseSequence(), m_RecvReliableWindow.GetMsgCount(), m_RecvReliableWindow.GetSyncMask());

		if (hrTem == Result(ResultCode::SUCCESS_IO_PROCESSED_SEQUENCE))
		{
			// Added to msg window just send ACK
			SendReliableMessageAck(msgID);

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
			netCheck(hrTem);

			// Added to msg window just send ACK
			SendReliableMessageAck(msgID);

			pIMsg = nullptr;

			SharedPointerT<Message::MessageData> pPopMsg;
			while (m_RecvReliableWindow.PopMsg(pPopMsg))
			{
				if (pPopMsg->GetMessageHeader()->msgID.GetMsgID() == PACKET_NETCTRL_SEQUENCE_FRAME.GetMsgID())
				{
					hr = OnFrameSequenceMessage(pPopMsg, [this](SharedPointerT<Message::MessageData>& pMsgData) { super::OnRecv(pMsgData); });
				}
				else
				{
					hr = super::OnRecv(pPopMsg);
				}
			}

			//if (GetEventHandler() != nullptr)
			//{
			//	MessageDataPtr temp;
			//	GetEventHandler()->OnRecvMessage(this, temp);
			//}
		}

		pIMsg = nullptr;

		return hr;
	}

	Result ConnectionUDPBase::SendReliableMessageAck(Message::MessageID msgID)
	{
		return SendNetCtrl(PACKET_NETCTRL_ACK, msgID.IDSeq.Sequence, msgID, GetLocalInfo().PeerID);
	}

	// Send message to connected entity
	Result ConnectionUDPBase::Send(const SharedPointerT<Message::MessageData> &pMsg )
	{
		Message::MessageID msgID;
		ScopeContext hr([this, &msgID](Result hr)
			{
				if (hr)
				{
					if (msgID.IDs.Type == Message::MSGTYPE_NETCONTROL)
					{
						SFLog(Net, Debug6, "TCP Ctrl CID:{2}, ip:{0}, msg:{1}", GetRemoteInfo().PeerAddress, msgID, GetCID());
					}
					else
					{
						SFLog(Net, Debug5, "TCP Send CID:{2}, ip:{0}, msg:{1}", GetRemoteInfo().PeerAddress, msgID, GetCID());
					}
				}

			});
		uint uiMsgLen;

		if (GetConnectionState() == ConnectionState::DISCONNECTED)
			return ResultCode::SUCCESS_FALSE;

		Message::MessageHeader* pMsgHeader = pMsg->GetMessageHeader();
		msgID = pMsgHeader->msgID;
		uiMsgLen = pMsg->GetMessageSize();

		if (pMsgHeader->msgID.IDs.Mobile)
		{
			pMsg->GetMobileMessageHeader()->PeerID = GetLocalInfo().PeerID;
		}

		if( (msgID.IDs.Type != Message::MSGTYPE_NETCONTROL && GetConnectionState() == ConnectionState::DISCONNECTING)
			|| GetConnectionState() == ConnectionState::DISCONNECTED)
		{
			// Send fail by connection closed
			return hr;
		}

		if( !msgID.IDs.Reliability && pMsg->GetMessageSize() > (uint)Const::INTER_PACKET_SIZE_MAX )
		{
			SFLog(Net, Warning, "Too big packet: msg:{0}, seq:{1}, len:{2}",
				msgID,
				msgID.IDSeq.Sequence,
				uiMsgLen);

			netCheck( ResultCode::IO_BADPACKET_TOOBIG );
		}

		Protocol::PrintDebugMessage( "Send", pMsg );

		if (!msgID.IDs.Reliability
			&& m_SendGuaQueue.size() > Const::GUARANT_PENDING_MAX)
		{
			// Drop if there is too many reliable packets are pending
			netCheck(ResultCode::IO_SEND_FAIL);
		}


		if( !msgID.IDs.Reliability )
		{
			pMsg->UpdateChecksumNEncrypt();

			if( !pMsg->GetIsSequenceAssigned() )
				pMsg->AssignSequence( NewSeqNone() );

			SFLog(Net, Debug4, "SEND : msg:{0}, seq:{1}, len:{2}",
				msgID,
				msgID.IDSeq.Sequence,
				uiMsgLen);

			netCheck(SendRaw(pMsg));
		}
		else
		{
			if( pMsg->GetIsSequenceAssigned() )
			{
				netCheck(SendRaw(pMsg));
			}
			else
			{
				SFLog(Net, Debug2, "SENDGuaQueued : CID:{0}, msg:{1}, seq:{2}, len:{3}",
					GetCID(),
					msgID,
					msgID.IDSeq.Sequence,
					uiMsgLen);

				AssertRel(pMsg->GetMessageHeader()->msgID.IDSeq.Sequence == 0);

				if (pMsg->GetMessageSize() > (uint)Const::INTER_PACKET_SIZE_MAX)
				{
					netCheck(SendFrameSequenceMessage(pMsg));
				}
				else
				{
					pMsg->UpdateChecksumNEncrypt();

					netCheck(m_SendGuaQueue.Enqueue(SharedPointerT<Message::MessageData>(pMsg)));
				}

				SetSendBoost(Const::RELIABLE_SEND_BOOST);

				// Poke send if there is any message to send and not too many in the queue
				// Keep poking on bad network situation will make it worse
				if (m_SendReliableWindow.GetMsgCount() <= Const::AGRESSIVE_SEND_COUNT)
				{
					if (GetEventHandler() != nullptr)
						GetEventHandler()->OnNetSyncMessage(this);
					else
						GetNetSyncMessageDelegates().Invoke(this);
				}
			}
		}

		return hr;
	}


	// called when incoming message occur
	Result ConnectionUDPBase::OnRecv(uint uiBuffSize, const uint8_t* pBuff)
	{
		Result hr = ResultCode::SUCCESS;
		SharedPointerT<Message::MessageData> pMsg;
		Message::MobileMessageHeader* pMsgHeader = (Message::MobileMessageHeader*)pBuff;

		SFLog(Net, Debug4, "UDP Recv ip:{0}, msg:{1}, seq:{2}, len:{3}", GetRemoteInfo().PeerAddress, pMsgHeader->msgID, pMsgHeader->msgID.IDSeq.Sequence, uiBuffSize);

		if (uiBuffSize == 0)
		{
			IncZeroRecvCount();

			if (GetZeroRecvCount() > (uint32_t)Const::CONNECTION_ZEROPACKET_MAX)
			{
				Disconnect("Too many zero packet");
			}
			return hr;
		}

		MutexScopeLock scopeLock(GetUpdateLock());

		while (uiBuffSize && GetConnectionState() != ConnectionState::DISCONNECTED)
		{
			pMsgHeader = (Message::MobileMessageHeader*)pBuff;
			if (uiBuffSize < sizeof(Message::MobileMessageHeader) || uiBuffSize < pMsgHeader->Length)
			{
				SFLog(Net, Error, "Unexpected packet buffer size:{0}, size in header:{1}", uiBuffSize, pMsgHeader->Length);
				netErr(ResultCode::IO_BADPACKET_SIZE);
			}

#ifdef UDP_PACKETLOS_EMULATE
			if ((Util::Random.Rand() % UDP_PACKETLOS_RATE) < UDP_PACKETLOS_BOUND)
				goto Proc_End;
#endif	// UDP_PACKETLOS_EMULATE

			ResetZeroRecvCount();

			if (pMsgHeader->msgID.IDs.Type == Message::MSGTYPE_NETCONTROL) // if net control message then process immediately
			{
				netChk(ProcNetCtrl((MsgNetCtrl*)pMsgHeader));
			}
			else
			{
				if (GetConnectionState() == ConnectionState::CONNECTED)
				{
					netMem(pMsg = Message::MessageData::NewMessage(GetHeap(), pMsgHeader->msgID.ID, pMsgHeader->Length, pBuff));

					hr = OnRecv(pMsg);
					netChk(hr);
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


	Result ConnectionUDPBase::OnRecv(SharedPointerT<Message::MessageData>& pMsg)
	{
		ScopeContext hr([this](Result hr)
			{
				if (!hr)
				{
					CloseConnection("OnRecv is failed");
				}
			});
		Message::MessageHeader* pMsgHeader = pMsg->GetMessageHeader();

		if (GetConnectionState() != ConnectionState::CONNECTED)
		{
			return hr;
		}

		netCheck(pMsg->ValidateChecksumNDecrypt());

		if (pMsgHeader->msgID.IDs.Reliability)
		{
			Assert(!pMsgHeader->msgID.IDs.Encrypted);

			SFLog(Net, Debug2, "RECVGua    : CID:{0} msg:{1}, seq:{2}, len:{3}",
				GetCID(),
				pMsg->GetMessageHeader()->msgID,
				pMsg->GetMessageHeader()->msgID.IDSeq.Sequence,
				pMsg->GetMessageHeader()->Length);

			netCheck(OnGuaranteedMessageRecv(pMsg));
		}
		else
		{
			netCheck(super::OnRecv(pMsg));
		}
		pMsg = nullptr;

		return hr;
	}



	
	////////////////////////////////////////////////////////////////////////////////
	//
	//	UDP connection class
	//


	// Update net control, process connection heartbeat, ... etc
	Result ConnectionUDP::TickUpdate()
	{
		ScopeContext hr([this](Result hr) 
			{
				SendFlush();
			});

		netCheck(super::TickUpdate());

		// It is in state action
		//netCheck(UpdateSendQueue());

		return hr;
	}
	

} // namespace Net
} // namespace SF


