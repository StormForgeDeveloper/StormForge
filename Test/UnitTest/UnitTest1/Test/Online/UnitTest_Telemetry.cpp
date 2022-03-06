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

#include "Online/Telemetry/SFTelemetryBR.h"


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
	
	TelemetryBR telemetry;

	auto ret = telemetry.Initialize(m_TelemetryServer, m_TelemetryPort, m_TelemetryClientId, m_TelemetryAuthKey);
	EXPECT_TRUE(ret);

	while (telemetry.IsValid() && !telemetry.IsConnected());

	int iTest = 0;
	for (; telemetry.IsConnected() && iTest < 20; iTest++)
	{
		TelemetryEvent* pTelemetryEvent = telemetry.CreateTelemetryEvent("TestEvent");


		pTelemetryEvent->Send();

		ThisThread::SleepFor(DurationMS(100));
	}

	telemetry.Terminate();

}

