////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) Kyungkun Ko
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
#include "Multithread/SFSynchronization.h"
#include "MemoryManager/SFMemoryPool.h"



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

		UniqueIDGenerator();
		~UniqueIDGenerator();

		// Generate New ID
		uint NewID();

		// Free Generated ID
		bool FreeID( uint uiID );

		// Clear all IDs
		void ClearAllIDs();

	private:

		// Free UID list
		StackPool	m_FreeIDs;
        StackPool	m_FreeIDItems;

		// Counter for new ID
		SyncCounter			m_CounterForID;
	};


	// Unique Id Handle
	class UniqueIDHandle
	{
	public:
		UniqueIDHandle()
		{
		}

		UniqueIDHandle(UniqueIDGenerator& generator)
			: m_Generator(&generator)
		{
			if (m_Generator)
			{
				m_UniqueId = m_Generator->NewID();
				assert(m_UniqueId);
			}
		}

		UniqueIDHandle(UniqueIDHandle&& src) noexcept
			: m_Generator(src.m_Generator)
		{
			m_UniqueId = src.m_UniqueId;

			src.m_Generator = nullptr;
			src.m_UniqueId = 0;
		}

		~UniqueIDHandle()
		{
			Reset();
		}

		SF_FORCEINLINE void Reset()
		{
			if (m_UniqueId != 0)
			{
				assert(m_Generator);
				m_Generator->FreeID(m_UniqueId);
				m_UniqueId = 0;
			}
		}

		SF_FORCEINLINE bool IsValid() const { return m_UniqueId != 0 && m_Generator != nullptr; }

		SF_FORCEINLINE operator uint32_t() const { return m_UniqueId; }


		SF_FORCEINLINE UniqueIDHandle& operator = (UniqueIDHandle&& src) noexcept
		{
			m_Generator = src.m_Generator;
			m_UniqueId = src.m_UniqueId;

			src.m_Generator = nullptr;
			src.m_UniqueId = 0;

			return *this;
		}

		SF_FORCEINLINE bool operator == (uint32_t value)
		{
			return m_UniqueId == value;
		}


	private:

		UniqueIDGenerator* m_Generator{};

		uint32_t m_UniqueId{};
	};

} // namespace SF


