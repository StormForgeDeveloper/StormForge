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
#include "ResultCode/SFResultCodeSystem.h"


namespace SF
{

		/////////////////////////////////////////////////////////////////////////////////
		//
		//	Thread safe hash map
		//
		template<class NodeType>
		class StaticDoubleLinkedListT
		{
		public:

			typedef NodeType Node;

			// iterator class
			class iterator
			{
			private:
				mutable Node *m_pHeader;
				mutable Node *m_pCur;

			public:
				iterator() : m_pHeader(nullptr), m_pCur(nullptr)
				{}
				iterator(const Node* pHeader, const Node* pCur)
					: m_pHeader(const_cast<Node*>(pHeader))
					, m_pCur(const_cast<Node*>(pCur))
				{}
				iterator(const iterator& itSrc)
					: m_pHeader(itSrc.m_pHeader)
					, m_pCur(itSrc.m_pCur)
				{}

				iterator& operator++()
				{
					if (m_pCur != nullptr) m_pCur = static_cast<Node*>(m_pCur->pNext);
					return *this;
				}

				const iterator& operator++() const
				{
					if (m_pCur != nullptr) m_pCur = static_cast<Node*>(m_pCur->pNext);
					return *this;
				}

				bool IsValid() const
				{
					return m_pCur != nullptr && m_pCur != m_pHeader;
				}

				Node* operator* ()
				{
					AssertRel(m_pCur != nullptr);
					return m_pCur != m_pHeader ? m_pCur : nullptr;
				}

				const Node* operator* () const
				{
					AssertRel(m_pCur != nullptr);
					return m_pCur != m_pHeader ? m_pCur : nullptr;
				}

				bool operator !=(const iterator& op) const
				{
					return m_pCur != op.m_pCur;
				}

				bool operator ==(const iterator& op) const
				{
					return m_pCur == op.m_pCur;
				}

				iterator& operator = (const iterator& itSrc)
				{
					m_pCur = itSrc.m_pCur;
					return *this;
				}

				friend class StaticDoubleLinkedListT;
			};

		private:
			// Header for node
			Node	m_Header;

			// Number of items
			size_t	m_NumItems = 0;

		public:

			// Constructor
			StaticDoubleLinkedListT()
			{
				m_Header.pPrev = &m_Header;
				m_Header.pNext = &m_Header;
			}

			virtual ~StaticDoubleLinkedListT()
			{
				Clear();
			}

			// pop one item from front
			Node* pop_front()
			{
				if (m_Header.pNext == &m_Header)
					return nullptr;

				auto pRemoved = m_Header.pNext;
				Remove(static_cast<Node*>(m_Header.pNext));

				return static_cast<Node*>(pRemoved);
			}

			// pop one item from back
			Node* pop_back()
			{
				if (m_Header.pPrev == &m_Header)
					return nullptr;

				auto pRemoved = m_Header.pPrev;
				Remove(static_cast<Node*>(m_Header.pPrev));

				return static_cast<Node*>(pRemoved);
			}

			// insert after specific node, if null for pPrevNode, added at front
			Result Add(Node* pNew)
			{
				if (pNew == nullptr)
					return ResultCode::INVALID_POINTER;

				if (pNew->pNext != nullptr || pNew->pPrev != nullptr)
					return ResultCode::UNEXPECTED;

				pNew->pPrev = &m_Header;
				pNew->pNext = m_Header.pNext;
				m_Header.pNext = pNew;
				Assert(pNew->pNext->pPrev == &m_Header);
				pNew->pNext->pPrev = pNew;

				m_NumItems++;

				return ResultCode::SUCCESS;
			}

			// Remove 
			Result Remove(Node* pRemove)
			{
				if (pRemove == nullptr)
					return ResultCode::INVALID_POINTER;

				if (pRemove == &m_Header)
					return ResultCode::INVALID_ARG;

				if (pRemove->pNext == nullptr || pRemove->pPrev == nullptr)
					return ResultCode::UNEXPECTED;

				pRemove->pPrev->pNext = pRemove->pNext;
				pRemove->pNext->pPrev = pRemove->pPrev;
				pRemove->pNext = nullptr;
				pRemove->pPrev = nullptr;

				m_NumItems--;

				return ResultCode::SUCCESS;
			}

			void Clear()
			{
				auto pNext = m_Header.pNext;
				for (auto pCur = pNext; pCur; pCur = pNext)
				{
					pNext = pCur->pNext;

					pCur->RemoveFromList();
				}

				m_Header = {};
				m_Header.pPrev = &m_Header;
				m_Header.pNext = &m_Header;
			}

			// add item to the front
			Result push_front(Node* pNew)
			{
				if (pNew == nullptr)
					return ResultCode::INVALID_POINTER;

				if (pNew == &m_Header)
					return ResultCode::INVALID_ARG;

				if (pNew->pNext != nullptr || pNew->pPrev != nullptr)
					return ResultCode::UNEXPECTED;

				pNew->pPrev = &m_Header;
				pNew->pNext = m_Header.pNext;
				m_Header.pNext = pNew;
				Assert(pNew->pNext->pPrev == &m_Header);
				pNew->pNext->pPrev = pNew;

				m_NumItems++;

				return ResultCode::SUCCESS;
			}

			// add item to the back
			Result push_back(Node* pNew)
			{
				if (pNew == nullptr)
					return ResultCode::INVALID_POINTER;

				if (pNew == &m_Header)
					return ResultCode::INVALID_ARG;

				if (pNew->pNext != nullptr || pNew->pPrev != nullptr)
					return ResultCode::UNEXPECTED;

				pNew->pPrev = m_Header.pPrev;
				pNew->pNext = &m_Header;
				m_Header.pPrev->pNext = pNew;
				m_Header.pPrev = pNew;
				//Assert(pNew->pNext->pPrev == &m_Header);
				//pNew->pNext->pPrev = pNew;

				m_NumItems++;

				return ResultCode::SUCCESS;
			}

			iterator begin() const
			{
				return iterator(&m_Header, static_cast<Node*>(m_Header.pNext));
			}

			iterator end() const
			{
				return iterator(&m_Header, &m_Header);
			}

			SF_FORCEINLINE size_t size() const
			{
				return m_NumItems;
			}

			SF_FORCEINLINE Result erase(const iterator& itCur)
			{
				if (!itCur.IsValid())
					return ResultCode::FAIL;

				return Remove(itCur.m_pCur);
			}

			SF_FORCEINLINE bool IsEmpty() const
			{
				return m_Header.pNext == m_Header.pPrev;
			}

			void clear()
			{
				Clear();
			}

			StaticDoubleLinkedListT& operator =(StaticDoubleLinkedListT&& src)
			{
				Clear();
				
				if (src.m_Header.pNext != &src.m_Header)
				{
					auto firstNode = src.m_Header.pNext;
					auto lastNode = src.m_Header.pPrev;
					m_Header.pNext = firstNode;
					firstNode->pPrev = &m_Header;
					m_Header.pPrev = lastNode;
					lastNode->pNext = &m_Header;
				}
				else
				{
					assert(src.m_NumItems == 0);// empty list
				}
				m_NumItems = src.m_NumItems;

				// clear out src
				src.m_Header.Data = {};
				src.m_Header.pPrev = &src.m_Header;
				src.m_Header.pNext = &src.m_Header;
				src.m_NumItems = 0;

				return *this;
			}
		};


		using StaticDoubleLinkedList = StaticDoubleLinkedListT<DoubleLinkedListNode>;
}




