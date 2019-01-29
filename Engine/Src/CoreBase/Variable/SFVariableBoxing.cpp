////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2016 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : VariableBox
//	
//
////////////////////////////////////////////////////////////////////////////////



#include "CoreBasePCH.h"
#include "SFTypedefs.h"
#include "Variable/SFVariableBoxing.h"
#include "String/SFToString.h"


namespace SF
{
	
	////////////////////////////////////////////////////////////////////////////////
	//
	//	VariableBox class
	//

	constexpr int VariableBox::BUFFER_SIZE;

	VariableBox::VariableBox()
		: m_DataBuffer(GetSystemHeap())
	{
	}

	VariableBox::VariableBox(const VariableBox& src)
		: m_DataBuffer(GetSystemHeap())
	{
		if(src.m_pVariable != nullptr)
			m_pVariable = src.m_pVariable->Clone(m_DataBuffer);
	}

	VariableBox::VariableBox(const Variable& src)
		: m_DataBuffer(GetSystemHeap())
	{
		m_pVariable = src.Clone(m_DataBuffer);
	}

	VariableBox::~VariableBox()
	{
		if (m_pVariable != nullptr)
			m_pVariable->~Variable();
		m_pVariable = nullptr;
	}
	//void VariableBox::GetValueString(ToStringContext& context) const
	//{
	//	if (m_pVariable)
	//	{
	//		m_pVariable->ToString(context);
	//	}

	//}
	VariableBox& VariableBox::operator = (const VariableBox& src)
	{
		if (m_pVariable != nullptr)
			m_pVariable->~Variable();
		m_pVariable = nullptr;

		if (src.m_pVariable != nullptr)
			m_pVariable = src.m_pVariable->Clone(m_DataBuffer);
		return *this;
	}


	void TestFunc()
	{
		bool TestBool = true;
		auto boxBool = Boxing(TestBool);
		Assert(Unboxing<bool>(boxBool) == TestBool);

		int TestInt = 10;
		auto boxInt = Boxing(TestInt);
		Assert(Unboxing<int>(boxInt) == TestInt);

		const char* testCharString = "TestString";
		auto boxCharStr = Boxing(testCharString);
		Assert(Unboxing<const char*>(boxCharStr) == testCharString);
	}


/*
	template< >
	class ArgumentWrapperT<double> : public VariableBox
	{
	private:
		double m_Data;
		unsigned m_digitAfterDecimalPoint;

	public:
		ArgumentWrapperT(double src, unsigned digitAfterDecimalPoint = 5)
			:m_Data(src),
			m_digitAfterDecimalPoint(digitAfterDecimalPoint)
		{
		}

		ArgumentWrapperT(const ArgumentWrapperT& src)
			: m_Data(src.m_Data)
			, m_digitAfterDecimalPoint(src.m_digitAfterDecimalPoint)
		{
		}

		VariableBox* Clone(INT iBuffLen, uint8_t* pBuff) const override
		{
			AssertRel(iBuffLen >= sizeof(ArgumentWrapperT<double>));
			return new(pBuff)ArgumentWrapperT<double>(*this);
		}

		virtual void GetValueString(char*& pBuff, INT& iBuffLen) const
		{
			ToString<double>(pBuff, iBuffLen, m_Data, (int)(m_digitAfterDecimalPoint << 16));
		}
	};
*/





//	template class ArgumentWrapperT < int8_t>;
//	template class ArgumentWrapperT < uint8_t>;
//	template class ArgumentWrapperT < int16_t>;
//	template class ArgumentWrapperT < uint16_t>;
//	template class ArgumentWrapperT < int32_t>;
//	template class ArgumentWrapperT < uint32_t>;
//	template class ArgumentWrapperT < int64_t>;
//	template class ArgumentWrapperT < uint64_t>;
//#if SF_PLATFORM == SF_PLATFORM_WINDOWS
//	//template class ArgumentWrapperT < long>;
//	//template class ArgumentWrapperT < unsigned long>;
//	template class ArgumentWrapperT < char>;
//#endif
//	template class ArgumentWrapperT < LPCSTR>;
//	template class ArgumentWrapperT < LPSTR>;
//	template class ArgumentWrapperT < wchar_t>;
//	template class ArgumentWrapperT < LPCWSTR>;
//	template class ArgumentWrapperT < LPWSTR>;
//	template class ArgumentWrapperT < std::string>;
//	template class ArgumentWrapperT < std::wstring>;
//    template class ArgumentWrapperT < Result>;

}; // namespace StrUtil



