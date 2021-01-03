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


namespace SF 
{


	//////////////////////////////////////////////////////////////////////////////
	//
	//	Matrix3Soft
	//

	template<class T>
	inline Matrix3Soft<T>::Matrix3Soft(const T& f0, const T& f1, const T& f2,
		const T& f3, const T& f4, const T& f5,
		const T& f6, const T& f7, const T& f8)
		: a00(f0), a10(f1), a20(f2),
		a01(f3), a11(f4), a21(f5),
		a02(f6), a12(f7), a22(f8)
	{
	}

	template<class T>
	inline Matrix3Soft<T>& Matrix3Soft<T>::InitIdentity()
	{
		Elements[0] = T(1);
		Elements[1] = T(0);
		Elements[2] = T(0);
		Elements[3] = T(0);
		Elements[4] = T(1);
		Elements[5] = T(0);
		Elements[6] = T(0);
		Elements[7] = T(0);
		Elements[8] = T(1);
		return *this;
	}

	template<class T>
	inline const Vector3Soft<T> Matrix3Soft<T>::Col(const int i) const
	{
		return Vector3Soft<T>(Elements[i], Elements[i + 3], Elements[i + 6]);
	}

	template<class T>
	inline const Vector3Soft<T> Matrix3Soft<T>::Row(const int i) const
	{
		return Vector3Soft<T>(&Elements[i * 3]);
	}

	template<class T>
	inline const Vector3Soft<T> Matrix3Soft<T>::operator[](int i) const
	{
		return Vector3Soft<T>(&Elements[i * 3]);
	}

	template<class T>
	inline const T& Matrix3Soft<T>::operator()(const int& i, const int& j) const
	{
		return Elements[j + i * 3];
	}

	template<class T>
	inline T& Matrix3Soft<T>::operator()(const int& i, const int& j)
	{
		return  Elements[j + i * 3];
	}

	template<class T>
	inline Matrix3Soft<T> Matrix3Soft<T>::operator*(const T & scala) const
	{
		return Matrix3Soft<T>(
			Elements[0] * scala,
			Elements[1] * scala,
			Elements[2] * scala,
			Elements[3] * scala,
			Elements[4] * scala,
			Elements[5] * scala,
			Elements[6] * scala,
			Elements[7] * scala,
			Elements[8] * scala
			);
	}

	template<class T>
	inline Matrix3Soft<T> & Matrix3Soft<T>::operator*=(const T & scala)
	{
		for (int i = 0; i < 9; ++i)
			Elements[i] *= scala;
		return *this;
	}

	template<class T>
	inline Matrix3Soft<T>  Matrix3Soft<T>::operator*(const Matrix3Soft<T> & M) const
	{
		return Matrix3Soft(
			a00 * M.a00 + a01 * M.a10 + a02 * M.a20,
			a00 * M.a01 + a01 * M.a11 + a02 * M.a21,
			a00 * M.a02 + a01 * M.a12 + a02 * M.a22,

			a10 * M.a00 + a11 * M.a10 + a12 * M.a20,
			a10 * M.a01 + a11 * M.a11 + a12 * M.a21,
			a10 * M.a02 + a11 * M.a12 + a12 * M.a22,

			a20 * M.a00 + a21 * M.a10 + a22 * M.a20,
			a20 * M.a01 + a21 * M.a11 + a22 * M.a21,
			a20 * M.a02 + a21 * M.a12 + a22 * M.a22
			);
	}

	template<class T>
	inline Matrix3Soft<T> & Matrix3Soft<T>::operator*=(const Matrix3Soft<T> & M)
	{
		*this = (*this) * M;
		return *this;
	}

	template<class T>
	inline Matrix3Soft<T>  Matrix3Soft<T>::operator+(const Matrix3Soft<T> & M) const
	{
		Matrix3Soft<T> res(*this);

		res += M;

		return res;
	}

	template<class T>
	inline Matrix3Soft<T> & Matrix3Soft<T>::operator+=(const Matrix3Soft<T> & M)
	{
		for (int i = 0; i < 9; i += 3)
		{
			Elements[i] += M.Elements[i];
			Elements[i + 1] += M.Elements[i + 1];
			Elements[i + 2] += M.Elements[i + 2];
		}
		return *this;
	}

	template<class T>
	inline Matrix3Soft<T>  Matrix3Soft<T>::operator-(const Matrix3Soft<T> & M) const
	{
		Matrix3Soft<T> res(*this);

		res -= M;

		return res;
	}

