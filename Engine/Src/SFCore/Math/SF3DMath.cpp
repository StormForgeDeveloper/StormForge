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

#include "SFCorePCH.h"
#include "SFTypedefs.h"
#include "Math/SF3DMath.h"


namespace SF {


	template struct Vector2Soft<float>;
	template struct Vector3Soft<float>;
	template struct Vector4Soft<float>;
	template struct Vector2Soft<int>;
	template struct Vector3Soft<int>;
	template struct Vector4Soft<int>;
	template struct Vector2Soft<unsigned int>;
	template struct Vector3Soft<unsigned int>;
	template struct Vector4Soft<unsigned int>;

	template struct Vector4Soft<uint8_t>;
	template struct Vector4Soft<short>;
	template struct Vector4Soft<unsigned short>;


	template struct Matrix3Soft<float>;
	template struct Matrix4Soft<float>;

	template struct QuaternionSoft<float>;

}

