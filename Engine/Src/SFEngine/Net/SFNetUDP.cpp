////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) Kyungkun Ko.
// 
// Author : KyungKun Ko
//
// Description : Net UDP
//	
//
////////////////////////////////////////////////////////////////////////////////



#include "SFEnginePCH.h"
#include "ResultCode/SFResultCodeEngine.h"
#include "Multithread/SFThread.h"
#include "SFProtocol.h"
#include "Service/SFEngineService.h"
#include "Util/SFToString.h"
#include "Util/SFStrUtil.h"
#include "Util/SFTimeUtil.h"
#include "Util/SFLog.h"

#include "Net/SFNetToString.h"
#include "Net/SFNetConst.h"
#include "Net/SFNetSystem.h"
#include "Net/SFNetUDP.h"



namespace SF {
namespace Net {




	//////////////////////////////////////////////////////////////////////////////////////////
	//
	//	class NetUDP
	//


	NetUDP::MyNetSocketIOAdapter::MyNetSocketIOAdapter(NetUDP &owner)
		: SocketIOUDP(owner.GetHeap())
		, m_Owner(owner)
	{
	}

	Result NetUDP::MyNetSocketIOAdapter::OnIORecvCompleted(Result hrRes, IOBUFFER_READ* &pIOBuffer)
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

				if (!(hr = m_Owner.OnRecv(pIOBuffer->NetAddr.From, pIOBuffer->TransferredSize, (uint8_t*)pIOBuffer->GetPayloadPtr())))
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
            // We bulk allocated the buffer
			//Util::SafeDelete(pIOBuffer);
		}


