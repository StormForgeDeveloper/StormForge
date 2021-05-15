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


	/////////////////////////////////////////////////////////////////////////////
	//
	//	Vector4SSE
	//


	inline float Vector4SSE::SquareLength3() const
	{
		return Dot3(*this);
	}

	inline float Vector4SSE::Length3() const
	{
		return (float)sqrt(SquareLength3());
	}


	inline float Vector4SSE::SquareLength4() const
	{
		return Dot4(*this);
	}

	inline float Vector4SSE::Length4() const
	{
		return (float)sqrt(SquareLength4());
	}


	// returns orthogonal length
	inline void Vector4SSE::Normalize4()
	{
#if 0 // faster but too low precision
		auto invLength = _mm_rsqrt_ps(_mm_dp_ps(Packed, Packed, 0xFF));
		Packed = _mm_mul_ps(Packed, invLength);
#else
		auto len = _mm_sqrt_ps(_mm_dp_ps(Packed, Packed, 0xFF));
		if (_mm_cvtss_f32(len) < std::numeric_limits<float>::epsilon())
			Packed = _mm_set_ps(1, 0, 0, 0);
		else
			Packed = _mm_div_ps(Packed, len);
#endif
	}

	inline void Vector4SSE::Normalize3()
	{
#if 0 // faster but low precision
		auto invLength = _mm_rsqrt_ps(_mm_dp_ps(Packed, Packed, 0x77));
		Packed = _mm_blend_ps(_mm_mul_ps(Packed, invLength), zero, 8);
#else
		auto len = _mm_sqrt_ps(_mm_dp_ps(Packed, Packed, 0x7F));
		if (_mm_cvtss_f32(len) < std::numeric_limits<float>::epsilon())
			Packed = _mm_set_ps(0, 0, 0, 0);
		else
			Packed = _mm_div_ps(Packed, len);
#endif
	}

	inline float Vector4SSE::Normalize3Hi()
	{
		auto length = _mm_sqrt_ps(_mm_dp_ps(Packed, Packed, 0x7F));
		auto one = _mm_set1_ps(1);
		Packed = _mm_blend_ps(_mm_div_ps(Packed, length), one, 8);

		return _mm_cvtss_f32(length);
	}

	inline Vector4SSE& Vector4SSE::Scale3(float scale)
	{
		auto scaleVec = _mm_set_ps(1, scale, scale, scale);

		Packed = _mm_mul_ps(Packed, scaleVec);
		return *this;
	}

	
	inline Vector4SSE Vector4SSE::GetAbs() const
	{
		return Vector4SSE((float)Math::Abs(x), (float)Math::Abs(y), (float)Math::Abs(z), (float)Math::Abs(w));
	}

	inline float Vector4SSE::Dot4(const Vector4SSE& op) const
	{
		return _mm_cvtss_f32(_mm_dp_ps(Packed, op.Packed, 0xF1));
	}

	inline float Vector4SSE::Dot3(const Vector4SSE& op) const
	{
		return _mm_cvtss_f32(_mm_dp_ps(Packed, op.Packed, 0x71));
	}

	inline Vector4SSE Vector4SSE::Cross(const Vector4SSE& op) const
	{
		auto result = CrossRaw(op);

		// I prefer to set 1 for w
		// Set w to zero
		//return _mm_insert_ps(result, result, 0x38);

		auto one = _mm_set1_ps(1);
		return _mm_blend_ps(result.Packed, one, 8);
	}

	inline Vector4SSE Vector4SSE::CrossRaw(const Vector4SSE& op) const
	{
		//return Vector4SSE(_mm_sub_ps(
		//		_mm_mul_ps(_mm_shuffle_ps(Packed, Packed, _MM_SHUFFLE(3, 0, 2, 1)), _mm_shuffle_ps(op.Packed, op.Packed, _MM_SHUFFLE(3, 1, 0, 2))),
		//		_mm_mul_ps(_mm_shuffle_ps(Packed, Packed, _MM_SHUFFLE(3, 1, 0, 2)), _mm_shuffle_ps(op.Packed, op.Packed, _MM_SHUFFLE(3, 0, 2, 1)))
		//	));

		__m128 result = _mm_sub_ps(
			_mm_mul_ps(op.Packed, _mm_shuffle_ps(Packed, Packed, _MM_SHUFFLE(3, 1, 0, 2))),
			_mm_mul_ps(Packed, _mm_shuffle_ps(op.Packed, op.Packed, _MM_SHUFFLE(3, 1, 0, 2)))
		);

		return _mm_shuffle_ps(result, result, _MM_SHUFFLE(3, 2, 0, 1));

		//return Vector4SSE(
		//y * op.z - z * op.y, 
		//z * op.x - x * op.z, 
		//x * op.y - y * op.x, 1);
	}

	
	inline Vector4SSE& Vector4SSE::MAdd(const float& scala)
	{
		Packed = _mm_add_ps( Packed, _mm_mul_ps(Packed, _mm_set_ps1(scala)) );
		//x = (float)(x + x * scala);
		//y = (float)(y + y * scala);
		//z = (float)(z + z * scala);
		//w = (float)(w + w * scala);
		return *this;
	}

	
	inline Vector4SSE Vector4SSE::operator*(const Matrix4SSE & M) const
	{
		return Vector4SSE(_SF_SHUFFLE4(
			_mm_dp_ps(Packed, M.Packed[3], 0xF1),
			_mm_dp_ps(Packed, M.Packed[2], 0xF1),
			_mm_dp_ps(Packed, M.Packed[1], 0xF1),
			_mm_dp_ps(Packed, M.Packed[0], 0xF1),
			0, 0, 0, 0
		));

		//const Vector4SSE &v = *this;
		//Vector4SSE res;

		//res.x = float(M.a00 * v.x + M.a10 * v.y + M.a20 * v.z + M.a30 * w);
		//res.y = float(M.a01 * v.x + M.a11 * v.y + M.a21 * v.z + M.a31 * w);
		//res.z = float(M.a02 * v.x + M.a12 * v.y + M.a22 * v.z + M.a32 * w);
		//res.w = float(M.a03 * v.x + M.a13 * v.y + M.a23 * v.z + M.a33 * w);

		//return res;
	}

	
	inline Vector4SSE & Vector4SSE::operator*=(const Matrix4SSE & M)
	{
		//Vector4SSE v(*this);

		//x = float(M.a00 * v.x + M.a10 * v.y + M.a20 * v.z + M.a30 * w);
		//y = float(M.a01 * v.x + M.a11 * v.y + M.a21 * v.z + M.a31 * w);
		//z = float(M.a02 * v.x + M.a12 * v.y + M.a22 * v.z + M.a32 * w);
		//w = float(M.a03 * v.x + M.a13 * v.y + M.a23 * v.z + M.a33 * w);


		auto vec0 = _mm_dp_ps(Packed, _SF_SHUFFLE4(M.Packed[3], M.Packed[2], M.Packed[1], M.Packed[0], 0, 0, 0, 0), 0xF1);
		auto vec1 = _mm_dp_ps(Packed, _SF_SHUFFLE4(M.Packed[3], M.Packed[2], M.Packed[1], M.Packed[0], 1, 1, 1, 1), 0xF1);
		auto vec2 = _mm_dp_ps(Packed, _SF_SHUFFLE4(M.Packed[3], M.Packed[2], M.Packed[1], M.Packed[0], 2, 2, 2, 2), 0xF1);
		auto vec3 = _mm_dp_ps(Packed, _SF_SHUFFLE4(M.Packed[3], M.Packed[2], M.Packed[1], M.Packed[0], 3, 3, 3, 3), 0xF1);

		Packed = _SF_SHUFFLE4(vec3, vec2, vec1, vec0, 0, 0, 0, 0);

		//Packed = _mm_set_ps(
		//	//				w,    z,      y,     x
		//	Dot4(Vector4SSE(M.a03, M.a13, M.a23, M.a33)),  // w
		//	Dot4(Vector4SSE(M.a02, M.a12, M.a22, M.a32)),  // z
		//	Dot4(Vector4SSE(M.a01, M.a11, M.a21, M.a31)),  // y
		//	Dot4(Vector4SSE(M.a00, M.a10, M.a20, M.a30))   // x
		//);

		return (*this);
	}

	
	inline Vector4SSE Vector4SSE::operator/(const float & scala) const
	{
		return Vector4SSE(_mm_div_ps(Packed, _mm_set_ps1(scala)));
	}

	
	inline Vector4SSE Vector4SSE::operator*(const float & scala) const
	{
		return Vector4SSE(_mm_mul_ps(Packed, _mm_set_ps1(scala)));
	}

	inline Vector4SSE & Vector4SSE::operator/=(const float & scala)
	{
		Packed = _mm_div_ps(Packed, _mm_set_ps1(scala));
		return *this;
	}


	inline Vector4SSE & Vector4SSE::operator*=(const float & scala)
	{
		Packed = _mm_mul_ps(Packed, _mm_set_ps1(scala));
		return *this;
	}

	
	inline Vector4SSE & Vector4SSE::operator-=(const Vector4SSE & u)
	{
		Packed = _mm_sub_ps(Packed, u.Packed);
		//x = float(x - u.x);
		//y = float(y - u.y);
		//z = float(z - u.z);
		//w = float(w - u.w);
		return *this;
	}

	
	inline Vector4SSE & Vector4SSE::operator+=(const Vector4SSE & u)
	{
		Packed = _mm_add_ps(Packed, u.Packed);
		//x = float(x + u.x);
		//y = float(y + u.y);
		//z = float(z + u.z);
		//w = float(w + u.w);
		return *this;
	}


	
	inline Vector4SSE Vector4SSE::operator-(const Vector4SSE & u) const
	{
		return Vector4SSE(_mm_sub_ps(Packed, u.Packed));
	}

	
	inline Vector4SSE Vector4SSE::operator+(const Vector4SSE & u) const
	{
		return Vector4SSE(_mm_add_ps(Packed, u.Packed));
	}

	
	inline Vector4SSE Vector4SSE::operator*(const Vector4SSE & u) const
	{
		return Vector4SSE(_mm_mul_ps(Packed, u.Packed));
	}

	
	inline Vector4SSE Vector4SSE::operator/(const Vector4SSE & u) const
	{
		return Vector4SSE(_mm_div_ps(Packed, u.Packed));
		//return Vector4SSE(x / u.x, y / u.y, z / u.z, w);
	}

	
	inline Vector4SSE & Vector4SSE::operator=(const Vector4SSE & src)
	{
		Packed = src.Packed;
		//memcpy(Elements, src.Elements, sizeof(Elements));
		return *this;
	}



}





