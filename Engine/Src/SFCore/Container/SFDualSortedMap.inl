////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2016 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Shared pointer
//
////////////////////////////////////////////////////////////////////////////////

namespace SF {

		///////////////////////////////////////////////////////////////////////////
		//
		//	DualSortedMap<KeyType,ValueType>::MapNode
		//

		template<class KeyType, class ValueType>
		int DualSortedMap<KeyType, ValueType>::MapNode::UpdateBalanceFactor()
		{
			auto left = Left.load();
			auto right = Right.load();
			int iLeftDepth = 0, iLeftChildren = 0;
			int iRightDepth = 0, iRightChildren = 0;
			if (left != nullptr)
			{
				iLeftDepth = left->DepthOfChildren + 1;
				iLeftChildren = left->NumberOfChildren + 1;
			}
			if (right != nullptr)
			{
				iRightDepth = right->DepthOfChildren + 1;
				iRightChildren = right->NumberOfChildren + 1;
			}

			// Original AVL just uses -BalanceTolerance ~ BalanceTolerance expression
			Balance = iRightDepth - iLeftDepth;
			DepthOfChildren = std::max(iRightDepth, iLeftDepth);
			NumberOfChildren = iLeftChildren + iRightChildren;

			return Balance;
		}


		///////////////////////////////////////////////////////////////////////////
		//
		//
		//

		template<class KeyType, class ValueType>
		DualSortedMap<KeyType, ValueType>::DualSortedMap(IHeap& memoryManager)
			: m_Heap(memoryManager)
			, m_ReadRoot(nullptr)
			, m_ReadIndex(0)
			, m_CurReadRoot(nullptr)
			, m_PrevReadRoot(nullptr)
			, m_WriteRoot(nullptr)
			, m_PendingFreeCount(0)
			, m_PendingFreeList(nullptr)
			, m_UpdateSerial(1)
			, m_IsModified(false)
			, m_ItemCount(0)
			, m_ReadItemCount(0)
			//, m_PendingFreeListTail(nullptr)
		{
			for (uint iVal = 0; iVal < countof(m_ReadCount); iVal++)
			{
				m_ReadCount[iVal] = 0;
			}

			m_pNodePool = new(GetHeap()) ObjectPoolT<MapNode>(GetHeap());
		}

		template<class KeyType, class ValueType>
		DualSortedMap<KeyType, ValueType>::~DualSortedMap()
		{
			Reset();

			if (m_pNodePool != nullptr)
			{
				IHeap::Delete(m_pNodePool);
			}
		}

		template<class KeyType, class ValueType>
		void DualSortedMap<KeyType, ValueType>::Reset()
		{
			std::queue<MapNode*> mapNodes;

			CommitChanges();

			MapNode* pCurNode = m_ReadRoot.load();
			if (pCurNode != nullptr) mapNodes.push(pCurNode);

			m_ReadRoot = nullptr;
			while (mapNodes.size() > 0)
			{
				pCurNode = mapNodes.front();
				mapNodes.pop();

				if (pCurNode->Left != nullptr)	mapNodes.push(pCurNode->Left.load());
				if (pCurNode->Right != nullptr)	mapNodes.push(pCurNode->Right.load());

				FreeNode(pCurNode);
			}
			Assert(m_WriteRoot == nullptr);

			m_ItemCount = 0;

			CommitPendingFree();
		}

