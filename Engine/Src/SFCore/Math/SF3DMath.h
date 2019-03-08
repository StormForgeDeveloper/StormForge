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

#include "Math/SFMathConsts.h"
#include <math.h>

#include "Math/SF3DMathSoft.h"
#include "Math/SF3DMathSSE.h"

namespace SF {



#if defined(SF_SIMD_SSE)
	typedef Vector4SSE Vector4;
	typedef Matrix4SSE Matrix4;
	typedef QuaternionSSE Quaternion;
#else
	typedef Vector4Soft<float> Vector4;
	typedef Matrix4Soft<float> Matrix4;
	typedef QuaternionSoft<float> Quaternion;
#endif

	typedef Vector3Soft<float> Vector3;
	typedef Vector2Soft<float> Vector2;

}



