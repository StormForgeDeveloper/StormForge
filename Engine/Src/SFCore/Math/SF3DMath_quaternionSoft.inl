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


namespace SF {



	template<class T>
	inline QuaternionSoft<T>::QuaternionSoft(const Vector3Soft<T>& axis, T angle)
	{
		T len = axis.Length();
		if (len) {
			T invLen = 1 / len;
			T angle2 = angle / 2;
			T Scale = sinf(angle2) * invLen;
			x = Scale * axis[0];
			y = Scale * axis[1];
			z = Scale * axis[2];
			w = cosf(angle2);
		}
		else
		{
			x = 0; y = 0; z = 0; w = 1;
		}
	}

	template<class T>
	inline QuaternionSoft<T>::QuaternionSoft(const Vector3Soft<T>& eulerXYZ)
	{
		// TODO:
		assert(false);
	}

	template<class T>
	inline QuaternionSoft<T>::QuaternionSoft(const Matrix3Soft<T>& rot)
	{
		(*this) = rot;
	}

	template<class T>
	inline QuaternionSoft<T>::QuaternionSoft(const Vector4Soft<T>& axis)
	{
		T angle = axis.w;
		T len = axis.Length3();
		if (len) {
			T invLen = 1 / len;
			T angle2 = angle / 2;
			T Scale = sinf(angle2) * invLen;
			x = Scale * axis[0];
			y = Scale * axis[1];
			z = Scale * axis[2];
			w = cosf(angle2);
		}
		else
		{
			x = 0; y = 0; z = 0; w = 1;
		}
	}

	template<class T>
	inline QuaternionSoft<T>::QuaternionSoft(const Matrix4Soft<T>& rot)
	{
		(*this) = rot;
	}

	template<class T>
	inline QuaternionSoft<T>& QuaternionSoft<T>::operator=(const QuaternionSoft<T>& q)
	{
		x = q.x;
		y = q.y;
		z = q.z;
		w = q.w;
		return *this;
	}

	template<class T>
	inline QuaternionSoft<T>& QuaternionSoft<T>::operator=(const Matrix3Soft<T>& mat)
	{
		T trace = mat.a00 + mat.a11 + mat.a22;
		if (trace > T(0))
		{
			T Scale = sqrtf(trace + T(1));
			w = T(0.5) * Scale;
			Scale = T(0.5) / Scale;
			x = Scale * (mat.a21 - mat.a12);
			y = Scale * (mat.a02 - mat.a20);
			z = Scale * (mat.a10 - mat.a01);
		}
		else
		{
			static int next[] = { 1, 2, 0 };
			int i = 0;
			if (mat.a11 > mat.a00)
				i = 1;
			if (mat.a22 > mat(i, i))
				i = 2;
			int j = next[i];
			int k = next[j];
			T Scale = sqrtf(mat(i, i) - mat(j, j) - mat(k, k) + 1);
			T* q[] = { &x, &y, &z };
			*q[i] = 0.5f * Scale;
			Scale = 0.5f / Scale;
			w = Scale * (mat(k, j) - mat(j, k));
			*q[j] = Scale * (mat(j, i) + mat(i, j));
			*q[k] = Scale * (mat(k, i) + mat(i, k));
		}

		return *this;
	}

	template<class T>
	inline QuaternionSoft<T>& QuaternionSoft<T>::operator=(const Matrix4Soft<T>& mat)
	{
		T trace = mat(0, 0) + mat(1, 1) + mat(2, 2);
		if (trace > T(0))
		{
			T Scale = sqrtf(trace + T(1));
			w = T(0.5) * Scale;
			Scale = T(0.5) / Scale;
			x = Scale * (mat(2, 1) - mat(1, 2));
			y = Scale * (mat(0, 2) - mat(2, 0));
			z = Scale * (mat(1, 0) - mat(0, 1));
		}
		else
		{
			static int next[] = { 1, 2, 0 };
			int i = 0;
			if (mat(1, 1) > mat(0, 0))
				i = 1;
			if (mat(2, 2) > mat(i, i))
				i = 2;
			int j = next[i];
			int k = next[j];
			T Scale = sqrtf(mat(i, i) - mat(j, j) - mat(k, k) + 1);
			T* q[] = { &x, &y, &z };
			*q[i] = 0.5f * Scale;
			Scale = 0.5f / Scale;
			w = Scale * (mat(k, j) - mat(j, k));
			*q[j] = Scale * (mat(j, i) + mat(i, j));
			*q[k] = Scale * (mat(k, i) + mat(i, k));
		}

		return *this;
	}


