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
	private:
		StringCrc32 m_Name;

	public:

		NamedVariableBox() = default;
		NamedVariableBox(const NamedVariableBox& src);
		NamedVariableBox(StringCrc32 name, const Variable& src);

		void SetName(StringCrc32 Name) { m_Name = Name; }
		StringCrc32 GetName() const { return m_Name; }

		~NamedVariableBox() = default;

		bool operator == (const NamedVariableBox& src) const;

		NamedVariableBox& operator = (const NamedVariableBox& src);
	};


} // namespace SF



