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

#include "SFTypedefs.h"

namespace SF {


	static const double C_HALF_PI          =   (3.14159265358979323846264338327950288419716939937510582 * 0.5);
	static const double C_QUARTER_PI       =   (3.14159265358979323846264338327950288419716939937510582 * 0.25);
	static const double C_PI               =   (3.14159265358979323846264338327950288419716939937510582);
	static const double C_TWO_PI           =   (3.14159265358979323846264338327950288419716939937510582 * 2.0);
	static const double C_1_OVER_PI        = (1.0 / C_PI);
	static const double C_1_OVER_TWO_PI    = (1.0 / C_TWO_PI);
	static const double C_1_OVER_255       = (1.0 / float(255));
	static const double C_1_OVER_128       = (1.0 / float(128));
	static const double C_TO_RAD           = (C_PI / float(180));
	static const double C_TO_DEG           = (double(180) / C_PI);
	static const double C_EPSILON          = (10e-6);
	static const double C_DOUBLE_EPSILON   = (10e-6 * 2.0);
	static const double C_BIG_EPS          = (10e-2);
	static const double C_SMALL_EPS        = (10e-6);
	static const double C_SQRTHALF         = (0.7071067811865475244);

	inline double SF_RAD2DEG(double a)     { return ((a)* C_TO_DEG); }
	inline double SF_DEG2RAD(double a)     { return ((a)* C_TO_RAD); }

	template<class DataType>
	inline DataType abs(DataType x)
	{
		return (DataType)(x < 0 ? -x : x);
	}

	template<>
	inline unsigned int abs(unsigned int x)
	{
		return x;
	}

}


