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
#include "Multithread/SFSystemSynchronization.h"
#include "Multithread/SFThread.h"
#include "Container/SFDualSortedMap.h"
#include "Util/SFTimeUtil.h"
#include "Util/SFRandom.h"
#include "Util/SFToString.h"
#include "MemoryManager/SFCircularHeap.h"
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
TEST_F(MemoryTest, CircularHeap)
{
	SharedPointerT<CircularHeapT<1024 * 512>> circularHeap = new CircularHeapT<1024 * 512>(GetHeap());
	StaticArray<int*, 512> allocatedList(GetHeap());

	// out of stack allocation
	auto pPtr = circularHeap->Alloc(1024);
	circularHeap->Free(pPtr);

	// simple alloc/deallocate test
	DynamicArray<void*> testList(GetHeap());
	testList.push_back(circularHeap->Alloc(128));
	testList.push_back(circularHeap->Alloc(32));
	testList.push_back(circularHeap->Alloc(24));
	testList.push_back(circularHeap->Alloc(512));

	circularHeap->Free(testList[2]);
	circularHeap->Free(testList[1]);
	circularHeap->Free(testList[0]);
	circularHeap->Free(testList[3]);

	testList.Clear();


	// zero size allocation test
	testList.push_back(circularHeap->Alloc(0));
	testList.push_back(circularHeap->Alloc(0));
	testList.push_back(circularHeap->Alloc(24));
	testList.push_back(circularHeap->Alloc(512));

	circularHeap->Free(testList[2]);
	circularHeap->Free(testList[1]);
	circularHeap->Free(testList[0]);
	circularHeap->Free(testList[3]);

	testList.Clear();

	auto minAllocationSize = CircularHeap::MemoryChunkHeader::CalculateAllocationSize(0);

	for (int iTest = 0; iTest < 10000; iTest++)
	{
		auto randVal = Util::Random.Rand(100);
		if ((allocatedList.size() > 0 && randVal > 50) || circularHeap->GetFreeMemorySize() < minAllocationSize)
		{
			auto pDeletePtr = allocatedList.pop_back();
            circularHeap->Free(pDeletePtr);
		}
		else
		{
            auto pNewPtr = reinterpret_cast<int*>(circularHeap->Alloc(sizeof(int) * (randVal % 10)));
			allocatedList.push_back(pNewPtr);
		}

	}


	for (auto itPtr : allocatedList)
	{
        circularHeap->Free(itPtr);
	}
}

TEST_F(MemoryTest, CircularHeap_RandomDelete)
{
	Heap heapForStack("heapForStack", GetHeap());
	Heap heapForSortedSet("heapForSortedSet", GetHeap());
	SharedPointerT<CircularHeapT<1024 * 512>> circularHeap = new CircularHeapT<1024 * 512>(heapForStack);
	SortedSet<int*> allocatedList(heapForSortedSet);

	DynamicArray<void*> testList(GetHeap());
	testList.push_back(circularHeap->Alloc(128));
	testList.push_back(circularHeap->Alloc(32));
	testList.push_back(circularHeap->Alloc(24));
	testList.push_back(circularHeap->Alloc(512));

	circularHeap->Free(testList[2]);
	circularHeap->Free(testList[1]);
	circularHeap->Free(testList[0]);
	circularHeap->Free(testList[3]);

	testList.Clear();

	auto minAllocationSize = CircularHeap::MemoryChunkHeader::CalculateAllocationSize(0);

	int breakOnLoopCount = 0x22cb;

	for (int iTest = 0; iTest < 1000000; iTest++)
	{
		if (iTest == breakOnLoopCount)
		{
			breakOnLoopCount = 0;
		}

		auto randVal = Util::Random.Rand(100);
		if (allocatedList.size() > 0 && (randVal > 50 || circularHeap->GetFreeMemorySize() < minAllocationSize))
		{
			randVal = Util::Random.Rand(static_cast<int>(allocatedList.size() - 1));
			auto refCount = circularHeap->GetReferenceCount();
			Assert(refCount >= 2);
			unused(refCount);
			auto pPtr = allocatedList.GetKeyAt(randVal);
            circularHeap->Free(pPtr);
			allocatedList.Remove(pPtr);
			auto refCount2 = circularHeap->GetReferenceCount();
			if (allocatedList.size() > 0)
			{
				EXPECT_GE(refCount2, 2);
				//Assert(refCount2 >= 2);
			}
			else
			{
				EXPECT_GE(refCount2, 1);
				//Assert(refCount2 >= 1);
			}
		}
		else
		{
			auto refCount = circularHeap->GetReferenceCount();
			EXPECT_GE(refCount, 1);
			//Assert(refCount >= 1);
            auto pPtr = reinterpret_cast<int*>(circularHeap->Alloc(sizeof(int) * (randVal % 10)));
			auto refCount2 = circularHeap->GetReferenceCount();
			EXPECT_GE(refCount2, 2);
			//Assert(refCount2 >= 2);
			auto result = allocatedList.Insert(pPtr);
			EXPECT_EQ(ResultCode::SUCCESS, result);
			Assert(result);
		}

	}

	for (auto itPtr : allocatedList)
	{
		circularHeap->Free(itPtr);
	}
	allocatedList.Clear();
}
