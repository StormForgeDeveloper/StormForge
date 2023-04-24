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
#include "Container/SFDoubleLinkedListBase.h"


namespace SF {

	class IHeap;



	/////////////////////////////////////////////////////////////////////////////////
	//
	//	Generic Double linked list
	//


	template<class DataType, typename ThreadTrait = ThreadSyncTraitReadWrite >
	class DoubleLinkedListStaticT : public DoubleLinkedListBase<DoubleLinkedListNodeDataT<DataType>, ThreadTrait>
	{
	public:

		typedef DoubleLinkedListBase<DoubleLinkedListNodeDataT<DataType>, ThreadTrait> super;

		// linked list node
		typedef DoubleLinkedListNodeDataT<DataType> Node;

		// Iterator class
		class Iterator
		{
		private:
			Node *m_pCur;

		public:
			Iterator() : m_pCur(nullptr)
			{}
			Iterator(const Node* pSrc) : m_pCur(const_cast<Node*>(pSrc))
			{}
			Iterator(const Iterator& itSrc) : m_pCur(itSrc.m_pCur)
			{}

			Iterator& operator++()
			{
				if (m_pCur != nullptr) m_pCur = static_cast<Node*>(m_pCur->pNext);
				return *this;
			}

			const Iterator& operator++() const
			{
				if (m_pCur != nullptr) m_pCur = static_cast<Node*>(m_pCur->pNext);
				return *this;
			}

			bool IsValid() const
			{
				return m_pCur != nullptr;
			}

			Node* GetNode()
			{
				return m_pCur;
			}

			const Node* GetNode() const
			{
				return m_pCur;
			}

			DataType& operator* ()
			{
				AssertRel(m_pCur != nullptr);
				return m_pCur->Data;
			}

			const DataType& operator* () const
			{
				AssertRel(m_pCur != nullptr);
				return m_pCur->Data;
			}

			DataType* operator-> ()
			{
				AssertRel(m_pCur != nullptr);
				return &m_pCur->Data;
			}

			const DataType* operator-> () const
			{
				AssertRel(m_pCur != nullptr);
				return &m_pCur->Data;
			}

			bool operator !=(const Iterator& op) const
			{
				// both are end()
				if (!IsValid() && !op.IsValid())
					return false;

				return m_pCur != op.m_pCur;
			}

			bool operator ==(const Iterator& op) const
			{
				// both are end()
				if (!IsValid() && !op.IsValid())
					return true;

				return m_pCur->Data == op.m_pCur->Data;
			}

			Iterator& operator = (const Iterator& itSrc)
			{
				m_pCur = itSrc.m_pCur;
				return *this;
			}

			friend class DoubleLinkedListBase<DoubleLinkedListNodeDataT<DataType>, ThreadTrait>;
		};

		typedef Iterator iterator;

	public:

		// Constructor
		DoubleLinkedListStaticT()
		{
		}

		virtual ~DoubleLinkedListStaticT()
		{
		}

		// insert after specific node, if null for pPrevNode, added at front
		Result Add(Node* pNode)
		{
			return super::Add(pNode);
		}

		// Remove 
		Result Remove(Node* pNode)
		{
			return super::Remove(pNode);
		}

		Iterator begin()
		{
			return Iterator(this->m_Header);
		}

		Iterator end()
		{
			return Iterator();
		}

		size_t size()
		{
			return super::size();
		}

        Iterator erase(const Iterator& itCur)
        {
            if (!itCur.IsValid())
                return end();

            Iterator itNew(itCur);
            ++itNew;

            super::Remove(const_cast<Node*>(itCur.GetNode()));

            return itNew;
        }

		bool Empty()
		{
			return this->m_Header == nullptr;
		}

		virtual void Clear() override
		{
			super::Clear();
		}

		// If func returns false, it will terminate the loop
		template<class Func>
		void for_each(Func func)
		{
			super::for_each(
				[&func](DoubleLinkedListNode* pNode) -> bool
			{
				auto myNode = static_cast<Node*>(pNode);
				if (myNode == nullptr) return false;

				return func(myNode->Data);
			});
		}

		// If func returns false, that node will be removed
		template<class Func>
		void ForeachWithRemove(Func func)
		{
			super::ForeachWithRemove(
				[&func](DoubleLinkedListNodeDataT<DataType>* pNode) -> bool
				{
					auto myNode = static_cast<Node*>(pNode);
					if (myNode == nullptr) return false;

					return func(*myNode);
				}
			);
		}

	};


	/////////////////////////////////////////////////////////////////////////////////
	//
	//	Genric Double linked list
	//

	template<class DataType, typename ThreadTrait = ThreadSyncTraitReadWrite >
	class DoubleLinkedList : protected DoubleLinkedListBase<DoubleLinkedListNodeDataT<DataType>, ThreadTrait>
	{
	public:

