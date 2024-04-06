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
#include "SFProtocol.h"

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
		, m_SendReliableWindow(GetHeap())
		, m_uiMaxGuarantedRetryAtOnce(Const::UDP_SVR_RETRY_ONETIME_MAX)
        , m_SendGuaQueue(GetHeap())
	{
		SetUseAddressMap(true);

		SetNetCtrlAction(NetCtrlCode_Ack, &m_HandleAck);
		SetNetCtrlAction(NetCtrlCode_Nack, &m_HandleNack);
		SetNetCtrlAction(NetCtrlCode_Heartbeat, &m_HandleHeartbeat);
		SetNetCtrlAction(NetCtrlCode_TimeSync, &m_HandleTimeSync);
		SetNetCtrlAction(NetCtrlCode_Connect, &m_HandleConnect);
		SetNetCtrlAction(NetCtrlCode_Disconnect, &m_HandleDisconnect);

        AddStateAction(ConnectionState::CONNECTING, &m_ActFlushNet);
        AddStateAction(ConnectionState::DISCONNECTING, &m_ActFlushNet);
		AddStateAction(ConnectionState::CONNECTED, &m_ActSendReliableQueue);
		AddStateAction(ConnectionState::CONNECTED, &m_ActSendReliableRetry);
        AddStateAction(ConnectionState::CONNECTED, &m_ActFlushNet);
    }

	ConnectionUDPBase::~ConnectionUDPBase()
	{
		m_RecvReliableWindow.Reset();
		m_SendReliableWindow.ClearWindow();
        m_SendGuaQueue.Reset();

        ClearReceivedSubframeStates();
	}

    void ConnectionUDPBase::Dispose()
    {
        super::Dispose();

        m_RecvReliableWindow.Reset();
        m_SendReliableWindow.ClearWindow();
        m_SendGuaQueue.Reset();

        ClearReceivedSubframeStates();
    }

    void ConnectionUDPBase::ClearReceivedSubframeStates()
    {
        for (SubframeRecvState* pSubframeState : m_ReceivedSubframeStates)
        {
            GetSystemHeap().Free(pSubframeState);
        }
        m_ReceivedSubframeStates.Reset();

    }

    // Make Ack packet and enqueue to SendNetCtrlqueue
    Result ConnectionUDPBase::SendNetCtrl(uint uiCtrlCode, uint uiSequence, MessageID returnMsgID, uint64_t parameter0)
    {
        return SendPending(uiCtrlCode, uiSequence, returnMsgID, parameter0);
    }

	// gathering
	Result ConnectionUDPBase::SendPending( uint uiCtrlCode, uint uiSequence, MessageID returnMsgID, uint64_t parameter0)
	{
		Result hr;

        MsgNetCtrlBuffer netCtrlBuffer{};
        netCheck(MakeNetCtrl(&netCtrlBuffer.Header, uiCtrlCode, uiSequence, returnMsgID, parameter0));

        netCheck(SendRaw(&netCtrlBuffer.Header));

        return hr;
	}


	Result ConnectionUDPBase::SendFlush()
	{
        Result hr;
        MutexScopeLock scopeLock(m_GatheringBufferLock);

        while (true)
        {
            // use nolock version because we already have m_GatheringBufferLock
            CircularBufferQueue::ItemReadPtr itemReadPtr = m_GatheringBufferQueue.DequeueReadNoLock();
            if (!itemReadPtr)
                break;

            MessageHeader* pMsgHeader = reinterpret_cast<MessageHeader*>(itemReadPtr.data());

            netCheck(PrepareGatheringBuffer(pMsgHeader->MessageSize));

            netCheckMem(m_GatheringBuffer->AddMessage(pMsgHeader));

            itemReadPtr.Reset();
        }

        SendFlushGatheringBufferInternal();

		return hr;
	}

    Result ConnectionUDPBase::SendFlushGatheringBufferInternal()
    {
        Net::SocketIO* pIOHandler = GetNetIOHandler();
        ScopeContext hr([this, &pIOHandler](Result hr)
            {
                if (!hr.IsSuccess() && pIOHandler != nullptr)
                    pIOHandler->DecPendingSendCount();
            });

        if (m_GatheringBuffer == nullptr)
            return hr;

        if (pIOHandler != nullptr)
        {
            if (pIOHandler->GetIsIORegistered() && GetConnectionState() != ConnectionState::DISCONNECTED
                && m_GatheringBuffer->Payload.size() > m_uiMinGatherSizeForFlush)
            {
                SFUniquePtr<PacketData> pSendBuffer(m_GatheringBuffer.release());

                pIOHandler->IncPendingSendCount();

                pSendBuffer->SetupSendUDP(GetSocket(), GetRemoteSockAddr(),
                    (uint)pSendBuffer->Payload.size(), pSendBuffer->Payload.data());

                netCheckPtr(GetNetIOHandler());

                // Ignore send failure, we can drop them, and reliability logic will kicked in
                Result sendRes = GetNetIOHandler()->WriteBuffer(pSendBuffer.get());
                if (sendRes)
                {
                    pSendBuffer.release();
                }
                else
                {
                    SFLog(Net, Warning, "UDP send failure hr:{0}, to:{1}, size:{2}", sendRes, GetRemoteInfo().PeerAddress, pSendBuffer->SendBufferSize);
                    pSendBuffer.reset();
                }
            }

        }

        return hr;
    }

    Result ConnectionUDPBase::AllocSendGatherBuffer()
    {
        assert(m_GatheringBuffer == nullptr);
        m_GatheringBuffer.reset(PacketData::NewPacketData());

        if (m_bIncludePacketHeader)
        {
            m_GatheringBuffer->AddPacketHeader(GetLocalInfo().PeerID);
        }

        return ResultCode::SUCCESS;
    }

	// Prepare gathering buffer
	Result ConnectionUDPBase::PrepareGatheringBuffer(uint uiRequiredSize)
	{
		Result hr = ResultCode::SUCCESS;

		// You tried to use this method in a wrong way
		if( uiRequiredSize > Const::PACKET_GATHER_SIZE_MAX )
		{
			return ResultCode::FAIL;
		}

		//AssertRel(GetRunningThreadID() == ThisThread::GetThreadID());

        if (m_GatheringBuffer == nullptr)
        {
            netCheck(AllocSendGatherBuffer());
        }

        if (!m_GatheringBuffer->CanAdd(uiRequiredSize))
        {
            SendFlushGatheringBufferInternal();
            if (m_GatheringBuffer == nullptr) // we have exception case not flushing out
            {
                netCheck(AllocSendGatherBuffer());
            }
        }

        assert(m_GatheringBuffer && m_GatheringBuffer->CanAdd(uiRequiredSize));

        return hr;
	}

	// frame sequence
	Result ConnectionUDPBase::SendFrameSequenceMessage(const MessageHeader* pSrcMsgHeader)
	{
		Result hr = ResultCode::SUCCESS;
		TimeStampMS ulTimeCur = Util::Time.GetTimeMs();
		uint32_t remainSize = pSrcMsgHeader->MessageSize;
		unsigned offset = 0;

		SFLog(Net, Debug2, "SEND Spliting : CID:{0}, msg:{1}, len:{2}",
			GetCID(),
			pSrcMsgHeader->MessageId,
			pSrcMsgHeader->MessageSize);

        uint16_t subFrameSerial = uint16_t(++m_SubframePacketSerial);
		const uint8_t* pCurSrc = reinterpret_cast<const uint8_t*>(pSrcMsgHeader);
		for (uint iSequence = 0; remainSize > 0; iSequence++)
		{
			uint frameSize = Math::Min(remainSize, (uint)MAX_SUBFRAME_SIZE);

			MsgNetCtrlSequenceFrame* pCurrentFrame = nullptr;
			SharedPointerT<MessageData> pSubframeMessage;

			netCheckPtr(pSubframeMessage = MessageData::NewMessage(GetHeap(), PACKET_NETCTRL_SEQUENCE_FRAME, uint(sizeof(MessageHeader) + sizeof(MsgNetCtrlSequenceFrame) + frameSize)));

			// fill up frame header
			pCurrentFrame = (MsgNetCtrlSequenceFrame*)pSubframeMessage->GetPayloadPtr();
            pCurrentFrame->SubframeId = subFrameSerial;
			pCurrentFrame->Offset = uint16_t(offset);
			pCurrentFrame->ChunkSize = uint16_t(frameSize);
			pCurrentFrame->TotalSize = uint16_t(pSrcMsgHeader->MessageSize);

			// copy frame size
			memcpy(pCurrentFrame + 1, pCurSrc, frameSize);

			SFLog(Net, Debug3, "Send subframe: CID:{0}, seq:{1}, msg:{2}, len:{3}",
				GetCID(),
				pSubframeMessage->GetMessageHeader()->GetSequence(),
				pSubframeMessage->GetMessageHeader()->GetMessageID(),
				pSubframeMessage->GetMessageHeader()->MessageSize);

            if (iSequence == 0)
            {
                ((MessageHeader*)(pCurrentFrame + 1))->SetSequence(0);
            }

			pSubframeMessage->UpdateChecksumNEncrypt();

			netCheck(m_SendGuaQueue.Enqueue(pSubframeMessage));

			remainSize -= frameSize;
			offset += frameSize;
			pCurSrc += frameSize;
		}

		return hr;
	}

	Result ConnectionUDPBase::OnFrameSequenceMessage(const MessageHeader* pMsg)
	{
		Result hr = ResultCode::SUCCESS;
		if (pMsg == nullptr)
			return ResultCode::INVALID_POINTER;

        MsgNetCtrlSequenceFrame* pCurrentFrame = reinterpret_cast<MsgNetCtrlSequenceFrame*>(pMsg->GetPayloadPtr());

		const uint8_t* dataPtr = reinterpret_cast<const uint8_t*>(pCurrentFrame + 1);

		if (pCurrentFrame->ChunkSize > MAX_SUBFRAME_SIZE)
		{
			netCheck(ResultCode::IO_BADPACKET_NOTEXPECTED);
		}

        // Since OnFrameSequenceMessage is called directly from network recv thread we need to lock them
        MutexScopeLock scopeLock(m_SubframeLock);

        uint totalBlockCount = (pCurrentFrame->TotalSize + MAX_SUBFRAME_SIZE - 1) / MAX_SUBFRAME_SIZE;
        uint blockIndex = pCurrentFrame->Offset / MAX_SUBFRAME_SIZE;

        SFLog(Net, Log, "OnFrameSequenceMessage: MsgSeq:{0}, MainSeq:{1}, ChunkSize:{2}, Offset:{3}, TotalSize:{4}, block:{5}/{6}",
            pMsg->GetSequence(), pCurrentFrame->SubframeId, pCurrentFrame->ChunkSize, pCurrentFrame->Offset, pCurrentFrame->TotalSize, blockIndex, totalBlockCount);

        // Mostly the array size should be 0 or 1, rarely 2
        SubframeRecvState* pCurSubframeState{};
        for (SubframeRecvState* pSubframeState : m_ReceivedSubframeStates)
        {
            if (pSubframeState->SubframeId == pCurrentFrame->SubframeId)
            {
                pCurSubframeState = pSubframeState;
                break;
            }
        }

        if (pCurSubframeState == nullptr)
        {
            pCurSubframeState = reinterpret_cast<SubframeRecvState*>(GetSystemHeap().Alloc(sizeof(SubframeRecvState) + pCurrentFrame->TotalSize));
            pCurSubframeState->SubframeId = pCurrentFrame->SubframeId;
            pCurSubframeState->TotalSize = pCurrentFrame->TotalSize;
            pCurSubframeState->ReceivedBlockMask = 0;
            pCurSubframeState->FullyReceivedBlockMask = (1 << totalBlockCount) - 1;

            // reset header section
            memset(pCurSubframeState->GetMessageHeader(), 0, sizeof(MessageHeader));
            m_ReceivedSubframeStates.push_back(pCurSubframeState);
        }

        MessageHeader* messageHeader = pCurSubframeState->GetMessageHeader();

		if (messageHeader->MessageSize != 0 && messageHeader->MessageSize != pCurrentFrame->TotalSize)
		{
			netCheck(ResultCode::IO_BADPACKET_NOTEXPECTED);
		}

		memcpy(reinterpret_cast<uint8_t*>(messageHeader) + pCurrentFrame->Offset, dataPtr, pCurrentFrame->ChunkSize);

        if (blockIndex >= (sizeof(SubframeRecvState::ReceivedBlockMask) * 8))
        {
            SFLog(Net, Error, "OnFrameSequenceMessage: MsgSeq:{0}, MainSeq:{1}, ChunkSize:{2}, Offset:{3}, TotalSize:{4}, Too big blockIndex:{5}",
                pMsg->GetSequence(), pCurrentFrame->SubframeId, pCurrentFrame->ChunkSize, pCurrentFrame->Offset, pCurrentFrame->TotalSize, blockIndex);

            netCheck(ResultCode::IO_BADPACKET_NOTEXPECTED);
        }

        pCurSubframeState->ReceivedBlockMask |= (1 << blockIndex);

        if ((pCurSubframeState->ReceivedBlockMask & pCurSubframeState->FullyReceivedBlockMask) == pCurSubframeState->FullyReceivedBlockMask)
        {
            SFLog(Net, Log, "OnFrameSequenceMessage: MsgSeq:{0}, MainSeq:{1}, ChunkSize:{2}, Offset:{3}, TotalSize:{4}, blockIndex:{5}/{6} finished",
                pMsg->GetSequence(), pCurrentFrame->SubframeId, pCurrentFrame->ChunkSize, pCurrentFrame->Offset, pCurrentFrame->TotalSize, blockIndex, totalBlockCount);

            // done
            super::OnRecv(messageHeader);

            m_ReceivedSubframeStates.RemoveItem(pCurSubframeState);
            GetSystemHeap().Free(pCurSubframeState);
		}

		return hr;
	}

	// Initialize connection
	Result ConnectionUDPBase::InitConnection(const PeerInfo &local, const PeerInfo &remote)
	{
		Result hr = ResultCode::SUCCESS;

        m_GatheringBuffer = nullptr;

		netCheck(Connection::InitConnection( local, remote ) );

		netCheck( ClearQueues() );

        ClearReceivedSubframeStates();

		return hr;
	}

	// Close connection
	Result ConnectionUDPBase::CloseConnection(const char* reason)
	{
		Result hr = ResultCode::SUCCESS;

		if (GetConnectionState() == ConnectionState::CONNECTED)
			Disconnect(reason);

		hr = Connection::CloseConnection(reason);

        ClearReceivedSubframeStates();

		return hr;
	}

	// Clear Queue
	Result ConnectionUDPBase::ClearQueues()
	{
		Connection::ClearQueues();

		m_RecvReliableWindow.Reset();
		m_SendReliableWindow.ClearWindow();
        m_SendGuaQueue.Reset();

        ClearReceivedSubframeStates();

        return ResultCode::SUCCESS;
	}

	// Disconnect connection
	Result ConnectionUDPBase::Disconnect(const char* reason)
	{
		if (GetConnectionState() != ConnectionState::CONNECTED)
		{
			// Send disconnect signal
			MessageID msgIDTem;

			msgIDTem.ID = PACKET_NETCTRL_NONE;
			SendNetCtrl(PACKET_NETCTRL_DISCONNECT, 0, msgIDTem);
		}

		return Connection::Disconnect(reason);
	}

	// Process network control message
	Result ConnectionUDPBase::ProcNetCtrl(const MsgNetCtrlBuffer* pNetCtrl)
	{
		Result hr;
		ConnectionMessageAction* pAction = nullptr;

		if (pNetCtrl->Header.MessageSize < (sizeof(MessageHeader) + sizeof(MsgNetCtrl)))
		{
			SFLog(Net, Info, "HackWarn : Invalid packet CID:{0}, Addr {1}", GetCID(), GetRemoteInfo().PeerAddress);
			netCheck(Disconnect("Invalid packet"));
			netCheck(ResultCode::IO_BADPACKET_NOTEXPECTED);
		}

		pAction = m_NetCtrlAction[pNetCtrl->Header.MessageId.IDs.MsgCode];
		if (pAction != nullptr)
		{
			return pAction->Run(&pNetCtrl->Header);
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

	Result ConnectionUDPBase::OnGuaranteedMessageRecv(const MessageHeader* pHeader)
	{
		Result hr;

		MessageID msgID = pHeader->MessageId;
		uint seq = pHeader->GetSequence();
        uint len = pHeader->MessageSize;

		Result hrTem = m_RecvReliableWindow.AddMsg(pHeader);

		SFLog(Net, Debug5, "RECVGuaAdd : CID:{0} msgId:{1}, seq:{2}, len:{3}, hr:{4}, Window base:{5}, msgCount:{6}, syncMask:{7}",
			GetCID(), 
			msgID, seq, len, hrTem,
			m_RecvReliableWindow.GetBaseSequence(), m_RecvReliableWindow.GetMsgCount(), m_RecvReliableWindow.GetSyncMask());

		if (hrTem == Result(ResultCode::SUCCESS_IO_PROCESSED_SEQUENCE))
		{
			// Added to msg window just send ACK
			SendReliableMessageAck(msgID);

			return hr;
		}
		else if (hrTem == Result(ResultCode::IO_INVALID_SEQUENCE) || hrTem == Result(ResultCode::IO_SEQUENCE_OVERFLOW))
		{
			// out of window, we are going to receive this message again
			return hr;
		}
		else
		{
			netCheck(hrTem);

			// Added to msg window just send ACK
			SendReliableMessageAck(msgID);

            RecvMsgWindow2::MessageBuffer::ItemReadPtr messageItemPtr;
            while (m_RecvReliableWindow.PopMsg(messageItemPtr))
            {
                MessageHeader* pPopHeader = reinterpret_cast<MessageHeader*>(messageItemPtr.data());
                if (pPopHeader->GetMessageID() == PACKET_NETCTRL_SEQUENCE_FRAME)
                {
                    hr = OnFrameSequenceMessage(pHeader);
                }
                else
                {
                    hr = super::OnRecv(pPopHeader);
                }
            }
		}

		return hr;
	}

	Result ConnectionUDPBase::SendReliableMessageAck(MessageID msgID)
	{
		return SendNetCtrl(PACKET_NETCTRL_ACK, msgID.GetSequence(), msgID);
	}

    Result ConnectionUDPBase::SendMsg(const MessageHeader* pMsgHeader)
    {
        MessageID msgID;
        ScopeContext hr([this, &msgID](Result hr)
            {
                if (hr)
                {
                    if (msgID.GetMessageType() == EMessageType::NetCtrl)
                    {
                        SFLog(Net, Debug6, "TCP Ctrl CID:{2}, ip:{0}, msg:{1}", GetRemoteInfo().PeerAddress, msgID, GetCID());
                    }
                    else
                    {
                        SFLog(Net, Debug5, "TCP Send CID:{2}, ip:{0}, msg:{1}", GetRemoteInfo().PeerAddress, msgID, GetCID());
                    }
                }

            });
        uint uiMsgLen{};

        if (GetConnectionState() == ConnectionState::DISCONNECTED)
            return ResultCode::SUCCESS_FALSE;

        msgID = pMsgHeader->MessageId;
        uiMsgLen = pMsgHeader->MessageSize;

        if ((msgID.GetMessageType() != EMessageType::NetCtrl && GetConnectionState() == ConnectionState::DISCONNECTING)
            || GetConnectionState() == ConnectionState::DISCONNECTED)
        {
            // Send fail by connection closed
            return hr;
        }

        // nerf size limit for now
        if (!msgID.IDs.Reliability && pMsgHeader->MessageSize > (uint)Const::PACKET_SIZE_MAX)
        {
            SFLog(Net, Debug, "Too big packet: msg:{0}, seq:{1}, len:{2}",
                msgID,
                msgID.GetSequence(),
                uiMsgLen);

            Protocol::PrintDebugMessage("SendBig", pMsgHeader);
            //netCheck(ResultCode::IO_BADPACKET_TOOBIG);
        }
        else
        {
            Protocol::PrintDebugMessage("Send", pMsgHeader);
        }

        if (!msgID.IDs.Reliability
            && m_SendGuaQueue.size() > Const::GUARANTEED_PENDING_MAX)
        {
            // Drop if there is too many reliable packets are pending
            netCheck(ResultCode::IO_SEND_FAIL);
        }

        if (msgID.GetMessageType() == EMessageType::NetCtrl)
        {
            netCheck(SendRaw(pMsgHeader));
        }
        else
        {
            if (!msgID.IDs.Reliability)
            {
                SFLog(Net, Debug4, "SEND : msg:{0}, len:{1}", msgID, uiMsgLen);

                CircularBufferQueue::ItemWritePtr itemWritePtr = m_GatheringBufferQueue.AllocateWrite(pMsgHeader->MessageSize);
                if (!itemWritePtr)
                {
                    // OOM? try flush out and try again
                    SendFlush();
                    itemWritePtr = m_GatheringBufferQueue.AllocateWrite(pMsgHeader->MessageSize);
                }

                if (!itemWritePtr)
                {
                    netCheck(ResultCode::OUT_OF_RESERVED_MEMORY);
                }

                memcpy(itemWritePtr.data(), pMsgHeader, pMsgHeader->MessageSize);

                MessageHeader* pCopiedMessage = reinterpret_cast<MessageHeader*>(itemWritePtr.data());
                pCopiedMessage->SetSequence(NewSeqNone());

                itemWritePtr.Reset();
            }
            else
            {
                if (m_SendGuaQueue.size() > Const::GUARANTEED_PENDING_MAX)
                {
                    // too many pending messages, disconnect
                    SFLog(Net, Error, "Reliable queue overflow RemoteIp:{0}", GetRemoteInfo().PeerAddress);
                    Disconnect("Reliable queue overflow");
                    return hr;
                }

                SFLog(Net, Debug6, "SENDGuaQueued : CID:{0}, msg:{1}, len:{2}",
                    GetCID(),
                    msgID,
                    uiMsgLen);

                if (pMsgHeader->MessageSize > (uint)Const::INTER_PACKET_SIZE_MAX)
                {
                    netCheck(SendFrameSequenceMessage(pMsgHeader));
                }
                else
                {
                    MessageDataPtr msgDataPtr = MessageData::NewMessage(GetSystemHeap(), pMsgHeader);
                    // For relay message the message could have sequence which need to be cleared
                    msgDataPtr->GetMessageHeader()->SetSequence(0);
                    msgDataPtr->UpdateChecksumNEncrypt();

                    netCheck(m_SendGuaQueue.Enqueue(std::forward<MessageDataPtr>(msgDataPtr)));
                }

                SetSendBoost(Const::RELIABLE_SEND_BOOST);
            }
        }

        return hr;
    }


    Result ConnectionUDPBase::SendRaw(const MessageHeader* pMsgHeader)
    {
        Result hr;

        netCheckPtr(pMsgHeader);

        if (pMsgHeader->MessageSize > (uint)Const::PACKET_SIZE_MAX)
        {
            netCheck(ResultCode::IO_BADPACKET_TOOBIG);
        }

        CircularBufferQueue::ItemWritePtr itemWritePtr = m_GatheringBufferQueue.AllocateWrite(pMsgHeader->MessageSize);
        if (!itemWritePtr)
        {
            // OOM? try flush out and try again
            SendFlush();
            itemWritePtr = m_GatheringBufferQueue.AllocateWrite(pMsgHeader->MessageSize);
        }

        if (!itemWritePtr)
        {
            netCheck(ResultCode::OUT_OF_RESERVED_MEMORY);
        }

        memcpy(itemWritePtr.data(), pMsgHeader, pMsgHeader->MessageSize);

        itemWritePtr.Reset();

        return hr;
    }

	// called when incoming message occur
	Result ConnectionUDPBase::OnRecv(uint uiBuffSize, uint8_t* pBuff)
	{
		Result hr = ResultCode::SUCCESS;
		SharedPointerT<MessageData> pMsg;

		if (uiBuffSize == 0)
		{
            SFLog(Net, Debug4, "UDP Recv ip:{0}, Zero size packet", GetRemoteInfo().PeerAddress);

			IncZeroRecvCount();

			if (GetZeroRecvCount() > (uint32_t)Const::CONNECTION_ZEROPACKET_MAX)
			{
				Disconnect("Too many zero packet");
			}
			return hr;
		}

        PacketHeader* pPacketHeader{};
        MessageHeader* pMsgHeader{};
        if (m_bIncludePacketHeader)
        {
            pPacketHeader = reinterpret_cast<PacketHeader*>(pBuff);
            pMsgHeader = reinterpret_cast<MessageHeader*>(pPacketHeader + 1);
        }
        else
        {
            pMsgHeader = reinterpret_cast<MessageHeader*>(pBuff);
        }

        SFLog(Net, Debug4, "UDP Recv ip:{0}, msg:{1}, seq:{2}, len:{3}", GetRemoteInfo().PeerAddress, pMsgHeader->MessageId, pMsgHeader->GetSequence(), uiBuffSize);

		MutexScopeLock scopeLock(GetUpdateLock());

		while (uiBuffSize && GetConnectionState() != ConnectionState::DISCONNECTED)
		{
            pMsgHeader = reinterpret_cast<MessageHeader*>(pBuff);
			if (uiBuffSize < pMsgHeader->GetHeaderSize() || uiBuffSize < pMsgHeader->MessageSize || pMsgHeader->MessageSize == 0)
			{
				SFLog(Net, Error, "Unexpected packet buffer size:{0}, size in header:{1}", uiBuffSize, pMsgHeader->MessageSize);
				netErr(ResultCode::IO_BADPACKET_SIZE);
			}

#ifdef UDP_PACKETLOS_EMULATE
			if ((Util::Random.Rand() % UDP_PACKETLOS_RATE) < UDP_PACKETLOS_BOUND)
				goto Proc_End;
#endif	// UDP_PACKETLOS_EMULATE

			ResetZeroRecvCount();

			if (pMsgHeader->MessageId.GetMessageType() == EMessageType::NetCtrl) // if net control message then process immediately
			{
				netChk(ProcNetCtrl(reinterpret_cast<const MsgNetCtrlBuffer*>(pMsgHeader)));
			}
			else
			{
				if (GetConnectionState() == ConnectionState::CONNECTED)
				{
                    hr = OnRecv(pMsgHeader);
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


			uiBuffSize -= pMsgHeader->MessageSize;
			pBuff += pMsgHeader->MessageSize;
			pMsg = nullptr;
		}

	Proc_End:

		SendFlush();

		return hr;
	}


	Result ConnectionUDPBase::OnRecv(MessageHeader* pMsgHeader)
	{
		ScopeContext hr([this](Result hr)
			{
				if (!hr.IsSuccess())
				{
					CloseConnection("OnRecv is failed");
				}
			});

		if (GetConnectionState() != ConnectionState::CONNECTED)
		{
			return hr;
		}

		if (pMsgHeader->MessageId.IDs.Reliability)
		{
			SFLog(Net, Debug5, "RECVGua    : CID:{0} msg:{1}, seq:{2}, len:{3}",
				GetCID(),
				pMsgHeader->MessageId,
				pMsgHeader->GetSequence(),
				pMsgHeader->MessageSize);

			netCheck(OnGuaranteedMessageRecv(pMsgHeader));
		}
		else
		{
			netCheck(super::OnRecv(pMsgHeader));
		}

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

		return hr;
	}
	
} // namespace Net
} // namespace SF
