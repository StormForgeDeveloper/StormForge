////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : SortedMap(Multithread)
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "SFTypedefs.h"
#include "SFAssert.h"
#include "Multithread/SFSynchronization.h"
#include "Container/SFArray.h"
#include "Object/SFObjectPool.h"
#include "Container/SFSortedMap_Base.h"

namespace SF {


		///////////////////////////////////////////////////////////
		//
		//	Concurrent SortedMap
		//	- Implementation of concurrent AVLTree
		//

		template<class KeyType, class ValueType>
		class DualSortedMap
		{
		public:
			//typedef uint KeyType;
			//typedef uint ValueType;

			typedef CounterType size_t;
			typedef std::atomic<size_t> SynchronizeCounter;

			enum {
				BalanceTolerance = 4,
				MaxRebalancingTry = 20
			};



			class MapNode;

#define DEBUG_NODEPTR
			//typedef MapNode* ReferenceAccessPoint;
			class ReferenceAccessPoint
			{
			private:
				std::atomic<MapNode*> m_NodePtr;
#ifdef DEBUG_NODEPTR
				MapNode* m_DebugPtr;
#endif
			public:
				ReferenceAccessPoint()
					: m_NodePtr(nullptr)
#ifdef DEBUG_NODEPTR
					, m_DebugPtr(nullptr)
#endif
				{}

				ReferenceAccessPoint(ReferenceAccessPoint& src)
				{
					auto srcPtr = src.m_NodePtr.load(std::memory_order_relaxed);
#ifdef DEBUG_NODEPTR
					m_DebugPtr = srcPtr;
#endif
					m_NodePtr.store(srcPtr, std::memory_order_relaxed);
				}

				ReferenceAccessPoint(MapNode* pNode)
				{
					auto srcPtr = pNode;
#ifdef DEBUG_NODEPTR
					m_DebugPtr = srcPtr;
#endif
					m_NodePtr.store(srcPtr, std::memory_order_relaxed);
				}

				MapNode* load(std::memory_order order = std::memory_order_relaxed) const
				{
					return m_NodePtr.load(order);
				}

				MapNode* store(MapNode* pNode, std::memory_order order = std::memory_order_relaxed)
				{
					m_NodePtr.store(pNode, order);
#ifdef DEBUG_NODEPTR
					m_DebugPtr = pNode;
#endif
					return pNode;
				}

				bool operator != (const MapNode* pNode) const { return load() != pNode; }
				bool operator == (const MapNode* pNode) const { return load() == pNode; }

				MapNode* operator ->() { return load(); }
				const MapNode* operator ->() const { return load(); }

				MapNode* operator = (const ReferenceAccessPoint& src)
				{
					MapNode* pNode = src.load();
					store(pNode);
					return pNode;
				}

				MapNode* operator = (const MapNode* pNode)
				{
					auto pWritable = const_cast<MapNode*>(pNode);
					store(pWritable);
					return pWritable;
				}
			};


			class MapNode : public ObjectPoolObject
			{
			public:
				Atomic<KeyType> Key{};
				ValueType Value{};

				INT Balance = 0;
				INT DepthOfChildren = 0;
				// Number of nodes - include child
				INT NumberOfChildren = 0;

				uint UpdateSerial = 0;

				ReferenceAccessPoint Left;
				ReferenceAccessPoint Right;

				MapNode* NextPendingFree = nullptr;
                Atomic<MapNode*> ClonedNode = nullptr;
#ifdef DEBUG
				CallStackTraceT<6> StackTrace;
#endif

				MapNode()
					: Left(nullptr)
					, Right(nullptr)
				{
				}

				void SetValue()
				{
					Balance = 0;
					DepthOfChildren = 0;
					NumberOfChildren = 0;
					Key = 0;
					Value = 0;
                    ClonedNode.store(nullptr, MemoryOrder::release);
					Left = nullptr;
					Right = nullptr;
					UpdateSerial = 0;
				}