		// Insert a key
		template<class KeyType, class ValueType>
		Result DualSortedMap<KeyType, ValueType>::Insert(KeyType key, const ValueType& value, int64_t *insertedOrder)
		{
			OperationTraversalHistory travelHistory(GetHeap(), m_WriteRoot, m_ItemCount.load(std::memory_order_relaxed));

			MapNode* pFound = nullptr;
			if (!FindNode(travelHistory, key, pFound))
			{
				if (m_WriteRoot != nullptr)
					return ResultCode::FAIL;
				else
				{
					auto newNode = AllocateNode(key, value);
					m_WriteRoot = newNode;

					if (newNode == nullptr)
						return ResultCode::OUT_OF_MEMORY;

					m_IsModified = true;
					m_ItemCount.fetch_add(1, std::memory_order_relaxed);

					if (insertedOrder != nullptr)
					{
						*insertedOrder = 0;
					}

					return ResultCode::SUCCESS;
				}
			}

			// Clone nodes along  the path
			MapNode* pInserted = nullptr;
			auto foundKey = pFound->Key.load(MemoryOrder::memory_order_acquire);
			if (key > foundKey) // duplicate key will be put at the left most side
			{
				auto right = pFound->Right;
				if (right != nullptr)
					return ResultCode::FAIL;

				pFound->Right = pInserted = AllocateNode(key, value);
			}
			else if (key == foundKey)
			{
				auto left = pFound->Left = CloneNode(pFound->Left.load());
				if (left != nullptr)
				{
					auto biggestNode = FindBiggestNode(travelHistory, left);
					auto right = biggestNode->Right;
					if (right != nullptr)
						return ResultCode::FAIL;

					biggestNode->Right = pInserted = AllocateNode(key, value);
				}
				else
				{
					pFound->Left = pInserted = AllocateNode(key, value);
				}
			}
			else // if (key < pCurNode->Key) 
			{
				auto left = pFound->Left;
				if (left != nullptr)
					return ResultCode::FAIL;

				pFound->Left = pInserted = AllocateNode(key, value);
			}


			if (insertedOrder != nullptr)
			{
				*insertedOrder = CalculateOrder(travelHistory, pInserted);
			}

			FixupBalance(travelHistory);

			m_IsModified = true;
			m_ItemCount.fetch_add(1, std::memory_order_relaxed);

			return ResultCode::SUCCESS;
		}


		// Remove an item and return the removed value
		template<class KeyType, class ValueType>
		Result DualSortedMap<KeyType, ValueType>::Remove(KeyType key, ValueType& value)
		{
			OperationTraversalHistory travelHistory(GetHeap(), m_WriteRoot, m_ItemCount.load(std::memory_order_relaxed));

			MapNode* pRemoved = nullptr;
			MapNode* pFound = nullptr;
			if (!FindNode(travelHistory, key, pFound))
				return ResultCode::INVALID_ARG;

			// unique key
			auto foundKey = pFound->Key.load(MemoryOrder::memory_order_acquire);
			if (foundKey != key)
				return ResultCode::FAIL;

			value = pFound->Value;

			int iFoundIndex = (int)travelHistory.GetHistorySize() - 1;
			auto left = pFound->Left.load();
			auto right = pFound->Right.load();
			// If it's not a leap node, find a replacement
			if (left != nullptr || right != nullptr)
			{
				// select a child to replace
				bool rightHeavy = false;
				int leftDepth = left == nullptr ? -1 : left->DepthOfChildren;
				int rightDepth = right == nullptr ? -1 : right->DepthOfChildren;
				if (leftDepth > rightDepth)
				{
				}
				else if (leftDepth < rightDepth)
				{
					rightHeavy = true;
				}
				else
				{
					int leftChildren = left == nullptr ? -1 : left->NumberOfChildren;
					int rightChildren = right == nullptr ? -1 : right->NumberOfChildren;
					if (leftChildren > rightChildren)
					{
					}
					else
					{
						rightHeavy = true;
					}
				}

				const MapNode* child = nullptr;
				if (rightHeavy) // select heavy tree child
				{
					right = pFound->Right = CloneNode(right);
					pRemoved = FindSmallestNode(travelHistory, right);
					Assert(pRemoved->Left == nullptr);
					child = pRemoved->Right.load();
				}
				else
				{
					left = pFound->Left = CloneNode(left);
					pRemoved = FindBiggestNode(travelHistory, left);
					Assert(pRemoved->Right == nullptr);
					child = pRemoved->Left.load();
				}

				// swap node
				//assert(iFoundIndex == travelHistory.FindIndex(pFound));
				auto pParentPointer = travelHistory.GetParentAccessPoint((int)travelHistory.GetHistorySize() - 1, pRemoved);
				*pParentPointer = child;

				travelHistory.Replace(m_UpdateSerial, iFoundIndex, true, pFound, pRemoved);

				// pFound is the one need to be deleted
				pRemoved = const_cast<MapNode*>(pFound);
			}
			else
			{
				// if it doesn't have any child
				pRemoved = pFound;

				auto pParentPointer = travelHistory.GetParentAccessPoint((int)travelHistory.GetHistorySize() - 1, pRemoved);
				*pParentPointer = nullptr;
			}


			// remove from the traversal history, replacement node will not be need to be took care
			travelHistory.RemoveLastHistory();

			FixupBalance(travelHistory);

			if (pRemoved) FreeNode(pRemoved);

			m_IsModified = true;
			m_ItemCount.fetch_sub(1, std::memory_order_release);

			return ResultCode::SUCCESS;
		}



