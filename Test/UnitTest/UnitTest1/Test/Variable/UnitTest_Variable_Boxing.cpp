// Algorithm test.
//

#include "UnitTest1PCH.h"
#include <gtest/gtest.h>
#include "Multithread/SFSystemSynchronization.h"
#include "Multithread/SFThread.h"
#include "MemoryManager/SFStackHeap.h"
#include "Util/SFTimeUtil.h"
#include "Util/SFRandom.h"
#include "Util/SFToString.h"
#include "Container/SFArray.h"
#include "UnitTest_Variable.h"
#include "Stream/SFMemoryStream.h"
#include "Variable/SFVariableSerialization.h"
#include "Util/SFStrUtil.h"
#include "Util/SFStrFormat.h"
#include "Util/SFToStringEngineTypes.h"
#include "Types/SFEngineTypeSerialization.h"

using ::testing::EmptyTestEventListener;
using ::testing::InitGoogleTest;
using ::testing::Test;
using ::testing::TestCase;
using ::testing::TestEventListeners;
using ::testing::TestInfo;
using ::testing::TestPartResult;
using ::testing::UnitTest;
using namespace ::SF;




TEST_F(VariableTest, Boxing1)
{
	DynamicArray<FriendInformation> testFriendList(GetSystemHeap());
	FriendInformation test;
	test.FBUID = 1;
	testFriendList.push_back(test);
	test.FBUID = 2;
	testFriendList.push_back(test);

	const Array< FriendInformation>& testFriendListC = testFriendList;
	char testString[512];
	StrUtil::Format(testString, "{0}", testFriendList);
	StrUtil::Format(testString, "{0}", testFriendListC);


	auto boxedFriendList = Boxing(GetSystemHeap(), testFriendList);
	auto pFriendList = UnboxingReference<Array<FriendInformation>>(boxedFriendList);
	for (auto& fr : *pFriendList)
	{
		StrUtil::Format(testString, "{0}", fr);
	}

}

