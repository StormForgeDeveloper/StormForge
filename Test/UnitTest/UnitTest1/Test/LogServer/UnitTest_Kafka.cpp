// UnitTest_Zookeeper.cpp : Defines the entry point for the console application.
//

#include "UnitTest1PCH.h"
#include <gtest/gtest.h>
#include "SFAssert.h"

#include "Task/SFTask.h"

#include "String/SFStringCrc32.h"
#include "String/SFString.h"
#include "Container/SFCircularPageQueue.h"
#include "UnitTest_Kafka.h"

#include "rdkafka.h"



using ::testing::EmptyTestEventListener;
using ::testing::InitGoogleTest;
using ::testing::Test;
using ::testing::TestCase;
using ::testing::TestEventListeners;
using ::testing::TestInfo;
using ::testing::TestPartResult;
using ::testing::UnitTest;
using namespace ::SF;




GTEST_TEST(Kafka, Simple)
{
}