		// Find a key value
		template<class KeyType, class ValueType>
		Result DualSortedMap<KeyType, ValueType>::FindInWriteTree(KeyType key, ValueType& value)
		{
			auto pReadRoot = m_WriteRoot;
			if (pReadRoot == nullptr)
			{
				// try in read tree again
				return Find(key, value);
			}

			OperationTraversalHistory travelHistory(GetHeap(), pReadRoot, m_ItemCount.load(std::memory_order_relaxed));

			MapNode* pFound = nullptr;
			if (!FindNode(travelHistory, key, pFound))
			{
				return ResultCode::FAIL;
			}

			// unique key
			auto foundKey = pFound->Key.load(MemoryOrder::memory_order_acquire);
			if (foundKey != key)
			{
				return ResultCode::FAIL;
			}

			value = pFound->Value;

			return ResultCode::SUCCESS;
		}

		// commit changes
		template<class KeyType, class ValueType>
		Result DualSortedMap<KeyType, ValueType>::CommitChanges()
		{
			// Nothing to commit
			if (!m_IsModified)
			{
				return ResultCode::SUCCESS;
			}

#ifdef DEBUG
			//auto oldReadCount0 = m_ReadCount[0].load(std::memory_order_relaxed);
			//auto oldReadCount1 = m_ReadCount[1].load(std::memory_order_relaxed);
			//auto oldReadCount2 = m_ReadCount[2].load(std::memory_order_relaxed);
#endif

		// flip root
			auto oldRoot = m_PrevReadRoot = m_ReadRoot.load(std::memory_order_relaxed);
			Assert(m_WriteRoot == nullptr || m_WriteRoot.load() != oldRoot);
			if (m_WriteRoot != nullptr)
			{
				Assert(!m_WriteRoot->IsCloned);
			}

			if (oldRoot != nullptr)
			{
				AssertRel(oldRoot->UpdateSerial != m_UpdateSerial);
				AssertRel(oldRoot->UpdateSerial == (m_UpdateSerial - 1));
			}

			m_UpdateSerial++; // Some read assert on debug build require memory fence

			auto oldWrite = m_WriteRoot;
			m_WriteRoot = nullptr;

			std::atomic_thread_fence(std::memory_order_seq_cst);

			m_ReadRoot = oldWrite;

			std::atomic_thread_fence(std::memory_order_seq_cst);

			// after flip the root we need to wait all previous working indexies
			auto oldReadIndex = m_ReadIndex.fetch_add(1, std::memory_order_release) % countof(m_ReadCount);
			while (m_ReadCount[oldReadIndex].load(std::memory_order_relaxed) > 0)
			{
				ThisThread::SleepFor(DurationMS(0));
			}

			//Clean up cloned sources
	//#ifdef DEBUG
	//		ForeachOrder(m_ReadRoot.load(), 0, (uint)m_ItemCount.load(std::memory_order_relaxed), [&](MapNode* pNode)-> bool
	//		{
	//			ForeachPendingFree([&pNode](ObjectPoolObject *pPoolObject)
	//			{
	//				AssertRel(pPoolObject != (ObjectPoolObject*)pNode);
	//			});
	//			return true;
	//		});
	//#endif

			CommitPendingFree();


			m_IsModified = false;

			m_ReadItemCount = m_ItemCount.load(std::memory_order_relaxed);

			return ResultCode::SUCCESS;
		}

		// Find a key value
		template<class KeyType, class ValueType>
		Result DualSortedMap<KeyType, ValueType>::Find(KeyType key, ValueType& value, int64_t *pOrder)
		{
			auto readIdx = m_ReadIndex.load(std::memory_order_relaxed) % countof(m_ReadCount);
			ScopeCounter localCounter(m_ReadCount[readIdx]);

			m_CurReadRoot = m_ReadRoot.load(std::memory_order_acquire);
			MapNode* pReadRoot = (MapNode*)m_CurReadRoot.load();
			if (pReadRoot == nullptr)
			{
				return ResultCode::FAIL;
			}

			Assert(m_UpdateSerial != pReadRoot->UpdateSerial);
			Assert(m_WriteRoot.load() != pReadRoot);
			 
			OperationTraversalHistory travelHistory(GetHeap(), pReadRoot, m_ReadItemCount);

			MapNode* pFound = nullptr;

			if (!FindNodeRead(travelHistory, pReadRoot, key, pFound))
			{
				return ResultCode::FAIL;
			}

			// unique key
			auto foundKey = pFound->Key.load(MemoryOrder::memory_order_acquire);
			if (foundKey != key)
			{
				return ResultCode::FAIL;
			}

			value = pFound->Value;

			if (pOrder != nullptr)
			{
				*pOrder = CalculateOrder(travelHistory, pFound);
			}

			return ResultCode::SUCCESS;
		}