		return hr;

	}

	Result NetUDP::MyNetSocketIOAdapter::OnWriteReady()
	{
		//return ProcessSendQueue();
        assert(false);
        return ResultCode::NOT_IMPLEMENTED;
	}

	// Send message to connection with network device
	Result NetUDP::MyNetSocketIOAdapter::WriteBuffer(IOBUFFER_WRITE *pSendBuffer)
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
	//	class NetUDP
	//

	NetUDP::NetUDP()
		: m_Heap("NetNetUDP", Service::NetSystem->GetHeap())
		, m_NetIOAdapter(*this)
	{
	}

	NetUDP::NetUDP(IHeap& heap)
		: m_Heap("NetNetUDP", heap)
		, m_NetIOAdapter(*this)
	{
	}

	NetUDP::~NetUDP()
	{
		delete (m_pRecvBuffers);
	}

	Result NetUDP::InitializeNet(const NetAddress& localAddress, MessageHandlerFunc &&Handler)
	{
        SF_SOCKET socket = INVALID_SOCKET;
        ScopeContext hr([this, &socket](Result hr)
            {
                if (hr.IsFailure())
                    TerminateNet();

                if (socket != INVALID_SOCKET)
                    Service::NetSystem->CloseSocket(socket);

                SFLog(Net, Info, "NetUDP: Opened {0}, hr={1:X8}", m_LocalAddress, hr);

            });
		INT iOptValue;
		//int bOptValue = 0;
		sockaddr_storage bindAddr;
		NetAddress myAddress;

		m_NetIOAdapter.CloseSocket();

		m_MessageHandler = std::forward<MessageHandlerFunc>(Handler);

		if (StrUtil::IsNullOrEmpty(localAddress.Address) == '\0')
		{
			netCheck(Net::GetLocalAddressIPv6(myAddress));
		}
		else
		{
			myAddress = localAddress;
		}

		m_LocalAddress = myAddress;
		Addr2SockAddr(m_LocalAddress, m_LocalSockAddress);


		SFLog(Net, Debug2, "NetUDP: Opening UDP Net {0}", m_LocalAddress);

		socket = Service::NetSystem->Socket(m_LocalAddress.SocketFamily, SocketType::DataGram);
		if (socket == INVALID_SOCKET)
		{
			SFLog(Net, Error, "NetUDP: Failed to Open NetUDP Socket {0}", GetLastNetSystemResult());
			netCheck(ResultCode::UNEXPECTED);
		}

		iOptValue = 0;
#if SF_PLATFORM == SF_PLATFORM_WINDOWS
		int iOptLen = static_cast<int>(sizeof(iOptValue));
		if (getsockopt(socket, SOL_SOCKET, SO_MAX_MSG_SIZE, (char *)&iOptValue, &iOptLen) == SOCKET_ERROR)
		{
			SFLog(Net, Error, "NetUDP: Failed to get socket option SO_MAX_MSG_SIZE = {0}, err = {1}", iOptValue, GetLastNetSystemResult());
            netCheck(ResultCode::UNEXPECTED);
		}
		if (iOptValue < Const::PACKET_SIZE_MAX)
		{
			SFLog(Net, Warning, "NetUDP: Socket max packet size too small, Change to socket maximum SocketMax={0}, SvrMax={1}, err = {2}", iOptValue, (uint)Const::PACKET_SIZE_MAX, GetLastNetSystemResult());
			//Const::PACKET_SIZE_MAX = iOptValue;
		}
#else
		unused(iOptValue);
#endif

        netCheck(Service::NetSystem->SetupCommonSocketOptions(SocketType::DataGram, m_LocalAddress.SocketFamily, socket));

		GetAnyBindAddr(m_LocalSockAddress, bindAddr);
		if (bind(socket, (sockaddr*)&bindAddr, sizeof(bindAddr)) == SOCKET_ERROR)
		{
			SFLog(Net, Error, "NetUDP: Socket bind failed, UDP err={0:X8}", GetLastNetSystemResult());
            netCheck(ResultCode::UNEXPECTED);
		}
		m_LocalSockAddress = bindAddr;

		m_NetIOAdapter.SetSocket(m_LocalAddress.SocketFamily, SocketType::DataGram, socket);
		socket = INVALID_SOCKET;


        netCheck(Service::NetSystem->RegisterSocket(&m_NetIOAdapter));


		// Ready recv
		if (NetSystem::IsProactorSystem())
		{
			if (m_pRecvBuffers) GetHeap().Delete(m_pRecvBuffers);
			netCheckPtr(m_pRecvBuffers = new IOBUFFER_READ[Const::SVR_NUM_RECV_THREAD]);

			for (int uiRecv = 0; uiRecv < Const::SVR_NUM_RECV_THREAD; uiRecv++)
			{
				m_NetIOAdapter.PendingRecv(&m_pRecvBuffers[uiRecv]);
			}
		}

		return hr;
	}

	Result NetUDP::TerminateNet()
	{
		ScopeContext hr;

		m_NetIOAdapter.CloseSocket();

		// Clear handler pointer
		m_MessageHandler = {};

		SFLog(Net, Info, "NetUDP Close {0}, hr={1}", m_LocalAddress, hr);

		return hr;
	}


	// Send message to connection with network device
	Result NetUDP::SendMsg(const sockaddr_storage& dest, size_t sendSize, uint8_t* pBuff)
	{
		Result hr = ResultCode::SUCCESS, hrErr = ResultCode::SUCCESS;
		IOBUFFER_WRITE *pOverlapped = nullptr;

		netMem(pOverlapped = new IOBUFFER_WRITE);
		pOverlapped->SetupSendUDP(m_NetIOAdapter.GetIOSocket(), dest, (uint)sendSize, pBuff);

    	netChk(m_NetIOAdapter.WriteBuffer(pOverlapped));

	Proc_End:

		if (!hr.IsSuccess())
		{
			if (pOverlapped)
			{
				pOverlapped->ClearBuffer();
				delete (pOverlapped);
			}
			else
			{
			}

			if (hr != Result(ResultCode::IO_IO_SEND_FAIL))
			{
				SFLog(Net, Error, "NetUDP Send Failed, err:{1:X8}, hr:{2:X8}", hrErr, hr);
			}
			else
			{
				SFLog(Net, Debug3, "NetUDP Send Failed, err:{1:X8}, hr:{2:X8}", hrErr, hr);
				return ResultCode::SUCCESS;
			}
		}
		else
		{
			SFLog(Net, Debug3, "NetUDP Send dest:{0}, size:{1}", dest, sendSize);
		}

		return hr;
	}


	// called when incoming message occur
	Result NetUDP::OnRecv(const sockaddr_storage& remoteAddr, uint uiBuffSize, uint8_t* pBuff)
	{
		Result hr;

		if (uiBuffSize == 0)
			return hr;

		m_MessageHandler(remoteAddr, uiBuffSize, pBuff);

		return hr;
	}



} // namespace Net
} // namespace SF

