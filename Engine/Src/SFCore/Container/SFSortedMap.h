////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2014 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Sorted map
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "SFTypedefs.h"
#include "Object/SFSharedObject.h"
#include "Object/SFObjectPool.h"
#include "Multithread/SFSynchronization.h"
#include "Container/SFArray.h"
#include "Container/SFSortedMap_Base.h"

namespace SF {


		///////////////////////////////////////////////////////////
		//
		//	SortedMap
		//	- Implementation of AVLTree
		//

		template<class KeyType, class ValueType>
		class SortedMap
		{
		public:

			typedef CounterType SynchronizeCounterType;

			enum {
				BalanceTolerance = 8,
				MaxRebalancingTry = 20
			};


			class MapNode;
			typedef MapNode* ReferenceAccessPoint;

			class MapNode : public ObjectPoolObject
			{
			public:
				KeyType Key{};
				ValueType Value{};

				int Balance = 0;
				int DepthOfChildren = 0;
				// Number of nodes - include child
				int NumberOfChildren = 0;

				ReferenceAccessPoint Left = nullptr;
				ReferenceAccessPoint Right = nullptr;

				MapNode()
				{
				}

				void SetValue()
				{
					Balance = 0;
					DepthOfChildren = 0;
					NumberOfChildren = 0;
					Key = KeyType{};
					Value = ValueType{};
					Left = nullptr;
					Right = nullptr;
				}

				void SetValue(KeyType key, ValueType value)
				{
					Balance = 0;
					DepthOfChildren = 0;
					NumberOfChildren = 0;
					Key = key;
					Value = value;
					Left = nullptr;
					Right = nullptr;
				}

				int UpdateBalanceFactor();

				SF_FORCEINLINE void ValidateUpdateSerial(uint32_t updateSerialExpected) {}

			};

			typedef ObjectPoolT<MapNode> MyObjectPool;

		private:

			using OperationTraversalHistory = SortedMapTraversalHistoryT<MapNode, ReferenceAccessPoint>;



		private:

			// Root node
			ReferenceAccessPoint m_Root;

			// item count in the tree
			SynchronizeCounterType m_ItemCount;

			bool m_DeleteNodePool;

			IHeap& m_Heap;
			MyObjectPool *m_pNodePool;

		public:

			SortedMap(IHeap& heap = GetSystemHeap());
			~SortedMap();

			IHeap& GetHeap() const { return m_Heap; }

			void ClearMap();
			void Reset();

			// Insert a key
			Result Insert(KeyType key, const ValueType& value, int64_t *insertedOrder = nullptr);

			// Remove an item and return the removed value
			Result Remove(KeyType key, ValueType& value);

			// Find a key value
			Result Find(KeyType key, ValueType& value, int64_t *pOrder = nullptr) const;
			Result FindRef(KeyType key, const ValueType*& pValue, int64_t* pOrder = nullptr) const
			{
				return const_cast<SortedMap*>(this)->FindRef(key, pValue, pOrder);
			}
			Result FindRef(KeyType key, ValueType*& pValue, int64_t* pOrder = nullptr);
			Result FindInWriteTree(KeyType key, ValueType& value) const { return Find(key, value); }

			// Same as insert, replaces if mapping is exist
			Result Emplace(KeyType key, const ValueType& value);

			// get number of values
			size_t size() const { return (size_t)m_ItemCount; }

			class iterator
			{
			public:

				iterator()
				{}

				iterator(IHeap& heap, SortedMap* pContainer, const MapNode* pRootNode, int startOrderIndex)
					: m_pContainer(pContainer)
					, m_pCurNode(pRootNode)
					, m_TravelHistory(const_cast<MapNode*>(pRootNode), pContainer->m_ItemCount)
				{
					m_TravelHistory.Clear();
					m_TravelHistory.SetPreserveDataOnResize(true);

					// find start point
					while(m_pCurNode)
					{
						m_TravelHistory.AddHistory(m_pCurNode);

						auto right = m_pCurNode->Right;
						auto rightNumChildren = right != nullptr ? right->NumberOfChildren : -1;
						if (rightNumChildren >= startOrderIndex)
						{
							m_pCurNode = right;
						}
						else
						{
							if (rightNumChildren >= 0)
							{
								startOrderIndex -= rightNumChildren + 1;
							}
							if (startOrderIndex == 0) // current node is the start point
								break;

							startOrderIndex--;
							auto left = m_pCurNode->Left;
							m_pCurNode = left;
						}

					} // while (m_pCurNode != nullptr);

				}