		// Find biggest from less than or equal to
		template<class KeyType, class ValueType>
		Result DualSortedMap<KeyType, ValueType>::FindBiggest(KeyType key, ValueType& value, int64_t *pOrder)
		{
			auto readIdx = m_ReadIndex.load(std::memory_order_relaxed) % countof(m_ReadCount);
			ScopeCounter localCounter(m_ReadCount[readIdx]);

			m_CurReadRoot = m_ReadRoot.load(std::memory_order_acquire);
			auto pReadRoot = (MapNode*)m_CurReadRoot.load();
			if (pReadRoot == nullptr)
			{
				return ResultCode::FAIL;
			}

			Assert(m_UpdateSerial != pReadRoot->UpdateSerial);
			Assert(m_WriteRoot != pReadRoot);

			OperationTraversalHistory travelHistory(GetHeap(), pReadRoot, m_ReadItemCount);

			MapNode* pFound = nullptr;

			FindNodeRead(travelHistory, pReadRoot, key, pFound); // This function will return closest node to the key value
			if (pFound == nullptr)
				return ResultCode::FAIL;

			if (pFound->Key != key)
			{
				if (pFound->Key > key)
				{
					auto left = pFound->Left.load(std::memory_order_relaxed);
					if (left != nullptr)
					{
						pFound = FindBiggestNodeRead(travelHistory, left);
					}
					else
					{
					}

					if (pFound == nullptr)
					{
						assert(false);
						if (pOrder != nullptr)
						{
							*pOrder = 0;
						}
						return ResultCode::SUCCESS_FALSE;
					}
				}
			}
			else
			{
				assert(pFound->Key == key);
			}



			value = pFound->Value;

			if (pOrder != nullptr)
			{
				*pOrder = CalculateOrder(travelHistory, pFound);
			}

			return ResultCode::SUCCESS;
		}

		//// enumerate the values
		//template<class KeyType, class ValueType>
		//Result DualSortedMap<KeyType, ValueType>::ForeachOrder(INT startOrderIndex, uint count, const std::function<bool(const KeyType&, const ValueType&)>& functor)
		//{
		//	auto readIdx = m_ReadIndex.load(std::memory_order_relaxed) % countof(m_ReadCount);
		//	ScopeCounter localCounter(m_ReadCount[readIdx]);

		//	m_CurReadRoot = m_ReadRoot.load(std::memory_order_acquire);
		//	auto readRoot = (MapNode*)m_CurReadRoot;
		//	if (readRoot == nullptr)
		//		return ResultCode::FAIL;

		//	return ForeachOrder(readRoot, startOrderIndex, count, functor);
		//}


		//template<class KeyType, class ValueType, class Func>
		//Result DualSortedMap<KeyType, ValueType>::ForeachReverseOrder(INT startOrderIndex, uint count, Func functor)
		////Result DualSortedMap<KeyType, ValueType>::ForeachReverseOrder(INT startOrderIndex, uint count, const std::function<bool(const KeyType&, const ValueType&)>& functor)


		//// enumerate the values
		//template<class KeyType, class ValueType>
		//Result DualSortedMap<KeyType, ValueType>::ForeachOrderWrite(INT startOrderIndex, uint count, const std::function<bool(const KeyType&, const ValueType&)>& functor)
		//{
		//	if (!m_IsModified)
		//	{
		//		return ForeachOrder(startOrderIndex, count, functor);
		//	}

		//	return ForeachOrder(m_WriteRoot, startOrderIndex, count, functor);
		//}

