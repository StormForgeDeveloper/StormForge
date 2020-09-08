// UnitTest_TexturePng.cpp : Defines the entry point for the console application.
//

#include "UnitTest1PCH.h"
#include <gtest/gtest.h>
#include "SFAssert.h"
#include "Util/SFUtility.h"
#include "ResultCode/SFResultCodeLibrary.h"
#include "Memory/SFMemoryManager.h"
#include "Memory/SFMemory.h"

#include "Task/SFTask.h"

#include "String/SFStringCrc32.h"
#include "String/SFString.h"
#include "Container/SFCircularPageQueue.h"


#include "Asset/Importer/SFAssetImporterTextureTGA.h"
#include "IO/SFFileInputStream.h"


using ::testing::EmptyTestEventListener;
using ::testing::InitGoogleTest;
using ::testing::Test;
using ::testing::TestCase;
using ::testing::TestEventListeners;
using ::testing::TestInfo;
using ::testing::TestPartResult;
using ::testing::UnitTest;
using namespace ::SF;


const uint TestScale = 5;
const uint TEST_COUNT = 4000000 * TestScale;



GTEST_TEST(Texture, TGASimple)
{
	Heap testHeap("test", GetSystemHeap());

	StaticArray<ResourcePtr, 10> resources(testHeap);
	FileInputStream inputStream("data/testImage24.tga");

	AssetImporterTextureTGA* imageImporter = new(testHeap) AssetImporterTextureTGA(testHeap);

	GTEST_ASSERT_EQ(true, inputStream.CanRead());


	AssetImportContext context(testHeap, inputStream, "testImage24.tga");

	auto result = imageImporter->Import(context, resources);
	GTEST_ASSERT_EQ(ResultCode::SUCCESS, result);



	FileInputStream inputStream32("data/testImage32.tga");
	GTEST_ASSERT_EQ(true, inputStream32.CanRead());

	AssetImportContext context32(testHeap, inputStream32, "testImage32.tga");
	result = imageImporter->Import(context32, resources);
	GTEST_ASSERT_EQ(ResultCode::SUCCESS, result);


	// Release before return
	IHeap::Delete(imageImporter);

	for (auto itRes : resources)
	{
		itRes->Dispose();
	}
	resources.Clear();
}
