////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2018 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Script service
//	
//
////////////////////////////////////////////////////////////////////////////////


#include "CoreBasePCH.h"
#include "SFTypedefs.h"
#include "SFAssert.h"
#include "String/SFStrUtil.h"
#include "Service/SFScriptService.h"



namespace SF
{
	constexpr FixedString ScriptObject::Type_Variable;
	constexpr FixedString ScriptObject::Type_Function;

	ScriptEnvironment::ScriptEnvironment(IHeap& heap, ScriptEnvironment* pParent, const String& name)
		: m_Heap("ScriptEnvironment", heap)
		, m_pParent(pParent)
		, m_Name(m_Heap, name)
	{
	}

	ScriptEnvironment::~ScriptEnvironment()
	{
	}

} // namespace SF