		// find parent node or candidate, we clone nodes along the way
		template<class KeyType, class ValueType>
		Result DualSortedMap<KeyType, ValueType>::FindNode(OperationTraversalHistory &travelHistory, KeyType key, MapNode* &pNode)
		{
			MapNode* pCurNode = m_WriteRoot.load();
			if (pCurNode == nullptr)
			{
				if (!m_IsModified)
				{
					auto readRoot = m_ReadRoot.load(std::memory_order_relaxed);
					if (readRoot == nullptr)
						return ResultCode::FAIL;
					Assert(m_UpdateSerial != readRoot->UpdateSerial);
					pCurNode = m_WriteRoot = CloneNode(readRoot);
					Assert(m_WriteRoot != readRoot);
					m_IsModified = true;
				}
				else
				{
					return ResultCode::FAIL;
				}
			}
			Assert(m_WriteRoot != m_ReadRoot.load());

			travelHistory.Clear();
			travelHistory.SetPreserveDataOnResize(true);

			do
			{
				Assert(pCurNode->UpdateSerial == m_UpdateSerial);
				Assert(!pCurNode->IsCloned);
				travelHistory.AddHistory(pCurNode);

				// multiple key
				auto curKey = pCurNode->Key.load(MemoryOrder::memory_order_acquire);
				if (curKey == key)
				{
					pNode = pCurNode;
					return ResultCode::SUCCESS;
				}

				if (key > curKey)
				{
					auto right = pCurNode->Right.load();
					if (right == nullptr)
					{
						pNode = pCurNode;
						return ResultCode::SUCCESS;
					}
					else
					{
						right = pCurNode->Right = CloneNode(right);
						pCurNode = right;
					}
				}
				else // if (key <= curKey)
				{
					auto left = pCurNode->Left.load();
					left = pCurNode->Left = CloneNode(left);

					if (left == nullptr)
					{
						pNode = pCurNode;
						return ResultCode::SUCCESS;
					}
					else
					{
						// Handle multiple key
						// choose left most one
						if (curKey == key)
						{
							auto leftKey = left->Key.load(MemoryOrder::memory_order_acquire);
							if (leftKey != key)
							{
								pNode = FindBiggestNode(travelHistory, left);
								return ResultCode::SUCCESS;
							}
						}
						pCurNode = left;
					}
				}

			} while (pCurNode != nullptr);

			travelHistory.SetPreserveDataOnResize(false);

			return ResultCode::SUCCESS;
		}

		template<class KeyType, class ValueType>
		typename DualSortedMap<KeyType, ValueType>::MapNode* DualSortedMap<KeyType, ValueType>::FindSmallestNode(OperationTraversalHistory &travelHistory, MapNode* pRootNode)
		{
			if (pRootNode == nullptr) return nullptr;

			auto pCurNode = pRootNode;
			while (pCurNode != nullptr)
			{
				Assert(pCurNode->UpdateSerial == m_UpdateSerial);
				travelHistory.AddHistory(pCurNode);
				auto left = pCurNode->Left = CloneNode(pCurNode->Left.load());
				if (left == nullptr)
					return pCurNode;

				pCurNode = left;
			}

			return pCurNode;
		}

		template<class KeyType, class ValueType>
		typename DualSortedMap<KeyType, ValueType>::MapNode* DualSortedMap<KeyType, ValueType>::FindBiggestNode(OperationTraversalHistory &travelHistory, MapNode* pRootNode)
		{
			if (pRootNode == nullptr) return nullptr;

			Assert(pRootNode->UpdateSerial == m_UpdateSerial);

			auto pCurNode = pRootNode;
			while (pCurNode != nullptr)
			{
				Assert(pCurNode->UpdateSerial == m_UpdateSerial);
				travelHistory.AddHistory(pCurNode);
				auto right = pCurNode->Right = CloneNode(pCurNode->Right.load());
				if (right == nullptr)
					return pCurNode;

				pCurNode = right;
			}

			return pCurNode;
		}

		template<class KeyType, class ValueType>
		Result DualSortedMap<KeyType, ValueType>::FindNodeRead(OperationTraversalHistory &travelHistory, MapNode* pRootNode, KeyType key, MapNode* &pNode)
		{
			MapNode* pCurNode = pRootNode;
			if (pCurNode == nullptr)
				return ResultCode::FAIL;

			do
			{
				travelHistory.AddHistory(pCurNode);

				// multiple key
				auto curKey = pCurNode->Key.load(MemoryOrder::memory_order_acquire);
				if (curKey == key)
				{
					pNode = pCurNode;
					return ResultCode::SUCCESS;
				}

				if (key > curKey)
				{
					auto right = pCurNode->Right.load();
					if (right == nullptr)
					{
						pNode = pCurNode;
						return ResultCode::SUCCESS;
					}
					else
					{
						pCurNode = right;
					}
				}
				else // if (key <= curKey)
				{
					auto left = pCurNode->Left.load();
					if (left == nullptr)
					{
						pNode = pCurNode;
						return ResultCode::SUCCESS;
					}
					else
					{
						// Handle multiple key
						// choose left most one
						if (curKey == key)
						{
							auto leftKey = left->Key.load(MemoryOrder::memory_order_acquire);
							if (leftKey != key)
							{
								pNode = FindBiggestNodeRead(travelHistory, left);
								return ResultCode::SUCCESS;
							}
						}
						pCurNode = left;
					}
				}

			} while (pCurNode != nullptr);

			return ResultCode::SUCCESS;
		}

