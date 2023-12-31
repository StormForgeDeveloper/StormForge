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

	//////////////////////////////////////////////////////////////////////////////////////
	//
	//  Function context
	//


	// Intended to replace goto Proc_End style with c++ way
	// Function Result handling. If error Func has assigned, it will run the error function on failure when the function scope is finished.
	template<typename ExitFunc = std::function<void(Result result)>>
	class ScopeContext
	{
	public:

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
