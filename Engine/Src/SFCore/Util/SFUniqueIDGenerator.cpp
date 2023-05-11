////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2016 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : UID Generator
//
////////////////////////////////////////////////////////////////////////////////


#include "SFCorePCH.h"
#include "Util/SFUniqueIDGenerator.h"



namespace SF {

	UniqueIDGenerator::UniqueIDGenerator(IHeap& heap)
		: m_MemoryPool(nullptr)
		, m_CounterForID(1)
	{
		m_MemoryPool = MemoryPoolManager::GetMemoryPoolBySize(sizeof(Item));
	}

	UniqueIDGenerator::~UniqueIDGenerator()
	{
	}

	// Generate New ID
	uint UniqueIDGenerator::NewID()
	{
		uint uiNewID = 0;
		Item *pItem = (Item*)m_FreeIDs.Pop();

		if( pItem )
		{
			uiNewID = pItem->UID;
			m_MemoryPool->Free(pItem);
		}
		else
		{
			// gen a new ID
			uiNewID = (uint)m_CounterForID.fetch_add(1, std::memory_order_relaxed);

		}

		return uiNewID;
	}

	// Free Generated ID
	bool UniqueIDGenerator::FreeID( uint uiID )
	{
		void* pPtr = m_MemoryPool->Alloc(m_MemoryPool->GetAllocSize());
		Item *pItem = new(pPtr) Item;

		pItem->UID = uiID;

		m_FreeIDs.Push(pItem);

		return true;
	}


	// Clear all IDs
	void UniqueIDGenerator::ClearAllIDs()
	{
		m_FreeIDs.for_each( [](StackPool::Item *pItem) 
		{
			Item* pMyItem = (Item*)pItem;
			IHeap::Delete(pMyItem);
		});
		m_FreeIDs.Clear();
		m_CounterForID = 0;
	}

} // namespace SF