	template<class T>
	inline Matrix3Soft<T> & Matrix3Soft<T>::operator-=(const Matrix3Soft<T> & M)
	{
		for (int i = 0; i < 9; i+=3)
		{
			Elements[i] -= M.Elements[i];
			Elements[i+1] -= M.Elements[i+1];
			Elements[i+2] -= M.Elements[i+2];
		}
		return *this;
	}


	template<class T>
	inline Vector3Soft<T> Matrix3Soft<T>::operator*(const Vector3Soft<T>& v) const
	{
		return Vector3Soft<T>(
			a00 * v.x + a01 * v.y + a02 * v.z,
			a10 * v.x + a11 * v.y + a12 * v.z,
			a20 * v.x + a21 * v.y + a22 * v.z
			);
	}

	template<class T>
	inline Vector4Soft<T> Matrix3Soft<T>::operator*(const Vector4Soft<T>& v) const
	{
		return Vector4Soft<T>(
			a00 * v.x + a01 * v.y + a02 * v.z,
			a10 * v.x + a11 * v.y + a12 * v.z,
			a20 * v.x + a21 * v.y + a22 * v.z,
			v.w
			);
	}

	template<class T>
	inline Matrix3Soft<T> & Matrix3Soft<T>::SetRow(int i, const Vector3Soft<T> & v)
	{
		Elements[i] = v.x;
		Elements[i + 3] = v.y;
		Elements[i + 6] = v.z;
		return *this;
	}

	template<class T>
	inline Matrix3Soft<T> & Matrix3Soft<T>::SetColumn(int i, const Vector3Soft<T> & v)
	{
		Elements[i * 3] = v.x;
		Elements[i * 3 + 1] = v.y;
		Elements[i * 3 + 2] = v.z;
		return *this;
	}

	// v is normalized
	// theta in radians
	template<class T>
	inline Matrix3Soft<T> & Matrix3Soft<T>::SetRotation(const T& theta, const Vector3Soft<T>& v)
	{
		T ct = T(cos(theta));
		T st = T(sin(theta));

		T xx = v.x * v.x;
		T yy = v.y * v.y;
		T zz = v.z * v.z;
		T xy = v.x * v.y;
		T xz = v.x * v.z;
		T yz = v.y * v.z;

		a00 = xx + ct*(1 - xx);
		a01 = xy + ct*(-xy) + st*-v.z;
		a02 = xz + ct*(-xz) + st*v.y;

		a10 = xy + ct*(-xy) + st*v.z;
		a11 = yy + ct*(1 - yy);
		a12 = yz + ct*(-yz) + st*-v.x;

		a20 = xz + ct*(-xz) + st*-v.y;
		a21 = yz + ct*(-yz) + st*v.x;
		a22 = zz + ct*(1 - zz);
		return *this;
	}

	template<class T>
	inline Matrix3Soft<T> & Matrix3Soft<T>::SetRotation(const Vector3Soft<T>& u, const Vector3Soft<T>& v)
	{
		T phi;
		T h;
		T scala;
		Vector3Soft<T> w;

		w = u.Cross(v);
		phi = u.Dot(v);
		scala = w.Dot(w);
		if (scala > C_EPSILON)
			h = (T(1) - phi) / scala;
		else
			h = scala;

		T hxy = w.x * w.y * h;
		T hxz = w.x * w.z * h;
		T hyz = w.y * w.z * h;

		a00 = phi + w.x * w.x * h;
		a01 = hxy - w.z;
		a02 = hxz + w.y;

		a10 = hxy + w.z;
		a11 = phi + w.y * w.y * h;
		a12 = hyz - w.x;

		a20 = hxz - w.y;
		a21 = hyz + w.x;
		a22 = phi + w.z * w.z * h;
		return *this;
	}


	template<class T>
	inline Matrix3Soft<T> & Matrix3Soft<T>::SetRotation(const QuaternionSoft<T> & q)
	{
		q.ToMatrix(*this);
		return *this;
	}
	

	template<class T>
	inline Matrix3Soft<T> Matrix3Soft<T>::operator - () const
	{
		Matrix3Soft<T> N;
		for (int i = 0; i < 9; ++i)
			N.Elements[i] = -Elements[i];
		return N;
	}


	template<class T>
	inline T Matrix3Soft<T>::GetNorm() const
	{
		T sum, max = T(0);
		sum = (T)(fabs(a00) + fabs(a10) + fabs(a20));
		if (max < sum)
			max = sum;
		sum = (T)(fabs(a01) + fabs(a11) + fabs(a21));
		if (max < sum)
			max = sum;
		sum = (T)(fabs(a02) + fabs(a12) + fabs(a22));
		if (max < sum)
			max = sum;
		return max;
	}

