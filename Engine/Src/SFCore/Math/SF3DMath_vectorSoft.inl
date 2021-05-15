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


namespace SF {


	template<class T>
	inline constexpr Vector2Soft<T>::Vector2Soft(const Vector3Soft<T>& u)
	{
		x = u.x;
		y = u.y;
	}

	template<class T>
	inline constexpr Vector2Soft<T>::Vector2Soft(const Vector4Soft<T>& u)
	{
		x = u.x;
		y = u.y;
	}

	template<class T>
	inline Vector2Soft<T> Vector2Soft<T>::operator*(const Vector2Soft<T> & op) const
	{
		return Vector2Soft<T>(x * op.x, y * op.y);
	}

	template<class T>
	inline Vector2Soft<T> Vector2Soft<T>::operator/(const Vector2Soft<T> & op) const
	{
		return Vector2Soft<T>(x / op.x, y / op.y);
	}

	template<class T>
	inline Vector2Soft<T> Vector2Soft<T>::operator-(const Vector2Soft & op) const
	{
		return Vector2Soft<T>(x - op.x, y - op.y);
	}

	template<class T>
	inline Vector2Soft<T> Vector2Soft<T>::operator+(const Vector2Soft & op) const
	{
		return Vector2Soft<T>(x + op.x, y + op.y);
	}

	template<class T>
	inline bool Vector2Soft<T>::operator==(const Vector2Soft & u) const
	{
		return (u.x == x && u.y == y) ? true : false;
	}

	template<class T>
	inline bool Vector2Soft<T>::operator!=(const Vector2Soft & u) const
	{
		return !(*this == u);
	}

	template<class T>
	inline Vector2Soft<T> & Vector2Soft<T>::operator*=(const T & lambda)
	{
		x *= lambda;
		y *= lambda;
		return *this;
	}


	template<class T>
	inline Vector2Soft<T> & Vector2Soft<T>::operator/=(const T & lambda)
	{
		x /= lambda;
		y /= lambda;
		return *this;
	}

	template<class T>
	inline Vector2Soft<T> & Vector2Soft<T>::operator-=(const Vector2Soft & u)
	{
		x -= u.x;
		y -= u.y;
		return *this;
	}

	template<class T>
	inline Vector2Soft<T> & Vector2Soft<T>::operator+=(const Vector2Soft & u)
	{
		x += u.x;
		y += u.y;
		return *this;
	}

	template<class T>
	inline T & Vector2Soft<T>::operator[](int i)
	{
		return Elements[i];
	}

	template<class T>
	inline const T& Vector2Soft<T>::operator[](int i) const
	{
		return Elements[i];
	}


	template<>
	inline Vector2Soft<unsigned int> Vector2Soft<unsigned int>::operator - () const
	{
		return Vector2Soft<unsigned int>(x, y);
	}

	template<class T>
	inline T Vector2Soft<T>::Normalize()
	{
		T norm = Length();
		if (norm > C_EPSILON)
			norm = T(1) / norm;
		else
			norm = T(0);

		*this *= norm;

		return norm;
	}

	template<class T>
	inline Vector2Soft<T> Vector2Soft<T>::GetAbs() const
	{
		return Vector2Soft<T>((T)Math::Abs(x), (T)Math::Abs(y));
	}

	template<>
	inline Vector2Soft<unsigned int> Vector2Soft<unsigned int>::GetAbs() const
	{
		return *this;
	}



	////////////////////////////////////////////////////////////////////////////////////
	//
	//	Vector3Soft
	//

	template<class T>
	inline Vector3Soft<T>::Vector3Soft(const Vector4Soft<T>& u)
	{
		x = u.x;
		y = u.y;
		z = u.z;
	}


