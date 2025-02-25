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


#define USE_REACTOR_PATTERN (SF_PLATFORM == SF_PLATFORM_LINUX || SF_PLATFORM == SF_PLATFORM_ANDROID | SF_PLATFORM == SF_PLATFORM_IOS)


#include "SFTypedefs.h"
#include "Util/SFStrUtil.h"
#include "Container/SFHashTable.h"
#include "MemoryManager/SFMemoryPool.h"
#include "Multithread/SFThread.h"
#include "IO/AsyncIO/AsyncIOPortSystemImpl.h"




namespace SF {
	namespace AsyncIO {

		class AsyncIOAdapter;


		struct IOBUFFER_READ_REACTOR : public IOBUFFER_READ
		{

		};

		struct IOBUFFER_WRITE_REACTOR : public IOBUFFER_WRITE
		{

		};



		////////////////////////////////////////////////////////////////////////////////
		//
		//	Overlapped I/O structures
		//


		class AsyncIOSystem_Reactor : public AsyncIOPortSystem_Impl
		{
		private:



		public:

			AsyncIOSystem_Reactor(IHeap& heap);


			virtual Result Initialize(uint netThreadCount) override;
			virtual void Terminate() override;

			// Register the socket to EPOLL
			virtual Result RegisterIO(AsyncIOAdapter* cbInstance) override;
			virtual Result UnregisterIO(AsyncIOAdapter* cbInstance, const char* strReason) override;

			//virtual const char* EventFlagToString(int32_t bufferSize, char* stringBuffer, uint32_t eventFlags) override;
	};



	} // namespace AsyncIO
} // namespace SF





