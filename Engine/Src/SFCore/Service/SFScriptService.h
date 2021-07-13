////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2018 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : StormForge script service
//
////////////////////////////////////////////////////////////////////////////////


#pragma once 

#include "SFTypedefs.h"
#include "SFResult.h"
#include "Util/SFStringCrc64.h"
#include "Util/SFStringCrc32.h"
#include "Variable/SFVariableBoxing.h"
#include "Util/SFPathString.h"
#include "Util/SFString.h"
#include "MemoryManager/SFMemoryManager.h"

namespace SF
{
	class ScriptEnvironment;

	//////////////////////////////////////////////////////////////////////////////////////////
	//
	//	class Script object
	//   - Base class for script object
	//

	class ScriptObject
	{
	public:

		constexpr static StringCrc64 Type_Variable = "VARIABLE";
		constexpr static StringCrc64 Type_Function = "FUNCTION";

	private:
		// Object Type name
		//  - nullptr : not assigned
		//  - "VARIABLE" : ScriptVariable
		//  - "FUNCTION" : Function
		StringCrc64 m_ObjectTypeName;

		// Environment that holds this object
		ScriptEnvironment* m_pEnv = nullptr;

	public:
		ScriptObject(StringCrc64 objectTypeName, ScriptEnvironment* pEnv)
			: m_ObjectTypeName(objectTypeName)
			, m_pEnv(pEnv)
		{}
		virtual ~ScriptObject() {}

		// Get object type name
		StringCrc64 GetObjectTypeName() const { return m_ObjectTypeName; }

		// Get Environment
		ScriptEnvironment* GetEnvironment() const { return m_pEnv; }
	};



	//////////////////////////////////////////////////////////////////////////////////////////
	//
	//	class ScriptVariable interface
	//   - Holds value and encapsulate the interface
	//

	class ScriptVariable : public ScriptObject
	{
	private:
	public:
		ScriptVariable(ScriptEnvironment* pEnv)
			: ScriptObject(Type_Variable, pEnv)
		{}
		virtual ~ScriptVariable() {}

		// Get variable
		virtual Variable* GetVariable() = 0;

		// Set variable
		virtual Result SetVariable(const Variable& varBox) = 0;



		// Get value by type
		template<class ValueType>
		ValueType GetValue()
		{
			auto pVariable = GetVariable();
			if (pVariable == nullptr)
				return ValueType{};

			return pVariable->GetValue<ValueType>();
		}


		// Set value by type interface
		template<class ValueType>
		Result SetValue(ValueType value)
		{
			auto pVariable = GetVariable();
			if (pVariable == nullptr)
			{
				VariableBox boxedValue = Boxing(value);
				return SetVariable(*boxedValue.GetVariable());
			}
			else
			{
				return pVariable->SetValue(value);
			}
		}
	};


	class ScriptContext
	{
	private:
		ScriptEnvironment& m_Env;

	public:

		ScriptContext(ScriptEnvironment& env)
			: m_Env(env)
		{}

		virtual ~ScriptContext() {}

		// 
		ScriptEnvironment& GetEnvironment() { return m_Env; }
	};



	//////////////////////////////////////////////////////////////////////////////////////////
	//
	//	class ScriptVariable interface
	//   - Holds value and encapsulate the interface
	//

	class ScriptFunction : public ScriptObject
	{
	public:

		struct ParameterInfo
		{
			StringCrc64 Name = nullptr;
			StringCrc64 TypeName = nullptr;

			ParameterInfo(void* pInitValue = nullptr) {}
		};


	public:
		ScriptFunction(ScriptEnvironment* pEnv)
			: ScriptObject(ScriptObject::Type_Function, pEnv)
		{}
		virtual ~ScriptFunction() {}


		/////////////////////////////////////////////////////////////////////////////////////////////////
		//
		//	Support parameter arg style call
		//

			// Call with context
		virtual Result CallWithContext(ScriptContext& context) const { unused(context);  return ResultCode::NOT_IMPLEMENTED; }

		// Call with variable list
		virtual Result CallWithParam(const Array<VariableBox>& args) const { unused(args);  return ResultCode::NOT_IMPLEMENTED; }


		// 
		inline Result Call() const
		{
			return CallWithParam(ArrayView<VariableBox>(0, 0, nullptr));
		}

		// 
		template< class ...ArgTypes >
		inline Result Call(const ArgTypes&... args) const
		{
			StaticMemoryAllocatorT<2048> Allocator("TempStatic", GetSystemHeap());
			VariableBox arguments[sizeof...(args)] = { Boxing((IHeap&)Allocator, args)... };
			return CallWithParam(ArrayView<VariableBox>(sizeof...(args), sizeof...(args), arguments));
		}
	};


	//////////////////////////////////////////////////////////////////////////////////////////
	//
	//	class ScriptEnvironment interface
	//   - An environment is variable and 
	//

