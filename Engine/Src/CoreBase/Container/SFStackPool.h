////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2016 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Thread utilities Stack base object pool
//
////////////////////////////////////////////////////////////////////////////////


#pragma once

#include "SFTypedefs.h"
#include "SFAssert.h"
#include "Thread/SFSynchronization.h"
#include "Memory/SFMemory.h"



namespace SF {

		//////////////////////////////////////////////////////////////////////////////////
		//
		//	Stack base object pool with Multithread access
		//

		class StackPool
		{
		public:

			// Node that pool object must have or inherite
			struct Item
			{
				Item* pNext = nullptr;
			};



			// Header


		private:

			// Header
			std::atomic<Item*> m_head;

			// Size
			SyncCounter m_lSize;

			// thread ticketing ID
			Ticketing	m_Ticket;


		public:

			// Constructor
			StackPool();
			virtual ~StackPool();

			// Clear
			// NOTE: This method is not thread safe
			void Clear();

			// for_each functor
			// NOTE: This method is not thread safe
			template< class Functor >
			void for_each(Functor func);

			// GetSize
			size_t size() const { return m_lSize; }

			// Pop item 
			Item* Pop();

			// Push item
			void Push(Item* pEntry);

		};




} // namespace SF


#include "SFStackPool.inl"

