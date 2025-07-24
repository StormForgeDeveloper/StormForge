////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) Kyungkun Ko
// 
// Author : Kyungkun Ko
//
// Description : Result definitions
//	
//
////////////////////////////////////////////////////////////////////////////////


#pragma once

#include <stdint.h>
#include <format>

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

        explicit operator bool() const { return m_Value.HResultCode >= 0; }

        uint32_t GetHResultCode() const { return m_Value.HResultCode; }

        bool IsSuccess() const { return m_Value.HResultCode >= 0; }
        bool IsFailure() const { return m_Value.HResultCode < 0; }

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

        const char* GetNameString() const;

		const char* ToString() const;
		const char* ToDescString() const;
	};
}

namespace std
{
    template <>
    struct formatter<SF::Result>
    {
        // Specify the default format (e.g., "{}")
        constexpr auto parse(std::format_parse_context& ctx) {
            return ctx.begin();
        }

        // Define how the object is formatted
        template <typename FormatContext>
        auto format(const SF::Result& value, FormatContext& ctx) const
        {
            const char* name = value.GetNameString();
            if (name)
            {
                return std::format_to(ctx.out(), "{}", name);
            }
            else
            {
                return std::format_to(ctx.out(), "{0:#08x}", value.GetHResultCode());
            }
        }
    };

}
