////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Math library
//	
//
////////////////////////////////////////////////////////////////////////////////

#include "SFCorePCH.h"
#include "SFTypedefs.h"
#include "Math/SF3DMath.h"
#include "Math/SF3DMathSerialization.h"
#include "Stream/SFStream.h"


namespace SF {

	Result operator >> (IInputStream& input, Vector4& data)
	{
		return input.Read(&data, sizeof(data));
	}

	Result operator << (IOutputStream& output, const Vector4& data)
	{
		return output.Write(&data, sizeof(data));
	}


	Result _ToString(ToStringContext& context, const Vector4& value)
	{
		if (!StrUtil::StringCopyEx(context.OutStream.pBuffer, context.OutStream.BuffLen, "("))
			return ResultCode::FAIL;

		if (!_FToA(context, value.x))
			return ResultCode::FAIL;


		if (!StrUtil::StringCopyEx(context.OutStream.pBuffer, context.OutStream.BuffLen, ","))
			return ResultCode::FAIL;

		if (!_FToA(context, value.y))
			return ResultCode::FAIL;


		if (!StrUtil::StringCopyEx(context.OutStream.pBuffer, context.OutStream.BuffLen, ","))
			return ResultCode::FAIL;

		if (!_FToA(context, value.z))
			return ResultCode::FAIL;

		if (!StrUtil::StringCopyEx(context.OutStream.pBuffer, context.OutStream.BuffLen, ")"))
			return ResultCode::FAIL;

		return ResultCode::SUCCESS;
	}


	Result operator >> (IInputStream& input, Vector3& data)
	{
		return input.Read(&data, sizeof(float) * 3);
	}

	Result operator << (IOutputStream& output, const Vector3& data)
	{
		return output.Write(&data, sizeof(float) * 3);
	}


	Result _ToString(ToStringContext& context, const Vector3& value)
	{
		if (!StrUtil::StringCopyEx(context.OutStream.pBuffer, context.OutStream.BuffLen, "("))
			return ResultCode::FAIL;

		if (!_FToA(context, value.x))
			return ResultCode::FAIL;


		if (!StrUtil::StringCopyEx(context.OutStream.pBuffer, context.OutStream.BuffLen, ","))
			return ResultCode::FAIL;

		if (!_FToA(context, value.y))
			return ResultCode::FAIL;


		if (!StrUtil::StringCopyEx(context.OutStream.pBuffer, context.OutStream.BuffLen, ","))
			return ResultCode::FAIL;

		if (!_FToA(context, value.z))
			return ResultCode::FAIL;

		if (!StrUtil::StringCopyEx(context.OutStream.pBuffer, context.OutStream.BuffLen, ")"))
			return ResultCode::FAIL;

		return ResultCode::SUCCESS;
	}


	IMPLEMENT_BOXING_TEMPLETE_BYVALUE(Vector4)
	IMPLEMENT_BOXING_TEMPLETE_BYVALUE(Vector3)



	Result operator >> (IInputStream& input, Vector3i& data)
	{
		return input.Read(&data, sizeof(int) * 3);
	}

	Result operator << (IOutputStream& output, const Vector3i& data)
	{
		return output.Write(&data, sizeof(int) * 3);
	}


	Result _ToString(ToStringContext& context, const Vector3i& value)
	{
		if (!StrUtil::StringCopyEx(context.OutStream.pBuffer, context.OutStream.BuffLen, "("))
			return ResultCode::FAIL;

		if (!_IToA(context, value.x))
			return ResultCode::FAIL;


		if (!StrUtil::StringCopyEx(context.OutStream.pBuffer, context.OutStream.BuffLen, ","))
			return ResultCode::FAIL;

		if (!_IToA(context, value.y))
			return ResultCode::FAIL;


		if (!StrUtil::StringCopyEx(context.OutStream.pBuffer, context.OutStream.BuffLen, ","))
			return ResultCode::FAIL;

		if (!_IToA(context, value.z))
			return ResultCode::FAIL;

		if (!StrUtil::StringCopyEx(context.OutStream.pBuffer, context.OutStream.BuffLen, ")"))
			return ResultCode::FAIL;

		return ResultCode::SUCCESS;
	}

	IMPLEMENT_BOXING_TEMPLETE_BYVALUE(Vector3i)


	Result operator >> (IInputStream& input, Vector2i& data)
	{
		return input.Read(&data, sizeof(int) * 2);
	}

	Result operator << (IOutputStream& output, const Vector2i& data)
	{
		return output.Write(&data, sizeof(int) * 2);
	}


	Result _ToString(ToStringContext& context, const Vector2i& value)
	{
		if (!StrUtil::StringCopyEx(context.OutStream.pBuffer, context.OutStream.BuffLen, "("))
			return ResultCode::FAIL;

		if (!_IToA(context, value.x))
			return ResultCode::FAIL;

		if (!StrUtil::StringCopyEx(context.OutStream.pBuffer, context.OutStream.BuffLen, ","))
			return ResultCode::FAIL;

		if (!_IToA(context, value.y))
			return ResultCode::FAIL;

		if (!StrUtil::StringCopyEx(context.OutStream.pBuffer, context.OutStream.BuffLen, ")"))
			return ResultCode::FAIL;

		return ResultCode::SUCCESS;
	}

	IMPLEMENT_BOXING_TEMPLETE_BYVALUE(Vector2i)
}

