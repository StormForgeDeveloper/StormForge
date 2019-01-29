////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2016 Kyungkun Ko
// 
// Author : Kyungkun Ko
//
// Description : Result definitions
//	
//
////////////////////////////////////////////////////////////////////////////////


#pragma once

#include <stdint.h>


namespace SF
{

	class Result
	{
		enum {
			CodeBits		= 16,
			FacilityBits	= 12,
			ReservedBits	= 1,
			CustomBits		= 1,
			SeverityBits	= 2,
		};

		union ValueType
		{
			struct
			{
				int32_t Code : CodeBits;
				int32_t Facility : FacilityBits;
				int32_t Reserved : ReservedBits;
				int32_t Custom : CustomBits;
				int32_t Severity : SeverityBits;
			} ByBits;

			// HResult code value
			int32_t HResultCode;

			constexpr ValueType() : HResultCode(0) {}
			constexpr ValueType(int32_t value) : HResultCode(value) {}

		} m_Value;


	public:
		constexpr Result()
			: m_Value(0)
		{
		}

		constexpr Result(int32_t hResultCode)
			: m_Value(hResultCode)
		{
		}


		explicit constexpr operator int32_t() const { return m_Value.HResultCode; }

		explicit constexpr operator uint32_t() const { return (uint32_t)m_Value.HResultCode; }

		operator bool() const { return m_Value.HResultCode >= 0; }

		Result& operator = (const Result& op)
		{
			m_Value.HResultCode = op.m_Value.HResultCode;
			return *this;
		}

		bool operator == (const Result& op) const
		{
			return m_Value.HResultCode == op.m_Value.HResultCode;
		}
		bool operator != (const Result& op) const
		{
			return m_Value.HResultCode != op.m_Value.HResultCode;
		}

		bool operator == (const int32_t& op) const
		{
			return m_Value.HResultCode == op;
		}
		bool operator != (const int32_t& op) const
		{
			return m_Value.HResultCode != op;
		}

	};
}
