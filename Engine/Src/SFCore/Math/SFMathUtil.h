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
		template<class Type>
        constexpr SF_FORCEINLINE Type Clamp(Type mi, Type ma, Type value)
		{
			if (value < mi) value = mi;
			if (value > ma) value = ma;
			return value;
		}

		// get absolute value
		template<class Type>
        constexpr SF_FORCEINLINE Type Abs(Type value) { return value < 0 ? -value : value; }

		template<>
        constexpr SF_FORCEINLINE unsigned int Abs(unsigned int x)
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


        constexpr SF_FORCEINLINE float DistanceCmToM(float cm)
		{
			return cm / 100.f;
		}

        constexpr SF_FORCEINLINE float DistanceMToCm(float m)
        {
            return m * 100.f;
        }

        constexpr SF_FORCEINLINE float SlerpDegree(float a, float b, float t)
		{
			a = Math::Clamp(0.f, 360.f, a);
			b = Math::Clamp(0.f, 360.f, b);

			if (Math::Abs(a - b) < 180)
			{
				return a + (b - a) * t;
			}
			else
			{
				if (a > b)
				{
					b += 360;
				}
				else
				{
					a += 360;
				}
				return Math::Clamp(0.f, 360.f, a + (b - a) * t);
			}
		}


		SF_FORCEINLINE uint32_t FloorLog2(uint32_t Value)
		{
			// Use BSR to return the log2 of the integer
#if _MSC_VER
			unsigned long Log2 = 0;
			if (_BitScanReverse(&Log2, Value) != 0)
			{
				return Log2;
			}
			return 0;
#else
			int32_t Mask = -int32_t(Value != 0);
			return (31 - __builtin_clz(Value)) & Mask;
#endif
			return 0;
		}

		SF_FORCEINLINE uint64_t FloorLog2(uint64_t Value)
		{
			// Use BSR to return the log2 of the integer
#if _MSC_VER
			unsigned long Log2;
			long Mask = -long(_BitScanReverse64(&Log2, Value) != 0);
			return Log2 & Mask;
#else
			int64_t Mask = -int64_t(Value != 0);
			return (63 - __builtin_clzll(Value)) & Mask;
#endif
		}

		SF_FORCEINLINE uint32_t Find1FromLSB(uint32_t Value)
		{
			if (Value == 0)
			{
				return uint32_t(-1);
			}
#if _MSC_VER
			unsigned long BitIndex;	// 0-based, where the LSB is 0 and MSB is 31
			_BitScanForward(&BitIndex, Value);	// Scans from LSB to MSB
			return BitIndex;
#else
			return __builtin_ctz(Value);
#endif
		}

		SF_FORCEINLINE constexpr uint32_t Find1FromLSBConstexpr(uint32_t Value)
		{
			if (Value == 0)
			{
				return 32;
			}

			uint32_t index = 0;
			uint32_t LowBits = Value & 0xFFFF;
			if (LowBits)
				Value = LowBits;
			else
			{
				Value >>= 16;
				index += 16;
			}

			LowBits = Value & 0xFF;
			if (LowBits)
				Value = LowBits;
			else
			{
				Value >>= 8;
				index += 8;
			}

			LowBits = Value & 0xF;
			if (LowBits)
				Value = LowBits;
			else
			{
				Value >>= 4;
				index += 4;
			}

			LowBits = Value & 0x3;
			if (LowBits)
				Value = LowBits;
			else
			{
				Value >>= 2;
				index += 2;
			}

			LowBits = Value & 0x2;
			return index + ((LowBits) ? 0 : 1);
		}

		SF_FORCEINLINE uint32_t Find1FromLSB(uint64_t Value)
		{
			if (Value == 0)
			{
				return uint32_t(-1);
			}
#if _MSC_VER
			unsigned long BitIndex;	// 0-based, where the LSB is 0 and MSB is 31
			_BitScanForward64(&BitIndex, Value);	// Scans from LSB to MSB
			return BitIndex;
#else
			return __builtin_ctzll(Value);
#endif
		}

		SF_FORCEINLINE uint32_t Find1FromMSB(uint32_t Value)
		{
#if _MSC_VER
			unsigned long Log2;
			_BitScanReverse64(&Log2, (uint64_t(Value) << 1) | 1);
			return 32 - Log2;
#else
			return __builtin_clzll((uint64_t(Value) << 1) | 1) - 31;
#endif
		}

		SF_FORCEINLINE constexpr uint32_t Find1FromMSBConstexpr(uint32_t Value)
		{
			if (Value == 0)
			{
				return 32;
			}

			uint32_t index = 0;
			uint32_t HighBits = Value & 0xFFFF0000L;
			if (HighBits)
			{
				Value >>= 16;
			}
			else
			{
				//Value &= 0xFFFF;
				index += 16;
			}

			HighBits = Value & 0xFF00L;
			if (HighBits)
			{
				Value >>= 8;
			}
			else
			{
				//Value &= 0xFF;
				index += 8;
			}

			HighBits = Value & 0xF0L;
			if (HighBits)
			{
				Value >>= 4;
			}
			else
			{
				index += 4;
			}

			HighBits = Value & 0xC;
			if (HighBits)
			{
				Value >>= 2;
			}
			else
			{
				index += 2;
			}

			HighBits = Value & 0x2;
			return index + (HighBits ? 0 : 1);
		}

		SF_FORCEINLINE uint64_t Find1FromMSB(uint64_t Value)
		{
#if _MSC_VER
			unsigned long Log2;
			long Mask = -long(_BitScanReverse64(&Log2, Value) != 0);
			return ((63 - Log2) & Mask) | (64 & ~Mask);
#else
			if (Value == 0)
			{
				return 64;
			}

			return __builtin_clzll(Value);
#endif
		}

		SF_FORCEINLINE uint32_t CeilLogTwo(uint32_t Arg)
		{
			int32_t Bitmask = ((int32_t)(Find1FromMSB(Arg) << 26)) >> 31;
			return (32 - Find1FromMSB(Arg - 1)) & (~Bitmask);
		}

		SF_FORCEINLINE constexpr uint32_t CeilLogTwoConstexpr(uint32_t Arg)
		{
			int32_t Bitmask = ((int32_t)(Find1FromMSBConstexpr(Arg) << 26)) >> 31;
			return (32 - Find1FromMSBConstexpr(Arg - 1)) & (~Bitmask);
		}

		SF_FORCEINLINE uint64_t CeilLogTwo(uint64_t Arg)
		{
			int64_t Bitmask = ((int64_t)(Find1FromMSB(Arg) << 57)) >> 63;
			return (64 - Find1FromMSB(Arg - 1)) & (~Bitmask);
		}

		SF_FORCEINLINE uint32_t RoundUpToPowerOfTwo(uint32_t Arg)
		{
			return uint32_t(1) << CeilLogTwo(Arg);
		}

		SF_FORCEINLINE constexpr uint32_t RoundUpToPowerOfTwoConstexpr(uint32_t Arg)
		{
			return (uint32_t)(uint64_t(1) << CeilLogTwoConstexpr(Arg));
		}

		SF_FORCEINLINE uint64_t RoundUpToPowerOfTwo(uint64_t Arg)
		{
			return uint64_t(1) << CeilLogTwo(Arg);
		}

	}



} //namespace SF



