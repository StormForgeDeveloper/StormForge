
////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) The Braves
// 
// Author: Kyungkun Ko
//
// Description : Fishing zone area data
//
////////////////////////////////////////////////////////////////////////////////


#pragma once

#include "SFTypedefs.h"
#include "Container/SFHashTable2.h"
#include "Container/SFSortedSet.h"
#include "Math/SF3DMath.h"


namespace SF
{


	////////////////////////////////////////////////////////////
	//
	//	class SparseQuadGrid
	//
	class SparseQuadGrid
	{
	public:

		static const Vector4 GridScale;

		// RegionID
		union RegionID
		{
			uint32_t RegionId{};
			struct {
				int16_t RegionX;
				int16_t RegionY;
			} Components;

			RegionID() {}
			RegionID(uint32_t regionId)
				: RegionId(regionId)
			{}
			RegionID(int16_t regionX, int16_t regionY)
			{
				Components.RegionX = regionX;
				Components.RegionY = regionY;
			}

			operator uint32_t() { return RegionId; }

			bool operator >(const RegionID& op) const { return RegionId > op.RegionId; }
			bool operator >=(const RegionID& op) const { return RegionId >= op.RegionId; }
			bool operator <(const RegionID& op) const { return RegionId < op.RegionId; }
			bool operator <=(const RegionID& op) const { return RegionId <= op.RegionId; }
			bool operator ==(const RegionID& op) const { return RegionId == op.RegionId; }
			bool operator !=(const RegionID& op) const { return RegionId != op.RegionId; }
		};

		// Quad
		struct SF_DECLARE_ALIGN_DOUBLE QuadNode
		{
			RegionID RegionId;

			QuadNode(IHeap& heap, const RegionID& regionId = {})
				: RegionId(regionId)
				, TriangleAreas(heap)
			{}
		};

	public:

		SparseQuadGrid();
		SparseQuadGrid(IHeap& heap);
		~SparseQuadGrid();


		IHeap& GetHeap() { return m_Heap; }

		void Reset();

		Result AddTriangle(const TriangleRegionPrecalculated* triangleRegion);

		const TriangleRegionPrecalculated* TestIntersection(StringCrc32 filter, const Vector4& pos) const;

	private:

		void AddLineRegions(const TriangleRegionPrecalculated* triangleRegion, int curY, int lX, int rX);

	private:

		// Heap
		IHeap& m_Heap;

		// Root object
		SortedMap<RegionID,QuadNode*> m_SortedNodeList;
	};


	//////////////////////////////////////////////////////////////////////////////////
	//
	//	class FishingGameZoneAreaData
	//
	class FishingGameZoneAreaData
	{
	public:

		struct SeatInfo
		{
			Vector4 Position;
			uint32_t SeatInstanceId;	// unique index in the zone
			uint32_t SeatId;			// seat table id
		};


	public:

		FishingGameZoneAreaData();
		~FishingGameZoneAreaData();

		SF_FORCEINLINE IHeap& GetHeap() { return GetSystemHeap(); }

		Result LoadZoneAreaData(const char* ZoneDataSchemaPath, const char* ZoneDataPath);

		StringCrc32 TestIntersection(StringCrc32 filter, const Vector4& pos) const;

		Vector4 PickRandomSpawnPosition() const;

		SF_FORCEINLINE const Array<SeatInfo>& GetSeatArray() const { return m_SeatInfoList; }

	private:

		SF::String m_Name;

		AvroSchema m_Schema;

		SparseQuadGrid m_SparseQuadGrid;

		// Triangles
		DynamicArray<TriangleRegionPrecalculated> m_TriangleRegions;
		DynamicArray<TriangleRegionPrecalculated> m_RespawnRegions;

		DynamicArray<TriangleRegionPrecalculated> m_NavigationMeshs;

		DynamicArray<SeatInfo> m_SeatInfoList;
	};

}  // namespace SF
