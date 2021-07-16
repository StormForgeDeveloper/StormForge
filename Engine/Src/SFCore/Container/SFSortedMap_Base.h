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

		using MapNode = MapNodeType;
		using ReferenceAccessPoint = ReferenceAccessPointType;

	private:

		ReferenceAccessPoint* m_Root{};
		int m_HistorySize = 0;
		const MapNode* m_TraversalHistory[128]{};

	public:

		SortedMapTraversalHistoryT()
		{
		}

		SortedMapTraversalHistoryT(ReferenceAccessPoint& root, size_t totalItemCount)
			: m_Root(&root)
		{
			assert(Math::CeilLogTwo(totalItemCount + 1) <= countof(m_TraversalHistory));
		}

		SortedMapTraversalHistoryT(const ReferenceAccessPoint& root, size_t totalItemCount)
			: m_Root(const_cast<ReferenceAccessPoint*>(&root))
		{
			assert(Math::CeilLogTwo(totalItemCount + 1) <= countof(m_TraversalHistory));
		}

		SF_FORCEINLINE size_t GetHistorySize() const { return m_HistorySize; }

		SF_FORCEINLINE void Clear()
		{
			m_HistorySize = 0;
		}

		SF_FORCEINLINE void SetPreserveDataOnResize(bool conserveDataOnResize)
		{
		}

		SF_FORCEINLINE void AddHistory(const MapNode* pNode)
		{
			assert((m_HistorySize+1) < countof(m_TraversalHistory));
			m_TraversalHistory[m_HistorySize++] = pNode;
		}

		SF_FORCEINLINE void RemoveLastHistory()
		{
			if (m_HistorySize > 0)
				m_HistorySize--;
		}

		SF_FORCEINLINE void TruncateHistoryFrom(int iIndex) { assert(iIndex >= 0); m_HistorySize = (size_t)iIndex; }

		SF_FORCEINLINE const MapNode* GetHistory(int iIndex) { assert(iIndex >= 0 && iIndex < m_HistorySize); return m_TraversalHistory[iIndex]; }

		SF_FORCEINLINE const MapNode* GetLastHistory() { if (m_HistorySize == 0) return nullptr; return m_TraversalHistory[m_HistorySize - 1]; }

		// set Reserve size
		SF_FORCEINLINE Result Reserve(size_t szReserv)
		{
			assert(szReserv > countof(m_TraversalHistory));
		}

		SF_FORCEINLINE int FindIndex(const MapNode* pNode) const
		{
			int iIndex = 0;
			for (; iIndex < m_HistorySize; iIndex++)
				if (m_TraversalHistory[iIndex] == pNode)
					return iIndex;

			return -1;
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

