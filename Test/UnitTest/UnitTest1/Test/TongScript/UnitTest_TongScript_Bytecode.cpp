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
#include "Util/SFToString.h"
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
	auto res = pEnvironment->SetFunction("testDataNoOp"_crc64, parameterInfos, ArrayView<const uint8_t>(countof(testDataNoOp), testDataNoOp));
	EXPECT_TRUE(res);
	const VariableBox testInputNoOp[] = { Boxing(GetHeap(), 10), Boxing(GetHeap(), 11) };
	const VariableBox testResultNoOp[] = { Boxing(GetHeap(), 11), Boxing(GetHeap(), 10) };
	RunFunctionTest(pEnvironment, "testDataNoOp", ArrayView<const VariableBox>(countof(testInputNoOp), testInputNoOp), ArrayView<const VariableBox>(countof(testResultNoOp), testResultNoOp));

	const uint8_t testDataAdd[] = { 0, (uint8_t)Tong::SrciptBytecodeOpCode::Add, (uint8_t)Tong::SrciptBytecodeOpCode::Exit };
	EXPECT_TRUE(pEnvironment->SetFunction("testDataAdd"_crc64, parameterInfos, ArrayView<const uint8_t>(countof(testDataAdd), testDataAdd)));
	const VariableBox testInputAdd[] = { Boxing(GetHeap(), 10), Boxing(GetHeap(), 11) };
	const VariableBox testResultAdd[] = { Boxing(GetHeap(), 21) };
	RunFunctionTest(pEnvironment, "testDataAdd", ArrayView<const VariableBox>(countof(testInputAdd), testInputAdd), ArrayView<const VariableBox>(countof(testResultAdd), testResultAdd));

	const uint8_t testDataSub[] = { 0, (uint8_t)Tong::SrciptBytecodeOpCode::Sub, (uint8_t)Tong::SrciptBytecodeOpCode::Exit };
	EXPECT_TRUE(pEnvironment->SetFunction("testDataSub"_crc64, parameterInfos, ArrayView<const uint8_t>(countof(testDataSub), testDataSub)));
	const VariableBox testInputSub[] = { Boxing(GetHeap(), 10), Boxing(GetHeap(), 11) };
	const VariableBox testResultSub[] = { Boxing(GetHeap(), -1) };
	RunFunctionTest(pEnvironment, "testDataSub", ArrayView<const VariableBox>(countof(testInputSub), testInputSub), ArrayView<const VariableBox>(countof(testResultSub), testResultSub));

	const uint8_t testDataMul[] = { 0, (uint8_t)Tong::SrciptBytecodeOpCode::Mul, (uint8_t)Tong::SrciptBytecodeOpCode::Exit };
	EXPECT_TRUE(pEnvironment->SetFunction(StringCrc64("testDataMul"), parameterInfos, ArrayView<const uint8_t>(countof(testDataMul), testDataMul)));
	const VariableBox testInputMul[] = { Boxing(GetHeap(), 10), Boxing(GetHeap(), 11) };
	const VariableBox testResultMul[] = { Boxing(GetHeap(), 110) };
	RunFunctionTest(pEnvironment, "testDataMul", ArrayView<const VariableBox>(countof(testInputMul), testInputMul), ArrayView<const VariableBox>(countof(testResultMul), testResultMul));

	const uint8_t testDataDiv[] = { 0, (uint8_t)Tong::SrciptBytecodeOpCode::Div, (uint8_t)Tong::SrciptBytecodeOpCode::Exit };
	EXPECT_TRUE(pEnvironment->SetFunction(StringCrc64("testDataDiv"), parameterInfos, ArrayView<const uint8_t>(countof(testDataDiv), testDataDiv)));
	const VariableBox testInputDiv[] = { Boxing(GetHeap(), 100), Boxing(GetHeap(), 10) };
	const VariableBox testResultDiv[] = { Boxing(GetHeap(), 10) };
	RunFunctionTest(pEnvironment, "testDataDiv", ArrayView<const VariableBox>(countof(testInputDiv), testInputDiv), ArrayView<const VariableBox>(countof(testResultDiv), testResultDiv));

	// one value in stack and one result in stack
	const uint8_t testDataAddI[] = { 0, (uint8_t)Tong::SrciptBytecodeOpCode::AddI, 3, 0, 0, 0, (uint8_t)Tong::SrciptBytecodeOpCode::Exit };
	EXPECT_TRUE(pEnvironment->SetFunction(StringCrc64("testDataAddI"), parameterInfos, ArrayView<const uint8_t>(countof(testDataAddI), testDataAddI)));
	const VariableBox testInputAddI[] = { Boxing(GetHeap(), 10) };
	const VariableBox testResultAddI[] = { Boxing(GetHeap(), 13) };
	RunFunctionTest(pEnvironment, "testDataAddI", ArrayView<const VariableBox>(countof(testInputAddI), testInputAddI), ArrayView<const VariableBox>(countof(testResultAddI), testResultAddI));

	const uint8_t testDataSubI[] = { 0, (uint8_t)Tong::SrciptBytecodeOpCode::SubI, 3, 0, 0, 0, (uint8_t)Tong::SrciptBytecodeOpCode::Exit };
	EXPECT_TRUE(pEnvironment->SetFunction(StringCrc64("testDataSubI"), parameterInfos, ArrayView<const uint8_t>(countof(testDataSubI), testDataSubI)));
	const VariableBox testInputSubI[] = { Boxing(GetHeap(), 10) };
	const VariableBox testResultSubI[] = { Boxing(GetHeap(), 7) };
	RunFunctionTest(pEnvironment, "testDataSubI", ArrayView<const VariableBox>(countof(testInputSubI), testInputSubI), ArrayView<const VariableBox>(countof(testResultSubI), testResultSubI));

	const uint8_t testDataMulI[] = { 0, (uint8_t)Tong::SrciptBytecodeOpCode::MulI, 3, 0, 0, 0, (uint8_t)Tong::SrciptBytecodeOpCode::Exit };
	EXPECT_TRUE(pEnvironment->SetFunction(StringCrc64("testDataMulI"), parameterInfos, ArrayView<const uint8_t>(countof(testDataMulI), testDataMulI)));
	const VariableBox testInputMulI[] = { Boxing(GetHeap(), 10) };
	const VariableBox testResultMulI[] = { Boxing(GetHeap(), 30) };
	RunFunctionTest(pEnvironment, "testDataMulI", ArrayView<const VariableBox>(countof(testInputMulI), testInputMulI), ArrayView<const VariableBox>(countof(testResultMulI), testResultMulI));

	const uint8_t testDataDivI[] = { 0, (uint8_t)Tong::SrciptBytecodeOpCode::DivI, 3, 0, 0, 0, (uint8_t)Tong::SrciptBytecodeOpCode::Exit };
	EXPECT_TRUE(pEnvironment->SetFunction(StringCrc64("testDataDivI"), parameterInfos, ArrayView<const uint8_t>(countof(testDataDivI), testDataDivI)));
	const VariableBox testInputDivI[] = { Boxing(GetHeap(), 30) };
	const VariableBox testResultDivI[] = { Boxing(GetHeap(), 10) };
	RunFunctionTest(pEnvironment, "testDataDivI", ArrayView<const VariableBox>(countof(testInputDivI), testInputDivI), ArrayView<const VariableBox>(countof(testResultDivI), testResultDivI));


	// one value in stack and one result in stack
	const float testFloat3 = 3.f;
	const uint8_t* testFloat3Bytes = reinterpret_cast<const uint8_t*>(&testFloat3);
	const uint8_t testDataAddF[] = { 0, (uint8_t)Tong::SrciptBytecodeOpCode::AddF, testFloat3Bytes[0], testFloat3Bytes[1], testFloat3Bytes[2], testFloat3Bytes[3], (uint8_t)Tong::SrciptBytecodeOpCode::Exit };
	EXPECT_TRUE(pEnvironment->SetFunction(StringCrc64("testDataAddF"), parameterInfos, ArrayView<const uint8_t>(countof(testDataAddF), testDataAddF)));
	const VariableBox testInputAddF[] = { Boxing(GetHeap(), 10.f) };
	const VariableBox testResultAddF[] = { Boxing(GetHeap(), 13.f) };
	RunFunctionTest(pEnvironment, "testDataAddF", ArrayView<const VariableBox>(countof(testInputAddF), testInputAddF), ArrayView<const VariableBox>(countof(testResultAddF), testResultAddF));

	const uint8_t testDataSubF[] = { 0, (uint8_t)Tong::SrciptBytecodeOpCode::SubF, testFloat3Bytes[0], testFloat3Bytes[1], testFloat3Bytes[2], testFloat3Bytes[3], (uint8_t)Tong::SrciptBytecodeOpCode::Exit };
	EXPECT_TRUE(pEnvironment->SetFunction(StringCrc64("testDataSubF"), parameterInfos, ArrayView<const uint8_t>(countof(testDataSubF), testDataSubF)));
	const VariableBox testInputSubF[] = { Boxing(GetHeap(), 10.f) };
	const VariableBox testResultSubF[] = { Boxing(GetHeap(), 7.f) };
	RunFunctionTest(pEnvironment, "testDataSubF", ArrayView<const VariableBox>(countof(testInputSubF), testInputSubF), ArrayView<const VariableBox>(countof(testResultSubF), testResultSubF));

	const uint8_t testDataMulF[] = { 0, (uint8_t)Tong::SrciptBytecodeOpCode::MulF, testFloat3Bytes[0], testFloat3Bytes[1], testFloat3Bytes[2], testFloat3Bytes[3], (uint8_t)Tong::SrciptBytecodeOpCode::Exit };
	EXPECT_TRUE(pEnvironment->SetFunction(StringCrc64("testDataMulF"), parameterInfos, ArrayView<const uint8_t>(countof(testDataMulF), testDataMulF)));
	const VariableBox testInputMulF[] = { Boxing(GetHeap(), 10.f) };
	const VariableBox testResultMulF[] = { Boxing(GetHeap(), 30.f) };
	RunFunctionTest(pEnvironment, "testDataMulF", ArrayView<const VariableBox>(countof(testInputMulF), testInputMulF), ArrayView<const VariableBox>(countof(testResultMulF), testResultMulF));

	const uint8_t testDataDivF[] = { 0, (uint8_t)Tong::SrciptBytecodeOpCode::DivF, testFloat3Bytes[0], testFloat3Bytes[1], testFloat3Bytes[2], testFloat3Bytes[3], (uint8_t)Tong::SrciptBytecodeOpCode::Exit };
	EXPECT_TRUE(pEnvironment->SetFunction(StringCrc64("testDataDivF"), parameterInfos, ArrayView<const uint8_t>(countof(testDataDivF), testDataDivF)));
	const VariableBox testInputDivF[] = { Boxing(GetHeap(), 30.f) };
	const VariableBox testResultDivF[] = { Boxing(GetHeap(), 10.f) };
	RunFunctionTest(pEnvironment, "testDataDivF", ArrayView<const VariableBox>(countof(testInputDivF), testInputDivF), ArrayView<const VariableBox>(countof(testResultDivF), testResultDivF));


	// one value in stack and one result in stack
	const uint8_t testDataCmpEqual[] = { 0, (uint8_t)Tong::SrciptBytecodeOpCode::CmpEqual, (uint8_t)Tong::SrciptBytecodeOpCode::Exit };
	EXPECT_TRUE(pEnvironment->SetFunction(StringCrc64("testDataCmpEqual"), parameterInfos, ArrayView<const uint8_t>(countof(testDataCmpEqual), testDataCmpEqual)));
	const VariableBox testInputCmpEqual[] = { Boxing(GetHeap(), 10), Boxing(GetHeap(), 11) };
	const VariableBox testResultCmpEqual[] = { Boxing(GetHeap(), false) };
	RunFunctionTest(pEnvironment, "testDataCmpEqual", ArrayView<const VariableBox>(countof(testInputCmpEqual), testInputCmpEqual), ArrayView<const VariableBox>(countof(testResultCmpEqual), testResultCmpEqual));

	const uint8_t testDataCmpGreater[] = { 0, (uint8_t)Tong::SrciptBytecodeOpCode::CmpGreater, (uint8_t)Tong::SrciptBytecodeOpCode::Exit };
	EXPECT_TRUE(pEnvironment->SetFunction(StringCrc64("testDataCmpGreater"), parameterInfos, ArrayView<const uint8_t>(countof(testDataCmpGreater), testDataCmpGreater)));
	const VariableBox testInputCmpGreater[] = { Boxing(GetHeap(), 10), Boxing(GetHeap(), 11) };
	const VariableBox testResultCmpGreater[] = { Boxing(GetHeap(), false) };
	RunFunctionTest(pEnvironment, "testDataCmpGreater", ArrayView<const VariableBox>(countof(testInputCmpGreater), testInputCmpGreater), ArrayView<const VariableBox>(countof(testResultCmpGreater), testResultCmpGreater));

	const uint8_t testDataCmpLess[] = { 0, (uint8_t)Tong::SrciptBytecodeOpCode::CmpLess, (uint8_t)Tong::SrciptBytecodeOpCode::Exit };
	EXPECT_TRUE(pEnvironment->SetFunction(StringCrc64("testDataCmpLess"), parameterInfos, ArrayView<const uint8_t>(countof(testDataCmpLess), testDataCmpLess)));
	const VariableBox testInputCmpLess[] = { Boxing(GetHeap(), 10), Boxing(GetHeap(), 11) };
	const VariableBox testResultCmpLess[] = { Boxing(GetHeap(), true) };
	RunFunctionTest(pEnvironment, "testDataCmpLess", ArrayView<const VariableBox>(countof(testInputCmpLess), testInputCmpLess), ArrayView<const VariableBox>(countof(testResultCmpLess), testResultCmpLess));

	const uint8_t testDataCmpGreaterOrEqual[] = { 0, (uint8_t)Tong::SrciptBytecodeOpCode::CmpGreaterOrEqual, (uint8_t)Tong::SrciptBytecodeOpCode::Exit };
	EXPECT_TRUE(pEnvironment->SetFunction(StringCrc64("testDataCmpGreaterOrEqual"), parameterInfos, ArrayView<const uint8_t>(countof(testDataCmpGreaterOrEqual), testDataCmpGreaterOrEqual)));
	const VariableBox testInputCmpGreaterOrEqual[] = { Boxing(GetHeap(), 10), Boxing(GetHeap(), 11) };
	const VariableBox testResultCmpGreaterOrEqual[] = { Boxing(GetHeap(), false) };
	RunFunctionTest(pEnvironment, "testDataCmpGreaterOrEqual", ArrayView<const VariableBox>(countof(testInputCmpGreaterOrEqual), testInputCmpGreaterOrEqual), ArrayView<const VariableBox>(countof(testResultCmpGreaterOrEqual), testResultCmpGreaterOrEqual));


	const uint8_t testDataCmpLessOrEqual[] = { 0, (uint8_t)Tong::SrciptBytecodeOpCode::CmpLessOrEqual, (uint8_t)Tong::SrciptBytecodeOpCode::Exit };
	EXPECT_TRUE(pEnvironment->SetFunction(StringCrc64("testDataCmpLessOrEqual"), parameterInfos, ArrayView<const uint8_t>(countof(testDataCmpLessOrEqual), testDataCmpLessOrEqual)));
	const VariableBox testInputCmpLessOrEqual[] = { Boxing(GetHeap(), 10), Boxing(GetHeap(), 11) };
	const VariableBox testResultCmpLessOrEqual[] = { Boxing(GetHeap(), true) };
	RunFunctionTest(pEnvironment, "testDataCmpLessOrEqual", ArrayView<const VariableBox>(countof(testInputCmpLessOrEqual), testInputCmpLessOrEqual), ArrayView<const VariableBox>(countof(testResultCmpLessOrEqual), testResultCmpLessOrEqual));


	const uint8_t testDataStoreToContext[] = { 0, 
		(uint8_t)Tong::SrciptBytecodeOpCode::StoreToContext, 5, 'T', 'e', 's', 't', '\0',
		(uint8_t)Tong::SrciptBytecodeOpCode::Exit };
	EXPECT_TRUE(pEnvironment->SetFunction(StringCrc64("testDataStoreToContext"), parameterInfos, ArrayView<const uint8_t>(countof(testDataStoreToContext), testDataStoreToContext)));
	const VariableBox testInputStoreToContext[] = { Boxing(GetHeap(), true), Boxing(GetHeap(), 10) };
	const VariableBox testResultStoreToContext[] = { Boxing(GetHeap(), 10), Boxing(GetHeap(), true) };
	RunFunctionTest(pEnvironment, "testDataStoreToContext", 
		ArrayView<const VariableBox>(countof(testInputStoreToContext), testInputStoreToContext), 
		ArrayView<const VariableBox>(countof(testResultStoreToContext), testResultStoreToContext),
		[](Tong::ScriptContext& context)
		{
			auto pEnvVar = context.GetEnvironment().GetVariable(StringCrc64("Test"));
			EXPECT_EQ(nullptr, pEnvVar);
			auto pContextVar = context.GetVariable("Test");
			EXPECT_NE(nullptr, pContextVar);
			EXPECT_EQ(pContextVar->GetValueUInt32(), uint32_t(10));
		}
	);

	const uint8_t testDataStore[] = { 0, 
		(uint8_t)Tong::SrciptBytecodeOpCode::Store, 5, 'T', 'e', 's', 't', '\0',
		(uint8_t)Tong::SrciptBytecodeOpCode::Exit };
	EXPECT_TRUE(pEnvironment->SetFunction(StringCrc64("testDataStore"), parameterInfos, ArrayView<const uint8_t>(countof(testDataStore), testDataStore)));
	const VariableBox testInputStore[] = { Boxing(GetHeap(), true), Boxing(GetHeap(), 11.f) };
	const VariableBox testResultStore[] = { Boxing(GetHeap(), 11.f), Boxing(GetHeap(), true) };
	RunFunctionTest(pEnvironment, "testDataStore", 
		ArrayView<const VariableBox>(countof(testInputStore), testInputStore), 
		ArrayView<const VariableBox>(countof(testResultStore), testResultStore),
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
	EXPECT_TRUE(pEnvironment->SetFunction(StringCrc64("testDataLoad"), parameterInfos, ArrayView<const uint8_t>(countof(testDataLoad), testDataLoad)));
	const VariableBox testInputLoad[] = { Boxing(GetHeap(), 10), Boxing(GetHeap(), 11) };
	const VariableBox testResultLoad[] = { Boxing(GetHeap(), 6), Boxing(GetHeap(), 11), Boxing(GetHeap(), 10) };
	RunFunctionTest(pEnvironment, "testDataLoad", ArrayView<const VariableBox>(countof(testInputLoad), testInputLoad), ArrayView<const VariableBox>(countof(testResultLoad), testResultLoad));


	const uint8_t testDataJump[] =
	{ 
		0, 
		(uint8_t)Tong::SrciptBytecodeOpCode::Jump, 8, 0, 0, 0,
		(uint8_t)Tong::SrciptBytecodeOpCode::Add,
		(uint8_t)Tong::SrciptBytecodeOpCode::Sub,
		(uint8_t)Tong::SrciptBytecodeOpCode::Exit
	};
	EXPECT_TRUE(pEnvironment->SetFunction(StringCrc64("testDataJump"), parameterInfos, ArrayView<const uint8_t>(countof(testDataJump), testDataJump)));
	const VariableBox testInputJump[] = { Boxing(GetHeap(), 10), Boxing(GetHeap(), 11) };
	const VariableBox testResultJump[] = { Boxing(GetHeap(), 11), Boxing(GetHeap(), 10) };
	RunFunctionTest(pEnvironment, "testDataJump", ArrayView<const VariableBox>(countof(testInputJump), testInputJump), ArrayView<const VariableBox>(countof(testResultJump), testResultJump));


	const uint8_t testDataJumpFalse[] = 
	{
		0,
		(uint8_t)Tong::SrciptBytecodeOpCode::CmpEqual,
		(uint8_t)Tong::SrciptBytecodeOpCode::JumpFalse, 8, 0, 0, 0,
		(uint8_t)Tong::SrciptBytecodeOpCode::Add,
		(uint8_t)Tong::SrciptBytecodeOpCode::Sub,
		(uint8_t)Tong::SrciptBytecodeOpCode::Exit
	};
	EXPECT_TRUE(pEnvironment->SetFunction(StringCrc64("testDataJumpFalse"), parameterInfos, ArrayView<const uint8_t>(countof(testDataJumpFalse), testDataJumpFalse)));
	const VariableBox testInputJumpFalse[] = { Boxing(GetHeap(), 10), Boxing(GetHeap(), 11), Boxing(GetHeap(), 10), Boxing(GetHeap(), 11) };
	const VariableBox testResultJumpFalse[] = { Boxing(GetHeap(), -1) };
	RunFunctionTest(pEnvironment, "testDataJumpFalse", ArrayView<const VariableBox>(countof(testInputJumpFalse), testInputJumpFalse), ArrayView<const VariableBox>(countof(testResultJumpFalse), testResultJumpFalse));


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
	EXPECT_TRUE(pEnvironment->SetFunction(StringCrc64("testDataLoop"), parameterInfos, ArrayView<const uint8_t>(countof(testDataLoop), testDataLoop)));
	const VariableBox testInputLoop[] = { Boxing(GetHeap(), 10), Boxing(GetHeap(), 11) };
	const VariableBox testResultLoop[] = { Boxing(GetHeap(), 111), Boxing(GetHeap(), 10) };
	RunFunctionTest(pEnvironment, "testDataLoop", ArrayView<const VariableBox>(countof(testInputLoop), testInputLoop), ArrayView<const VariableBox>(countof(testResultLoop), testResultLoop));


	if (pEnvironment != nullptr)
		IHeap::Delete(pEnvironment);
	pEnvironment = nullptr;
}

