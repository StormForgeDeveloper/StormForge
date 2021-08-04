// UnitTest1.cpp : Defines the entry point for the console application.
//

#include "UnitTest1PCH.h"
#include <gtest/gtest.h>
#include "SFAssert.h"
#include "Util/SFUtility.h"

#include "SFEngine.h"




using ::testing::EmptyTestEventListener;
using ::testing::InitGoogleTest;
using ::testing::Test;
using ::testing::TestCase;
using ::testing::TestEventListeners;
using ::testing::TestInfo;
using ::testing::TestPartResult;
using ::testing::UnitTest;
using namespace ::SF;

// --gtest_filter=NetTest.RecvMessageWindowMT2 --gtest_catch_exceptions=0 --gtest_break_on_failure
// to disable exception catch
// --gtest_catch_exceptions=0 --gtest_break_on_failure

int main(int argc, char** argv)
{
	EngineInitParam initParam;
	initParam.GlobalLogOutputMask.Factal = 1;
	initParam.GlobalLogOutputMask.Error = 1;
	initParam.GlobalLogOutputMask.Warning = 1;
	initParam.GlobalLogOutputMask.Info = 1;
	initParam.LogOutputDebugger.Composited = uint32_t(-1);
	initParam.LogOutputConsole.Composited = uint32_t(-1);
	initParam.EnableMemoryLeakDetection = true;
	initParam.GraphicSystem = "Vulkan";

	Engine::Start(initParam);

	InitGoogleTest(&argc, argv);

	//UnitTest& unit_test = *UnitTest::GetInstance();

	int iRes = RUN_ALL_TESTS();

	SF::Service::LogModule->Flush();

	Engine::Stop();

	return iRes;
}

