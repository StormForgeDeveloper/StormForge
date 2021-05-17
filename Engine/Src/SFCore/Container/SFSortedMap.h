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

			};

			typedef ObjectPoolT<MapNode> MyObjectPool;

		private:

			// Search history buffer
			class OperationTraversalHistory
			{
			public:

				enum { GrowthBy = 32 };

			private:

				const ReferenceAccessPoint &m_Root;
				StaticArray<const MapNode*, GrowthBy * 2> m_TraversalHistory;

			public:

				OperationTraversalHistory(IHeap& heap, const ReferenceAccessPoint& root, SynchronizeCounterType totalItemCount)
					: m_Root(root)
					, m_TraversalHistory(heap)
				{
					Assert((size_t)ceil(log2(totalItemCount + 1)) <= m_TraversalHistory.GetAllocatedSize());
					//m_TraversalHistory.Reserve();
					m_TraversalHistory.SetIncreaseSize(GrowthBy);
				}

				size_t GetHistorySize() const { return m_TraversalHistory.size(); }

				void Clear()
				{
					m_TraversalHistory.Clear();
				}

				void SetPreserveDataOnResize(bool conserveDataOnResize)
				{
					m_TraversalHistory.SetPreserveDataOnResize(conserveDataOnResize);
				}

				void AddHistory(const MapNode* pNode)
				{
					m_TraversalHistory.push_back(pNode);
				}

				void RemoveLastHistory()
				{
					Assert(m_TraversalHistory.size() > 0);
					m_TraversalHistory.resize(m_TraversalHistory.size() - 1);
				}

				void TruncateHistoryFrom(int iIndex) { m_TraversalHistory.resize(iIndex); }

				const MapNode* GetHistory(int iIndex) const { return m_TraversalHistory[iIndex]; }

				const MapNode* GetLastHistory() const { if (m_TraversalHistory.size() == 0) return nullptr; return m_TraversalHistory[m_TraversalHistory.size() - 1]; }

				// set Reserve size
				Result Reserve(size_t szReserv)
				{
					if (szReserv <= m_TraversalHistory.GetAllocatedSize())
						return ResultCode::SUCCESS;

					szReserv = GrowthBy * ((szReserv + GrowthBy - 1) / GrowthBy);

					return m_TraversalHistory.Reserve(szReserv);
				}

				ReferenceAccessPoint* GetParentAccessPoint(int nodeIndex, const MapNode* pNode);
				ReferenceAccessPoint* GetParentAccessPoint(int nodeIndex, const MapNode* pNode) const
				{
					return const_cast<OperationTraversalHistory*>(this)->GetParentAccessPoint(nodeIndex, pNode);
				}
			};



		private:

			// Root node
			ReferenceAccessPoint m_Root;

			// item count in the tree
			SynchronizeCounterType m_ItemCount;

			bool m_DeleteNodePool;

			IHeap& m_Heap;
			MyObjectPool *m_pNodePool;

		public:

			SortedMap(IHeap& heap);
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
			Result FindInWriteTree(KeyType key, ValueType& value) const { return Find(key, value); }

			// get number of values
			size_t size() const { return (size_t)m_ItemCount; }

			// enumerate the values
			//Result ForeachOrder(int startOrderIndex, uint count, const std::function<bool(const KeyType&, const ValueType&)>& functor);
			template<class Func>
			Result ForeachOrder(int startOrderIndex, uint count, Func functor) const
			{
				const MapNode* pCurNode = m_Root;
				if (pCurNode == nullptr)
					return ResultCode::SUCCESS;

				OperationTraversalHistory travelHistory(GetHeap(), m_Root, m_ItemCount);
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

				OperationTraversalHistory travelHistory(GetHeap(), m_Root, m_ItemCount);
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