	template<class T>
	QuaternionSoft<T> QuaternionSoft<T>::operator * (const QuaternionSoft<T>& q)
	{
		return QuaternionSoft<T>(
			w * q.x + x * q.w + y * q.z - z * q.y,
			w * q.y - x * q.z + y * q.w + z * q.x,
			w * q.z + x * q.y - y * q.x + z * q.w,
			w * q.w - x * q.x - y * q.y - z * q.z
			);
	}

	template<class T>
	QuaternionSoft<T>& QuaternionSoft<T>::operator *= (const QuaternionSoft<T>& q)
	{
		(*this) = (*this) * q;
		return *this;
	}


	template<class T>
	QuaternionSoft<T> QuaternionSoft<T>::operator-(T scala) const
	{
		return QuaternionSoft<T>(x-scala, y - scala, z - scala, w - scala);
	}

	template<class T>
	QuaternionSoft<T> QuaternionSoft<T>::operator + (T scala) const
	{
		return QuaternionSoft<T>(x + scala, y + scala, z + scala, w + scala);
	}

	template<class T>
	QuaternionSoft<T> QuaternionSoft<T>::operator * (T scala) const
	{
		return QuaternionSoft<T>(x * scala, y * scala, z * scala, w * scala);
	}

	template<class T>
	QuaternionSoft<T> QuaternionSoft<T>::operator / (T scala) const
	{
		return QuaternionSoft<T>(x / scala, y / scala, z / scala, w / scala);
	}



	template<class T>
	inline QuaternionSoft<T> QuaternionSoft<T>::GetInverse() const
	{
		return QuaternionSoft<T>(-x, -y, -z, w);
	}
	template<class T>
	inline QuaternionSoft<T> QuaternionSoft<T>::GetConjugate() const
	{
		return QuaternionSoft<T>(-x, -y, -z, w);
	}

	template<class T>
	inline void QuaternionSoft<T>::Normalize()
	{
		T len = sqrtf(x * x + y * y + z * z + w * w);
		if (len > C_EPSILON)
		{
			T invLen = 1 / len;
			x *= invLen;
			y *= invLen;
			z *= invLen;
			w *= invLen;
		}
		else
		{
			assert(false);
			x = 0;
			y = 0;
			z = 0;
			w = 1;
		}
	}


	// Dot product
	template<class T>
	inline T QuaternionSoft<T>::Dot(const QuaternionSoft<T>& op) const
	{
		return x * x + y * y + z * z + w * w;
	}

	template<class T>
	inline void QuaternionSoft<T>::ToMatrix(Matrix3Soft<T>& mat) const
	{
		T x2 = x * 2;
		T y2 = y * 2;
		T z2 = z * 2;
		T wx = x2 * w;
		T wy = y2 * w;
		T wz = z2 * w;
		T xx = x2 * x;
		T xy = y2 * x;
		T xz = z2 * x;
		T yy = y2 * y;
		T yz = z2 * y;
		T zz = z2 * z;
		mat(0, 0) = 1 - (yy + zz);
		mat(0, 1) = xy - wz;
		mat(0, 2) = xz + wy;
		mat(1, 0) = xy + wz;
		mat(1, 1) = 1 - (xx + zz);
		mat(1, 2) = yz - wx;
		mat(2, 0) = xz - wy;
		mat(2, 1) = yz + wx;
		mat(2, 2) = 1 - (xx + yy);
	}

	template<class T>
	inline void QuaternionSoft<T>::ToMatrix(Matrix4Soft<T>& mat) const
	{
		T x2 = x * 2;
		T y2 = y * 2;
		T z2 = z * 2;
		T wx = x2 * w;
		T wy = y2 * w;
		T wz = z2 * w;
		T xx = x2 * x;
		T xy = y2 * x;
		T xz = z2 * x;
		T yy = y2 * y;
		T yz = z2 * y;
		T zz = z2 * z;
		mat(0, 0) = 1 - (yy + zz);
		mat(0, 1) = xy - wz;
		mat(0, 2) = xz + wy;
		mat(0, 3) = 0.0f;
		mat(1, 0) = xy + wz;
		mat(1, 1) = 1 - (xx + zz);
		mat(1, 2) = yz - wx;
		mat(1, 3) = 0.0f;
		mat(2, 0) = xz - wy;
		mat(2, 1) = yz + wx;
		mat(2, 2) = 1 - (xx + yy);
		mat(2, 3) = 0.0f;
		mat(3, 0) = 0.0f;
		mat(3, 1) = 0.0f;
		mat(3, 2) = 0.0f;
		mat(3, 3) = 1.0f;
	}


