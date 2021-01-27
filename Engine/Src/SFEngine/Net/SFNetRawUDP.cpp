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
#include "Thread/SFThread.h"
#include "Protocol/SFProtocol.h"
#include "Service/SFEngineService.h"
#include "String/SFToString.h"
#include "String/SFStrUtil.h"
#include "Util/SFTimeUtil.h"
#include "Util/SFLog.h"

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

				if (!(hr = m_Owner.OnRecv(pIOBuffer->NetAddr.From, pIOBuffer->TransferredSize, (uint8_t*)pIOBuffer->buffer)))
					SFLog(Net, Debug3, "Read IO failed with hr={0:X8}", hr);

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
		return ProcessSendQueue();
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
		delete m_pRecvBuffers;
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

		if (StrUtil::IsNullOrEmpty(localAddress.Address) == '\0')
		{
			netChk(Net::GetLocalAddressIPv6(myAddress));
		}
		else
		{
			myAddress = localAddress;
		}

		m_LocalAddress = myAddress;
		Addr2SockAddr(m_LocalAddress, m_LocalSockAddress);


		SFLog(Net, Debug2, "RawUDP: Opening UDP Net {0}", m_LocalAddress);

		socket = Service::NetSystem->Socket(m_LocalAddress.SocketFamily, SockType::DataGram);
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

		netChk(Service::NetSystem->SetupCommonSocketOptions(SockType::DataGram, m_LocalAddress.SocketFamily, socket));

		GetAnyBindAddr(m_LocalSockAddress, bindAddr);
		if (bind(socket, (sockaddr*)&bindAddr, sizeof(bindAddr)) == SOCKET_ERROR)
		{
			SFLog(Net, Error, "RawUDP: Socket bind failed, UDP err={0:X8}", GetLastNetSystemResult());
			netErr(ResultCode::UNEXPECTED);
		}
		m_LocalSockAddress = bindAddr;

		m_NetIOAdapter.SetSocket(m_LocalAddress.SocketFamily, SockType::DataGram, socket);
		socket = INVALID_SOCKET;


		netChk(Service::NetSystem->RegisterSocket(&m_NetIOAdapter));


		// Ready recv
		if (NetSystem::IsProactorSystem())
		{
			if (m_pRecvBuffers) GetHeap().Delete(m_pRecvBuffers);
			netMem(m_pRecvBuffers = new(GetHeap()) IOBUFFER_READ[Const::SVR_NUM_RECV_THREAD]);

			for (int uiRecv = 0; uiRecv < Const::SVR_NUM_RECV_THREAD; uiRecv++)
			{
				m_NetIOAdapter.PendingRecv(&m_pRecvBuffers[uiRecv]);
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

		// Clear handler pointer
		m_MessageHandler = {};

		SFLog(Net, Info, "RawUDP Close {0}, hr={1}", m_LocalAddress, hr);

		return hr;
	}


	// Send message to connection with network device
	Result RawUDP::SendMsg(const sockaddr_storage& dest, SharedPointerT<Message::MessageData>& pMsg)
	{
		Result hr = ResultCode::SUCCESS, hrErr = ResultCode::SUCCESS;

		Message::MessageID msgID = pMsg->GetMessageHeader()->msgID;
		IOBUFFER_WRITE *pOverlapped = nullptr;


		netMem(pOverlapped = new(GetHeap()) IOBUFFER_WRITE);
		pOverlapped->SetupSendUDP(m_NetIOAdapter.GetIOSocket(), dest, std::forward<SharedPointerT<Message::MessageData>>(pMsg));
		pMsg = nullptr;

		if (NetSystem::IsProactorSystem())
		{
			netChk(m_NetIOAdapter.WriteBuffer(pOverlapped));
		}
		else
		{
			netChk(m_NetIOAdapter.EnqueueBuffer(pOverlapped));
		}

	Proc_End:

		if (!(hr))
		{
			if (pOverlapped)
			{
				pOverlapped->ClearBuffer();
				pOverlapped->pMsgs = nullptr;
				delete pOverlapped;
			}
			else
			{
				pMsg = nullptr;
			}

			if (hr != Result(ResultCode::IO_IO_SEND_FAIL))
			{
				SFLog(Net, Error, "RawUDP Send Failed, err:{1:X8}, hr:{2:X8}", hrErr, hr);
			}
			else
			{
				SFLog(Net, Debug3, "RawUDP Send Failed, err:{1:X8}, hr:{2:X8}", hrErr, hr);
				return ResultCode::SUCCESS;
			}
		}
		else
		{
			if (msgID.IDs.Type == Message::MSGTYPE_NETCONTROL)
			{
				SFLog(Net, Debug3, "RawUDP SendCtrl dest:{0}, msg:{1}", dest, msgID);
			}
			else
			{
				SFLog(Net, Debug3, "RawUDP Send dest:{0}, msg:{1}", dest, msgID);
			}
		}

		return hr;
	}


	// called when incoming message occur
	Result RawUDP::OnRecv(const sockaddr_storage& remoteAddr, uint uiBuffSize, const uint8_t* pBuff)
	{
		Result hr = ResultCode::SUCCESS;
		SharedPointerT<Message::MessageData> pMsg;
		Message::MobileMessageHeader * pMsgHeader = (Message::MobileMessageHeader*)pBuff;

		//SFLog(Net, Debug3, "UDP Recv ip:{0}, msg:{1}, seq:{2}, len:{3}", GetRemoteInfo().PeerAddress, pMsgHeader->msgID, pMsgHeader->msgID.IDSeq.Sequence, uiBuffSize);

		if (uiBuffSize == 0)
			goto Proc_End;

		while (uiBuffSize)
		{
			pMsgHeader = (Message::MobileMessageHeader*)pBuff;
			if (uiBuffSize < sizeof(Message::MobileMessageHeader) || uiBuffSize < pMsgHeader->Length)
			{
				SFLog(Net, Error, "Unexpected packet buffer size:{0}, size in header:{1}", uiBuffSize, pMsgHeader->Length);
				netErr(ResultCode::IO_BADPACKET_SIZE);
			}

			netMem(pMsg = Message::MessageData::NewMessage(GetHeap(), pMsgHeader->msgID.ID, pMsgHeader->Length, pBuff));

			uiBuffSize -= pMsgHeader->Length;
			pBuff += pMsgHeader->Length;

			m_MessageHandler(remoteAddr, pMsg);

			netChk(hr);
		}

	Proc_End:

		pMsg = nullptr;

		return hr;
	}



} // namespace Net
} // namespace SF

