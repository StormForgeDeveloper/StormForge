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
#include "Math/SFMathUtil.h"
#include <math.h>

namespace SF {


	template<class T> struct Vector2Soft;
	template<class T> struct Vector3Soft;
	template<class T> struct Vector4Soft;
	template<class T> struct Matrix3Soft;
	template<class T> struct Matrix4Soft;
	template<class T> struct QuaternionSoft;

	template<class T>
	T Determinent2x2(T a1, T a2, T b1, T b2);


	template<class T>
	struct Vector2Soft
	{
		Vector2Soft() { }
		constexpr Vector2Soft(T x) : x(T(x)), y(T(x)) { }
		template<typename T0, typename T1>
		constexpr Vector2Soft(T0 x, T1 y) : x(T(x)), y(T(y)) { }
		Vector2Soft(const T* xy) : x(xy[0]), y(xy[1]) { }
		constexpr Vector2Soft(const Vector2Soft& u) : x(u.x), y(u.y) { }
		constexpr Vector2Soft(const Vector3Soft<T>&);
		constexpr Vector2Soft(const Vector4Soft<T>&);

		bool operator==(const Vector2Soft & u) const;
		bool operator!=(const Vector2Soft & u) const;

		Vector2Soft<T> operator*(const Vector2Soft & op) const;
		Vector2Soft<T> operator/(const Vector2Soft & op) const;
		Vector2Soft<T> operator-(const Vector2Soft & op) const;
		Vector2Soft<T> operator+(const Vector2Soft & op) const;

		Vector2Soft<T> operator*(const T& scala)
		{
			return Vector2Soft<T>(x* scala, y* scala);
		}
		Vector2Soft<T> operator/(const T& scala)
		{
			return Vector2Soft<T>(x / scala, y / scala);
		}

		Vector2Soft<T>& operator*=(const T & scala);
		Vector2Soft<T>& operator/=(const T & scala);
		Vector2Soft<T>& operator-=(const Vector2Soft & u);
		Vector2Soft<T>& operator+=(const Vector2Soft & u);

		T & operator[](int i);

		const T& operator[](int i) const;

		T SquareLength() const { return x * x + y * y; }
		T Length() const { return (T)sqrt((double)SquareLength()); }

		// Returns original length
		T Normalize();

		Vector2Soft<T> Abs() const;

		T* get_value() { return Elements; }
		const T* get_value() const { return Elements; }

		Vector2Soft<T> operator - () const { return Vector2Soft<T>(-x, -y); }

		T Dot(const Vector2Soft<T>& op) const { return x * op.x + y * op.y; }


		union {
			struct {
				T x, y;          // standard names for components
			};
			T Elements[2];     // array access
		};

	};



	template<class T>
	struct Vector3Soft
	{
		Vector3Soft() { }
		Vector3Soft(T x) : x(T(x)), y(T(x)), z(T(x)) { }
		template<typename T0, typename T1, typename T2>
		Vector3Soft(T0 x, T1 y, T2 z) : x(T(x)), y(T(y)), z(T(z)) { }
		Vector3Soft(const T* xyz) : x(xyz[0]), y(xyz[1]), z(xyz[2]) { }
		Vector3Soft(const Vector2Soft<T>& u) : x(u.x), y(u.y), z(T(1)) { }
		Vector3Soft(const Vector2Soft<T>& u, T v) : x(u.x), y(u.y), z(v) { }
		Vector3Soft(const Vector3Soft<T>& u) : x(u.x), y(u.y), z(u.z) { }
		Vector3Soft(const Vector4Soft<T>&);

		bool operator==(const Vector3Soft<T> & u) const { return (u.x == x && u.y == y && u.z == z) ? true : false; }
		bool operator!=(const Vector3Soft<T>& rhs) const { return !(*this == rhs); }

		Vector3Soft<T>  operator*(const Matrix3Soft<T> & M) const;
		Vector3Soft<T> & operator*=(const Matrix3Soft<T> & M);
		Vector3Soft<T>  operator*(const Matrix4Soft<T> & M) const;
		Vector3Soft<T> & operator*=(const Matrix4Soft<T> & M);

		Vector3Soft<T> & operator/=(const Vector3Soft<T> & d);
		Vector3Soft<T> & operator*=(const Vector3Soft<T> & v);

		Vector3Soft<T> operator* (const T & scala) const;
		Vector3Soft<T> & operator*=(const T & scala);

