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
#pragma pack(push,4)
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

		// Constructor
		IOBUFFER_WRITE();
		~IOBUFFER_WRITE();

		// Initialize for IO
		inline void InitForIO(SF_SOCKET sockWrite);
		//inline void InitMsg(bool bIncludePacketHeader, SharedPointerT<MessageData>&& pMsg);
		inline void InitBuff(uint uiBuffSize, uint8_t* pBuff);

		// Setup sending mode
		inline void SetupSendUDP(SF_SOCKET sockWrite, const sockaddr_storage& to, uint uiBuffSize, uint8_t* pBuff);
		inline void SetupSendTCP(uint uiBuffSize, uint8_t* pBuff);

	};


	// UDP/TCP read overlapped
	struct IOBUFFER_READ : public IOBUFFER_RWBASE
	{
        static constexpr size_t MaxPacketSize = Const::INTER_PACKET_SIZE_MAX;

        // Recv connection ID for error check
        uint64_t CID;

        // UDP Recv socket length
		socklen_t iSockLen;

		std::atomic<bool> bIsPending;

		// constructor
		IOBUFFER_READ();
		~IOBUFFER_READ();

        void* operator new(size_t size) {
            return GetSystemHeap().Alloc(size + MaxPacketSize);
        }
        void operator delete(void* pPtr)
        {
            GetSystemHeap().Free(pPtr);
        }

        SF_FORCEINLINE uint8_t* GetPayloadPtr() const
        {
            return const_cast<uint8_t*>(reinterpret_cast<const uint8_t*>(this + 1));
        }

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
#pragma pack(pop)


#include "SFNetSystem_Linux.inl"

} // namespace Net
} // namespace SF
