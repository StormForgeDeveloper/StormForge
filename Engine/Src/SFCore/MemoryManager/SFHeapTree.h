////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2018 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Heap tree
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "SFTypedefs.h"
#include "MemoryManager/SFMemory.h"


namespace SF {


		///////////////////////////////////////////////////////////
		//
		//	HeapTree
		//	- Implementation of AVLTree
		//	- This one doesn't allocate anything  internally.
		//	- Descending sort, left is bigger
		//

		class HeapTree
		{
		public:

			static constexpr int BalanceTolerance = 8;
			static constexpr int MaxRebalancingTry = 20;

			struct MapNode;
			typedef MapNode* ReferenceAccessPoint;
			typedef uint32_t KeyType; // We only support max 4GB allocation


#pragma pack(push,4)
			struct MapNode
			{
				ReferenceAccessPoint Left = nullptr;
				ReferenceAccessPoint Right = nullptr;

				// Same key attached to next
				DoubleLinkedListNode SameKeyNextNode;

				// Previous memory chunk in linear space
				ReferenceAccessPoint PrevMemoryChunk = nullptr;

				// key, sizeof data node
				KeyType Key() { return MemChunkHeader.Size; };

				// Tree depth information
				int32_t Balance : 8;
				int32_t DepthOfChildren : 8;
				// Number of nodes - include child
				int32_t NumberOfChildren : 8;
				int32_t : 0;

				MemBlockHdr MemChunkHeader;


				MapNode()
				{
					Balance = 0;
					DepthOfChildren = 0;
					NumberOfChildren = 0;
				}

				MapNode(IHeap* ThisHeap, uint32_t magic, size_t dataBlockSize)
				{
					Balance = 0;
					DepthOfChildren = 0;
					NumberOfChildren = 0;
					MemChunkHeader.InitHeader(ThisHeap, (uint32_t)dataBlockSize, (uint32_t)AlignUp(sizeof(HeapTree::MapNode), MemBlockHdr::MaxHeaderAlignment));
					MemChunkHeader.Magic = magic;
				}

				int UpdateBalanceFactor();

				void ValidateUpdateSerial(uint32_t) {}

				SF_FORCEINLINE void* GetDataPtr() { return reinterpret_cast<uint8_t*>(this) + MemChunkHeader.HeaderSize; }
				SF_FORCEINLINE MemBlockFooter* GetFooter() { return (MemBlockFooter*)(reinterpret_cast<uint8_t*>(GetDataPtr()) + MemChunkHeader.Size); }
			};
#pragma pack(pop)


		private:

			//using OperationTraversalHistory = SortedMapTraversalHistoryT<MapNode*, ReferenceAccessPoint>;
			// Search history buffer
			class OperationTraversalHistory
			{
			public:

				static constexpr size_t GrowthBy = 32;

			private:

				ReferenceAccessPoint &m_Root;
				size_t m_HistorySize = 0;
				MapNode* m_TraversalHistory[128]{}; // Something bigger enough to hold

			public:

				OperationTraversalHistory(IHeap& heap, ReferenceAccessPoint& root, size_t totalItemCount)
					: m_Root(root)
				{
					Assert((size_t)ceil(log2(totalItemCount + 1)) <= countof(m_TraversalHistory));
				}

				SF_FORCEINLINE size_t GetHistorySize() { return m_HistorySize; }

				void Clear()
				{
					m_HistorySize = 0;
				}

				void SetPreserveDataOnResize(bool conserveDataOnResize)
				{
					
				}

				SF_FORCEINLINE void AddHistory(MapNode* pNode)
				{
					assert((m_HistorySize + 1) < countof(m_TraversalHistory));
					m_TraversalHistory[m_HistorySize++] = pNode;
				}

				SF_FORCEINLINE void RemoveLastHistory()
				{
					if (m_HistorySize > 0)
						m_HistorySize--;
				}

				SF_FORCEINLINE void TruncateHistoryFrom(int iIndex) { assert(iIndex >= 0); m_HistorySize = (size_t)iIndex; }

				SF_FORCEINLINE MapNode* GetHistory(int iIndex) { assert(iIndex >= 0 && iIndex < m_HistorySize); return m_TraversalHistory[iIndex]; }

				SF_FORCEINLINE MapNode* GetLastHistory() { if (m_HistorySize == 0) return nullptr; return m_TraversalHistory[m_HistorySize - 1]; }

				// set Reserve size
				Result Reserve(size_t szReserv)
				{
					assert(szReserv > countof(m_TraversalHistory));
					return ResultCode::SUCCESS;
				}

				void Replace(uint updateSerial, int nodeIndex, bool isInPlaceSwap, const MapNode* pNode, MapNode* pNewNode)
				{
					Assert(GetHistory(nodeIndex) == pNode);
					if (GetHistorySize() <= 1 || nodeIndex < 1) // only the found node is in there
					{
						m_Root = const_cast<MapNode*>(pNewNode);
					}
					else
					{
						auto parentNode = const_cast<MapNode*>(GetHistory(nodeIndex - 1));
						parentNode->ValidateUpdateSerial(updateSerial);
						if (parentNode->Left == pNode)
						{
							parentNode->Left = const_cast<MapNode*>(pNewNode);
						}
						else
						{
							assert(parentNode->Right == pNode);
							parentNode->Right = const_cast<MapNode*>(pNewNode);
						}
					}

					// if it is in-place swap, we need to copy over left and right
					if (isInPlaceSwap)
					{
						m_TraversalHistory[nodeIndex] = pNewNode;
						pNewNode->Left = pNode->Left;
						pNewNode->Right = pNode->Right;
					}
				}

				ReferenceAccessPoint* GetParentAccessPoint(int nodeIndex, MapNode* pNode);
			};



		private:

			// Root node
			ReferenceAccessPoint m_Root;

			// item count in the tree
			size_t m_ItemCount;

		private:

			// find parent node or candidate
			Result FindNode(OperationTraversalHistory &travelHistory, KeyType key, MapNode* &pNode);

			MapNode* FindSmallestNode(OperationTraversalHistory &travelHistory, MapNode* pRootNode);
			MapNode* FindBiggestNode(OperationTraversalHistory &travelHistory, MapNode* pRootNode);

			// Update valance factor and return new balance value
			void FixupBalance(OperationTraversalHistory &travelHistory);

			int64_t CalculateOrder(OperationTraversalHistory &travelHistory, MapNode* pNode);

			bool ValidateNextLink(MapNode* pNode);
			
		public:

			HeapTree();
			~HeapTree();

			// clear tree
			void ClearMap();

			// Insert a key
			Result Insert(MapNode *pNode);

			// Remove an item and return the removed value
			Result Remove(MapNode *pNode);

			// Find a key value
			Result IsInTheTree(MapNode* pNode);

			Result FindSameOrBigger(KeyType key, MapNode* &pFound);

			// get number of values
			size_t size() { return (size_t)m_ItemCount; }

			// for interface match
			Result CommitChanges() { return ResultCode::SUCCESS; }

		};


}

