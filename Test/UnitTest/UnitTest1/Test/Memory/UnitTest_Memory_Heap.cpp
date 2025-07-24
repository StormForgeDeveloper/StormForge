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
	auto pPtr = (uint8_t*)GetSystemHeap().Alloc(100);
	EXPECT_NE(nullptr, pPtr);

	for (int i = 0; i < 100; i++)
	{
		pPtr[i] = (uint8_t)(i + 1);
	}

	SF::SortedArray<StringCrc64, intptr_t> testArray(GetSystemHeap());
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

    GetSystemHeap().Free(pPtr);
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


	auto arrayValue = new TestAllocationObject[204800];
	delete[] arrayValue;
}

TEST_F(MemoryTest, HeapMemory)
{
	struct TestItem
	{
		uint32_t InvenCategory : 8;
		uint32_t ItemEquipType : 2;
		uint32_t Count : 16;
		uint32_t : 0;
		uint32_t ItemId{};
	};


	SF::StaticMemoryAllocatorT<256> localHeap("localHeap", GetSystemHeap());
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

	SF::StaticMemoryAllocatorT<4096> categoryHeap("testHeap", GetSystemHeap());
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
		uint32_t InvenCategory : 8;
		uint32_t ItemEquipType : 2;
		uint32_t Count : 16;
		uint32_t : 0;
		uint32_t ItemId{};
	};


	SF::StaticMemoryAllocatorT<1024> localHeap("localHeap", GetSystemHeap());
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

TEST_F(MemoryTest, HeapMemoryRandomSameSize)
{
	constexpr size_t TestDataSize = 0x20;

	SF::StaticMemoryAllocatorT<8*1024> localHeap("localHeap", GetSystemHeap());
	std::vector<void*> allocated;

	for (int iTest = 0; iTest < 100; iTest++)
	{
		auto pAllocated = localHeap.Alloc(TestDataSize);
		memset(pAllocated, TestDataSize, TestDataSize);

		allocated.push_back(pAllocated);
	}

	while (allocated.size() > 0)
	{
		auto index = SF::Util::Random.Rand(0, (int)allocated.size() - 1);
		localHeap.Free(allocated[index]);
		allocated.erase(allocated.begin() + index);
	}

}


