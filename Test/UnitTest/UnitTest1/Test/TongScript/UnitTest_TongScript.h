////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2018 StormForge
// 
// Author : KyungKun Ko
//
// Description : AVL tree test
//	
//
////////////////////////////////////////////////////////////////////////////////



#include <gtest/gtest.h>
#include "Thread/SFThread.h"
#include "Memory/SFMemoryManager.h"
#include "String/SFToString.h"
#include "Script/Tong/SFTongScriptBytecode.h"
#include "Script/Tong/SFTongScriptEngine.h"
#include "Script/Tong/SFTongScriptContext.h"
#include "Script/Tong/SFTongScriptEnvironment.h"
#include "Script/Tong/SFTongScriptFunction.h"
#include "Script/Tong/SFTongScriptVariable.h"
#include "../SFTestBase.h"


// common setting class
class TongScriptTest : public MyTestBase
{
protected:

	// Heap for test
	SF::Heap m_Heap;

	SF::Tong::ScriptEngine *m_pScriptEngine = nullptr;

	SF::SpinLock m_LockObject;


public:

	TongScriptTest()
		: m_Heap("TongScriptTest", SF::GetSystemHeap())
	{

	}

	// Heap interface
	SF::IHeap& GetHeap() { return m_Heap; }

	SF::Tong::ScriptEngine * GetScriptEngine() { return m_pScriptEngine; }



	// Remember that SetUp() is run immediately before a test starts.
	virtual void SetUp()
	{
		MyTestBase::SetUp();
		m_pScriptEngine = new(GetHeap()) SF::Tong::ScriptEngine(GetHeap());

	}

	// TearDown() is invoked immediately after a test finishes.  Here we
	virtual void TearDown()
	{
		if (m_pScriptEngine != nullptr)
			delete m_pScriptEngine;
		m_pScriptEngine = nullptr;
		MyTestBase::TearDown();

	}

	void RunFunctionTest(SF::Tong::ScriptEnvironment* pEnvironment, 
		SF::StringCrc64 functName, 
		const SF::Array<SF::VariableBox>& stackVariables, 
		const SF::Array<SF::VariableBox>& expectedStackResults,
		std::function<void(SF::Tong::ScriptContext& context)> extTest = [](SF::Tong::ScriptContext& context) {})
	{
		SF::Tong::ScriptContext context(*pEnvironment);
		for (auto itStackVar : stackVariables)
			context.GetVariableStack().Push(*itStackVar.GetVariable());
		auto pFunction = pEnvironment->GetFunction(functName);
		ASSERT_NE(nullptr, pFunction);

		ASSERT_EQ(SF::ResultCode::SUCCESS, pFunction->CallWithContext(context));

		EXPECT_EQ(expectedStackResults.size(), context.GetVariableStack().size());
		if (expectedStackResults.size() != context.GetVariableStack().size())
			return;

		for (auto itExpectedVar : expectedStackResults)
		{
			auto pVar = context.GetVariableStack().GetFromFront();
			ASSERT_NE(nullptr, pVar);

			//ASSERT_EQ(pVar->GetTypeName(), itExpectedVar.GetVariable()->GetTypeName());
			EXPECT_EQ(*pVar, *itExpectedVar.GetVariable());
			Assert(*pVar == *itExpectedVar.GetVariable());

			context.GetVariableStack().Pop();
		}

		extTest(context);
	}

};

