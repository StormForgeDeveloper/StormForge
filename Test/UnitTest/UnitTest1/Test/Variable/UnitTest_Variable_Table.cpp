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
	VariableTable table(GetHeap());

	auto boxedInt = Boxing(GetHeap(), 10);
	table.SetVariable("testInt", *boxedInt.GetVariable());

	auto boxedFloat = Boxing(GetHeap(), 10.f);
	table.SetVariable("testFloat", *boxedFloat.GetVariable());

	auto boxedDouble = Boxing(GetHeap(), 10.);
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
	VariableTable table(GetHeap());

	auto boxedInt = Boxing(GetHeap(), 10);
	table.SetVariable("testInt", *boxedInt.GetVariable());
	table.SetVariable("testInt", *boxedInt.GetVariable());

	auto boxedFloat = Boxing(GetHeap(), 10.f);
	table.SetVariable("testFloat", *boxedFloat.GetVariable());
	table.SetVariable("testFloat", *boxedFloat.GetVariable());

	auto boxedDouble = Boxing(GetHeap(), 10.);
	table.SetVariable("testDouble", *boxedDouble.GetVariable());
	table.SetVariable("testDouble", *boxedDouble.GetVariable());

	EXPECT_EQ(boxedInt.GetVariable()->GetValue<int>(), table.GetValue<int>("testInt"));
	EXPECT_EQ(boxedFloat.GetVariable()->GetValue<float>(), table.GetValue<float>("testFloat"));
	EXPECT_EQ(boxedDouble.GetVariable()->GetValue<double>(), table.GetValue<double>("testDouble"));
}



TEST_F(VariableTest, Serialization)
{
	VariableTable table1(GetHeap());
	DynamicArray<uint8_t> table1Bin(GetHeap());
	table1.SetValue("sex", 1);
	table1.SetValue("hat", 10);
	table1.SetValue("shoes", 10);
	table1.SetValue("Name", "testName1234");

	uint8_t testData[] = {12,114,54,66,234, 235};
	SFUniquePtr<Variable> blobVar(new(GetEngineHeap()) VariableBLOB(ArrayView<uint8_t>(sizeof(testData), testData)));
	table1.SetVariable("BinData", blobVar);

	table1Bin.reserve(2048);
	{
		OutputMemoryStream outputStream(table1Bin, true);
		outputStream << table1;
	}

	auto expectedSize = SerializedSizeOf(table1);

	EXPECT_EQ(expectedSize, table1Bin.size());

	// Serialization validation
	VariableTable tableDeserialized;
	{
		InputMemoryStream inStream(table1Bin);
		inStream >> tableDeserialized;
	}

	EXPECT_EQ(table1.GetValue<int32_t>("sex"), tableDeserialized.GetValue<int32_t>("sex"));
	EXPECT_EQ(table1.GetValue<int32_t>("hat"), tableDeserialized.GetValue<int32_t>("hat"));
	EXPECT_EQ(table1.GetValue<int32_t>("shoes"), tableDeserialized.GetValue<int32_t>("shoes"));
	EXPECT_EQ(table1.GetValue<String>("Name"), tableDeserialized.GetValue<String>("Name"));
	EXPECT_EQ(table1.GetValueBLOB("BinData"), tableDeserialized.GetValueBLOB("BinData"));
}

