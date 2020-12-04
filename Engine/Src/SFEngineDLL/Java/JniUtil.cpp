////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2016 StormForge
// 
// Author : KyungKun Ko
//
// Description : Basic android application
//	
//
////////////////////////////////////////////////////////////////////////////////


#include "SFEngineDLLPCH.h"

#if SF_PLATFORM == SF_PLATFORM_ANDROID

#include "SFAssert.h"
#include "Util/SFUtility.h"

#include "JniUtil.h"




namespace SF
{

	/////////////////////////////////////////////////////////////////////////////
	//
	//	Variable map builder for java map object
	//


	void VariableMapBuilderJObject::SetVariable(const char* varName, Result value)
	{
		jstring jstrBuf = m_Env->NewStringUTF((const char*)varName);
		m_Env->CallVoidMethod(m_MapObject, m_SetMethodID, jstrBuf, (uint32_t)value);
	}

	void VariableMapBuilderJObject::SetVariable(const char* varName, bool value)
	{
		jstring jstrBuf = m_Env->NewStringUTF((const char*)varName);
		m_Env->CallVoidMethod(m_MapObject, m_SetMethodID, jstrBuf, value);
	}

	//void VariableMapBuilderJObject::SetVariable(const char* varName, int value)
	//{
	//	jstring jstrBuf = m_Env->NewStringUTF((const char*)varName);
	//	m_Env->CallVoidMethod(m_MapObject, m_SetMethodID, jstrBuf, value);
	//}

	//void VariableMapBuilderJObject::SetVariable(const char* varName, uint value)
	//{
	//	jstring jstrBuf = m_Env->NewStringUTF((const char*)varName);
	//	m_Env->CallVoidMethod(m_MapObject, m_SetMethodID, jstrBuf, value);
	//}

	void VariableMapBuilderJObject::SetVariable(const char* varName, int8_t value)
	{
		jstring jstrBuf = m_Env->NewStringUTF((const char*)varName);
		m_Env->CallVoidMethod(m_MapObject, m_SetMethodID, jstrBuf, value);
	}

	void VariableMapBuilderJObject::SetVariable(const char* varName, uint8_t value)
	{
		jstring jstrBuf = m_Env->NewStringUTF((const char*)varName);
		m_Env->CallVoidMethod(m_MapObject, m_SetMethodID, jstrBuf, value);
	}

	void VariableMapBuilderJObject::SetVariable(const char* varName, int16_t value)
	{
		jstring jstrBuf = m_Env->NewStringUTF((const char*)varName);
		m_Env->CallVoidMethod(m_MapObject, m_SetMethodID, jstrBuf, value);
	}

	void VariableMapBuilderJObject::SetVariable(const char* varName, uint16_t value)
	{
		jstring jstrBuf = m_Env->NewStringUTF((const char*)varName);
		m_Env->CallVoidMethod(m_MapObject, m_SetMethodID, jstrBuf, value);
	}

	void VariableMapBuilderJObject::SetVariable(const char* varName, int32_t value)
	{
		jstring jstrBuf = m_Env->NewStringUTF((const char*)varName);
		m_Env->CallVoidMethod(m_MapObject, m_SetMethodID, jstrBuf, value);
	}

	void VariableMapBuilderJObject::SetVariable(const char* varName, uint32_t value)
	{
		jstring jstrBuf = m_Env->NewStringUTF((const char*)varName);
		m_Env->CallVoidMethod(m_MapObject, m_SetMethodID, jstrBuf, value);
	}

	void VariableMapBuilderJObject::SetVariable(const char* varName, int64_t value)
	{
		jstring jstrBuf = m_Env->NewStringUTF((const char*)varName);
		m_Env->CallVoidMethod(m_MapObject, m_SetMethodID, jstrBuf, value);
	}

	void VariableMapBuilderJObject::SetVariable(const char* varName, uint64_t value)
	{
		jstring jstrBuf = m_Env->NewStringUTF((const char*)varName);
		m_Env->CallVoidMethod(m_MapObject, m_SetMethodID, jstrBuf, value);
	}

	void VariableMapBuilderJObject::SetVariable(const char* varName, uint128_t value)
	{
		jstring jstrBuf = m_Env->NewStringUTF((const char*)varName);
		m_Env->CallVoidMethod(m_MapObject, m_SetMethodID, jstrBuf, value);
	}

