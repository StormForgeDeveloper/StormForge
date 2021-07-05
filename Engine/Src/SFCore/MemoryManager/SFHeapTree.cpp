////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2018 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Heap tree
//
////////////////////////////////////////////////////////////////////////////////

#include "SFCorePCH.h"
#include "SFTypedefs.h"
#include "SFAssert.h"
#include "MemoryManager/SFHeapTree.h"


namespace SF
{

	///////////////////////////////////////////////////////////////////////////
	//
	//	Heap tree
	//


	constexpr int HeapTree::BalanceTolerance;
	constexpr int HeapTree::MaxRebalancingTry;
	constexpr size_t HeapTree::OperationTraversalHistory::GrowthBy;


	///////////////////////////////////////////////////////////////////////////
	//
	//	HeapTree::MapNode
	//

	int HeapTree::MapNode::UpdateBalanceFactor()
	{
		auto left = Left;
		auto right = Right;
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
		Balance = int8_t(iRightDepth - iLeftDepth);
		DepthOfChildren = int8_t(std::max(iRightDepth, iLeftDepth));
		NumberOfChildren = int8_t(iLeftChildren + iRightChildren);

		return Balance;
	}


	///////////////////////////////////////////////////////////////////////////
	//
	//	HeapTree::OperationTraversalHistory
	//

	HeapTree::ReferenceAccessPoint* HeapTree::OperationTraversalHistory::GetParentAccessPoint(int nodeIndex, MapNode* pNode)
	{
		ReferenceAccessPoint* pParentPointer = nullptr;
		Assert(GetHistory(nodeIndex) == pNode);
		if (GetHistorySize() <= 1 || nodeIndex < 1) // only the found node is in there
		{
			pParentPointer = &m_Root;
		}
		else
		{
			auto parentNode = GetHistory(nodeIndex - 1);
			if (parentNode->Left == pNode)
				pParentPointer = &parentNode->Left;
			else
				pParentPointer = &parentNode->Right;

			Assert(*pParentPointer == pNode);
		}

		return pParentPointer;
	}


	///////////////////////////////////////////////////////////////////////////
	//
	//
	//

	HeapTree::HeapTree()
		: m_Root(nullptr)
		, m_ItemCount(0)
	{
	}

	HeapTree::~HeapTree()
	{
		ClearMap();
	}

	void HeapTree::ClearMap()
	{
		MapNode* pCurNode = m_Root;
		std::queue<MapNode*> mapNodes;

		m_Root = nullptr;
		m_ItemCount = 0;

		if (pCurNode != nullptr) mapNodes.push(pCurNode);
		while (mapNodes.size() > 0)
		{
			pCurNode = mapNodes.front();
			mapNodes.pop();

			if (pCurNode->Left != nullptr)	mapNodes.push(pCurNode->Left);
			if (pCurNode->Right != nullptr)	mapNodes.push(pCurNode->Right);
		}
	}

	// Insert a key
	Result HeapTree::Insert(MapNode *pNode)
	{
		if (pNode == nullptr)
			return ResultCode::INVALID_POINTER;

		Assert(pNode->NextNode.NotInAnyList());

		KeyType key = pNode->Key();
		OperationTraversalHistory traversalHistory(GetSystemHeap(), m_Root, m_ItemCount);

		MapNode* pFound = nullptr;
		if (!(FindNode(traversalHistory, key, pFound)))
		{
			if (m_Root != nullptr)
				return ResultCode::FAIL;
			else
			{
				m_Root = pNode;

				m_ItemCount++;

				return ResultCode::SUCCESS;
			}
		}

		// When the search finishes, it returns one of leaf node
		if (key > pFound->Key()) // duplicate key will be put at the left most side
		{
			auto right = pFound->Right;
			if (right != nullptr)
				return ResultCode::FAIL;

			pFound->Right = pNode;
		}
		else if (key == pFound->Key())
		{
			// same key. attach to next
			pNode->NextNode.pPrev = &pFound->NextNode;
			pNode->NextNode.pNext = pFound->NextNode.pNext;
			pFound->NextNode.pNext = &pNode->NextNode;
		}
		else // if (key < pCurNode->Key()) 
		{
			auto left = pFound->Left;
			if (left != nullptr)
				return ResultCode::FAIL;

			pFound->Left = pNode;
		}

		FixupBalance(traversalHistory);

		m_ItemCount++;

		return ResultCode::SUCCESS;
	}


