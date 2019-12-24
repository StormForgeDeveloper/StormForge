////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2016 Kyungkun Ko.
// 
// Author : KyungKun Ko
//
// Description : Net Raw UDP
//	
//
////////////////////////////////////////////////////////////////////////////////


#pragma once

#include "Net/SFNetDef.h"
#include "Net/SFNetCtrl.h"
#include "Net/SFNetSystem.h"
#include "Net/SFNetSocket.h"


namespace SF {
namespace Net {


	

	////////////////////////////////////////////////////////////////////////////////
	//
	//	Client base class
	//

	class RawUDP
	{
	public :

		// Network IO adapter
		class MyNetSocketIOAdapter : public SocketIOUDP
		{
		private:

			RawUDP &m_Owner;

		public:

			MyNetSocketIOAdapter(RawUDP &owner);


			// Send message to connection with network device
			virtual Result WriteBuffer(IOBUFFER_WRITE *pSendBuffer) override;

			// called when receiving TCP message
			virtual Result OnIORecvCompleted(Result hrRes, IOBUFFER_READ* &pIOBuffer) override;

			virtual Result OnWriteReady() override;
		};

		class MessageHandler
		{
		public:
			virtual Result OnRecv(const sockaddr_storage& remoteAddr, SharedPointerT<Message::MessageData>& pMsg) = 0;
		};

	private:

		Heap m_Heap;

		MyNetSocketIOAdapter m_NetIOAdapter;

		NetAddress m_LocalAddress;
		sockaddr_storage m_LocalSockAddress;

		IOBUFFER_READ *m_pRecvBuffers = nullptr;

		MessageHandler *m_pMessageHandler = nullptr;



	protected:

	public:

		RawUDP();
		virtual ~RawUDP();

		IHeap& GetHeap() { return m_Heap; }

		Result InitializeNet(const NetAddress& localAddress, MessageHandler *pHandler);
		Result TerminateNet();

		const NetAddress& GetLocalAddress() const { return m_LocalAddress; }

		//Result PendingRecv(IOBUFFER_READ *pOver);
		//virtual Result WriteBuffer(IOBUFFER_WRITE *pSendBuffer) override;
		Result SendMsg(const sockaddr_storage& dest, SharedPointerT<Message::MessageData>& pMsg);


		// called when incoming message occur
		Result OnRecv(const sockaddr_storage& remoteAddr, uint uiBuffSize, const uint8_t* pBuff);
	};






} // namespace Net
} // namespace SF



