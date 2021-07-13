////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Thread Synchronize
//
////////////////////////////////////////////////////////////////////////////////



#pragma once

#include "SFTypedefs.h"
#include "SFAssert.h"
#include "Container/SFContainerTraitBase.h"
#include "Container/SFSortedMap.h"
#include "Container/SFDualSortedMap.h"



namespace SF {




	template<class KeyType, class ValueType>
	struct ThreadSyncTraitNoneT
	{
		enum Consts {
			ThreadSafe = 0
		};
		typedef TicketLock	TicketLockType;
		typedef SortedMap<KeyType, ValueType> ItemContainer;
	};

	template<class KeyType, class ValueType>
	struct ThreadSyncTraitReadWriteT
	{
		enum Consts {
			ThreadSafe = 1
		};
		typedef TicketLock	TicketLockType;
		typedef DualSortedMap<KeyType, ValueType> ItemContainer;
	};

	// Synchronization trait, thread safe
	template<class KeyType, class ValueType>
	struct ThreadSyncTraitWriteT
	{
		enum Consts {
			ThreadSafe = 1
		};

		typedef WriteOnlyTicketLock	TicketLockType;
		typedef DualSortedMap<KeyType, ValueType> ItemContainer;
	};





} // namespace SF

