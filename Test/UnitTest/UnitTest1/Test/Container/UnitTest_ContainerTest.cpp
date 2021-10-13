////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2018 Blue3K
// 
// Author : KyungKun Ko
//
// Description : utility
//	
//
////////////////////////////////////////////////////////////////////////////////


#include "UnitTest1PCH.h"
#include <gtest/gtest.h>
#include "SFAssert.h"
#include "Util/SFUtility.h"
#include "ResultCode/SFResultCodeLibrary.h"
#include "MemoryManager/SFMemoryManager.h"
#include "MemoryManager/SFMemory.h"

#include "SFEngine.h"

#include "Util/SFStringCrc32.h"
#include "Util/SFString.h"
#include "Util/SFRandom.h"
#include "Util/SFLog.h"

#include "Container/SFStaticDoubleLinkedList.h"
#include "Container/SFDoubleLinkedListBase.h"

#include "UnitTest_ContainerTest.h"


using ::testing::EmptyTestEventListener;
using ::testing::InitGoogleTest;
using ::testing::Test;
using ::testing::TestCase;
using ::testing::TestEventListeners;
using ::testing::TestInfo;
using ::testing::TestPartResult;
using ::testing::UnitTest;
using namespace ::SF;



class TestData
{
public:
	int Value{};
};


TEST_F(ContainerTest, StaticLinkedList)
{
	Heap testHeap("test", GetSystemHeap());

	StaticDoubleLinkedListT<DoubleLinkedListNodeDataT<TestData>> EmptyList;

	int NumIterated = 0;
	for (auto itData : EmptyList)
	{
		EXPECT_TRUE(itData);
		EXPECT_TRUE(itData->Data.Value == 0);
	}
	EXPECT_TRUE(NumIterated == 0);


	StaticDoubleLinkedListT<DoubleLinkedListNodeDataT<TestData>> TestList;

	for (int iTest = 0; iTest < 100; iTest++)
	{
		auto newData = new DoubleLinkedListNodeDataT<TestData>;
		newData->Data.Value = iTest + 1;
		TestList.Add(newData);
	}

	NumIterated = 0;
	for (auto itData : TestList)
	{
		EXPECT_TRUE(itData);
		NumIterated++;
		EXPECT_TRUE(itData->Data.Value > 0);
	}

	EXPECT_TRUE(NumIterated == TestList.size());
	EXPECT_TRUE(NumIterated == 100);

	auto* pCur = TestList.pop_front();
	while (pCur)
	{
		delete pCur;
		pCur = TestList.pop_front();
	}
}

