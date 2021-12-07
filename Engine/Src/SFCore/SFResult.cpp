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

	const char* Result::ToString() const
	{
		auto& stringMap = ResultTable::GetFacility(m_Value.ByBits.Facility);
		auto pStr = stringMap.find(m_Value.HResultCode);
		if (pStr.CodeName != nullptr)
		{
			return pStr.CodeName;
		}
		else
		{
			return "UNKNOWN_ERROR_CODE";
		}
	}

	const char* Result::ToDescString() const
	{
		auto& stringMap = ResultTable::GetFacility(m_Value.ByBits.Facility);
		auto pStr = stringMap.find(m_Value.HResultCode);
		if (pStr.CodeName != nullptr)
		{
			return pStr.CodeDesc;
		}
		else
		{
			return "UNKNOWN_ERROR_CODE";
		}
	}

}
