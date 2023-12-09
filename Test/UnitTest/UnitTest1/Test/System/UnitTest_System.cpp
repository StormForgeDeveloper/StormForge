// UnitTestMath3DVector.cpp : Defines the entry point for the console application.
//

#include "UnitTest1PCH.h"
#include <gtest/gtest.h>
#include "Container/SFDualSortedMap.h"
#include "UnitTest_System.h"
#include "Platform/SFCPUInfo.h"

using ::testing::EmptyTestEventListener;
using ::testing::InitGoogleTest;
using ::testing::Test;
using ::testing::TestCase;
using ::testing::TestEventListeners;
using ::testing::TestInfo;
using ::testing::TestPartResult;
using ::testing::UnitTest;
using namespace ::SF;


TEST_F(SystemTest, Util)
{
    SFLog(System, Info, "CPUInfo {0}", CPUInfo::Vendor());

    EXPECT_TRUE(CPUInfo::GetFeatures().SSE);
    EXPECT_TRUE(CPUInfo::GetFeatures().SSE2);
    EXPECT_TRUE(CPUInfo::GetFeatures().SSE3);
    EXPECT_TRUE(CPUInfo::GetFeatures().SSE41);
    EXPECT_TRUE(CPUInfo::GetFeatures().SSE42);
    EXPECT_TRUE(CPUInfo::GetFeatures().AVX);
    // AVX2 is optional

}