	void VariableMapBuilderJObject::SetVariable(const char* varName, float value)
	{
		jstring jstrBuf = m_Env->NewStringUTF((const char*)varName);
		m_Env->CallVoidMethod(m_MapObject, m_SetMethodID, jstrBuf, value);
	}

	void VariableMapBuilderJObject::SetVariable(const char* varName, double value)
	{
		jstring jstrBuf = m_Env->NewStringUTF((const char*)varName);
		m_Env->CallVoidMethod(m_MapObject, m_SetMethodID, jstrBuf, value);
	}

	void VariableMapBuilderJObject::SetVariable(const char* varName, const char* value)
	{
		jstring jstrBuf = m_Env->NewStringUTF((const char*)varName);
		jstring jstrValue = m_Env->NewStringUTF(value);
		m_Env->CallVoidMethod(m_MapObject, m_SetMethodID, jstrBuf, jstrValue);
	}

	void VariableMapBuilderJObject::SetVariable(const char* varName, const StringCrc64& value)
	{
		jstring jstrBuf = m_Env->NewStringUTF((const char*)varName);
		jstring jstrValue = m_Env->NewStringUTF((const char*)value);
		m_Env->CallVoidMethod(m_MapObject, m_SetMethodID, jstrBuf, jstrValue);
	}

	void VariableMapBuilderJObject::SetVariable(const char* varName, const RouteContext& value)
	{
		static jclass jcls = m_Env->FindClass("java/com/sf/SFRouteContext");
		static jmethodID constructorID = m_Env->GetMethodID(jcls, "<init>", "(J;J)V");

		jobject jobj = m_Env->NewObject(jcls, constructorID, (uint64_t)value.Components.From, (uint64_t)value.Components.To);

		jstring jstrBuf = m_Env->NewStringUTF((const char*)varName);
		m_Env->CallVoidMethod(m_MapObject, m_SetMethodID, jstrBuf, jobj);
	}

	void VariableMapBuilderJObject::SetVariable(const char* varName, const NetAddress& value)
	{
		static jclass jcls = m_Env->FindClass("java/com/sf/SFRouteContext");
		static jmethodID constructorID = m_Env->GetMethodID(jcls, "<init>", "(I;Ljava/lang/String;I)V");

		jstring jstrAddress = m_Env->NewStringUTF(value.Address);

		jobject jobj = m_Env->NewObject(jcls, constructorID, (int)value.SocketFamily, jstrAddress, (int)value.Port);

		jstring jstrBuf = m_Env->NewStringUTF((const char*)varName);
		m_Env->CallVoidMethod(m_MapObject, m_SetMethodID, jstrBuf, jobj);
	}

	void VariableMapBuilderJObject::SetVariable(const char* varName, const PlayerInformation& value)
	{
		static jclass jcls = m_Env->FindClass("java/com/sf/SFPlayerInformation");
		static jmethodID constructorID = m_Env->GetMethodID(jcls, "<init>", "(J;J;Ljava/lang/String;J;I;I)V");

		jstring jstrName = m_Env->NewStringUTF(value.NickName);

		jobject jobj = m_Env->NewObject(jcls, constructorID, (jlong)value.PlayerID, (jlong)value.FBUID, jstrName, (jlong)value.LastActiveTime, (int)value.Level, (int)value.IsPlayingGame);

		jstring jstrBuf = m_Env->NewStringUTF((const char*)varName);
		m_Env->CallVoidMethod(m_MapObject, m_SetMethodID, jstrBuf, jobj);
	}

	void VariableMapBuilderJObject::SetVariable(const char* varName, const RankingPlayerInformation& value)
	{
		static jclass jcls = m_Env->FindClass("java/com/sf/SFRankingPlayerInformation");
		static jmethodID constructorID = m_Env->GetMethodID(jcls, "<init>", "(J;J;Ljava/lang/String;J;I;I;I;I)V");

		jstring jstrName = m_Env->NewStringUTF(value.NickName);

		jobject jobj = m_Env->NewObject(jcls, constructorID, (jlong)value.PlayerID, (jlong)value.FBUID, jstrName, (jlong)value.LastActiveTime, (int)value.Level, (int)value.IsPlayingGame, (int)value.WeeklyWin, (int)value.WeeklyLose);

		jstring jstrBuf = m_Env->NewStringUTF((const char*)varName);
		m_Env->CallVoidMethod(m_MapObject, m_SetMethodID, jstrBuf, jobj);
	}