	class ScriptEnvironment
	{
	private:

		// TODO: switch to Heap Memory when it tested
		// Each environment has it's own heap
		Heap m_Heap;

		// parent script environment
		ScriptEnvironment* m_pParent = nullptr;

		// Environment name
		String m_Name;

	public:
		ScriptEnvironment(IHeap& heap, ScriptEnvironment* pParent, const String& name);
		virtual ~ScriptEnvironment();

		// Get Heap
		IHeap& GetHeap() { return *m_Heap.get(); }

		// Get parent script environment
		ScriptEnvironment* GetParent() { return m_pParent; }

		// Environment name
		const String& GetName() const { return m_Name; }

		// Get script object - Searches local first and extend search to the parent environment
		virtual ScriptObject* GetScriptObject(StringCrc64 objectType, StringCrc64 variableName, bool searchLocalOnly = false) { unused(objectType, variableName); return nullptr; }

		// Get variable - Takes full/partial path of the function
		//				- ex) /globalVarName, /myParent/VarName, myScope/Varname
		virtual ScriptObject* GetScriptObject(StringCrc64 objectType, const PathString& variablePath) { unused(objectType, variablePath); return nullptr; }


		// Get variable - Searchs local first and extend search to the parent environment
		virtual Variable* GetVariable(StringCrc64 variableName)
		{
			auto pObject = GetScriptObject(ScriptObject::Type_Variable, variableName);
			if (pObject == nullptr || pObject->GetObjectTypeName() != ScriptObject::Type_Variable)
				return nullptr;

			return static_cast<ScriptVariable*>(pObject)->GetVariable();
		}

		// Get variable - Takes full/partial path of the function
		//				- ex) /globalVarName, /myParent/VarName, myScope/Varname
		virtual Variable* GetVariable(const PathString& variablePath)
		{
			auto pObject = GetScriptObject(ScriptObject::Type_Variable, variablePath);
			if (pObject == nullptr || pObject->GetObjectTypeName() != ScriptObject::Type_Variable)
				return nullptr;

			return static_cast<ScriptVariable*>(pObject)->GetVariable();
		}

		// Call a function- Searches local first and extend search to the parent environment
		virtual ScriptFunction* GetFunction(StringCrc64 functionName)
		{
			auto pObject = GetScriptObject(ScriptObject::Type_Function, functionName);
			if (pObject == nullptr || pObject->GetObjectTypeName() != ScriptObject::Type_Function)
				return nullptr;

			return static_cast<ScriptFunction*>(pObject);
		}

		// Call a function - Takes full/partial path of the function
		//				- ex) /globalVarName, /myParent/VarName, myScope/Varname
		virtual ScriptFunction* GetFunction(const PathString& functionPath)
		{
			auto pObject = GetScriptObject(ScriptObject::Type_Function, functionPath);
			if (pObject == nullptr || pObject->GetObjectTypeName() != ScriptObject::Type_Function)
				return nullptr;

			return static_cast<ScriptFunction*>(pObject);
		}

		// Set variable - Takes full/partial path of the function
//				- ex) /globalVarName, /myParent/VarName, myScope/Varname
		virtual Result SetVariable(const PathString& variablePath, const Variable& variable) = 0;
		virtual Result SetVariable(StringCrc64 variableName, const Variable& variable) = 0;

		template<class ValueType>
		Result SetValue(const PathString& variablePath, const ValueType& value)
		{
			VariableBox boxed = Boxing(GetHeap(), value);
			return SetVariable(variablePath, *boxed.GetVariable());
		}

		template<class ValueType>
		Result SetValue(StringCrc64 variableName, const ValueType& value)
		{
			VariableBox boxed = Boxing(GetHeap(), value);
			return SetVariable(variableName, *boxed.GetVariable());
		}

		// Set function - Takes full/partial path of the function
		//				- ex) /globalVarName, /myParent/VarName, myScope/Varname
		virtual Result SetFunction(const PathString& functionPath, const Array<ScriptFunction::ParameterInfo>& parameterList, const Array<const uint8_t>& byteCode) = 0;
		virtual Result SetFunction(StringCrc64 functionPath, const Array<ScriptFunction::ParameterInfo>& parameterList, const Array<const uint8_t>& byteCode) = 0;

	};


	//////////////////////////////////////////////////////////////////////////////////////////
	//
	//	class ScriptEngineService
	//

	class ScriptEngineService
	{
	private:


	public:

		ScriptEngineService() {}
		virtual ~ScriptEngineService() {}

		// Create a script context
		//   @inParent: parent script environment, Child environment will inherit all variables from parent environment
		//   @return: Created environment
		virtual ScriptEnvironment* CreateEnvironment(ScriptEnvironment* inParent, const String& name) { unused(inParent, name);  return nullptr; }


	};

}; // namespace SF

