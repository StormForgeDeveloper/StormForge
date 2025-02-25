////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2017 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Async IO Port service
//
////////////////////////////////////////////////////////////////////////////////


#pragma once 

#include "SFTypedefs.h"
#include "MemoryManager/SFIMemoryManager.h"



namespace SF {

	namespace AsyncIO {

		struct IOBUFFER;
		class AsyncIOAdapter;
	};

	///////////////////////////////////////////////////////////////////////
	//
	//	AsyncIOPortService class
	//

	class AsyncIOPortService
	{
	protected:


	public:

		AsyncIOPortService() {  }
		virtual ~AsyncIOPortService() {}


		virtual IHeap& GetHeap() { return GetSystemHeap(); }


		///////////////////////////////////////////////////////////////////////////////
		// Handler handling 

		virtual Result RegisterIO(AsyncIO::AsyncIOAdapter* cbInstance) { return ResultCode::NOT_IMPLEMENTED; }
		virtual Result UnregisterIO(AsyncIO::AsyncIOAdapter* cbInstance, const char* strReason) { return ResultCode::NOT_IMPLEMENTED; }
	};

} // namespace SF