	template<class T>
	inline T Matrix3Soft<T>::GetNormInf() const
	{
		T sum, max = T(0);
		sum = (T)(fabs(a00) + fabs(a01) + fabs(a02));
		if (max < sum)
			max = sum;
		sum = (T)(fabs(a10) + fabs(a11) + fabs(a12));
		if (max < sum)
			max = sum;
		sum = (T)(fabs(a20) + fabs(a21) + fabs(a22));
		if (max < sum)
			max = sum;
		return max;
	}


	template<class T>
	inline Matrix3Soft<T> Matrix3Soft<T>::GetInvert() const
	{
		Matrix3Soft<T> B;
		T det, invDet;

		B.a00 = (a11 * a22 - a21 * a12);
		B.a10 = -(a10 * a22 - a20 * a12);
		B.a20 = (a10 * a21 - a20 * a11);
		B.a01 = -(a01 * a22 - a21 * a02);
		B.a11 = (a00 * a22 - a20 * a02);
		B.a21 = -(a00 * a21 - a20 * a01);
		B.a02 = (a01 * a12 - a11 * a02);
		B.a12 = -(a00 * a12 - a10 * a02);
		B.a22 = (a00 * a11 - a10 * a01);

		det = (a00 * B.a00) + (a01 * B.a10) + (a02 * B.a20);

		invDet = T(1) / det;

		B.a00 *= invDet; B.a01 *= invDet; B.a02 *= invDet;
		B.a10 *= invDet; B.a11 *= invDet; B.a12 *= invDet;
		B.a20 *= invDet; B.a21 *= invDet; B.a22 *= invDet;
		return B;
	}


	template<class T>
	inline Matrix3Soft<T>& Matrix3Soft<T>::Invert()
	{
		Matrix3Soft<T> B;
		T det, invDet;

		B.a00 = (a11 * a22 - a21 * a12);
		B.a10 = -(a10 * a22 - a20 * a12);
		B.a20 = (a10 * a21 - a20 * a11);
		B.a01 = -(a01 * a22 - a21 * a02);
		B.a11 = (a00 * a22 - a20 * a02);
		B.a21 = -(a00 * a21 - a20 * a01);
		B.a02 = (a01 * a12 - a11 * a02);
		B.a12 = -(a00 * a12 - a10 * a02);
		B.a22 = (a00 * a11 - a10 * a01);

		det = (a00 * B.a00) + (a01 * B.a10) + (a02 * B.a20);

		invDet = T(1) / det;

		a00 = B.a00 * invDet; a01 = B.a01 * invDet; a02 = B.a02 * invDet;
		a10 = B.a10 * invDet; a11 = B.a11 * invDet; a12 = B.a12 * invDet;
		a20 = B.a20 * invDet; a21 = B.a21 * invDet; a22 = B.a22 * invDet;
		return *this;
	}


	template<class T>
	inline Matrix3Soft<T> Matrix3Soft<T>::GetTranspose()
	{
		return Matrix3Soft<T>(
			a00, a10, a20,
			a01, a11, a21,
			a02, a12, a22
		);
	}

	template<class T>
	inline Matrix3Soft<T>& Matrix3Soft<T>::Transpose()
	{
		T temp;
		temp = a01; a01 = a10; a10 = temp;
		temp = a02; a02 = a20; a20 = temp;
		temp = a12; a12 = a21; a21 = temp;

		return *this;
	}

	// Determinent
	//| a1 a2 |
	//| b1 b2 |
	template<class T>
	inline T Determinent2x2(T a1, T a2, T b1, T b2)
	{
		return a1 * b2 - b1 * a2;
	}


	// Determinent
	template<class T>
	inline T Matrix3Soft<T>::GetDeterminent()
	{
		return a00 * Determinent2x2(a11, a12, a21, a22) - a10 * Determinent2x2(a01, a02, a21, a22) + a20 * Determinent2x2(a01, a02, a11, a12);
	}

