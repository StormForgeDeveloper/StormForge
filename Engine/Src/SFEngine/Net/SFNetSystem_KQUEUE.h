////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2015 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Network system for KQUEUE
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
#include "Service/SFEngineServices.h"
#include "Net/SFNetUtil.h"


#if KQUEUE



namespace SF {
namespace Net {

	class Connection;
	enum class IOBUFFER_OPERATION : uint8_t;



	////////////////////////////////////////////////////////////////////////////////
	//
	//	KQUEUE thread worker
	//


	class KQUEUEWorker : public Thread
	{
	public:

		enum {
			MAX_KQUEUE_EVENTS = 1000,
			MAX_KQUEUE_WAIT = 500,
		};

	private:
		// KQUEUE handle
		int m_hKQUEUE;
		bool m_HandleSend;

	public:
		// Constructor/destructor
		KQUEUEWorker(bool bHandleSend, int hKQUEUE = 0);

		~KQUEUEWorker();

		int GetKQUEUEHandle() {
			return m_hKQUEUE;
		}

		Result RegisterSocket(SocketIO* cbInstance);
		Result UnregisterSocket(SocketIO* cbInstance);

		virtual void Run() override;


		Result HandleAccept(SF_SOCKET sock, SocketIO* pCallBack);
		Result HandleRW(SF_SOCKET sock, unsigned int events, SocketIO* pCallBack);
	};


	class KQUEUESendWorker : public Thread
	{
	public:

	private:
		// KQUEUE handle
		
		WriteBufferQueue m_WriteQueue;

	public:
		// Constructor/destructor
		KQUEUESendWorker();

		~KQUEUESendWorker();

		WriteBufferQueue& GetWriteQueue() { return m_WriteQueue; }

		virtual void Run() override;
	};


	////////////////////////////////////////////////////////////////////////////////
	//
	//	
	//

	class KQUEUESystem : public NetSystemService::NetIOSystem
	{
	private:


		KQUEUEWorker* m_ListenWorker;
		// workers for TCP
		std::atomic<int> m_iTCPAssignIndex;
		DynamicArray<KQUEUEWorker*> m_WorkerTCP;

		// workers for UDP
		KQUEUESendWorker* m_UDPSendWorker;
		DynamicArray<KQUEUEWorker*> m_WorkerUDP;

	public:

		KQUEUESystem();

		virtual Result Initialize(uint netThreadCount) override;
		virtual void Terminate() override;

		virtual Result MakeSocketNonBlocking(SF_SOCKET sfd) override;
		virtual WriteBufferQueue* GetWriteBufferQueue() override;
		//Result RegisterSharedSocket(SockType sockType, SocketIO* cbInstance) override;

		// Register the socket to KQUEUE
		virtual Result RegisterToNETIO(SockType sockType, SocketIO* cbInstance) override;
		virtual Result UnregisterFromNETIO(SocketIO* cbInstance) override;


	};





} // namespace Net
} // namespace SF


#endif
