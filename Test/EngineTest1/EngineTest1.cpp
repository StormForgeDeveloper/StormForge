// EngineTest1.cpp : Defines the entry point for the console application.
//

#include "EngineTest1PCH.h"
#include "gtest\gtest.h"
#include "SFTypedefs.h"

using ::testing::EmptyTestEventListener;
using ::testing::InitGoogleTest;
using ::testing::Test;
using ::testing::TestCase;
using ::testing::TestEventListeners;
using ::testing::TestInfo;
using ::testing::TestPartResult;
using ::testing::UnitTest;
using namespace ::SF;


// --gtest_catch_exceptions=0 to disable exception catch


int main(int argc, char **argv)
{
	InitGoogleTest(&argc, argv);

	UnitTest& unit_test = *UnitTest::GetInstance();

	int iRes = RUN_ALL_TESTS();


    return iRes;
}