	template<class T>
	inline Vector3Soft<T> Vector3Soft<T>::operator*(const Matrix3Soft<T> & M) const
	{
		const Vector3Soft<T> &v = *this;
		Vector3Soft<T> res;

		res.x = M.a00 * v.x + M.a10 * v.y + M.a20 * v.z;
		res.y = M.a01 * v.x + M.a11 * v.y + M.a21 * v.z;
		res.z = M.a02 * v.x + M.a12 * v.y + M.a22 * v.z;

		return res;
	}

	template<class T>
	inline Vector3Soft<T> & Vector3Soft<T>::operator*=(const Matrix3Soft<T> & M)
	{
		Vector3Soft<T> v(*this);

		x = M.a00 * v.x + M.a10 * v.y + M.a20 * v.z;
		y = M.a01 * v.x + M.a11 * v.y + M.a21 * v.z;
		z = M.a02 * v.x + M.a12 * v.y + M.a22 * v.z;

		return (*this);
	}

	template<class T>
	inline Vector3Soft<T> Vector3Soft<T>::operator*(const Matrix4Soft<T> & M) const
	{
		const Vector3Soft<T> &v = *this;
		Vector3Soft<T> res;
		// assume w = 1
		res.x = (T)(M.a00 * v.x + M.a10 * v.y + M.a20 * v.z + M.a30);
		res.y = (T)(M.a01 * v.x + M.a11 * v.y + M.a21 * v.z + M.a31);
		res.z = (T)(M.a02 * v.x + M.a12 * v.y + M.a22 * v.z + M.a32);
		//res.w = M.a03 * v.x + M.a13 * v.y + M.a23 * v.z + M.a33 * 1;

		return res;
	}

	template<class T>
	inline Vector3Soft<T> & Vector3Soft<T>::operator*=(const Matrix4Soft<T> & M)
	{
		Vector3Soft<T> v(*this);
		// assume w = 1
		x = (T)(M.a00 * v.x + M.a10 * v.y + M.a20 * v.z + M.a30);
		y = (T)(M.a01 * v.x + M.a11 * v.y + M.a21 * v.z + M.a31);
		z = (T)(M.a02 * v.x + M.a12 * v.y + M.a22 * v.z + M.a32);
		//w = M.a03 * v.x + M.a13 * v.y + M.a23 * v.z + M.a33 * 1;

		return (*this);
	}

	template<class T>
	inline Vector3Soft<T> & Vector3Soft<T>::operator/=(const Vector3Soft<T> & d)
	{
		x /= d.x;
		y /= d.y;
		z /= d.z;
		return *this;
	}

	template<class T>
	inline Vector3Soft<T> operator* (const T & scala, const Vector3Soft<T>& v)
	{
		return Vector3Soft<T>(v.x * scala, v.y * scala, v.z * scala);
	}

	template<class T>
	inline Vector3Soft<T> Vector3Soft<T>::operator*(const T & lambda) const
	{
		return Vector3Soft<T>(x * lambda, y * lambda, z * lambda);
	}

	template<class T>
	inline Vector3Soft<T> & Vector3Soft<T>::operator*=(const T & lambda)
	{
		x *= lambda;
		y *= lambda;
		z *= lambda;
		return *this;
	}

	template<class T>
	inline Vector3Soft<T> operator/ (const T & lambda, const Vector3Soft<T>& v)
	{
		return Vector3Soft<T>(lambda / v.x, lambda / v.y, lambda / v.z);
	}

	template<class T>
	inline Vector3Soft<T> Vector3Soft<T>::operator/(const T & lambda) const
	{
		return Vector3Soft<T>(x / lambda, y / lambda, z / lambda);
	}

	template<class T>
	inline Vector3Soft<T> & Vector3Soft<T>::operator/=(const T & lambda)
	{
		x /= lambda;
		y /= lambda;
		z /= lambda;
		return *this;
	}

	template<class T>
	inline Vector3Soft<T> & Vector3Soft<T>::operator*=(const Vector3Soft<T> & v)
	{
		x *= v.x;
		y *= v.y;
		z *= v.z;
		return *this;
	}

