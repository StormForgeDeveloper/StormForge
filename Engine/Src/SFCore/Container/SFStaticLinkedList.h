////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2016 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : static hash map
//
////////////////////////////////////////////////////////////////////////////////


#pragma once


#include "SFTypedefs.h"
#include "SFAssert.h"
#include "MemoryManager/SFMemoryPool.h"
#include "Container/SFContainerTrait.h"


namespace SF {


		/////////////////////////////////////////////////////////////////////////////////
		//
		//	Thread safe hash map
		//

		template< typename ThreadTrait = ThreadSyncTraitReadWrite >
		class StaticLinkedList
		{
		public:

			// Single linked list
			struct Node {
				Node*		pNext;
			};

			// iterator class
			class iterator
			{
			private:
				Node *m_pCur;

			public:
				iterator() : m_pCur(nullptr)
				{}
				iterator(const Node* pSrc) : m_pCur(const_cast<Node*>(pSrc))
				{}
				iterator(const iterator& itSrc) : m_pCur(itSrc.m_pCur)
				{}

				iterator& operator++()
				{
					if (m_pCur != nullptr) m_pCur = m_pCur->pNext;
					return *this;
				}

				const iterator& operator++() const
				{
					if (m_pCur != nullptr) m_pCur = m_pCur->pNext;
					return *this;
				}

				bool IsValid() const
				{
					return m_pCur != nullptr && m_pCur->pNext != nullptr;
				}

				Node& operator* ()
				{
					AssertRel(m_pCur != nullptr && m_pCur->pNext != nullptr);
					return *m_pCur->pNext;
				}

				const Node& operator* () const
				{
					AssertRel(m_pCur != nullptr && m_pCur->pNext != nullptr);
					return *m_pCur->pNext;
				}

				Node* operator-> ()
				{
					AssertRel(m_pCur != nullptr && m_pCur->pNext != nullptr);
					return m_pCur->pNext;
				}

				const Node* operator-> () const
				{
					AssertRel(m_pCur != nullptr && m_pCur->pNext != nullptr);
					return m_pCur->pNext;
				}

				bool operator !=(const iterator& op) const
				{
					// both are end()
					if (!IsValid() && !op.IsValid())
						return false;

					return ((m_pCur != op.m_pCur) || ((m_pCur&&op.m_pCur) && (m_pCur->pNext != op.m_pCur->pNext)));
				}

				bool operator ==(const iterator& op) const
				{
					// both are end()
					if (!IsValid() && !op.IsValid())
						return true;

					return m_pCur == op.m_pCur;
				}

				iterator& operator = (const iterator& itSrc)
				{
					m_pCur = itSrc.m_pCur;
					return *this;
				}

				friend class StaticLinkedList<ThreadTrait>;
			};

		private:
			// Header for node
			Node	m_Header;

			size_t	m_NumItems;

		public:

			// Constructor
			StaticLinkedList()
				:m_NumItems(0)
			{
				memset(&m_Header, 0, sizeof(m_Header));
			}

			virtual ~StaticLinkedList()
			{
			}

			// Find Previous Node
			Result FindPrevNode(Node *pNode, Node* &pPrevNode)
			{
				pPrevNode = &m_Header;
				if (pNode == nullptr) return pPrevNode;

				for (; pPrevNode->pNext != nullptr; pPrevNode = pPrevNode->pNext)
				{
					Node *pNextNode = pPrevNode->pNext;
					if (pNextNode == pNode)
						break;
				}
				return ResultCode::SUCCESS;
			}

			// insert after specific node, if null for pPrevNode, added at front
			Result Insert(Node* pPrevNode, Node* pNew)
			{
				if (pPrevNode == nullptr)
					return ResultCode::INVALID_POINTER;

				if (pNew->pNext != nullptr)
					return ResultCode::UNEXPECTED;

				pNew->pNext = pPrevNode->pNext;

				// This will make this operation as thread safe operation for MT-read, single write
				//_WriteBarrier();
				std::atomic_thread_fence(std::memory_order_seq_cst);
				pPrevNode->pNext = pNew;

				m_NumItems++;

				return ResultCode::SUCCESS;
			}

			// insert after specific node, if null for pPrevNode, added at front
			Result Add(Node* pNew)
			{
				auto pPrevNode = &m_Header;
				if (pNew->pNext != nullptr)
					return ResultCode::UNEXPECTED;

				pNew->pNext = pPrevNode->pNext;

				// This will make this operation as thread safe operation for MT-read, single write
				//_WriteBarrier();
				std::atomic_thread_fence(std::memory_order_seq_cst);
				pPrevNode->pNext = pNew;

				m_NumItems++;

				return ResultCode::SUCCESS;
			}

			// Remove 
			Result Remove(Node* pPrevNode, Node* pRemove)
			{
				if (pPrevNode == nullptr)
					return ResultCode::INVALID_POINTER;

				if (pPrevNode->pNext != pRemove)
					return ResultCode::UNEXPECTED;

				pPrevNode->pNext = pRemove->pNext;
				pRemove->pNext = nullptr;

				m_NumItems--;

				return ResultCode::SUCCESS;
			}

			iterator begin()
			{
				return iterator(&m_Header);
			}

			iterator end()
			{
				return iterator();
			}

			size_t size()
			{
				return m_NumItems;
			}

			Result erase(const iterator& itCur)
			{
				if (!itCur.IsValid())
					return ResultCode::FAIL;

				return Remove(itCur.m_pCur, itCur.m_pCur->pNext);
			}

			bool empty()
			{
				return m_Header.pNext == nullptr;
			}

			void clear()
			{
				memset(&m_Header, 0, sizeof(m_Header));
			}
		};


}




