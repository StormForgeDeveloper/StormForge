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

#include "SFTypedefs.h"
#include "Container/SFCircularPageQueue.h"
#include "MemoryManager/SFMemoryPool.h"
#include "Component/SFLibraryComponent.h"
#include "Service/SFAsyncIOPortService.h"


namespace SF {
	namespace AsyncIO {



		class AsyncIOPortHandler;
		class AsyncIOPortSystem_Impl;



		////////////////////////////////////////////////////////////////////////////////
		//
		//	I/O Worker thread base class
		//


		class IOWorker : public Thread
		{
		private:
			AsyncIOPortSystem_Impl* m_Owner;
			int m_ID;

		public:
			// Constructor/destructor
			IOWorker(AsyncIOPortSystem_Impl* ownerSystem, int ID);
			~IOWorker();

			AsyncIOPortSystem_Impl* GetOwner() { return m_Owner; }
			int GetID() { return m_ID; }

			virtual Result RegisterIO(AsyncIOAdapter* cbInstance);
			virtual Result UnregisterIO(AsyncIOAdapter* cbInstance, const char* strReason);

		};

		////////////////////////////////////////////////////////////////////////////////
		//
		// AsyncIOPortSystem_Impl base
		//

		class AsyncIOPortSystem_Impl
		{
		private:

			IHeap& m_Heap;
			NativeHandle m_IOSystemHandle = INVALID_NATIVE_HANDLE_VALUE;

			// workers
			std::atomic<int> m_iWorkerAssignIndex;
			DynamicArray<IOWorker*> m_Workers;

		protected:

			void SetNativeIOSystemHandle(NativeHandle handle) { assert(m_IOSystemHandle == INVALID_NATIVE_HANDLE_VALUE); m_IOSystemHandle = handle; }

			void AddIOWorker(IOWorker*);

		public:

			AsyncIOPortSystem_Impl(IHeap& mgr);
			virtual ~AsyncIOPortSystem_Impl();

			NativeHandle GetNativeIOSystemHandle() { return m_IOSystemHandle; }
			IHeap& GetHeap() { return m_Heap; }

			IOWorker* GetNextWorkerAssignment();
			IOWorker* GetWorker(int id);

			virtual void CloseSystemHandle() { m_IOSystemHandle = INVALID_NATIVE_HANDLE_VALUE; }


			virtual Result Initialize(uint netThreadCount);
			virtual void Terminate();


			virtual Result RegisterIO(AsyncIOAdapter* cbInstance);
			virtual Result UnregisterIO(AsyncIOAdapter* cbInstance, const char* strReason);

			virtual const char* EventFlagToString(int32_t bufferSize, char* stringBuffer, uint32_t eventFlags) { return ""; }
		};





	} // AsyncIO
} // namespace SF