	void VariableMapBuilderJObject::SetVariable(const char* varName, const FriendInformation& value)
	{
		jobject jobj = ToJavaObject(value);

		jstring jstrBuf = m_Env->NewStringUTF((const char*)varName);
		m_Env->CallVoidMethod(m_MapObject, m_SetMethodID, jstrBuf, jobj);
	}

	void VariableMapBuilderJObject::SetVariable(const char* varName, const TotalRankingPlayerInformation& value)
	{
		jobject jobj = ToJavaObject(value);

		jstring jstrBuf = m_Env->NewStringUTF((const char*)varName);
		m_Env->CallVoidMethod(m_MapObject, m_SetMethodID, jstrBuf, jobj);
	}

	void VariableMapBuilderJObject::SetVariable(const char* varName, const RelayPlayerInfo& value)
	{
		jobject jobj = ToJavaObject(value);

		jstring jstrBuf = m_Env->NewStringUTF((const char*)varName);
		m_Env->CallVoidMethod(m_MapObject, m_SetMethodID, jstrBuf, jobj);
	}

	void VariableMapBuilderJObject::SetVariable(const char* varName, const GameInstanceInfo& value)
	{
		jobject jobj = ToJavaObject(value);

		jstring jstrBuf = m_Env->NewStringUTF((const char*)varName);
		m_Env->CallVoidMethod(m_MapObject, m_SetMethodID, jstrBuf, jobj);
	}




	void VariableMapBuilderJObject::SetVariable(const char* varName, const Array<const char*>& value)
	{
		jstring jstrBuf = m_Env->NewStringUTF((const char*)varName);

		jstring* pValues = new jstring[value.size()];
		for (int iValue = 0; iValue < value.size(); iValue++)
			pValues[iValue] = m_Env->NewStringUTF(value[iValue]);

		auto valueArray = m_Env->NewStringArray(value.size());
		m_Env->SetStringArrayRegion(valueArray, 0, value.size(), pValues);

		delete[] pValues;

		m_Env->CallVoidMethod(m_MapObject, m_SetMethodID, jstrBuf, valueArray);
	}

	void VariableMapBuilderJObject::SetVariable(const char* varName, const Array<bool>& value)
	{
		jstring jstrBuf = m_Env->NewStringUTF((const char*)varName);

		jboolean *pJBooleanValues = new jboolean[value.size()];
		for (int iValue = 0; iValue < value.size(); iValue++)
			pJBooleanValues[iValue] = value[iValue];

		auto valueArray = m_Env->NewBooleanArray(value.size());
		m_Env->SetBooleanArrayRegion(valueArray, 0, value.size(), pJBooleanValues);

		delete[] pJBooleanValues;

		m_Env->CallVoidMethod(m_MapObject, m_SetMethodID, jstrBuf, valueArray);
	}

	void VariableMapBuilderJObject::SetVariable(const char* varName, const Array<int8_t>& value)
	{
		jstring jstrBuf = m_Env->NewStringUTF((const char*)varName);

		auto valueArray = m_Env->NewByteArray(value.size());
		m_Env->SetByteArrayRegion(valueArray, 0, value.size(), value.data());

		m_Env->CallVoidMethod(m_MapObject, m_SetMethodID, jstrBuf, valueArray);
	}

	void VariableMapBuilderJObject::SetVariable(const char* varName, const Array<uint8_t>& value)
	{
		jstring jstrBuf = m_Env->NewStringUTF((const char*)varName);

		auto valueArray = m_Env->NewByteArray(value.size());
		m_Env->SetByteArrayRegion(valueArray, 0, value.size(), (int8_t*)value.data());

		m_Env->CallVoidMethod(m_MapObject, m_SetMethodID, jstrBuf, valueArray);
	}

	void VariableMapBuilderJObject::SetVariable(const char* varName, const Array<int16_t>& value)
	{
		jstring jstrBuf = m_Env->NewStringUTF((const char*)varName);

		auto valueArray = m_Env->NewShortArray(value.size());
		m_Env->SetShortArrayRegion(valueArray, 0, value.size(), value.data());

		m_Env->CallVoidMethod(m_MapObject, m_SetMethodID, jstrBuf, valueArray);
	}