	template<class T>
	inline Vector3Soft<T> QuaternionSoft<T>::RotateVector(const Vector3Soft<T>& v)
	{
		const QuaternionSoft<T>& q = *this;

		//*this = q * QuaternionSoft(x,y,z,0) * q.GetConjugate();
		return Vector3Soft<T>(
			2 * (q.w*v.z*q.y + q.x*v.z*q.z - q.w*v.y*q.z + q.x*v.y*q.y) + v.x*(q.w*q.w + q.x*q.x - q.y*q.y - q.z*q.z),
			2 * (q.w*v.x*q.z + q.x*v.x*q.y - q.w*v.z*q.x + q.y*v.z*q.z) + v.y*(q.w*q.w - q.x*q.x + q.y*q.y - q.z*q.z),
			2 * (q.w*v.y*q.x - q.w*v.x*q.y + q.x*v.x*q.z + q.y*v.y*q.z) + v.z*(q.w*q.w - q.x*q.x - q.y*q.y + q.z*q.z)
			);
	}

	template<class T>
	inline Vector4Soft<T> QuaternionSoft<T>::RotateVector(const Vector4Soft<T>& v)
	{
		const QuaternionSoft<T>& q = *this;

		//*this = q * QuaternionSoft(x,y,z,0) * q.GetConjugate();
		return Vector4Soft<T>(
			2 * (q.w*v.z*q.y + q.x*v.z*q.z - q.w*v.y*q.z + q.y*v.y*q.x) + v.x*(q.w*q.w + q.x*q.x - q.y*q.y - q.z*q.z),
			2 * (q.w*v.x*q.z + q.x*v.x*q.y - q.w*v.z*q.x + q.y*v.z*q.z) + v.y*(q.w*q.w - q.x*q.x + q.y*q.y - q.z*q.z),
			2 * (q.w*v.y*q.x + q.x*v.x*q.z - q.w*v.x*q.y + q.y*v.y*q.z) + v.z*(q.w*q.w - q.x*q.x - q.y*q.y + q.z*q.z),
			v.w
			);
	}


	//template<class T>
	//inline void QuaternionSoft<T>::ToEulerXYZ(Vector3Soft<T> & r)
	//{

	//}

	//template<class T>
	//inline void QuaternionSoft<T>::ToEulerXYZ(T* r)
	//{

	//}

	//template<class T>
	//inline void QuaternionSoft<T>::FromEulerXYZ(const Vector3Soft<T>& r)
	//{

	//}

	template<class T>
	inline void QuaternionSoft<T>::FromAxisAngle(const Vector4Soft<T>& axis)
	{
		auto angle = axis.w / T(2.0);
		auto axis3 = Vector3Soft<T>(axis);
		axis3.Normalize();
		auto sinHalfTheta = sin(angle);
		x = (T)(axis3.x * sinHalfTheta);
		y = (T)(axis3.y * sinHalfTheta);
		z = (T)(axis3.z * sinHalfTheta);
		w = (T)(cos(angle));
	}

	template<class T>
	inline void QuaternionSoft<T>::FromMatrix(const Matrix3Soft<T>& mat)
	{
		//*this = mat.ToQuaternion();
		T trace = mat(0, 0) + mat(1, 1) + mat(2, 2);
		if (trace > T(0))
		{
			T Scale = sqrtf(trace + T(1));
			w = T(0.5) * Scale;
			Scale = T(0.5) / Scale;
			x = Scale * (mat(2, 1) - mat(1, 2));
			y = Scale * (mat(0, 2) - mat(2, 0));
			z = Scale * (mat(1, 0) - mat(0, 1));
		}
		else
		{
			static int next[] = { 1, 2, 0 };
			int i = 0;
			if (mat(1, 1) > mat(0, 0))
				i = 1;
			if (mat(2, 2) > mat(i, i))
				i = 2;
			int j = next[i];
			int k = next[j];
			T Scale = sqrtf(mat(i, i) - mat(j, j) - mat(k, k) + 1);
			T* q[] = { &x, &y, &z };
			*q[i] = 0.5f * Scale;
			Scale = 0.5f / Scale;
			w = Scale * (mat(k, j) - mat(j, k));
			*q[j] = Scale * (mat(j, i) + mat(i, j));
			*q[k] = Scale * (mat(k, i) + mat(i, k));
		}
	}

	template<class T>
	inline void QuaternionSoft<T>::FromMatrix(const Matrix4Soft<T>& mat)
	{
		*this = mat.ToQuaternion();
	}


	//template<class T>
	//inline  QuaternionSoft<T> operator*(const QuaternionSoft<T>& q1, const QuaternionSoft<T>& q2)
	//{
	//	QuaternionSoft<T> p;
	//	QuaternionSoft<T> t1, t2;