	template<class T>
	inline Matrix3Soft<T> Matrix3Soft<T>::GetInvert()
	{
		Matrix3Soft<T> B;

		B.a00 = Determinent2x2(a11, a12, a21, a22);
		B.a01 = -Determinent2x2(a01, a02, a21, a22);
		B.a02 = Determinent2x2(a01, a02, a11, a12);

		auto det = (a00 * B.a00) + (a10 * B.a01) + (a20 * B.a02);
		if (det < C_EPSILON)
		{
			assert(false);
			B.InitIdentity();
			return B;
		}

		B.a10 = -Determinent2x2(a10, a12, a20, a22);
		B.a11 = Determinent2x2(a00, a02, a20, a22);
		B.a12 = -Determinent2x2(a00, a02, a10, a12);

		B.a20 = Determinent2x2(a10, a11, a20, a21);
		B.a21 = -Determinent2x2(a00, a01, a20, a21);
		B.a22 = Determinent2x2(a00, a01, a10, a11);

		auto invDet = T(1) / det;

		return B * invDet;
	}

	// Invert transform matrix without scale
	template<class T>
	inline Matrix3Soft<T> Matrix3Soft<T>::GetInvertNoScale()
	{
		return Matrix3Soft<T>(
			a00, a01, a02, 
			a10, a11, a12, 
			a20, a21, a22
			);
	}



	//////////////////////////////////////////////////////////////////////////////
	//
	//	Matrix4Soft
	//

	template<class T>
	inline Matrix4Soft<T>& Matrix4Soft<T>::InitIdentity()
	{
		Elements[0] = T(1);
		Elements[1] = T(0);
		Elements[2] = T(0);
		Elements[3] = T(0);

		Elements[4] = T(0);
		Elements[5] = T(1);
		Elements[6] = T(0);
		Elements[7] = T(0);

		Elements[8] = T(0);
		Elements[9] = T(0);
		Elements[10] = T(1);
		Elements[11] = T(0);

		Elements[12] = T(0);
		Elements[13] = T(0);
		Elements[14] = T(0);
		Elements[15] = T(1);

		return *this;
	}

	template<class T>
	inline Matrix4Soft<T> Matrix4Soft<T>::GetTranspose()
	{
		return Matrix4Soft<T>(
			a00, a10, a20, a30,
			a01, a11, a21, a31,
			a02, a12, a22, a32,
			a03, a13, a23, a33
			);
	}

	template<class T>
	inline Matrix4Soft<T>& Matrix4Soft<T>::Transpose()
	{
		std::swap(a10, a01);
		std::swap(a20, a02);
		std::swap(a30, a03);
		std::swap(a12, a21);
		std::swap(a13, a31);
		std::swap(a23, a32);

		return *this;
	}


	template<class T>
	inline Matrix3Soft<T> Matrix4Soft<T>::GetRotationMatrix() const
	{
		return Matrix3Soft<T>(
			a00, a10, a20,
			a01, a11, a21,
			a02, a12, a22
			);
	}

	template<class T>
	inline Matrix4Soft<T> & Matrix4Soft<T>::InitRotationMatrix(const QuaternionSoft<T>& q)
	{
		float x2 = q.x * 2;
		float y2 = q.y * 2;
		float z2 = q.z * 2;
		float wx = x2 * q.w;
		float wy = y2 * q.w;
		float wz = z2 * q.w;
		float xx = x2 * q.x;
		float xy = y2 * q.x;
		float xz = z2 * q.x;
		float yy = y2 * q.y;
		float yz = z2 * q.y;
		float zz = z2 * q.z;
		a00 = 1 - (yy + zz);
		a01 = xy - wz;
		a02 = xz + wy;
		a03 = 0.0f;
		a10 = xy + wz;
		a11 = 1 - (xx + zz);
		a12 = yz - wx;
		a13 = 0.0f;
		a20 = xz - wy;
		a21 = yz + wx;
		a22 = 1 - (xx + yy);
		a23 = 0.0f;
		a30 = 0.0f;
		a31 = 0.0f;
		a32 = 0.0f;
		a33 = 1.0f;
		return *this;
	}

	// v is normalized
	// theta in radians
	template<class T>
	inline Matrix4Soft<T> & Matrix4Soft<T>::InitRotationMatrix(const Vector4Soft<T>& v)
	{
		const T theta = v.w;
		T ct = T(cos(theta));
		T st = T(sin(theta));

		T xx = v.x * v.x;
		T yy = v.y * v.y;
		T zz = v.z * v.z;
		T xy = v.x * v.y;
		T xz = v.x * v.z;
		T yz = v.y * v.z;

		a00 = xx + ct * (1 - xx);
		a10 = xy + ct * (-xy) + st * v.z;
		a20 = xz + ct * (-xz) + st * -v.y;
		a30 = 0;

		a01 = xy + ct * (-xy) + st * -v.z;
		a11 = yy + ct * (1 - yy);
		a21 = yz + ct * (-yz) + st * v.x;
		a31 = 0;

		a02 = xz + ct * (-xz) + st * v.y;
		a12 = yz + ct * (-yz) + st * -v.x;
		a22 = zz + ct * (1 - zz);
		a32 = 0;

		a03 = a13 = a23 = 0;
		a33 = 1;

		return *this;
	}

