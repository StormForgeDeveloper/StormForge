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
#include "Container/SFArray.h"
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


#pragma pack(push,1)
			struct MapNode : public MemBlockHdr
			{
				ReferenceAccessPoint Left = nullptr;
				ReferenceAccessPoint Right = nullptr;

				// Same key attached to next
				DoubleLinkedListNode NextNode;

				// Previous chunk
				ReferenceAccessPoint PrevChunk = nullptr;

				// key, sizeof data node
				KeyType Key() { return Size; };

				// Tree depth information
				int8_t Balance				= 0;
				int8_t DepthOfChildren		= 0;
				// Number of nodes - include child
				int8_t NumberOfChildren		= 0;
				int8_t State				= 0;


				MapNode()
				{
				}

				MapNode(size_t dataBlockSize)
				{
					Size = (decltype(Size))dataBlockSize;
				}

				int UpdateBalanceFactor();
			};
#pragma pack(pop)


		private:

			// Search history buffer
			class OperationTraversalHistory
			{
			public:

				static constexpr size_t GrowthBy = 32;

			private:

				ReferenceAccessPoint &m_Root;
				StaticArray<MapNode*, GrowthBy * 2> m_TraversalHistory;

			public:

				OperationTraversalHistory(IHeap& memoryManager, ReferenceAccessPoint& root, size_t totalItemCount)
					: m_Root(root)
					, m_TraversalHistory(memoryManager)
				{
					Assert((size_t)ceil(log2(totalItemCount + 1)) <= m_TraversalHistory.GetAllocatedSize());
					//m_TraversalHistory.Reserve();
					m_TraversalHistory.SetIncreaseSize(GrowthBy);
				}

				size_t GetHistorySize() { return m_TraversalHistory.size(); }

				void Clear()
				{
					m_TraversalHistory.Clear();
				}

				void SetPreserveDataOnResize(bool conserveDataOnResize)
				{
					m_TraversalHistory.SetPreserveDataOnResize(conserveDataOnResize);
				}

				void AddHistory(MapNode* pNode)
				{
					m_TraversalHistory.push_back(pNode);
				}

				void RemoveLastHistory()
				{
					Assert(m_TraversalHistory.size() > 0);
					m_TraversalHistory.resize(m_TraversalHistory.size() - 1);
				}

				void TruncateHistoryFrom(int iIndex) { m_TraversalHistory.resize(iIndex); }

				MapNode* GetHistory(int iIndex) { return m_TraversalHistory[iIndex]; }

				MapNode* GetLastHistory() { if (m_TraversalHistory.size() == 0) return nullptr; return m_TraversalHistory[m_TraversalHistory.size() - 1]; }

				// set Reserve size
				Result Reserve(size_t szReserv)
				{
					if (szReserv <= m_TraversalHistory.GetAllocatedSize())
						return ResultCode::SUCCESS;

					szReserv = GrowthBy * ((szReserv + GrowthBy - 1) / GrowthBy);

					return m_TraversalHistory.reserve(szReserv);
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
			Result Find(KeyType key, MapNode* &pFound, int64_t *pOrder = nullptr);

			Result FindSameOrBigger(KeyType key, MapNode* &pFound);

			// get number of values
			size_t size() { return (size_t)m_ItemCount; }

			// for interface match
			Result CommitChanges() { return ResultCode::SUCCESS; }

		};


}

