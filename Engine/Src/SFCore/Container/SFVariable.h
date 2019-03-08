////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2016 StormForge
// 
// Author : KyungKun Ko
//
// Description : Variables
//
////////////////////////////////////////////////////////////////////////////////


#pragma once


#include "SFTypedefs.h"
#include "SFAssert.h"
#include "String/FixedString.h"
#include "String/SFString.h"


namespace SF {



	/////////////////////////////////////////////////////////////////////////////////
	//
	//	variable base class for boxing/unboxing
	//

	class Variable
	{
	private:

	public:

		Variable()
		{
		}

		virtual ~Variable()
		{
		}

		virtual void SetValue(bool value) { unused(value); }
		virtual void SetValue(int value) { unused(value); }
		virtual void SetValue(uint value) { unused(value); }
		virtual void SetValue(int8_t value) { unused(value); }
		virtual void SetValue(uint8_t value) { unused(value); }
		virtual void SetValue(int16_t value) { unused(value); }
		virtual void SetValue(uint16_t value) { unused(value); }
		virtual void SetValue(int32_t value) { unused(value); }
		virtual void SetValue(uint32_t value) { unused(value); }
		virtual void SetValue(int64_t value) { unused(value); }
		virtual void SetValue(uint64_t value) { unused(value); }
		virtual void SetValue(float value) { unused(value); }
		virtual void SetValue(double value) { unused(value); }
		virtual void SetValue(const char* value) { unused(value); }
		virtual void SetValue(const FixedString& value) { unused(value); }

		virtual bool GetValueBool() const { return false; }
		virtual int GetValueInt() const { return 0; }
		virtual uint GetValueUInt() const { return 0; }
		virtual int8_t GetValueInt8() const { return 0; }
		virtual uint8_t GetValueUint8() const { return 0; }
		virtual int16_t GetValueInt16() const { return 0; }
		virtual uint16_t GetValueUInt16() const { return 0; }
		virtual int32_t GetValueInt32() const { return 0; }
		virtual uint32_t GetValueUInt32() const { return 0; }
		virtual int64_t GetValueInt64() const { return 0; }
		virtual uint64_t GetValueUInt64() const { return 0; }
		virtual float GetValueFloat() const { return 0; }
		virtual double GetValueDouble() const { return 0; }
		virtual const String& GetValueString() const { return String::Empty; }
		virtual const FixedString& GetValueFixedString() const { return FixedString::Empty; }
	};


	//////////////////////////////////////////////////////////////////////////////////////////////////
	//
	//	Variable bool
	//

	class VariableBool : public Variable
	{
	private:
		bool m_Value;

	public:
		VariableBool()
			: m_Value(false)
		{
		}
		VariableBool(bool value)
			: m_Value(value)
		{
		}

		virtual void SetValue(bool value) override { m_Value = value; }
		virtual void SetValue(int value) override { m_Value = value == 0 ? false : true; }
		virtual void SetValue(uint value) override { m_Value = value == 0 ? false : true; }
		virtual void SetValue(int8_t value) override { m_Value = value == 0 ? false : true; }
		virtual void SetValue(uint8_t value) override { m_Value = value == 0 ? false : true; }
		virtual void SetValue(int16_t value) override { m_Value = value == 0 ? false : true; }
		virtual void SetValue(uint16_t value) override { m_Value = value == 0 ? false : true; }
		virtual void SetValue(int32_t value) override { m_Value = value == 0 ? false : true; }
		virtual void SetValue(uint32_t value) override { m_Value = value == 0 ? false : true; }
		virtual void SetValue(int64_t value) override { m_Value = value == 0 ? false : true; }
		virtual void SetValue(uint64_t value) override { m_Value = value == 0 ? false : true; }
		virtual void SetValue(float value) override { m_Value = value == 0 ? false : true; }
		virtual void SetValue(double value) override { m_Value = value == 0 ? false : true; }

		virtual bool GetValueBool() const override { return m_Value; }
		virtual int GetValueInt() const override { return m_Value ? 1 : 0; }
		virtual uint GetValueUInt() const override { return m_Value ? 1 : 0; }
		virtual int8_t GetValueInt8() const override { return m_Value ? 1 : 0; }
		virtual uint8_t GetValueUint8() const override { return m_Value ? 1 : 0; }
		virtual int16_t GetValueInt16() const override { return m_Value ? 1 : 0; }
		virtual uint16_t GetValueUInt16() const override { return m_Value ? 1 : 0; }
		virtual int32_t GetValueInt32() const override { return m_Value ? 1 : 0; }
		virtual uint32_t GetValueUInt32() const override { return m_Value ? 1 : 0; }
		virtual int64_t GetValueInt64() const override { return m_Value ? 1 : 0; }
		virtual uint64_t GetValueUInt64() const override { return m_Value ? 1 : 0; }
		virtual float GetValueFloat() const override { return m_Value ? 1 : 0; }
		virtual double GetValueDouble() const override { return m_Value ? 1 : 0; }

	};


