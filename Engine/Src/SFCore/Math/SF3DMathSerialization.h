////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2016 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Math library
//	
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "Math/SF3DMath.h"

namespace SF {


	class IInputStream;
	class IOutputStream;
	struct ToStringContext;

	inline size_t SerializedSizeOf(const Vector4& Value) { return sizeof(Value); }
	Result operator >> (IInputStream& input, Vector4& data);
	Result operator << (IOutputStream& output, const Vector4& data);

	Result _ToString(ToStringContext& context, const Vector4& value);


	inline size_t SerializedSizeOf(const Vector3& Value) { return sizeof(Value); }
	Result operator >> (IInputStream& input, Vector3& data);
	Result operator << (IOutputStream& output, const Vector3& data);

	Result _ToString(ToStringContext& context, const Vector3& value);


	DECLARE_BOXING_TEMPLETE_BYVALUE(Vector4);
	DECLARE_BOXING_TEMPLETE_BYVALUE(Vector3);

}



