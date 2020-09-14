////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2020 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : NamedVariableBox
//	
//
////////////////////////////////////////////////////////////////////////////////


#pragma once

#include "SFTypedefs.h"
#include "Variable/SFVariableBoxing.h"



namespace SF {


	////////////////////////////////////////////////////////////////////////////////
	//
	// VariableBox 
	// 
	class NamedVariableBox : public VariableBox
	{
	public:

		using NameType = StringCrc32;


	private:
		NameType m_Name;

	public:

		NamedVariableBox() = default;
		NamedVariableBox(const NamedVariableBox& src);
		NamedVariableBox(StringCrc32 name, const Variable& src);

		void SetName(NameType Name) { m_Name = Name; }
		NameType GetName() const { return m_Name; }

		~NamedVariableBox() = default;

		bool operator == (const NamedVariableBox& src) const;

		NamedVariableBox& operator = (const NamedVariableBox& src);
	};


} // namespace SF



