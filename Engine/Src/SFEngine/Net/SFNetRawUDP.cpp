////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2016 Kyungkun Ko.
// 
// Author : KyungKun Ko
//
// Description : Net Client
//	
//
////////////////////////////////////////////////////////////////////////////////



#include "SFEnginePCH.h"
#include "ResultCode/SFResultCodeEngine.h"
#include "Multithread/SFThread.h"
#include "Protocol/SFProtocol.h"
#include "Service/SFEngineService.h"
#include "Util/SFToString.h"
#include "Util/SFStrUtil.h"
#include "Util/SFTimeUtil.h"
#include "Util/SFLog.h"
#include "SFScopeContext.h"
#include "Net/SFNetPacketData.h"

#include "Net/SFNetToString.h"
#include "Net/SFNetConst.h"
#include "Net/SFNetSystem.h"
#include "Net/SFNetRawUDP.h"



namespace SF {
namespace Net {




	//////////////////////////////////////////////////////////////////////////////////////////
	//
	//	class RawUDP
	//


	RawUDP::MyNetSocketIOAdapter::MyNetSocketIOAdapter(RawUDP &owner)
		: SocketIOUDP(owner.GetHeap())
		, m_Owner(owner)
	{
	}

	Result RawUDP::MyNetSocketIOAdapter::OnIORecvCompleted(Result hrRes, IOBUFFER_READ* &pIOBuffer)
	{
		Result hr = ResultCode::SUCCESS;

		if (pIOBuffer != nullptr && pIOBuffer->Operation != IOBUFFER_OPERATION::OP_UDPREAD)
		{
			netErr(ResultCode::UNEXPECTED);
		}


		// Pending recv count and registered status should be checked together so that we can prevent infinit pending recv
		// And PendingRecv should be decreased after new pending is happened
		if (GetIsIORegistered())
		{

			if (hrRes)
			{
				netChkPtr(pIOBuffer);

				if (!(hr = m_Owner.OnRecv(pIOBuffer->NetAddr.From, pIOBuffer->TransferredSize, pIOBuffer->GetPayloadPtr())))
					SFLog(Net, Debug3, "Read IO failed with hr={0:X8}", hr);

                // turn off flag before reuse
                pIOBuffer->SetPendingFalse();

				PendingRecv(pIOBuffer);
				pIOBuffer = nullptr;
			}
			else
			{
				// TODO: need to mark close connection
				//m_Owner.Disconnect("Recv failed");
			}
		}

	Proc_End:

		// decrease should be happened at last, and always
		if (NetSystem::IsProactorSystem())
			DecPendingRecvCount();

		if (pIOBuffer != nullptr)
		{
			pIOBuffer->SetPendingFalse();
			Util::SafeDelete(pIOBuffer);
		}


		return hr;

	}

	Result RawUDP::MyNetSocketIOAdapter::OnWriteReady()
	{
		//return ProcessSendQueue();
        assert(false);
        return ResultCode::NOT_IMPLEMENTED;
	}

	// Send message to connection with network device
	Result RawUDP::MyNetSocketIOAdapter::WriteBuffer(IOBUFFER_WRITE *pSendBuffer)
	{
		auto result = SocketIOUDP::WriteBuffer(pSendBuffer);
		switch ((uint32_t)result)
		{
		case (uint32_t)ResultCode::IO_TRY_AGAIN:
		case (uint32_t)ResultCode::IO_CONNABORTED:
		case (uint32_t)ResultCode::IO_CONNRESET:
		case (uint32_t)ResultCode::IO_NETRESET:
		case (uint32_t)ResultCode::IO_NOTCONN:
		case (uint32_t)ResultCode::IO_NOTSOCK:
		case (uint32_t)ResultCode::IO_SHUTDOWN:
		case (uint32_t)ResultCode::INVALID_PIPE:
			// Send fail by connection close
			// Need to disconnect
			//m_Owner.Disconnect("SendBufferUDP is failed");
			break;
		}

		return result;

	}


