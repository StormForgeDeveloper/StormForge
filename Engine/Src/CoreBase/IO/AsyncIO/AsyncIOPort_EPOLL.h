////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2017 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Async IO
//	
//
////////////////////////////////////////////////////////////////////////////////


#pragma once


#if USE_REACTOR_PATTERN && EPOLL

#include "SFTypedefs.h"
#include "String/SFStrUtil.h"
#include "Container/SFHashTable.h"
#include "Memory/SFMemoryPool.h"
#include "Thread/SFThread.h"
#include "IO/AsyncIO/AsyncIOPort.h"
#include "IO/AsyncIO/AsyncIOPort_Reactor.h"
#include "IO/AsyncIO/AsyncIOAdapter.h"





namespace SF {
namespace AsyncIO {


	////////////////////////////////////////////////////////////////////////////////
	//
	//	EPOLL thread worker
	//


	class IOWorkerEPOLL : public IOWorker
	{
	public:

		enum {
			MAX_EPOLL_EVENTS = 1000,
			MAX_EPOLL_WAIT = 500,
		};

	private:
		// Epoll handle
		int m_hEpoll;

	public:
		// Constructor/destructor
		IOWorkerEPOLL(AsyncIOPortSystem_Impl* ownerSystem, int id, int hEpoll);
		~IOWorkerEPOLL();

		int GetEpollHandle() {
			return m_hEpoll;
		}

		virtual Result RegisterIO(AsyncIOAdapter* cbInstance) override;
		virtual Result UnregisterIO(AsyncIOAdapter* cbInstance) override;

		virtual void Run() override;


		Result HandleRW(unsigned int events, AsyncIOAdapter* pCallBack);
	};




	////////////////////////////////////////////////////////////////////////////////
	//
	//	
	//

	class EPOLLSystem : public AsyncIOSystem_Reactor
	{
	private:

		// workers
		std::atomic<int> m_iWorkerAssignIndex;
		DynamicArray<IOWorkerEPOLL*> m_Workers;

	public:

		EPOLLSystem(IHeap& memMgr);

		virtual Result Initialize(uint netThreadCount) override;
		virtual void Terminate() override;

		// Register the socket to EPOLL
		virtual Result RegisterIO(AsyncIOAdapter* cbInstance) override;
		virtual Result UnregisterIO(AsyncIOAdapter* cbInstance) override;

		virtual const char* EventFlagToString(int32_t bufferSize, char* stringBuffer, uint32_t eventFlags) override;
	};





} // namespace AsyncIO
} // namespace SF


#endif