	template<class T>
	inline Matrix4Soft<T> & Matrix4Soft<T>::InitRotationMatrix(const Vector4Soft<T>& u, const Vector4Soft<T>& v)
	{
		T phi;
		T h;
		T scala;
		Vector4Soft<T> w;

		w = u.Cross(v);
		phi = u.Dot3(v);
		scala = w.Dot3(w);
		if (scala > C_EPSILON)
			h = (T(1) - phi) / scala;
		else
			h = scala;

		T hxy = w.x * w.y * h;
		T hxz = w.x * w.z * h;
		T hyz = w.y * w.z * h;

		a00 = phi + w.x * w.x * h;
		a01 = hxy - w.z;
		a02 = hxz + w.y;
		a03 = 0;

		a10 = hxy + w.z;
		a11 = phi + w.y * w.y * h;
		a12 = hyz - w.x;
		a13 = 0;

		a20 = hxz - w.y;
		a21 = hyz + w.x;
		a22 = phi + w.z * w.z * h;
		a23 = 0;

		a03 = a13 = a23 = 0;
		a33 = 1;
		return *this;
	}

	template<class T>
	inline Matrix4Soft<T> & Matrix4Soft<T>::InitRotationMatrix(const Matrix3Soft<T>& M)
	{
		// copy the 3x3 rotation block
		a00 = M.a00; a10 = M.a10; a20 = M.a20; a30 = 0;
		a01 = M.a01; a11 = M.a11; a21 = M.a21; a31 = 0;
		a02 = M.a02; a12 = M.a12; a22 = M.a22; a32 = 0;
		a03 = 0; a13 = 0; a23 = 0; a33 = 1;
		return *this;
	}

	template<class T>
	inline Matrix4Soft<T> & Matrix4Soft<T>::InitRotationMatrix(const Matrix4Soft<T>& M)
	{
		// copy the 3x3 rotation block
		a00 = M.a00; a10 = M.a10; a20 = M.a20; a30 = 0;
		a01 = M.a01; a11 = M.a11; a21 = M.a21; a31 = 0;
		a02 = M.a02; a12 = M.a12; a22 = M.a22; a32 = 0;
		a03 = 0; a13 = 0; a23 = 0; a33 = 1;
		return *this;
	}


	template<class T>
	inline Matrix4Soft<T> & Matrix4Soft<T>::InitScaleMatrix(const Vector3Soft<T>& s)
	{
		InitIdentity();
		a00 = s.x;
		a11 = s.y;
		a22 = s.z;
		return *this;
	}

	template<class T>
	inline Matrix4Soft<T> & Matrix4Soft<T>::InitScaleMatrix(const T& s)
	{
		InitIdentity();
		a00 = s;
		a11 = s;
		a22 = s;
		return *this;
	}

	template<class T>
	inline Matrix4Soft<T> & Matrix4Soft<T>::SetTranslation(const Vector3Soft<T>& t)
	{
		a03 = t.x;
		a13 = t.y;
		a23 = t.z;
		return *this;
	}

	template<class T>
	inline Vector3Soft<T> Matrix4Soft<T>::GetTranslation() const
	{
		return Vector3Soft<T>(a03, a13, a23);
	}

	template<class T>
	inline Matrix4Soft<T> & Matrix4Soft<T>::InitTranslationMatrix(const Vector3Soft<T>& t)
	{
		InitIdentity();
		a03 = t.x;
		a13 = t.y;
		a23 = t.z;
		return *this;
	}

	template<class T>
	inline QuaternionSoft<T> Matrix4Soft<T>::ToQuaternion() const
	{
		QuaternionSoft<T> q;

		float trace = a00 + a11 + a22;
		if (trace > float(0))
		{
			float Scale = sqrtf(trace + float(1));
			q.w = float(0.5) * Scale;
			Scale = float(0.5) / Scale;
			q.x = Scale * (a21 - a12);
			q.y = Scale * (a02 - a20);
			q.z = Scale * (a10 - a01);
		}
		else
		{
			auto& mat = *this;
			static int next[] = { 1, 2, 0 };
			int i = 0;
			if (a11 > a00)
				i = 1;
			if (a22 > mat(i, i))
				i = 2;
			int j = next[i];
			int k = next[j];
			float Scale = sqrtf(mat(i, i) - mat(j, j) - mat(k, k) + 1);
			float* qe[] = { &q.x, &q.y, &q.z };
			*qe[i] = 0.5f * Scale;
			Scale = 0.5f / Scale;
			q.w = Scale * (mat(k, j) - mat(j, k));
			*qe[j] = Scale * (mat(j, i) + mat(i, j));
			*qe[k] = Scale * (mat(k, i) + mat(i, k));
		}

		return q;
	}


