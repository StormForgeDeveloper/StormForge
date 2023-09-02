////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) StormForge
// 
// Author : KyungKun Ko
//
// Description : Stream test
//	
//
////////////////////////////////////////////////////////////////////////////////

#include "UnitTest1PCH.h"
#include <gtest/gtest.h>
#include "SFAssert.h"

#include "Task/SFTask.h"

#include "Util/SFTimeUtil.h"
#include "UnitTest_Telemetry.h"

#include "Online/Telemetry/SFTelemetryClientAvro.h"


using ::testing::EmptyTestEventListener;
using ::testing::InitGoogleTest;
using ::testing::Test;
using ::testing::TestCase;
using ::testing::TestEventListeners;
using ::testing::TestInfo;
using ::testing::TestPartResult;
using ::testing::UnitTest;
using namespace ::SF;


TEST_F(TelemetryTest, Client)
{
	//TelemetryBR telemetry;

	//auto ret = telemetry.Initialize(m_TelemetryServer, m_TelemetryPort, m_TelemetryClientId, m_TelemetryAuthKey);
	//EXPECT_TRUE(ret);

	//while (telemetry.IsValid() && !telemetry.IsConnected());

	//int iTest = 0;
	//for (; telemetry.IsConnected() && iTest < 20; iTest++)
	//{
	//	SFUniquePtr<TelemetryEvent> pTelemetryEvent(telemetry.CreateTelemetryEvent("TestEvent"));

	//	char TestString[128];
	//	StrUtil::Format(TestString, "TestString:{0}", iTest);

	//	pTelemetryEvent->Add("TestData1", iTest);
	//	pTelemetryEvent->Add("TestData2", (int64_t)iTest);
	//	pTelemetryEvent->Add("TestData3", TestString);

	//	pTelemetryEvent.reset();

	//	ThisThread::SleepFor(DurationMS(100));
	//}

	//telemetry.Terminate();
}

