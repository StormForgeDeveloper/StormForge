////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2016 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Basic android application
//	
//
////////////////////////////////////////////////////////////////////////////////


#include "SFEngineDLLPCH.h"
#include "SFAssert.h"
#include "Util/SFUtility.h"

#include "SFCSUtil.h"




namespace SF
{

	/////////////////////////////////////////////////////////////////////////////
	//
	//	Variable map builder for java map object
	//


	void VariableMapBuilderCS::SetVariable(const char* varName, Result value)
	{
		m_SetFunc(varName, "Result", &value);
	}

	void VariableMapBuilderCS::SetVariable(const char* varName, bool value)
	{
		m_SetFunc(varName, "bool", &value);
	}

	void VariableMapBuilderCS::SetVariable(const char* varName, int8_t value)
	{
		m_SetFunc(varName, "int8", &value);
	}

	void VariableMapBuilderCS::SetVariable(const char* varName, uint8_t value)
	{
		m_SetFunc(varName, "uint8", &value);
	}

	void VariableMapBuilderCS::SetVariable(const char* varName, int16_t value)
	{
		m_SetFunc(varName, "int16", &value);
	}

	void VariableMapBuilderCS::SetVariable(const char* varName, uint16_t value)
	{
		m_SetFunc(varName, "uint16", &value);
	}

	void VariableMapBuilderCS::SetVariable(const char* varName, int32_t value)
	{
		m_SetFunc(varName, "int32", &value);
	}

	void VariableMapBuilderCS::SetVariable(const char* varName, uint32_t value)
	{
		m_SetFunc(varName, "uint32", &value);
	}

	void VariableMapBuilderCS::SetVariable(const char* varName, int64_t value)
	{
		m_SetFunc(varName, "int64", &value);
	}

	void VariableMapBuilderCS::SetVariable(const char* varName, uint64_t value)
	{
		m_SetFunc(varName, "uint64", &value);
	}

	void VariableMapBuilderCS::SetVariable(const char* varName, uint128_t value)
	{
		m_SetFunc(varName, "uint128", &value);
	}

	void VariableMapBuilderCS::SetVariable(const char* varName, float value)
	{
		m_SetFunc(varName, "float", &value);
	}

	void VariableMapBuilderCS::SetVariable(const char* varName, double value)
	{
		m_SetFunc(varName, "double", &value);
	}

	void VariableMapBuilderCS::SetVariable(const char* varName, const char* value)
	{
		auto strLen = value != nullptr ? strlen(value) : 0;
		m_SetArrayFunc(varName, "single_string", (int)strLen, value);
		//m_SetFunc(varName, "string", value);
	}

	void VariableMapBuilderCS::SetVariable(const char* varName, const StringCrc64& value)
	{
		uint64_t hashValue = value;
		m_SetFunc(varName, "StringCrc64", &hashValue);
	}

	void VariableMapBuilderCS::SetVariable(const char* varName, const RouteContext& value)
	{
		m_SetFunc(varName, "RouteContext", &value);
	}

	void VariableMapBuilderCS::SetVariable(const char* varName, const NetAddress& value)
	{
		//uint8_t buffer[1024];
		//for (int iIndex = 0; iIndex < countof(buffer); iIndex++)
		//{
		//	buffer[iIndex] = iIndex;
		//}
		m_SetFunc(varName, "NetAddress", &value);
	}

	void VariableMapBuilderCS::SetVariable(const char* varName, const PlayerInformation& value)
	{
		m_SetFunc(varName, "PlayerInformation", &value);
	}

	void VariableMapBuilderCS::SetVariable(const char* varName, const RankingPlayerInformation& value)
	{
		m_SetFunc(varName, "RankingPlayerInformation", &value);
	}

	void VariableMapBuilderCS::SetVariable(const char* varName, const FriendInformation& value)
	{
		m_SetFunc(varName, "FriendInformation", &value);
	}

	void VariableMapBuilderCS::SetVariable(const char* varName, const TotalRankingPlayerInformation& value)
	{
		m_SetFunc(varName, "TotalRankingPlayerInformation", &value);
	}

	void VariableMapBuilderCS::SetVariable(const char* varName, const RelayPlayerInfo& value)
	{
		m_SetFunc(varName, "RelayPlayerInfo", &value);
	}

	void VariableMapBuilderCS::SetVariable(const char* varName, const NamedVariable& value)
	{
		m_SetFunc(varName, "NamedVariable", &value);
	}

	void VariableMapBuilderCS::SetVariable(const char* varName, const Array<bool>& value)
	{
		m_SetArrayFunc(varName, "bool", (int)value.size(), value.data());
	}

	void VariableMapBuilderCS::SetVariable(const char* varName, const Array<int8_t>& value)
	{
		m_SetArrayFunc(varName, "int8", (int)value.size(), value.data());
	}

	void VariableMapBuilderCS::SetVariable(const char* varName, const Array<uint8_t>& value)
	{
		m_SetArrayFunc(varName, "uint8", (int)(int)value.size(), value.data());
	}

	void VariableMapBuilderCS::SetVariable(const char* varName, const Array<int16_t>& value)
	{
		m_SetArrayFunc(varName, "int16", (int)value.size(), value.data());
	}

	void VariableMapBuilderCS::SetVariable(const char* varName, const Array<uint16_t>& value)
	{
		m_SetArrayFunc(varName, "uint16", (int)value.size(), value.data());
	}

	void VariableMapBuilderCS::SetVariable(const char* varName, const Array<int32_t>& value)
	{
		m_SetArrayFunc(varName, "int32", (int)value.size(), value.data());
	}

	void VariableMapBuilderCS::SetVariable(const char* varName, const Array<uint32_t>& value)
	{
		m_SetArrayFunc(varName, "uint32", (int)value.size(), value.data());
	}

	void VariableMapBuilderCS::SetVariable(const char* varName, const Array<int64_t>& value)
	{
		m_SetArrayFunc(varName, "int64", (int)value.size(), value.data());
	}

	void VariableMapBuilderCS::SetVariable(const char* varName, const Array<uint64_t>& value)
	{
		m_SetArrayFunc(varName, "uint64", (int)value.size(), value.data());
	}

	void VariableMapBuilderCS::SetVariable(const char* varName, const Array<float>& value)
	{
		m_SetArrayFunc(varName, "float", (int)value.size(), value.data());
	}

	void VariableMapBuilderCS::SetVariable(const char* varName, const Array< double>& value)
	{
		m_SetArrayFunc(varName, "double", (int)value.size(), value.data());
	}

	void VariableMapBuilderCS::SetVariable(const char* varName, const Array<FriendInformation>& value)
	{
		m_SetArrayFunc(varName, "FriendInformation", (int)value.size(), value.data());
	}

	void VariableMapBuilderCS::SetVariable(const char* varName, const Array<TotalRankingPlayerInformation>& value)
	{
		m_SetArrayFunc(varName, "TotalRankingPlayerInformation", (int)value.size(), value.data());
	}

	void VariableMapBuilderCS::SetVariable(const char* varName, const Array<RelayPlayerInfo>& value)
	{
		m_SetArrayFunc(varName, "RelayPlayerInfo", (int)value.size(), value.data());
	}

	void VariableMapBuilderCS::SetVariable(const char* varName, const Array<NamedVariable>& value)
	{
		m_SetArrayFunc(varName, "NamedVariable", (int)value.size(), value.data());
	}



}