	//////////////////////////////////////////////////////////////////////////////////////////
	//
	//	class RawUDP
	//

	RawUDP::RawUDP()
		: m_Heap("NetRawUDP", Service::NetSystem->GetHeap())
		, m_NetIOAdapter(*this)
	{
	}

	RawUDP::RawUDP(IHeap& heap)
		: m_Heap("NetRawUDP", heap)
		, m_NetIOAdapter(*this)
	{
	}

	RawUDP::~RawUDP()
	{
	}

	Result RawUDP::InitializeNet(const NetAddress& localAddress, MessageHandlerFunc &&Handler)
	{
		Result hr = ResultCode::SUCCESS;
		SF_SOCKET socket = INVALID_SOCKET;
		INT iOptValue;
		//int bOptValue = 0;
		sockaddr_storage bindAddr;
		NetAddress myAddress;

		m_NetIOAdapter.CloseSocket();

		m_MessageHandler = std::forward<MessageHandlerFunc>(Handler);

		if (StrUtil::IsNullOrEmpty(localAddress.Address))
		{
            // Default IPv6
			netChk(Net::GetLocalAddressIPv6(myAddress));
		}
		else
		{
			myAddress = localAddress;
		}

		m_LocalAddress = myAddress;
		Addr2SockAddr(m_LocalAddress, m_LocalSockAddress);


		SFLog(Net, Debug2, "RawUDP: Opening UDP Net {0}", m_LocalAddress);

		socket = Service::NetSystem->Socket(m_LocalAddress.SocketFamily, SocketType::DataGram);
		if (socket == INVALID_SOCKET)
		{
			SFLog(Net, Error, "RawUDP: Failed to Open RawUDP Socket {0}", GetLastNetSystemResult());
			netErr(ResultCode::UNEXPECTED);
		}

		iOptValue = 0;
#if SF_PLATFORM == SF_PLATFORM_WINDOWS
		INT iOptLen = sizeof(iOptValue);
		if (getsockopt(socket, SOL_SOCKET, SO_MAX_MSG_SIZE, (char *)&iOptValue, &iOptLen) == SOCKET_ERROR)
		{
			SFLog(Net, Error, "RawUDP: Failed to get socket option SO_MAX_MSG_SIZE = {0}, err = {1}", iOptValue, GetLastNetSystemResult());
			netErr(ResultCode::UNEXPECTED);
		}
		if (iOptValue < Const::PACKET_SIZE_MAX)
		{
			SFLog(Net, Warning, "RawUDP: Socket max packet size too small, Change to socket maximum SocketMax={0}, SvrMax={1}, err = {2}", iOptValue, (uint)Const::PACKET_SIZE_MAX, GetLastNetSystemResult());
			//Const::PACKET_SIZE_MAX = iOptValue;
		}
#else
		unused(iOptValue);
#endif

		netChk(Service::NetSystem->SetupCommonSocketOptions(SocketType::DataGram, m_LocalAddress.SocketFamily, socket));

		GetAnyBindAddr(m_LocalSockAddress, bindAddr);
		if (bind(socket, (sockaddr*)&bindAddr, sizeof(bindAddr)) == SOCKET_ERROR)
		{
			SFLog(Net, Error, "RawUDP: Socket bind failed, UDP err={0:X8}", GetLastNetSystemResult());
			netErr(ResultCode::UNEXPECTED);
		}
		m_LocalSockAddress = bindAddr;

		m_NetIOAdapter.SetSocket(m_LocalAddress.SocketFamily, SocketType::DataGram, socket);
		socket = INVALID_SOCKET;


		netChk(Service::NetSystem->RegisterSocket(&m_NetIOAdapter));


		// Ready recv
		if (NetSystem::IsProactorSystem())
		{
			for (int uiRecv = 0; uiRecv < Const::SVR_NUM_RECV_THREAD; uiRecv++)
			{
                IOBUFFER_READ* pRecvBuffer{};
                netMem(pRecvBuffer = new(GetHeap()) IOBUFFER_READ);
				m_NetIOAdapter.PendingRecv(pRecvBuffer);
			}
		}


	Proc_End:

		if (!(hr))
			TerminateNet();

		if (socket != INVALID_SOCKET)
			Service::NetSystem->CloseSocket(socket);

		SFLog(Net, Info, "RawUDP: Opened {0}, hr={1:X8}", m_LocalAddress, hr);

		return hr;
	}

