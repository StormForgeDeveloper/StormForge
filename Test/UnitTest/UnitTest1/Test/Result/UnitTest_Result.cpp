// Algorithm test.
//

#include "UnitTest1PCH.h"
#include <gtest/gtest.h>
#include "SFResult.h"
#include "ResultCode/SFResultCodeEngine.h"
#include "UnitTest_Result.h"

using ::testing::EmptyTestEventListener;
using ::testing::InitGoogleTest;
using ::testing::Test;
using ::testing::TestCase;
using ::testing::TestEventListeners;
using ::testing::TestInfo;
using ::testing::TestPartResult;
using ::testing::UnitTest;
using namespace ::SF;


TEST_F(ResultTest , ToString)
{
	EXPECT_TRUE(StrUtil::StringCompair("ENGINE_INITIALIZATION_FAILED", ResultCode::ENGINE_INITIALIZATION_FAILED.ToString(), (int)strlen("ENGINE_INITIALIZATION_FAILED")));
}