		typedef DoubleLinkedListBase<DoubleLinkedListNodeDataT<DataType>, ThreadTrait> super;

		// linked list node
		typedef DoubleLinkedListNodeDataT<DataType> Node;

		// Iterator class
		class Iterator
		{
		private:
			Node *m_pCur;

		public:
			Iterator() : m_pCur(nullptr)
			{}
			Iterator(const Node* pSrc) : m_pCur(const_cast<Node*>(pSrc))
			{}
			Iterator(const Iterator& itSrc) : m_pCur(itSrc.m_pCur)
			{}

			Iterator& operator++()
			{
				if (m_pCur != nullptr) m_pCur = m_pCur->pNext;
				return *this;
			}

			const Iterator& operator++() const
			{
				if (m_pCur != nullptr) m_pCur = m_pCur->pNext;
				return *this;
			}

			bool IsValid() const
			{
				return m_pCur != nullptr;
			}

			Node* GetNode()
			{
				return m_pCur;
			}

			const Node* GetNode() const
			{
				return m_pCur;
			}

			DataType& operator* ()
			{
				AssertRel(m_pCur != nullptr);
				return m_pCur->Data;
			}

			const DataType& operator* () const
			{
				AssertRel(m_pCur != nullptr);
				return m_pCur->Data;
			}

			DataType* operator-> ()
			{
				AssertRel(m_pCur != nullptr);
				return &m_pCur->Data;
			}

			const DataType* operator-> () const
			{
				AssertRel(m_pCur != nullptr);
				return &m_pCur->Data;
			}

			bool operator !=(const Iterator& op) const
			{
				// both are end()
				if (!IsValid() && !op.IsValid())
					return false;

				return m_pCur != op.m_pCur;
			}

			bool operator ==(const Iterator& op) const
			{
				// both are end()
				if (!IsValid() && !op.IsValid())
					return true;

				return m_pCur->Data == op.m_pCur->Data;
			}

			Iterator& operator = (const Iterator& itSrc)
			{
				m_pCur = itSrc.m_pCur;
				return *this;
			}

			friend class DoubleLinkedListBase<DoubleLinkedListNodeDataT<DataType>, ThreadTrait>;
		};

		typedef Iterator iterator;

	private:

		IHeap& m_Heap;

	public:

		// Constructor
		DoubleLinkedList(IHeap& memoryManager = GetSystemHeap())
			: m_Heap(memoryManager)
		{
		}

		virtual ~DoubleLinkedList()
		{
		}

		// insert after specific node, if null for pPrevNode, added at front
		Result Add(const DataType& newData)
		{
			auto pNode = (Node*)m_Heap.Alloc(sizeof(Node));
			pNode->Data = newData;
			return Add(pNode);
		}

		// insert after specific node, if null for pPrevNode, added at front
		Result Add(DataType&& newData)
		{
			auto pNode = (Node*)m_Heap.Alloc(sizeof(Node));
			pNode->Data = std::forward<DataType>(newData);
			return Add(pNode);
		}

		// Remove 
		Result Remove(const DataType& removeData)
		{
			Node* found = nullptr;

			super::for_each(
				[&found, &removeData](DoubleLinkedListNode* pNode) -> bool
			{
				auto myNode = static_cast<Node*>(pNode);
				if (myNode == nullptr) return false;
				if (myNode->Data == removeData)
				{
					found = myNode;
					return false;
				}
				return true;
			});

			if (found != nullptr)
				return Remove(found);

			return ResultCode::SUCCESS_FALSE;
		}

		Iterator Begin()
		{
			return Iterator(this->m_Header);
		}

		Iterator End()
		{
			return Iterator();
		}

		size_t size()
		{
			return super::size();
		}

		Result Erase(const Iterator& itCur)
		{
			if (!itCur.IsValid())
				return ResultCode::FAIL;

			return Remove(itCur.m_pCur);
		}

		bool Empty()
		{
			return this->m_Header == nullptr;
		}

		virtual void Clear() override
		{
			super::Clear();
		}

		template<class Func>
		void for_each(Func func)
		{
			super::for_each(
				[&func](DoubleLinkedListNode* pNode) -> bool
			{
				auto myNode = static_cast<Node*>(pNode);
				if (myNode == nullptr) return false;

				return func(myNode->Data);
			});
		}

		template<class Func>
		void ForeachNode(Func func)
		{
			super::for_each(
				[&func](DoubleLinkedListNode* pNode) -> bool
			{
				auto myNode = static_cast<Node*>(pNode);
				if (myNode == nullptr) return false;

				return func(*myNode);
			});
		}
	};


}