static const HeapMemoryHistory g_TestHeapPattern[] =
{
{ 'A', 0, 0x70,4208,16 },
{ 'A', 0, 0x11a0,4208,16 },
{ 'A', 0, 0x22d0,4208,16 },
{ 'A', 0, 0x3400,4208,16 },
{ 'A', 0, 0x4530,8,16 },
{ 'A', 0, 0x4600,240,16 },
{ 'A', 0, 0x47b0,424,16 },
{ 'A', 0, 0x4a20,16,16 },
{ 'A', 0, 0x4af0,16,16 },
{ 'A', 0, 0x4bc0,640,16 },
{ 'F',0x4af0, 0, 0, 0 },
{ 'F',0x4a20, 0, 0, 0 },
{ 'A', 0, 0x4a20,72,16 },
{ 'A', 0, 0x4f00,1025,16 },
{ 'A', 0, 0x53d0,72,16 },
{ 'A', 0, 0x54e0,24,16 },
{ 'F',0x54e0, 0, 0, 0 },
{ 'F',0x53d0, 0, 0, 0 },
{ 'F',0x4f00, 0, 0, 0 },
{ 'F',0x4a20, 0, 0, 0 },
{ 'A', 0, 0x4a20,72,16 },
{ 'A', 0, 0x4f00,1025,16 },
{ 'F',0x4f00, 0, 0, 0 },
{ 'F',0x4a20, 0, 0, 0 },
{ 'A', 0, 0x4a20,16,16 },
{ 'A', 0, 0x4f00,536,16 },
{ 'A', 0, 0x51e0,16,16 },
{ 'A', 0, 0x52b0,160,16 },
{ 'A', 0, 0x5410,16,16 },
{ 'A', 0, 0x54e0,56,16 },
{ 'A', 0, 0x55e0,640,16 },
{ 'A', 0, 0x5920,72,16 },
{ 'A', 0, 0x5a30,1025,16 },
{ 'A', 0, 0x5f00,72,16 },
{ 'A', 0, 0x6010,32,16 },
{ 'F',0x6010, 0, 0, 0 },
{ 'F',0x5f00, 0, 0, 0 },
{ 'F',0x5a30, 0, 0, 0 },
{ 'F',0x5920, 0, 0, 0 },
{ 'A', 0, 0x5920,72,16 },
{ 'A', 0, 0x5a30,1025,16 },
{ 'F',0x5a30, 0, 0, 0 },
{ 'F',0x5920, 0, 0, 0 },
{ 'A', 0, 0x5920,72,16 },
{ 'A', 0, 0x5a30,544,16 },
{ 'A', 0, 0x5d10,72,16 },
{ 'A', 0, 0x5e20,1025,16 },
{ 'A', 0, 0x62f0,72,16 },
{ 'A', 0, 0x6400,23,16 },
{ 'F',0x6400, 0, 0, 0 },
{ 'F',0x62f0, 0, 0, 0 },
{ 'F',0x5e20, 0, 0, 0 },
{ 'F',0x5d10, 0, 0, 0 },
{ 'A', 0, 0x5d10,72,16 },
{ 'A', 0, 0x5e20,1025,16 },
{ 'F',0x5e20, 0, 0, 0 },
{ 'F',0x5d10, 0, 0, 0 },
{ 'A', 0, 0x5d10,16,16 },
{ 'A', 0, 0x5de0,160,16 },
{ 'A', 0, 0x5f40,16,16 },
{ 'A', 0, 0x6010,56,16 },
{ 'A', 0, 0x6110,640,16 },
{ 'A', 0, 0x6450,16,16 },
{ 'A', 0, 0x6520,16,16 },
{ 'F',0x6520, 0, 0, 0 },
{ 'F',0x6450, 0, 0, 0 },
{ 'A', 0, 0x6450,72,16 },
{ 'A', 0, 0x6560,1025,16 },
{ 'A', 0, 0x6a30,72,16 },
{ 'A', 0, 0x6b40,55,16 },
{ 'F',0x6b40, 0, 0, 0 },
{ 'F',0x6a30, 0, 0, 0 },
{ 'F',0x6560, 0, 0, 0 },
{ 'F',0x6450, 0, 0, 0 },
{ 'A', 0, 0x6450,72,16 },
{ 'A', 0, 0x6560,1025,16 },
{ 'A', 0, 0x6a30,72,16 },
{ 'A', 0, 0x6b40,16,16 },
{ 'F',0x6b40, 0, 0, 0 },
{ 'F',0x6a30, 0, 0, 0 },
{ 'F',0x6560, 0, 0, 0 },
{ 'F',0x6450, 0, 0, 0 },
{ 'F',0x5920, 0, 0, 0 },
{ 'F',0x51e0, 0, 0, 0 },
{ 'F',0x5410, 0, 0, 0 },
{ 'F',0x52b0, 0, 0, 0 },
{ 'F',0x55e0, 0, 0, 0 },
{ 'F',0x4f00, 0, 0, 0 },
{ 'A', 0, 0x55e0,72,16 },
{ 'A', 0, 0x56f0,72,16 },
{ 'A', 0, 0x4f00,1025,16 },
{ 'A', 0, 0x5800,72,16 },
{ 'A', 0, 0x6450,50,16 },
{ 'F',0x6450, 0, 0, 0 },
{ 'F',0x5800, 0, 0, 0 },
{ 'F',0x4f00, 0, 0, 0 },
{ 'F',0x56f0, 0, 0, 0 },
{ 'A', 0, 0x56f0,40,16 },
{ 'A', 0, 0x57e0,16,16 },
{ 'A', 0, 0x4f00,16,16 },
{ 'A', 0, 0x4fd0,160,16 },
{ 'F',0x57e0, 0, 0, 0 },
{ 'A', 0, 0x57e0,40,16 },
{ 'A', 0, 0x5130,40,16 },
{ 'F',0x57e0, 0, 0, 0 },
{ 'A', 0, 0x6450,800,16 },
{ 'F',0x4fd0, 0, 0, 0 },
{ 'F',0x56f0, 0, 0, 0 },
{ 'A', 0, 0x4fd0,80,16 },
{ 'A', 0, 0x5220,72,16 },
{ 'A', 0, 0x5330,34,16 },
{ 'A', 0, 0x56f0,2,16 },
{ 'R',0x56f0,0x56f0,6,16 },
{ 'R',0x56f0,0x56f0,10,16 },
{ 'R',0x56f0,0x56f0,18,16 },
{ 'R',0x56f0,0x56f0,22,16 },
{ 'R',0x56f0,0x56f0,26,16 },
{ 'R',0x56f0,0x56f0,28,16 },
{ 'R',0x56f0,0x56f0,34,16 },
{ 'R',0x56f0,0x56f0,38,16 },
{ 'R',0x56f0,0x56f0,42,16 },
{ 'R',0x56f0,0x56f0,44,16 },
{ 'R',0x56f0,0x56f0,76,16 },
{ 'F',0x56f0, 0, 0, 0 },
{ 'A', 0, 0x56f0,4,16 },
{ 'R',0x56f0,0x56f0,6,16 },
{ 'R',0x56f0,0x56f0,8,16 },
{ 'R',0x56f0,0x56f0,20,16 },
{ 'F',0x56f0, 0, 0, 0 },
{ 'F',0x4fd0, 0, 0, 0 },
{ 'F',0x5330, 0, 0, 0 },
{ 'F',0x5220, 0, 0, 0 },
{ 'A', 0, 0x56f0,624,16 },
{ 'A', 0, 0x4fd0,16,16 },
{ 'A', 0, 0x5220,160,16 },
{ 'A', 0, 0x6830,16,16 },
{ 'A', 0, 0x6900,64,16 },
{ 'A', 0, 0x6a00,2,16 },
{ 'A', 0, 0x6ad0,2,16 },
{ 'A', 0, 0x6ba0,72,16 },
{ 'A', 0, 0x6cb0,2,16 },
{ 'A', 0, 0x6d80,160,16 },
{ 'F',0x6ad0, 0, 0, 0 },
{ 'A', 0, 0x6ad0,2,16 },
{ 'A', 0, 0x6ee0,72,16 },
{ 'A', 0, 0x6ff0,2,16 },
{ 'F',0x6ad0, 0, 0, 0 },
{ 'R',0x6a00,0x6a00,6,16 },
{ 'R',0x6a00,0x6a00,10,16 },
{ 'R',0x6a00,0x6a00,14,16 },
{ 'A', 0, 0x6ad0,14,16 },
{ 'A', 0, 0x70c0,72,16 },
{ 'A', 0, 0x71d0,14,16 },
{ 'F',0x6ad0, 0, 0, 0 },
{ 'A', 0, 0x72a0,640,16 },
{ 'A', 0, 0x6ad0,16,16 },
{ 'A', 0, 0x75e0,16,16 },
{ 'F',0x75e0, 0, 0, 0 },
{ 'F',0x6ad0, 0, 0, 0 },
{ 'A', 0, 0x75e0,72,16 },
{ 'A', 0, 0x76f0,1025,16 },
{ 'A', 0, 0x7bc0,72,16 },
{ 'A', 0, 0x7cd0,94,16 },
{ 'F',0x7cd0, 0, 0, 0 },
{ 'F',0x7bc0, 0, 0, 0 },
{ 'F',0x76f0, 0, 0, 0 },
{ 'F',0x75e0, 0, 0, 0 },
{ 'A', 0, 0x75e0,72,16 },
{ 'A', 0, 0x76f0,1025,16 },
{ 'A', 0, 0x7bc0,72,16 },
{ 'A', 0, 0x6ad0,16,16 },
{ 'F',0x6ad0, 0, 0, 0 },
{ 'F',0x7bc0, 0, 0, 0 },
{ 'F',0x76f0, 0, 0, 0 },
{ 'F',0x75e0, 0, 0, 0 },
{ 'F',0x6a00, 0, 0, 0 },
{ 'F',0x6900, 0, 0, 0 },
{ 'F',0x55e0, 0, 0, 0 },
{ 'F',0x5d10, 0, 0, 0 },
{ 'F',0x5f40, 0, 0, 0 },
{ 'F',0x5de0, 0, 0, 0 },
{ 'F',0x4f00, 0, 0, 0 },
{ 'F',0x5130, 0, 0, 0 },
{ 'F',0x6450, 0, 0, 0 },
{ 'F',0x6110, 0, 0, 0 },
{ 'F',0x5a30, 0, 0, 0 },
{ 'A', 0, 0x55e0,72,16 },
{ 'A', 0, 0x5a30,1025,16 },
{ 'A', 0, 0x6900,72,16 },
{ 'A', 0, 0x6110,100,16 },
{ 'F',0x6110, 0, 0, 0 },
{ 'F',0x6900, 0, 0, 0 },
{ 'F',0x5a30, 0, 0, 0 },
{ 'F',0x55e0, 0, 0, 0 },
{ 'A', 0, 0x55e0,72,16 },
{ 'A', 0, 0x6900,80,16 },
{ 'A', 0, 0x5a30,72,16 },
{ 'A', 0, 0x5130,34,16 },
{ 'A', 0, 0x4f00,4,16 },
{ 'R',0x4f00,0x4f00,6,16 },
{ 'R',0x4f00,0x4f00,8,16 },
{ 'A', 0, 0x5b40,20,16 },
{ 'F',0x4f00, 0, 0, 0 },
{ 'F',0x5b40, 0, 0, 0 },
{ 'F',0x6900, 0, 0, 0 },
{ 'F',0x5130, 0, 0, 0 },
{ 'F',0x5a30, 0, 0, 0 },
{ 'A', 0, 0x5a30,544,16 },
{ 'A', 0, 0x6900,72,16 },
{ 'A', 0, 0x6110,1025,16 },
{ 'A', 0, 0x65e0,72,16 },
{ 'A', 0, 0x5130,23,16 },
{ 'F',0x5130, 0, 0, 0 },
{ 'F',0x65e0, 0, 0, 0 },
{ 'F',0x6110, 0, 0, 0 },
{ 'F',0x6900, 0, 0, 0 },
{ 'A', 0, 0x6900,72,16 },
{ 'A', 0, 0x6110,1025,16 },
{ 'F',0x6110, 0, 0, 0 },
{ 'F',0x6900, 0, 0, 0 },
{ 'A', 0, 0x4f00,16,16 },
{ 'A', 0, 0x6900,160,16 },
{ 'A', 0, 0x5130,16,16 },
{ 'A', 0, 0x6110,640,16 },
{ 'A', 0, 0x5d10,16,16 },
{ 'A', 0, 0x5de0,16,16 },
{ 'F',0x5de0, 0, 0, 0 },
{ 'F',0x5d10, 0, 0, 0 },
{ 'A', 0, 0x5d10,72,16 },
{ 'A', 0, 0x75e0,1025,16 },
{ 'A', 0, 0x5e20,72,16 },
{ 'A', 0, 0x6450,55,16 },
{ 'F',0x6450, 0, 0, 0 },
{ 'F',0x5e20, 0, 0, 0 },
{ 'F',0x75e0, 0, 0, 0 },
{ 'F',0x5d10, 0, 0, 0 },
{ 'A', 0, 0x5d10,72,16 },
{ 'A', 0, 0x75e0,1025,16 },
{ 'A', 0, 0x5e20,72,16 },
{ 'A', 0, 0x6450,16,16 },
{ 'F',0x6450, 0, 0, 0 },
{ 'F',0x5e20, 0, 0, 0 },
{ 'F',0x75e0, 0, 0, 0 },
{ 'F',0x5d10, 0, 0, 0 },
{ 'F',0x6cb0, 0, 0, 0 },
{ 'F',0x6ba0, 0, 0, 0 },
{ 'F',0x6ff0, 0, 0, 0 },
{ 'F',0x6ee0, 0, 0, 0 },
{ 'F',0x71d0, 0, 0, 0 },
{ 'F',0x70c0, 0, 0, 0 },
{ 'F',0x6d80, 0, 0, 0 },
{ 'F',0x55e0, 0, 0, 0 },
{ 'F',0x4fd0, 0, 0, 0 },
{ 'F',0x6830, 0, 0, 0 },
{ 'F',0x5220, 0, 0, 0 },
{ 'F',0x72a0, 0, 0, 0 },
{ 'F',0x56f0, 0, 0, 0 },
{ 'A', 0, 0x4fd0,72,16 },
{ 'A', 0, 0x5220,16,16 },
{ 'A', 0, 0x52f0,160,16 },
{ 'A', 0, 0x5d10,40,16 },
{ 'A', 0, 0x5e00,40,16 },
{ 'A', 0, 0x55e0,72,16 },
{ 'A', 0, 0x56f0,2,16 },
{ 'A', 0, 0x57c0,72,16 },
{ 'A', 0, 0x6450,14,16 },
{ 'A', 0, 0x6520,72,16 },
{ 'A', 0, 0x6630,2,16 },
{ 'A', 0, 0x6ba0,800,16 },
{ 'F',0x5220, 0, 0, 0 },
{ 'F',0x5d10, 0, 0, 0 },
{ 'F',0x5e00, 0, 0, 0 },
{ 'F',0x56f0, 0, 0, 0 },
{ 'F',0x55e0, 0, 0, 0 },
{ 'F',0x6450, 0, 0, 0 },
{ 'F',0x57c0, 0, 0, 0 },
{ 'F',0x6630, 0, 0, 0 },
{ 'F',0x6520, 0, 0, 0 },
{ 'F',0x52f0, 0, 0, 0 },
{ 'A', 0, 0x5d10,536,16 },
{ 'A', 0, 0x5220,16,16 },
{ 'A', 0, 0x52f0,160,16 },
{ 'A', 0, 0x55e0,16,16 },
{ 'A', 0, 0x56b0,640,16 },
{ 'A', 0, 0x6450,72,16 },
{ 'A', 0, 0x6f80,1025,16 },
{ 'A', 0, 0x6560,72,16 },
{ 'A', 0, 0x6670,32,16 },
{ 'F',0x6670, 0, 0, 0 },
{ 'F',0x6560, 0, 0, 0 },
{ 'F',0x6f80, 0, 0, 0 },
{ 'F',0x6450, 0, 0, 0 },
{ 'A', 0, 0x6450,72,16 },
{ 'A', 0, 0x6f80,1025,16 },
{ 'F',0x6f80, 0, 0, 0 },
{ 'F',0x6450, 0, 0, 0 },
{ 'F',0x4fd0, 0, 0, 0 },
{ 'F',0x4f00, 0, 0, 0 },
{ 'F',0x5130, 0, 0, 0 },
{ 'F',0x6900, 0, 0, 0 },
{ 'F',0x6ba0, 0, 0, 0 },
{ 'F',0x6110, 0, 0, 0 },
{ 'F',0x5a30, 0, 0, 0 },
{ 'A', 0, 0x5a30,72,16 },
{ 'F',0x5a30, 0, 0, 0 },
{ 'F',0x5220, 0, 0, 0 },
{ 'F',0x55e0, 0, 0, 0 },
{ 'F',0x52f0, 0, 0, 0 },
{ 'F',0x56b0, 0, 0, 0 },
{ 'F',0x5d10, 0, 0, 0 },

};

TEST_F(MemoryTest, HeapMemoryTestPattern1)
{
	using TestHeapType = SF::StaticMemoryAllocatorT<2 * 1024 * 1024>;

	SFUniquePtr<TestHeapType> localHeap(new TestHeapType("localHeap", GetSystemHeap()));

	// This is not memory leak test. just memory break things test
	localHeap->SetIgnoreMemmoryLeak(true);
	
	HeapMemoryHistory::ReplayHistory(*localHeap, reinterpret_cast<const uint8_t*>(localHeap->GetBaseMemoryBlock()), countof(g_TestHeapPattern), g_TestHeapPattern);

}