				void SetValue(uint updateSerial, KeyType key, ValueType value)
				{
					Balance = 0;
					DepthOfChildren = 0;
					NumberOfChildren = 0;
					Key = key;
					Value = value;

                    ClonedNode.store(nullptr, MemoryOrder::release);
					Left = nullptr;
					Right = nullptr;
					UpdateSerial = updateSerial;
				}

				void SetValue(uint updateSerial, const MapNode& src)
				{
					Balance = src.Balance;
					DepthOfChildren = src.DepthOfChildren;
					NumberOfChildren = src.NumberOfChildren;
					Key = src.Key;
					Value = src.Value;
                    ClonedNode.store(nullptr, MemoryOrder::release);
					Left = src.Left;
					Right = src.Right;
					UpdateSerial = updateSerial;
				}

				int UpdateBalanceFactor();

				SF_FORCEINLINE void ValidateUpdateSerial(uint32_t updateSerialExpected)
				{
					assert(UpdateSerial == updateSerialExpected);
				}
			};

			typedef ObjectPoolT<MapNode> MyObjectPool;

		private:

			using OperationTraversalHistory = SortedMapTraversalHistoryT<MapNode, ReferenceAccessPoint>;

			//// Search history buffer
			//class OperationTraversalHistory
			//{
			//public:

			//	enum { GrowthBy = 32 };

			//private:

			//	MapNode* &m_Root;
			//	StaticArray<MapNode*, GrowthBy * 2> m_TraversalHistory;

			//public:

			//	OperationTraversalHistory(IHeap& memoryManager, MapNode* &root, size_t totalItemCount)
			//		: m_Root(root)
			//		, m_TraversalHistory(memoryManager)
			//	{
			//		Assert((size_t)ceil(log2(totalItemCount + 1)) <= m_TraversalHistory.GetAllocatedSize());
			//		m_TraversalHistory.SetIncreaseSize(GrowthBy);
			//	}

			//	size_t GetHistorySize() { return m_TraversalHistory.size(); }

			//	void Clear()
			//	{
			//		m_TraversalHistory.Clear();
			//	}

			//	void SetPreserveDataOnResize(bool conserveDataOnResize)
			//	{
			//		m_TraversalHistory.SetPreserveDataOnResize(conserveDataOnResize);
			//	}

			//	void AddHistory(MapNode* pNode)
			//	{
			//		m_TraversalHistory.push_back(pNode);
			//	}

			//	void RemoveLastHistory()
			//	{
			//		Assert(m_TraversalHistory.size() > 0);
			//		m_TraversalHistory.resize(m_TraversalHistory.size() - 1);
			//	}

			//	void TruncateHistoryFrom(int iIndex) { m_TraversalHistory.resize(iIndex); }

			//	MapNode* GetHistory(int iIndex) { return m_TraversalHistory[iIndex]; }

			//	MapNode* GetLastHistory() { if (m_TraversalHistory.size() == 0) return nullptr; return m_TraversalHistory[m_TraversalHistory.size() - 1]; }

			//	// set Reserve size
			//	Result Reserve(size_t szReserv)
			//	{
			//		if (szReserv <= m_TraversalHistory.GetAllocatedSize())
			//			return ResultCode::SUCCESS;

			//		szReserv = GrowthBy * ((szReserv + GrowthBy - 1) / GrowthBy);

			//		return m_TraversalHistory.Reserve(szReserv);
			//	}


			//	void Replace(uint updateSerial, int nodeIndex, MapNode* pNode, MapNode* pNewNode);
			//};



		private:

			IHeap& m_Heap;

			// read Root
			// ping pong counter
			SyncCounter m_ReadCount[3];
			ReferenceAccessPoint m_ReadRoot;
			SynchronizeCounter m_ReadIndex;

			//For read debug
			ReferenceAccessPoint m_CurReadRoot;
			volatile MapNode* m_PrevReadRoot;

			// Write root
			ReferenceAccessPoint m_WriteRoot;

			MyObjectPool *m_pNodePool = nullptr;

