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


#include "Asset/Importer/SFAssetImporterTexturePNG.h"
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


GTEST_TEST(Texture, PngSimple)
{
	Heap testHeap("test", GetSystemHeap());
	
	StaticArray<ResourcePtr,10> resources(testHeap);
	FileInputStream inputStream("data/testImage.png");

	AssetImporterTexturePNG* png = new(testHeap) AssetImporterTexturePNG(testHeap);

	GTEST_ASSERT_EQ(true, inputStream.CanRead());

	AssetImportContext context(testHeap, inputStream, "testImage.png");

	auto result = png->Import(context, resources);
	GTEST_ASSERT_EQ(ResultCode::SUCCESS, result);

	// Release before return
	IHeap::Delete(png);

	for (auto itRes : resources)
	{
		itRes->Dispose();
	}
	resources.Clear();
}
