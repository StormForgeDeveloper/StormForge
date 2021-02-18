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
	typedef void(*SET_MESSAGE_FUNCTION)(uint32_t messageID);
	typedef void(*ON_READY_FUNCTION)();
	typedef void(*SET_EVENT_FUNCTION)(Net::ConnectionEvent::EventTypes eventType, int32_t result, Net::ConnectionState state);


	/////////////////////////////////////////////////////////////////////////////
	//
	//	Variable map builder for java map object
	//

	class VariableMapBuilderCS : public IVariableMapBuilder
	{
	public:

		typedef void(*SET_FUNCTION)(const char* stringHash, const char* typeNameHash, const void* Value);
		typedef void(*SET_ARRAY_FUNCTION)(const char* stringHash, const char* typeNameHash, int arrayCount, const void* Value);

	private:

		SET_FUNCTION m_SetFunc;
		SET_ARRAY_FUNCTION m_SetArrayFunc;

	public:

		VariableMapBuilderCS(SET_FUNCTION setMethod, SET_ARRAY_FUNCTION setArrayMethod)
			: m_SetFunc(setMethod)
			, m_SetArrayFunc(setArrayMethod)
		{
		}


		virtual void SetVariable(const char* varName, Result value) override;
		virtual void SetVariable(const char* varName, bool value) override;
		virtual void SetVariable(const char* varName, int8_t value) override;
		virtual void SetVariable(const char* varName, uint8_t value) override;
		virtual void SetVariable(const char* varName, int16_t value) override;
		virtual void SetVariable(const char* varName, uint16_t value) override;
		virtual void SetVariable(const char* varName, int32_t value) override;
		virtual void SetVariable(const char* varName, uint32_t value) override;
		virtual void SetVariable(const char* varName, int64_t value) override;
		virtual void SetVariable(const char* varName, uint64_t value) override;
		virtual void SetVariable(const char* varName, uint128_t value) override;
		virtual void SetVariable(const char* varName, float value) override;
		virtual void SetVariable(const char* varName, double value) override;
		virtual void SetVariable(const char* varName, const char* value) override;
		virtual void SetVariable(const char* varName, const StringCrc64& value) override;

		virtual void SetVariable(const char* varName, const RouteContext& value) override;
		virtual void SetVariable(const char* varName, const NetAddress& value) override;
		virtual void SetVariable(const char* varName, const PlayerInformation& value) override;
		virtual void SetVariable(const char* varName, const RankingPlayerInformation& value) override;
		virtual void SetVariable(const char* varName, const FriendInformation& value) override;
		virtual void SetVariable(const char* varName, const TotalRankingPlayerInformation& value) override;
		virtual void SetVariable(const char* varName, const RelayPlayerInfo& value) override;
		virtual void SetVariable(const char* varName, const GameInstanceInfo& value) override;

		virtual void SetVariable(const char* varName, const Array<bool>& value) override;
		virtual void SetVariable(const char* varName, const Array<int8_t>& value) override;
		virtual void SetVariable(const char* varName, const Array<uint8_t>& value) override;
		virtual void SetVariable(const char* varName, const Array<int16_t>& value) override;
		virtual void SetVariable(const char* varName, const Array<uint16_t>& value) override;
		virtual void SetVariable(const char* varName, const Array<int32_t>& value) override;
		virtual void SetVariable(const char* varName, const Array<uint32_t>& value) override;
		virtual void SetVariable(const char* varName, const Array<int64_t>& value) override;
		virtual void SetVariable(const char* varName, const Array<uint64_t>& value) override;
		virtual void SetVariable(const char* varName, const Array<float>& value) override;
		virtual void SetVariable(const char* varName, const Array<double>& value) override;
		virtual void SetVariable(const char* varName, const Array<PlayerInformation>& value) override;
		virtual void SetVariable(const char* varName, const Array<FriendInformation>& value) override;
		virtual void SetVariable(const char* varName, const Array<TotalRankingPlayerInformation>& value) override;
		virtual void SetVariable(const char* varName, const Array<RelayPlayerInfo>& value) override;
		virtual void SetVariable(const char* varName, const Array<GameInstanceInfo>& value) override;
		virtual void SetVariable(const char* varName, const Array<const char*>& value) override;
		virtual void SetVariable(const char* varName, const Array<VariableTable>& value) override;

		virtual void SetVariable(const char* varName, const char* typeName, const Array<uint8_t>& value) override;

	};


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

