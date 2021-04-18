////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2018 Kyungkun Ko
// 
// Author : Kyungkun Ko
//
// Description : StormForge, Tong Script
//	
//
////////////////////////////////////////////////////////////////////////////////


#pragma once


#include "SFTypedefs.h"
#include "Service/SFScriptService.h"
#include "Component/SFLibraryComponent.h"
#include "Container/SFSortedArray.h"

namespace SF
{

	namespace Tong
	{
		class ScriptVariable;
		class ScriptFunction;

		/////////////////////////////////////////////////////////////////////////////////
		//
		//	Tong script Environment
		//

		class ScriptEnvironment : public SF::ScriptEnvironment
		{
		private:

			// environment path
			PathString m_Path;

			// variable object list
			SortedArray<StringCrc64, ScriptVariable*, true, false> m_VairableTable;

			// function object list
			SortedArray<StringCrc64, ScriptFunction*, true, false> m_FunctionTable;

		public:

			ScriptEnvironment(IHeap& heap, ScriptEnvironment* pParent, const String& name);
			~ScriptEnvironment();


			// Find environment holding the object
			ScriptEnvironment* FindParentEnvironment(const PathString& objectPath);

			// Path
			const PathString& GetPath() const { return m_Path; }

			// Get script object - Searches local first and extend search to the parent environment
			virtual ScriptObject* GetScriptObject(StringCrc64 objectType, StringCrc64 variableName, bool searchLocalOnly = false) override;

			// Get variable - Takes full/partial path of the function
			//				- ex) /globalVarName, /myParent/VarName, myScope/Varname
			virtual ScriptObject* GetScriptObject(StringCrc64 objectType, const PathString& variablePath) override;


			// Set variable - Takes full/partial path of the function
			//				- ex) /globalVarName, /myParent/VarName, myScope/Varname
			virtual Result SetVariable(const PathString& variablePath, const Variable& variable) override;
			virtual Result SetVariable(StringCrc64 variableName, const Variable& variable) override;


			// Set function - Takes full/partial path of the function
			//				- ex) /globalVarName, /myParent/VarName, myScope/Varname
			virtual Result SetFunction(const PathString& functionPath, const Array<SF::ScriptFunction::ParameterInfo>& parameterList, const Array<const uint8_t>& byteCode) override;
			virtual Result SetFunction(StringCrc64 functionPath, const Array<SF::ScriptFunction::ParameterInfo>& parameterList, const Array<const uint8_t>& byteCode) override;
		};

	}
}