		template<class KeyType, class ValueType>
		typename DualSortedMap<KeyType, ValueType>::MapNode* DualSortedMap<KeyType, ValueType>::FindSmallestNodeRead(OperationTraversalHistory &travelHistory, MapNode* pRootNode)
		{
			if (pRootNode == nullptr) return nullptr;

			auto pCurNode = pRootNode;
			while (pCurNode != nullptr)
			{
				travelHistory.AddHistory(pCurNode);

				auto left = pCurNode->Left.load();
				if (left == nullptr)
					return pCurNode;

				pCurNode = left;
			}

			return pCurNode;
		}

		template<class KeyType, class ValueType>
		typename DualSortedMap<KeyType, ValueType>::MapNode* DualSortedMap<KeyType, ValueType>::FindBiggestNodeRead(OperationTraversalHistory &travelHistory, MapNode* pRootNode)
		{
			if (pRootNode == nullptr) return nullptr;

			auto pCurNode = pRootNode;
			while (pCurNode != nullptr)
			{
				travelHistory.AddHistory(pCurNode);

				auto right = pCurNode->Right.load();
				if (right == nullptr)
					return pCurNode;

				pCurNode = right;
			}

			return pCurNode;
		}

		//template<class KeyType, class ValueType>
		//Result DualSortedMap<KeyType, ValueType>::ForeachOrder(MapNode* pRootNode, INT startOrderIndex, uint count, const std::function<bool(const KeyType&, const ValueType&)>& functor)
		//{
		//	if (pRootNode == nullptr)
		//		return ResultCode::SUCCESS;

		//	OperationTraversalHistory travelHistory(pRootNode, m_ReadItemCount);

		//	MapNode* pCurNode = pRootNode;
		//	if (pCurNode == nullptr)
		//	{
		//		return ResultCode::SUCCESS;
		//	}

		//	travelHistory.Clear();
		//	travelHistory.SetPreserveDataOnResize(true);

		//	// find start point
		//	do
		//	{
		//		travelHistory.AddHistory(pCurNode);

		//		auto right = pCurNode->Right.load();
		//		auto rightNumChildren = right != nullptr ? right->NumberOfChildren : -1;
		//		if (rightNumChildren >= startOrderIndex)
		//		{
		//			pCurNode = right;
		//		}
		//		else
		//		{
		//			if (rightNumChildren >= 0)
		//			{
		//				startOrderIndex -= rightNumChildren + 1;
		//			}
		//			if (startOrderIndex == 0) // current node is the start point
		//				break;

		//			startOrderIndex--;
		//			auto left = pCurNode->Left.load();
		//			pCurNode = left;
		//		}

		//	} while (pCurNode != nullptr);

		//	if (pCurNode == nullptr)
		//	{
		//		return ResultCode::SUCCESS;
		//	}


		//	// iterate
		//	do
		//	{
		//		if (!functor(pCurNode->Key, pCurNode->Value))
		//			return ResultCode::SUCCESS;

		//		count--;
		//		if (count == 0)
		//			break;

		//		auto left = pCurNode->Left.load();
		//		if (left != nullptr)
		//		{
		//			pCurNode = FindBiggestNodeRead(travelHistory, left);
		//		}
		//		else // this is a leaf node pop up
		//		{
		//			travelHistory.RemoveLastHistory();
		//			MapNode* parent = nullptr;
		//			do
		//			{
		//				parent = travelHistory.GetLastHistory();
		//				if (parent == nullptr)
		//				{
		//					// nothing to process
		//					pCurNode = nullptr;
		//					break;
		//				}

		//				if (pCurNode == parent->Left.load())
		//				{
		//					travelHistory.RemoveLastHistory();
		//				}
		//				else
		//				{
		//					pCurNode = parent;
		//					break;
		//				}

		//				pCurNode = parent;

		//			} while (parent != nullptr);
		//		}

		//	} while (pCurNode != nullptr);


		//	return ResultCode::SUCCESS;
		//}


		//template<class KeyType, class ValueType, class Func>
		//Result DualSortedMap<KeyType, ValueType>::ForeachReverseOrder(MapNode* pRootNode, INT startOrderIndex, uint count, Func functor)
		////Result DualSortedMap<KeyType, ValueType>::ForeachReverseOrder(MapNode* pRootNode, INT startOrderIndex, uint count, const std::function<bool(const KeyType&, const ValueType&)>& functor)
		//

