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


#ifndef _WIN32
#define _isnan isnan
#define _finite finite
#endif

namespace SF {



	template<class T>
	inline Vector3Soft<T> Reflect(const Vector3Soft<T>& n, const Vector3Soft<T>& l)
	{
		Vector3Soft<T> r;

		auto n_dot_l = -2.0 * Dot(n, l);
		r = n_dot_l * n + l;

		return r;
	}



	template<class T>
	inline Matrix4Soft<T> MakeLookAtMatrix(const Vector3Soft<T>& eye, const Vector3Soft<T>& center, const Vector3Soft<T>& up)
	{
		Matrix4Soft<T> M;
		Vector3Soft<T> x, y, z;

		// Z Vector
		z.x = eye.x - center.x;
		z.y = eye.y - center.y;
		z.z = eye.z - center.z;
		z.Normalize();

		// Y Vector
		y.x = up.x;
		y.y = up.y;
		y.z = up.z;

		// X Vector = Y Cross Z
		x = y.Cross(z);

		// Recompute Y = Z Cross X
		y = z.Cross(x);

		// Cross product gives area of parallelogram, which is < 1.0 for
		// non-perpendicular unit-length Vectors; so Normalize x, y here
		x.Normalize();
		y.Normalize();

		M.a00 = x.x; M.a01 = x.y; M.a02 = x.z; M.a03 = -x.x * eye.x - x.y * eye.y - x.z*eye.z;
		M.a10 = y.x; M.a11 = y.y; M.a12 = y.z; M.a13 = -y.x * eye.x - y.y * eye.y - y.z*eye.z;
		M.a20 = z.x; M.a21 = z.y; M.a22 = z.z; M.a23 = -z.x * eye.x - z.y * eye.y - z.z*eye.z;
		M.a30 = T(0); M.a31 = T(0); M.a32 = T(0); M.a33 = T(1);
		return M;
	}

	template<class T>
	inline Matrix4Soft<T> MakeFrustumMatrix(const T l, const T r, const T b,
	  const T t, const T n, const T f)
	{
		Matrix4Soft<T> M;
		M.a00 = (T(2)*n) / (r-l);
		M.a10 = 0.0;
		M.a20 = 0.0;
		M.a30 = 0.0;

		M.a01 = 0.0;
		M.a11 = (T(2)*n) / (t-b);
		M.a21 = 0.0;
		M.a31 = 0.0;

		M.a02 = (r+l) / (r-l);
		M.a12 = (t+b) / (t-b);
		M.a22 = -(f+n) / (f-n);
		M.a32 = -T(1);

		M.a03 = 0.0;
		M.a13 = 0.0;
		M.a23 = -(T(2)*f*n) / (f-n);
		M.a33 = 0.0;
		return M;
	}

	template<class T>
	inline Matrix4Soft<T> MakePerspectiveMatrix(const T fovy, const T aspect, const T n, const T f)
	{
		T xmin, xmax, ymin, ymax;

		ymax = n * tanf(fovy * nv_to_rad * T(0.5));
		ymin = -ymax;

		xmin = ymin * aspect;
		xmax = ymax * aspect;

		return frustum(xmin, xmax, ymin, ymax, n, f);
	}

	template<class T>
	inline Matrix4Soft<T> MakeOrthoMatrix(const T left,
	  const T right, 
	  const T bottom, 
	  const T top,
	  const T n,
	  const T f)
	{
		Matrix4Soft<T> M;
		M.a00 = T(2) / (right - left);
		M.a01 = T(0);
		M.a02 = T(0);
		M.a03 = - (right + left) / (right - left);
		M.a10 = T(0);
		M.a11 = T(2) / (top - bottom);
		M.a12 = T(0);
		M.a13 = - (top + bottom) / (top - bottom);
		M.a20 = T(0);
		M.a21 = T(0);
		M.a22 = - T(2) / (f - n);
		M.a23 = - (f + n) / (f - n);
		M.a30 = T(0);
		M.a31 = T(0);
		M.a32 = T(0);
		M.a33 = T(1);
		return M;
	}



	template<class T>
	inline Matrix4Soft<T> MakeRotationYawPitchRoll( const T yaw , const T pitch , const T roll )
	{
		Matrix4Soft<T> M;
		M.identity();
		Matrix4Soft<T> rot;

		if (roll)
		{
			M.Rotate(roll, Vector3Soft<T>(0,0,1));
		}
		if (pitch)
		{
			M.Rotate(pitch, Vector3Soft<T>(1,0,0));
		}
		if (yaw)
		{
			M.Rotate(yaw, Vector3Soft<T>(0,1,0));
		}

		return M;
	}


} //namespace SF
