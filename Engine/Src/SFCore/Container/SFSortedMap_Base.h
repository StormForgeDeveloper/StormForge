////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) Kyungkun Ko
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
#include "Math/SFMathUtil.h"


namespace SF {


	// Search history buffer
	template<class MapNodeType, class ReferenceAccessPointType>
	class SortedMapTraversalHistoryT
	{
	public:

		enum { GrowthBy = 32 };

		using MapNode = MapNodeType;
		using ReferenceAccessPoint = ReferenceAccessPointType;

	private:

		//ReferenceAccessPoint m_RootDummy;
		ReferenceAccessPoint* m_Root;
		StaticArray<const MapNode*, GrowthBy * 2> m_TraversalHistory;

	public:

		SortedMapTraversalHistoryT(IHeap& heap, ReferenceAccessPoint& root, size_t totalItemCount)
			: m_Root(&root)
			, m_TraversalHistory(heap)
		{
			m_TraversalHistory.reserve(Math::CeilLogTwo(totalItemCount + 1));
			//Assert((size_t)ceil(log2(totalItemCount + 1)) <= m_TraversalHistory.GetAllocatedSize());
			//m_TraversalHistory.Reserve();
			m_TraversalHistory.SetIncreaseSize(GrowthBy);
		}

		SortedMapTraversalHistoryT(IHeap& heap, const ReferenceAccessPoint& root, size_t totalItemCount)
			: m_Root(const_cast<ReferenceAccessPoint*>(&root))
			, m_TraversalHistory(heap)
		{
			m_TraversalHistory.reserve(Math::CeilLogTwo(totalItemCount + 1));
			//Assert((size_t)ceil(log2(totalItemCount + 1)) <= m_TraversalHistory.GetAllocatedSize());
			//m_TraversalHistory.Reserve();
			m_TraversalHistory.SetIncreaseSize(GrowthBy);
		}

		SF_FORCEINLINE size_t GetHistorySize() const { return m_TraversalHistory.size(); }

		void Clear()
		{
			m_TraversalHistory.Clear();
		}

		SF_FORCEINLINE void SetPreserveDataOnResize(bool conserveDataOnResize)
		{
			m_TraversalHistory.SetPreserveDataOnResize(conserveDataOnResize);
		}

		SF_FORCEINLINE void AddHistory(const MapNode* pNode)
		{
			m_TraversalHistory.push_back(pNode);
		}

		SF_FORCEINLINE void RemoveLastHistory()
		{
			Assert(m_TraversalHistory.size() > 0);
			m_TraversalHistory.resize(m_TraversalHistory.size() - 1);
		}

		SF_FORCEINLINE void TruncateHistoryFrom(int iIndex) { m_TraversalHistory.resize(iIndex); }

		SF_FORCEINLINE const MapNode* GetHistory(int iIndex) const { return m_TraversalHistory[iIndex]; }
		//MapNode* GetHistory(int iIndex) { return m_TraversalHistory[iIndex]; }

		SF_FORCEINLINE const MapNode* GetLastHistory() const { if (m_TraversalHistory.size() == 0) return nullptr; return m_TraversalHistory[m_TraversalHistory.size() - 1]; }
		//MapNode* GetLastHistory() { if (m_TraversalHistory.size() == 0) return nullptr; return m_TraversalHistory[m_TraversalHistory.size() - 1]; }

		// set Reserve size
		Result Reserve(size_t szReserv)
		{
			if (szReserv <= m_TraversalHistory.GetAllocatedSize())
				return ResultCode::SUCCESS;

			szReserv = GrowthBy * ((szReserv + GrowthBy - 1) / GrowthBy);

			return m_TraversalHistory.Reserve(szReserv);
		}

		SF_FORCEINLINE int FindIndex(const MapNode* pNode) const
		{
			return m_TraversalHistory.FindIndex([pNode](const MapNode* x) { return x == pNode; });
		}

		void Replace(uint updateSerial, int nodeIndex, bool isInPlaceSwap, const MapNode* pNode, MapNode* pNewNode)
		{
			Assert(GetHistory(nodeIndex) == pNode);
			if (GetHistorySize() <= 1 || nodeIndex < 1) // only the found node is in there
			{
				*m_Root = const_cast<MapNode*>(pNewNode);
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


		ReferenceAccessPoint* GetParentAccessPoint(int nodeIndex, const MapNode* pNode)
		{
			const ReferenceAccessPoint* pParentPointer = nullptr;
			Assert(GetHistory(nodeIndex) == pNode);
			if (GetHistorySize() <= 1 || nodeIndex < 1) // only the found node is in there
			{
				pParentPointer = m_Root;
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

			return const_cast<ReferenceAccessPoint*>(pParentPointer);
		}

		SF_FORCEINLINE ReferenceAccessPoint* GetParentAccessPoint(int nodeIndex, const MapNode* pNode) const
		{
			return const_cast<SortedMapTraversalHistoryT*>(this)->GetParentAccessPoint(nodeIndex, pNode);
		}

		SF_FORCEINLINE SortedMapTraversalHistoryT& operator = (const SortedMapTraversalHistoryT& src)
		{
			m_Root = src.m_Root;
			m_TraversalHistory = src.m_TraversalHistory;

			return *this;
		}
	};

}

