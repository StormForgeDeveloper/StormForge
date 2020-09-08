////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2016 StormForge
// 
// Author : KyungKun Ko
//
// Description : jni utility
//	
//
////////////////////////////////////////////////////////////////////////////////


#pragma once


#if SF_PLATFORM == SF_PLATFORM_ANDROID

#include "String/SFStringCrc64.h"
#include "String/SFString.h"
#include "Variable/SFVariableMapBuilder.h"
#include "jni.h"

struct ANativeActivity;
struct AConfiguration;

namespace SF
{
	/////////////////////////////////////////////////////////////////////////////
	//
	//	Variable map builder for java map object
	//

	class VariableMapBuilderJObject : public IVariableMapBuilder
	{
	private:

		JNIEnv* m_Env;
		jobject m_MapObject;
		jmethodID m_SetMethodID;

	public:

		VariableMapBuilderJObject(JNIEnv* env, jobject mapObject, jmethodID setMethodID)
			: m_Env(env)
			, m_MapObject(mapObject)
			, m_SetMethodID(setMethodID)
		{
		}


		virtual void SetVariable(const char* varName, Result value) override;
		virtual void SetVariable(const char* varName, bool value) override;
		//virtual void SetVariable(const char* varName, int value) override;
		//virtual void SetVariable(const char* varName, uint value) override;
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
		virtual void SetVariable(const char* varName, const Array<FriendInformation>& value) override;
		virtual void SetVariable(const char* varName, const Array<TotalRankingPlayerInformation>& value) override;
		virtual void SetVariable(const char* varName, const Array<RelayPlayerInfo>& value) override;


		jobject ToJavaObject(const FriendInformation& value);
		jobject ToJavaObject(const TotalRankingPlayerInformation& value);
		jobject ToJavaObject(const RelayPlayerInfo& value);

	};




}

#endif


