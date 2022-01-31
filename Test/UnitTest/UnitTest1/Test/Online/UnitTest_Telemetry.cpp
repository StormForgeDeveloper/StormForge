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

#include "Util/SFStringCrc32.h"
#include "Util/SFString.h"
#include "Container/SFCircularPageQueue.h"
#include "Util/SFTimeUtil.h"
#include "UnitTest_Telemetry.h"

#include "Online/Telemetry/SFTelemetry.h"


#include "Protocol/PlayInstanceMsgClass.h"


using ::testing::EmptyTestEventListener;
using ::testing::InitGoogleTest;
using ::testing::Test;
using ::testing::TestCase;
using ::testing::TestEventListeners;
using ::testing::TestInfo;
using ::testing::TestPartResult;
using ::testing::UnitTest;
using namespace ::SF;


TEST_F(TelemetryTest, Simple)
{
	//m_ConfigJson;
 //   const char* topic = "MyTestTopic1";
 //   uint8_t testData[] = {1,2,3,4,5,6,7,8,9};
 //   uint8_t testData1[] = { 'T', 'e', 's', 't', 'D', 'a', 't', 'a', 'D', 'a', 't', 'a', '\0' };
	//uint8_t testData2[] = { 1,2,3,4,5,6,7,8,9, 123 };

 //   StreamDBProducer streamDB;

 //   GTEST_ASSERT_EQ(streamDB.Initialize(m_StreamServerAddress[0], topic), ResultCode::SUCCESS);

 //   GTEST_ASSERT_EQ(streamDB.SendRecord(ArrayView<const uint8_t>(testData)), ResultCode::SUCCESS);
	//GTEST_ASSERT_EQ(streamDB.SendRecord(ArrayView<const uint8_t>(testData1)), ResultCode::SUCCESS);
	//GTEST_ASSERT_EQ(streamDB.SendRecord(ArrayView<const uint8_t>(testData2)), ResultCode::SUCCESS);

 //   GTEST_ASSERT_EQ(streamDB.Flush(), ResultCode::SUCCESS);
    
}

