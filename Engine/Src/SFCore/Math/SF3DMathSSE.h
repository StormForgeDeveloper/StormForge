////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2018 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Math library
//	
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "Math/SFMathConsts.h"
#include "MemoryManager/SFMemory.h"
#include "Math/SFMathUtil.h"


#ifdef SF_SIMD_SSE

#include <xmmintrin.h>
#ifdef SF_SIMD_AVX
#include <immintrin.h>
#endif

namespace SF {

	struct Matrix4SSE;
	struct QuaternionSSE;



	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//
	//	SSE macros
	//

	// vec(0, 1, 2, 3) -> (vec[x], vec[y], vec[z], vec[w])
	#define _SF_SWIZZLE(vec, w,z,y,x)           _mm_shuffle_ps(vec, vec, _MM_SHUFFLE(w,z,y,x))
	#define _SF_SWIZZLE1(vec, x)                _mm_shuffle_ps(vec, vec, _MM_SHUFFLE(x,x,x,x))

	// special swizzle
	// xyxy
	#define _SF_SWIZZLE_0101(vec)               _mm_movelh_ps(vec, vec)
	// zwzw
	#define _SF_SWIZZLE_2323(vec)               _mm_movehl_ps(vec, vec)
	// xxzz
	#define _SF_SWIZZLE_0022(vec)               _mm_moveldup_ps(vec)
	// yyww
	#define _SF_SWIZZLE_1133(vec)               _mm_movehdup_ps(vec)

	// return (vec1[x], vec1[y], vec2[z], vec2[w])
	#define _SF_SHUFFLE(vec1, vec2, w,z,y,x)    _mm_shuffle_ps(vec1, vec2, _MM_SHUFFLE(w,z,y,x))
	// special shuffle
	#define _SF_SHUFFLE_0101(vec1, vec2)        _mm_movelh_ps(vec1, vec2)
	#define _SF_SHUFFLE_2323(vec1, vec2)        _mm_movehl_ps(vec2, vec1)

