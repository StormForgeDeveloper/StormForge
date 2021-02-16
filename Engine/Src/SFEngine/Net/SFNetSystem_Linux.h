////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2015 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Network system linux shared
//	
//
////////////////////////////////////////////////////////////////////////////////


#pragma once

#include "SFTypedefs.h"
#include "Net/SFNetDef.h"
#include "Net/SFNetConst.h"
#include "Util/SFStrUtil.h"
#include "Container/SFHashTable.h"
#include "MemoryManager/SFMemoryPool.h"
#include "Multithread/SFThread.h"
#include "Net/SFNetUtil.h"





namespace SF {
namespace Net {

	class Connection;
	enum class IOBUFFER_OPERATION : uint8_t;

	////////////////////////////////////////////////////////////////////////////////
	//
	//	Overlapped I/O structures
	//

	struct IOBUFFER
	{
		IOBUFFER_OPERATION Operation;

		// Clear Buffer
		void ClearBuffer();
	};


	// UDP/TCP read/write overlapped base
	struct IOBUFFER_RWBASE : public IOBUFFER
	{
		// transferred buffer size
		uint32_t TransferredSize;

		union {
			// UDP Read from
			struct sockaddr_storage From;
			struct sockaddr_storage To;
		} NetAddr;


		// Constructor
		IOBUFFER_RWBASE();
	};


	// UDP/TCP write overlapped
	struct IOBUFFER_WRITE : public IOBUFFER_RWBASE
	{
		SF_SOCKET SockWrite;

		// Sending raw buffer, always has send buffer data pointer and size
		uint RawSendSize;
		uint8_t* pRawSendBuffer;

		// Message pointer to send, when send message data
		SharedPointerAtomicT<Message::MessageData> pMsgs;

		// Message buffer pointer to send, when send buffer data
		uint8_t *pSendBuff;

		// Constructor
		IOBUFFER_WRITE();
		~IOBUFFER_WRITE();

		// Initialize for IO
		inline void InitForIO(SF_SOCKET sockWrite);
		inline void InitMsg(SharedPointerT<Message::MessageData>&& pMsg);
		inline void InitBuff(uint uiBuffSize, uint8_t* pBuff);

		// Setup sending mode
		inline void SetupSendUDP(SF_SOCKET sockWrite, const sockaddr_storage& to, SharedPointerT<Message::MessageData>&& pMsg);
		inline void SetupSendUDP(SF_SOCKET sockWrite, const sockaddr_storage& to, uint uiBuffSize, uint8_t* pBuff);
		inline void SetupSendTCP(SharedPointerT<Message::MessageData>&& pMsg);
		inline void SetupSendTCP(uint uiBuffSize, uint8_t* pBuff);

	};


	// UDP/TCP read overlapped
	struct IOBUFFER_READ : public IOBUFFER_RWBASE
	{
		// UDP Recv socket length
		socklen_t iSockLen;

		// Recv connection ID for error check
		uint64_t CID;

		// Recv buffer
		char buffer[Const::INTER_PACKET_SIZE_MAX];

		std::atomic<bool> bIsPending;

		// constructor
		IOBUFFER_READ();
		~IOBUFFER_READ();

		// Initialize for IO
		inline void InitForIO();
		inline void InitRecv(uint64_t iCID);

		// Setup recving mode
		inline void SetupRecvUDP(uint64_t iCID);
		inline void SetupRecvTCP(uint64_t iCID);

		bool IsPendingTrue() { return bIsPending.load(std::memory_order_consume); }
		Result SetPendingTrue();
		Result SetPendingFalse();
	};


	// TCP accept overlapped
	struct IOBUFFER_ACCEPT : public IOBUFFER
	{
		SF_SOCKET sockAccept;

		sockaddr_storage sockAddr;

		// Constructor
		IOBUFFER_ACCEPT();
		~IOBUFFER_ACCEPT();

		// Setup accept
		inline void SetupAccept(SF_SOCKET sock);
	};



#include "SFNetSystem_Linux.inl"

} // namespace Net
} // namespace SF



