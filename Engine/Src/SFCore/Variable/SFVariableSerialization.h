////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Variable serialization
//	
//
////////////////////////////////////////////////////////////////////////////////


#pragma once


#include "SFTypedefs.h"
#include "SFAssert.h"
#include "ResultCode/SFResultCodeSystem.h"
#include "Variable/SFVariableBoxing.h"
#include "Service/SFService.h"
#include "Stream/SFStream.h"
#include "Variable/SFVariableTable.h"
#include "Variable/SFNamedVariableBox.h"


namespace SF {



	////////////////////////////////////////////////////////////////////////////////
	//
	//	Variable serialization size calculations
	//


	inline size_t SerializedSizeOf(const Variable& Value);
	inline size_t SerializedSizeOf(const VariableBox& Value);
	inline size_t SerializedSizeOf(const NamedVariableBox& Value);
	inline size_t SerializedSizeOf(const VariableTable& Value);


	Result operator >> (IInputStream& input, VariableBox& data);
	Result operator << (IOutputStream& output, const VariableBox& data);

	Result operator >> (IInputStream& input, NamedVariableBox& data);
	Result operator << (IOutputStream& output, const NamedVariableBox& data);

	Result operator >> (IInputStream& input, VariableTable& data);
	Result operator << (IOutputStream& output, const VariableTable& data);



} // namespace SF
