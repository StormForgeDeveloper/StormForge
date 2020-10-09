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
			return Size;
		}



} // namespace SF