		Vector3Soft<T>  operator/ (const T & scala) const;
		Vector3Soft<T> & operator/=(const T & scala);

		Vector3Soft<T> operator - () const;

		Vector3Soft<T> operator-(const Vector3Soft<T> & u) const;
		Vector3Soft<T> operator+(const Vector3Soft<T> & u) const;

		Vector3Soft<T> & operator-=(const Vector3Soft<T> & u);
		Vector3Soft<T> & operator+=(const Vector3Soft<T> & u);

		Vector3Soft<T> & RotateBy(const QuaternionSoft<T>& q);

		// Returns original length
		T Normalize();

		// Make orthogonal to vector v
		void Orthogonalize(const Vector3Soft<T>& v);
		void Orthonormalize(const Vector3Soft<T>& v)
		{
			Orthogonalize(v);
			Normalize();
		}

		T SquareLength() const { return x * x + y * y + z * z; }
		T Length() const;

		T & operator[](int i) { return Elements[i]; }
		const T& operator[](int i) const { return Elements[i]; }

		Vector3Soft<T> Abs() const;

		T Dot(const Vector3Soft<T>& op) const { return x * op.x + y * op.y + z * op.z; }
		T Dot(const Vector4Soft<T>& op) const { return x * op.x + y * op.y + z * op.z; }

		Vector3Soft<T> Cross(const Vector3Soft<T>& op) const;
		Vector4Soft<T> Cross(const Vector4Soft<T>& op) const;


		Vector3Soft<T>& MAdd(const T& scala);


		T* GetValues() { return Elements; }
		const T* GetValues() const { return Elements; }


		// Data definitions
		union {
			struct {
				T x, y, z;
			};
			T Elements[3];
		};
	};



	template<class T>
	struct Vector4Soft
	{
		static const Vector4Soft<T>& Zero() { static const Vector4Soft<T> Value(0, 0, 0, 0); return Value; }
		static const Vector4Soft<T>& One() { static const Vector4Soft<T> Value(1, 1, 1, 1); return Value; }


		Vector4Soft() { }
		Vector4Soft(T x) : x(T(x)), y(T(x)), z(T(x)), w(T(x)) { }
		Vector4Soft(T x, T y, T z, T w = 0) : x(T(x)), y(T(y)), z(T(z)), w(T(w)) { }
		Vector4Soft(const T* xyzw) : x(xyzw[0]), y(xyzw[1]), z(xyzw[2]), w(xyzw[3]) { }
		Vector4Soft(const Vector4Soft<T>& u) : x(u.x), y(u.y), z(u.z), w(u.w) { }

		bool operator==(const Vector4Soft<T> & u) const { return (u.x == x && u.y == y && u.z == z && u.w == w) ? true : false; }
		bool operator!=(const Vector4Soft<T>& rhs) const { return !(*this == rhs); }


		Vector4Soft<T> operator*(const Matrix3Soft<T> & M) const;
		Vector4Soft<T> & operator*=(const Matrix3Soft<T> & M);
		Vector4Soft<T> operator*(const Matrix4Soft<T> & M) const;
		Vector4Soft<T> & operator*=(const Matrix4Soft<T> & M);

		Vector4Soft<T>  operator/(const T & scala) const;
		Vector4Soft<T>  operator*(const T & scala) const;
		Vector4Soft<T> & operator/=(const T & scala);
		Vector4Soft<T> & operator*=(const T & scala);

		Vector4Soft<T> & operator-=(const Vector4Soft<T> & u);
		Vector4Soft<T> & operator+=(const Vector4Soft<T> & u);

		Vector4Soft<T> operator-(const Vector4Soft<T> & u) const;
		Vector4Soft<T> operator+(const Vector4Soft<T> & u) const;
		Vector4Soft<T> operator*(const Vector4Soft<T> & u) const;
		Vector4Soft<T> operator/(const Vector4Soft<T> & u) const;

		Vector4Soft<T> operator - () const { return Vector4Soft<T>(-x, -y, -z, -w); }

		T SquareLength4() const { return T(x * x + y * y + z * z + w * w); }
		T Length4() const { return (T)sqrt(SquareLength4()); }

		T SquareLength3() const { return T(x * x + y * y + z * z); }
		T Length3() const { return (T)sqrt(SquareLength3()); }

		// returns orthogonal length
		void Normalize4();
		void Normalize3();
		T Normalize3Hi();