	template<class T>
	inline Matrix4Soft<T> Matrix4Soft<T>::operator*(const T& scala) const
	{
		return Matrix4Soft<T>(
			a00 * scala,
			a01 * scala,
			a02 * scala,
			a03 * scala,
			a10 * scala,
			a11 * scala,
			a12 * scala,
			a13 * scala,
			a20 * scala,
			a21 * scala,
			a22 * scala,
			a23 * scala,
			a30 * scala,
			a31 * scala,
			a32 * scala,
			a33 * scala
			);
	}

	template<class T>
	inline Matrix4Soft<T>& Matrix4Soft<T>::operator*=(const T& scala)
	{
		for (int i = 0; i < 16; i += 4)
		{
			Elements[i] *= scala;
			Elements[i + 1] *= scala;
			Elements[i + 2] *= scala;
			Elements[i + 3] *= scala;
		}

		return *this;
	}


	template<class T>
	inline Matrix4Soft<T> Matrix4Soft<T>::operator/(const T& scala) const
	{
		float invScala = T(1) / scala;
		return Matrix4Soft<T>(
			a00 * invScala,
			a01 * invScala,
			a02 * invScala,
			a03 * invScala,
			a10 * invScala,
			a11 * invScala,
			a12 * invScala,
			a13 * invScala,
			a20 * invScala,
			a21 * invScala,
			a22 * invScala,
			a23 * invScala,
			a30 * invScala,
			a31 * invScala,
			a32 * invScala,
			a33 * invScala
			);
	}

	template<class T>
	inline Matrix4Soft<T>& Matrix4Soft<T>::operator/=(const T& scala)
	{
		float invScala = T(1) / scala;
		for (int i = 0; i < 16; i += 4)
		{
			Elements[i] *= invScala;
			Elements[i + 1] *= invScala;
			Elements[i + 2] *= invScala;
			Elements[i + 3] *= invScala;
		}

		return *this;
	}


	// C = A * B

	// C.a00 C.a01 C.a02 C.a03   A.a00 A.a01 A.a02 A.a03   B.a00 B.a01 B.a02 B.a03
	//                                                                            
	// C.a10 C.a11 C.a12 C.a13   A.a10 A.a11 A.a12 A.a13   B.a10 B.a11 B.a12 B.a13
	//                                                                         
	// C.a20 C.a21 C.a22 C.a23   A.a20 A.a21 A.a22 A.a23   B.a20 B.a21 B.a22 B.a23  
	//                                                                            
	// C.a30 C.a31 C.a32 C.a33 = A.a30 A.a31 A.a32 A.a33 * B.a30 B.a31 B.a32 B.a33
	template<class T>
	inline Matrix4Soft<T> Matrix4Soft<T>::operator*(const Matrix4Soft<T>& B) const
	{
		Matrix4Soft<T> C;
		C.a00 = a00 * B.a00 + a01 * B.a10 + a02 * B.a20 + a03 * B.a30;
		C.a10 = a10 * B.a00 + a11 * B.a10 + a12 * B.a20 + a13 * B.a30;
		C.a20 = a20 * B.a00 + a21 * B.a10 + a22 * B.a20 + a23 * B.a30;
		C.a30 = a30 * B.a00 + a31 * B.a10 + a32 * B.a20 + a33 * B.a30;

		C.a01 = a00 * B.a01 + a01 * B.a11 + a02 * B.a21 + a03 * B.a31;
		C.a11 = a10 * B.a01 + a11 * B.a11 + a12 * B.a21 + a13 * B.a31;
		C.a21 = a20 * B.a01 + a21 * B.a11 + a22 * B.a21 + a23 * B.a31;
		C.a31 = a30 * B.a01 + a31 * B.a11 + a32 * B.a21 + a33 * B.a31;

		C.a02 = a00 * B.a02 + a01 * B.a12 + a02 * B.a22 + a03 * B.a32;
		C.a12 = a10 * B.a02 + a11 * B.a12 + a12 * B.a22 + a13 * B.a32;
		C.a22 = a20 * B.a02 + a21 * B.a12 + a22 * B.a22 + a23 * B.a32;
		C.a32 = a30 * B.a02 + a31 * B.a12 + a32 * B.a22 + a33 * B.a32;

		C.a03 = a00 * B.a03 + a01 * B.a13 + a02 * B.a23 + a03 * B.a33;
		C.a13 = a10 * B.a03 + a11 * B.a13 + a12 * B.a23 + a13 * B.a33;
		C.a23 = a20 * B.a03 + a21 * B.a13 + a22 * B.a23 + a23 * B.a33;
		C.a33 = a30 * B.a03 + a31 * B.a13 + a32 * B.a23 + a33 * B.a33;
		return C;
	}

