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

	typedef Matrix3Soft<float> Matrix3;

#if defined(SF_SIMD_SSE)
	typedef Vector4SSE Vector4;
	typedef Matrix4SSE Matrix4;
	typedef QuaternionSSE Quaternion;
#else
	typedef Vector4Soft<float> Vector4;
	typedef Matrix4Soft<float> Matrix4;
	typedef QuaternionSoft<float> Quaternion;

	// TODO: Preventing compile errors until I have solution
	using Vector4SSE = Vector4Soft<float>;
	using Matrix4SSE = Matrix4Soft<float>;
	using QuaternionSSE = QuaternionSoft<float>;

#endif

	typedef Vector3Soft<float> Vector3;
	typedef Vector2Soft<float> Vector2;

	typedef Vector3Soft<int> Vector3i;
	typedef Vector2Soft<int> Vector2i;

	/////////////////////////////////////////////////////////////////
	// Row first matrix. 
	struct SF_DECLARE_ALIGN_DOUBLE Matrix2
	{
		using T = float;

		Matrix2() : Vec() {}
		Matrix2(int one) : Vec() { InitIdentity(); }
		Matrix2(const T& f0, const T& f1, const T& f2, const T& f3)
			: Vec(f0, f1, f2, f3)
			//, a00(f0), a10(f1), a01(f2), a11(f3)
		{}
		Matrix2(const T* array) : Vec(array) {}
		Matrix2(const Matrix2& M) : Vec(M.Vec) {}

		Matrix2& operator = (const Matrix2& src) { memcpy(Elements, src.Elements, sizeof(T) * 4); return *this; }

		Matrix2& InitIdentity() {
			a00 = 1; a10 = 0;
			a01 = 0; a11 = 1;
			return *this;
		}

		const Vector2Soft<T> Col(const int i) const
		{
			return Vector2Soft<T>(Elements[i], Elements[i + 2]);
		}

		const Vector2Soft<T> Row(const int i) const
		{
			return Vector3Soft<T>(&Elements[i * 2]);
		}

		const Vector2Soft<T> operator[](int i) const
		{
			return Vector3Soft<T>(&Elements[i * 2]);
		}

		const T& operator()(const int& i, const int& j) const
		{
			return Elements[j + i * 2];
		}
		T& operator()(const int& i, const int& j)
		{
			return Elements[j + i * 2];
		}

		Matrix2  operator*(const T& scala) const
		{
			return Matrix2(
				Elements[0] * scala,
				Elements[1] * scala,
				Elements[2] * scala,
				Elements[3] * scala
			);
		}
		Matrix2& operator*=(const T& scala)
		{
			Elements[0] *= scala;
			Elements[1] *= scala;
			Elements[2] *= scala;
			Elements[3] *= scala;
			return *this;
		}

		Matrix2  operator*(const Matrix2& M) const
		{
			return Matrix2(
				a00 * M.a00 + a01 * M.a10,
				a00 * M.a01 + a01 * M.a11,

				a10 * M.a00 + a11 * M.a10,
				a10 * M.a01 + a11 * M.a11
			);
		}
		Matrix2& operator*=(const Matrix2& M)
		{
			Matrix2 temp = *this;
			a00 = temp.a00 * M.a00 + temp.a01 * M.a10;
			a01 = temp.a00 * M.a01 + temp.a01 * M.a11;

			a10 = temp.a10 * M.a00 + temp.a11 * M.a10;
			a10 = temp.a10 * M.a01 + temp.a11 * M.a11;

			return *this;
		}


		Matrix2  operator+(const Matrix2& M) const
		{
			return Matrix2(
				Elements[0] + M.Elements[0],
				Elements[1] + M.Elements[1],
				Elements[2] + M.Elements[2],
				Elements[3] + M.Elements[3]
			);
		}
		Matrix2& operator+=(const Matrix2& M)
		{
			Elements[0] += M.Elements[0];
			Elements[1] += M.Elements[1];
			Elements[2] += M.Elements[2];
			Elements[3] += M.Elements[3];
			return *this;
		}


		Matrix2  operator-(const Matrix2& M) const
		{
			return Matrix2(
				Elements[0] - M.Elements[0],
				Elements[1] - M.Elements[1],
				Elements[2] - M.Elements[2],
				Elements[3] - M.Elements[3]
			);
		}

		Matrix2& operator-=(const Matrix2& M)
		{
			Elements[0] -= M.Elements[0];
			Elements[1] -= M.Elements[1];
			Elements[2] -= M.Elements[2];
			Elements[3] -= M.Elements[3];
			return *this;
		}


		Vector2Soft<T> operator*(const Vector2Soft<T>& v) const
		{
			return Vector2Soft<T>(
				a00 * v.x + a01 * v.y,
				a10 * v.x + a11 * v.y
				);
		}


		Matrix2& SetRow(int i, const Vector2Soft<T>& v)
		{
			Elements[i] = v.x;
			Elements[i + 2] = v.y;
			return *this;
		}
		Matrix2& SetColumn(int i, const Vector2Soft<T>& v)
		{
			Elements[i * 2] = v.x;
			Elements[i * 2 + 1] = v.y;
			return *this;
		}

		Matrix2 operator -() const
		{
			return Matrix2(
				-Elements[0],
				-Elements[1],
				-Elements[2],
				-Elements[3]
			);
		}

		// Matrix norms...
		// Compute || M ||
		//                1
		T GetNorm() const
		{
			T sum, max = T(0);
			sum = (T)(fabs(a00) + fabs(a10));
			if (max < sum)
				max = sum;
			sum = (T)(fabs(a01) + fabs(a11));
			if (max < sum)
				max = sum;
			return max;
		}


		// Compute || M ||
		//                +inf
		T GetNormInf() const
		{
			T sum, max = T(0);
			sum = (T)(fabs(a00) + fabs(a01));
			if (max < sum)
				max = sum;
			sum = (T)(fabs(a10) + fabs(a11));
			if (max < sum)
				max = sum;
			return max;
		}

		Matrix2 GetInvert() const
		{
			Matrix2 B = *this;
			B.Invert();
			return B;
		}
		Matrix2& Invert()
		{
			Matrix2 B;

			B.a00 = a11;
			B.a10 = -a10;
			B.a01 = -a01;
			B.a11 = a00;

			T det = Determinent2x2(a00, a01, a10, a11);

			T invDet = T(1) / det;

			a00 = B.a00 * invDet; a01 = B.a01 * invDet;
			a10 = B.a10 * invDet; a11 = B.a11 * invDet;

			return *this;
		}


		Matrix2 GetTranspose() const
		{
			return Matrix2(a00, a10, a01, a11);
		}
		Matrix2& Transpose()
		{
			std::swap(a01, a10);
			return *this;
		}

		T GetDeterminent() const
		{
#if defined(SF_SIMD_SSE42)
			return Determinent2x2SSE(Vec.Packed);
#else
			return Determinent2x2(a00, a01, a10, a11);
#endif
		}

		T* GetValues() { return Elements; }
		const T* GetValues() const { return Elements; }


		// Data elements
		union {
			// NOTE: Same row placed at column direction
			Vector4 Vec; // In vector form
			struct {
				T a00, a10;
				T a01, a11;
			};
			T Elements[4];
		};

	};

    template<class VectorType>
    struct SF_DECLARE_ALIGN_DOUBLE Box
    {
        VectorType Min;
        VectorType Max;

        Box() {}
        Box(const Box& src)
            : Min(src.Min)
            , Max(src.Max)
        {}
        Box(const VectorType& vMin, const VectorType& vMax)
            : Min(vMin)
            , Max(vMax)
        {}

        SF_FORCEINLINE VectorType GetMid() const { return (Min + Max) / 2; }
        SF_FORCEINLINE bool IsInside(const VectorType& testPos) const
        {
            return Min <= testPos && testPos <= Max;
        }
    };


    using Box4 = Box<Vector4>;
    using Box2i = Box<Vector2i>;
    using Box3i = Box<Vector3i>;
}