		template<class KeyType, class ValueType>
		void DualSortedMap<KeyType, ValueType>::FixupBalance(OperationTraversalHistory &travelHistory)
		{
			int iRebalancing = 0;
			for (int iHistory = (int)travelHistory.GetHistorySize() - 1; iHistory >= 0; iHistory--)
			{
				auto pCurNode = const_cast<MapNode*>(travelHistory.GetHistory(iHistory));
				auto balance = pCurNode->UpdateBalanceFactor();

				if (std::abs(balance) < BalanceTolerance)
					continue;

				iRebalancing++;
				if (iRebalancing > MaxRebalancingTry)
					continue;

				// Truncate history, it's need to be update
				//auto parentAccessPoint = travelHistory.GetParentAccessPoint(m_UpdateSerial, iHistory, pCurNode);

				travelHistory.TruncateHistoryFrom(iHistory + 1);

				Assert(pCurNode->UpdateSerial == m_UpdateSerial);

				if (balance <= -BalanceTolerance)
				{
					auto left = pCurNode->Left = CloneNode(pCurNode->Left.load());
					// left-right case
					if (left->Balance >= 0)
					{
						auto leftRight = left->Right = CloneNode(left->Right.load());
						Assert(leftRight->UpdateSerial == m_UpdateSerial);
						Assert(left->UpdateSerial == m_UpdateSerial);
						left->Right = leftRight->Left;
						pCurNode->Left = leftRight->Right;

						leftRight->Left = left;
						leftRight->Right = pCurNode;

						//*parentAccessPoint = leftRight;
						travelHistory.Replace(m_UpdateSerial, iHistory, false, pCurNode, leftRight);
						travelHistory.RemoveLastHistory(); // remove pcurnode before add other
						travelHistory.AddHistory(leftRight);
					}
					else // left-left case
					{
						Assert(left->UpdateSerial == m_UpdateSerial);
						pCurNode->Left = left->Right;
						left->Right = pCurNode;
						//*parentAccessPoint = left;
						travelHistory.Replace(m_UpdateSerial, iHistory, false, pCurNode, left);
						travelHistory.RemoveLastHistory(); // remove pcurnode before add other
					}

					travelHistory.AddHistory(left);
				}
				else// if (balance >= BalanceTolerance)
				{
					auto right = pCurNode->Right = CloneNode(pCurNode->Right.load());
					// right-left case
					if (right->Balance < 0)
					{
						auto rightLeft = right->Left = CloneNode(right->Left.load());
						Assert(rightLeft->UpdateSerial == m_UpdateSerial);
						Assert(right->UpdateSerial == m_UpdateSerial);
						pCurNode->Right = rightLeft->Left;
						right->Left = rightLeft->Right;

						rightLeft->Left = pCurNode;
						rightLeft->Right = right;

						//*parentAccessPoint = rightLeft;
						travelHistory.Replace(m_UpdateSerial, iHistory, false, pCurNode, rightLeft);
						travelHistory.RemoveLastHistory(); // remove pcurnode before add other
						travelHistory.AddHistory(rightLeft);
					}
					else // right-right case
					{
						Assert(right->UpdateSerial == m_UpdateSerial);
						pCurNode->Right = right->Left;
						right->Left = pCurNode;
						//*parentAccessPoint = right;
						travelHistory.Replace(m_UpdateSerial, iHistory, false, pCurNode, right);
						travelHistory.RemoveLastHistory(); // remove pcurnode before add other
					}

					travelHistory.AddHistory(right);
				}

				travelHistory.AddHistory(pCurNode);

				iHistory = (int)travelHistory.GetHistorySize();// -1; // loop count will be decreased before procedeed
			}
		}

		template<class KeyType, class ValueType>
		int64_t DualSortedMap<KeyType, ValueType>::CalculateOrder(OperationTraversalHistory &travelHistory, MapNode* pNode)
		{
			if (pNode == nullptr)
				return 0;

			int64_t order = 0;
			int iDepth = (int)travelHistory.GetHistorySize() - 1;
			if (travelHistory.GetLastHistory() == pNode) // Should not include itself, but children bigger than it should be included
			{
				auto right = pNode->Right.load(std::memory_order_relaxed);
				if (right != nullptr)
				{
					order += right->NumberOfChildren + 1; // right + number of children  of right
				}
				iDepth--; // remove himself
			}

			for (; iDepth >= 0; iDepth--)
			{
				MapNode* pParentNode = const_cast<MapNode*>(travelHistory.GetHistory(iDepth));
				if (pParentNode->Left.load() == pNode)
				{
					auto right = pParentNode->Right.load();
					order += right == nullptr ? 1 : right->NumberOfChildren + 2;
				}
				else //if (pParentNode->Right.load() == pNode)
				{
					Assert(pParentNode->Right.load() == pNode);
				}

				pNode = pParentNode;
			}

			return order;
		}


