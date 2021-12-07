////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) Kyungkun Ko
// 
// Author : Kyungkun Ko
//
// Description : Result definitions
//	
//
////////////////////////////////////////////////////////////////////////////////


#include "SFCorePCH.h"
#include "SFTypedefs.h"
#include "SFResult.h"
#include "ResultCode/SFResultTable.h"

namespace SF
{
	UniquePtr<ResultTable> ResultTable::stm_Instance;


	ResultTable::ResultMap& ResultTable::GetOrAddFacility(uint32_t facility)
	{
		if (stm_Instance == nullptr)
		{
			stm_Instance.reset(new ResultTable);
		}

		auto pMap = stm_Instance->FacilityMaps.find(facility);
		if (pMap == nullptr)
		{
			pMap = new ResultMap;
			stm_Instance->FacilityMaps.Insert(facility, pMap);
		}

		return *pMap;
	}

	const ResultTable::ResultMap& ResultTable::GetFacility(uint32_t facility)
	{
		static ResultMap Dummy;

		if (stm_Instance == nullptr)
		{
			return Dummy;
		}

		auto pMap = stm_Instance->FacilityMaps.find(facility);
		if (pMap == nullptr)
		{
			return Dummy;
		}

		return *pMap;
	}
}