	void VariableMapBuilderJObject::SetVariable(const char* varName, const Array<uint16_t>& value)
	{
		jstring jstrBuf = m_Env->NewStringUTF((const char*)varName);

		auto valueArray = m_Env->NewShortArray(value.size());
		m_Env->SetShortArrayRegion(valueArray, 0, value.size(), (int16_t*)value.data());

		m_Env->CallVoidMethod(m_MapObject, m_SetMethodID, jstrBuf, valueArray);
	}

	void VariableMapBuilderJObject::SetVariable(const char* varName, const Array<int32_t>& value)
	{
		jstring jstrBuf = m_Env->NewStringUTF((const char*)varName);

		auto valueArray = m_Env->NewIntArray(value.size());
		m_Env->SetIntArrayRegion(valueArray, 0, value.size(), value.data());

		m_Env->CallVoidMethod(m_MapObject, m_SetMethodID, jstrBuf, valueArray);
	}

	void VariableMapBuilderJObject::SetVariable(const char* varName, const Array<uint32_t>& value)
	{
		jstring jstrBuf = m_Env->NewStringUTF((const char*)varName);

		auto valueArray = m_Env->NewIntArray(value.size());
		m_Env->SetIntArrayRegion(valueArray, 0, value.size(), (int32_t*)value.data());

		m_Env->CallVoidMethod(m_MapObject, m_SetMethodID, jstrBuf, valueArray);
	}

	void VariableMapBuilderJObject::SetVariable(const char* varName, const Array<int64_t>& value)
	{
		jstring jstrBuf = m_Env->NewStringUTF((const char*)varName);

		auto valueArray = m_Env->NewLongArray(value.size());
		m_Env->SetLongArrayRegion(valueArray, 0, value.size(), (jlong*)value.data());

		m_Env->CallVoidMethod(m_MapObject, m_SetMethodID, jstrBuf, valueArray);
	}

	void VariableMapBuilderJObject::SetVariable(const char* varName, const Array<uint64_t>& value)
	{
		jstring jstrBuf = m_Env->NewStringUTF((const char*)varName);

		auto valueArray = m_Env->NewLongArray(value.size());
		m_Env->SetLongArrayRegion(valueArray, 0, value.size(), (jlong*)value.data());

		m_Env->CallVoidMethod(m_MapObject, m_SetMethodID, jstrBuf, valueArray);
	}

	void VariableMapBuilderJObject::SetVariable(const char* varName, const Array<float>& value)
	{
		jstring jstrBuf = m_Env->NewStringUTF((const char*)varName);

		auto valueArray = m_Env->NewFloatArray(value.size());
		m_Env->SetFloatArrayRegion(valueArray, 0, value.size(), value.data());

		m_Env->CallVoidMethod(m_MapObject, m_SetMethodID, jstrBuf, valueArray);
	}

	void VariableMapBuilderJObject::SetVariable(const char* varName, const Array< double>& value)
	{
		jstring jstrBuf = m_Env->NewStringUTF((const char*)varName);

		auto valueArray = m_Env->NewDoubleArray(value.size());
		m_Env->SetDoubleArrayRegion(valueArray, 0, value.size(), value.data());

		m_Env->CallVoidMethod(m_MapObject, m_SetMethodID, jstrBuf, valueArray);
	}

	void VariableMapBuilderJObject::SetVariable(const char* varName, const Array<FriendInformation>& value)
	{
		jstring jstrBuf = m_Env->NewStringUTF((const char*)varName);
		auto objectClass = m_Env->FindClass("java/lang/Object");
		auto valueArray = m_Env->NewObjectArray(value.size(), objectClass, nullptr);

		for (int iValue = 0; iValue < value.size(); iValue++)
			m_Env->SetObjectArrayElement(valueArray, iValue, ToJavaObject(value[iValue]));

		m_Env->CallVoidMethod(m_MapObject, m_SetMethodID, jstrBuf, valueArray);
	}