		// Commit pending free list
		template<class KeyType, class ValueType>
		void DualSortedMap<KeyType, ValueType>::CommitPendingFree()
		{
			std::atomic_thread_fence(std::memory_order_acq_rel);

			if (m_PendingFreeList)
			{
				//m_PendingFreeListTail->pNext = m_FreeList;
				auto curNode = m_PendingFreeList;
				while (curNode != nullptr)
				{
					auto next = curNode->NextPendingFree;
					curNode->NextPendingFree = nullptr;
					FreeNode(curNode);
					curNode = next;
				}
			}

			m_PendingFreeList = nullptr;
			m_PendingFreeCount = 0;
		}

		template<class KeyType, class ValueType>
		Result DualSortedMap<KeyType, ValueType>::ForeachPendingFree(std::function<void(MapNode*)> functor)
		{
			auto curNode = m_PendingFreeList;
			while (curNode != nullptr)
			{
				functor(curNode);
				curNode = curNode->NextPendingFree;
			}
			return ResultCode::SUCCESS;
		}


		template<class KeyType, class ValueType>
		typename DualSortedMap<KeyType, ValueType>::MapNode* DualSortedMap<KeyType, ValueType>::CloneNode(MapNode* mapNodeToClone)
		{
			if (mapNodeToClone == nullptr)
				return nullptr;

			//Assert(mapNodeToClone->pNext == nullptr);

			// if already new node
			if (mapNodeToClone->UpdateSerial == m_UpdateSerial)
			{
				return mapNodeToClone;
			}

			Assert(!mapNodeToClone->IsCloned);
			mapNodeToClone->IsCloned = true;

			Assert(m_UpdateSerial != mapNodeToClone->UpdateSerial);

			PendingFreeNode(mapNodeToClone);

			MapNode* newNode = nullptr;
			m_pNodePool->Alloc(newNode);
			Assert(newNode != mapNodeToClone);
			if (newNode != nullptr)
			{
				newNode->SetValue(m_UpdateSerial, *mapNodeToClone);
			}

			Assert(newNode->UpdateSerial != mapNodeToClone->UpdateSerial);

			return newNode;
		}

		template<class KeyType, class ValueType>
		typename DualSortedMap<KeyType, ValueType>::MapNode* DualSortedMap<KeyType, ValueType>::AllocateNode(KeyType key, const ValueType& value)
		{
			MapNode* newNode = nullptr;
			m_pNodePool->Alloc(newNode);
			if (newNode != nullptr)
			{
				newNode->SetValue(m_UpdateSerial, key, value);
			}
			return newNode;

		}

		template<class KeyType, class ValueType>
		void DualSortedMap<KeyType, ValueType>::FreeNode(MapNode* pNode)
		{
			//#ifdef DEBUG
			//		ForeachOrder(m_WriteRoot, 0, (uint)m_ItemCount, [&pNode](MapNode* pCurNode)-> bool
			//		{
			//			Assert(pCurNode != pNode);
			//			return true;
			//		});
			//		ForeachOrder(m_ReadRoot.load(), 0, (uint)m_ItemCount, [&pNode](MapNode* pCurNode)-> bool
			//		{
			//			Assert(pCurNode != pNode);
			//			return true;
			//		});
			//#endif
			pNode->Value = ValueType{};
			m_pNodePool->Free(pNode);
		}

		template<class KeyType, class ValueType>
		void DualSortedMap<KeyType, ValueType>::PendingFreeNode(MapNode* pNode)
		{
			Assert(pNode->IsCloned);

			if (pNode == nullptr)
				return;

#ifdef DEBUG
			new(&pNode->StackTrace) CallStackTrace;
            pNode->StackTrace.CaptureCallStack();
			//StackWalker::CaptureCallStack(pNode->StackTrace);
#endif

			AssertRel(pNode->NextPendingFree == nullptr && pNode != m_PendingFreeList);
			pNode->NextPendingFree = m_PendingFreeList;
			m_PendingFreeList = pNode;

			m_PendingFreeCount++;

			return;
		}

}
