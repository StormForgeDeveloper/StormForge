////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2016 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Math utility
//
////////////////////////////////////////////////////////////////////////////////


#pragma once

#include "Math/SFMathConsts.h"

namespace SF {

	class Radian;

	//////////////////////////////////////////////////////
	// Angle conversion

	inline float RadToDeg(float radian) { return float(radian / C_PI * 360.f); }
	inline float DegToRad(float degree) { return float(degree / 360.f * C_PI); }


	//////////////////////////////////////////////////////
	// Angle in degree
	class Degree
	{
	private:
		float m_DegreeValue;

	public:
		Degree();
		explicit Degree(float degree);
		Degree(const Degree& src);
		Degree(const Radian& src);

		Degree operator + (const Degree& op) const;
		Degree operator - (const Degree& op) const;
		Degree operator / (const Degree& op) const;
		Degree operator * (const Degree& op) const;
		Degree operator / (float op) const;
		Degree operator * (float op) const;

		Degree& operator += (const Degree& op);
		Degree& operator -= (const Degree& op);
		Degree& operator /= (const Degree& op);
		Degree& operator *= (const Degree& op);
		Degree& operator /= (float op);
		Degree& operator *= (float op);


		Degree& operator = (float systemUnit);
		Degree& operator = (const Degree& op);
		Degree& operator = (const Radian& op);

		explicit operator Radian() const;

		// To Radian value, automatic float case always uses radian
		explicit operator float() const;
		// To system unit(raw radian)
		float ToRawRadian() const;

		static Degree FromSystemUnit(float systemUnit);
	};


	///////////////////////////////////////////////////////
	// Angle in radian
	class Radian
	{
	private:
		float m_RadianValue;

	public:
		Radian();
		Radian(float radian);
		Radian(const Degree& src);
		Radian(const Radian& src);

		Radian operator + (const Radian& op) const;
		Radian operator - (const Radian& op) const;
		Radian operator / (const Radian& op) const;
		Radian operator * (const Radian& op) const;
		Radian operator / (float op) const;
		Radian operator * (float op) const;

		Radian& operator += (const Radian& op);
		Radian& operator -= (const Radian& op);
		Radian& operator /= (const Radian& op);
		Radian& operator *= (const Radian& op);
		Radian& operator /= (float op);
		Radian& operator *= (float op);

		Radian& operator = (float systemUnit);
		Radian& operator = (const Degree& op);
		Radian& operator = (const Radian& op);

		explicit operator Degree() const;

		// To raw value
		explicit operator float() const;

		// To system unit(raw radian)
		float ToRawRadian() const;

		static Radian FromSystemUnit(float systemUnit);
	};

}; // namespace SF



#include "SFAngle.inl"