	void VariableMapBuilderJObject::SetVariable(const char* varName, const Array<TotalRankingPlayerInformation>& value)
	{
		jstring jstrBuf = m_Env->NewStringUTF((const char*)varName);

		auto objectClass = m_Env->FindClass("java/lang/Object");
		auto valueArray = m_Env->NewObjectArray(value.size(), objectClass, nullptr);

		for (int iValue = 0; iValue < value.size(); iValue++)
			m_Env->SetObjectArrayElement(valueArray, iValue, ToJavaObject(value[iValue]));

		m_Env->CallVoidMethod(m_MapObject, m_SetMethodID, jstrBuf, valueArray);
	}

	void VariableMapBuilderJObject::SetVariable(const char* varName, const Array<RelayPlayerInfo>& value)
	{
		jstring jstrBuf = m_Env->NewStringUTF((const char*)varName);

		auto objectClass = m_Env->FindClass("java/lang/Object");
		auto valueArray = m_Env->NewObjectArray(value.size(), objectClass, nullptr);

		for (int iValue = 0; iValue < value.size(); iValue++)
			m_Env->SetObjectArrayElement(valueArray, iValue, ToJavaObject(value[iValue]));

		m_Env->CallVoidMethod(m_MapObject, m_SetMethodID, jstrBuf, valueArray);
	}

	void VariableMapBuilderJObject::SetVariable(const char* varName, const Array<GameInstanceInfo>& value)
	{
		jstring jstrBuf = m_Env->NewStringUTF((const char*)varName);

		auto objectClass = m_Env->FindClass("java/lang/Object");
		auto valueArray = m_Env->NewObjectArray(value.size(), objectClass, nullptr);

		for (int iValue = 0; iValue < value.size(); iValue++)
			m_Env->SetObjectArrayElement(valueArray, iValue, ToJavaObject(value[iValue]));

		m_Env->CallVoidMethod(m_MapObject, m_SetMethodID, jstrBuf, valueArray);
	}

	void VariableMapBuilderJObject::SetVariable(const char* varName, const char* TypeName, const Array<uint8_t>& value)
	{
		jstring jstrBuf = m_Env->NewStringUTF((const char*)varName);
		jstring jstrBufType = m_Env->NewStringUTF((const char*)TypeName);

		auto valueArray = m_Env->NewByteArray(value.size());
		m_Env->SetByteArrayRegion(valueArray, 0, value.size(), (int8_t*)value.data());

		m_Env->CallVoidMethod(m_MapObject, m_SetMethodID, jstrBuf, jstrBufType, valueArray);
	}




	jobject VariableMapBuilderJObject::ToJavaObject(const FriendInformation& value)
	{
		static jclass jcls = m_Env->FindClass("java/com/sf/SFFriendInformation");
		static jmethodID constructorID = m_Env->GetMethodID(jcls, "<init>", "(J;J;Ljava/lang/String;J;I;I;I;I;J)V");

		jstring jstrName = m_Env->NewStringUTF(value.NickName);

		jobject jobj = m_Env->NewObject(jcls, constructorID, (jlong)value.PlayerID, (jlong)value.FBUID, jstrName, (jlong)value.LastActiveTime, (int)value.Level, (int)value.IsPlayingGame, (int)value.WeeklyWin, (int)value.WeeklyLose, (jlong)value.LastStaminaSent);
		return jobj;
	}

	jobject VariableMapBuilderJObject::ToJavaObject(const TotalRankingPlayerInformation& value)
	{
		static jclass jcls = m_Env->FindClass("java/com/sf/SFTotalRankingPlayerInformation");
		static jmethodID constructorID = m_Env->GetMethodID(jcls, "<init>", "(I;I;J;J;Ljava/lang/String;I;I;I)V");

		jstring jstrName = m_Env->NewStringUTF(value.NickName);

		jobject jobj = m_Env->NewObject(jcls, constructorID, (int)value.RankingID, (int)value.Ranking, (jlong)value.PlayerID, (jlong)value.FBUID, jstrName, (int)value.Level, (int)value.ScoreLow, (int)value.ScoreHigh);
		return jobj;
	}


	jobject VariableMapBuilderJObject::ToJavaObject(const RelayPlayerInfo& value)
	{
		static jclass jcls = m_Env->FindClass("java/com/sf/SFRelayPlayerInfo");
		static jmethodID constructorID = m_Env->GetMethodID(jcls, "<init>", "(J;J)V");

		jobject jobj = m_Env->NewObject(jcls, constructorID, (jlong)value.EndpointID, (jlong)value.RelayPlayerID);
		return jobj;
	}

}


#endif

