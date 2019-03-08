////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2018 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Math utility
//	
//
////////////////////////////////////////////////////////////////////////////////


#pragma once

#include "SFTypedefs.h"


namespace SF
{

	// Math utilities
	namespace Math
	{
		// get absolute value
		template<class Type>
		inline Type Abs(Type value) { return value < 0 ? -value : value; }
	}



} //namespace SF