		Vector4Soft<T>& Scale3(T scale)
		{
			x *= scale;
			y *= scale;
			z *= scale;
			return *this;
		}

		Vector4Soft<T> Abs() const;

		T Dot3(const Vector3Soft<T>& op) const { return (T)(x * op.x + y * op.y + z * op.z); }
		T Dot4(const Vector4Soft<T>& op) const { return (T)(x * op.x + y * op.y + z * op.z + w * op.w); }

		Vector4Soft<T> Cross(const Vector3Soft<T>& op) const { return Vector4Soft<T>(y * op.z - z * op.y, z * op.x - x * op.z, x * op.y - y * op.x, 1); }
		Vector4Soft<T> Cross(const Vector4Soft<T>& op) const { return Vector4Soft<T>(y * op.z - z * op.y, z * op.x - x * op.z, x * op.y - y * op.x, 1); }
		Vector4Soft<T> CrossRaw(const Vector4Soft<T>& op) const { return Vector4Soft<T>(y * op.z - z * op.y, z * op.x - x * op.z, x * op.y - y * op.x, 1); }


		Vector4Soft<T>& SwapLHInline()
		{
			std::swap(x, z);
			std::swap(y, w);
			return *this;
		}

		Vector4Soft<T>& MAdd(const T & scala);

		float GetX() const { return x; }
		float GetY() const { return y; }
		float GetZ() const { return z; }
		float GetW() const { return w; }



		T & operator[](int i) { return Elements[i]; }
		const T& operator[](int i) const { return Elements[i]; }

		T* GetValues() { return Elements; }
		const T* GetValues() const { return Elements; }


		// Data definitions
		union {
			struct {
				T x, y, z, w;
			};
			T Elements[4];
		};

	}; //struct Vector4Soft





	/////////////////////////////////////////////////////////////////
	// Row first matrix
	template<class T>
	struct Matrix3Soft
	{
		Matrix3Soft() {}
		Matrix3Soft(int one) { InitIdentity(); }
		Matrix3Soft(const T& f0, const T& f1, const T& f2,
			const T& f3, const T& f4, const T& f5,
			const T& f6, const T& f7, const T& f8
			);
		Matrix3Soft(const T * array) { memcpy(Elements, array, sizeof(T) * 9); }
		Matrix3Soft(const Matrix3Soft<T> & M) { memcpy(Elements, M.Elements, sizeof(T) * 9); }


		Matrix3Soft<T> & InitIdentity();

		const Vector3Soft<T> Col(const int i) const;
		const Vector3Soft<T> Row(const int i) const;

		const Vector3Soft<T> operator[](int i) const;

		const T& operator()(const int& i, const int& j) const;
		T& operator()(const int& i, const int& j);

		Matrix3Soft<T>  operator*(const T & scala) const;
		Matrix3Soft<T> & operator*=(const T & scala);

		Matrix3Soft<T>  operator*(const Matrix3Soft<T> & M) const;
		Matrix3Soft<T> & operator*=(const Matrix3Soft<T> & M);


		Matrix3Soft<T>  operator+(const Matrix3Soft<T> & M) const;
		Matrix3Soft<T> & operator+=(const Matrix3Soft<T> & M);

		Matrix3Soft<T>  operator-(const Matrix3Soft<T> & M) const;
		Matrix3Soft<T> & operator-=(const Matrix3Soft<T> & M);


		Vector3Soft<T> operator*(const Vector3Soft<T>& v) const;

		Vector4Soft<T> operator*(const Vector4Soft<T>& v) const;


		Matrix3Soft<T> & SetRow(int i, const Vector3Soft<T> & v);
		Matrix3Soft<T> & SetColumn(int i, const Vector3Soft<T> & v);

		Matrix3Soft<T> & SetRotation(const T & theta, const Vector3Soft<T> & v);
		Matrix3Soft<T> & SetRotation(const Vector3Soft<T> & u, const Vector3Soft<T> & v);
		Matrix3Soft<T> & SetRotation(const QuaternionSoft<T> & q);

		Matrix3Soft<T> operator - () const;

		// Matrix norms...
		// Compute || M ||
		//                1
		T GetNorm() const;

		// Compute || M ||
		//                +inf
		T GetNormInf() const;

		Matrix3Soft<T> GetInvert() const;
		Matrix3Soft<T>& Invert();
		Matrix3Soft<T> GetInvertNoScale();

