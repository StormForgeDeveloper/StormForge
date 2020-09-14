////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2020 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Variable
//	
//
////////////////////////////////////////////////////////////////////////////////


#include "SFCorePCH.h"
#include "Variable/SFVariable.h"
#include "Variable/SFVariableFactoryService.h"


namespace SF
{

	//////////////////////////////////////////////////////////////////////////////////////////////////
	//
	//	Variable Factory
	//

	Variable* VariableFactoryService::CreateVariable(StringCrc32 TypeName)
	{
		return CreateVariable(GetSystemHeap(), TypeName);
	}

	Variable* VariableFactoryService::CreateVariable(IHeap& heap, StringCrc32 TypeName)
	{
#define _CREATE_VARIABLE_TYPE_(TypeName) case TypeName::TYPE_NAME: return new(heap) TypeName();

		switch (TypeName)
		{
			_CREATE_VARIABLE_TYPE_(VariableBool);
			_CREATE_VARIABLE_TYPE_(VariableVoidP);
			_CREATE_VARIABLE_TYPE_(VariableInt);
			_CREATE_VARIABLE_TYPE_(VariableUInt);
			_CREATE_VARIABLE_TYPE_(VariableResult);
			_CREATE_VARIABLE_TYPE_(VariableInt64);
			_CREATE_VARIABLE_TYPE_(VariableUInt64);
			_CREATE_VARIABLE_TYPE_(VariableFloat);
			_CREATE_VARIABLE_TYPE_(VariableDouble);
			_CREATE_VARIABLE_TYPE_(VariableHex32);
			_CREATE_VARIABLE_TYPE_(VariableHex64);
			_CREATE_VARIABLE_TYPE_(VariableCharString);
			_CREATE_VARIABLE_TYPE_(VariableWCharString);
			_CREATE_VARIABLE_TYPE_(VariableString);
			_CREATE_VARIABLE_TYPE_(VariableStringCrc32);
			_CREATE_VARIABLE_TYPE_(VariableStringCrc64);
			_CREATE_VARIABLE_TYPE_(VariableBLOB);
		default:
			// TODO: Add dynamic type supports
			assert(false);
			return nullptr;
		}

#undef _CREATE_VARIABLE_TYPE_
	}

	Variable* VariableFactoryService::CreateVariable(Array<uint8_t>& bufer, StringCrc32 TypeName)
	{
#define _CREATE_VARIABLE_TYPE_(TypeName) case TypeName::TYPE_NAME: if (remainSize < sizeof(TypeName)) return nullptr; return new(pBufferPtr) TypeName();

		auto remainSize = bufer.GetAllocatedSize() - bufer.size();
		auto pBufferPtr = bufer.data() + bufer.size();
		switch (TypeName)
		{
			_CREATE_VARIABLE_TYPE_(VariableBool);
			_CREATE_VARIABLE_TYPE_(VariableVoidP);
			_CREATE_VARIABLE_TYPE_(VariableInt);
			_CREATE_VARIABLE_TYPE_(VariableUInt);
			_CREATE_VARIABLE_TYPE_(VariableResult);
			_CREATE_VARIABLE_TYPE_(VariableInt64);
			_CREATE_VARIABLE_TYPE_(VariableUInt64);
			_CREATE_VARIABLE_TYPE_(VariableFloat);
			_CREATE_VARIABLE_TYPE_(VariableDouble);
			_CREATE_VARIABLE_TYPE_(VariableHex32);
			_CREATE_VARIABLE_TYPE_(VariableHex64);
			_CREATE_VARIABLE_TYPE_(VariableCharString);
			_CREATE_VARIABLE_TYPE_(VariableWCharString);
			_CREATE_VARIABLE_TYPE_(VariableString);
			_CREATE_VARIABLE_TYPE_(VariableStringCrc32);
			_CREATE_VARIABLE_TYPE_(VariableStringCrc64);
			_CREATE_VARIABLE_TYPE_(VariableBLOB);

		default:
			// TODO: Add dynamic type supports
			assert(false);
			return nullptr;
		}

#undef _CREATE_VARIABLE_TYPE_
	}


} // namespace SF

