////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2018 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Variable table
//	
//
////////////////////////////////////////////////////////////////////////////////


#include "CoreBasePCH.h"
#include "SFTypedefs.h"
#include "Util/SFLog.h"
#include "Variable/SFVariableStack.h"



namespace SF {




	/////////////////////////////////////////////////////////////////////////////////
	//
	//	variable stack container
	//

	VariableStack::VariableStack(IHeap& heap)
		: m_Heap(new(heap) StackHeap<2048>("VariableStack", heap))
		, m_Vairables(heap)
	{
	}

	VariableStack::~VariableStack()
	{
		// everything will be wiped
		while (m_Vairables.size() > 0)
		{
			auto pVar = m_Vairables.pop_back();
			delete[] pVar;
		}
	}

	// Push/Pop variable
	Result VariableStack::Push(const Variable& variable)
	{
		//auto varSize = variable.GetVariableSize();
		auto pVar = variable.Clone(**m_Heap);
		return m_Vairables.push_back(pVar);
	}

	Variable* VariableStack::GetFromFront(int offset)
	{
		if (offset < 0)
			return nullptr;

		if (m_Vairables.size() <= static_cast<size_t>(offset))
			return nullptr;

		return m_Vairables[m_Vairables.size() - (1 + offset)];
	}

	Result VariableStack::Pop(size_t count)
	{
		int iCount = (int)count;
		for (; static_cast<int>(m_Vairables.size()) >= iCount && iCount > 0; iCount--)
		{
			auto pVar = m_Vairables.pop_back();
			delete pVar;
		}

		if (iCount > 0)
			return ResultCode::NOT_EXIST;

		return ResultCode::SUCCESS;
	}



} // namespace SF

