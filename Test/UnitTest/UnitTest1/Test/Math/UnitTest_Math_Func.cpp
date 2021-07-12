// UnitTestMath3DVector.cpp : Defines the entry point for the console application.
//

#include "UnitTest1PCH.h"
#include <gtest/gtest.h>
#include "Container/SFDualSortedMap.h"
#include "UnitTest_Math.h"


using ::testing::EmptyTestEventListener;
using ::testing::InitGoogleTest;
using ::testing::Test;
using ::testing::TestCase;
using ::testing::TestEventListeners;
using ::testing::TestInfo;
using ::testing::TestPartResult;
using ::testing::UnitTest;
using namespace ::SF;



TEST_F(MathTest, Util)
{
	uint32_t TestValues[] = { 0x800, 0x799, 798 };

	for (auto TestValue : TestValues)
	{
		uint32_t Local1 = Math::Find1FromMSB(TestValue - 1);
		uint32_t Local12 = Math::Find1FromMSBConstexpr(TestValue - 1);
		EXPECT_EQ(Local1, Local12);

		uint32_t LocalLog = Math::CeilLogTwo(TestValue);
		uint32_t LocalLog2 = Math::CeilLogTwoConstexpr(TestValue);
		EXPECT_EQ(LocalLog, LocalLog2);

		uint32_t PO2Value = Math::RoundUpToPowerOfTwo(TestValue);
		uint32_t PO2Value2 = Math::RoundUpToPowerOfTwoConstexpr(TestValue);

		EXPECT_EQ(PO2Value, PO2Value2);
	}

}