	template<class T>
	inline Vector3Soft<T> Vector3Soft<T>::operator - () const
	{
		return Vector3Soft<T>(-x, -y, -z);
	}

	template<>
	inline Vector3Soft<unsigned int> Vector3Soft<unsigned int>::operator - () const
	{
		return Vector3Soft<unsigned int>((unsigned int)-(int)x, (unsigned int)-(int)y, (unsigned int)-(int)z);
	}

	template<class T>
	inline Vector3Soft<T> Vector3Soft<T>::operator-(const Vector3Soft<T> & u) const
	{
		return Vector3Soft<T>(x - u.x, y - u.y, z - u.z);
	}

	template<class T>
	inline Vector3Soft<T> Vector3Soft<T>::operator+(const Vector3Soft<T> & u) const
	{
		return Vector3Soft<T>(x + u.x, y + u.y, z + u.z);
	}



	template<class T>
	inline Vector3Soft<T> & Vector3Soft<T>::operator-=(const Vector3Soft<T> & u)
	{
		x -= u.x;
		y -= u.y;
		z -= u.z;
		return *this;
	}

	template<class T>
	inline Vector3Soft<T> & Vector3Soft<T>::operator+=(const Vector3Soft<T> & u)
	{
		x += u.x;
		y += u.y;
		z += u.z;
		return *this;
	}


	template<class T>
	inline void Vector3Soft<T>::Orthogonalize(const Vector3Soft<T>& v)
	{
		Vector3Soft<T> res = Dot(v) * v;
		x -= res.x;
		y -= res.y;
		z -= res.y;
	}

	template<class T>
	inline T Vector3Soft<T>::Length() const
	{
		return (T)sqrt((double)SquareLength());
	}

	template<>
	inline int Vector3Soft<int>::Length() const
	{
		return (int)sqrt(SquareLength());
	}

	template<class T>
	inline Vector3Soft<T> Vector3Soft<T>::GetAbs() const
	{
		return Vector3Soft<T>((T)Math::Abs(x), (T)Math::Abs(y), (T)Math::Abs(z));
	}

	template<>
	inline Vector3Soft<unsigned int> Vector3Soft<unsigned int>::GetAbs() const
	{
		return *this;
	}

	template<class T>
	Vector3Soft<T> Vector3Soft<T>::Cross(const Vector3Soft<T>& op) const
	{
		return Vector3Soft<T>(y * op.z - z * op.y, z * op.x - x * op.z, x * op.y - y * op.x);
	}

	template<class T>
	Vector4Soft<T> Vector3Soft<T>::Cross(const Vector4Soft<T>& op) const
	{
		return Vector4Soft<T>(y * op.z - z * op.y, z * op.x - x * op.z, x * op.y - y * op.x);
	}


	template<class T>
	inline Vector3Soft<T> & Vector3Soft<T>::RotateBy(const QuaternionSoft<T>& q)
	{
		Vector3Soft<T> v(*this);

		//*this = q * QuaternionSoft(x,y,z,0) * q.GetConjugate();
		x = 2 * (q.w*v.z*q.y + q.x*v.z*q.z - q.w*v.y*q.z + q.x*v.y*q.y) + v.x*(q.w*q.w + q.x*q.x - q.y*q.y - q.z*q.z);
		y = 2 * (q.w*v.x*q.z + q.x*v.x*q.y - q.w*v.z*q.x + q.y*v.z*q.z) + v.y*(q.w*q.w - q.x*q.x + q.y*q.y - q.z*q.z);
		z = 2 * (q.w*v.y*q.x - q.w*v.x*q.y + q.x*v.x*q.z + q.y*v.y*q.z) + v.z*(q.w*q.w - q.x*q.x - q.y*q.y + q.z*q.z);

		return (*this);
	}


