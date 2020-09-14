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



#include "SFCorePCH.h"
#include "SFTypedefs.h"
#include "Variable/SFNamedVariableBox.h"



namespace SF
{
	
	NamedVariableBox::NamedVariableBox(const NamedVariableBox& src)
		: VariableBox(src)
		, m_Name(src.m_Name)
	{
	}

	NamedVariableBox::NamedVariableBox(StringCrc32 name, const Variable& src)
		: VariableBox(src)
		, m_Name(name)
	{
	}

	bool NamedVariableBox::operator == (const NamedVariableBox& src) const
	{
		auto pVariable = GetVariable();
		auto pSrcVariable = src.GetVariable();

		if (m_Name != src.m_Name)
			return false;

		if (pVariable == nullptr || pSrcVariable == nullptr)
			return pVariable == pSrcVariable;

		return *pVariable == *pSrcVariable;
	}

	NamedVariableBox& NamedVariableBox::operator = (const NamedVariableBox& src)
	{
		m_Name = src.m_Name;
		(*static_cast<VariableBox*>(this)) = src;
		return *this;
	}


} // namespace SF



