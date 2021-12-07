////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) Kyungkun Ko
// 
// Author : Kyungkun Ko
//
// Description : Result code table
//	
//
////////////////////////////////////////////////////////////////////////////////


#pragma once

#include "SFTypedefs.h"
#include "SFResult.h"
#include "Container/SFSortedArray.h"

namespace SF
{
	/////////////////////////////////////////////////////////////////////
	// 
	//	Result code table to convert result code into string
	class ResultTable
	{
	public:

		struct ResultString
		{
			const char* CodeName{};
			const char* CodeDesc{};
		};
		using ResultMap = SortedArray<uint32_t, ResultString>;

		static ResultMap& GetOrAddFacility(uint32_t facility);
		static const ResultMap& GetFacility(uint32_t facility);

	private:

		SortedArray<uint32_t, ResultMap*> FacilityMaps;
		

		static UniquePtr<ResultTable> stm_Instance;
	};

}
