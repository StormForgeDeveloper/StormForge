////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2013 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Thread Synchronize
//
////////////////////////////////////////////////////////////////////////////////



#pragma once

#include "SFTypedefs.h"
#include "SFAssert.h"
#include "Multithread/SFSynchronization.h"
#include "Multithread/SFSystemSynchronization.h"



namespace SF {



	/////////////////////////////////////////////////////////////////////////////////
	//
	//	trait definition, used for UniqueKey or non UniqueKey trait
	//

	template<class DataType>
	inline bool DataTrait_NeedFenceForRW()
	{
		return true;
	}


	/////////////////////////////////////////////////////////////////////////////////
	//
	//	trait definition, used for UniqueKey or non UniqueKey trait
	//

	struct UniqueKeyTrait
	{
		enum Consts {
			UniqueKey = 1
		};
	};

	struct NonUniqueKeyTrait
	{
		enum Consts {
			UniqueKey = 0
		};
	};

	// Hash map data mappter
	template< typename KeyType, typename ItemType >
	struct MapItem
	{
		KeyType Key;
		ItemType Data;
	};


	//////////////////////////////////////////////////////////////////////////////////
	//
	//	Synchronization trait
	//

	// Synchronization trait, not thread safe
	struct ThreadSyncTraitNone
	{
		enum Consts {
			ThreadSafe = 0
		};

		typedef FakeTicketLock	TicketLockType;
	};

	// Synchronization trait, thread safe
	struct ThreadSyncTraitReadWrite
	{
		enum Consts {
			ThreadSafe = 1
		};
		typedef TicketLock	TicketLockType;
	};






} // namespace SF

