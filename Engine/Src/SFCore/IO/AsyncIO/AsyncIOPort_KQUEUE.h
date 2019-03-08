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

#if USE_REACTOR_PATTERN && KQUEUE

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

	enum class IOBUFFER_OPERATION : uint8_t;



	////////////////////////////////////////////////////////////////////////////////
	//
	//	KQUEUE thread worker
	//


	class IOWorkerKQUEUE : public IOWorker
	{
	public:

		enum {
			MAX_KQUEUE_EVENTS = 1000,
			MAX_KQUEUE_WAIT = 500,
		};

	private:
		// KQUEUE handle
		int m_hKQUEUE;

	public:
		// Constructor/destructor
		IOWorkerKQUEUE(AsyncIOPortSystem_Impl* pOwnerSystem, int id, int hKQUEUE);

		~IOWorkerKQUEUE();

		int GetKQUEUEHandle() {
			return m_hKQUEUE;
		}

		virtual Result RegisterIOHandler(AsyncIOAdapter* cbInstance) override;
		virtual Result UnregisterIOHandler(AsyncIOAdapter* cbInstance) override;

		virtual void Run() override;


		Result HandleRW(unsigned int events, AsyncIOAdapter* pCallBack);
	};


	////////////////////////////////////////////////////////////////////////////////
	//
	//	
	//

	class KQUEUESystem : public AsyncIOSystem_Reactor
	{
	private:
	public:

		KQUEUESystem(IHeap& heap);

		virtual Result Initialize(uint netThreadCount) override;
		virtual void Terminate() override;




	};






} // namespace AsyncIO
} // namespace SF


#endif
