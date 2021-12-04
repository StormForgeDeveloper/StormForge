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
#include "Variable/SFNamedVariableArray.h"


namespace SF {



	////////////////////////////////////////////////////////////////////////////////
	//
	//	Variable serialization size calculations
	//


	size_t SerializedSizeOf(const Variable& Value);
	size_t SerializedSizeOf(const VariableBox& Value);
	size_t SerializedSizeOf(const NamedVariableBox& Value);
	size_t SerializedSizeOf(const VariableTable& Value);

	Result operator >> (IInputStream& input, VariableBox& data);
	Result operator << (IOutputStream& output, const VariableBox& data);

	Result operator >> (IInputStream& input, NamedVariableBox& data);
	Result operator << (IOutputStream& output, const NamedVariableBox& data);

	Result operator >> (IInputStream& input, VariableTable& data);
	Result operator << (IOutputStream& output, const VariableTable& data);

	size_t SerializedSizeOf(const NamedVariableArray& Value);
	Result operator >> (IInputStream& input, NamedVariableArray& data);
	Result operator << (IOutputStream& output, const NamedVariableArray& data);



} // namespace SF