		Matrix3Soft<T> GetTranspose() const;
		Matrix3Soft<T>& Transpose();

		T GetDeterminent() const;

		T* GetValues() { return Elements; }
		const T* GetValues() const { return Elements; }



		// Data elements
		union {
			// NOTE: Same row placed at column direction
			struct {
				T a00, a10, a20;
				T a01, a11, a21;
				T a02, a12, a22;
			};
			T Elements[9];
		};

	};


	//
	// newVtx = M * Mt * Ms * vtx is
	// M.identity()
	// M.translate(t)
	// M.scale(s)
	// vtx = M * vtx;
	//
	// right hand right vertex notation
	//
	template<class T>
	struct Matrix4Soft
	{
		static const Matrix4Soft<T>& Identity() { static const Matrix4Soft<T> Value(1,0,0,0, 0,1,0,0, 0,0,1,0, 0, 0, 0, 1); return Value; }


		Matrix4Soft() {}

		Matrix4Soft(int one) { InitIdentity(); }

		Matrix4Soft(const T * array)
		{
			memcpy(Elements, array, sizeof(T) * 16);
		}

		Matrix4Soft(const Matrix3Soft<T> & M)
		{
			memcpy(Elements, M.Elements, sizeof(T) * 3);
			Elements[3] = 0.0;
			memcpy(Elements + 4, M.Elements + 3, sizeof(T) * 3);
			Elements[7] = 0.0;
			memcpy(Elements + 8, M.Elements + 6, sizeof(T) * 3);
			Elements[11] = 0.0f;

			Elements[12] = 0.0f;
			Elements[13] = 0.0f;
			Elements[14] = 0.0f;
			Elements[15] = 1.0f;
		}

		Matrix4Soft(const Matrix4Soft<T> & M)
		{
			memcpy(Elements, M.Elements, sizeof(T) * 16);
		}

		Matrix4Soft(const T& f0, const T& f1, const T& f2, const T& f3,
			const T& f4, const T& f5, const T& f6, const T& f7,
			const T& f8, const T& f9, const T& f10, const T& f11,
			const T& f12, const T& f13, const T& f14, const T& f15)
		{
			a00 = (f0);  a01 = (f1);  a02 = (f2);  a03 = (f3);
			a10 = (f4);  a11 = (f5);  a12 = (f6);  a13 = (f7);
			a20 = (f8);  a21 = (f9);  a22 = (f10); a23 = (f11);
			a30 = (f12); a31 = (f13); a32 = (f14); a33 = (f15);
		}

		const Vector4Soft<T> GetColumn(const int i) const { return Vector4Soft<T>(&Elements[i * 4]); }
		const Vector4Soft<T> GetRow(const int i) const { return Vector4Soft<T>(Elements[i], Elements[i + 4], Elements[i + 8], Elements[i + 12]); }

		const Vector4Soft<T> operator[](const int& i) const { return GetRow(i); }

		const T& operator()(const int& i, const int& j) const { return Elements[j * 4 + i]; }
		T& operator()(const int& i, const int& j) { return  Elements[j * 4 + i]; }

		Matrix4Soft<T> & SetColumn(int i, const Vector4Soft<T> & v)
		{
			Elements[i * 4] = v.x;
			Elements[i * 4 + 1] = v.y;
			Elements[i * 4 + 2] = v.z;
			Elements[i * 4 + 3] = v.w;
			return *this;
		}

		Matrix4Soft<T> & SetRow(int i, const Vector4Soft<T> & v)
		{
			Elements[i] = v.x;
			Elements[i + 4] = v.y;
			Elements[i + 8] = v.z;
			Elements[i + 12] = v.w;
			return *this;
		}

		Matrix4Soft<T>& InitIdentity();

		Matrix4Soft<T> GetTranspose();
		Matrix4Soft<T>& Transpose();

		// Get rotation part of the matrix
		Matrix3Soft<T> GetRotationMatrix() const;

		// Get quaternion
		QuaternionSoft<T> ToQuaternion() const;


		// From quaternion matrix
		Matrix4Soft<T> & InitRotationMatrix(const QuaternionSoft<T> & q);

		// Axis angle w element is angle
		Matrix4Soft<T> & InitRotationMatrix(const Vector4Soft<T> & v);

