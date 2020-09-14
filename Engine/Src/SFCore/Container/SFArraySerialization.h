////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2019 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Array 
//	
//
////////////////////////////////////////////////////////////////////////////////


#pragma once

#include "SFTypedefs.h"
#include "SFAssert.h"
#include "Container/SFArray.h"

namespace SF {


		////////////////////////////////////////////////////////////////////////////////
		//
		//	Serialization
		//

		template<class DataType>
		inline size_t SerializedSizeOf(const Array<DataType>& Value)
		{
			size_t Size = sizeof(uint16_t);
			for (auto& itVar : Value)
			{
				Size += SerializedSizeOf(itVar);
			}
			return ResultCode::SUCCESS;
		}

		//template<class DataType>
		//inline Result IInputStream::Read(Array<DataType>& data)
		//{
		//	uint16_t NumItems{};
		//	if (!Read(NumItems))
		//		return ResultCode::END_OF_STREAM;

		//	data.reserve(NumItems);

		//	for (uint32_t iItem = 0; iItem < NumItems; iItem++)
		//	{
		//		DataType Item;
		//		auto Ret = Read(Item);
		//		if (!Ret)
		//			return Ret;

		//		data.push_back(Item);
		//	}

		//	return ResultCode::SUCCESS;
		//}



} // namespace SF



