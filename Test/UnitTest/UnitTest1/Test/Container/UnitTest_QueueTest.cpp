// QueueTest
//

#include "UnitTest1PCH.h"
#include <gtest/gtest.h>
#include "SFAssert.h"
#include "Util/SFUtility.h"
#include "ResultCode/SFResultCodeLibrary.h"
#include "MemoryManager/SFMemoryManager.h"
#include "MemoryManager/SFMemory.h"

#include "SFEngine.h"

#include "String/SFStringCrc32.h"
#include "String/SFString.h"
#include "Container/SFCircularPageQueue.h"




using ::testing::EmptyTestEventListener;
using ::testing::InitGoogleTest;
using ::testing::Test;
using ::testing::TestCase;
using ::testing::TestEventListeners;
using ::testing::TestInfo;
using ::testing::TestPartResult;
using ::testing::UnitTest;
using namespace ::SF;




GTEST_TEST(Container, QueueSimple)
{
	Heap testHeap("test", GetSystemHeap());

	Engine::GetEngineComponent<Log::LogModule>()->Flush();
}