	//////////////////////////////////////////////////////////////////////////////////////////////////
	//
	//	Variable int
	//

	class VariableInt : public Variable
	{
	private:
		int m_Value;

	public:
		VariableInt()
			: m_Value(0)
		{
		}
		VariableInt(int value)
			: m_Value(value)
		{
		}

		virtual void SetValue(bool value) override { m_Value = value == false ? 0 : 1; }
		virtual void SetValue(int value) override { m_Value = value; }
		virtual void SetValue(uint value) override { m_Value = (uint)value; }
		virtual void SetValue(int8_t value) override { m_Value = (int8_t)value; }
		virtual void SetValue(uint8_t value) override { m_Value = (uint8_t)value; }
		virtual void SetValue(int16_t value) override { m_Value = (int16_t)value; }
		virtual void SetValue(uint16_t value) override { m_Value = (uint16_t)value; }
		virtual void SetValue(int32_t value) override { m_Value = (int32_t)value; }
		virtual void SetValue(uint32_t value) override { m_Value = (uint32_t)value; }
		virtual void SetValue(int64_t value) override { m_Value = (int64_t)value; }
		virtual void SetValue(uint64_t value) override { m_Value = (uint64_t)value; }
		virtual void SetValue(float value) override { m_Value = value; }
		virtual void SetValue(double value) override { m_Value = value; }

		virtual bool GetValueBool() const override { return m_Value != 0; }
		virtual int GetValueInt() const override { return m_Value; }
		virtual uint GetValueUInt() const override { return (uint)m_Value; }
		virtual int8_t GetValueInt8() const override { return (int8_t)m_Value; }
		virtual uint8_t GetValueUint8() const override { return (uint8_t)m_Value; }
		virtual int16_t GetValueInt16() const override { return (int16_t)m_Value; }
		virtual uint16_t GetValueUInt16() const override { return (uint16_t)m_Value; }
		virtual int32_t GetValueInt32() const override { return (int32_t)m_Value; }
		virtual uint32_t GetValueUInt32() const override { return (uint32_t)m_Value; }
		virtual int64_t GetValueInt64() const override { return (int64_t)m_Value; }
		virtual uint64_t GetValueUInt64() const override { return (uint64_t)m_Value; }
		virtual float GetValueFloat() const override { return (float)m_Value; }
		virtual double GetValueDouble() const override { return (double)m_Value; }

	};


	//////////////////////////////////////////////////////////////////////////////////////////////////
	//
	//	Variable int
	//

	class VariableUInt : public Variable
	{
	private:
		uint m_Value;

	public:
		VariableUInt()
			: m_Value(0)
		{
		}
		VariableUInt(uint value)
			: m_Value(value)
		{
		}

		virtual void SetValue(bool value) { m_Value = value == false ? 0 : 1; }
		virtual void SetValue(int value) { m_Value = (int)value; }
		virtual void SetValue(uint value) { m_Value = (uint)value; }
		virtual void SetValue(int8_t value) { m_Value = (int8_t)value; }
		virtual void SetValue(uint8_t value) { m_Value = (uint8_t)value; }
		virtual void SetValue(int16_t value) { m_Value = (int16_t)value; }
		virtual void SetValue(uint16_t value) { m_Value = (uint16_t)value; }
		virtual void SetValue(int32_t value) { m_Value = (int32_t)value; }
		virtual void SetValue(uint32_t value) { m_Value = (uint32_t)value; }
		virtual void SetValue(int64_t value) { m_Value = (int64_t)value; }
		virtual void SetValue(uint64_t value) { m_Value = (uint64_t)value; }
		virtual void SetValue(float value) { m_Value = value; }
		virtual void SetValue(double value) { m_Value = value; }

		virtual bool GetValueBool() const { return m_Value != 0; }
		virtual int GetValueInt() const { return (int)m_Value; }
		virtual uint GetValueUInt() const { return (uint)m_Value; }
		virtual int8_t GetValueInt8() const { return (int8_t)m_Value; }
		virtual uint8_t GetValueUint8() const { return (uint8_t)m_Value; }
		virtual int16_t GetValueInt16() const { return (int16_t)m_Value; }
		virtual uint16_t GetValueUInt16() const { return (uint16_t)m_Value; }
		virtual int32_t GetValueInt32() const { return (int32_t)m_Value; }
		virtual uint32_t GetValueUInt32() const { return (uint32_t)m_Value; }
		virtual int64_t GetValueInt64() const { return (int64_t)m_Value; }
		virtual uint64_t GetValueUInt64() const { return (uint64_t)m_Value; }
		virtual float GetValueFloat() const { return (float)m_Value; }
		virtual double GetValueDouble() const { return (double)m_Value; }

	};



} // namespace SF




