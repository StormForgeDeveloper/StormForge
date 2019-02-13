// Algorithm test.
//

#include "UnitTest1PCH.h"
#include <gtest/gtest.h>
#include "Thread/SFSystemSynchronization.h"
#include "Thread/SFThread.h"
#include "Memory/SFStackHeap.h"
#include "Util/SFTimeUtil.h"
#include "Util/SFRandom.h"
#include "String/SFToString.h"
#include "Container/SFArray.h"
#include "UnitTest_Variable.h"


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

	auto boxedInt = Boxing(10);
	table.SetVariable("testInt"_crc, *boxedInt.GetVariable());

	auto boxedFloat = Boxing(10.f);
	table.SetVariable("testFloat"_crc, *boxedFloat.GetVariable());

	auto boxedDouble = Boxing(10.);
	table.SetVariable("testDouble"_crc, *boxedDouble.GetVariable());

	EXPECT_EQ(boxedInt.GetVariable()->GetValue<int>(), table.GetValue<int>("testInt"));
	EXPECT_EQ(boxedFloat.GetVariable()->GetValue<float>(), table.GetValue<float>("testFloat"));
	EXPECT_EQ(boxedDouble.GetVariable()->GetValue<double>(), table.GetValue<double>("testDouble"));
}



TEST_F(VariableTest, Table2)
{
	VariableTable table(GetHeap());

	auto boxedInt = Boxing(10);
	table.SetVariable("testInt"_crc, *boxedInt.GetVariable());
	table.SetVariable("testInt"_crc, *boxedInt.GetVariable());

	auto boxedFloat = Boxing(10.f);
	table.SetVariable("testFloat"_crc, *boxedFloat.GetVariable());
	table.SetVariable("testFloat"_crc, *boxedFloat.GetVariable());

	auto boxedDouble = Boxing(10.);
	table.SetVariable("testDouble"_crc, *boxedDouble.GetVariable());
	table.SetVariable("testDouble"_crc, *boxedDouble.GetVariable());

	EXPECT_EQ(boxedInt.GetVariable()->GetValue<int>(), table.GetValue<int>("testInt"_crc));
	EXPECT_EQ(boxedFloat.GetVariable()->GetValue<float>(), table.GetValue<float>("testFloat"_crc));
	EXPECT_EQ(boxedDouble.GetVariable()->GetValue<double>(), table.GetValue<double>("testDouble"_crc));
}

