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
	//	Pure UDP networking class
	//		- No logical connection management and so on
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

		using MessageHandlerFunc = std::function<void(const sockaddr_storage& remoteAddr, const MessageHeader* pMsg)>;

	private:

		Heap m_Heap;

		MyNetSocketIOAdapter m_NetIOAdapter;

		NetAddress m_LocalAddress;
		sockaddr_storage m_LocalSockAddress;

		IOBUFFER_READ *m_pRecvBuffers = nullptr;

		MessageHandlerFunc m_MessageHandler;


	protected:

	public:

		RawUDP();
		RawUDP(IHeap& heap);
		virtual ~RawUDP();

		IHeap& GetHeap() { return *m_Heap.get(); }

		bool CanDelete() { return m_NetIOAdapter.CanDelete(); }

		Result InitializeNet(const NetAddress& localAddress, MessageHandlerFunc&& Handler);
		Result TerminateNet();

		const NetAddress& GetLocalAddress() const { return m_LocalAddress; }

		Result SendMsg(const sockaddr_storage& dest, size_t sendSize, uint8_t* pBuff);

		// called when incoming message occur
		Result OnRecv(const sockaddr_storage& remoteAddr, uint uiBuffSize, const uint8_t* pBuff);
	};






} // namespace Net
} // namespace SF