		// Up and dir vector
		Matrix4Soft<T> & InitRotationMatrix(const Vector4Soft<T>& u, const Vector4Soft<T>& v);

		// copy rotation part from other matrix
		Matrix4Soft<T> & InitRotationMatrix(const Matrix3Soft<T>& M);
		Matrix4Soft<T> & InitRotationMatrix(const Matrix4Soft<T>& M);

		// scale matrix
		Matrix4Soft<T> & InitScaleMatrix(const Vector3Soft<T>& s);
		Matrix4Soft<T> & InitScaleMatrix(const T& s);

		// Translation matrix
		Matrix4Soft<T> & SetTranslation(const Vector3Soft<T> & t);
		Vector3Soft<T> GetTranslation() const;
		Matrix4Soft<T> & InitTranslationMatrix(const Vector3Soft<T> & t);


		Matrix4Soft<T> & Translate(Vector3Soft<T> t)
		{
			*this *= Matrix4Soft<T>().InitTranslationMatrix(t);
			return *this;
		}

		Matrix4Soft<T> & Translate(T *t)
		{
			*this *= Matrix4Soft<T>().InitTranslationMatrix(*(Vector3Soft<T>*)t);
			return *this;
		}

		Matrix4Soft<T> & Scale(Vector3Soft<T> s)
		{
			*this *= Matrix4Soft<T>().InitScaleMatrix(s);
			return *this;
		}

		Matrix4Soft<T> & Scale(T s)
		{
			*this *= Matrix4Soft<T>().InitScaleMatrix(s);
			return *this;
		}

		Matrix4Soft<T> & Rotate(const T & theta, const Vector3Soft<T> & v)
		{
			*this *= Matrix4Soft<T>().InitRotationMatrix(theta, Vector4Soft<T>(v.x, v.y, v.z));
			return *this;
		}

		Matrix4Soft<T> & Rotate(QuaternionSoft<T> &q)
		{
			*this *= Matrix4Soft<T>().InitRotationMatrix(q);
			return *this;
		}

		// Transform position vector
		// This operation same to matrix-vector multiplication, but it will ignore w component
		Vector4Soft<T> TransformVector(const Vector4Soft<T>& v);


		// Inverse matrix
		Matrix4Soft<T> GetInverse();
		// Inverse transform matrix, This method uses pretty assumption of TRS style transformation.
		// It doesn't work if the matrix has complicated scale, so use GetInverse() in that case
		// Moreover, If you do inverse twice, then the result will not be the original because once you inverse, the scale part get complicated
		Matrix4Soft<T> GetInverseTransform();
		// Inverse transform matrix ignoring scale
		Matrix4Soft<T> GetInverseTransformNoScale();

		// Normalize matrix to a valid transform matrix
		Matrix4Soft<T>& NormalizeTransform();

		Matrix4Soft<T> operator - () const
		{
			Matrix4Soft<T> N;
			for (int i = 0; i < 16; ++i)
				N.Elements[i] = -Elements[i];
			return N;
		}


		// operator
		Matrix4Soft<T>  operator*(const T & scala) const;
		Matrix4Soft<T> & operator*=(const T & scala);

		Matrix4Soft<T>  operator/(const T & scala) const;
		Matrix4Soft<T> & operator/=(const T & scala);

		Matrix4Soft<T> operator*(const Matrix4Soft<T>& m) const;
		Matrix4Soft<T> & operator*=(const Matrix4Soft<T> & m);

		Matrix4Soft<T>  operator+(const Matrix4Soft<T> & M) const;
		Matrix4Soft<T> & operator+=(const Matrix4Soft<T> & M);

		Matrix4Soft<T>  operator-(const Matrix4Soft<T> & M) const;
		Matrix4Soft<T> & operator-=(const Matrix4Soft<T> & M);

		Vector3Soft<T> operator*(const Vector3Soft<T>& v) const;

		Vector4Soft<T> operator*(const Vector4Soft<T>& v) const;


		T* get_value() { return Elements; }
		const T* get_value() const { return Elements; }


		// Data elements, 
		union {
			// NOTE: Same row placed at column direction
			Vector4Soft<T> Vec[4];
			struct {
				float a00, a10, a20, a30;
				float a01, a11, a21, a31;
				float a02, a12, a22, a32;
				float a03, a13, a23, a33;
			};
			T Elements[16];
		};

	};//struct Matrix4Soft


