////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2018 KyungKun Ko
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
#include "MemoryManager/SFStackHeap.h"
#include "Util/SFTimeUtil.h"
#include "Util/SFRandom.h"
#include "Util/SFToString.h"
#include "Container/SFArray.h"
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


TEST_F(MemoryTest, StackHeap)
{
	SharedPointerT<StackHeapT<1024*512>> stackHeap = new(GetHeap()) StackHeapT<1024 * 512>("testStackHeap", GetHeap());
	StaticArray<int*, 512> allocatedList(GetHeap());

	// out of stack allocation
	auto pPtr = stackHeap->Alloc(1024);
	stackHeap->Free(pPtr);

	// simple alloc/deallocate test
	DynamicArray<void*> testList(GetHeap());
	testList.push_back(stackHeap->Alloc(128));
	testList.push_back(stackHeap->Alloc(32));
	testList.push_back(stackHeap->Alloc(24));
	testList.push_back(stackHeap->Alloc(512));

	stackHeap->Free(testList[2]);
	stackHeap->Free(testList[1]);
	stackHeap->Free(testList[0]);
	stackHeap->Free(testList[3]);

	testList.Clear();


	// zero size allocation test
	testList.push_back(stackHeap->Alloc(0));
	testList.push_back(stackHeap->Alloc(0));
	testList.push_back(stackHeap->Alloc(24));
	testList.push_back(stackHeap->Alloc(512));

	stackHeap->Free(testList[2]);
	stackHeap->Free(testList[1]);
	stackHeap->Free(testList[0]);
	stackHeap->Free(testList[3]);

	testList.Clear();

	auto minAllocationSize = StackHeap::MemoryChunkHeader::CalculateAllocationSize(0);

	for (int iTest = 0; iTest < 10000; iTest++)
	{
		auto randVal = Util::Random.Rand(100);
		if ((allocatedList.size() > 0 && randVal > 50) || stackHeap->GetFreeMemorySize() < minAllocationSize)
		{
			auto pPtr = allocatedList.pop_back();
			IHeap::Delete(pPtr);
		}
		else
		{
			auto pPtr = new(*stackHeap.get()) int[randVal % 10];
			allocatedList.push_back(pPtr);
		}

	}


	for (auto itPtr : allocatedList)
	{
		IHeap::Delete(itPtr);
	}
}

TEST_F(MemoryTest, StackHeap_RandomDelete)
{
	Heap heapForStack("heapForStack", GetHeap());
	Heap heapForSortedSet("heapForSortedSet", GetHeap());
	SharedPointerT<StackHeapT<1024 * 512>> stackHeap = new(heapForStack) StackHeapT<1024 * 512>("testStackHeap", heapForStack);
	SortedSet<int*> allocatedList(heapForSortedSet);

	DynamicArray<void*> testList(GetHeap());
	testList.push_back(stackHeap->Alloc(128));
	testList.push_back(stackHeap->Alloc(32));
	testList.push_back(stackHeap->Alloc(24));
	testList.push_back(stackHeap->Alloc(512));

	stackHeap->Free(testList[2]);
	stackHeap->Free(testList[1]);
	stackHeap->Free(testList[0]);
	stackHeap->Free(testList[3]);

	testList.Clear();

	auto minAllocationSize = StackHeap::MemoryChunkHeader::CalculateAllocationSize(0);

	int breakOnLoopCount = 0x22cb;

	for (int iTest = 0; iTest < 1000000; iTest++)
	{
		if (iTest == breakOnLoopCount)
		{
			breakOnLoopCount = 0;
		}

		auto randVal = Util::Random.Rand(100);
		if ((allocatedList.size() > 0 && randVal > 50) || stackHeap->GetFreeMemorySize() < minAllocationSize)
		{
			randVal = Util::Random.Rand(static_cast<int>(allocatedList.size() - 1));
			auto refCount = stackHeap->GetReferenceCount();
			Assert(refCount >= 2);
			auto pPtr = allocatedList.GetKeyAt(randVal);
			IHeap::Delete(pPtr);
			allocatedList.Remove(pPtr);
			auto refCount2 = stackHeap->GetReferenceCount();
			if (allocatedList.size() > 0)
			{
				EXPECT_GE(refCount2,2);
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
			auto refCount = stackHeap->GetReferenceCount();
			EXPECT_GE(refCount, 1);
			//Assert(refCount >= 1);
			auto pPtr = new(*stackHeap.get()) int[randVal % 10];
			auto refCount2 = stackHeap->GetReferenceCount();
			EXPECT_GE(refCount2, 2);
			//Assert(refCount2 >= 2);
			auto result = allocatedList.Insert(pPtr);
			EXPECT_EQ(ResultCode::SUCCESS, result);
			Assert(result);
		}

	}

	for (auto itPtr : allocatedList)
	{
		IHeap::Delete(itPtr);
	}
	allocatedList.Clear();
}

