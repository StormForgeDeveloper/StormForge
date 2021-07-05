////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2016 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Double linked list
//
////////////////////////////////////////////////////////////////////////////////


#pragma once


#include "SFTypedefs.h"
#include "SFAssert.h"
#include "Container/SFContainerTraitBase.h"


namespace SF {


	/////////////////////////////////////////////////////////////////////////////////
	//
	//	Double linked list with external memory control
	//

	// linked list node
	struct DoubleLinkedListNode
	{
		DoubleLinkedListNode*		pPrev = nullptr;
		DoubleLinkedListNode*		pNext = nullptr;

		bool NotInAnyList()
		{
			return pPrev == nullptr && pNext == nullptr;
		}
	};

	template<class DataType>
	struct DoubleLinkedListNodeDataT : public DoubleLinkedListNode
	{
		DataType Data;

		DoubleLinkedListNodeDataT()
		{
			Data = DataType{};
		}

		DoubleLinkedListNodeDataT(const DataType& pObj)
			: Data(pObj)
		{
		}

		DoubleLinkedListNodeDataT(DataType&& pObj)
			: Data(std::forward<DataType>(pObj))
		{
		}

		virtual ~DoubleLinkedListNodeDataT() = default;
	};


	template<class NodeType, typename ThreadTrait = ThreadSyncTraitReadWrite >
	class DoubleLinkedListBase
	{
	public:

		typedef NodeType Node;

		typedef typename ThreadTrait::TicketLockType TicketLockType;

	protected:
		// Header for node
		Node*	m_Header;

	private:

		size_t	m_NumItems;

		TicketLockType m_Lock;

	public:

		// Constructor
		DoubleLinkedListBase()
			: m_Header(nullptr)
			, m_NumItems(0)
		{
			//memset(&m_Header, 0, sizeof(m_Header));
		}

		virtual ~DoubleLinkedListBase()
		{
		}


		bool IsInTheList(Node* pNode)
		{

			return m_Header == pNode || pNode->pNext != nullptr || pNode->pPrev != nullptr;
		}

		// insert after specific node, if null for pPrevNode, added at front
		Result Insert(Node* pPrevNode, Node* pNew)
		{
			TicketScopeLockT<TicketLockType> scopeLock(TicketLock::LockMode::Exclusive, m_Lock);

			assert(pNew != (Node*)0xdddddddddddddddd);

			if (IsInTheList(pNew))
			{
				assert(false);
				return ResultCode::UNEXPECTED;
			}

			if (pPrevNode == nullptr)
			{
				pNew->pNext = m_Header;
				if (m_Header != nullptr)
				{
					m_Header->pPrev = pNew;

				}
				m_Header = pNew;
			}
			else
			{
				if (pPrevNode->pNext == nullptr && pPrevNode->pPrev == nullptr)
					return ResultCode::UNEXPECTED;

				auto nexNode = (Node*)pPrevNode->pNext;
				pNew->pNext = nexNode;
				if (nexNode != nullptr)
				{
					nexNode->pPrev = pNew;
				}
				pPrevNode->pNext = pNew;
				pNew->pPrev = pPrevNode;
			}

			m_NumItems++;

			if constexpr (ThreadTrait::ThreadSafe)
			{
				// This will make this operation as thread safe operation for MT-read, single write
				std::atomic_thread_fence(std::memory_order_seq_cst);
			}

			return ResultCode::SUCCESS;
		}

		// insert after specific node, if null for pPrevNode, added at front
		Result Add(Node* pNew)
		{
			return Insert(nullptr, pNew);
		}

		Result Remove(Node* pRemove)
		{
			TicketScopeLockT<TicketLockType> scopeLock(TicketLock::LockMode::Exclusive, m_Lock);
			return RemoveNoLock(pRemove);
		}

		// Remove 
		Result RemoveNoLock(Node* pRemove)
		{
			if (pRemove == nullptr)
				return ResultCode::INVALID_POINTER;

			if (!IsInTheList(pRemove))
			{
				return ResultCode::NOT_EXIST;
			}

			if (pRemove == m_Header)
			{
				assert(pRemove->pNext != (Node*)0xdddddddddddddddd);
				m_Header = (Node*)pRemove->pNext;
			}

			auto pPrevNode = (Node*)pRemove->pPrev;
			auto pNext = (Node*)pRemove->pNext;
			if (pPrevNode != nullptr)
				pPrevNode->pNext = pNext;
			if (pNext != nullptr)
				pNext->pPrev = pPrevNode;

			pRemove->pPrev = nullptr;
			pRemove->pNext = nullptr;

			m_NumItems--;

			if constexpr (ThreadTrait::ThreadSafe)
			{
				// This will make this operation as thread safe operation for MT-read, single write
				std::atomic_thread_fence(std::memory_order_seq_cst);
			}

			return ResultCode::SUCCESS;
		}

		Node* RemoveFirst()
		{
			TicketScopeLockT<TicketLockType> scopeLock(TicketLock::LockMode::Exclusive, m_Lock);
			auto pRemove = m_Header;
			if (RemoveNoLock(m_Header))
				return nullptr;
			return pRemove;
		}

		size_t size()
		{
			return m_NumItems;
		}

		bool Empty()
		{
			return m_Header == nullptr;
		}

		virtual void Clear()
		{
			m_Header = nullptr;
		}

		// If func returns false, it will terminate the loop
		template<class Func>
		void for_each(Func func)
		{
			TicketScopeLockT<TicketLockType> scopeLock(TicketLock::LockMode::NonExclusive, m_Lock);

			auto pCur = m_Header;
			while (pCur != nullptr)
			{
				auto pNext = (Node*)pCur->pNext;
				if (!func(pCur)) return;
				pCur = pNext;
			}
		}

		// If func returns false, that node will be removed
		template<class Func>
		void ForeachWithRemove(Func func)
		{
			TicketScopeLockT<TicketLockType> scopeLock(TicketLock::LockMode::Exclusive, m_Lock);

			auto pCur = m_Header;
			while (pCur != nullptr)
			{
				auto pNext = (Node*)pCur->pNext;
				if (!func(pCur))
				{
					RemoveNoLock(pCur);
				}
				pCur = pNext;
			}
		}
	};



}




