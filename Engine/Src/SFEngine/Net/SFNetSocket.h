////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2018 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Network socket + IO handling class
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
#include "Component/SFLibraryComponent.h"
#include "EngineObject/SFEngineTask.h"

#include "Service/SFEngineServices.h"


namespace SF {
namespace Net {

	class Connection;


	////////////////////////////////////////////////////////////////////////////////
	//
	//	Overlapped I/O structures
	//

	struct IOBUFFER_WRITE;
	struct IOBUFFER_READ;
	struct IOBUFFER_ACCEPT;




	////////////////////////////////////////////////////////////////////////////////
	//
	// NetSocketIO  class
	//

	// This is Socket + IO handling class
	// TODO: Back in the day It was part of connection, and end up with having a lot of redundant codes. I am trying to separate Socket + IO handling from connection, and put them into independent class
	class SocketIO
	{
	public:

		struct CBFlags
		{
			// Is listen only socket?
			uint32_t IsListenSocket : 1;

			CBFlags()
				: IsListenSocket(0)
			{}

			~CBFlags()
			{
			}
		};

		enum class IOStatus : uint32_t
		{
			None,
			Registered
		};

	private:

		IHeap& m_Heap;

		CBFlags m_CBFlags;

		SockType m_IOSockType = SockType::DataGram;
		SockFamily m_IOSockFamily = SockFamily::IPV4;

		// Is registered to IO sub system
		std::atomic<IOStatus> m_IOStatus;

		WriteBufferQueue* m_pWriteQueues;

		// Assigned IO worker thread index
		int m_AssignedIOWorker = -1;

		// Link to original socket variable
		SF_SOCKET m_IOSocket = INVALID_SOCKET;

		// Recv pending count
		std::atomic<int32_t> m_PendingRecvCount;
		std::atomic<int32_t> m_PendingSendCount;

		// User socket identifier value, usually connection ID, default 0
		uint64_t m_UserSocketID = 0;

	protected:

		Result m_LastPendingRecvResult;

	public:

		SocketIO(IHeap& heap);
		virtual ~SocketIO();

		IHeap& GetIOHeap() { return m_Heap; }

		// Get latest pending recv result
		Result GetLastPendingRecvResult() { return m_LastPendingRecvResult; }

		// IO worker handling
		int GetAssignedIOWorker() const { return m_AssignedIOWorker; }
		void SetAssignedIOWorker(int assignedIOWorker);

		// User socket identifier value, usually connection ID
		uint64_t GetUserSocketID() const { return m_UserSocketID; }
		void SetUserSocketID(uint64_t userID) { m_UserSocketID = userID; }

		// casting, a bit faster than dynamic cast
		//virtual SharedObject* AsSharedObject() { return nullptr; }
		bool GetIsIORegistered() const { return m_IOStatus.load(std::memory_order_acquire) == IOStatus::Registered; }
		void OnIORegistered();
		void OnIOUnregistered();

		void SetSocket(SockFamily sockFamily, SockType socketType, SF_SOCKET socket);
		void CloseSocket();

		SockType GetIOSockType() const { return m_IOSockType; }
		SockFamily GetSocketFamily() const { return m_IOSockFamily; }

		const CBFlags& GetIOFlags() const { return m_CBFlags; }
		CBFlags& GetIOFlagsEditable() { return m_CBFlags; }
		SF_SOCKET GetIOSocket() const { return m_IOSocket; }

		// Write queue
		WriteBufferQueue* GetWriteQueue() { return m_pWriteQueues; }
		void SetWriteQueue(WriteBufferQueue* writeQueue) { Assert(writeQueue != nullptr && m_pWriteQueues == nullptr); m_pWriteQueues = writeQueue; }




		// Get pending recv count
		int32_t GetPendingRecvCount() { return m_PendingRecvCount.load(std::memory_order_relaxed); }
		int32_t IncPendingRecvCount() { return m_PendingRecvCount.fetch_add(1, std::memory_order_relaxed) + 1; }
		void DecPendingRecvCount() { auto recvCount = m_PendingRecvCount.fetch_sub(1, std::memory_order_relaxed) - 1; unused(recvCount); assert(recvCount >= 0); }
		void ResetPendingRecvCount() { m_PendingRecvCount = 0; }

		int32_t GetPendingSendCount() { return m_PendingSendCount.load(std::memory_order_relaxed); }
		int32_t IncPendingSendCount() { return m_PendingSendCount.fetch_add(1, std::memory_order_relaxed) + 1; }
		void DecPendingSendCount() { auto sendCount = m_PendingSendCount.fetch_sub(1, std::memory_order_relaxed) - 1; unused(sendCount); assert(sendCount >= 0); }
		void ResetPendingSendCount() { m_PendingSendCount = 0; }


		// Send message to connection with network device
		virtual Result WriteBuffer(IOBUFFER_WRITE *pSendBuffer) = 0;
		virtual Result EnqueueBuffer(IOBUFFER_WRITE *pSendBuffer);


		virtual Result Accept(IOBUFFER_ACCEPT* &pAcceptInfo) { return ResultCode::NOT_IMPLEMENTED; };
		// called when New connection TCP accepted
		virtual Result OnIOAccept(Result hrRes, IOBUFFER_ACCEPT *pAcceptInfo) { return ResultCode::NOT_IMPLEMENTED; };

		virtual Result PendingRecv(IOBUFFER_READ *pRecvBuffer = nullptr) = 0;
		virtual Result Recv(IOBUFFER_READ* pIOBuffer) = 0;
		// called when receiving a message is completed
		virtual Result OnIORecvCompleted(Result hrRes, IOBUFFER_READ* &pIOBuffer) = 0;

		virtual Result OnWriteReady() = 0;
		virtual Result ProcessSendQueue();
		// called when send completed
		virtual Result OnIOSendCompleted(Result hrRes, IOBUFFER_WRITE *pIOBuffer);

		// check whether this IO object can be deleted.
		// It tells whether it still has possibility to be accessed by net system.
		virtual bool CanDelete();
	};



	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//
	//	SocketIOUDP
	//	 - For UDP socket IO
	//

	class SocketIOUDP : public SocketIO
	{
	public:
		SocketIOUDP(IHeap& heap);

		virtual Result WriteBuffer(IOBUFFER_WRITE *pSendBuffer) override;

		virtual Result PendingRecv(IOBUFFER_READ *pRecvBuffer = nullptr) override;

		// Recv handling for UDP socket
		virtual Result Recv(IOBUFFER_READ* pIOBuffer) override;
	};



	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//
	//	SocketIOTCP
	//	 - For TCP socket IO
	//

	class SocketIOTCP : public SocketIO
	{
	public:
		SocketIOTCP(IHeap& heap);

		// Accept handling
		virtual Result Accept(IOBUFFER_ACCEPT* &pAcceptInfo) override;

		virtual Result WriteBuffer(IOBUFFER_WRITE *pSendBuffer) override;

		virtual Result PendingRecv(IOBUFFER_READ *pRecvBuffer = nullptr) override;

		// Recv handling for TCP socket
		virtual Result Recv(IOBUFFER_READ* pIOBuffer) override;
	};


} // namespace Net
} // namespace SF



