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


#include "SFCorePCH.h"
#include "SFTypedefs.h"
#include "SFAssert.h"
#include "Util/SFStrUtil.h"
#include "Service/SFScriptService.h"



namespace SF
{
	constexpr StringCrc64 ScriptObject::Type_Variable;
	constexpr StringCrc64 ScriptObject::Type_Function;

	ScriptEnvironment::ScriptEnvironment(IHeap& heap, ScriptEnvironment* pParent, const String& name)
		: m_Heap("ScriptEnvironment", heap)
		, m_pParent(pParent)
		, m_Name(GetHeap(), name)
	{
	}

	ScriptEnvironment::~ScriptEnvironment()
	{
	}

} // namespace SF


