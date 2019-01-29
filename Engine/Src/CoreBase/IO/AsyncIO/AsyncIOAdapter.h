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
#include "Memory/SFMemoryPool.h"
#include "Thread/SFThread.h"
#include "Object/SFLibraryComponent.h"


namespace SF {
	namespace AsyncIO {


		////////////////////////////////////////////////////////////////////////////////
		//
		// WriteBufferQueue  interface
		//

		struct IOBUFFER;
		struct IOBUFFER_WRITE;
		class WriteBufferQueue;


		////////////////////////////////////////////////////////////////////////////////
		//
		// AsyncIOAdapter  interface
		//

		class AsyncIOAdapter
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

			// Is registered to IO sub system
			std::atomic<IOStatus> m_IOStatus;

			WriteBufferQueue* m_pWriteQueues = nullptr;
			IOBUFFER_WRITE* m_pLatestWriteBuffer = nullptr;

			// Assigned IO worker thread index
			int m_AssignedIOWorker = -1;

			// Link to original IO handle
			const NativeHandle &m_IOHandle;

			// Read pending count
			std::atomic<int32_t> m_PendingReadCount;
			std::atomic<int32_t> m_PendingWriteCount;


		public:

			AsyncIOAdapter(IHeap& heap, const NativeHandle &IOHandleVariable);

			virtual ~AsyncIOAdapter();

			IHeap& GetIOHeap() { return m_Heap; }

			int GetAssignedIOWorker() const { return m_AssignedIOWorker; }
			void SetAssignedIOWorker(int assignedIOWorker);

			// casting, a bit faster than dynamic cast
			//virtual SharedObject* AsSharedObject() { return nullptr; }
			bool GetIsIORegistered() const { return m_IOStatus.load(std::memory_order_acquire) == IOStatus::Registered; }
			void OnIORegistered();
			void OnIOUnregistered();

			const CBFlags& GetIOFlags() const { return m_CBFlags; }
			CBFlags& GetIOFlagsEditable() { return m_CBFlags; }
			NativeHandle GetIOHandle() { return m_IOHandle; }

			// Write queue
			WriteBufferQueue* GetWriteQueue() { return m_pWriteQueues; }
			void SetWriteQueue(WriteBufferQueue* writeQueue) { Assert(writeQueue != nullptr && m_pWriteQueues == nullptr); m_pWriteQueues = writeQueue; }


			// Get pending Read count
			int32_t GetPendingReadCount() { return m_PendingReadCount.load(std::memory_order_relaxed); }
			int32_t IncPendingReadCount() { return m_PendingReadCount.fetch_add(1, std::memory_order_relaxed) + 1; }
			void DecPendingReadCount() { auto ReadCount = m_PendingReadCount.fetch_sub(1, std::memory_order_relaxed) - 1; unused(ReadCount); assert(ReadCount >= 0); }
			void ResetPendingReadCount() { m_PendingReadCount = 0; }

			int32_t GetPendingWriteCount() { return m_PendingWriteCount.load(std::memory_order_relaxed); }
			int32_t IncPendingWriteCount() { return m_PendingWriteCount.fetch_add(1, std::memory_order_relaxed) + 1; }
			void DecPendingWriteCount() { auto WriteCount = m_PendingWriteCount.fetch_sub(1, std::memory_order_relaxed) - 1; unused(WriteCount); assert(WriteCount >= 0); }
			void ResetPendingWriteCount() { m_PendingWriteCount = 0; }


			// Writable Event handler for Reactor Pattern IO
			virtual Result OnWriteReady();

			//virtual Result ProcessWriteQueue(); // merged to OnWriteReady
			virtual Result WriteBuffer(IOBUFFER_WRITE *pWriteBuffer) = 0;
			// Enqueue write buffer, For proactive system, it will directly call write buffer, otherwise enqueued to write queue
			virtual Result EnqueueWriteBuffer(IOBUFFER_WRITE* pWriteBuffer);

			// called when write completed
			virtual Result OnIOWriteCompleted(Result hrRes, IOBUFFER_WRITE *pIOBuffer) = 0;


			// Readable Event handler for Reactor Pattern IO
			// If you want to use default implementation of OnReadReady, you need to override this function
			virtual IOBUFFER_READ* CreateReadBuffer() { return nullptr; }

			// Readable Event handler for Reactor Pattern IO
			virtual Result OnReadReady();
			// Read buffer implementation
			virtual Result ReadBuffer(IOBUFFER_READ* pIOBuffer) = 0;
			// called when ReadBuffer is completed
			virtual Result OnIOReadCompleted(Result hrRes, IOBUFFER_READ* pIOBuffer) = 0;
		};


	} // AsyncIOPort
} // namespace SF


