// UnitTest_TexturePng.cpp : Defines the entry point for the console application.
//

#include "UnitTest1PCH.h"
#include <gtest/gtest.h>
#include "SFAssert.h"
#include "Util/SFUtility.h"
#include "ResultCode/SFResultCodeLibrary.h"
#include "MemoryManager/SFMemoryManager.h"
#include "MemoryManager/SFMemory.h"
#include "Util/SFPath.h"

#include "Task/SFTask.h"

#include "Util/SFStringCrc32.h"
#include "Util/SFString.h"
#include "Container/SFCircularPageQueue.h"


#include "Asset/Importer/SFAssetImporterTextureJPG.h"
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



GTEST_TEST(Texture, JpgSimple)
{
	Heap testHeap("test", GetSystemHeap());

	StaticArray<ResourcePtr, 10> resources(testHeap);
	auto dirPath = Util::Path::GetFileDirectory(__FILE__);
	auto filePath = Util::Path::Combine(dirPath, "../../data/testImage.jpg");

	FileInputStream inputStream(filePath);

	AssetImporterTextureJPG* imageImporter = new(testHeap) AssetImporterTextureJPG(testHeap);

	GTEST_ASSERT_EQ(true, inputStream.CanRead());

	AssetImportContext context(testHeap, inputStream, "testImage.jpg");

	auto result = imageImporter->Import(context, resources);
	GTEST_ASSERT_EQ(ResultCode::SUCCESS, result);

	// Release before return
	delete (imageImporter);

	for (auto itRes : resources)
	{
		itRes->Dispose();
	}
	resources.Clear();
}
