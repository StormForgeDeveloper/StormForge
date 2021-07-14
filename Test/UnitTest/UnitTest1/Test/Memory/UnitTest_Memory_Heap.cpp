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
#include "Container/SFSortedArray.h"
#include "Util/SFTimeUtil.h"
#include "Util/SFRandom.h"
#include "Util/SFToString.h"
#include "UnitTest_Memory.h"
#include "MemoryManager/SFHeapMemory.h"


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
	EXPECT_NE(nullptr, pPtr);

	for (int i = 0; i < 100; i++)
	{
		pPtr[i] = (uint8_t)(i + 1);
	}

	SF::SortedArray<StringCrc64, intptr_t> testArray(GetHeap());
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


TEST_F(MemoryTest, NewDelete)
{

	class TestAllocationObject
	{
	public:

		// Constructor
		TestAllocationObject()
		{
		}

		~TestAllocationObject()
		{
		}

	public:

		// Is available
		bool m_isAvailable{};

	private:
		// PreferencePlayer ID
		uint m_PlayerID{};

		// preference vector
		Vector4 m_PackedFactors[8]{};

		// current Shell Index, if belong to a Shell
		uint m_CurrentShellID = (uint)(-1);
		Mutex m_ShellLock;
	};


	auto arrayValue = new(GetHeap()) TestAllocationObject[204800];
	IHeap::Delete(arrayValue);
}

TEST_F(MemoryTest, HeapMemory)
{
	struct TestItem
	{
		uint32_t ItemCategory : 8;
		uint32_t ItemEquipType : 2;
		uint32_t Count : 16;
		uint32_t : 0;
		uint32_t ItemId{};
	};


	SF::StaticMemoryAllocatorT<256> localHeap("localHeap", GetHeap());
	SF::DynamicArray<TestItem> OutUpdated(localHeap);
	std::vector<void*> allocated;
	for (int iTest = 0; iTest < 10; iTest++)
	{
		auto allocSize = 64;
		auto pAllocated = localHeap.Alloc(allocSize);
		memset(pAllocated, allocSize, allocSize);
		allocated.push_back(pAllocated);
	}

	for (auto itAllocated : allocated)
	{
		localHeap.Free(itAllocated);
	}
	allocated.clear();

	SF::StaticMemoryAllocatorT<4096> categoryHeap("testHeap", GetHeap());
	{
		SF::DynamicArray<TestItem> Items(categoryHeap);
		Items.push_back(TestItem{});
		SF::SortedMap<uint32_t, SF::DynamicArray<TestItem*>*> ItemByItemID(categoryHeap);
	}
}

TEST_F(MemoryTest, HeapMemoryRandom)
{
	struct TestItem
	{
		uint32_t ItemCategory : 8;
		uint32_t ItemEquipType : 2;
		uint32_t Count : 16;
		uint32_t : 0;
		uint32_t ItemId{};
	};


	SF::StaticMemoryAllocatorT<1024> localHeap("localHeap", GetHeap());
	std::vector<void*> allocated;

	for (int iTest = 0; iTest < 100; iTest++)
	{
		auto allocSize = SF::Util::Random.Rand(32, 128);
		auto pAllocated = localHeap.Alloc(allocSize);
		memset(pAllocated, allocSize, allocSize);
		allocated.push_back(pAllocated);
		if (SF::Util::Random.Rand(0, 100) > 60)
		{
			auto index = SF::Util::Random.Rand(0, (int)allocated.size() - 1);
			localHeap.Free(allocated[index]);
			allocated.erase(allocated.begin() + index);
		}
	}

	while(allocated.size() > 0)
	{
		auto index = SF::Util::Random.Rand(0, (int)allocated.size() - 1);
		localHeap.Free(allocated[index]);
		allocated.erase(allocated.begin() + index);
	}
	
}
