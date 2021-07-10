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

	uint32_t LibraryComponentInitializer::stm_CalledMode = 0;
	LibraryComponentInitializer* LibraryComponentInitializer::stm_pHead = nullptr;


	LibraryComponentInitializer::LibraryComponentInitializer()
	{
		m_pNext = stm_pHead;
		stm_pHead = this;

		// call already initialized cases
		for (int iMode = 0; iMode < (int)ComponentInitializeMode::Max; iMode++)
		{
			if ((stm_CalledMode & (uint32_t(1) << iMode)) != 0)
			{
				Initialize((ComponentInitializeMode)iMode);
			}
		}
	}

	LibraryComponentInitializer::~LibraryComponentInitializer()
	{
	}


	void LibraryComponentInitializer::CallInitializers(ComponentInitializeMode InitMode)
	{
		stm_CalledMode |= uint32_t(1) << (int)InitMode;

		auto* pCur = stm_pHead;
		auto* pPrevAccessPoint = &stm_pHead;
		while (pCur)
		{
			bool bRet = pCur->Initialize(InitMode);
			auto pNext = pCur->m_pNext;
			if (bRet)
			{
				// Release current initializer and update prev access point
				pCur->Release();
				*pPrevAccessPoint = pNext;
			}
			else
			{
				// We don't release processed one, just update access point
				pPrevAccessPoint = &pCur->m_pNext;
			}

			pCur = pNext;
		}
	}
}