	////////////////////////////////////////////////////////////////////
	//
	// QuaternionSoft<T>ernion
	//
	template<class T>
	struct QuaternionSoft
	{
	public:

		static const QuaternionSoft<T>& Identity() { static const QuaternionSoft<T> Value(0, 0, 0, 1); return Value; }

	public:
		QuaternionSoft() {}
		QuaternionSoft(const T *q)
		{
			x = q[0];
			y = q[1];
			z = q[2];
			w = q[3];
		}

		template<typename T0, typename T1, typename T2, typename T3>
		QuaternionSoft(T0 x, T1 y, T2 z, T3 w)
			: x(T(x)), y(T(y)), z(T(z)), w(T(w))
		{
		}

		QuaternionSoft(const QuaternionSoft<T>& QuaternionSoft)
		{
			x = QuaternionSoft.x;
			y = QuaternionSoft.y;
			z = QuaternionSoft.z;
			w = QuaternionSoft.w;
		}

		QuaternionSoft(const Vector3Soft<T>& axis, T angle);
		QuaternionSoft(const Vector3Soft<T>& eulerXYZ); // From Euler
		QuaternionSoft(const Matrix3Soft<T>& rot);
		QuaternionSoft(const Vector4Soft<T>& axis);
		QuaternionSoft(const Matrix4Soft<T>& rot);


		QuaternionSoft<T>& operator=(const QuaternionSoft<T>& q);
		QuaternionSoft<T>& operator=(const Matrix3Soft<T>& mat);
		QuaternionSoft<T>& operator=(const Matrix4Soft<T>& mat);

		QuaternionSoft<T> operator-() { return QuaternionSoft<T>(-x, -y, -z, -w); }
		QuaternionSoft<T> operator + (const QuaternionSoft<T>& op) { return QuaternionSoft<T>(x + op.x, y + op.y, z + op.z, w + op.w); }
		QuaternionSoft<T> operator * (const QuaternionSoft<T>& q);
		QuaternionSoft<T>& operator *= (const QuaternionSoft<T>& q);

		// scala operation
		QuaternionSoft<T> operator-(T scala) const;
		QuaternionSoft<T> operator + (T scala) const;
		QuaternionSoft<T> operator * (T scala) const;
		QuaternionSoft<T> operator / (T scala) const;
		//friend QuaternionSoft<T> operator*(const QuaternionSoft<T>& q1, const QuaternionSoft<T>& q2);


		QuaternionSoft<T> GetInverse() const;
		QuaternionSoft<T> GetConjugate() const;
		void Normalize();

		// Dot product
		T Dot(const QuaternionSoft<T>& op) const;

		// spherical interpolation between this and q2
		QuaternionSoft<T> Slerp(T s, const QuaternionSoft<T> & q2);


		void ToMatrix(Matrix3Soft<T>& mat) const;
		void ToMatrix(Matrix4Soft<T>& mat) const;
		//void ToEulerXYZ(Vector3Soft<T> & r);
		//void ToEulerXYZ(T* r);

		//void FromEulerXYZ(const Vector3Soft<T>& r);
		void FromAxisAngle(const Vector4Soft<T>& axis);
		void FromMatrix(const Matrix3Soft<T>& mat);
		void FromMatrix(const Matrix4Soft<T>& mat);

		// Rotate vector 
		Vector3Soft<T> RotateVector(const Vector3Soft<T>& v);
		Vector4Soft<T> RotateVector(const Vector4Soft<T>& v);

		// Dual Quaternions
		static void MakeDualQuaternion(const QuaternionSoft<T>& q0, const Vector4Soft<T>& t, QuaternionSoft<T> dq[2]);
		static void DecomposeDualQuaternionNoScale(const QuaternionSoft<T> dq[2], QuaternionSoft<T>& q0, Vector4Soft<T>& t);
		static void DecomposeDualQuaternion(const QuaternionSoft<T> dq[2], QuaternionSoft<T>& q0, Vector4Soft<T>& t);


		T& operator[](int i) { return Elements[i]; }
		const T& operator[](int i) const { return Elements[i]; }


		// vector elements
		union {
			struct {
				T x, y, z, w;
			};
			T Elements[4];
		};

	};

}


#include "Math/SF3DMathSoft.inl"
#include "Math/SF3DMath_vectorSoft.inl"
#include "Math/SF3DMath_matrixSoft.inl"
#include "Math/SF3DMath_quaternionSoft.inl"