	template<class T>
	inline Vector3Soft<T>& Vector3Soft<T>::MAdd(const T& scala)
	{
		x += x * scala;
		y += y * scala;
		z += z * scala;
		return *this;
	}


	template<class T>
	inline T Vector3Soft<T>::Normalize()
	{
		T norm = Length();
		if (norm > C_EPSILON)
			norm = T(1) / norm;
		else
			norm = T(0);

		*this *= norm;

		return norm;
	}



	/////////////////////////////////////////////////////////////////////////////
	//
	//	Vector4Soft
	//


	// returns orthogonal length
	template<class T>
	inline void Vector4Soft<T>::Normalize4()
	{
		auto length = sqrt(x * x + y * y + z * z + w * w);
		if (length > C_EPSILON)
		{
			auto invLength = T(1) / length;
			x = T(x *invLength);
			y = T(y *invLength);
			z = T(z *invLength);
			w = T(w *invLength);
		}
		else
		{
			assert(false);
			x = y = z = w = 0;
		}
	}

	template<class T>
	inline void Vector4Soft<T>::Normalize3()
	{
		Normalize3Hi();
	}

	template<class T>
	inline T Vector4Soft<T>::Normalize3Hi()
	{
		auto length = Length3();
		if (length > C_EPSILON)
		{
			auto invLength = T(1) / length;
			x = T(x *invLength);
			y = T(y *invLength);
			z = T(z *invLength);
			w = 0;
		}
		else
		{
			assert(false);
			x = y = z = 0;
			w = 0;
		}

		return (T)length;
	}


	template<class T>
	inline Vector4Soft<T> Vector4Soft<T>::GetAbs() const
	{
		return Vector4Soft<T>((T)Math::Abs(x), (T)Math::Abs(y), (T)Math::Abs(z), (T)Math::Abs(w));
	}

	template<>
	inline Vector4Soft<unsigned int> Vector4Soft<unsigned int>::GetAbs() const
	{
		return *this;
	}

	template<class T>
	inline Vector4Soft<T>& Vector4Soft<T>::MAdd(const T& scala)
	{
		x = (T)(x + x * scala);
		y = (T)(y + y * scala);
		z = (T)(z + z * scala);
		w = (T)(w + w * scala);
		return *this;
	}

	template<class T>
	inline Vector4Soft<T> Vector4Soft<T>::operator*(const Matrix3Soft<T> & M) const
	{
		const Vector4Soft<T> &v = *this;
		Vector4Soft<T> res;

		res.x = T(M.a00 * v.x + M.a10 * v.y + M.a20 * v.z);
		res.y = T(M.a01 * v.x + M.a11 * v.y + M.a21 * v.z);
		res.z = T(M.a02 * v.x + M.a12 * v.y + M.a22 * v.z);

		return res;
	}

	template<class T>
	inline Vector4Soft<T> & Vector4Soft<T>::operator*=(const Matrix3Soft<T> & M)
	{
		Vector4Soft<T> v(*this);

		x = T(M.a00 * v.x + M.a10 * v.y + M.a20 * v.z);
		y = T(M.a01 * v.x + M.a11 * v.y + M.a21 * v.z);
		z = T(M.a02 * v.x + M.a12 * v.y + M.a22 * v.z);

		return (*this);
	}

	template<class T>
	inline Vector4Soft<T> Vector4Soft<T>::operator*(const Matrix4Soft<T> & M) const
	{
		const Vector4Soft<T> &v = *this;
		Vector4Soft<T> res;

		res.x = T(M.a00 * v.x + M.a10 * v.y + M.a20 * v.z + M.a30 * w);
		res.y = T(M.a01 * v.x + M.a11 * v.y + M.a21 * v.z + M.a31 * w);
		res.z = T(M.a02 * v.x + M.a12 * v.y + M.a22 * v.z + M.a32 * w);
		res.w = T(M.a03 * v.x + M.a13 * v.y + M.a23 * v.z + M.a33 * w);

		return res;
	}