	// Shuffling 4 vectors
	#define _SF_SHUFFLE4(w,z,y,x,iw,iz,iy,ix) _mm_shuffle_ps(\
												_mm_shuffle_ps(x, y, _MM_SHUFFLE(iy, iy, ix, ix)),\
												_mm_shuffle_ps(z, w, _MM_SHUFFLE(iw, iw, iz, iz)),\
												_MM_SHUFFLE(2, 0, 2, 0)\
											)



	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//
	//	SSE Vector4
	//

	struct SF_DECLARE_ALIGN_DOUBLE Vector4SSE
	{
		static const Vector4SSE& Zero() { static const Vector4SSE Value(0, 0, 0, 0); return Value; }
		static const Vector4SSE& One() { static const Vector4SSE Value(1, 1, 1, 1); return Value; }


		Vector4SSE() { }
		Vector4SSE(float x) : Packed(_mm_set_ps1(x)) {  }
		Vector4SSE(float x, float y, float z, float w = 0) : Packed(_mm_set_ps(w, z, y, x)) { }
		Vector4SSE(const float* xyzw) : Packed(_mm_set_ps(xyzw[3], xyzw[2], xyzw[1], xyzw[0])) { }
		Vector4SSE(const Vector4SSE& u) : Packed(u.Packed) { }
		Vector4SSE(const __m128& u) : Packed(u) { }

        SF_FORCEINLINE bool operator==(const Vector4SSE & u) const
		{
			__m128i vcmp = _mm_castps_si128(_mm_cmpneq_ps(Packed, u.Packed));
            int test = _mm_movemask_epi8(vcmp);
			return test == 0;
		}

        SF_FORCEINLINE bool operator!=(const Vector4SSE& op) const
		{
			__m128i vcmp = _mm_castps_si128(_mm_cmpneq_ps(Packed, op.Packed));
            int test = _mm_movemask_epi8(vcmp);
			return test != 0;
		}

        SF_FORCEINLINE bool operator>(const Vector4SSE& op) const
        {
            __m128i vcmp = _mm_castps_si128(_mm_cmpngt_ps(Packed, op.Packed));
            int test = _mm_movemask_epi8(vcmp);
            return test == 0;
        }

        SF_FORCEINLINE bool operator>=(const Vector4SSE& op) const
        {
            __m128i vcmp = _mm_castps_si128(_mm_cmpnge_ps(Packed, op.Packed));
            int test = _mm_movemask_epi8(vcmp);
            return test == 0;
        }

        SF_FORCEINLINE bool operator<(const Vector4SSE& op) const
        {
            __m128i vcmp = _mm_castps_si128(_mm_cmpnlt_ps(Packed, op.Packed));
            int test = _mm_movemask_epi8(vcmp);
            return test == 0;
        }

        SF_FORCEINLINE bool operator<=(const Vector4SSE& op) const
        {
            __m128i vcmp = _mm_castps_si128(_mm_cmpnle_ps(Packed, op.Packed));
            int test = _mm_movemask_epi8(vcmp);
            return test == 0;
        }


		Vector4SSE operator*(const Matrix4SSE & M) const;
		Vector4SSE & operator*=(const Matrix4SSE & M);

		Vector4SSE  operator/(const float & scala) const;
		Vector4SSE  operator*(const float & scala) const;
		Vector4SSE & operator/=(const float & scala);
		Vector4SSE & operator*=(const float & scala);

		Vector4SSE & operator-=(const Vector4SSE & u);
		Vector4SSE & operator+=(const Vector4SSE & u);

		Vector4SSE operator-(const Vector4SSE & u) const;
		Vector4SSE operator+(const Vector4SSE & u) const;
		Vector4SSE operator*(const Vector4SSE & u) const;
		Vector4SSE operator/(const Vector4SSE & u) const;

        SF_FORCEINLINE Vector4SSE operator - () const { return Vector4SSE(-x, -y, -z, -w); }

		Vector4SSE & operator=(const Vector4SSE & src);

		float SquareLength3() const;
		float Length3() const;

		float SquareLength4() const;
		float Length4() const;

		// returns orthogonal length
		void Normalize4();
		void Normalize3();
		float Normalize3Hi();

		Vector4SSE& Scale3(float scale);

		Vector4SSE GetAbs() const;

		float Dot3(const Vector4SSE& op) const;
		float Dot4(const Vector4SSE& op) const;

		// Cross operation
		Vector4SSE Cross(const Vector4SSE& op) const;

		// Same to Cross but leave w as garbage
		Vector4SSE CrossRaw(const Vector4SSE& op) const;

		Vector4SSE& SwapLH()
		{
			Packed = _SF_SWIZZLE(Packed, 1, 0, 3, 2);
			return *this;
		}

		Vector4SSE GetSwapLH()
		{
			return Vector4SSE(_SF_SWIZZLE(Packed, 1, 0, 3, 2));
		}
		Vector4SSE& MAdd(const float & scala);

		// simd friendly access
		float GetX() const { return _mm_cvtss_f32(Packed); }
		float GetY() const { return _mm_cvtss_f32(_SF_SWIZZLE(Packed, 1, 1, 1, 1)); }
		float GetZ() const { return _mm_cvtss_f32(_SF_SWIZZLE(Packed, 2, 2, 2, 2)); }
		float GetW() const { return _mm_cvtss_f32(_SF_SWIZZLE(Packed, 3, 3, 3, 3)); }

		float & operator[](int i) { return Elements[i]; }
		const float& operator[](int i) const { return Elements[i]; }

		float* GetValues() { return Elements; }
		const float* GetValues() const { return Elements; }


		// Data definitions
		union {
			__m128 Packed;
			struct {
				float x, y, z, w;
			};
			float Elements[4];
		};

	}; //struct Vector4SSE


	// Determinant 2X2
	//| v.x v.z |
	//| v.y v.w |
	inline float Determinent2x2SSE(__m128 v)
	{
		__m128 vwwyy = _SF_SWIZZLE(v, 1,1,3,3);
		__m128 v1 = _mm_mul_ps(v, vwwyy); // (x*w, y*w, z*y, w*y)
		__m128 v2 = _SF_SWIZZLE_2323(v1); // (z*y, w*y, z*y, w*y)
		return _mm_cvtss_f32(_mm_sub_ps(v1, v2));
		//return v.x * v.w - v.y * v.z;
	}




	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//
	//	SSE Vector4
	//

	//
	//	Column major 
	// right hand right vertex notation
	//
	struct SF_DECLARE_ALIGN_DOUBLE Matrix4SSE
	{
		static const Matrix4SSE& Identity() { static const Matrix4SSE Value(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1); return Value; }

		Matrix4SSE() {}

		Matrix4SSE(const float * array)
		{
			memcpy(Elements, array, sizeof(float) * 16);
		}

		Matrix4SSE(const Matrix4SSE & M) { memcpy(Elements, M.Elements, sizeof(float) * 16); }

		Matrix4SSE(const float& f0, const float& f1, const float& f2, const float& f3,
			const float& f4, const float& f5, const float& f6, const float& f7,
			const float& f8, const float& f9, const float& f10, const float& f11,
			const float& f12, const float& f13, const float& f14, const float& f15)
		{
			Packed[0] = _mm_set_ps(f12, f8, f4, f0);
			Packed[1] = _mm_set_ps(f13, f9, f5, f1);
			Packed[2] = _mm_set_ps(f14, f10, f6, f2);
			Packed[3] = _mm_set_ps(f15, f11, f7, f3);
		}

		Matrix4SSE(const __m128& c0, const __m128& c1, const __m128& c2, const __m128& c3)
		{
			Packed[0] = c0;
			Packed[1] = c1;
			Packed[2] = c2;
			Packed[3] = c3;
		}

		const Vector4SSE GetRow(const int i) const;
		const Vector4SSE GetColumn(const int i) const { return Vector4SSE(Packed[i]); }

		const Vector4SSE operator[](const int& i) const { return GetRow(i); }

		const float& operator()(const int& i, const int& j) const { return Elements[j * 4 + i]; }
		float& operator()(const int& i, const int& j) { return  Elements[j * 4 + i]; }

		Matrix4SSE & SetColumn(int i, const Vector4SSE & v)
		{
			Packed[i] = v.Packed;
			//Elements[i * 4] = v.x;
			//Elements[i * 4 + 1] = v.y;
			//Elements[i * 4 + 2] = v.z;
			//Elements[i * 4 + 3] = v.w;
			return *this;
		}


		Matrix4SSE & SetRow(int i, const Vector4SSE & v)
		{
			Elements[i] = v.x;
			Elements[i + 4] = v.y;
			Elements[i + 8] = v.z;
			Elements[i + 12] = v.w;
			return *this;
		}

		Matrix4SSE& InitIdentity();

		Matrix4SSE GetTranspose();
		Matrix4SSE& Transpose();


		Matrix4SSE GetRotationMatrix() const;
		QuaternionSSE ToQuaternion(bool bIgnoreScale = false) const;

		// From quaternion matrix
		Matrix4SSE & InitRotationMatrix(const QuaternionSSE & q);

		// Axis angle w element is angle
		Matrix4SSE & InitRotationMatrix(const Vector4SSE & v);

		// Up and dir vector
		Matrix4SSE & InitRotationMatrix(const Vector4SSE & u, const Vector4SSE & v);

		// Copy rotation part from other matrix
		Matrix4SSE & InitRotationMatrix(const Matrix4SSE& m);

		// initialize scale matrix
		Matrix4SSE & InitScaleMatrix(const Vector4SSE& s);
		Matrix4SSE & InitScaleMatrix(const float& s);


		Matrix4SSE & SetTranslation(const Vector4SSE & t);
		Vector4SSE GetTranslation() const;
		Matrix4SSE & InitTranslationMatrix(const Vector4SSE & t);

		Matrix4SSE  operator*(const float & scala) const;
		Matrix4SSE & operator*=(const float & scala);
		Matrix4SSE  operator/(const float & scala) const;
		Matrix4SSE & operator/=(const float & scala);

		Matrix4SSE operator*(const Matrix4SSE& m) const;
		Matrix4SSE & operator*=(const Matrix4SSE & m);

		Matrix4SSE  operator+(const Matrix4SSE & M) const;
		Matrix4SSE & operator+=(const Matrix4SSE & M);

		Matrix4SSE  operator-(const Matrix4SSE & M) const;
		Matrix4SSE & operator-=(const Matrix4SSE & M);


		Vector4SSE operator*(const Vector4SSE& v) const;
		__m128 operator*(const __m128& v) const;


		Matrix4SSE & operator=(const Matrix4SSE & M);


		Matrix4SSE & Translate(float *t)
		{
			*this *= Matrix4SSE().InitTranslationMatrix(*(Vector4SSE*)t);
			return *this;
		}

		Matrix4SSE & Scale(float s)
		{
			*this *= Matrix4SSE().InitScaleMatrix(s);
			return *this;
		}

		Matrix4SSE & Rotate(QuaternionSSE &q)
		{
			*this *= Matrix4SSE().InitRotationMatrix(q);
			return *this;
		}

		// Transform position vector
		// This operation same to matrix-vector multiplication, but it will ignore w component
		Vector4SSE TransformVector(const Vector4SSE& v);


		// Inverse matrix
		Matrix4SSE GetInverse();

		// Inverse transform matrix, This method uses pretty assumption of TRS style transformation.
		// It doesn't work if the matrix has complicated scale, so use GetInverse() in that case
		// Moreover, If you do inverse twice, then the result will not be the original because once you inverse, the scale part get complicated
		Matrix4SSE GetInverseTransform();

		// Inverse transform matrix ignoring scale
		Matrix4SSE GetInverseTransformNoScale();

		// Normalize matrix to a valid transform matrix
		Matrix4SSE& NormalizeTransform();


		Matrix4SSE operator - () const
		{
			Matrix4SSE N;
			for (int i = 0; i < 16; ++i)
				N.Elements[i] = -Elements[i];
			return N;
		}


		// Data elements
		union {
			__m128 Packed[4]; // Column bases
			//Vector4SSE Vec[4];
			struct {
				__m128 a0010a2030; // c0
				__m128 a0111a2131; // c1
				__m128 a0212a2232; // c2
				__m128 a0313a2333; // c3
			};
			struct {
				float a00, a10, a20, a30;
				float a01, a11, a21, a31;
				float a02, a12, a22, a32;
				float a03, a13, a23, a33;
			};
			float Elements[16];
		};

	};//struct Matrix4SSE



	////////////////////////////////////////////////////////////////////
	//
	// QuaternionSSE
	//

	struct SF_DECLARE_ALIGN_DOUBLE QuaternionSSE
	{
	public:
		static const QuaternionSSE& Identity() { static const QuaternionSSE Value(0, 0, 0, 1); return Value; }

	public:
		QuaternionSSE() {}
		QuaternionSSE(const float *q)
			: Packed(_mm_set_ps(q[3], q[2], q[1], q[0]))
		{
		}

		QuaternionSSE(float x, float y, float z, float w)
			: Packed(_mm_set_ps(w, z, y, x))
		{
		}

		QuaternionSSE(__m128 src) : Packed(src) {}

		QuaternionSSE(const Vector4SSE& axisAngle);

		QuaternionSSE(const QuaternionSSE& src)
			: Packed(src.Packed)
		{
		}

		QuaternionSSE(const Matrix4SSE& rot);


		QuaternionSSE& operator=(const QuaternionSSE& q);
		QuaternionSSE& operator=(const Matrix4SSE& mat);

		QuaternionSSE operator-() { return QuaternionSSE(-x, -y, -z, -w); }

		QuaternionSSE operator + (const QuaternionSSE& op) { return QuaternionSSE(x + op.x, y + op.y, z + op.z, w + op.w); }

		QuaternionSSE operator * (const QuaternionSSE& q);
		QuaternionSSE& operator *= (const QuaternionSSE& q);

        // Compare two quaternion
        bool Comapre(const QuaternionSSE& q, float testEpsilon = std::numeric_limits<float>::epsilon()) const;

		// scala operation
		QuaternionSSE operator-(float scala) const;
		QuaternionSSE operator + (float scala) const;
		QuaternionSSE operator * (float scala) const;
		QuaternionSSE operator / (float scala) const;

		//friend QuaternionSSE operator*(const QuaternionSSE& q1, const QuaternionSSE& q2);


		QuaternionSSE GetInverse() const;
		QuaternionSSE GetConjugate() const;
		void Normalize();


		// Dot product
		float Dot(const QuaternionSSE& op) const;


		// spherical interpolation between this and q2
		QuaternionSSE Slerp(float s, const QuaternionSSE & q2);



		void FromAxisAngle(const Vector4SSE& axis);
		void FromMatrix(const Matrix4SSE& mat);

		Vector4SSE RotateVector(const Vector4SSE& v);

		// Dual Quaternions
		static void MakeDualQuaternion(const QuaternionSSE& q0, const Vector4SSE& t, QuaternionSSE dq[2]);
		static void DecomposeDualQuaternionNoScale(const QuaternionSSE dq[2], QuaternionSSE& q0, Vector4SSE& t);
		static void DecomposeDualQuaternion(const QuaternionSSE dq[2], QuaternionSSE& q0, Vector4SSE& t);


		float& operator[](int i) { return Elements[i]; }
		const float& operator[](int i) const { return Elements[i]; }


		union {
			__m128  Packed;
			struct {
				float x, y, z, w;
			};
			float Elements[4];
		};

	};




}


#include "Math/SF3DMathSSE.inl"
#include "Math/SF3DMath_vectorSSE.inl"
#include "Math/SF3DMath_matrixSSE.inl"
#include "Math/SF3DMath_quaternionSSE.inl"

#endif

