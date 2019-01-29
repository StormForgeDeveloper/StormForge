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


namespace SF
{
	//  This function is only faster when you use with register variable
	template<unsigned i>
	inline float PackedSSEGet(__m128 V)
	{
#ifdef __SSE4_1__
		return _mm_extract_epi32(V, i);
#else
		float ret;
		// shuffle V so that the element that you want is moved to the least-
		// significant element of the vector (V[0])
		V = _mm_shuffle_ps(V, V, _MM_SHUFFLE(i, i, i, i));
		// return the value in V[0]
		return _mm_cvtss_f32(V);
#endif
	}

}





