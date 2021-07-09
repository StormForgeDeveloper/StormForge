////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : utility
//	
//
////////////////////////////////////////////////////////////////////////////////


#include "SFCorePCH.h"
#include "SFTypedefs.h"
#include "Util/SFLog.h"
#include "Component/SFLibraryComponentInitializer.h"



namespace SF {


	LibraryComponentInitializer* LibraryComponentInitializer::stm_pHead = nullptr;


	LibraryComponentInitializer::LibraryComponentInitializer()
	{
		m_pNext = stm_pHead;
		stm_pHead = this;
	}

	LibraryComponentInitializer::~LibraryComponentInitializer()
	{
	}


	void LibraryComponentInitializer::CallInitializers(ComponentInitializeMode InitMode)
	{
		auto pCur = stm_pHead;
		for (; pCur; pCur = pCur->m_pNext)
		{
			pCur->Initialize(InitMode);
		}
	}


}


