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


	static constexpr double C_HALF_PI          =   (3.14159265358979323846264338327950288419716939937510582 * 0.5);
	static constexpr double C_QUARTER_PI       =   (3.14159265358979323846264338327950288419716939937510582 * 0.25);
	static constexpr double C_PI               =   (3.14159265358979323846264338327950288419716939937510582);
	static constexpr double C_TWO_PI           =   (3.14159265358979323846264338327950288419716939937510582 * 2.0);
	static constexpr double C_1_OVER_PI        = (1.0 / C_PI);
	static constexpr double C_1_OVER_TWO_PI    = (1.0 / C_TWO_PI);
	static constexpr double C_1_OVER_255       = (1.0 / float(255));
	static constexpr double C_1_OVER_128       = (1.0 / float(128));
	static constexpr double C_TO_RAD           = (C_PI / float(180));
	static constexpr double C_TO_DEG           = (double(180) / C_PI);
	static constexpr double C_EPSILON          = (10e-6);
	static constexpr double C_DOUBLE_EPSILON   = (10e-6 * 2.0);
	static constexpr double C_BIG_EPS          = (10e-2);
	static constexpr double C_SMALL_EPS        = (10e-6);
	static constexpr double C_SQRTHALF         = (0.7071067811865475244);

	static constexpr float C_FHALF_PI = static_cast<float>(C_HALF_PI);
	static constexpr float C_FQUARTER_PI = static_cast<float>(3.14159265358979323846264338327950288419716939937510582 * 0.25);
	static constexpr float C_FPI = static_cast<float>(3.14159265358979323846264338327950288419716939937510582);
	static constexpr float C_FTWO_PI = static_cast<float>(3.14159265358979323846264338327950288419716939937510582 * 2.0);
	static constexpr float C_F1_OVER_PI = static_cast<float>(1.0 / C_PI);
	static constexpr float C_F1_OVER_TWO_PI = static_cast<float>(1.0 / C_TWO_PI);
	static constexpr float C_F1_OVER_255 = static_cast<float>(1.0 / float(255));
	static constexpr float C_F1_OVER_128 = static_cast<float>(1.0 / float(128));
	static constexpr float C_FTO_RAD = static_cast<float>(C_PI / float(180));
	static constexpr float C_FTO_DEG = static_cast<float>(double(180) / C_PI);
	static constexpr float C_FEPSILON = static_cast<float>(10e-6);
	static constexpr float C_FDOUBLE_EPSILON = static_cast<float>(10e-6 * 2.0);
	static constexpr float C_FBIG_EPS = static_cast<float>(10e-2);
	static constexpr float C_FSMALL_EPS = static_cast<float>(10e-6);
	static constexpr float C_FSQRTHALF = static_cast<float>(0.7071067811865475244);

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