	// Remove an item and return the removed value
	Result HeapTree::Remove(MapNode *pNode)
	{
		if (pNode == nullptr)
			return ResultCode::INVALID_POINTER;

		OperationTraversalHistory travelHistory(GetSystemHeap(), m_Root, m_ItemCount);

		auto key = pNode->Key();
		MapNode* pFound = nullptr;
		if (!(FindNode(travelHistory, key, pFound)))
			return ResultCode::FAIL;

		// key
		if (pFound->Key() != key)
			return ResultCode::FAIL;

		if (pFound == pNode)
		{
			// This node need to be removed
			//ReferenceAccessPoint *pParentPointer = nullptr;
			MapNode* replacedChild = nullptr;
			if (pFound->NextNode.pNext == nullptr)
			{
				// find replacement from children
				auto left = pFound->Left;
				auto right = pFound->Right;
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

					// select heavy tree child, and swap
					if (rightHeavy) 
					{
						replacedChild = FindSmallestNode(travelHistory, right);
						Assert(replacedChild->Left == nullptr);

						// remove replacement from the tree
						ReferenceAccessPoint* pParentAccessOfReplaced = travelHistory.GetParentAccessPoint((int)travelHistory.GetHistorySize() - 1, replacedChild);
						*pParentAccessOfReplaced = replacedChild->Right;
						replacedChild->Right = nullptr;
					}
					else
					{
						replacedChild = FindBiggestNode(travelHistory, left);
						Assert(replacedChild->Right == nullptr);

						// remove replacement from the tree
						ReferenceAccessPoint* pParentAccessOfReplaced = travelHistory.GetParentAccessPoint((int)travelHistory.GetHistorySize() - 1, replacedChild);
						*pParentAccessOfReplaced = replacedChild->Left;
						replacedChild->Left = nullptr;
					}
				}
				else
				{
					// if it doesn't have any child
					// We don't need to find replacement
				}

				ReferenceAccessPoint* pParentAccessOfReplaced = travelHistory.GetParentAccessPoint((int)travelHistory.GetHistorySize() - 1, pFound);
				*pParentAccessOfReplaced = replacedChild;

				// Tree structure has been updated
				// remove from the traversal history, replacement node will not be need to be took care
				travelHistory.RemoveLastHistory();

				FixupBalance(travelHistory);
			}
			else
			{
				// find replacement from dup key node
				auto pNewNode = pFound->NextNode.pNext;
				auto pNext = pNewNode->pNext;
				memcpy(pNewNode, pFound, sizeof(MapNode));
				//pNewNode->Prev = nullptr; // it shares with Left
				pNewNode->pNext = pNext;
				replacedChild = ContainerPtrFromMember(HeapTree::MapNode, NextNode, pNext);
				//replacedChild = ((HeapTree::MapNode*)((uint8_t*)(pNext)-offsetof(HeapTree::MapNode, NextNode)));

				ReferenceAccessPoint* pParentAccessOfReplaced = travelHistory.GetParentAccessPoint((int)travelHistory.GetHistorySize() - 1, pFound);
				*pParentAccessOfReplaced = replacedChild;
			}
		}
		else
		{
			// The one in duplication list. simple remove the node from the list
#if 1 || defined(DEBUG)
			// Linked list Validation
			auto pCurLink = pFound->NextNode.pNext;
			bool bIsExist = false;
			while (pCurLink != nullptr)
			{
				bIsExist = bIsExist || pNode == ContainerPtrFromMember(HeapTree::MapNode, NextNode, pCurLink);
				pCurLink = pCurLink->pNext;
			}
#endif
			auto pPrev = pNode->NextNode.pPrev;
			auto pNext = pNode->NextNode.pNext;

			Assert(pPrev != nullptr); // pPrev always exist, if the node is in the list
			if (pPrev == nullptr)
				return ResultCode::NOT_EXIST;

			pPrev->pNext = pNext;
			if (pNext != nullptr) pNext->pPrev = pPrev;

			pNode->NextNode.pPrev = nullptr;
			pNode->NextNode.pNext = nullptr;
		}

		m_ItemCount--;