			uint		m_PendingFreeCount;
			MapNode*	m_PendingFreeList;
			//MapNode*	m_PendingFreeListTail;


			uint m_UpdateSerial;
			bool m_IsModified;

			// item count in the tree
			Atomic<size_t> m_ItemCount;
			size_t m_ReadItemCount;

		public:

			DualSortedMap(IHeap& memoryManager);
			~DualSortedMap();

			IHeap& GetHeap() { return m_Heap; }

			void clear() { Reset(); }
			void ClearMap() { Reset(); }
			void Reset();

			// Insert a key
			Result Insert(KeyType key, const ValueType& value, int64_t *insertedOrder = nullptr);

			// Remove an item and return the removed value
			Result Remove(KeyType key, ValueType& value);

			Result FindInWriteTree(KeyType key, ValueType& value);

			// commit changes
			Result CommitChanges();

			// Find a key value
			Result Find(KeyType key, ValueType& value, int64_t *pOrder = nullptr);

			bool Contains(KeyType key);

			// Find biggest from less than or equal to
			Result FindBiggest(KeyType key, ValueType& value, int64_t *pOrder = nullptr);

			// get number of values
			size_t size() const { return m_ReadItemCount; }
			size_t GetWriteItemCount() const { return m_ItemCount.load(std::memory_order_relaxed); }


			template<class Func>
			Result ForeachOrder(int startOrderIndex, uint count, Func functor) const
			{
				return const_cast<DualSortedMap*>(this)->ForeachOrder(startOrderIndex, count, functor);
			}

			// enumerate the values
			template<class Func>
			Result ForeachOrder(INT startOrderIndex, uint count, const Func& functor)
			{
				auto readIdx = m_ReadIndex.load(std::memory_order_relaxed) % countof(m_ReadCount);
				ScopeCounter localCounter(m_ReadCount[readIdx]);

				m_CurReadRoot = m_ReadRoot.load(std::memory_order_acquire);
				auto readRoot = (MapNode*)m_CurReadRoot.load();
				if (readRoot == nullptr)
					return ResultCode::FAIL;

				return ForeachOrder(readRoot, startOrderIndex, count, functor);
			}

			template<class Func>
			Result ForeachReverseOrder(INT startOrderIndex, uint count, Func functor)
			{
				auto readIdx = m_ReadIndex.load(std::memory_order_relaxed) % countof(m_ReadCount);
				ScopeCounter localCounter(m_ReadCount[readIdx]);

				m_CurReadRoot = m_ReadRoot.load(std::memory_order_acquire);
				auto readRoot = (MapNode*)m_CurReadRoot.load();
				if (readRoot == nullptr)
					return ResultCode::FAIL;

				return ForeachReverseOrder(readRoot, startOrderIndex, count, functor);
			}

			//
			template<class Func>
			Result ForeachOrderWrite(INT startOrderIndex, uint count, const Func& functor)
			{
				if (!m_IsModified)
				{
					return ForeachOrder(startOrderIndex, count, functor);
				}

				return ForeachOrder(m_WriteRoot, startOrderIndex, count, functor);
			}


		private:

			// find parent node or candidate
			Result FindNode(OperationTraversalHistory &travelHistory, KeyType key, MapNode* &pNode);

			MapNode* FindSmallestNode(OperationTraversalHistory &travelHistory, MapNode* pRootNode);
			MapNode* FindBiggestNode(OperationTraversalHistory &travelHistory, MapNode* pRootNode);

			Result FindNodeRead(OperationTraversalHistory &travelHistory, MapNode* pRootNode, KeyType key, MapNode* &pNode);
			MapNode* FindSmallestNodeRead(OperationTraversalHistory &travelHistory, MapNode* pRootNode);
			MapNode* FindBiggestNodeRead(OperationTraversalHistory &travelHistory, MapNode* pRootNode);

