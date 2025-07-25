////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2020 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Variables
//
////////////////////////////////////////////////////////////////////////////////


#pragma once


#include "SFTypedefs.h"
#include "SFAssert.h"
#include "Util/SFStringCrc32.h"

namespace SF {


	class Variable;


	/////////////////////////////////////////////////////////////////////////////////
	//
	//	variable Factory
	//

	class VariableFactoryService
	{
	public:
		VariableFactoryService() = default;
		virtual ~VariableFactoryService() = default;

		virtual Variable* CreateVariable(StringCrc32 TypeName);
	};

} // namespace SF




