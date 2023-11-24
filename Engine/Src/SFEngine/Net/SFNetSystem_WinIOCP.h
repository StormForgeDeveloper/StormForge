////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2016 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Network system for IOCP
//	
//
////////////////////////////////////////////////////////////////////////////////


#pragma once

#if SF_PLATFORM == SF_PLATFORM_WINDOWS

#include "SFTypedefs.h"
#include "Net/SFNetDef.h"
#include "Net/SFNetConst.h"

namespace SF {
namespace Net {

	class Connection;
	enum class IOBUFFER_OPERATION : uint8_t;
	
	////////////////////////////////////////////////////////////////////////////////
	//
	//	Overlapped I/O structures
	//

	struct IOBUFFER : public WSAOVERLAPPED
	{
		IOBUFFER_OPERATION Operation;

		// Clear Buffer
		void ClearBuffer();

	} ;

#pragma pack(push,4)
	// UDP/TCP read/write overlapped base
	struct IOBUFFER_RWBASE : public IOBUFFER
	{
		// IOCP buffer 
		WSABUF	wsaBuff;

		// Transferred buffer size
		uint32_t TransferredSize;

		union {
			// UDP Read from
			struct sockaddr_storage From;
			struct sockaddr_storage To;
		} NetAddr;


		// Constructor
		IOBUFFER_RWBASE();


	} ;


	// UDP/TCP write overlapped
	struct IOBUFFER_WRITE : public IOBUFFER_RWBASE
	{
        uint SendBufferSize = 0;

		// Constructor
		IOBUFFER_WRITE();
		~IOBUFFER_WRITE();

		// Initialize for IO
		inline void InitForIO(SF_SOCKET sockWrite);
		inline void InitBuff(uint uiBuffSize, uint8_t* pBuff);

		// Setup sending mode
		inline void SetupSendUDP(SF_SOCKET sockWrite, const sockaddr_storage& to, uint uiBuffSize, uint8_t* pBuff );
		inline void SetupSendTCP(uint uiBuffSize, uint8_t* pBuff);
	};


	// UDP/TCP read overlapped
	struct IOBUFFER_READ : public IOBUFFER_RWBASE
	{
        static constexpr size_t MaxPacketSize = Const::READ_PACKET_BUFFER_SIZE_MAX;

        // Recv connection ID for error check
        uint64_t CID;

        // Read flag
		DWORD dwFlags;
		DWORD dwNumberOfByte;

		// UDP Recv socket length
		INT iSockLen;

        // Mark whether this buffer is in use
        std::atomic<bool> bIsPending;

        uint8_t Payload[MaxPacketSize];

		// constructor
		IOBUFFER_READ();
		~IOBUFFER_READ();

        SF_FORCEINLINE uint8_t* GetPayloadPtr()
        {
            return Payload;
        }

		// Initialize for IO
		inline void InitForIO();
		inline void InitRecv( uint64_t iCID );

		// Setup receiving mode
		inline void SetupRecvUDP( uint64_t iCID );
		inline void SetupRecvTCP( uint64_t iCID );

		bool IsPendingTrue() { return bIsPending.load(std::memory_order_consume); }
		Result SetPendingTrue();
		Result SetPendingFalse();

	};


	// TCP accept overlapped
	struct IOBUFFER_ACCEPT : public IOBUFFER
	{
		//Connection	*pConnection;
		SF_SOCKET sockAccept;
		uint8_t pAcceptInfo[sizeof(sockaddr_storage)*2];
		DWORD dwByteReceived;

		// Constructor
		IOBUFFER_ACCEPT();
		~IOBUFFER_ACCEPT();

		// Setup accept
		inline void SetupAccept(SF_SOCKET sock );

	};

#pragma pack(pop)



	////////////////////////////////////////////////////////////////////////////////
	//
	//	IO operations
	//

	namespace IOCPSystem
	{
		
		////////////////////////////////////////////////////////////////////////////////
		//
		//	IOCP thread worker
		//
		class IOCPWorker : public Thread
		{
		private:
			// IOCP handle
			HANDLE m_hIOCP;

		public:
			// Constructor/destructor
			IOCPWorker();
			~IOCPWorker();

			inline void SetIOCPHandle( HANDLE hIOCP );

			virtual void Run() override;
		};

		
		
		//////////////////////////////////////////////////////////////////
		//
		//	network IOCP System
		//

		class IOCPSystem : public NetSystemService::NetIOSystem
		{
		private:

			// IOCP system open reference count
			SyncCounter m_RefCount;

			// IOCP worker thread list
			std::vector<IOCPWorker*> m_pWorkers;

			// global statistic
			SyncCounter m_NumReadWait;
			SyncCounter m_NumWriteWait;

			IHeap& m_Heap;

		public:
			IOCPSystem(IHeap& memoryManager);
			~IOCPSystem();

			IHeap& GetHeap() { return m_Heap; }

			virtual Result Initialize(uint netThreadCount) override;
			virtual void Terminate() override;
		};



	}; // namespace IOCPSystem



#include "SFNetSystem_WinIOCP.inl"

} // namespace Net
} // namespace SF

#endif