				iterator(const iterator& src)
					: m_pContainer(src.m_pContainer)
					, m_pCurNode(src.m_pCurNode)
				{
					m_TravelHistory = src.m_TravelHistory;
				}

				iterator& operator++()
				{
					if (m_pCurNode == nullptr)
						return *this;

					auto left = m_pCurNode->Left;
					if (left != nullptr)
					{
						m_pCurNode = m_pContainer->FindBiggestNode(m_TravelHistory, left);
					}
					else // this is a leap node pop up
					{
						m_TravelHistory.RemoveLastHistory();
						const MapNode* parent = nullptr;
						do
						{
							parent = m_TravelHistory.GetLastHistory();
							if (parent == nullptr)
							{
								// nothing to process
								m_pCurNode = nullptr;
								break;
							}

							if (m_pCurNode == parent->Left)
								m_TravelHistory.RemoveLastHistory();
							else
							{
								m_pCurNode = parent;
								break;
							}

							m_pCurNode = parent;

						} while (parent != nullptr);
					}

					return *this;
				}

				SF_FORCEINLINE ValueType& operator *()
				{
					assert(m_pCurNode != nullptr);
					return const_cast<MapNode*>(m_pCurNode)->Value;
				}

				SF_FORCEINLINE ValueType* operator ->()
				{
					assert(m_pCurNode != nullptr);
					return &m_pCurNode->Value;
				}

				SF_FORCEINLINE bool operator == (const iterator& src) const { return m_pCurNode == src.m_pCurNode; }
				SF_FORCEINLINE bool operator != (const iterator& src) const { return m_pCurNode != src.m_pCurNode; }

				iterator& operator = (const iterator& src)
				{
					m_pCurNode = src.m_pCurNode;
					m_TravelHistory.Reset();
					m_TravelHistory = src.m_TravelHistory;
					return *this;
				}

			private:

				SortedMap* m_pContainer{};

				const MapNode* m_pCurNode{};

				OperationTraversalHistory m_TravelHistory;
			};


			SF_FORCEINLINE iterator begin() const { return iterator(GetHeap(), const_cast<SortedMap*>(this), const_cast<ReferenceAccessPoint&>(m_Root), 0); }
			SF_FORCEINLINE iterator end() const { return iterator(); }

			// enumerate the values
			//Result ForeachOrder(int startOrderIndex, uint count, const std::function<bool(const KeyType&, const ValueType&)>& functor);
			template<class Func>
			Result ForeachOrder(int startOrderIndex, uint count, Func functor) const
			{
				const MapNode* pCurNode = m_Root;
				if (pCurNode == nullptr)
					return ResultCode::SUCCESS;

				OperationTraversalHistory travelHistory(m_Root, m_ItemCount);
				travelHistory.Clear();
				travelHistory.SetPreserveDataOnResize(true);

				// find start point
				do
				{
					travelHistory.AddHistory(pCurNode);

					auto right = pCurNode->Right;
					auto rightNumChildren = right != nullptr ? right->NumberOfChildren : -1;
					if (rightNumChildren >= startOrderIndex)
					{
						pCurNode = right;
					}
					else
					{
						if (rightNumChildren >= 0)
						{
							startOrderIndex -= rightNumChildren + 1;
						}
						if (startOrderIndex == 0) // current node is the start point
							break;

						startOrderIndex--;
						auto left = pCurNode->Left;
						pCurNode = left;
					}

				} while (pCurNode != nullptr);

				if (pCurNode == nullptr)
					return ResultCode::SUCCESS;


				// iterate
				do
				{
					if (!functor(pCurNode->Key, pCurNode->Value))
						return ResultCode::SUCCESS;

					count--;
					if (count == 0)
						break;

					auto left = pCurNode->Left;
					if (left != nullptr)
					{
						pCurNode = FindBiggestNode(travelHistory, left);
					}
					else // this is a leap node pop up
					{
						travelHistory.RemoveLastHistory();
						const MapNode* parent = nullptr;
						do
						{
							parent = travelHistory.GetLastHistory();
							if (parent == nullptr)
							{
								// nothing to process
								pCurNode = nullptr;
								break;
							}

							if (pCurNode == parent->Left)
								travelHistory.RemoveLastHistory();
							else
							{
								pCurNode = parent;
								break;
							}

							pCurNode = parent;

						} while (parent != nullptr);
					}

				} while (pCurNode != nullptr);


				travelHistory.SetPreserveDataOnResize(false);

				return ResultCode::SUCCESS;
			}

