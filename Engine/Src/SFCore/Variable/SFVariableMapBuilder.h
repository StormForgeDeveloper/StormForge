////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2016 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Variable map builder
//
////////////////////////////////////////////////////////////////////////////////


#pragma once


#include "SFTypedefs.h"
#include "Types/SFEngineTypedefs.h"
#include "SFAssert.h"
#include "String/SFStringCrc64.h"
#include "String/SFString.h"


namespace SF {



	/////////////////////////////////////////////////////////////////////////////////
	//
	//	variable map builder class
	//

	class IVariableMapBuilder
	{
	private:

	public:

		IVariableMapBuilder()
		{
		}

		virtual ~IVariableMapBuilder()
		{
		}

		virtual void SetVariable(const char* varName, Result value) = 0;
		virtual void SetVariable(const char* varName, bool value) = 0;
		virtual void SetVariable(const char* varName, int8_t value) = 0;
		virtual void SetVariable(const char* varName, uint8_t value) = 0;
		virtual void SetVariable(const char* varName, int16_t value) = 0;
		virtual void SetVariable(const char* varName, uint16_t value) = 0;
		virtual void SetVariable(const char* varName, int32_t value) = 0;
		virtual void SetVariable(const char* varName, uint32_t value) = 0;
		virtual void SetVariable(const char* varName, int64_t value) = 0;
		virtual void SetVariable(const char* varName, uint64_t value) = 0;
		virtual void SetVariable(const char* varName, uint128_t value) = 0;
		virtual void SetVariable(const char* varName, float value) = 0;
		virtual void SetVariable(const char* varName, double value) = 0;
		virtual void SetVariable(const char* varName, const StringCrc64& value) = 0;
		virtual void SetVariable(const char* varName, const char* value) = 0;

		virtual void SetVariable(const char* varName, const RouteContext& value) = 0;
		virtual void SetVariable(const char* varName, const NetAddress& value) = 0;
		virtual void SetVariable(const char* varName, const PlayerInformation& value) = 0;
		virtual void SetVariable(const char* varName, const RankingPlayerInformation& value) = 0;
		virtual void SetVariable(const char* varName, const FriendInformation& value) = 0;
		virtual void SetVariable(const char* varName, const TotalRankingPlayerInformation& value) = 0;
		virtual void SetVariable(const char* varName, const RelayPlayerInfo& value) = 0;

		virtual void SetVariable(const char* varName, const Array<bool>& value) = 0;
		virtual void SetVariable(const char* varName, const Array<int8_t>& value) = 0;
		virtual void SetVariable(const char* varName, const Array<uint8_t>& value) = 0;
		virtual void SetVariable(const char* varName, const Array<int16_t>& value) = 0;
		virtual void SetVariable(const char* varName, const Array<uint16_t>& value) = 0;
		virtual void SetVariable(const char* varName, const Array<int32_t>& value) = 0;
		virtual void SetVariable(const char* varName, const Array<uint32_t>& value) = 0;
		virtual void SetVariable(const char* varName, const Array<int64_t>& value) = 0;
		virtual void SetVariable(const char* varName, const Array<uint64_t>& value) = 0;
		virtual void SetVariable(const char* varName, const Array<float>& value) = 0;
		virtual void SetVariable(const char* varName, const Array<double>& value) = 0;
		virtual void SetVariable(const char* varName, const Array<FriendInformation>& value) = 0;
		virtual void SetVariable(const char* varName, const Array<TotalRankingPlayerInformation>& value) = 0;
		virtual void SetVariable(const char* varName, const Array<RelayPlayerInfo>& value) = 0;
	};



} // namespace SF