	template<class T>
	inline Matrix4Soft<T>& Matrix4Soft<T>::operator*=(const Matrix4Soft<T> & m)
	{
		*this = (*this) * m;
		return *this;
	}


	template<class T>
	Matrix4Soft<T>  Matrix4Soft<T>::operator+(const Matrix4Soft<T> & M) const
	{
		Matrix4Soft<T> res(*this);
		res += M;
		return res;
	}

	template<class T>
	Matrix4Soft<T> & Matrix4Soft<T>::operator+=(const Matrix4Soft<T> & M)
	{
		for (int i = 0; i < 16; i += 4)
		{
			Elements[i] += M.Elements[i];
			Elements[i + 1] += M.Elements[i + 1];
			Elements[i + 2] += M.Elements[i + 2];
			Elements[i + 3] += M.Elements[i + 3];
		}

		return *this;
	}

	template<class T>
	Matrix4Soft<T>  Matrix4Soft<T>::operator-(const Matrix4Soft<T> & M) const
	{
		Matrix4Soft<T> res(*this);
		res -= M;
		return res;
	}

	template<class T>
	Matrix4Soft<T> & Matrix4Soft<T>::operator-=(const Matrix4Soft<T> & M)
	{
		for (int i = 0; i < 16; i += 4)
		{
			Elements[i] -= M.Elements[i];
			Elements[i + 1] -= M.Elements[i + 1];
			Elements[i + 2] -= M.Elements[i + 2];
			Elements[i + 3] -= M.Elements[i + 3];
		}

		return *this;
	}

	template<class T>
	Vector3Soft<T> Matrix4Soft<T>::operator*(const Vector3Soft<T>& v) const
	{
		return Vector3Soft<T>(
			a00 * v.x + a01 * v.y + a02 * v.z + a03,
			a10 * v.x + a11 * v.y + a12 * v.z + a13,
			a20 * v.x + a21 * v.y + a22 * v.z + a23
			);
	}

	template<class T>
	Vector4Soft<T> Matrix4Soft<T>::operator*(const Vector4Soft<T>& v) const
	{
		return Vector4Soft<T>(
			a00 * v.x + a01 * v.y + a02 * v.z + a03 * v.w,
			a10 * v.x + a11 * v.y + a12 * v.z + a13 * v.w,
			a20 * v.x + a21 * v.y + a22 * v.z + a23 * v.w,
			a30 * v.x + a31 * v.y + a32 * v.z + a33 * v.w
			);
	}



	// Determinent
	template<class T>
	inline T Determinent3x3(T a00, T a10, T a20,
							T a01, T a11, T a21,
							T a02, T a12, T a22)
	{
		return a00 * Determinent2x2(a11, a12, a21, a22) - a10 * Determinent2x2(a01, a02, a21, a22) + a20 * Determinent2x2(a01, a02, a11, a12);
	}


	// Transform position vector
	// This operation same to matrix-vector multiplication, but it will ignore w component
	template<class T>
	inline Vector4Soft<T> Matrix4Soft<T>::TransformVector(const Vector4Soft<T>& v)
	{
		return Vector4Soft<T>(
			a00 * v.x + a01 * v.y + a02 * v.z + a03,
			a10 * v.x + a11 * v.y + a12 * v.z + a13,
			a20 * v.x + a21 * v.y + a22 * v.z + a23,
			1
			);
	}