			//Result ForeachReverseOrder(int startOrderIndex, uint count, const std::function<bool(const KeyType&, const ValueType&)>& functor);
			template<class Func>
			Result ForeachReverseOrder(int startOrderIndex, uint count, Func functor)
			{
				MapNode* pCurNode = m_Root;
				if (pCurNode == nullptr)
					return ResultCode::SUCCESS;

				OperationTraversalHistory travelHistory(m_Root, m_ItemCount);
				travelHistory.Clear();
				travelHistory.SetPreserveDataOnResize(true);

				// find start point
				do
				{
					travelHistory.AddHistory(pCurNode);

					auto left = pCurNode->Left;
					auto leftNumChildren = left != nullptr ? left->NumberOfChildren : -1;
					if (leftNumChildren >= startOrderIndex)
					{
						pCurNode = left;
					}
					else
					{
						if (leftNumChildren >= 0)
						{
							startOrderIndex -= leftNumChildren + 1;
						}
						if (startOrderIndex == 0) // current node is the start point
							break;

						startOrderIndex--;
						auto right = pCurNode->Right;
						pCurNode = right;
					}

				} while (pCurNode != nullptr);

				if (pCurNode == nullptr)
					return ResultCode::SUCCESS;


				// iterate
				do
				{
					if (!functor(pCurNode->Key, pCurNode->Value))
						return ResultCode::SUCCESS;

					count--;
					if (count == 0)
						break;

					auto right = pCurNode->Right;
					if (right != nullptr)
					{
						pCurNode = FindSmallestNode(travelHistory, right);
					}
					else // this is a leap node pop up
					{
						travelHistory.RemoveLastHistory();
						const MapNode* parent = nullptr;
						do
						{
							parent = travelHistory.GetLastHistory();
							if (parent == nullptr)
							{
								// nothing to process
								pCurNode = nullptr;
								break;
							}

							if (pCurNode == parent->Right)
								travelHistory.RemoveLastHistory();
							else
							{
								pCurNode = const_cast<MapNode*>(parent);
								break;
							}

							pCurNode = const_cast<MapNode*>(parent);

						} while (parent != nullptr);
					}

				} while (pCurNode != nullptr);


				travelHistory.SetPreserveDataOnResize(false);

				return ResultCode::SUCCESS;
			}

			// for interface match
			Result CommitChanges() { return ResultCode::SUCCESS; }


		private:

			// find parent node or candidate
			Result FindNode(OperationTraversalHistory &travelHistory, KeyType key, const MapNode* &pNode) const;

			const MapNode* FindSmallestNode(OperationTraversalHistory& travelHistory, const MapNode* pRootNode) const 
			{
				return const_cast<SortedMap*>(this)->FindSmallestNode(travelHistory, pRootNode);
			}
			MapNode* FindSmallestNode(OperationTraversalHistory& travelHistory, const MapNode* pRootNode);
			const MapNode* FindBiggestNode(OperationTraversalHistory &travelHistory, const MapNode* pRootNode) const
			{
				return const_cast<SortedMap*>(this)->FindBiggestNode(travelHistory, pRootNode);
			}
			MapNode* FindBiggestNode(OperationTraversalHistory& travelHistory, const MapNode* pRootNode);

			// Update valance factor and return new balance value
			void FixupBalance(OperationTraversalHistory &travelHistory);

			int64_t CalculateOrder(OperationTraversalHistory &travelHistory, const MapNode* pNode) const;

			MapNode* AllocateNode(KeyType key, const ValueType& value);
			void FreeNode(MapNode* pNode);
		};


}

#include "SFSortedMap.inl"
