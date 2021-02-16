// Algorithm test.
//

#include "UnitTest1PCH.h"
#include <gtest/gtest.h>
#include "Multithread/SFSystemSynchronization.h"
#include "Multithread/SFThread.h"
#include "Container/SFDualSortedMap.h"
#include "Util/SFTimeUtil.h"
#include "Util/SFRandom.h"
#include "Variable/SFVariable.h"
#include "String/SFToString.h"
#include "UnitTest_TongScript.h"


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

TEST_F(TongScriptTest, Bytecode)
{
	auto pEnvironment = static_cast<Tong::ScriptEnvironment*>(GetScriptEngine()->CreateEnvironment(nullptr, "TestEnv"));
	ASSERT_NE(nullptr, pEnvironment);
	StaticArray<ScriptFunction::ParameterInfo, 5> parameterInfos(GetHeap());


	// two values in stack and one result in stack
	const uint8_t testDataNoOp[] = { 0, (uint8_t)Tong::SrciptBytecodeOpCode::NoOp, (uint8_t)Tong::SrciptBytecodeOpCode::Exit };
	EXPECT_TRUE(pEnvironment->SetFunction(StringCrc64("testDataNoOp"), parameterInfos, Array<uint8_t>(countof(testDataNoOp), testDataNoOp)));
	const VariableBox testInputNoOp[] = { Boxing(10), Boxing(11) };
	const VariableBox testResultNoOp[] = { Boxing(11), Boxing(10) };
	RunFunctionTest(pEnvironment, "testDataNoOp", Array<VariableBox>(countof(testInputNoOp), testInputNoOp), Array<VariableBox>(countof(testResultNoOp), testResultNoOp));

	const uint8_t testDataAdd[] = { 0, (uint8_t)Tong::SrciptBytecodeOpCode::Add, (uint8_t)Tong::SrciptBytecodeOpCode::Exit };
	EXPECT_TRUE(pEnvironment->SetFunction(StringCrc64("testDataAdd"), parameterInfos, Array<uint8_t>(countof(testDataAdd), testDataAdd)));
	const VariableBox testInputAdd[] = { Boxing(10), Boxing(11) };
	const VariableBox testResultAdd[] = { Boxing(21) };
	RunFunctionTest(pEnvironment, "testDataAdd", Array<VariableBox>(countof(testInputAdd), testInputAdd), Array<VariableBox>(countof(testResultAdd), testResultAdd));

	const uint8_t testDataSub[] = { 0, (uint8_t)Tong::SrciptBytecodeOpCode::Sub, (uint8_t)Tong::SrciptBytecodeOpCode::Exit };
	EXPECT_TRUE(pEnvironment->SetFunction(StringCrc64("testDataSub"), parameterInfos, Array<uint8_t>(countof(testDataSub), testDataSub)));
	const VariableBox testInputSub[] = { Boxing(10), Boxing(11) };
	const VariableBox testResultSub[] = { Boxing(-1) };
	RunFunctionTest(pEnvironment, "testDataSub", Array<VariableBox>(countof(testInputSub), testInputSub), Array<VariableBox>(countof(testResultSub), testResultSub));

	const uint8_t testDataMul[] = { 0, (uint8_t)Tong::SrciptBytecodeOpCode::Mul, (uint8_t)Tong::SrciptBytecodeOpCode::Exit };
	EXPECT_TRUE(pEnvironment->SetFunction(StringCrc64("testDataMul"), parameterInfos, Array<uint8_t>(countof(testDataMul), testDataMul)));
	const VariableBox testInputMul[] = { Boxing(10), Boxing(11) };
	const VariableBox testResultMul[] = { Boxing(110) };
	RunFunctionTest(pEnvironment, "testDataMul", Array<VariableBox>(countof(testInputMul), testInputMul), Array<VariableBox>(countof(testResultMul), testResultMul));

	const uint8_t testDataDiv[] = { 0, (uint8_t)Tong::SrciptBytecodeOpCode::Div, (uint8_t)Tong::SrciptBytecodeOpCode::Exit };
	EXPECT_TRUE(pEnvironment->SetFunction(StringCrc64("testDataDiv"), parameterInfos, Array<uint8_t>(countof(testDataDiv), testDataDiv)));
	const VariableBox testInputDiv[] = { Boxing(100), Boxing(10) };
	const VariableBox testResultDiv[] = { Boxing(10) };
	RunFunctionTest(pEnvironment, "testDataDiv", Array<VariableBox>(countof(testInputDiv), testInputDiv), Array<VariableBox>(countof(testResultDiv), testResultDiv));

	// one value in stack and one result in stack
	const uint8_t testDataAddI[] = { 0, (uint8_t)Tong::SrciptBytecodeOpCode::AddI, 3, 0, 0, 0, (uint8_t)Tong::SrciptBytecodeOpCode::Exit };
	EXPECT_TRUE(pEnvironment->SetFunction(StringCrc64("testDataAddI"), parameterInfos, Array<uint8_t>(countof(testDataAddI), testDataAddI)));
	const VariableBox testInputAddI[] = { Boxing(10) };
	const VariableBox testResultAddI[] = { Boxing(13) };
	RunFunctionTest(pEnvironment, "testDataAddI", Array<VariableBox>(countof(testInputAddI), testInputAddI), Array<VariableBox>(countof(testResultAddI), testResultAddI));

	const uint8_t testDataSubI[] = { 0, (uint8_t)Tong::SrciptBytecodeOpCode::SubI, 3, 0, 0, 0, (uint8_t)Tong::SrciptBytecodeOpCode::Exit };
	EXPECT_TRUE(pEnvironment->SetFunction(StringCrc64("testDataSubI"), parameterInfos, Array<uint8_t>(countof(testDataSubI), testDataSubI)));
	const VariableBox testInputSubI[] = { Boxing(10) };
	const VariableBox testResultSubI[] = { Boxing(7) };
	RunFunctionTest(pEnvironment, "testDataSubI", Array<VariableBox>(countof(testInputSubI), testInputSubI), Array<VariableBox>(countof(testResultSubI), testResultSubI));

	const uint8_t testDataMulI[] = { 0, (uint8_t)Tong::SrciptBytecodeOpCode::MulI, 3, 0, 0, 0, (uint8_t)Tong::SrciptBytecodeOpCode::Exit };
	EXPECT_TRUE(pEnvironment->SetFunction(StringCrc64("testDataMulI"), parameterInfos, Array<uint8_t>(countof(testDataMulI), testDataMulI)));
	const VariableBox testInputMulI[] = { Boxing(10) };
	const VariableBox testResultMulI[] = { Boxing(30) };
	RunFunctionTest(pEnvironment, "testDataMulI", Array<VariableBox>(countof(testInputMulI), testInputMulI), Array<VariableBox>(countof(testResultMulI), testResultMulI));

	const uint8_t testDataDivI[] = { 0, (uint8_t)Tong::SrciptBytecodeOpCode::DivI, 3, 0, 0, 0, (uint8_t)Tong::SrciptBytecodeOpCode::Exit };
	EXPECT_TRUE(pEnvironment->SetFunction(StringCrc64("testDataDivI"), parameterInfos, Array<uint8_t>(countof(testDataDivI), testDataDivI)));
	const VariableBox testInputDivI[] = { Boxing(30) };
	const VariableBox testResultDivI[] = { Boxing(10) };
	RunFunctionTest(pEnvironment, "testDataDivI", Array<VariableBox>(countof(testInputDivI), testInputDivI), Array<VariableBox>(countof(testResultDivI), testResultDivI));


	// one value in stack and one result in stack
	const float testFloat3 = 3.f;
	const uint8_t* testFloat3Bytes = reinterpret_cast<const uint8_t*>(&testFloat3);
	const uint8_t testDataAddF[] = { 0, (uint8_t)Tong::SrciptBytecodeOpCode::AddF, testFloat3Bytes[0], testFloat3Bytes[1], testFloat3Bytes[2], testFloat3Bytes[3], (uint8_t)Tong::SrciptBytecodeOpCode::Exit };
	EXPECT_TRUE(pEnvironment->SetFunction(StringCrc64("testDataAddF"), parameterInfos, Array<uint8_t>(countof(testDataAddF), testDataAddF)));
	const VariableBox testInputAddF[] = { Boxing(10.f) };
	const VariableBox testResultAddF[] = { Boxing(13.f) };
	RunFunctionTest(pEnvironment, "testDataAddF", Array<VariableBox>(countof(testInputAddF), testInputAddF), Array<VariableBox>(countof(testResultAddF), testResultAddF));

	const uint8_t testDataSubF[] = { 0, (uint8_t)Tong::SrciptBytecodeOpCode::SubF, testFloat3Bytes[0], testFloat3Bytes[1], testFloat3Bytes[2], testFloat3Bytes[3], (uint8_t)Tong::SrciptBytecodeOpCode::Exit };
	EXPECT_TRUE(pEnvironment->SetFunction(StringCrc64("testDataSubF"), parameterInfos, Array<uint8_t>(countof(testDataSubF), testDataSubF)));
	const VariableBox testInputSubF[] = { Boxing(10.f) };
	const VariableBox testResultSubF[] = { Boxing(7.f) };
	RunFunctionTest(pEnvironment, "testDataSubF", Array<VariableBox>(countof(testInputSubF), testInputSubF), Array<VariableBox>(countof(testResultSubF), testResultSubF));

	const uint8_t testDataMulF[] = { 0, (uint8_t)Tong::SrciptBytecodeOpCode::MulF, testFloat3Bytes[0], testFloat3Bytes[1], testFloat3Bytes[2], testFloat3Bytes[3], (uint8_t)Tong::SrciptBytecodeOpCode::Exit };
	EXPECT_TRUE(pEnvironment->SetFunction(StringCrc64("testDataMulF"), parameterInfos, Array<uint8_t>(countof(testDataMulF), testDataMulF)));
	const VariableBox testInputMulF[] = { Boxing(10.f) };
	const VariableBox testResultMulF[] = { Boxing(30.f) };
	RunFunctionTest(pEnvironment, "testDataMulF", Array<VariableBox>(countof(testInputMulF), testInputMulF), Array<VariableBox>(countof(testResultMulF), testResultMulF));

	const uint8_t testDataDivF[] = { 0, (uint8_t)Tong::SrciptBytecodeOpCode::DivF, testFloat3Bytes[0], testFloat3Bytes[1], testFloat3Bytes[2], testFloat3Bytes[3], (uint8_t)Tong::SrciptBytecodeOpCode::Exit };
	EXPECT_TRUE(pEnvironment->SetFunction(StringCrc64("testDataDivF"), parameterInfos, Array<uint8_t>(countof(testDataDivF), testDataDivF)));
	const VariableBox testInputDivF[] = { Boxing(30.f) };
	const VariableBox testResultDivF[] = { Boxing(10.f) };
	RunFunctionTest(pEnvironment, "testDataDivF", Array<VariableBox>(countof(testInputDivF), testInputDivF), Array<VariableBox>(countof(testResultDivF), testResultDivF));


	// one value in stack and one result in stack
	const uint8_t testDataCmpEqual[] = { 0, (uint8_t)Tong::SrciptBytecodeOpCode::CmpEqual, (uint8_t)Tong::SrciptBytecodeOpCode::Exit };
	EXPECT_TRUE(pEnvironment->SetFunction(StringCrc64("testDataCmpEqual"), parameterInfos, Array<uint8_t>(countof(testDataCmpEqual), testDataCmpEqual)));
	const VariableBox testInputCmpEqual[] = { Boxing(10), Boxing(11) };
	const VariableBox testResultCmpEqual[] = { Boxing(false) };
	RunFunctionTest(pEnvironment, "testDataCmpEqual", Array<VariableBox>(countof(testInputCmpEqual), testInputCmpEqual), Array<VariableBox>(countof(testResultCmpEqual), testResultCmpEqual));

	const uint8_t testDataCmpGreater[] = { 0, (uint8_t)Tong::SrciptBytecodeOpCode::CmpGreater, (uint8_t)Tong::SrciptBytecodeOpCode::Exit };
	EXPECT_TRUE(pEnvironment->SetFunction(StringCrc64("testDataCmpGreater"), parameterInfos, Array<uint8_t>(countof(testDataCmpGreater), testDataCmpGreater)));
	const VariableBox testInputCmpGreater[] = { Boxing(10), Boxing(11) };
	const VariableBox testResultCmpGreater[] = { Boxing(false) };
	RunFunctionTest(pEnvironment, "testDataCmpGreater", Array<VariableBox>(countof(testInputCmpGreater), testInputCmpGreater), Array<VariableBox>(countof(testResultCmpGreater), testResultCmpGreater));

	const uint8_t testDataCmpLess[] = { 0, (uint8_t)Tong::SrciptBytecodeOpCode::CmpLess, (uint8_t)Tong::SrciptBytecodeOpCode::Exit };
	EXPECT_TRUE(pEnvironment->SetFunction(StringCrc64("testDataCmpLess"), parameterInfos, Array<uint8_t>(countof(testDataCmpLess), testDataCmpLess)));
	const VariableBox testInputCmpLess[] = { Boxing(10), Boxing(11) };
	const VariableBox testResultCmpLess[] = { Boxing(true) };
	RunFunctionTest(pEnvironment, "testDataCmpLess", Array<VariableBox>(countof(testInputCmpLess), testInputCmpLess), Array<VariableBox>(countof(testResultCmpLess), testResultCmpLess));

	const uint8_t testDataCmpGreaterOrEqual[] = { 0, (uint8_t)Tong::SrciptBytecodeOpCode::CmpGreaterOrEqual, (uint8_t)Tong::SrciptBytecodeOpCode::Exit };
	EXPECT_TRUE(pEnvironment->SetFunction(StringCrc64("testDataCmpGreaterOrEqual"), parameterInfos, Array<uint8_t>(countof(testDataCmpGreaterOrEqual), testDataCmpGreaterOrEqual)));
	const VariableBox testInputCmpGreaterOrEqual[] = { Boxing(10), Boxing(11) };
	const VariableBox testResultCmpGreaterOrEqual[] = { Boxing(false) };
	RunFunctionTest(pEnvironment, "testDataCmpGreaterOrEqual", Array<VariableBox>(countof(testInputCmpGreaterOrEqual), testInputCmpGreaterOrEqual), Array<VariableBox>(countof(testResultCmpGreaterOrEqual), testResultCmpGreaterOrEqual));


	const uint8_t testDataCmpLessOrEqual[] = { 0, (uint8_t)Tong::SrciptBytecodeOpCode::CmpLessOrEqual, (uint8_t)Tong::SrciptBytecodeOpCode::Exit };
	EXPECT_TRUE(pEnvironment->SetFunction(StringCrc64("testDataCmpLessOrEqual"), parameterInfos, Array<uint8_t>(countof(testDataCmpLessOrEqual), testDataCmpLessOrEqual)));
	const VariableBox testInputCmpLessOrEqual[] = { Boxing(10), Boxing(11) };
	const VariableBox testResultCmpLessOrEqual[] = { Boxing(true) };
	RunFunctionTest(pEnvironment, "testDataCmpLessOrEqual", Array<VariableBox>(countof(testInputCmpLessOrEqual), testInputCmpLessOrEqual), Array<VariableBox>(countof(testResultCmpLessOrEqual), testResultCmpLessOrEqual));


	const uint8_t testDataStoreToContext[] = { 0, 
		(uint8_t)Tong::SrciptBytecodeOpCode::StoreToContext, 5, 'T', 'e', 's', 't', '\0',
		(uint8_t)Tong::SrciptBytecodeOpCode::Exit };
	EXPECT_TRUE(pEnvironment->SetFunction(StringCrc64("testDataStoreToContext"), parameterInfos, Array<uint8_t>(countof(testDataStoreToContext), testDataStoreToContext)));
	const VariableBox testInputStoreToContext[] = { Boxing(true), Boxing(10) };
	const VariableBox testResultStoreToContext[] = { Boxing(10), Boxing(true) };
	RunFunctionTest(pEnvironment, "testDataStoreToContext", 
		Array<VariableBox>(countof(testInputStoreToContext), testInputStoreToContext), 
		Array<VariableBox>(countof(testResultStoreToContext), testResultStoreToContext),
		[](Tong::ScriptContext& context)
		{
			auto pEnvVar = context.GetEnvironment().GetVariable(StringCrc64("Test"));
			EXPECT_EQ(nullptr, pEnvVar);
			auto pContextVar = context.GetVariable("Test");
			EXPECT_NE(nullptr, pContextVar);
			EXPECT_EQ(pContextVar->GetValueUInt32(), 10);
		}
	);

	const uint8_t testDataStore[] = { 0, 
		(uint8_t)Tong::SrciptBytecodeOpCode::Store, 5, 'T', 'e', 's', 't', '\0',
		(uint8_t)Tong::SrciptBytecodeOpCode::Exit };
	EXPECT_TRUE(pEnvironment->SetFunction(StringCrc64("testDataStore"), parameterInfos, Array<uint8_t>(countof(testDataStore), testDataStore)));
	const VariableBox testInputStore[] = { Boxing(true), Boxing(11.f) };
	const VariableBox testResultStore[] = { Boxing(11.f), Boxing(true) };
	RunFunctionTest(pEnvironment, "testDataStore", 
		Array<VariableBox>(countof(testInputStore), testInputStore), 
		Array<VariableBox>(countof(testResultStore), testResultStore),
		[](Tong::ScriptContext& context)
		{
			auto pEnvVar = context.GetEnvironment().GetVariable(StringCrc64("Test"));
			EXPECT_NE(nullptr, pEnvVar);
			EXPECT_EQ(11.f, pEnvVar->GetValueFloat());
		}
	);

	const uint8_t testDataLoad[] = { 0, 
		(uint8_t)Tong::SrciptBytecodeOpCode::Load, 6, 'C', 'o', 'u', 'n', 't', '\0',// size 8 
		(uint8_t)Tong::SrciptBytecodeOpCode::Exit };
	pEnvironment->SetValue(StringCrc64("Count"), 6);
	EXPECT_TRUE(pEnvironment->SetFunction(StringCrc64("testDataLoad"), parameterInfos, Array<uint8_t>(countof(testDataLoad), testDataLoad)));
	const VariableBox testInputLoad[] = { Boxing(10), Boxing(11) };
	const VariableBox testResultLoad[] = { Boxing(6), Boxing(11), Boxing(10) };
	RunFunctionTest(pEnvironment, "testDataLoad", Array<VariableBox>(countof(testInputLoad), testInputLoad), Array<VariableBox>(countof(testResultLoad), testResultLoad));


	const uint8_t testDataJump[] =
	{ 
		0, 
		(uint8_t)Tong::SrciptBytecodeOpCode::Jump, 8, 0, 0, 0,
		(uint8_t)Tong::SrciptBytecodeOpCode::Add,
		(uint8_t)Tong::SrciptBytecodeOpCode::Sub,
		(uint8_t)Tong::SrciptBytecodeOpCode::Exit
	};
	EXPECT_TRUE(pEnvironment->SetFunction(StringCrc64("testDataJump"), parameterInfos, Array<uint8_t>(countof(testDataJump), testDataJump)));
	const VariableBox testInputJump[] = { Boxing(10), Boxing(11) };
	const VariableBox testResultJump[] = { Boxing(11), Boxing(10) };
	RunFunctionTest(pEnvironment, "testDataJump", Array<VariableBox>(countof(testInputJump), testInputJump), Array<VariableBox>(countof(testResultJump), testResultJump));


	const uint8_t testDataJumpFalse[] = 
	{
		0,
		(uint8_t)Tong::SrciptBytecodeOpCode::CmpEqual,
		(uint8_t)Tong::SrciptBytecodeOpCode::JumpFalse, 8, 0, 0, 0,
		(uint8_t)Tong::SrciptBytecodeOpCode::Add,
		(uint8_t)Tong::SrciptBytecodeOpCode::Sub,
		(uint8_t)Tong::SrciptBytecodeOpCode::Exit
	};
	EXPECT_TRUE(pEnvironment->SetFunction(StringCrc64("testDataJumpFalse"), parameterInfos, Array<uint8_t>(countof(testDataJumpFalse), testDataJumpFalse)));
	const VariableBox testInputJumpFalse[] = { Boxing(10), Boxing(11), Boxing(10), Boxing(11) };
	const VariableBox testResultJumpFalse[] = { Boxing(-1) };
	RunFunctionTest(pEnvironment, "testDataJumpFalse", Array<VariableBox>(countof(testInputJumpFalse), testInputJumpFalse), Array<VariableBox>(countof(testResultJumpFalse), testResultJumpFalse));


	const uint8_t testDataLoop[] =
	{
		0,
		// store 100 to counter
		(uint8_t)Tong::SrciptBytecodeOpCode::LoadI, 100, 0, 0, 0,					// size 5
		(uint8_t)Tong::SrciptBytecodeOpCode::Store, 6, 'C', 'o', 'u', 'n', 't', '\0',// size 8

		// store 0 to sum
		(uint8_t)Tong::SrciptBytecodeOpCode::LoadI, 0, 0, 0, 0,						// size 5
		(uint8_t)Tong::SrciptBytecodeOpCode::MoveToContext, 4, 'S', 'u', 'm', '\0',			// size 5

		// start of loop

		// add count to sum
		(uint8_t)Tong::SrciptBytecodeOpCode::Load, 6, 'C', 'o', 'u', 'n', 't', '\0',// size 8
		(uint8_t)Tong::SrciptBytecodeOpCode::Load, 4, 'S', 'u', 'm', '\0',			// size 5
		(uint8_t)Tong::SrciptBytecodeOpCode::Add,									// size 5
		(uint8_t)Tong::SrciptBytecodeOpCode::MoveToContext, 4, 'S', 'u', 'm', '\0',			// size 5

		(uint8_t)Tong::SrciptBytecodeOpCode::Load, 6, 'C', 'o', 'u', 'n', 't', '\0',// size 8
		(uint8_t)Tong::SrciptBytecodeOpCode::SubI, 1, 0, 0, 0,						// size 5
		(uint8_t)Tong::SrciptBytecodeOpCode::Store, 6, 'C', 'o', 'u', 'n', 't', '\0',// size 8

		(uint8_t)Tong::SrciptBytecodeOpCode::LoadI, 0, 0, 0, 0,						// size 5
		(uint8_t)Tong::SrciptBytecodeOpCode::CmpLessOrEqual,						// size 1
		(uint8_t)Tong::SrciptBytecodeOpCode::JumpFalse, 24, 0, 0, 0,				// size 5
		(uint8_t)Tong::SrciptBytecodeOpCode::Add,
		(uint8_t)Tong::SrciptBytecodeOpCode::Exit
	};
	EXPECT_TRUE(pEnvironment->SetFunction(StringCrc64("testDataLoop"), parameterInfos, Array<uint8_t>(countof(testDataLoop), testDataLoop)));
	const VariableBox testInputLoop[] = { Boxing(10), Boxing(11) };
	const VariableBox testResultLoop[] = { Boxing(111), Boxing(10) };
	RunFunctionTest(pEnvironment, "testDataLoop", Array<VariableBox>(countof(testInputLoop), testInputLoop), Array<VariableBox>(countof(testResultLoop), testResultLoop));


	if (pEnvironment != nullptr)
		IHeap::Delete(pEnvironment);
	pEnvironment = nullptr;
}

