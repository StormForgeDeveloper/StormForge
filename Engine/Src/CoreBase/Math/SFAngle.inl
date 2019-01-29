////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2016 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Math utility
//
////////////////////////////////////////////////////////////////////////////////



namespace SF {

	//////////////////////////////////////////////////////
	// Angle in degree

	Degree::Degree()
	{
	}

	Degree::Degree(float degree)
		: m_DegreeValue(degree)
	{
	}

	constexpr Degree::Degree(float degree)
		: m_DegreeValue(degree)
	{
	}

	Degree::Degree(const Degree& src)
		: m_DegreeValue(src.m_DegreeValue)
	{
	}

	Degree::Degree(const Radian& src)
		: m_DegreeValue(((Degree)src).m_DegreeValue)
	{
	}

	Degree Degree::operator + (const Degree& op) const
	{
		return Degree(m_DegreeValue + op.m_DegreeValue);
	}

	Degree Degree::operator - (const Degree& op) const
	{
		return Degree(m_DegreeValue - op.m_DegreeValue);
	}

	Degree Degree::operator / (const Degree& op) const
	{
		return Degree(m_DegreeValue / op.m_DegreeValue);
	}

	Degree Degree::operator * (const Degree& op) const
	{
		return Degree(m_DegreeValue * op.m_DegreeValue);
	}

	Degree Degree::operator / (float op) const
	{
		return Degree(m_DegreeValue / op);
	}

	Degree Degree::operator * (float op) const
	{
		return Degree(m_DegreeValue / op);
	}

	Degree& Degree::operator += (const Degree& op)
	{
		m_DegreeValue += op.m_DegreeValue;
		return *this;
	}

	Degree& Degree::operator -= (const Degree& op)
	{
		m_DegreeValue -= op.m_DegreeValue;
		return *this;
	}
	Degree& Degree::operator /= (const Degree& op)
	{
		m_DegreeValue /= op.m_DegreeValue;
		return *this;
	}
	Degree& Degree::operator *= (const Degree& op)
	{
		m_DegreeValue *= op.m_DegreeValue;
		return *this;
	}
	Degree& Degree::operator /= (float op)
	{
		m_DegreeValue /= op;
		return *this;
	}
	Degree& Degree::operator *= (float op)
	{
		m_DegreeValue *= op;
		return *this;
	}


	Degree& Degree::operator = (float systemUnit)
	{
		m_DegreeValue = systemUnit;
		return *this;
	}
	Degree& Degree::operator = (const Degree& op)
	{
		m_DegreeValue = op.m_DegreeValue;
		return *this;
	}
	Degree& Degree::operator = (const Radian& op)
	{
		m_DegreeValue = RadToDeg(op.ToRawRadian());
		return *this;
	}

	Degree::operator Radian() const
	{
		return Radian(DegToRad(m_DegreeValue));
	}

	// To Radian value
	Degree::operator float() const
	{
		return ToRawRadian();
	}

	// To system unit(raw radian)
	float Degree::ToRawRadian() const
	{
		return DegToRad(m_DegreeValue);
	}

	inline Degree Degree::FromSystemUnit(float systemUnit)
	{
		return Degree(RadToDeg(systemUnit));
	}


	//////////////////////////////////////////////////////
	// Angle in radian

	Radian::Radian()
	{
	}

	Radian::Radian(float degree)
		: m_RadianValue(degree)
	{
	}

	constexpr Radian::Radian(float degree)
		: m_RadianValue(degree)
	{
	}

	Radian::Radian(const Degree& src)
		: m_RadianValue(src.ToRawRadian())
	{
	}

	Radian::Radian(const Radian& src)
		: m_RadianValue(src.m_RadianValue)
	{
	}

	Radian Radian::operator + (const Radian& op) const
	{
		return Radian(m_RadianValue + op.m_RadianValue);
	}

	Radian Radian::operator - (const Radian& op) const
	{
		return Radian(m_RadianValue - op.m_RadianValue);
	}

	Radian Radian::operator / (const Radian& op) const
	{
		return Radian(m_RadianValue / op.m_RadianValue);
	}

	Radian Radian::operator * (const Radian& op) const
	{
		return Radian(m_RadianValue * op.m_RadianValue);
	}

	Radian Radian::operator / (float op) const
	{
		return Radian(m_RadianValue / op);
	}

	Radian Radian::operator * (float op) const
	{
		return Radian(m_RadianValue / op);
	}

	Radian& Radian::operator += (const Radian& op)
	{
		m_RadianValue += op.m_RadianValue;
		return *this;
	}

	Radian& Radian::operator -= (const Radian& op)
	{
		m_RadianValue -= op.m_RadianValue;
		return *this;
	}
	Radian& Radian::operator /= (const Radian& op)
	{
		m_RadianValue /= op.m_RadianValue;
		return *this;
	}
	Radian& Radian::operator *= (const Radian& op)
	{
		m_RadianValue *= op.m_RadianValue;
		return *this;
	}
	Radian& Radian::operator /= (float op)
	{
		m_RadianValue /= op;
		return *this;
	}
	Radian& Radian::operator *= (float op)
	{
		m_RadianValue *= op;
		return *this;
	}


	Radian& Radian::operator = (float systemUnit)
	{
		m_RadianValue = systemUnit;
		return *this;
	}

	Radian& Radian::operator = (const Degree& op)
	{
		m_RadianValue = op.ToRawRadian();
		return *this;
	}

	Radian& Radian::operator = (const Radian& op)
	{
		m_RadianValue = op.m_RadianValue;
		return *this;
	}

	Radian::operator Degree() const
	{
		return Degree(RadToDeg(m_RadianValue));
	}

	// To raw value
	Radian::operator float() const
	{
		return m_RadianValue;
	}

	// To system unit(raw radian)
	float Radian::ToRawRadian() const
	{
		return m_RadianValue;
	}

	inline Radian Radian::FromSystemUnit(float systemUnit)
	{
		return Radian(systemUnit);
	}


} // namespace SF {
