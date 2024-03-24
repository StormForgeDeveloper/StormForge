////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2016 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : jni utility
//	
//
////////////////////////////////////////////////////////////////////////////////


#pragma once

#include "Util/SFStringCrc64.h"
#include "Util/SFString.h"
#include "Variable/SFVariableMapBuilder.h"
#include "Net/SFNetDef.h"




namespace SF
{
	typedef void(*ON_MESSAGE_FUNCTION)(uint32_t messageID, TransactionID transactionId, uint payloadSize, void* payloadPtr);
    typedef void(*SET_EVENT_FUNCTION)(Net::ConnectionEvent::EventTypes eventType, int32_t result, Net::ConnectionState state);



	template<typename DataType>
	class ArrayObject : public SharedObject, public DynamicArray<DataType>
	{
	public:
		ArrayObject(IHeap& heap = GetSystemHeap(), size_t increaseSize = 16)
			: DynamicArray<DataType>(heap, increaseSize)
		{
		}

		virtual ~ArrayObject()
		{}

		ArrayObject<DataType>& operator = (const Array<DataType>& src) { Array<DataType>::operator = (src); return *this; }
	};


	template<class Type>
	Type* NativeToObject(intptr_t pObj)
	{
		return static_cast<Type*>((SF::SharedObject*)pObj);
	}

	template<class Type>
	intptr_t NativeObjectToIntptr(Type* pObj)
	{
		return reinterpret_cast<intptr_t>(static_cast<SharedObject*>(pObj));
	}

}

