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
#include <format>

namespace SF
{

	//////////////////////////////////////////////////////////////////////////////////////
	//
	//  Function context
	//


	// Intended to replace goto Proc_End style with c++ way
	// Function Result handling. If error Func has assigned, it will run the error function on failure when the function scope is finished.
	class ScopeContext
	{
	public:
        using ExitFunc = std::function<void(Result result)>;

		ScopeContext()
			: m_ExitFunc([](Result hr) { return hr; })
		{
		}

		ScopeContext(Result src)
			: m_ExitFunc([](Result hr) { return hr; })
			, m_Hr(src)
		{}
		ScopeContext(ExitFunc&& errorFunc)
			: m_ExitFunc(errorFunc)
		{
		}

		~ScopeContext()
		{
			if (!m_ExitFuncHasCalled)
			{
				m_ExitFuncHasCalled = true;
				m_ExitFunc(m_Hr);
			}
		}

		bool operator == (Result hr) const { return m_Hr == hr; }
		bool operator != (Result hr) const { return m_Hr != hr; }

		ScopeContext& operator = (Result src) { m_Hr = src; return *this; }

		operator Result() const { return m_Hr; }
		operator decltype(auto)() const{ m_ExitFuncHasCalled = true;  return m_ExitFunc(m_Hr); }
        bool IsSuccess() const { return m_Hr.IsSuccess(); }
        bool IsFailure() const { return m_Hr.IsFailure(); }

	private:

		// function will be invoked when it has error
		mutable bool m_ExitFuncHasCalled = false;
		ExitFunc m_ExitFunc;
		Result m_Hr;
	};

}

template <>
struct std::formatter<SF::ScopeContext>
{
    // Specify the default format (e.g., "{}")
    constexpr auto parse(std::format_parse_context& ctx) {
        return ctx.begin();
    }

    // Define how the object is formatted
    template <typename FormatContext>
    auto format(const SF::ScopeContext& value, FormatContext& ctx) const
    {
        return std::format_to(ctx.out(), "{}", (SF::Result)value);
    }
};
