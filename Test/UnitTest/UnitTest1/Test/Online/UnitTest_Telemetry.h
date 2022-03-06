////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2019 StormForge
// 
// Author : KyungKun Ko
//
// Description : AVL tree test
//	
//
////////////////////////////////////////////////////////////////////////////////



#include <gtest/gtest.h>
#include "Multithread/SFThread.h"
#include "MemoryManager/SFMemoryManager.h"
#include "Util/SFToString.h"
#include "../SFTestBase.h"
#include "json/json.h"


// common setting class
class TelemetryTest : public MyTestBase
{
protected:

#ifdef DEBUG
	const int MAX_TEST_VALUE = 100;
#else
	const int MAX_TEST_VALUE = 1100000;
#endif

	// Heap for test
	SF::Heap m_Heap;

	// Thread module test
	std::vector<SF::Thread*>	m_Threads;

	SF::SpinLock m_LockObject;

	SF::String m_TelemetryServer;
	int m_TelemetryPort{};
	SF::String m_TelemetryClientId;
	SF::String m_TelemetryAuthKey;


public:

	TelemetryTest()
		: m_Heap("TelemetryTest", SF::GetSystemHeap())
	{

	}

	// Heap interface
	SF::IHeap& GetHeap() { return m_Heap; }


	// Stop all thread
	void StopAllThread()
	{
		std::for_each( m_Threads.begin(), m_Threads.end(), []( SF::Thread* pThread )
		{
			if( pThread ) pThread->Stop( true );
			SF::IHeap::Delete(pThread);
		});
		m_Threads.clear();
	}

	// Remember that SetUp() is run immediately before a test starts.
	virtual void SetUp()
	{
		MyTestBase::SetUp();

		m_TelemetryServer = m_ConfigJson.get("TelemetryServer", "").asCString();
		m_TelemetryPort = m_ConfigJson.get("TelemetryPort", 1111).asInt();
		m_TelemetryClientId = m_ConfigJson.get("TelemetryClientId", "").asCString();
		m_TelemetryAuthKey = m_ConfigJson.get("TelemetryAuthKey", "").asCString();
	}

	// TearDown() is invoked immediately after a test finishes.  Here we
	virtual void TearDown()
	{
		MyTestBase::TearDown();

		StopAllThread();
	}
};

