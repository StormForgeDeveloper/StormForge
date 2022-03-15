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


#include "SFMathTypes.h"
#include "Math/SF3DMathSoft.h"


namespace SF
{



	//////////////////////////////////////////////////////
	// Linear Algebra functions

	static const Vector2Soft<float>      Vector2Softf_Zero(0,0);
	static const Vector4Soft<float>      Vector4Softf_One(1,1,1,1);
	static const Vector3Soft<float>      Vector3Softf_One(1,1,1);
	static const Vector3Soft<float>      Vector3Softf_Zero(0,0,0);
	static const Vector3Soft<float>      Vector3Softf_X(1,0,0);
	static const Vector3Soft<float>      Vector3Softf_Y(0,1,0);
	static const Vector3Soft<float>      Vector3Softf_Z(0,0,1);
	static const Vector3Soft<float>      Vector3Softf_Neg_X(-1,0,0);
	static const Vector3Soft<float>      Vector3Softf_Neg_Y(0,-1,0);
	static const Vector3Soft<float>      Vector3Softf_Neg_Z(0,0,-1);
	static const Vector4Soft<float>      Vector4Softf_Zero(0,0,0,0);
	static const Vector4Soft<float>      Vector4Softf_X(1,0,0,0);
	static const Vector4Soft<float>      Vector4Softf_Neg_X(-1,0,0,0);
	static const Vector4Soft<float>      Vector4Softf_Y(0,1,0,0);
	static const Vector4Soft<float>      Vector4Softf_Neg_Y(0,-1,0,0);
	static const Vector4Soft<float>      Vector4Softf_Z(0,0,1,0);
	static const Vector4Soft<float>      Vector4Softf_Neg_Z(0,0,-1,0);
	static const Vector4Soft<float>      Vector4Softf_W(0,0,0,1);
	static const Vector4Soft<float>      Vector4Softf_Neg_W(0,0,0,-1);
	static const QuaternionSoft<float>   QuaternionSoft_Identity(0,0,0,1);


	extern template struct Vector2Soft<int>;
	extern template struct Vector2Soft<float>;
	extern template struct Vector3Soft<float>;
	extern template struct Vector4Soft<float>;
	extern template struct Vector2Soft<int>;
	extern template struct Vector3Soft<int>;
	extern template struct Vector4Soft<int>;
	extern template struct Vector2Soft<unsigned int>;
	extern template struct Vector3Soft<unsigned int>;
	extern template struct Vector4Soft<unsigned int>;
	extern template struct Vector4Soft<uint8_t>;
	extern template struct Vector4Soft<short>;
	extern template struct Vector4Soft<unsigned short>;
	extern template struct Matrix3Soft<float>;
	extern template struct Matrix4Soft<float>;
	extern template struct QuaternionSoft<float>;





	typedef Vector2Soft<float> Vector2Softf;
	typedef Vector3Soft<float> Vector3Softf;
	typedef Vector4Soft<float> Vector4Softf;

	typedef Vector2Soft<int> Vector2Softi;
	typedef Vector3Soft<int> Vector3Softi;
	typedef Vector4Soft<int> Vector4Softi;

	typedef Vector2Soft<unsigned int> Vector2Softui;
	typedef Vector3Soft<unsigned int> Vector3Softui;
	typedef Vector4Soft<unsigned int> Vector4Softui;

	typedef Vector4Soft<uint8_t> Vector4Softb;

	typedef Vector4Soft<short> Vector4Softs;
	typedef Vector4Soft<unsigned short> Vector4Softus;

	typedef Matrix3Soft<float> Matrix3Softf;
	typedef Matrix3Soft<float> Matrix4Softf;
	typedef QuaternionSoft<float> QuaternionSoftf;





	//
	//                R     N     L
	//                  _       _
	//                 |\   ^   /|
	//                   \  |  /
	//                    \ | /
	//                     \|/
	//                      +
	template<class T>  Vector3Soft<T> Reflect(const Vector3Soft<T> & n, const Vector3Soft<T> & l);


	template<class T>  Matrix4Soft<T> MakeLookAtMatrix(const Vector3Soft<T> & eye, const Vector3Soft<T> & center, const Vector3Soft<T> & up);
	template<class T>  Matrix4Soft<T> MakeFrustumMatrix(const T l, const T r, const T b, const T t, const T n, const T f);

	template<class T>  Matrix4Soft<T> MakePerspectiveMatrix(const T fovy, const T aspect, const T n, const T f);
	template<class T>  Matrix4Soft<T> MakeOrthoMatrix(const T left,
		const T right,
		const T bottom,
		const T top,
		const T n,
		const T f);


	template<class T>
	Matrix4Soft<T> MakeRotationYawPitchRoll(const T yaw, const T pitch, const T roll);

} //namespace SF


#include "SFMath.inl"