			template<class Func>
			Result ForeachOrder(MapNode* pRootNode, INT startOrderIndex, uint count, const Func& functor)
			{
				if (pRootNode == nullptr)
					return ResultCode::SUCCESS;

				OperationTraversalHistory travelHistory(pRootNode, m_ReadItemCount);

				const MapNode* pCurNode = pRootNode;
				if (pCurNode == nullptr)
				{
					return ResultCode::SUCCESS;
				}

				travelHistory.Clear();
				travelHistory.SetPreserveDataOnResize(true);

				// find start point
				do
				{
					travelHistory.AddHistory(pCurNode);

					auto right = pCurNode->Right.load();
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
						auto left = pCurNode->Left.load();
						pCurNode = left;
					}

				} while (pCurNode != nullptr);

				if (pCurNode == nullptr)
				{
					return ResultCode::SUCCESS;
				}

#ifdef DEBUG
				int DbgCurTraversalIndex = 0;
				const MapNode* DbgTraversalHistory[32]{};
#endif


				// iterate
				do
				{
#ifdef DEBUG
					DbgTraversalHistory[DbgCurTraversalIndex] = pCurNode;
					DbgCurTraversalIndex = (DbgCurTraversalIndex + 1) % countof(DbgTraversalHistory);
#endif
					if (!functor(pCurNode->Key, const_cast<MapNode*>(pCurNode)->Value))
						return ResultCode::SUCCESS;

					count--;
					if (count == 0)
						break;

					auto left = pCurNode->Left.load();
					if (left != nullptr)
					{
						pCurNode = FindBiggestNodeRead(travelHistory, left);
					}
					else // this is a leaf node pop up
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

							if (pCurNode == parent->Left.load())
							{
								travelHistory.RemoveLastHistory();
							}
							else
							{
								pCurNode = parent;
								break;
							}

							pCurNode = parent;

						} while (parent != nullptr);
					}

				} while (pCurNode != nullptr);


				return ResultCode::SUCCESS;
			}

			template<class Func>
			Result ForeachReverseOrder(MapNode* pRootNode, INT startOrderIndex, uint count, Func functor)
			{
				if (pRootNode == nullptr)
					return ResultCode::SUCCESS;

				OperationTraversalHistory travelHistory(pRootNode, m_ReadItemCount);

				const MapNode* pCurNode = pRootNode;
				if (pCurNode == nullptr)
				{
					return ResultCode::SUCCESS;
				}

				travelHistory.Clear();
				travelHistory.SetPreserveDataOnResize(true);

				// find start point
				do
				{
					travelHistory.AddHistory(pCurNode);

					auto left = pCurNode->Left.load();
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
						auto right = pCurNode->Right.load();
						pCurNode = right;
					}

				} while (pCurNode != nullptr);

				if (pCurNode == nullptr)
				{
					return ResultCode::SUCCESS;
				}


				// iterate
				do
				{
					if (!functor(pCurNode->Key, pCurNode->Value))
						break;

					count--;
					if (count == 0)
						break;

					auto right = pCurNode->Right.load();
					if (right != nullptr)
					{
						pCurNode = FindSmallestNodeRead(travelHistory, right);
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

							if (pCurNode == parent->Right.load())
							{
								travelHistory.RemoveLastHistory();
							}
							else
							{
								pCurNode = parent;
								break;
							}

							pCurNode = parent;

						} while (parent != nullptr);
					}

				} while (pCurNode != nullptr);


				return ResultCode::SUCCESS;
			}

			//RoateLeft(pNode);
			// Update valance factor and return new balance value
			void FixupBalance(OperationTraversalHistory &travelHistory);

			int64_t CalculateOrder(OperationTraversalHistory &travelHistory, MapNode* pNode);

			// Commit pending free list
			void CommitPendingFree();
			Result ForeachPendingFree(std::function<void(MapNode*)> functor);


			MapNode* CloneNode(MapNode* mapNodeToClone);
			MapNode* AllocateNode(KeyType key, const ValueType& value);
			void FreeNode(MapNode* pNode);
			void PendingFreeNode(MapNode* pNode);
		};



}

#include "SFDualSortedMap.inl"