	template<class T>
	inline Vector4Soft<T> & Vector4Soft<T>::operator*=(const Matrix4Soft<T> & M)
	{
		Vector4Soft<T> v(*this);

		x = T(M.a00 * v.x + M.a10 * v.y + M.a20 * v.z + M.a30 * w);
		y = T(M.a01 * v.x + M.a11 * v.y + M.a21 * v.z + M.a31 * w);
		z = T(M.a02 * v.x + M.a12 * v.y + M.a22 * v.z + M.a32 * w);
		w = T(M.a03 * v.x + M.a13 * v.y + M.a23 * v.z + M.a33 * w);

		return (*this);
	}

	template<class T>
	inline Vector4Soft<T> Vector4Soft<T>::operator/(const T & scala) const
	{
		return Vector4Soft<T>(T(x / scala),
			T(y / scala),
			T(z / scala),
			T(w / scala));
	}

	template<class T>
	inline Vector4Soft<T>  Vector4Soft<T>::operator*(const T & scala) const
	{
		return Vector4Soft<T>(T(x * scala),
			T(y * scala),
			T(z * scala),
			T(w * scala));
	}

	template<class T>
	inline Vector4Soft<T>&  Vector4Soft<T>::operator/=(const T & scala)
	{
		x = T(x / scala);
		y = T(y / scala);
		z = T(z / scala);
		w = T(w / scala);
		return *this;
	}

	template<class T>
	inline Vector4Soft<T> & Vector4Soft<T>::operator*=(const T & scala)
	{
		x = T(x *scala);
		y = T(y *scala);
		z = T(z *scala);
		w = T(w *scala);
		return *this;
	}

	template<class T>
	inline Vector4Soft<T> & Vector4Soft<T>::operator-=(const Vector4Soft<T> & u)
	{
		x = T(x - u.x);
		y = T(y - u.y);
		z = T(z - u.z);
		w = T(w - u.w);
		return *this;
	}

	template<class T>
	inline Vector4Soft<T> & Vector4Soft<T>::operator+=(const Vector4Soft<T> & u)
	{
		x = T(x + u.x);
		y = T(y + u.y);
		z = T(z + u.z);
		w = T(w + u.w);
		return *this;
	}


	template<class T>
	inline Vector4Soft<T> Vector4Soft<T>::operator-(const Vector4Soft<T> & u) const
	{
		// assume Vector3Soft
		return Vector4Soft<T>(x - u.x, y - u.y, z - u.z, w);
	}

	template<class T>
	inline Vector4Soft<T> Vector4Soft<T>::operator+(const Vector4Soft<T> & u) const
	{
		// assume Vector3Soft
		return Vector4Soft<T>(x + u.x, y + u.y, z + u.z, w);
	}

	template<class T>
	inline Vector4Soft<T> Vector4Soft<T>::operator*(const Vector4Soft<T> & u) const
	{
		// assume Vector3Soft
		return Vector4Soft<T>(x * u.x, y * u.y, z * u.z, w);
	}

	template<class T>
	inline Vector4Soft<T> Vector4Soft<T>::operator/(const Vector4Soft<T> & u) const
	{
		// assume Vector3Soft
		return Vector4Soft<T>(x / u.x, y / u.y, z / u.z, w);
	}

	template<class T>
	inline Vector4Soft<T> Normalize(const Vector4Soft<T>& v)
	{
		Vector4Soft<T> u(v);
		T norm = sqrtf(u.x * u.x + u.y * u.y + u.z * u.z + u.w * u.w);
		if (norm > C_EPSILON)
			norm = T(1) / norm;
		else
			norm = T(0);
		return Scale(u, norm);
	}

	template<>
	inline Vector4Soft<unsigned int> Vector4Soft<unsigned int>::operator - () const
	{
		return Vector4Soft<unsigned int>(x, y, z, w);
	}


}





