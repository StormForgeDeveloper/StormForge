////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2020 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Base type ToString implementation
//	
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "SFTypedefs.h"
#include "SFAssert.h"
#include "Variable/SFVariableBoxing.h"
#include "Variable/SFNamedVariableBox.h"
#include "Variable/SFVariableTable.h"
#include "Variable/SFVariableSerialization.h"


namespace SF
{


	Result _ToString(ToStringContext& context, const NamedVariableBox& value);
	Result _ToString(ToStringContext& context, const VariableTable& value);


	DECLARE_BOXING_TEMPLETE_BYVALUE(NamedVariableBox);
	DECLARE_BOXING_TEMPLETE_BYREFERENCE(VariableTable);

} // namespace SF

