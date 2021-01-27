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
	//	, m_RecvGuaQueue(GetHeap(), MessageWindow::MESSAGE_QUEUE_SIZE / 2 )
		, m_pWriteQueuesUDP(nullptr)
	{
		SetHeartbitTry( Const::UDP_HEARTBIT_TIME);

		SetWriteQueueUDP(Service::NetSystem->GetWriteBufferQueue());
		SetUseAddressMap(true);
	}

	ConnectionUDPBase::~ConnectionUDPBase()
	{
		m_RecvReliableWindow.ClearWindow();
		m_SendReliableWindow.ClearWindow();


		if(m_pGatheringBuffer != nullptr)
			IHeap::Free(m_pGatheringBuffer);
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

	//Result ConnectionUDPBase::ProcGuarrentedMessageWindow(const std::function<void(SharedPointerT<Message::MessageData>& pMsgData)>& action)
	//{
	//	Result hr = ResultCode::SUCCESS;
	//	SharedPointerT<Message::MessageData> pIMsg;

	//	// slide recv window
	//	while ((m_RecvReliableWindow.PopMsg(pIMsg)))
	//	{
	//		Assert(pIMsg != nullptr);
	//		Message::MessageHeader *pQMsgHeader = pIMsg->GetMessageHeader();
	//		SFLog(Net, Debug2, "RECVGuaDEQ : CID:{0}:{1}, seq:{2}, msg:{3}, len:%4%",
	//			GetCID(), m_RecvReliableWindow.GetBaseSequence(),
	//			pQMsgHeader->msgID.IDSeq.Sequence,
	//			pQMsgHeader->msgID,
	//			pQMsgHeader->Length);


	//		if (pIMsg->GetMessageHeader()->msgID.GetMsgID() == PACKET_NETCTRL_SEQUENCE_FRAME.GetMsgID())
	//		{
	//			OnFrameSequenceMessage(pIMsg, action);
	//		}
	//		else
	//		{
	//			action(pIMsg);
	//		}
	//		//netChk(Connection::OnRecv(pIMsg));
	//		pIMsg = nullptr;
	//	}

	////Proc_End:

	//	pIMsg = nullptr;

	//	return hr;
	//}

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

		netChkPtr( pMsg );

		if( pMsg->GetMessageSize() > (uint)Const::INTER_PACKET_SIZE_MAX )
		{
			netErr( ResultCode::IO_BADPACKET_TOOBIG );
		}

		if( !(PrepareGatheringBuffer(pMsg->GetMessageSize()) ) )
		{
			return Send(pMsg);
		}

		memcpy( m_pGatheringBuffer+m_uiGatheredSize, pMsg->GetMessageBuff(), pMsg->GetMessageSize() );

		m_uiGatheredSize += pMsg->GetMessageSize();


	Proc_End:

		pMsg = nullptr;

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
			IHeap::Free(m_pGatheringBuffer);

		if (pSendBuffer != nullptr)
			IHeap::Delete(pSendBuffer);

		m_pGatheringBuffer = nullptr;


		return hr;
	}

	// Prepare gathering buffer
	Result ConnectionUDPBase::PrepareGatheringBuffer( uint uiRequiredSize )
	{
		Result hr = ResultCode::SUCCESS;

		// You tryed to use this method in a wrong way
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
	Result ConnectionUDPBase::SendFrameSequenceMessage(SharedPointerT<Message::MessageData>& pMsg)
	{
		Result hr = ResultCode::SUCCESS;
		SharedPointerT<Message::MessageData> pNewMessageData;
		TimeStampMS ulTimeCur = Util::Time.GetTimeMs();
		auto pMsgHeader = pMsg->GetMessageHeader();
		auto remainSize = pMsgHeader->Length;
		unsigned offset = 0;

		SFLog(Net, Debug2, "SEND Spliting : CID:{0}, seq:{1}, msg:{2}, len:{3}",
			GetCID(),
			pMsg->GetMessageHeader()->msgID.IDSeq.Sequence,
			pMsg->GetMessageHeader()->msgID,
			pMsg->GetMessageHeader()->Length);

		for (uint iSequence = 0; remainSize > 0; iSequence++)
		{
			auto frameSize = Util::Min(pMsgHeader->Length, (uint)Message::MAX_SUBFRAME_SIZE);

			MsgMobileNetCtrlSequenceFrame* pCurrentFrame = nullptr;

			netChkPtr(pNewMessageData = Message::MessageData::NewMessage(GetHeap(), PACKET_NETCTRL_SEQUENCE_FRAME, frameSize + (uint)sizeof(MsgMobileNetCtrlSequenceFrame), pMsg->GetMessageBuff() + offset));

			pCurrentFrame = (MsgMobileNetCtrlSequenceFrame*)pNewMessageData->GetMessageBuff();
			pCurrentFrame->SetSubSeqNSize(iSequence, pMsgHeader->Length);

			netChk(m_SendReliableWindow.EnqueueMessage(ulTimeCur, pNewMessageData));
			SendPending(pNewMessageData);
			SFLog(Net, Debug2, "SENDENQReliable : CID:{0}, seq:{1}, msg:{2}, len:{3}",
				GetCID(),
				pNewMessageData->GetMessageHeader()->msgID.IDSeq.Sequence,
				pNewMessageData->GetMessageHeader()->msgID,
				pNewMessageData->GetMessageHeader()->Length);

			pNewMessageData = nullptr;

			remainSize -= frameSize;
			offset += frameSize;
		}

		pMsg = nullptr;

	Proc_End:

		pNewMessageData = nullptr;

		return hr;
	}

	Result ConnectionUDPBase::OnFrameSequenceMessage(SharedPointerT<Message::MessageData>& pMsg, const std::function<void(SharedPointerT<Message::MessageData>& pMsgData)>& action)
	{
		Result hr = ResultCode::SUCCESS;
		Message::MessageData* pFrameMessage = nullptr;
		if (pMsg == nullptr)
			return ResultCode::INVALID_POINTER;

		Message::MessageHeader* pMsgHeader = pMsg->GetMessageHeader();

		auto* pFrame = (MsgMobileNetCtrlSequenceFrame*)pMsgHeader;
		uint subFrameSequence = pFrame->SubSequence;
		uint frameSize = pFrame->Length - (uint)sizeof(MsgMobileNetCtrlSequenceFrame);
		uint totalSize = pFrame->TotalSize;
		auto* dataPtr = (const uint8_t*)(pFrame + 1);
		uint offset = subFrameSequence * Message::MAX_SUBFRAME_SIZE;

		Assert(frameSize <= Message::MAX_SUBFRAME_SIZE);
		if (frameSize > Message::MAX_SUBFRAME_SIZE)
		{
			netErr(ResultCode::IO_BADPACKET_NOTEXPECTED);
		}

		if (subFrameSequence == 0) // first frame
		{
			//Assert(m_SubFrameMessage == nullptr);
			m_SubFrameMessage = nullptr;

			uint dummyID = PACKET_NETCTRL_SEQUENCE_FRAME;
			netChkPtr(pFrameMessage = Message::MessageData::NewMessage(GetHeap(), dummyID, totalSize));
			memcpy(pFrameMessage->GetMessageHeader(), dataPtr, frameSize);
			if (pFrameMessage->GetMessageHeader()->Length != totalSize)
			{
				Assert(false);
				netErr(ResultCode::IO_BADPACKET_NOTEXPECTED);
			}

			m_SubFrameMessage = std::forward<SharedPointerT<Message::MessageData>>(pFrameMessage);
			pFrameMessage = nullptr;
		}
		else
		{
			if (m_SubFrameMessage == nullptr)
			{
				Assert(m_SubFrameMessage != nullptr);
				netErr(ResultCode::IO_BADPACKET_NOTEXPECTED);
			}

			uint8_t* pDest = m_SubFrameMessage->GetMessageBuff() + offset;

			if (m_SubFrameMessage->GetMessageHeader()->Length != totalSize)
			{
				Assert(false);
				netErr(ResultCode::IO_BADPACKET_NOTEXPECTED);
			}

			if ((offset + frameSize) > totalSize)
			{
				Assert(false);
				netErr(ResultCode::IO_BADPACKET_NOTEXPECTED);
			}

			memcpy(pDest, dataPtr, frameSize);
		}

		if (m_SubFrameMessage != nullptr && (offset + frameSize) == totalSize)
		{
			netChk(m_SubFrameMessage->ValidateChecksumNDecrypt());
			action(m_SubFrameMessage);
			m_SubFrameMessage = nullptr;
			netChk(hr);
		}

	Proc_End:


		

		return hr;
	}

	// Initialize connection
	Result ConnectionUDPBase::InitConnection(const PeerInfo &local, const PeerInfo &remote)
	{
		Result hr = ResultCode::SUCCESS;

		m_uiGatheredSize = 0;

		//m_RecvGuaQueue.ClearQueue();

		netChk(Connection::InitConnection( local, remote ) );

		netChk( ClearQueues() );

		m_SubFrameMessage = nullptr;

	Proc_End:

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

	Result ConnectionUDPBase::SendRaw(SharedPointerT<Message::MessageData> &pMsg)
	{
		Result hr = ResultCode::SUCCESS;
		IOBUFFER_WRITE *pSendBuffer = nullptr;
		auto pIOHandler = GetNetIOHandler();
		if (pIOHandler == nullptr || !pIOHandler->GetIsIORegistered())
			return ResultCode::SUCCESS_FALSE;

		pIOHandler->IncPendingSendCount();

		netChkPtr(pMsg);

		if (pMsg->GetDataLength() != 0 && pMsg->GetMessageHeader()->Crc32 == 0 && pMsg->GetMessageHeader()->msgID.IDs.Policy != PROTOCOLID_NONE)
		{
			Assert(pMsg->GetDataLength() == 0 || pMsg->GetMessageHeader()->Crc32 != 0 || pMsg->GetMessageHeader()->msgID.IDs.Policy == PROTOCOLID_NONE);
			hr = ResultCode::FAIL;
			goto Proc_End;
		}

		netMem(pSendBuffer = new(GetIOHeap()) IOBUFFER_WRITE);

		pSendBuffer->SetupSendUDP(GetSocket(), GetRemoteSockAddr(), std::forward<SharedPointerT<Message::MessageData>>(pMsg));

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


		pMsg = nullptr;
		pSendBuffer = nullptr;

	Proc_End:

		IHeap::Free(pSendBuffer);

		if(!hr && pIOHandler != nullptr)
			pIOHandler->DecPendingSendCount();


		return hr;
	}

	// Send message to connected entity
	Result ConnectionUDPBase::Send(SharedPointerT<Message::MessageData> &pMsg )
	{
		Result hr = ResultCode::SUCCESS;
		Message::MessageID msgID;
		uint uiMsgLen;

		if (GetConnectionState() == ConnectionState::DISCONNECTED)
			return ResultCode::SUCCESS_FALSE;

		Message::MessageHeader* pMsgHeader = pMsg->GetMessageHeader();
		msgID = pMsgHeader->msgID;
		uiMsgLen = pMsg->GetMessageHeader()->Length;

		if (pMsgHeader->msgID.IDs.Mobile)
		{
			pMsg->GetMobileMessageHeader()->PeerID = GetLocalInfo().PeerID;
		}

		if( (msgID.IDs.Type != Message::MSGTYPE_NETCONTROL && GetConnectionState() == ConnectionState::DISCONNECTING)
			|| GetConnectionState() == ConnectionState::DISCONNECTED)
		{
			// Send fail by connection closed
			pMsg = nullptr;
			goto Proc_End;
		}

		if( pMsg->GetMessageSize() > (uint)Const::INTER_PACKET_SIZE_MAX )
		{
			pMsg = nullptr;
			netErr( ResultCode::IO_BADPACKET_TOOBIG );
		}

		Protocol::PrintDebugMessage( "Send", pMsg );

		if (!msgID.IDs.Reliability
			&& m_SendGuaQueue.size() > Const::GUARANT_PENDING_MAX)
		{
			// Drop if there is too many reliable packets are pending
			netErr(ResultCode::IO_SEND_FAIL);
		}

		pMsg->UpdateChecksumNEncrypt();


		if( !msgID.IDs.Reliability )
		{
			if( !pMsg->GetIsSequenceAssigned() )
				pMsg->AssignSequence( NewSeqNone() );

			SFLog(Net, Debug1, "SEND : msg:{0}, seq:{1}, len:{2}",
				msgID,
				msgID.IDSeq.Sequence,
				uiMsgLen);

			netChk(SendRaw(pMsg));
		}
		else
		{
			if( pMsg->GetIsSequenceAssigned() )
			{
				netChk(SendRaw(pMsg));
			}
			else
			{
				SFLog(Net, Debug2, "SENDGuaQueued : CID:{0}, msg:{1}, seq:{2}, len:{3}",
					GetCID(),
					msgID,
					msgID.IDSeq.Sequence,
					uiMsgLen);

				AssertRel(pMsg->GetMessageHeader()->msgID.IDSeq.Sequence == 0);

				netChk( m_SendGuaQueue.Enqueue( std::forward<SharedPointerT<Message::MessageData>>(pMsg) ) );

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
		pMsg = nullptr;

	Proc_End:

		if (!(hr))
		{
			pMsg = nullptr;
		}
		else
		{
			if (msgID.IDs.Type == Message::MSGTYPE_NETCONTROL)
			{
				SFLog(Net, Debug1, "TCP Ctrl CID:{2}, ip:{0}, msg:{1}", GetRemoteInfo().PeerAddress, msgID, GetCID());
			}
			else
			{
				SFLog(Net, Debug3, "TCP Send CID:{2}, ip:{0}, msg:{1}", GetRemoteInfo().PeerAddress, msgID, GetCID());
			}
		}

		return hr;
	}




	
	////////////////////////////////////////////////////////////////////////////////
	//
	//	UDP connection class
	//

	// called when incoming message occure
	Result ConnectionUDP::OnRecv( uint uiBuffSize, const uint8_t* pBuff )
	{
		Result hr = ResultCode::SUCCESS;
		SharedPointerT<Message::MessageData> pMsg;

		Message::MessageHeader * pMsgHeader = (Message::MessageHeader*)pBuff;

		SFLog(Net, Debug3, "UDP Recv ip:{0}, msg:{1}, seq:{2}, len:{3}", GetRemoteInfo().PeerAddress, pMsgHeader->msgID, pMsgHeader->msgID.IDSeq.Sequence, uiBuffSize);

		if( uiBuffSize == 0 )
		{
			IncZeroRecvCount();

			if( GetZeroRecvCount() > (uint32_t)Const::CONNECTION_ZEROPACKET_MAX )
			{
				Disconnect("Too many zero packets");
			}
			goto Proc_End;
		}


		while( uiBuffSize )
		{
			pMsgHeader = (Message::MessageHeader*)pBuff;

			if( uiBuffSize < pMsgHeader->Length )
			{
				//Assert(0); // Will not occure with UDP packet
				netErr( ResultCode::IO_BADPACKET_SIZE );
			}


#ifdef UDP_PACKETLOS_EMULATE
			if( (Util::Random.Rand() % UDP_PACKETLOS_RATE) < UDP_PACKETLOS_BOUND )
				goto Proc_End;
#endif	// UDP_PACKETLOS_EMULATE

			ResetZeroRecvCount();

			// if net control message then process immediately except reliable messages
			if (pMsgHeader->msgID.IDs.Type == Message::MSGTYPE_NETCONTROL && pMsgHeader->msgID.IDs.Reliability == false) 
			{
				netChk(ProcNetCtrl((MsgNetCtrl*)pMsgHeader));
			}
			else
			{
				if (GetConnectionState() == Net::ConnectionState::CONNECTED)
				{
					netMem( pMsg = Message::MessageData::NewMessage(GetHeap(), pMsgHeader->msgID.ID, pMsgHeader->Length, pBuff ) );

					hr = OnRecv( pMsg );
					pMsg = nullptr;
					netChk( hr );
				}
			}


			uiBuffSize -= pMsgHeader->Length;
			pBuff += pMsgHeader->Length;

			pMsg = nullptr;
		}

	Proc_End:

		pMsg = nullptr;

		return hr;
	}


	Result ConnectionUDP::OnRecv(SharedPointerT<Message::MessageData>& pMsg )
	{
		Result hr = ResultCode::SUCCESS;
		uint length = 0;
		uint8_t* pDataPtr = nullptr;

		Message::MessageHeader* pMsgHeader = pMsg->GetMessageHeader();

		if (GetConnectionState() != Net::ConnectionState::CONNECTED)
		{
			goto Proc_End;
		}


		pMsg->GetLengthNDataPtr( length, pDataPtr );
		Assert(length == 0 || pMsgHeader->Crc32 != 0 );

		netChk( pMsg->ValidateChecksumNDecrypt() );

		if( pMsgHeader->msgID.IDs.Reliability )
		{
			Assert( !pMsgHeader->msgID.IDs.Encrypted );

			// This message need to be merged before adding recv queue
			if (pMsgHeader->msgID.GetMsgID() == PACKET_NETCTRL_SEQUENCE_FRAME.GetMsgID())
			{
				hr = OnFrameSequenceMessage(pMsg, [&](SharedPointerT<Message::MessageData>& pMsgData) { hr = m_RecvReliableWindow.AddMsg(pMsgData); });
			}
			else
			{
				hr = m_RecvReliableWindow.AddMsg(pMsg);
			}

			pMsg = nullptr;
			netChk(hr);

			SharedPointerT<Message::MessageData> pPopMsg;
			while (m_RecvReliableWindow.PopMsg(pPopMsg))
			{
				hr = ConnectionUDPBase::OnRecv(pPopMsg);
			}
		}
		else
		{
			hr = ConnectionUDPBase::OnRecv( pMsg );
			pMsg = nullptr;
			netChk( hr );
		}


	Proc_End:

		pMsg = nullptr;

		if( !( hr ) )
		{
			CloseConnection("OnRecv failed");
		}

		return hr;
	}


	// Process network control message
	Result ConnectionUDP::ProcNetCtrl( const MsgNetCtrl* pNetCtrl )
	{
		Result hr = ResultCode::SUCCESS;
		Result hrTem = ResultCode::SUCCESS;

		switch( pNetCtrl->msgID.IDs.MsgCode )
		{
		case NetCtrlCode_Ack:
			if( pNetCtrl->rtnMsgID.IDs.Type == Message::MSGTYPE_NETCONTROL )// connecting process
			{
				switch( pNetCtrl->rtnMsgID.IDs.MsgCode )
				{
				case NetCtrlCode_Disconnect:
					if (GetConnectionState() == ConnectionState::DISCONNECTING || GetConnectionState() == ConnectionState::CONNECTED)
					{
						SFLog(Net, Info, "RECV Disconnected CID:{0}", GetCID() );
						netChk( CloseConnection("Disconnect ack") );
					}
					break;
				case NetCtrlCode_Connect:
					if (GetConnectionState() == ConnectionState::CONNECTING
						&& GetRemoteInfo().PeerClass != NetClass::Unknown )
					{
						OnConnectionResult( ResultCode::SUCCESS );
					}
					break;
				case NetCtrlCode_HeartBit:
					m_ulNetCtrlTime = Util::Time.GetTimeMs();
					break;
				default:
					m_ulNetCtrlTime = Util::Time.GetTimeMs();
					break;
				};
			}
			else // general message
			{
				// Remove from Guranted queue
				if( pNetCtrl->rtnMsgID.IDs.Reliability )
				{
					hrTem = m_SendReliableWindow.ReleaseSingleMessage(pNetCtrl->msgID.IDSeq.Sequence);
					SFLog(Net, Debug1, "NetCtrl Recv GuaAck : CID:{0}:{1}, seq:{2}, rtnmsg:{3}, hr={4:X8}",
						GetCID(), m_SendReliableWindow.GetBaseSequence(), pNetCtrl->msgID.IDSeq.Sequence, pNetCtrl->rtnMsgID, hrTem);
					netChk( hrTem );
				}
			}
			break;
		case NetCtrlCode_Nack:
			if( pNetCtrl->rtnMsgID.IDs.Type == Message::MSGTYPE_NETCONTROL )// connecting process
			{
				switch( pNetCtrl->rtnMsgID.IDs.MsgCode )
				{
				case NetCtrlCode_Disconnect:
					break;
				case NetCtrlCode_Connect:
					if (GetConnectionState() == ConnectionState::CONNECTING || GetConnectionState() == ConnectionState::CONNECTED)
					{
						// Protocol version mismatch
						OnConnectionResult( ResultCode::IO_PROTOCOL_VERSION_MISMATCH );
					}
					netChk( Disconnect("Protocol mismatch") );
					break;
				case NetCtrlCode_HeartBit:
					break;
				default:
					break;
				};
			}
			else // general message
			{
			}
			break;
		case NetCtrlCode_HeartBit:
			m_ulNetCtrlTime = Util::Time.GetTimeMs();
			netChk(SendPending(PACKET_NETCTRL_ACK, pNetCtrl->msgID.IDSeq.Sequence, pNetCtrl->msgID));
			break;
		case NetCtrlCode_Connect:
		{
			if( pNetCtrl->Length < sizeof(MsgNetCtrlConnect) )
			{
				SFLog(Net, Warning, "HackWarn : Invalid packet CID:{0}, Addr {1}", GetCID(), GetRemoteInfo().PeerAddress );
				netChk( Disconnect("Invalid packet") );
				netErr( ResultCode::UNEXPECTED );
			}
			const MsgNetCtrlConnect *pNetCtrlCon = (const MsgNetCtrlConnect*)pNetCtrl;
			uint ProtocolVersion = pNetCtrl->rtnMsgID.ID;
			switch (GetConnectionState())
			{
			case  ConnectionState::CONNECTING:
				if( pNetCtrl->rtnMsgID.ID != SF_PROTOCOL_VERSION )
				{
					netChk(SendNetCtrl(PACKET_NETCTRL_NACK, pNetCtrl->msgID.IDSeq.Sequence, pNetCtrl->msgID));
					OnConnectionResult( ResultCode::IO_PROTOCOL_VERSION_MISMATCH );
					netChk( Disconnect("Protocol mismatch") );
					break;
				}
				else if( GetRemoteInfo().PeerClass != NetClass::Unknown && pNetCtrlCon->Peer.PeerClass != GetRemoteInfo().PeerClass )
				{
					netChk(SendNetCtrl(PACKET_NETCTRL_NACK, pNetCtrl->msgID.IDSeq.Sequence, pNetCtrl->msgID));
					OnConnectionResult( ResultCode::IO_INVALID_NETCLASS );
					netChk( Disconnect("Invalid netclass") );
					break;
				}

				SFLog(Net, Debug2, "UDP Recv Connecting CID({0}) : C:{1}, Ver:{2})", GetCID(), pNetCtrlCon->Peer.PeerClass, ProtocolVersion );
				SetRemoteInfo(pNetCtrlCon->Peer.PeerClass, pNetCtrlCon->Peer.PeerID );

			case ConnectionState::CONNECTED:
				m_ulNetCtrlTime = Util::Time.GetTimeMs();
				netChk(SendNetCtrl(PACKET_NETCTRL_ACK, pNetCtrl->msgID.IDSeq.Sequence, pNetCtrl->msgID));
				break;
			default:
				break;
			};

			break;
		}
		case NetCtrlCode_ConnectPeer:
		{
			break;
		}
		case NetCtrlCode_Disconnect:
			SendFlush();
			netChk(SendNetCtrl(PACKET_NETCTRL_ACK, pNetCtrl->msgID.IDSeq.Sequence, pNetCtrl->msgID));
			netChk(SendNetCtrl(PACKET_NETCTRL_ACK, pNetCtrl->msgID.IDSeq.Sequence, pNetCtrl->msgID));
			SendFlush();
			SFLog(Net, Info, "Disconnect from remote CID:{0}", GetCID() );
			netChk( CloseConnection("Received disconnect") );
			break;
		default:
			//Assert( 0 );
			SFLog(Net, Warning, "HackWarn : Invalid packet CID:{0}, Addr {1}", GetCID(), GetRemoteInfo().PeerAddress );
			netChk( CloseConnection("Invalid packet") );
			netErr( ResultCode::UNEXPECTED );
			break;
		};


	Proc_End:

		return hr;
	}


	// Process Send queue
	Result ConnectionUDP::ProcSendReliableQueue()
	{
		Result hr = ResultCode::SUCCESS;
		SharedPointerT<Message::MessageData> pIMsg;
		Message::MessageHeader *pMsgHeader = nullptr;
		TimeStampMS ulTimeCur = Util::Time.GetTimeMs();
		uint halfWindowSize = m_SendReliableWindow.GetAcceptableSequenceRange() >> 1;
		Assert(halfWindowSize >= 16);

		// Send guaranteed message process
		auto availableWindow = m_SendReliableWindow.GetAvailableSize();
		auto uiNumPacket = m_SendGuaQueue.size();
		CounterType availablePush = Util::Min(availableWindow, halfWindowSize);
		auto NumProc = Util::Min(availablePush, uiNumPacket);
		for( CounterType uiPacket = 0; uiPacket < NumProc; uiPacket++ )
		{
			if( !(m_SendGuaQueue.Dequeue( pIMsg )) )
				break;

			if (pMsgHeader->msgID.IDs.Reliability)
			{
				pMsgHeader = pIMsg->GetMessageHeader();
				if (pMsgHeader->Length > Message::MAX_SUBFRAME_SIZE)
				{
					netChk(SendFrameSequenceMessage(pIMsg));
				}
				else
				{
					if ((m_SendReliableWindow.EnqueueMessage(ulTimeCur, pIMsg)))
					{
						Assert(pIMsg->GetDataLength() == 0 || pIMsg->GetMessageHeader()->Crc32 != 0);
						SendPending(pIMsg);
						Assert(pIMsg->GetDataLength() == 0 || pIMsg->GetMessageHeader()->Crc32 != 0);
						SFLog(Net, Debug2, "SENDENQReliable : CID:{0}, seq:{1}, msg:{2}, len:{3}",
							GetCID(),
							pIMsg->GetMessageHeader()->msgID.IDSeq.Sequence,
							pIMsg->GetMessageHeader()->msgID,
							pIMsg->GetMessageHeader()->Length);
					}
				}
				pIMsg = nullptr;
			}
			else
			{
				Assert(false);
			}
		}


	Proc_End:

		pIMsg = nullptr;

		return hr;
	}
		
	// Process message window queue
	Result ConnectionUDP::ProcReliableSendRetry()
	{
		Result hr = ResultCode::SUCCESS;
		SendMsgWindow::MessageData *pMessageElement = nullptr;
		TimeStampMS ulTimeCur = Util::Time.GetTimeMs();

		// Guaranteed retry
		// TODO: limit with total data size than count
		uint uiMaxProcess = Util::Min( m_SendReliableWindow.GetMsgCount(), m_uiMaxGuarantedRetryAtOnce );
		for( uint uiIdx = 0, uiMsgProcessed = 0; uiIdx < (uint)m_SendReliableWindow.GetAcceptableSequenceRange() && uiMsgProcessed < uiMaxProcess; uiIdx++ )
		{
			if( (m_SendReliableWindow.GetAt( uiIdx, pMessageElement ))
				&& pMessageElement && pMessageElement->pMsg != nullptr)
			{
				if( (ulTimeCur-pMessageElement->ulTimeStamp) > DurationMS(Const::SEND_RETRY_TIME) )
				{
					SFLog(Net, Debug2, "SENDGuaRetry : CID:{0}, seq:{1}, msg:{2}, len:{3}",
									GetCID(),
									pMessageElement->pMsg->GetMessageHeader()->msgID.IDSeq.Sequence,
									pMessageElement->pMsg->GetMessageHeader()->msgID, 
									pMessageElement->pMsg->GetMessageHeader()->Length );
					pMessageElement->ulTimeStamp = ulTimeCur;
					// Creating new reference object will increase reference count of the message instance.
					// And more importantly, SendPending is taking reference of the variable and clear it when it done sending
					auto tempMsg = pMessageElement->pMsg;
					SendPending(tempMsg);
				}
			}
			pMessageElement = nullptr;
		}


	//Proc_End:

		if (pMessageElement != nullptr) pMessageElement->Clear();

		return hr;
	}

	

	// Update net control, process connection heartbit, ... etc
	Result ConnectionUDP::TickUpdate()
	{
		Result hr = ResultCode::SUCCESS;
		Message::MessageID msgIDTem;

		if (GetConnectionState() == Net::ConnectionState::DISCONNECTED)
			goto Proc_End;

		hr = ProcConnectionStateAction();
		if( !(hr) )
		{
			SFLog(Net, Info, "Process Connection state failed {0:X8}", hr );
		}

/*
		hr = ProcRecvReliableQueue();
		if( !(hr) )
		{
			SFLog(Net, Info, "Process Recv Guaranted queue failed {0:X8}", hr );
		}
*/
		hr = ProcSendReliableQueue();
		if( !(hr) )
		{
			SFLog(Net, Info, "Process Send Guaranted queue failed {0:X8}", hr );
		}

		hr = ProcReliableSendRetry();
		if( !(hr) )
		{
			SFLog(Net, Info, "Process message window failed {0:X8}", hr );
		}


	Proc_End:

		//SendFlush();

		return hr;
	}



	

} // namespace Net
} // namespace SF


