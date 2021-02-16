////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2015 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Network system for EPOLL
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
#include "Service/SFEngineServices.h"


#if EPOLL



namespace SF {
namespace Net {

	class Connection;
	enum class IOBUFFER_OPERATION : uint8_t;



	////////////////////////////////////////////////////////////////////////////////
	//
	//	EPOLL thread worker
	//


	class EPOLLWorker : public Thread
	{
	public:

		enum {
			MAX_EPOLL_EVENTS = 1000,
			MAX_EPOLL_WAIT = 500,
		};

	private:
		// Epoll handle
		int m_hEpoll;
		bool m_HandleSend;

	public:
		// Constructor/destructor
		EPOLLWorker(bool bHandleSend, int hEpoll = 0);
		~EPOLLWorker();

		int GetEpollHandle() {
			return m_hEpoll;
		}

		Result RegisterSocket(SocketIO* cbInstance);
		Result UnregisterSocket(SocketIO* cbInstance);

		virtual void Run() override;


		Result HandleAccept(SF_SOCKET sock, SocketIO* pCallBack);
		Result HandleRW(SF_SOCKET sock, unsigned int events, SocketIO* pCallBack);
	};



	class EPOLLSendWorker : public Thread
	{
	public:

	private:
		// Epoll handle
		
		WriteBufferQueue m_WriteQueue;

	public:
		// Constructor/destructor
		EPOLLSendWorker();
		~EPOLLSendWorker();

		WriteBufferQueue& GetWriteQueue() { return m_WriteQueue; }

		virtual void Run() override;
	};


	////////////////////////////////////////////////////////////////////////////////
	//
	//	
	//

	class EPOLLSystem : public NetSystemService::NetIOSystem
	{
	private:

		EPOLLWorker* m_ListenWorker;
		// workers for TCP
		std::atomic<int> m_iTCPAssignIndex;
		DynamicArray<EPOLLWorker*> m_WorkerTCP;

		// workers for UDP
		EPOLLSendWorker* m_UDPSendWorker;
		DynamicArray<EPOLLWorker*> m_WorkerUDP;

	public:

		EPOLLSystem();

		virtual Result Initialize(uint netThreadCount) override;
		virtual void Terminate() override;

		virtual Result MakeSocketNonBlocking(SF_SOCKET sfd) override;
		virtual WriteBufferQueue* GetWriteBufferQueue() override;
		//Result RegisterSharedSocket(SockType sockType, SocketIO* cbInstance);

		// Register the socket to EPOLL
		virtual Result RegisterToNETIO(SocketIO* cbInstance) override;
		virtual Result UnregisterFromNETIO(SocketIO* cbInstance) override;

		virtual const char* EventFlagToString(int32_t bufferSize, char* stringBuffer, uint32_t eventFlags) override;
	};





} // namespace Net
} // namespace SF


#endif