		return ResultCode::SUCCESS;
	}


	// Find a key value
	Result HeapTree::Find(KeyType key, MapNode* &pFound, int64_t *pOrder)
	{
		OperationTraversalHistory travelHistory(GetSystemHeap(), m_Root, m_ItemCount);

		if (!(FindNode(travelHistory, key, pFound)))
			return ResultCode::FAIL;

		// unique key
		if (pFound->Key() != key)
			return ResultCode::FAIL;

		if (pOrder != nullptr)
		{
			*pOrder = CalculateOrder(travelHistory, pFound);
		}

		return ResultCode::SUCCESS;
	}


	// Find a key value
	Result HeapTree::FindSameOrBigger(KeyType key, MapNode* &pFound)
	{
		// TODO: 
		OperationTraversalHistory travelHistory(GetSystemHeap(), m_Root, m_ItemCount);

		if (!(FindNode(travelHistory, key, pFound)))
			return ResultCode::FAIL;

		// unique key
		if (pFound->Key() != key)
			return ResultCode::FAIL;

		return ResultCode::SUCCESS;
	}


	// find parent node or candidate
	Result HeapTree::FindNode(OperationTraversalHistory &travelHistory, KeyType key, MapNode* &pNode)
	{
		MapNode* pCurNode = m_Root;
		if (pCurNode == nullptr)
			return ResultCode::FAIL;

		travelHistory.Clear();
		travelHistory.SetPreserveDataOnResize(true);

		do
		{
			travelHistory.AddHistory(pCurNode);

			// existing key
			if (pCurNode->Key() == key)
			{
				// stop searching
				pNode = pCurNode;
				return ResultCode::SUCCESS;
			}

			if (key > pCurNode->Key())
			{
				auto right = pCurNode->Right;
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
			else // if (key < pCurNode->Key())
			{
				auto left = pCurNode->Left;
				if (left == nullptr)
				{
					pNode = pCurNode;
					return ResultCode::SUCCESS;
				}
				else
				{
					// Handle multiple key
					// choose left most one
					if (pCurNode->Key() == key)
					{
						if (left->Key() != key)
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

	HeapTree::MapNode* HeapTree::FindSmallestNode(OperationTraversalHistory &travelHistory, MapNode* pRootNode)
	{
		if (pRootNode == nullptr) return nullptr;

		auto pCurNode = pRootNode;
		while (pCurNode != nullptr)
		{
			travelHistory.AddHistory(pCurNode);
			auto left = pCurNode->Left;
			if (left == nullptr)
				return pCurNode;

			pCurNode = left;
		}

		return pCurNode;
	}

	HeapTree::MapNode* HeapTree::FindBiggestNode(OperationTraversalHistory &travelHistory, MapNode* pRootNode)
	{
		if (pRootNode == nullptr) return nullptr;

		auto pCurNode = pRootNode;
		while (pCurNode != nullptr)
		{
			travelHistory.AddHistory(pCurNode);
			auto right = pCurNode->Right;
			if (right == nullptr)
				return pCurNode;

			pCurNode = right;
		}

		return pCurNode;
	}

	void HeapTree::FixupBalance(OperationTraversalHistory &travelHistory)
	{
		int iRebalancing = 0;
		for (int iHistory = (int)travelHistory.GetHistorySize() - 1; iHistory >= 0; iHistory--)
		{
			auto pCurNode = travelHistory.GetHistory(iHistory);
			auto balance = pCurNode->UpdateBalanceFactor();

			if (std::abs(balance) < BalanceTolerance)
				continue;

			iRebalancing++;
			if (iRebalancing > MaxRebalancingTry)
				continue;

			// Truncate history, it's need to be update
			auto parentAccessPoint = travelHistory.GetParentAccessPoint(iHistory, pCurNode);
			travelHistory.TruncateHistoryFrom(iHistory);

			if (balance <= -BalanceTolerance)
			{
				auto left = pCurNode->Left;
				// left-right case
				if (left->Balance >= 0)
				{
					auto leftRight = left->Right;
					left->Right = leftRight->Left;
					pCurNode->Left = leftRight->Right;

					leftRight->Left = left;
					leftRight->Right = pCurNode;

					*parentAccessPoint = leftRight;
					travelHistory.AddHistory(leftRight);
				}
				else // left-left case
				{
					pCurNode->Left = left->Right;
					left->Right = pCurNode;
					*parentAccessPoint = left;
				}

				travelHistory.AddHistory(left);
			}
			else// if (balance >= BalanceTolerance)
			{
				auto right = pCurNode->Right;
				// right-left case
				if (right->Balance < 0)
				{
					auto rightLeft = right->Left;
					pCurNode->Right = rightLeft->Left;
					right->Left = rightLeft->Right;

					rightLeft->Left = pCurNode;
					rightLeft->Right = right;

					*parentAccessPoint = rightLeft;
					travelHistory.AddHistory(rightLeft);
				}
				else // right-right case
				{
					pCurNode->Right = right->Left;
					right->Left = pCurNode;
					*parentAccessPoint = right;
				}

				travelHistory.AddHistory(right);
			}

			travelHistory.AddHistory(pCurNode);

			iHistory = (int)travelHistory.GetHistorySize();// -1; // loop count will be decreased before procedeed
		}
	}

	int64_t HeapTree::CalculateOrder(OperationTraversalHistory &travelHistory, MapNode* pNode)
	{
		if (pNode == nullptr)
			return 0;

		int64_t order = 0;
		int iDepth = (int)travelHistory.GetHistorySize() - 1;
		if (travelHistory.GetLastHistory() == pNode) // Should not include itself, but children bigger than it should be included
		{
			auto right = pNode->Right;
			if (right != nullptr)
			{
				order += right->NumberOfChildren + 1; // right + number of children  of right
			}
			iDepth--; // remove himself
		}

		for (; iDepth >= 0; iDepth--)
		{
			MapNode* pParentNode = travelHistory.GetHistory(iDepth);
			if (pParentNode->Right == pNode)
			{
				//order += pParentNode->Right == nullptr ? 1 : pParentNode->Right->NumberOfChildren;
			}
			else if (pParentNode->Left == pNode)
			{
				order += pParentNode->Right == nullptr ? 1 : pParentNode->Right->NumberOfChildren + 2;
			}
			else
			{
				Assert(false);
			}

			pNode = pParentNode;
		}

		return order;
	}


}
