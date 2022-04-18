////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2013 Kyungkun Ko
// 
// Author : Kyungkun Ko
//
// Description : Single Linked list
//
////////////////////////////////////////////////////////////////////////////////


#pragma once

#include "SFTypedefs.h"
#include "SFAssert.h"



namespace SF {

	//////////////////////////////////////////////////////////////////////////////////
	//
	//	Linked list
	//		- NOTE: Because std::atomic_thread_fence doesn't gurantee memory operation for non-std::atomic types OrderedLinkedList can't be thread safe
	//

	template< class KeyType >
	class OrderedLinkedList
	{
	public:

		// Single linked list
		struct Node {
			Node*		pNext;

			KeyType	Key;

			Node() {}
		};

		// iterator class
		class iterator
		{
		private:
			Node *m_pCur;

		public:
			iterator() : m_pCur(nullptr)
			{}
			iterator( const Node* pSrc ) : m_pCur(const_cast<Node*>(pSrc))
			{}
			iterator( const iterator& itSrc ) : m_pCur(itSrc.m_pCur)
			{}

			iterator& operator++()
			{
				if( m_pCur != nullptr ) m_pCur = m_pCur->pNext;
				return *this;
			}

			const iterator& operator++() const
			{
				if( m_pCur != nullptr ) m_pCur = m_pCur->pNext;
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

			bool operator !=( const iterator& op ) const
			{
				// both are end()
				if( !IsValid() && !op.IsValid() )
					return false;

				return ( (m_pCur != op.m_pCur) || ((m_pCur&&op.m_pCur)&&(m_pCur->pNext != op.m_pCur->pNext)) );
			}

			bool operator ==( const iterator& op ) const
			{
				// both are end()
				if( !IsValid() && !op.IsValid() )
					return true;

				return m_pCur == op.m_pCur;
			}
				
			iterator& operator = ( const iterator& itSrc )
			{
				m_pCur = itSrc.m_pCur;
				return *this;
			}

			friend class OrderedLinkedList<KeyType>;
		};

	private:
		// Header for node
		Node	m_Header;

		size_t	m_NumItems;

	public:

		// Constructor
		OrderedLinkedList()
			:m_NumItems(0)
		{
			memset( &m_Header, 0, sizeof(m_Header) );
		}

		virtual ~OrderedLinkedList()
		{
		}

		// Find Previous which is same or smaller Node
		Result FindPrevNode( KeyType keyValue, Node* &pPrevNode ) const
		{
			pPrevNode = const_cast<Node*>(&m_Header);
			for( ; pPrevNode->pNext != nullptr; pPrevNode = pPrevNode->pNext )
			{
				Node *pNextNode = pPrevNode->pNext;
				if (pNextNode->Key <= keyValue)
					return ResultCode::SUCCESS;
			}

			// No smaller or same node is found, return head
			AssertRel(pPrevNode == &m_Header || pPrevNode->Key > keyValue);
			return ResultCode::SUCCESS;
		}

		Result Insert( iterator itNode, KeyType keyValue, Node* pNew )
		{
			if( itNode.m_pCur == nullptr ) return ResultCode::INVALID_POINTER;

			return Insert( itNode.m_pCur, keyValue, pNew );
		}

		// insert after specific node, if null for pPrevNode, added at front
		Result Insert( Node* pPrevNode, KeyType keyValue, Node* pNew )
		{
			if( pPrevNode == nullptr )
				return ResultCode::INVALID_POINTER;

			if( pNew->pNext != nullptr )
				return ResultCode::UNEXPECTED;

			// This node should be in the list already
			if( pPrevNode == pNew || pPrevNode->pNext == pNew )
				return ResultCode::UNEXPECTED;

			if( pPrevNode != &m_Header )
			{
				AssertRel(pPrevNode->Key > keyValue);
			}

			pNew->Key = keyValue;
			pNew->pNext = pPrevNode->pNext;

			// This will make this operation as a thread safe operation for MT-read, single write
			//_WriteBarrier();
			std::atomic_thread_fence(std::memory_order_seq_cst);
			pPrevNode->pNext = pNew;

			m_NumItems++;

			return ResultCode::SUCCESS;
		}

		// Remove 
		
		Result Remove( iterator &itNode )
		{
			if( !itNode.IsValid() ) return ResultCode::INVALID_POINTER;

			return Remove( itNode.m_pCur, itNode.m_pCur->pNext );
		}
		
		Result FindAndRemove( Node* pSearchPrevNode, Node* pRemove )
		{
			if( pSearchPrevNode == nullptr )
				pSearchPrevNode = &m_Header;

			while( pSearchPrevNode != nullptr && pSearchPrevNode->pNext != pRemove )
			{
				pSearchPrevNode = pSearchPrevNode->pNext;
			}

			if( pSearchPrevNode == nullptr )
				return ResultCode::UNEXPECTED;

			pSearchPrevNode->pNext = pRemove->pNext;
			pRemove->pNext = nullptr;

			m_NumItems--;

			return ResultCode::SUCCESS;
		}

		Result Remove( Node* pPrevNode, Node* pRemove )
		{
			if( pPrevNode == nullptr )
				return ResultCode::INVALID_POINTER;

			if( pPrevNode->pNext != pRemove )
				return ResultCode::UNEXPECTED;

			pPrevNode->pNext = pRemove->pNext;
			pRemove->pNext = nullptr;

			m_NumItems--;

			return ResultCode::SUCCESS;
		}

		iterator begin() const
		{
			return iterator(&m_Header);
		}

		iterator end() const
		{
			return iterator();
		}

		size_t size() const
		{
			return m_NumItems;
		}
		
		Result erase( const iterator& itCur )
		{
			if( !itCur.IsValid() )
				return ResultCode::FAIL;

			return Remove( itCur.m_pCur, itCur.m_pCur->pNext );
		}
		
		bool empty()
		{
			return m_Header.pNext == nullptr;
		}
		
		void clear()
		{
			memset( &m_Header, 0, sizeof(m_Header) );
		}
	};

}; // namespace SF

