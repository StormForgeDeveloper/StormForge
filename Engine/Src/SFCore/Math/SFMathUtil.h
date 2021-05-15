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

		template<>
		inline unsigned int Abs(unsigned int x)
		{
			return x;
		}

		template<class ValueType>
		constexpr ValueType Min(ValueType val1, ValueType val2)
		{
			return (((val1) < (val2)) ? (val1) : (val2));
		}

		template<class ValueType>
		constexpr ValueType Max(ValueType val1, ValueType val2)
		{
			return (((val1) > (val2)) ? (val1) : (val2));
		}

		// Find least significant bit index
		inline int FindLSBIndex(uint32_t value)
		{
			if (value == 0)
				return -1;

			uint32_t TestMaxBits = sizeof(decltype(value)) * 8;
			auto TestMask = static_cast<decltype(value)>(-1);
			uint32_t bitIndex = 0;

			for (int iLoop = 0; iLoop < 5; iLoop++)
			{
				TestMaxBits >>= 1;
				TestMask >>= TestMaxBits;
				if ((TestMask & value) == 0)
				{
					value >>= TestMaxBits;
					bitIndex += TestMaxBits;
				}
			}

			return bitIndex;
		}
	}



} //namespace SF



