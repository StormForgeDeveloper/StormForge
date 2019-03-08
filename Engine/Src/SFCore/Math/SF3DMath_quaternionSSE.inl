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



	
	inline QuaternionSSE::QuaternionSSE(const Vector4SSE& axisAngle)
	{
		FromAxisAngle(axisAngle);
	}

	
	inline QuaternionSSE::QuaternionSSE(const Matrix4SSE& rot)
	{
		(*this) = rot;
	}

	
	inline QuaternionSSE& QuaternionSSE::operator=(const QuaternionSSE& q)
	{
		Packed = q.Packed;
		return *this;
	}


	
	inline QuaternionSSE& QuaternionSSE::operator=(const Matrix4SSE& mat)
	{
		*this = mat.ToQuaternion();
		return *this;
	}


	
	inline QuaternionSSE QuaternionSSE::operator * (const QuaternionSSE& q)
	{
		auto sign = _mm_set_ps(-1,1,1,1);
		auto accmulate = _mm_mul_ps(_mm_shuffle_ps(Packed, Packed, _MM_SHUFFLE(3, 3, 3, 3)), q.Packed);
		accmulate = _mm_add_ps(accmulate, _mm_mul_ps(sign, _mm_mul_ps(_mm_shuffle_ps(Packed, Packed, _MM_SHUFFLE(0, 0, 1, 0)), _mm_shuffle_ps(q.Packed, q.Packed, _MM_SHUFFLE(0, 1, 3, 3)))) );
		accmulate = _mm_add_ps(accmulate, _mm_mul_ps(sign, _mm_mul_ps(_mm_shuffle_ps(Packed, Packed, _MM_SHUFFLE(1, 2, 2, 1)), _mm_shuffle_ps(q.Packed, q.Packed, _MM_SHUFFLE(1, 3, 0, 2)))) );
		accmulate = _mm_sub_ps(accmulate, _mm_mul_ps(_mm_shuffle_ps(Packed, Packed, _MM_SHUFFLE(2, 1, 0, 2)), _mm_shuffle_ps(q.Packed, q.Packed, _MM_SHUFFLE(2, 0, 2, 1))));
		return QuaternionSSE(
			accmulate
			//w * q.x + x * q.w + y * q.z - z * q.y,
			//w * q.y + y * q.w + z * q.x - x * q.z,
			//w * q.z + x * q.y + z * q.w - y * q.x,
			//w * q.w - x * q.x - y * q.y - z * q.z
			);
	}

	
	inline QuaternionSSE& QuaternionSSE::operator *= (const QuaternionSSE& q)
	{
		(*this) = (*this) * q;
		return *this;
	}


	inline QuaternionSSE QuaternionSSE::operator-(float scala) const
	{
		return QuaternionSSE(_mm_sub_ps(Packed,_mm_set1_ps(scala)));
	}

	inline QuaternionSSE QuaternionSSE::operator + (float scala) const
	{
		return QuaternionSSE(_mm_add_ps(Packed, _mm_set1_ps(scala)));
	}

	inline QuaternionSSE QuaternionSSE::operator * (float scala) const
	{
		return QuaternionSSE(_mm_mul_ps(Packed, _mm_set1_ps(scala)));
	}

	inline QuaternionSSE QuaternionSSE::operator / (float scala) const
	{
		return QuaternionSSE(_mm_div_ps(Packed, _mm_set1_ps(scala)));
	}



	
	inline QuaternionSSE QuaternionSSE::GetInverse() const
	{
		return QuaternionSSE(_mm_mul_ps(Packed, _mm_set_ps(1,-1,-1,-1)));
	}
	
	inline QuaternionSSE QuaternionSSE::GetConjugate() const
	{
		return QuaternionSSE(_mm_mul_ps(Packed, _mm_set_ps(1, -1, -1, -1)));
	}

	
	inline void QuaternionSSE::Normalize()
	{
#if 0 // This is faster but less accurate
		auto invLen = _mm_rsqrt_ps(_mm_dp_ps(Packed, Packed, 0xFF));
		Packed = _mm_mul_ps(Packed, invLen);
#else
		auto len = _mm_sqrt_ps(_mm_dp_ps(Packed, Packed, 0xFF));
		if (_mm_cvtss_f32(len) < std::numeric_limits<float>::epsilon())
			Packed = _mm_set_ps(1, 0, 0, 0);
		else
			Packed = _mm_div_ps(Packed, len);
#endif
	}

	
	inline Vector4SSE QuaternionSSE::RotateVector(const Vector4SSE& v)
	{
		//const QuaternionSSE& q = *this;

		//*this = q * QuaternionSSE(x,y,z,0) * q.GetConjugate();

		auto qx = _SF_SWIZZLE1(Packed, 0);
		auto qy = _SF_SWIZZLE1(Packed, 1);
		auto qz = _SF_SWIZZLE1(Packed, 2);
		auto qw = _SF_SWIZZLE1(Packed, 3);

		auto resLeft =                _mm_mul_ps(_mm_mul_ps(qw, _SF_SWIZZLE(v.Packed, 3, 1, 0, 2)), _SF_SWIZZLE(Packed, 3, 0, 2, 1));
		resLeft = _mm_add_ps(resLeft, _mm_mul_ps(_mm_mul_ps(qx, _SF_SWIZZLE(v.Packed, 3, 0, 0, 2)), _SF_SWIZZLE(Packed, 3, 2, 1, 2)));
		resLeft = _mm_sub_ps(resLeft, _mm_mul_ps(_mm_mul_ps(qw, _SF_SWIZZLE(v.Packed, 3, 0, 2, 1)), _SF_SWIZZLE(Packed, 3, 1, 0, 2)));
		resLeft = _mm_add_ps(resLeft, _mm_mul_ps(_mm_mul_ps(qy, _SF_SWIZZLE(v.Packed, 3, 1, 2, 1)), _SF_SWIZZLE(Packed, 3, 2, 2, 0)));
		resLeft = _mm_mul_ps(resLeft, _mm_set_ps(0, 2, 2, 2));

		auto sign = _mm_set_ps(0, 1, -1, 1);
		auto resRight =					_mm_mul_ps(_mm_mul_ps(qw, qw), _SF_SWIZZLE(sign, 3, 0, 0, 0));
		resRight = _mm_add_ps(resRight, _mm_mul_ps(_mm_mul_ps(qx, qx), _SF_SWIZZLE(sign, 3, 1, 1, 0)));
		resRight = _mm_add_ps(resRight, _mm_mul_ps(_mm_mul_ps(qy, qy), _SF_SWIZZLE(sign, 3, 1, 0, 1)));
		resRight = _mm_add_ps(resRight, _mm_mul_ps(_mm_mul_ps(qz, qz), _SF_SWIZZLE(sign, 3, 0, 1, 1)));
		resRight = _mm_add_ps(resRight, _SF_SWIZZLE(sign, 2, 3, 3, 3));
		resRight = _mm_mul_ps(resRight, v.Packed);

		return Vector4SSE(
			_mm_add_ps(resLeft, resRight)
		);
		//return Vector4SSE(
		//	2 * (q.w*v.z*q.y + q.x*v.z*q.z - q.w*v.y*q.z + q.y*v.y*q.x) + v.x*(q.w*q.w + q.x*q.x - q.y*q.y - q.z*q.z),
		//	2 * (q.w*v.x*q.z + q.x*v.x*q.y - q.w*v.z*q.x + q.y*v.z*q.z) + v.y*(q.w*q.w - q.x*q.x + q.y*q.y - q.z*q.z),
		//	2 * (q.w*v.y*q.x + q.x*v.x*q.z - q.w*v.x*q.y + q.y*v.y*q.z) + v.z*(q.w*q.w - q.x*q.x - q.y*q.y + q.z*q.z),
		//	v.w
		//	);
	}

	// Dot product
	inline float QuaternionSSE::Dot(const QuaternionSSE& op) const
	{
		return _mm_cvtss_f32(_mm_dp_ps(Packed, Packed, 0xFF));
	}


	inline void QuaternionSSE::FromAxisAngle(const Vector4SSE& axisAngle)
	{
		float angleh = axisAngle.w / 2;
		float sinA = sinf(angleh);
		float cosA = cosf(angleh);

		auto squlen = _mm_dp_ps(axisAngle.Packed, axisAngle.Packed, 0x7F);
#if 0 // This is faster but less accurate
		auto invLen = _mm_rsqrt_ps(squlen);
		auto scale = _mm_mul_ps(_mm_set_ps(0, sinA, sinA, sinA), invLen);
#else
		auto len = _mm_sqrt_ps(squlen);
		__m128 scale;
		if (_mm_cvtss_f32(len) < std::numeric_limits<float>::epsilon())
			scale = _mm_set1_ps(0);
		else
			scale = _mm_div_ps(_mm_set_ps(0, sinA, sinA, sinA), len);
#endif
		Packed = _mm_add_ps(_mm_mul_ps(scale, axisAngle.Packed), _mm_set_ps(cosA, 0, 0, 0));
		//float Scale = sinf(angle2) * invLen;
		//x = Scale * axisAngle.x;
		//y = Scale * axisAngle.y;
		//z = Scale * axisAngle.z;
		//w = cosf(angle2);
	}

	
	inline void QuaternionSSE::FromMatrix(const Matrix4SSE& mat)
	{
		*this = mat.ToQuaternion();
	}

	
	// spherical interpolation between this and q2
	inline QuaternionSSE QuaternionSSE::Slerp(float s, const QuaternionSSE & q2)
	{
		float cosine = Dot(q2);

		if (cosine < -1)
			cosine = -1;
		else if (cosine > 1)
			cosine = 1;

		float angle = (float)acosf(cosine);
		if (fabs(angle) < std::numeric_limits<float>::epsilon())
		{
			return *this;
		}

		float sine = (float)sin(angle);
		float sineInv = 1.0f / sine;
		//auto c1 = (float)(sin((1.0f - s) * angle));
		//auto c2 = (float)(sin(s * angle));
		auto c1 = _mm_set1_ps((float)(sin((1.0f - s) * angle)));
		auto c2 = _mm_set1_ps((float)(sin(s * angle)));

		//p.x = (c1 * q1.x + c2 * q2.x) * sineInv;
		//p.y = (c1 * q1.y + c2 * q2.y) * sineInv;
		//p.z = (c1 * q1.z + c2 * q2.z) * sineInv;
		//p.w = (c1 * q1.w + c2 * q2.w) * sineInv;
		return QuaternionSSE(
			_mm_mul_ps(_mm_add_ps(_mm_mul_ps(Packed,c1),_mm_mul_ps(q2.Packed,c2)), _mm_set1_ps(sineInv))
		);
	}


	// Dual Quaternions
	inline void QuaternionSSE::MakeDualQuaternion(const QuaternionSSE& q0, const Vector4SSE& t, QuaternionSSE dq[2])
	{
		// non-dual part
		dq[0] = q0;

		// dual part:
#if 0  // Doing in different way
		auto sign = _mm_set_ps(0.5f, 0.5f, 0.5f, -0.5f);

		auto q2x = _mm_cvtss_f32(_mm_dp_ps(_mm_mul_ps(t.Packed, _SF_SWIZZLE(q0.Packed,0,3,2,1)), _SF_SWIZZLE(sign,1, 0, 0, 0), 0x71));
		auto q2y = _mm_cvtss_f32(_mm_dp_ps(_mm_mul_ps(t.Packed, _SF_SWIZZLE(q0.Packed,1,2,3,0)), _SF_SWIZZLE(sign,1, 0, 1, 1), 0x71));
		auto q2z = _mm_cvtss_f32(_mm_dp_ps(_mm_mul_ps(t.Packed, _SF_SWIZZLE(q0.Packed,2,1,0,3)), _SF_SWIZZLE(sign,1, 1, 1, 0), 0x71));
		auto q2w = _mm_cvtss_f32(_mm_dp_ps(_mm_mul_ps(t.Packed, _SF_SWIZZLE(q0.Packed,3,0,1,2)), _SF_SWIZZLE(sign,1, 1, 0, 1), 0x71));

		dq[1].Packed = _mm_set_ps(q2w, q2z, q2y, q2x);
#else
		auto sign = _mm_set_ps(0.5f, 0.5f, 0.5f, -0.5f);

		auto q2 =                _mm_mul_ps(_mm_mul_ps(_SF_SWIZZLE(t.Packed,0,0,0,0), _SF_SWIZZLE(q0.Packed, 2, 3, 0, 1)),  _SF_SWIZZLE(sign, 1, 0, 1, 0));
		q2 =      _mm_add_ps(q2, _mm_mul_ps(_mm_mul_ps(_SF_SWIZZLE(t.Packed,1,1,1,1), _SF_SWIZZLE(q0.Packed, 1, 0, 3, 2)),  _SF_SWIZZLE(sign, 0, 1, 1, 0)) );
		q2 =      _mm_add_ps(q2, _mm_mul_ps(_mm_mul_ps(_SF_SWIZZLE(t.Packed,2,2,2,2), _SF_SWIZZLE(q0.Packed, 0, 1, 2, 3)),  _SF_SWIZZLE(sign, 1, 1, 0, 0)) );

		dq[1].Packed = q2;
#endif
		//dq[1][0] = -0.5*(t[0] * q0[1] + t[1] * q0[2] + t[2] * q0[3]);
		//dq[1][1] = 0.5*(t[0] * q0[0] + t[1] * q0[3] - t[2] * q0[2]);
		//dq[1][2] = 0.5*(-t[0] * q0[3] + t[1] * q0[0] + t[2] * q0[1]);
		//dq[1][3] = 0.5*(t[0] * q0[2] - t[1] * q0[1] + t[2] * q0[0]);
	}

	// Dual Quaternion to rot/trans 
	inline void QuaternionSSE::DecomposeDualQuaternionNoScale(const QuaternionSSE dq[2], QuaternionSSE& q0, Vector4SSE& trans)
	{
		// regular quaternion (just copy the non-dual part):
		q0 = dq[0];

		// translation vector:
		auto sign = _mm_set_ps(0, 2, 2, -2);

		auto q1 = dq[1].Packed;
		auto t =          _mm_mul_ps(_mm_mul_ps(_SF_SWIZZLE(q1, 0, 0, 0, 0), _SF_SWIZZLE(q0.Packed, 2, 3, 2, 1)), _SF_SWIZZLE(sign, 3, 0, 0, 0));
		t = _mm_add_ps(t, _mm_mul_ps(_mm_mul_ps(_SF_SWIZZLE(q1, 1, 1, 1, 1), _SF_SWIZZLE(q0.Packed, 1, 2, 3, 0)), _SF_SWIZZLE(sign, 0, 0, 1, 1)));
		t = _mm_add_ps(t, _mm_mul_ps(_mm_mul_ps(_SF_SWIZZLE(q1, 2, 2, 2, 2), _SF_SWIZZLE(q0.Packed, 0, 1, 0, 3)), _SF_SWIZZLE(sign, 1, 1, 1, 0)));
		t = _mm_add_ps(t, _mm_mul_ps(_mm_mul_ps(_SF_SWIZZLE(q1, 3, 3, 3, 3), _SF_SWIZZLE(q0.Packed, 0, 0, 1, 2)), _SF_SWIZZLE(sign, 1, 1, 0, 1)));

		trans.Packed = t;

		//t[0] = 2.0*(-dq[1][0] * dq[0][1] + dq[1][1] * dq[0][0] - dq[1][2] * dq[0][3] + dq[1][3] * dq[0][2]);
		//t[1] = 2.0*(-dq[1][0] * dq[0][2] + dq[1][1] * dq[0][3] + dq[1][2] * dq[0][0] - dq[1][3] * dq[0][1]);
		//t[2] = 2.0*(-dq[1][0] * dq[0][3] - dq[1][1] * dq[0][2] + dq[1][2] * dq[0][1] + dq[1][3] * dq[0][0]);
	}

	// Dual Quaternion to rot/trans with normalization
	inline void QuaternionSSE::DecomposeDualQuaternion(const QuaternionSSE dq[2], QuaternionSSE& q0, Vector4SSE& trans)
	{
		auto invLen = _mm_rsqrt_ps(_mm_dp_ps(dq[0].Packed, dq[0].Packed, 0xFF));
		//float len = dq[0].Dot(dq[0]);
		//len = sqrt(len);

		//q0 = dq[0] / len;
		q0.Packed = _mm_mul_ps(invLen, dq[0].Packed);

		auto sign = _mm_mul_ps(invLen, _mm_set_ps(0, 2, 2, -2));

		auto q1 = dq[1].Packed;
		auto t =          _mm_mul_ps(_mm_mul_ps(_SF_SWIZZLE(q1, 0, 0, 0, 0), _SF_SWIZZLE(q0.Packed, 2, 3, 2, 1)), _SF_SWIZZLE(sign, 3, 0, 0, 0));
		t = _mm_add_ps(t, _mm_mul_ps(_mm_mul_ps(_SF_SWIZZLE(q1, 1, 1, 1, 1), _SF_SWIZZLE(q0.Packed, 1, 2, 3, 0)), _SF_SWIZZLE(sign, 0, 0, 1, 1)));
		t = _mm_add_ps(t, _mm_mul_ps(_mm_mul_ps(_SF_SWIZZLE(q1, 2, 2, 2, 2), _SF_SWIZZLE(q0.Packed, 0, 1, 0, 3)), _SF_SWIZZLE(sign, 1, 1, 1, 0)));
		t = _mm_add_ps(t, _mm_mul_ps(_mm_mul_ps(_SF_SWIZZLE(q1, 3, 3, 3, 3), _SF_SWIZZLE(q0.Packed, 0, 0, 1, 2)), _SF_SWIZZLE(sign, 1, 1, 0, 1)));

		trans.Packed = t;

		//t[0] = 2.0*(-dq[1][0] * dq[0][1] + dq[1][1] * dq[0][0] - dq[1][2] * dq[0][3] + dq[1][3] * dq[0][2]) / len;
		//t[1] = 2.0*(-dq[1][0] * dq[0][2] + dq[1][1] * dq[0][3] + dq[1][2] * dq[0][0] - dq[1][3] * dq[0][1]) / len;
		//t[2] = 2.0*(-dq[1][0] * dq[0][3] - dq[1][1] * dq[0][2] + dq[1][2] * dq[0][1] + dq[1][3] * dq[0][0]) / len;
	}

}





