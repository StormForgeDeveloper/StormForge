////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2016 Kyungkun Ko
// 
// Author: Kyungkun Ko
//
// Description : Base type ToString implementation
//	
//
////////////////////////////////////////////////////////////////////////////////


#pragma once


#include "SFTypedefs.h"
#include "Util/SFStrUtil.h"
#include "Container/SFArray.h"
#include "ResultCode/SFResultCodeSystem.h"


namespace SF {



	///////////////////////////////////////////////////////////////////////////////////
	//
	// ToString Context
	//

	struct ToStringContext
	{
		char*		StringBuffer = nullptr;
		int			StringBufferLength = 0;

		unsigned	Radix			= 10;
		int			MaxDigit		= 100;
		int			MaxCharacters	= std::numeric_limits<int>::max();
		int			MaxArraySize	= 20;
	};


	///////////////////////////////////////////////////////////////////////////////////
	//
	// ToString helper implementations
	//


	// 
	Result _IToA(ToStringContext& context, int8_t val);
	Result _IToA(ToStringContext& context, uint8_t val);
	Result _IToA(ToStringContext& context, int16_t val);
	Result _IToA(ToStringContext& context, uint16_t val);
	Result _IToA(ToStringContext& context, int32_t val);
	Result _IToA(ToStringContext& context, uint32_t val);
	Result _IToA(ToStringContext& context, int64_t val);
	Result _IToA(ToStringContext& context, uint64_t val);


	Result _FToA(ToStringContext& context, double val);



}; // namespace SF



