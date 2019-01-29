////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2018 StormForge
// 
// Author : KyungKun Ko
//
// Description : Memory
//	
//
////////////////////////////////////////////////////////////////////////////////

#include "UnitTest1PCH.h"
#include <gtest/gtest.h>
#include "Thread/SFSystemSynchronization.h"
#include "Thread/SFThread.h"
#include "Container/SFDualSortedMap.h"
#include "Container/SFSortedArray.h"
#include "Util/SFTimeUtil.h"
#include "Util/SFRandom.h"
#include "String/SFToString.h"
#include "UnitTest_Memory.h"


using ::testing::EmptyTestEventListener;
using ::testing::InitGoogleTest;
using ::testing::Test;
using ::testing::TestCase;
using ::testing::TestEventListeners;
using ::testing::TestInfo;
using ::testing::TestPartResult;
using ::testing::UnitTest;
using namespace ::SF;


//
// This is implementation of spherical shell matching


TEST_F(MemoryTest, Heap)
{
	auto pPtr = (uint8_t*)GetHeap().Alloc(100);
	EXPECT_EQ(nullptr, pPtr);

	for (int i = 0; i < 100; i++)
	{
		pPtr[i] = i + 1;
	}

	SF::SortedArray<FixedString, intptr_t> testArray(GetHeap());
	testArray.Set("a", 1);
	testArray.Set("b", 2);
	testArray.Set("c", 3);
	testArray.Set("d", 4);
	testArray.Set("e", 5);
	testArray.Set("f", 6);
	testArray.Set("g", 7);
	testArray.Set("h", 8);
	testArray.Set("i", 9);
	testArray.Set("j", 10);
	testArray.Set("k", 11);
	testArray.Set("l", 12);
	testArray.Set("m", 13);

	GetHeap().Free(pPtr);
}

