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
#include "IO/AsyncIO/AsyncIOPortWriteBufferQueue.h"



namespace SF {
	namespace AsyncIO {


		class AsyncIOPortSystem_Impl;
		class AsyncIOAdapter;


		// Generic read/write
		constexpr int OP_READ_BIT = 1 << 7;
		constexpr int OP_WRITE_BIT = 1 << 6;

		enum class IOBUFFER_OPERATION : uint8_t
		{
			OP_NONE = 0,

			OP_READ = OP_READ_BIT,
			OP_TCPREAD,
			OP_UDPREAD,

			OP_WRITE = OP_WRITE_BIT,
			OP_TCPWRITE,
			OP_UDPWRITE,

			OP_TCPACCEPT,
		};



		////////////////////////////////////////////////////////////////////////////////
		//
		//	Overlapped I/O structures
		//

		struct IOBUFFER
		{
			IOBUFFER_OPERATION Operation = IOBUFFER_OPERATION::OP_NONE;

			// Operation result size
			uint OperationSize = 0;

			// Operation buffer size
			uint OperationBufferSize = 0;

			// Operation Buffer pointer
			uint8_t* pOperationBuffer = nullptr;


			// Setup operation buffer
			void SetOperationBuffer(uint uiBuffSize, uint8_t* pBuff)
			{
				OperationBufferSize = uiBuffSize;
				pOperationBuffer = pBuff;
			}

			IOBUFFER() {}
			virtual ~IOBUFFER() {}
		};


		struct IOBUFFER_READ : public IOBUFFER
		{

			IOBUFFER_READ() {}
			virtual ~IOBUFFER_READ() {}
		};

		struct IOBUFFER_WRITE : public IOBUFFER
		{

			IOBUFFER_WRITE() {}
			virtual ~IOBUFFER_WRITE() {}
		};




		////////////////////////////////////////////////////////////////////////////////
		//
		//	Async IO Port system
		//


		class AsyncIOPortSystem : public LibraryComponent, public AsyncIOPortService
		{
		public:

			static constexpr StringCrc64 TypeName = "AsyncIOPortSystem";

		private:

			uint32_t m_NumThread;

			// Network memory manager
			Heap m_Heap;

			AsyncIOPortSystem_Impl* m_Impl;


		public:

			static inline bool IsProactorSystem()
			{
#if SF_PLATFORM == SF_PLATFORM_WINDOWS  // IOCP
				return true;
#else        // EPOLL/KQUEUE
				return false;
#endif
			}

			AsyncIOPortSystem(uint numThread);
			~AsyncIOPortSystem();

			virtual const StringCrc64& GetTypeName() const override { return TypeName; }

			// Initialize component
			virtual Result InitializeComponent() override;

			// Terminate component
			virtual void DeinitializeComponent() override;


			///////////////////////////////////////////////////////////////////////////////
			// 

			virtual IHeap& GetHeap() override { return *m_Heap.get(); }


			///////////////////////////////////////////////////////////////////////////////
			// Handler handling 

			virtual Result RegisterIO(AsyncIOAdapter* cbInstance) override;
			virtual Result UnregisterIO(AsyncIOAdapter* cbInstance) override;
		};




	} // AsyncIO
} // namespace SF


#include "IO/AsyncIO/AsyncIOPort_IOCP.h"
#include "IO/AsyncIO/AsyncIOPort_Reactor.h"


