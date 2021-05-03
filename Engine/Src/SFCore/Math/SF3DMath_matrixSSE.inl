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
	//	Matrix4SSE
	//

	
	inline Matrix4SSE& Matrix4SSE::InitIdentity()
	{
		Packed[0] = _mm_set_ps(0, 0, 0, 1);
		Packed[1] = _mm_set_ps(0, 0, 1, 0);
		Packed[2] = _mm_set_ps(0, 1, 0, 0);
		Packed[3] = _mm_set_ps(1, 0, 0, 0);

		return *this;
	}



	inline Matrix4SSE Matrix4SSE::GetTranspose()
	{
		__m128 tmp0 = _mm_shuffle_ps(Packed[0], Packed[1], 0x44);
		__m128 tmp2 = _mm_shuffle_ps(Packed[0], Packed[1], 0xEE);
		__m128 tmp1 = _mm_shuffle_ps(Packed[2], Packed[3], 0x44);
		__m128 tmp3 = _mm_shuffle_ps(Packed[2], Packed[3], 0xEE);

		return Matrix4SSE(
			_mm_shuffle_ps(tmp0, tmp1, 0x88),
			_mm_shuffle_ps(tmp0, tmp1, 0xDD),
			_mm_shuffle_ps(tmp2, tmp3, 0x88),
			_mm_shuffle_ps(tmp2, tmp3, 0xDD)
		);
	}

	inline Matrix4SSE& Matrix4SSE::Transpose()
	{
		__m128 tmp0 = _mm_shuffle_ps(Packed[0], Packed[1], 0x44);
		__m128 tmp2 = _mm_shuffle_ps(Packed[0], Packed[1], 0xEE);
		__m128 tmp1 = _mm_shuffle_ps(Packed[2], Packed[3], 0x44);
		__m128 tmp3 = _mm_shuffle_ps(Packed[2], Packed[3], 0xEE);

		Packed[0] = _mm_shuffle_ps(tmp0, tmp1, 0x88);
		Packed[1] = _mm_shuffle_ps(tmp0, tmp1, 0xDD);
		Packed[2] = _mm_shuffle_ps(tmp2, tmp3, 0x88);
		Packed[3] = _mm_shuffle_ps(tmp2, tmp3, 0xDD);

		return *this;
	}


	
	inline Matrix4SSE Matrix4SSE::GetRotationMatrix() const
	{
		auto invLength = _mm_rsqrt_ps(_mm_dp_ps(Packed[0], Packed[0], 0x77));
		auto c1 = _mm_mul_ps(Packed[0], invLength);

		invLength = _mm_rsqrt_ps(_mm_dp_ps(Packed[1], Packed[1], 0x77));
		auto c2 = _mm_mul_ps(Packed[1], invLength);

		invLength = _mm_rsqrt_ps(_mm_dp_ps(Packed[2], Packed[2], 0x77));
		auto c3 = _mm_mul_ps(Packed[2], invLength);

		Matrix4SSE temp(c1, c2, c3, _mm_set_ps(1,0,0,0));
		temp.a30 = temp.a31 = temp.a32 = 0;

		return temp;
	}


	inline QuaternionSSE Matrix4SSE::ToQuaternion(bool bIgnoreScale) const
	{
		QuaternionSSE q;
		//auto invLength = _mm_rsqrt_ps(_mm_dp_ps(Packed[0], Packed[0], 0x77));
		//auto c0 = _mm_mul_ps(Packed[0], invLength);

		//invLength = _mm_rsqrt_ps(_mm_dp_ps(Packed[1], Packed[1], 0x77));
		//auto c1 = _mm_mul_ps(Packed[1], invLength);

		//invLength = _mm_rsqrt_ps(_mm_dp_ps(Packed[2], Packed[2], 0x77));
		//auto c2 = _mm_mul_ps(Packed[2], invLength);

		float trace = a00 + a11 + a22;
		if (trace > float(0))
		{
			float Scale = sqrtf(trace + float(1));
			float invScale = float(0.5) / Scale;
			auto diff = _mm_sub_ps(_mm_set_ps(1.f, a10, a02, a21), _mm_set_ps(0.5f, a01, a20, a12));
			return _mm_mul_ps(_mm_set_ps(Scale, invScale, invScale, invScale), diff);
			//q.x = invScale * (a21 - a12);
			//q.y = invScale * (a02 - a20);
			//q.z = invScale * (a10 - a01);
			//q.w = Scale * float(0.5);
		}
		else
		{
			//auto& mat = *this;
			//static int next[] = { 1, 2, 0 };
			//int i = 0;
			//int j = 1;// next[i];
			//int k = 2;// next[j];
			if (a11 > a00)
			{
				//i = 1;
				if (a22 > a11/*mat(i, i)*/)
				{
					//i = 2;
					//j = 0;
					//k = 1;
					float Scale = sqrtf(a22 - a00 - a11 + 1);
					float invScale = 0.5f / Scale;
					q.Packed = _mm_mul_ps(
						_mm_set_ps(invScale, Scale, invScale, invScale), 
						_mm_add_ps(_mm_set_ps(a10, 1.f, a12, a02), _mm_set_ps(-a01, -0.5f, a21, a20))
						);
					//q.x = invScale * (a02 + a20);
					//q.y = invScale * (a12 + a21);
					//q.z = Scale * 0.5f;
					//q.w = invScale * (a10 - a01);
				}
				else
				{
					//i = 1;
					//j = 2;
					//k = 0;
					float Scale = sqrtf(a11 - a22 - a00 + 1);
					float invScale = 0.5f / Scale;
					q.Packed = _mm_mul_ps(
						_mm_set_ps(invScale, invScale, Scale, invScale),
						_mm_add_ps(_mm_set_ps(a02, a21, 1.f, a01), _mm_set_ps(-a20, a12, -0.5f, a10))
					);
					//q.x = invScale * (a01 + a10);
					//q.y = Scale * 0.5f;
					//q.z = invScale * (a21 + a12);
					//q.w = invScale * (a02 - a20);
				}
			}
			else
			{
				if (a22 > a00/*mat(i, i)*/)
				{
					//i = 2;
					//j = 0;
					//k = 1;
					float Scale = sqrtf(a22 - a00 - a11 + 1);
					float invScale = 0.5f / Scale;
					q.Packed = _mm_mul_ps(
						_mm_set_ps(invScale, Scale, invScale, invScale),
						_mm_add_ps(_mm_set_ps(a10, 1.f, a12, a02), _mm_set_ps(-a01, -0.5f, a21, a20))
					);
					//q.x = invScale * (a02 + a20);
					//q.y = invScale * (a12 + a21);
					//q.z = Scale * 0.5f;
					//q.w = invScale * (a10 - a01);
				}
				else
				{
					//i = 0;
					//j = 1;
					//k = 2;
					float Scale = sqrtf(a00 - a11 - a22 + 1);
					float invScale = 0.5f / Scale;
					q.Packed = _mm_mul_ps(
						_mm_set_ps(invScale, invScale, invScale, Scale),
						_mm_add_ps(_mm_set_ps(a21, a20, a10, 1.f), _mm_set_ps(-a12, a02, a01, -0.5f))
					);
					//q.x = Scale * 0.5f;
					//q.y = invScale * (a10 + a01);
					//q.z = invScale * (a20 + a02);
					//q.w = invScale * (a21 - a12);
				}
			}
			//if (a22 > mat(i, i))
			//{
			//	i = 2;
			//}

			//int j = next[i];
			//int k = next[j];
			//float Scale = sqrtf(mat(i, i) - mat(j, j) - mat(k, k) + 1);
			//float invScale = 0.5f / Scale;
			//float* qe[] = { &q.x, &q.y, &q.z };
			//*qe[i] = Scale * 0.5f;
			//*qe[j] = invScale * (mat(j, i) + mat(i, j));
			//*qe[k] = invScale * (mat(k, i) + mat(i, k));
			//q.w =    invScale * (mat(k, j) - mat(j, k));
		}

		return q;
	}


	inline Matrix4SSE & Matrix4SSE::InitRotationMatrix(const QuaternionSSE& q)
	{
		auto xyz = _mm_mul_ps(q.Packed, _mm_set1_ps(2));
		//float x2 = q.x * 2;
		//float y2 = q.y * 2;
		//float z2 = q.z * 2;

		auto wzxy = _mm_mul_ps(_mm_shuffle_ps(xyz, xyz, _MM_SHUFFLE(3, 1, 0, 2)), _mm_shuffle_ps(q.Packed, q.Packed, _MM_SHUFFLE(3,3,3,3)));
		//float wx = x2 * q.w;
		//float wy = y2 * q.w;
		//float wz = z2 * q.w;

		auto xyyzzx = _mm_mul_ps(xyz, _mm_shuffle_ps(q.Packed, q.Packed,_MM_SHUFFLE(3,0,2,1)));
		//float xy = x2 * q.y;
		//float yz = y2 * q.z;
		//float zx = z2 * q.x;

		auto xxyyzz = _mm_mul_ps(xyz, q.Packed);
		//float xx = x2 * q.x;
		//float yy = y2 * q.y;
		//float zz = z2 * q.z;

		auto xxyyzzSum = _mm_dp_ps(xyz, q.Packed, 0x77);
		auto a00a11a22  = (_mm_sub_ps(_mm_add_ps(_mm_set1_ps(1), xxyyzz), xxyyzzSum));
		//a00 = 1 - (yy + zz);
		//a11 = 1 - (zz + xx);
		//a22 = 1 - (xx + yy);

		auto a01a12a20 = (_mm_sub_ps(xyyzzx, wzxy));
		//a01 = xy - wz;
		//a12 = yz - wx;
		//a20 = zx - wy;

		auto a10a21a02 = (_mm_add_ps(xyyzzx, wzxy));
		//a10 = xy + wz;
		//a21 = yz + wx;
		//a02 = zx + wy;

		auto refZero = _mm_set_ps(1, 0, 0, 0);
		Packed[0] = _SF_SHUFFLE4(refZero, a01a12a20, a10a21a02, a00a11a22, 0, 2, 0, 0);
		Packed[1] = _SF_SHUFFLE4(refZero, a10a21a02, a00a11a22, a01a12a20, 0, 1, 1, 0);
		Packed[2] = _SF_SHUFFLE4(refZero, a00a11a22, a01a12a20, a10a21a02, 0, 2, 1, 2);
		//Packed[0] = _mm_set_ps(0, a01a12a20.z, a10a21a02.x, a00a11a22.x);
		//Packed[1] = _mm_set_ps(0, a10a21a02.y, a00a11a22.y, a01a12a20.x);
		//Packed[2] = _mm_set_ps(0, a00a11a22.z, a01a12a20.y, a10a21a02.z);
		Packed[2] = _mm_set_ps(1, 0, 0, 0);

		return *this;
	}


	// v is normalized
	// theta in radians
	inline Matrix4SSE & Matrix4SSE::InitRotationMatrix(const Vector4SSE& v)
	{
		float theta = v.w;
		auto ct = _mm_set1_ps(cos(theta));
		auto st = _mm_set1_ps(sin(theta));

		//float xx = v.x * v.x;
		//float yy = v.y * v.y;
		//float zz = v.z * v.z;
		//float xy = v.x * v.y;
		//float yz = v.y * v.z;
		//float zx = v.z * v.x;
		auto xxyyzz = _mm_mul_ps(v.Packed, v.Packed);
		auto xyyzzx = _mm_mul_ps(v.Packed, _mm_shuffle_ps(v.Packed, v.Packed, _MM_SHUFFLE(3, 0, 2, 1)));

		auto a00a11a22 = (_mm_add_ps(
			xxyyzz, 
			_mm_mul_ps(ct,_mm_sub_ps(_mm_set1_ps(1),xxyyzz))
		));
		//a00 = xx + ct * (1 - xx);
		//a11 = yy + ct * (1 - yy);
		//a22 = zz + ct * (1 - zz);

		auto vzxy = _mm_shuffle_ps(v.Packed, v.Packed, _MM_SHUFFLE(3,1,0,2));
		auto a01a12a20 = (_mm_sub_ps(
			_mm_sub_ps(
				xyyzzx, 
				_mm_mul_ps(ct, xyyzzx)
			),
			_mm_mul_ps(st, vzxy)
		));
		//a01 = xy + ct * (-xy) + st * -v.z;
		//a12 = yz + ct * (-yz) + st * -v.x;
		//a20 = zx + ct * (-xz) + st * -v.y;

		auto a10a21a02 = (_mm_add_ps(
			_mm_sub_ps(
				xyyzzx,
				_mm_mul_ps(ct, xyyzzx)
			),
			_mm_mul_ps(st, vzxy)
		));
		//a10 = xy + ct * (-xy) + st * v.z;
		//a21 = yz + ct * (-yz) + st * v.x;
		//a02 = zx + ct * (-zx) + st * v.y;
		
		//Packed[0] = _mm_set_ps(0, a01a12a20.z, a10a21a02.x, a00a11a22.x);
		//Packed[1] = _mm_set_ps(0, a10a21a02.y, a00a11a22.y, a01a12a20.x);
		//Packed[2] = _mm_set_ps(0, a00a11a22.z, a01a12a20.y, a10a21a02.z);
		auto refZero = _mm_set_ps(1, 0, 0, 0);
		Packed[0] = _SF_SHUFFLE4(refZero, a01a12a20, a10a21a02, a00a11a22, 0, 2, 0, 0);
		Packed[1] = _SF_SHUFFLE4(refZero, a10a21a02, a00a11a22, a01a12a20, 0, 1, 1, 0);
		Packed[2] = _SF_SHUFFLE4(refZero, a00a11a22, a01a12a20, a10a21a02, 0, 2, 1, 2);
		Packed[3] = refZero;

		return *this;
	}


	inline Matrix4SSE & Matrix4SSE::InitRotationMatrix(const Vector4SSE& u, const Vector4SSE& v)
	{
		float phi;
		__m128 h;
		float scala;
		Vector4SSE w;

		w = u.Cross(v);
		phi = u.Dot3(v);
		scala = w.Dot3(w);
		if (scala > C_EPSILON)
			h = _mm_set1_ps((float(1) - phi) / scala);
		else
			h = _mm_set1_ps(scala);

		auto wyzx = _mm_shuffle_ps(w.Packed, w.Packed, _MM_SHUFFLE(3, 0, 2, 1));
		auto wzxy = _mm_shuffle_ps(w.Packed, w.Packed, _MM_SHUFFLE(3, 1, 0, 2));
		auto hyzzxxy = _mm_mul_ps(_mm_mul_ps(wyzx, wzxy), h);
		//float hyz = w.y * w.z * h;
		//float hzx = w.z * w.x * h;
		//float hxy = w.x * w.y * h;

#if 0
		{
			auto a00a11a22 = Vector4SSE(_mm_add_ps(_mm_set1_ps(phi), _mm_mul_ps(_mm_mul_ps(w.Packed, w.Packed), h)));
			//a00 = phi + w.x * w.x * h;
			//a11 = phi + w.y * w.y * h;
			//a22 = phi + w.z * w.z * h;

			auto a12a20a01 = Vector4SSE(_mm_sub_ps(hyzzxxy, w.Packed));
			//a12 = hyz - w.x;
			//a20 = hzx - w.y;
			//a01 = hxy - w.z;

			auto a21a02a10 = Vector4SSE(_mm_add_ps(hyzzxxy, w.Packed));
			//a21 = hyz + w.x;
			//a02 = hzx + w.y;
			//a10 = hxy + w.z;

			// TODO: AVX permute
			Packed[0] = _mm_set_ps(0, a12a20a01.y, a21a02a10.z, a00a11a22.x);
			Packed[1] = _mm_set_ps(0, a21a02a10.x, a00a11a22.y, a12a20a01.z);
			Packed[2] = _mm_set_ps(0, a00a11a22.z, a12a20a01.x, a21a02a10.y);
			Packed[3] = _mm_set_ps(1, 0, 0, 0);
		}
#else
		auto a00a11a22 = (_mm_add_ps(_mm_set1_ps(phi), _mm_mul_ps(_mm_mul_ps(w.Packed, w.Packed), h)));
		//a00 = phi + w.x * w.x * h;
		//a11 = phi + w.y * w.y * h;
		//a22 = phi + w.z * w.z * h;

		auto a12a20a01 = (_mm_sub_ps(hyzzxxy, w.Packed));
		//a12 = hyz - w.x;
		//a20 = hzx - w.y;
		//a01 = hxy - w.z;

		auto a21a02a10 = (_mm_add_ps(hyzzxxy, w.Packed));
		//a21 = hyz + w.x;
		//a02 = hzx + w.y;
		//a10 = hxy + w.z;


		auto refZero = _mm_set_ps(1, 0, 0, 0);
		Packed[0] = _SF_SHUFFLE4(refZero, a12a20a01, a21a02a10, a00a11a22, 0, 1, 2, 0);
		Packed[1] = _SF_SHUFFLE4(refZero, a21a02a10, a00a11a22, a12a20a01, 0, 0, 1, 2);
		Packed[2] = _SF_SHUFFLE4(refZero, a00a11a22, a12a20a01, a21a02a10, 0, 2, 0, 1);
		//Packed[0] = _mm_set_ps(0, a12a20a01.y, a21a02a10.z, a00a11a22.x);
		//Packed[1] = _mm_set_ps(0, a21a02a10.x, a00a11a22.y, a12a20a01.z);
		//Packed[2] = _mm_set_ps(0, a00a11a22.z, a12a20a01.x, a21a02a10.y);
		Packed[3] = refZero;
#endif

		return *this;
	}


	// Copy rotation part from other matrix
	inline Matrix4SSE & Matrix4SSE::InitRotationMatrix(const Matrix4SSE& m)
	{
		Packed[0] = m.Packed[0];
		Packed[1] = m.Packed[1];
		Packed[2] = m.Packed[2];
		Packed[3] = _mm_set_ps(1, 0, 0, 0);

		

		return *this;
	}

	

		// initialize scale matrix
	inline Matrix4SSE & Matrix4SSE::InitScaleMatrix(const Vector4SSE& s)
	{
		Packed[0] = _mm_set_ps(0, 0, 0, s.x);
		Packed[1] = _mm_set_ps(0, 0, s.y, 0);
		Packed[2] = _mm_set_ps(0, s.z, 0, 0);
		Packed[3] = _mm_set_ps(1, 0, 0, 0);

		return *this;
	}

	
	inline Matrix4SSE & Matrix4SSE::InitScaleMatrix(const float& s)
	{
		Packed[0] = _mm_set_ps(0, 0, 0, s);
		Packed[1] = _mm_set_ps(0, 0, s, 0);
		Packed[2] = _mm_set_ps(0, s, 0, 0);
		Packed[3] = _mm_set_ps(1, 0, 0, 0);

		return *this;
	}

	
	inline Matrix4SSE & Matrix4SSE::SetTranslation(const Vector4SSE& t)
	{
		Packed[3] = _mm_set_ps(1, t.z, t.y, t.x);

		return *this;
	}

	
	inline Vector4SSE Matrix4SSE::GetTranslation() const
	{
		return Vector4SSE(Packed[3]);
	}

	
	inline Matrix4SSE & Matrix4SSE::InitTranslationMatrix(const Vector4SSE& t)
	{
		Packed[0] = _mm_set_ps(0, 0, 0, 1);
		Packed[1] = _mm_set_ps(0, 0, 1, 0);
		Packed[2] = _mm_set_ps(0, 1, 0, 0);
		Packed[3] = _mm_set_ps(1, t.z, t.y, t.x);

		return *this;
	}



	inline const Vector4SSE Matrix4SSE::GetRow(const int i) const
	{
		switch (i)
		{
		case 0: return Vector4SSE(_SF_SHUFFLE4(Packed[3], Packed[2], Packed[1], Packed[0], 0, 0, 0, 0));
		case 1: return Vector4SSE(_SF_SHUFFLE4(Packed[3], Packed[2], Packed[1], Packed[0], 1, 1, 1, 1));
		case 2: return Vector4SSE(_SF_SHUFFLE4(Packed[3], Packed[2], Packed[1], Packed[0], 2, 2, 2, 2));
		case 3: return Vector4SSE(_SF_SHUFFLE4(Packed[3], Packed[2], Packed[1], Packed[0], 3, 3, 3, 3));
		default:
			assert(false);
			return Vector4SSE();
		}
		//return Vector4SSE(Elements[i], Elements[i + 4], Elements[i + 8], Elements[i + 12]);
	}

	
	inline Matrix4SSE Matrix4SSE::operator*(const float& scala) const
	{
		auto scalaVec = _mm_set1_ps(scala);
		return Matrix4SSE(
			_mm_mul_ps(Packed[0], scalaVec),
			_mm_mul_ps(Packed[1], scalaVec),
			_mm_mul_ps(Packed[2], scalaVec),
			_mm_mul_ps(Packed[3], scalaVec)
		);
	}

	
	inline Matrix4SSE& Matrix4SSE::operator*=(const float& scala)
	{
		auto scalaVec = _mm_set1_ps(scala);
		Packed[0] = _mm_mul_ps(Packed[0], scalaVec);
		Packed[1] = _mm_mul_ps(Packed[1], scalaVec);
		Packed[2] = _mm_mul_ps(Packed[2], scalaVec);
		Packed[3] = _mm_mul_ps(Packed[3], scalaVec);

		return *this;
	}




	inline Matrix4SSE Matrix4SSE::operator/(const float& scala) const
	{
		auto scalaVec = _mm_set1_ps(1.0f / scala);
		return Matrix4SSE(
			_mm_mul_ps(Packed[0], scalaVec),
			_mm_mul_ps(Packed[1], scalaVec),
			_mm_mul_ps(Packed[2], scalaVec),
			_mm_mul_ps(Packed[3], scalaVec)
		);
	}


	inline Matrix4SSE& Matrix4SSE::operator/=(const float& scala)
	{
		auto scalaVec = _mm_set1_ps(1.0f / scala);
		Packed[0] = _mm_mul_ps(Packed[0], scalaVec);
		Packed[1] = _mm_mul_ps(Packed[1], scalaVec);
		Packed[2] = _mm_mul_ps(Packed[2], scalaVec);
		Packed[3] = _mm_mul_ps(Packed[3], scalaVec);

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
	
	inline Matrix4SSE Matrix4SSE::operator*(const Matrix4SSE& B) const
	{
		auto c0 = (*this) * B.Packed[0];
		auto c1 = (*this) * B.Packed[1];
		auto c2 = (*this) * B.Packed[2];
		auto c3 = (*this) * B.Packed[3];

		return Matrix4SSE(
			c0,
			c1,
			c2,
			c3
		);

	}

	
	inline Matrix4SSE& Matrix4SSE::operator*=(const Matrix4SSE & B)
	{
		auto c0 = (*this) * B.Packed[0];
		auto c1 = (*this) * B.Packed[1];
		auto c2 = (*this) * B.Packed[2];
		auto c3 = (*this) * B.Packed[3];

		Packed[0] = c0;
		Packed[1] = c1;
		Packed[2] = c2;
		Packed[3] = c3;

		return *this;
	}


	
	inline Matrix4SSE  Matrix4SSE::operator+(const Matrix4SSE & M) const
	{
		return Matrix4SSE(
			_mm_add_ps(Packed[0], M.Packed[0]),
			_mm_add_ps(Packed[1], M.Packed[1]),
			_mm_add_ps(Packed[2], M.Packed[2]),
			_mm_add_ps(Packed[3], M.Packed[3])
			);
	}

	
	inline Matrix4SSE & Matrix4SSE::operator+=(const Matrix4SSE & M)
	{
		Packed[0] = _mm_add_ps(Packed[0], M.Packed[0]);
		Packed[1] = _mm_add_ps(Packed[1], M.Packed[1]);
		Packed[2] = _mm_add_ps(Packed[2], M.Packed[2]);
		Packed[3] = _mm_add_ps(Packed[3], M.Packed[3]);

		return *this;
	}

	
	inline Matrix4SSE  Matrix4SSE::operator-(const Matrix4SSE & M) const
	{
		return Matrix4SSE(
			_mm_sub_ps(Packed[0], M.Packed[0]),
			_mm_sub_ps(Packed[1], M.Packed[1]),
			_mm_sub_ps(Packed[2], M.Packed[2]),
			_mm_sub_ps(Packed[3], M.Packed[3])
		);
	}

	
	inline Matrix4SSE & Matrix4SSE::operator-=(const Matrix4SSE & M)
	{
		Packed[0] = _mm_sub_ps(Packed[0], M.Packed[0]);
		Packed[1] = _mm_sub_ps(Packed[1], M.Packed[1]);
		Packed[2] = _mm_sub_ps(Packed[2], M.Packed[2]);
		Packed[3] = _mm_sub_ps(Packed[3], M.Packed[3]);

		return *this;
	}



	inline __m128 Matrix4SSE::operator*(const __m128& v) const
	{
		__m128 v0 = _mm_shuffle_ps(v, v, _MM_SHUFFLE(0, 0, 0, 0));
		__m128 v1 = _mm_shuffle_ps(v, v, _MM_SHUFFLE(1, 1, 1, 1));
		__m128 v2 = _mm_shuffle_ps(v, v, _MM_SHUFFLE(2, 2, 2, 2));
		__m128 v3 = _mm_shuffle_ps(v, v, _MM_SHUFFLE(3, 3, 3, 3));

		__m128 m0 = _mm_mul_ps(Packed[0], v0);
		__m128 m1 = _mm_mul_ps(Packed[1], v1);
		__m128 m2 = _mm_mul_ps(Packed[2], v2);
		__m128 m3 = _mm_mul_ps(Packed[3], v3);

		__m128 a0 = _mm_add_ps(m0, m1);
		__m128 a1 = _mm_add_ps(m2, m3);
		__m128 a2 = _mm_add_ps(a0, a1);

		return a2;
	}

	inline Vector4SSE Matrix4SSE::operator*(const Vector4SSE& v) const
	{
		return Vector4SSE((*this) * v.Packed);
	}

	inline Matrix4SSE& Matrix4SSE::operator=(const Matrix4SSE & M)
	{
		Packed[0] = M.Packed[0];
		Packed[1] = M.Packed[1];
		Packed[2] = M.Packed[2];
		Packed[3] = M.Packed[3];

		return *this;
	}

	// Transform position vector
	// This operation same to matrix-vector multiplication, but it will ignore w component
	inline Vector4SSE Matrix4SSE::TransformVector(const Vector4SSE& v)
	{
		auto vx = _SF_SWIZZLE1(v.Packed, 0);
		auto vy = _SF_SWIZZLE1(v.Packed, 1);
		auto vz = _SF_SWIZZLE1(v.Packed, 2);
		//auto vw = _SF_SWIZZLE1(v.Packed, 3);
		auto mask = _mm_set_ps(0, 1, 1, 1);
		auto w1 = _mm_set_ps(1, 0, 0, 0);

		auto res = _mm_mul_ps(Packed[0], vx);
		res = _mm_add_ps(res, _mm_mul_ps(Packed[0], vy));
		res = _mm_add_ps(res, _mm_mul_ps(Packed[0], vz));
		res = _mm_add_ps(_mm_mul_ps(res, mask), w1);

		return Vector4SSE(res);
	}




	// https://en.wikipedia.org/wiki/Invertible_matrix
	// https://en.wikipedia.org/wiki/Adjugate_matrix
	// https://en.wikipedia.org/wiki/Determinant#Relation_to_eigenvalues_and_trace
	// https://en.wikipedia.org/wiki/Trace_(linear_algebra)
	// https://software.intel.com/en-us/articles/optimized-matrix-library-for-use-with-the-intel-pentiumr-4-processors-sse2-instructions/
	// https://lxjk.github.io/2017/09/03/Fast-4x4-Matrix-Inverse-with-SSE-SIMD-Explained.html

	// for row major matrix
	// we use __m128 to represent 2x2 matrix as A = | A0  A1 |
	//                                              | A2  A3 |
	// 2x2 row major Matrix multiply A*B
	SF_FORCEINLINE __m128 _Mat2Mul(__m128 vec1, __m128 vec2)
	{
		return _mm_add_ps(
			_mm_mul_ps(vec1, _SF_SWIZZLE(vec2, 3, 3, 0,0)),
			_mm_mul_ps(_SF_SWIZZLE(vec1, 1,0,3,2), _SF_SWIZZLE(vec2, 2,2,1,1))
		);
	}

	// 2x2 column major Matrix adjugate multiply (A#)*B
	SF_FORCEINLINE __m128 _Mat2AdjMul(__m128 vec1, __m128 vec2)
	{
		return _mm_sub_ps(
			_mm_mul_ps(_SF_SWIZZLE(vec1, 0, 3, 0, 3), vec2),
			_mm_mul_ps(_SF_SWIZZLE(vec1, 1, 2, 1, 2), _SF_SWIZZLE(vec2, 2,3,0,1))
		);

	}
	// 2x2 column major Matrix multiply adjugate A*(B#)
	SF_FORCEINLINE __m128 _Mat2MulAdj(__m128 vec1, __m128 vec2)
	{
		return _mm_sub_ps(
			_mm_mul_ps(vec1, _SF_SWIZZLE(vec2, 0, 0, 3, 3)),
			_mm_mul_ps(_SF_SWIZZLE(vec1, 1,0,3,2), _SF_SWIZZLE(vec2, 2,2,1,1))
		);
	}


	// Inverse function is the same no matter column major or row major
	// this version treats it as column major
	inline Matrix4SSE Matrix4SSE::GetInverse()
		//inline Matrix4 GetInverse(const Matrix4& inM)
	{
		// use block matrix method
		// A is a matrix, then i(A) or iA means inverse of A, A# (or A_ in code) means adjugate of A, |A| (or detA in code) is determinant, tr(A) is trace

		// sub matrices
		__m128 A = _SF_SHUFFLE_0101(Packed[0], Packed[1]);
		__m128 C = _SF_SHUFFLE_2323(Packed[0], Packed[1]);
		__m128 B = _SF_SHUFFLE_0101(Packed[2], Packed[3]);
		__m128 D = _SF_SHUFFLE_2323(Packed[2], Packed[3]);

#if 1 // for determinant
		// determinant as (|A| |C| |B| |D|)
		__m128 detSub = _mm_sub_ps(
			_mm_mul_ps(_SF_SHUFFLE(Packed[0], Packed[2], 2, 0, 2, 0), _SF_SHUFFLE(Packed[1], Packed[3], 3, 1, 3, 1)),
			_mm_mul_ps(_SF_SHUFFLE(Packed[0], Packed[2], 3, 1, 3, 1), _SF_SHUFFLE(Packed[1], Packed[3], 2, 0, 2, 0))
		);
		__m128 detA = _SF_SWIZZLE1(detSub, 0);
		__m128 detC = _SF_SWIZZLE1(detSub, 1);
		__m128 detB = _SF_SWIZZLE1(detSub, 2);
		__m128 detD = _SF_SWIZZLE1(detSub, 3);
#else
		// This implementation works on Inter CPU, but has error on AMD CPU
		__m128 detA = _mm_set1_ps(a00 * a11 - a01 * a10);
		__m128 detC = _mm_set1_ps(a02 * a13 - a03 * a12);
		__m128 detB = _mm_set1_ps(a20 * a31 - a21 * a30);
		__m128 detD = _mm_set1_ps(a22 * a33 - a23 * a32);
#endif

		// let iM = 1/|M| * | X  Y |
		//                  | Z  W |
		// D#C
		__m128 D_C = _Mat2AdjMul(D, C);
		// A#B
		__m128 A_B = _Mat2AdjMul(A, B);
		// X# = |D|A - B(D#C)
		__m128 X_ = _mm_sub_ps(_mm_mul_ps(detD, A), _Mat2Mul(B, D_C));
		// W# = |A|D - C(A#B)
		__m128 W_ = _mm_sub_ps(_mm_mul_ps(detA, D), _Mat2Mul(C, A_B));

		// |M| = |A|*|D| + ... (continue later)
		__m128 detM = _mm_mul_ps(detA, detD);

		// Y# = |B|C - D(A#B)#
		__m128 Y_ = _mm_sub_ps(_mm_mul_ps(detB, C), _Mat2MulAdj(D, A_B));
		// Z# = |C|B - A(D#C)#
		__m128 Z_ = _mm_sub_ps(_mm_mul_ps(detC, B), _Mat2MulAdj(A, D_C));

		// |M| = |A|*|D| + |B|*|C| ... (continue later)
		detM = _mm_add_ps(detM, _mm_mul_ps(detB, detC));

		// tr((A#B)(D#C))
		__m128 tr = _mm_mul_ps(A_B, _SF_SWIZZLE(D_C, 3,1,2,0));
		tr = _mm_hadd_ps(tr, tr);
		tr = _mm_hadd_ps(tr, tr);
		// |M| = |A|*|D| + |B|*|C| - tr((A#B)(D#C))
		detM = _mm_sub_ps(detM, tr);

		const __m128 adjSignMask = _mm_setr_ps(1.f, -1.f, -1.f, 1.f);
		// (1/|M|, -1/|M|, -1/|M|, 1/|M|)
		__m128 rDetM = _mm_div_ps(adjSignMask, detM);

		X_ = _mm_mul_ps(X_, rDetM);
		Y_ = _mm_mul_ps(Y_, rDetM);
		Z_ = _mm_mul_ps(Z_, rDetM);
		W_ = _mm_mul_ps(W_, rDetM);

		// apply adjugate and store, here we combine adjugate shuffle and store shuffle
		return Matrix4SSE(
			_SF_SHUFFLE(X_, Z_, 1, 3, 1, 3),
			_SF_SHUFFLE(X_, Z_, 0, 2, 0, 2),
			_SF_SHUFFLE(Y_, W_, 1, 3, 1, 3),
			_SF_SHUFFLE(Y_, W_, 0, 2, 0, 2)
		);
	}


	// Inverse for transform without scale
	inline Matrix4SSE Matrix4SSE::GetInverseTransformNoScale()
	{
		Matrix4SSE r;
		// transpose 3x3, assuming a23 is zero
		__m128 a0010a0111 = _mm_movelh_ps(a0010a2030, a0111a2131);	// 00, 01, 10, 11
		__m128 a2030a2131 = _mm_movehl_ps(a0111a2131, a0010a2030);	// 02, 03, 12, 13
		r.Packed[0] = _mm_shuffle_ps(a0010a0111, a0212a2232, _MM_SHUFFLE(3, 0, 2, 0)); // 00, 10, 20, 23
		r.Packed[1] = _mm_shuffle_ps(a0010a0111, a0212a2232, _MM_SHUFFLE(3, 1, 3, 1)); // 01, 11, 21, 23
		r.Packed[2] = _mm_shuffle_ps(a2030a2131, a0212a2232, _MM_SHUFFLE(3, 2, 2, 0)); // 02, 12, 22, 23

		// multiply with transposed rotation
		r.Packed[3] = _mm_mul_ps(r.Packed[0], _mm_shuffle_ps(a0313a2333, a0313a2333, _MM_SHUFFLE(0, 0, 0, 0)));
		r.Packed[3] = _mm_add_ps(r.Packed[3], _mm_mul_ps(r.Packed[1], _mm_shuffle_ps(a0313a2333, a0313a2333, _MM_SHUFFLE(1, 1, 1, 1))));
		r.Packed[3] = _mm_add_ps(r.Packed[3], _mm_mul_ps(r.Packed[2], _mm_shuffle_ps(a0313a2333, a0313a2333, _MM_SHUFFLE(2, 2, 2, 2))));
		r.Packed[3] = _mm_sub_ps(_mm_set_ps(1, 0, 0, 0), r.Packed[3]);

		return r;
	}

	inline Matrix4SSE& Matrix4SSE::NormalizeTransform()
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

		float inv33 = 1.0f / a33;
		auto mmInv33 = _mm_set_ps1(inv33);
		Packed[0] = _mm_mul_ps(Packed[0], mmInv33);
		Packed[1] = _mm_mul_ps(Packed[1], mmInv33);
		Packed[2] = _mm_mul_ps(Packed[2], mmInv33);
		Packed[3] = _mm_mul_ps(Packed[3], mmInv33);

		return *this;
	}


	// Inverse for transform without scale
	inline Matrix4SSE Matrix4SSE::GetInverseTransform()
	{
		Matrix4SSE r;
		// transpose 3x3, assuming a23 is zero
		__m128 a0010a0111 = _mm_movelh_ps(a0010a2030, a0111a2131);	// 00, 01, 10, 11
		__m128 a2030a2131 = _mm_movehl_ps(a0111a2131, a0010a2030);	// 02, 03, 12, 13
		r.Packed[0] = _mm_shuffle_ps(a0010a0111, a0212a2232, _MM_SHUFFLE(3, 0, 2, 0)); // 00, 10, 20, 23
		r.Packed[1] = _mm_shuffle_ps(a0010a0111, a0212a2232, _MM_SHUFFLE(3, 1, 3, 1)); // 01, 11, 21, 23
		r.Packed[2] = _mm_shuffle_ps(a2030a2131, a0212a2232, _MM_SHUFFLE(3, 2, 2, 0)); // 02, 12, 22, 23

		// Handle reverse scale
		__m128 sizeSqr;
		// Get squre of size
		sizeSqr = _mm_mul_ps(r.Packed[0], r.Packed[0]);
		sizeSqr = _mm_add_ps(sizeSqr, _mm_mul_ps(r.Packed[1], r.Packed[1]));
		sizeSqr = _mm_add_ps(sizeSqr, _mm_mul_ps(r.Packed[2], r.Packed[2]));

		// avoid divide by 0
		__m128 one = _mm_set1_ps(1.f);
		// for each component, if(sizeSqr < epsilon) sizeSqr = 1;
		__m128 rSizeSqr = _mm_blendv_ps(
			_mm_div_ps(one, sizeSqr),
			one,
			_mm_cmplt_ps(sizeSqr, _mm_set1_ps(std::numeric_limits<float>::epsilon()))
		);

		// Divide by square of scale
		r.Packed[0] = _mm_mul_ps(r.Packed[0], rSizeSqr);
		r.Packed[1] = _mm_mul_ps(r.Packed[1], rSizeSqr);
		r.Packed[2] = _mm_mul_ps(r.Packed[2], rSizeSqr);


		// multiply with inverse rotation/scale
		r.Packed[3] = _mm_mul_ps(r.Packed[0], _mm_shuffle_ps(a0313a2333, a0313a2333, _MM_SHUFFLE(0, 0, 0, 0)));
		r.Packed[3] = _mm_add_ps(r.Packed[3], _mm_mul_ps(r.Packed[1], _mm_shuffle_ps(a0313a2333, a0313a2333, _MM_SHUFFLE(1, 1, 1, 1))));
		r.Packed[3] = _mm_add_ps(r.Packed[3], _mm_mul_ps(r.Packed[2], _mm_shuffle_ps(a0313a2333, a0313a2333, _MM_SHUFFLE(2, 2, 2, 2))));
		r.Packed[3] = _mm_sub_ps(_mm_set_ps(1, 0, 0, 0), r.Packed[3]);

		return r;
	}

}


