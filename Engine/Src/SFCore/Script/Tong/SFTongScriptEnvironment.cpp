////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2018 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : TongScript
//	
//
////////////////////////////////////////////////////////////////////////////////


#include "SFCorePCH.h"
#include "SFTypedefs.h"
#include "SFAssert.h"
#include "Util/SFStrUtil.h"
#include "Service/SFScriptService.h"
#include "Script/Tong/SFTongScriptEnvironment.h"
#include "Script/Tong/SFTongScriptVariable.h"
#include "Script/Tong/SFTongScriptFunction.h"
#include "Util/SFPath.h"



namespace SF
{
	namespace Tong
	{
		/////////////////////////////////////////////////////////////////////////////////
		//
		//	Tong script Environment
		//

		ScriptEnvironment::ScriptEnvironment(IHeap& heap, ScriptEnvironment* pParent, const String& name)
			: SF::ScriptEnvironment(heap, pParent, name)
			, m_Path(GetHeap())
			, m_VairableTable(GetHeap())
			, m_FunctionTable(GetHeap())
		{
			if (pParent != nullptr)
			{
				m_Path = pParent->GetPath();
				m_Path.Combine(GetName());
			}
			else
				m_Path = GetName();
		}

		ScriptEnvironment::~ScriptEnvironment()
		{
			for (auto itVar : m_VairableTable)
			{
				IHeap::Delete(itVar.GetValue());
			}
			m_VairableTable.Clear();

			for (auto itFunc : m_FunctionTable)
			{
				IHeap::Delete(itFunc.GetValue());
			}
			m_FunctionTable.Clear();
		}

		// Find environment holding the object
		ScriptEnvironment* ScriptEnvironment::FindParentEnvironment(const PathString& objectPath)
		{
			if (objectPath.size() <= 1)
			{
				return nullptr;
			}

			int checkStartIndex = (int)objectPath.size() - 2;
			SF::ScriptEnvironment* pCurEnv = this;
			for (; pCurEnv != nullptr; pCurEnv = pCurEnv->GetParent())
			{
				auto pCheckEnv = pCurEnv;
				int checkIndex = checkStartIndex;
				for (; checkIndex >= 0; checkIndex--, pCheckEnv = pCheckEnv->GetParent())
				{
					auto& checkPath = objectPath[checkIndex];
					if (pCheckEnv->GetName() != checkPath)
						break;
				}

				if (checkIndex < 0) // we found
					break;
			}

			return static_cast<ScriptEnvironment*>(pCurEnv);
		}


		// Get script object - Searches local first and extend search to the parent environment
		ScriptObject* ScriptEnvironment::GetScriptObject(StringCrc64 objectType, StringCrc64 variableName, bool searchLocalOnly)
		{
			if (objectType == nullptr || objectType == ScriptObject::Type_Variable)
			{
				auto itFound = m_VairableTable.find(variableName);
				if (itFound != nullptr)
					return itFound;
			}

			if (objectType == nullptr || objectType == ScriptObject::Type_Function)
			{
				auto itFound = m_FunctionTable.find(variableName);
				if (itFound != nullptr)
					return itFound;
			}

			// Not in local environment space. search parent
			if (!searchLocalOnly && GetParent() != nullptr)
				return GetParent()->GetScriptObject(objectType, variableName);

			return nullptr;
		}

		// Get variable - Takes full/partial path of the function
		//				- ex) /globalVarName, /myParent/VarName, myScope/Varname
		ScriptObject* ScriptEnvironment::GetScriptObject(StringCrc64 objectType, const PathString& variablePath)
		{
			if (variablePath.size() <= 1)
			{
				return GetScriptObject(objectType, StringCrc64(variablePath[0]));
			}

			auto pParentEnv = FindParentEnvironment(variablePath);
			if (pParentEnv == nullptr)
				return nullptr;

			return pParentEnv->GetScriptObject(objectType, StringCrc64(variablePath[(int)variablePath.size() - 1]), true);
		}


		// Get variable - Takes full/partial path of the function
		//				- ex) /globalVarName, /myParent/VarName, myScope/Varname
		Result ScriptEnvironment::SetVariable(const PathString& variablePath, const Variable& variable)
		{
			if (variablePath.size() == 0)
				return ResultCode::INVALID_ARG;
			else if (variablePath.size() == 1)
				return SetVariable(StringCrc64(variablePath[(int)variablePath.size() - 1]), variable);

			auto pEnv = FindParentEnvironment(variablePath);
			if (pEnv == nullptr)
			{
				return ResultCode::NOT_EXIST;
			}

			return SetVariable(StringCrc64(variablePath[(int)variablePath.size() - 1]), variable);
		}

		Result ScriptEnvironment::SetVariable(StringCrc64 variableName, const Variable& variable)
		{
			auto pScriptVar = m_VairableTable.find(variableName);
			if (pScriptVar == nullptr)
			{
				pScriptVar = new(GetHeap()) ScriptVariable(GetHeap(), this, variable);
				return m_VairableTable.Set(variableName, pScriptVar);
			}
			else
			{
				return pScriptVar->SetVariable(variable);
			}
		}


		// Set function - Takes full/partial path of the function
		//				- ex) /globalVarName, /myParent/VarName, myScope/Varname
		Result ScriptEnvironment::SetFunction(const PathString& functionPath, const Array<SF::ScriptFunction::ParameterInfo>& parameterList, const Array<const uint8_t>& byteCode)
		{
			auto pEnv = FindParentEnvironment(functionPath);
			if (pEnv == nullptr)
				return ResultCode::NOT_EXIST;

			return pEnv->SetFunction(functionPath[(int)functionPath.size() - 1], parameterList, byteCode);
		}

		Result ScriptEnvironment::SetFunction(StringCrc64 functionName, const Array<SF::ScriptFunction::ParameterInfo>& parameterList, const Array<const uint8_t>& byteCode)
		{
			ScriptFunction* pObj = nullptr;
			pObj = m_FunctionTable.find(functionName);
			if (pObj != nullptr)
			{
				return pObj->SetBytecode(byteCode);
			}

			auto pFunction = new(GetHeap()) ScriptFunction(GetHeap(), this, parameterList, byteCode);
			if (pFunction == nullptr)
				return ResultCode::OUT_OF_MEMORY;

			return m_FunctionTable.Insert(functionName, static_cast<Tong::ScriptFunction*>(pFunction));
		}

	}

} // namespace SF


