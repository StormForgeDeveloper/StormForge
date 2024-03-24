////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2013 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Net test
//	
//
////////////////////////////////////////////////////////////////////////////////

#include <gtest/gtest.h>
#include "Multithread/SFThread.h"
#include "MemoryManager/SFMemoryManager.h"
#include "Util/SFToString.h"
#include "../SFTestBase.h"
#include "Protocol/PlayInstanceRPCSendAdapter.h"
#include "MessageBus/SFMemoryEndpoint.h"
#include "Util/SFGuidHelper.h"
#include "Variable/SFVariableTable.h"

#ifdef DEBUG
#define TestScale 1
#else
#define TestScale 100
#endif



class NetTest : public MyTestBase
{
protected:
    SF::SharedPointerT<SF::MemoryEndpoint> m_MemoryEndpoint;
    SF::GuidGenerator<std::mt19937_64> m_GuidGen;

public:

    SF::MessageDataPtr NewMessage(SF::IHeap& memoryManager, uint32_t sequenceID);
    SF::MessageDataPtr NewMessage(SF::IHeap& memoryManager);

	// Remember that SetUp() is run immediately before a test starts.
	virtual void SetUp()
	{
        m_MemoryEndpoint = new(SF::GetSystemHeap()) SF::MemoryEndpoint();
		MyTestBase::SetUp();
	}

	// TearDown() is invoked immediately after a test finishes.  Here we
	virtual void TearDown()
	{
		MyTestBase::TearDown();
        m_MemoryEndpoint.reset();
	}
};




