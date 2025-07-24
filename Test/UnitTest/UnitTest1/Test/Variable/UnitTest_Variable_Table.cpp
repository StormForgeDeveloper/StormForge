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
#include "Util/SFGuid.h"
#include "Util/SFGuidHelper.h"
#include "Types/SFEngineTypedefs.h"
#include "Types/SFEngineTypeSerialization.h"
#include "Types/SFEngineTypeVariable.h"

using ::testing::EmptyTestEventListener;
using ::testing::InitGoogleTest;
using ::testing::Test;
using ::testing::TestCase;
using ::testing::TestEventListeners;
using ::testing::TestInfo;
using ::testing::TestPartResult;
using ::testing::UnitTest;
using namespace ::SF;




TEST_F(VariableTest, Table)
{
	VariableTable table;

	auto boxedInt = Boxing(10);
	table.SetVariable("testInt", *boxedInt.GetVariable());

	auto boxedFloat = Boxing(10.f);
	table.SetVariable("testFloat", *boxedFloat.GetVariable());

	auto boxedDouble = Boxing(10.);
	table.SetVariable("testDouble", *boxedDouble.GetVariable());

	auto testInt = table.GetValue<int>("testInt");
	auto testFloat = table.GetValue<float>("testFloat");
	auto testDouble = table.GetValue<double>("testDouble");
	EXPECT_EQ(boxedInt.GetVariable()->GetValue<int>(), testInt);
	EXPECT_EQ(boxedFloat.GetVariable()->GetValue<float>(), testFloat);
	EXPECT_EQ(boxedDouble.GetVariable()->GetValue<double>(), testDouble);
}



TEST_F(VariableTest, Table2)
{
	VariableTable table;

	auto boxedInt = Boxing(10);
	table.SetVariable("testInt", *boxedInt.GetVariable());
	table.SetVariable("testInt", *boxedInt.GetVariable());

	auto boxedFloat = Boxing(10.f);
	table.SetVariable("testFloat", *boxedFloat.GetVariable());
	table.SetVariable("testFloat", *boxedFloat.GetVariable());

	auto boxedDouble = Boxing(10.);
	table.SetVariable("testDouble", *boxedDouble.GetVariable());
	table.SetVariable("testDouble", *boxedDouble.GetVariable());

	EXPECT_EQ(boxedInt.GetVariable()->GetValue<int>(), table.GetValue<int>("testInt"));
	EXPECT_EQ(boxedFloat.GetVariable()->GetValue<float>(), table.GetValue<float>("testFloat"));
	EXPECT_EQ(boxedDouble.GetVariable()->GetValue<double>(), table.GetValue<double>("testDouble"));
}



TEST_F(VariableTest, Serialization)
{
	VariableTable table1;
	DynamicArray<uint8_t> table1Bin;
    Guid testGuid = GuidHelper::New();
    EntityID entityUid(12345);
    AccountID testAccountId(GuidHelper::New());

	table1.SetValue("sex", 1);
	table1.SetValue("hat", 10);
	table1.SetValue("shoes", 10);
	table1.SetValue("Name", "testName1234");

    table1.SetValue("UID", testGuid);
    Guid testGuidRes = table1.GetValue<Guid>("UID");
    EXPECT_EQ(testGuidRes, testGuid);

    table1.SetValue("EntityUID", entityUid);
    EntityID entityUidRes = table1.GetValue<uint32_t>("EntityUID");
    EXPECT_EQ(entityUidRes, entityUid);

    table1.SetValue("AccountID", testAccountId);
    AccountID testAccountIdRes = table1.GetValue<AccountID>("AccountID");
    EXPECT_EQ(testAccountIdRes, testAccountId);


	uint8_t testData[] = {12,114,54,66,234, 235};
	SFUniquePtr<Variable> blobVar(new VariableBLOB(ArrayView<uint8_t>(sizeof(testData), testData)));
	table1.SetVariable("BinData", blobVar);

	table1Bin.reserve(2048);
	{
		OutputMemoryStream outputStream(table1Bin, true);
		EXPECT_TRUE(outputStream << table1);
	}

	auto expectedSize = SerializedSizeOf(table1);

	EXPECT_EQ(expectedSize, table1Bin.size());

	// Serialization validation
	VariableTable tableDeserialized;
	{
		InputMemoryStream inStream(table1Bin);
        EXPECT_TRUE(inStream >> tableDeserialized);
	}

	EXPECT_EQ(table1.GetValue<int32_t>("sex"), tableDeserialized.GetValue<int32_t>("sex"));
	EXPECT_EQ(table1.GetValue<int32_t>("hat"), tableDeserialized.GetValue<int32_t>("hat"));
	EXPECT_EQ(table1.GetValue<int32_t>("shoes"), tableDeserialized.GetValue<int32_t>("shoes"));
	EXPECT_EQ(table1.GetValue<String>("Name"), tableDeserialized.GetValue<String>("Name"));
    EXPECT_EQ(testGuidRes, tableDeserialized.GetValue<Guid>("UID"));
    EXPECT_EQ(entityUidRes, tableDeserialized.GetValue<uint32_t>("EntityUID"));
    EXPECT_EQ(testAccountIdRes, tableDeserialized.GetValue<AccountID>("AccountID"));

    EXPECT_EQ(table1.GetValueBLOB("BinData"), tableDeserialized.GetValueBLOB("BinData"));
}