	template<class T>
	inline Matrix4Soft<T> Matrix4Soft<T>::GetInverse()
	{
		// http://semath.info/src/inverse-cofactor-ex4.html

		Matrix4Soft<T> B;
		T det;

		// Adjugate, index is transposed
		B.a00 = Determinent3x3(a11, a21, a31, a12, a22, a32, a13, a23, a33);
		B.a01 = -Determinent3x3(a01, a21, a31, a02, a22, a32, a03, a23, a33);
		B.a02 = Determinent3x3(a01, a11, a31, a02, a12, a32, a03, a13, a33);
		B.a03 = -Determinent3x3(a01, a11, a21, a02, a12, a22, a03, a13, a23);

		B.a10 = -Determinent3x3(a10, a20, a30, a12, a22, a32, a13, a23, a33);
		B.a11 = Determinent3x3(a00, a20, a30, a02, a22, a32, a03, a23, a33);
		B.a12 = -Determinent3x3(a00, a10, a30, a02, a12, a32, a03, a13, a33);
		B.a13 = Determinent3x3(a00, a10, a20, a02, a12, a22, a03, a13, a23);

		B.a20 = Determinent3x3(a10, a20, a30, a11, a21, a31, a13, a23, a33);
		B.a21 = -Determinent3x3(a00, a20, a30, a01, a21, a31, a03, a23, a33);
		B.a22 = Determinent3x3(a00, a10, a30, a01, a11, a31, a03, a13, a33);
		B.a23 = -Determinent3x3(a00, a10, a20, a01, a11, a21, a03, a13, a23);

		B.a30 = -Determinent3x3(a10, a20, a30, a11, a21, a31, a12, a22, a32);
		B.a31 = Determinent3x3(a00, a20, a30, a01, a21, a31, a02, a22, a32);
		B.a32 = -Determinent3x3(a00, a10, a30, a01, a11, a31, a02, a12, a32);
		B.a33 = Determinent3x3(a00, a10, a20, a01, a11, a21, a02, a12, a22);

		det = (a00 * B.a00) + (a10 * B.a01) + (a20 * B.a02) + (a30 * B.a03);

		if (Math::Abs(det) < std::numeric_limits<T>::epsilon())
		{
			//assert(false);
			B.InitIdentity();
			return B;
		}

		return B / det;
	}

	// Invert transform matrix without scale
	template<class T>
	inline Matrix4Soft<T> Matrix4Soft<T>::GetInverseTransform()
	{
		// Final matrix will be S`R`T`
		// So eventually multiplying 1/s^2 is correct approach
		auto scalex = Vec[0].SquareLength3();
		auto scaley = Vec[1].SquareLength3();
		auto scalez = Vec[2].SquareLength3();

		if (Math::Abs(scalex) < std::numeric_limits<T>::epsilon())
			scalex = 1;
		if (Math::Abs(scaley) < std::numeric_limits<T>::epsilon())
			scaley = 1;
		if (Math::Abs(scalez) < std::numeric_limits<T>::epsilon())
			scalez = 1;

		//if (Vec[0].Cross(Vec[1]).Dot3(Vec[2]) < 0)
		//{
		//	scalez = -scalez;
		//}

		auto invX = T(1) / scalex;
		auto invY = T(1) / scaley;
		auto invZ = T(1) / scalez;

		// transpose of rotation
		Matrix4Soft<T> rot
		(
			a00 * invX, a10 * invX, a20 * invX, 0,
			a01 * invY, a11 * invY, a21 * invY, 0,
			a02 * invZ, a12 * invZ, a22 * invZ, 0,
			0, 0, 0, 1
		);

		// Transform vector will ignore -w
		rot.Vec[3] = rot.TransformVector(-Vec[3]);

		return rot;
	}

	// Invert transform matrix without scale
	template<class T>
	inline Matrix4Soft<T> Matrix4Soft<T>::GetInverseTransformNoScale()
	{
		return Matrix4Soft<T>(
			a00, a10, a20, -(a00 * a03 + a10 * a13 + a20 * a23),
			a01, a11, a21, -(a01 * a03 + a11 * a13 + a21 * a23),
			a02, a12, a22, -(a02 * a03 + a12 * a13 + a22 * a23),

			0, 0, 0, 1
			);
	}


	template<class T>
	inline Matrix4Soft<T>& Matrix4Soft<T>::NormalizeTransform()
	{
		if (a33 < std::numeric_limits<float>::epsilon())
		{
			assert(false); // can't normalize
		}

		if (Math::Abs(1.0 - a33) < std::numeric_limits<float>::epsilon())
		{
			// doesn't need to be normalized
			return *this;
		}

		float inv33 = 1.0 / a33;
		for (int i = 0; i < 16; i+=4)
		{
			Elements[i + 0] *= inv33;
			Elements[i + 1] *= inv33;
			Elements[i + 2] *= inv33;
			Elements[i + 3] *= inv33;
		}

		return *this;
	}
}