	//	t1 = q1;
	//	t1.x *= q2.w;
	//	t1.y *= q2.w;
	//	t1.z *= q2.w;

	//	t2 = q2;
	//	t2.x *= q1.w;
	//	t2.y *= q1.w;
	//	t2.z *= q1.w;

	//	p.x = (q2.y * q1.z) - (q2.z * q1.y) + t1.x + t2.x;
	//	p.y = (q2.z * q1.x) - (q2.x * q1.z) + t1.y + t2.y;
	//	p.z = (q2.x * q1.y) - (q2.y * q1.x) + t1.z + t2.z;
	//	p.w = q1.w * q2.w - (q1.x * q2.x + q1.y * q2.y + q1.z * q2.z);

	//	return p;
	//}



	template<class T>
	// spherical interpolation between this and q2
	inline QuaternionSoft<T> QuaternionSoft<T>::Slerp(T s, const QuaternionSoft<T> & q2)
	{
		auto& q1 = *this;
		QuaternionSoft<T> p;

		T cosine = q1.Dot(q2);

		if (cosine < -1)
			cosine = -1;
		else if (cosine > 1)
			cosine = 1;

		T angle = (T)acosf(cosine);
		if (fabs(angle) < std::numeric_limits<float>::epsilon())
		{
			p = q1;
			return p;
		}

		T sine = (T)sin(angle);
		T sineInv = 1.0f / sine;
		T c1 = (T)(sin((1.0f - s) * angle) * sineInv);
		T c2 = (T)(sin(s * angle) * sineInv);
		p.x = c1 * q1.x + c2 * q2.x;
		p.y = c1 * q1.y + c2 * q2.y;
		p.z = c1 * q1.z + c2 * q2.z;
		p.w = c1 * q1.w + c2 * q2.w;

		return p;
	}


	// Dual Quaternions
	template<class T>
	inline void QuaternionSoft<T>::MakeDualQuaternion(const QuaternionSoft<T>& q0, const Vector4Soft<T>& t, QuaternionSoft<T> dq[2])
	{
		// non-dual part
		dq[0] = q0;

		// dual part:
		dq[1][0] = (T)(-0.5)*(t[0] * q0[1] + t[1] * q0[2] + t[2] * q0[3]);
		dq[1][1] = (T)(0.5)*(t[0] * q0[0] + t[1] * q0[3] - t[2] * q0[2]);
		dq[1][2] = (T)(0.5)*(-t[0] * q0[3] + t[1] * q0[0] + t[2] * q0[1]);
		dq[1][3] = (T)(0.5)*(t[0] * q0[2] - t[1] * q0[1] + t[2] * q0[0]);
	}

	// Dual Quaternion to rot/trans 
	template<class T>
	inline void QuaternionSoft<T>::DecomposeDualQuaternionNoScale(const QuaternionSoft<T> dq[2], QuaternionSoft<T>& q0, Vector4Soft<T>& t)
	{
		// regular quaternion (just copy the non-dual part):
		q0 = dq[0];

		// translation vector:
		t[0] = T(2)*(-dq[1][0] * dq[0][1] + dq[1][1] * dq[0][0] - dq[1][2] * dq[0][3] + dq[1][3] * dq[0][2]);
		t[1] = T(2)*(-dq[1][0] * dq[0][2] + dq[1][1] * dq[0][3] + dq[1][2] * dq[0][0] - dq[1][3] * dq[0][1]);
		t[2] = T(2)*(-dq[1][0] * dq[0][3] - dq[1][1] * dq[0][2] + dq[1][2] * dq[0][1] + dq[1][3] * dq[0][0]);
	}

	// Dual Quaternion to rot/trans with normalization
	template<class T>
	inline void QuaternionSoft<T>::DecomposeDualQuaternion(const QuaternionSoft<T> dq[2], QuaternionSoft<T>& q0, Vector4Soft<T>& t)
	{
		float len = dq[0].Dot(dq[0]);
		len = sqrt(len);

		q0 = dq[0] / len;

		t[0] = T(2)*(-dq[1][0] * dq[0][1] + dq[1][1] * dq[0][0] - dq[1][2] * dq[0][3] + dq[1][3] * dq[0][2]) / len;
		t[1] = T(2)*(-dq[1][0] * dq[0][2] + dq[1][1] * dq[0][3] + dq[1][2] * dq[0][0] - dq[1][3] * dq[0][1]) / len;
		t[2] = T(2)*(-dq[1][0] * dq[0][3] - dq[1][1] * dq[0][2] + dq[1][2] * dq[0][1] + dq[1][3] * dq[0][0]) / len;
	}

}





