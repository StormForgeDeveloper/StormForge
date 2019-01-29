////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2016 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : UID Generator
//
////////////////////////////////////////////////////////////////////////////////


#pragma once


#include "SFTypedefs.h"
#include "Util/SFLog.h"
#include "Container/SFStackPool.h"
#include "Thread/SFSynchronization.h"
#include "Memory/SFMemoryPool.h"



namespace SF {

	////////////////////////////////////////////////////////////////////////
	//
	//	UID generator
	//      - This class generates 
	//

	class UniqueIDGenerator
	{
	public:

		// Item for stack pool
		struct Item : public StackPool::Item
		{
			uint UID;

			Item()
			{
				memset(this, 0, sizeof(Item));
			}
		};

	public:

		UniqueIDGenerator(IHeap& memoryManager);
		~UniqueIDGenerator();

		// Generate New ID
		uint NewID();

		// Free Generated ID
		bool FreeID( uint uiID );

		// Clear all IDs
		void ClearAllIDs();

	private:

		MemoryPool* m_MemoryPool;

		// Free UID list
		StackPool			m_FreeIDs;

		// Counter for new ID
		SyncCounter			m_CounterForID;
	};


}; // namespace BR


