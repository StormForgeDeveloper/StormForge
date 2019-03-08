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

#if SF_PLATFORM == SF_PLATFORM_WINDOWS

#include "SFTypedefs.h"
#include "IO/AsyncIO/AsyncIOPort.h"
#include "IO/AsyncIO/AsyncIOPortSystemImpl.h"


namespace SF {
	namespace AsyncIO {

		enum class IOBUFFER_OPERATION : uint8_t;

		////////////////////////////////////////////////////////////////////////////////
		//
		//	Overlapped I/O structures
		//

		struct IOBUFFER_IOCP : public IOBUFFER, public WSAOVERLAPPED
		{
			IOBUFFER_OPERATION Operation = IOBUFFER_OPERATION::OP_NONE;

			// Operation size
			uint32_t OperationSize = 0;


			// Clear Buffer
			void ClearBuffer();
		};





		////////////////////////////////////////////////////////////////////////////////
		//
		//	IOCP thread worker
		//
		class IOCPWorker : public IOWorker
		{
		public:
			// Constructor/destructor
			IOCPWorker(AsyncIOPortSystem_Impl* ownerSystem, int id) : IOWorker(ownerSystem, id) {}
			~IOCPWorker() {}

			virtual void Run() override;
		};



		//////////////////////////////////////////////////////////////////
		//
		//	IOCP System, Proactor system
		//

		class IOCPSystem : public AsyncIOPortSystem_Impl
		{
		private:

			// IOCP system open reference count
			SyncCounter m_RefCount;

			// IOCP worker thread list
			std::vector<IOCPWorker*> m_pWorkers;

			// global statistic
			SyncCounter m_NumReadWait;
			SyncCounter m_NumWriteWait;

		public:
			IOCPSystem(IHeap& memoryManager);
			~IOCPSystem();

			virtual Result Initialize(uint netThreadCount) override;
			virtual void Terminate() override;

			virtual void CloseSystemHandle() override;

		};



	}
} // namespace SF

#endif