	Result RawUDP::TerminateNet()
	{
		ScopeContext hr;

		m_NetIOAdapter.CloseSocket();

        while (!m_NetIOAdapter.CanDelete())
        {
            ThisThread::SleepFor(DurationMS(1000));
            SFLog(Net, Info, "RawUDP Close wait net ");
        }

		// Clear handler pointer
		m_MessageHandler = {};

		SFLog(Net, Info, "RawUDP Close {0}, hr={1}", m_LocalAddress, hr);

		return hr;
	}


	// Send message to connection with network device
	Result RawUDP::SendMsg(const sockaddr_storage& dest, size_t sendSize, uint8_t* pBuff)
	{
        SFUniquePtr<PacketData> pSendBuffer(new(GetSystemHeap()) PacketData);
        ScopeContext hr(
            [this, &pSendBuffer](Result hr)
            {
                if (!hr)
                {
                    m_NetIOAdapter.DecPendingSendCount();
                    if (hr != Result(ResultCode::IO_IO_SEND_FAIL))
                    {
                        SFLog(Net, Error, "RawUDP Send Failed, hr:{0}", hr);
                    }
                    else
                    {
                        SFLog(Net, Debug3, "RawUDP Send Failed, hr:{0}", hr);
                    }
                }
            });

        m_NetIOAdapter.IncPendingSendCount();

        pSendBuffer->SetupSendUDP(m_NetIOAdapter.GetIOSocket(), dest, 0, nullptr);

        pSendBuffer->Payload.resize(sendSize);
        memcpy(pSendBuffer->Payload.data(), pBuff, sendSize);

        pSendBuffer->PrepareBufferForIO();

        netCheck(m_NetIOAdapter.WriteBuffer(pSendBuffer.get()));
        pSendBuffer.release();

		return hr;
	}


	// called when incoming message occur
	Result RawUDP::OnRecv(const sockaddr_storage& remoteAddr, uint uiBuffSize, const uint8_t* pBuff)
	{
		Result hr;
		SharedPointerT<MessageData> pMsg;
        const MessageHeader * pMsgHeader = reinterpret_cast<const MessageHeader*>(pBuff);

		//SFLog(Net, Debug3, "UDP Recv ip:{0}, msg:{1}, seq:{2}, len:{3}", GetRemoteInfo().PeerAddress, pMsgHeader->msgID, pMsgHeader->msgID.IDSeq.Sequence, uiBuffSize);

		if (uiBuffSize == 0)
			return hr;

		while (uiBuffSize)
		{
            pMsgHeader = reinterpret_cast<const MessageHeader*>(pBuff);
			if (uiBuffSize < pMsgHeader->GetHeaderSize() || uiBuffSize < pMsgHeader->Length || pMsgHeader->Length == 0)
			{
				SFLog(Net, Error, "Unexpected packet buffer size:{0}, size in header:{1}", uiBuffSize, pMsgHeader->Length);
				netCheck(ResultCode::IO_BADPACKET_SIZE);
			}

			uiBuffSize -= pMsgHeader->Length;
			pBuff += pMsgHeader->Length;

			m_MessageHandler(remoteAddr, pMsgHeader);

			netCheck(hr);
		}

		return hr;
	}

} // namespace Net
} // namespace SF

