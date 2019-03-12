////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2016 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Variables
//
////////////////////////////////////////////////////////////////////////////////


#pragma once


#include "SFTypedefs.h"
#include "SFAssert.h"
#include "String/SFFixedString.h"
#include "String/SFFixedString32.h"
#include "String/SFString.h"


namespace SF {


	struct ToStringContext;


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

		virtual FixedString GetTypeName() const = 0;


		virtual void SetValue(bool value) { unused(value); }
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
		virtual void SetValue(const wchar_t* value) { unused(value); }
		virtual void SetValue(const String& value) { unused(value); }
		virtual void SetValue(FixedString32 value) { unused(value); }
		virtual void SetValue(FixedString value) { unused(value); }


		virtual void* GetDataPtr() const { return nullptr; }
		virtual bool GetValueBool() const { return false; }
		virtual int8_t GetValueInt8() const { return 0; }
		virtual uint8_t GetValueUInt8() const { return 0; }
		virtual int16_t GetValueInt16() const { return 0; }
		virtual uint16_t GetValueUInt16() const { return 0; }
		virtual int32_t GetValueInt32() const { return 0; }
		virtual uint32_t GetValueUInt32() const { return 0; }
		virtual int64_t GetValueInt64() const { return 0; }
		virtual uint64_t GetValueUInt64() const { return 0; }
		virtual float GetValueFloat() const { return 0; }
		virtual double GetValueDouble() const { return 0; }
		virtual String GetValueString() const { return String::Empty; }
		virtual const char* GetValueCharString() const { return nullptr; }
		virtual const wchar_t* GetValueWCharString() const { return nullptr; }
		virtual FixedString32 GetValueFixedString32() const { return FixedString32(); }
		virtual FixedString GetValueFixedString() const { return FixedString(); }

		// Template implementation for type based GetValue access
		template<class ValueType>
		ValueType GetValue();

		// Variable instance size
		virtual size_t GetVariableSize() const { return sizeof(Variable); }

		// Clone variable into given buffer, the buffer should have enough space for the variable instance.
		// To get variable instance size call GetVariableSize
		//  @buffer: It uses external buffer for new instance allocation. Use ExternalBufferArray if you want to use manually allocated buffer.
		//  @return: nullptr if fails to create a copy
		virtual Variable* Clone(Array<uint8_t>& buffer) const = 0;
		virtual Variable* Clone(IHeap& heap) const = 0;

		// To string implementation
		virtual Result ToString(ToStringContext& context) const { return ResultCode::NOT_IMPLEMENTED; }

		virtual bool IsEqualTypeNValue (const Variable& op) const;
		virtual bool operator == (const Variable& op) const;
	};



	template<> inline bool Variable::GetValue<bool>() { return GetValueBool(); }
	template<> inline int8_t Variable::GetValue<int8_t>() { return GetValueInt8(); }
	template<> inline uint8_t Variable::GetValue<uint8_t>() { return GetValueUInt8(); }
	template<> inline int16_t Variable::GetValue<int16_t>() { return GetValueInt16(); }
	template<> inline uint16_t Variable::GetValue<uint16_t>() { return GetValueUInt16(); }
	template<> inline int32_t Variable::GetValue<int32_t>() { return GetValueInt32(); }
	template<> inline uint32_t Variable::GetValue<uint32_t>() { return GetValueUInt32(); }
	template<> inline int64_t Variable::GetValue<int64_t>() { return GetValueInt64(); }
	template<> inline uint64_t Variable::GetValue<uint64_t>() { return GetValueUInt64(); }
	template<> inline float Variable::GetValue<float>() { return GetValueFloat(); }
	template<> inline double Variable::GetValue<double>() { return GetValueDouble(); }
	template<> inline String Variable::GetValue<String>() { return GetValueString(); }
	template<> inline const char* Variable::GetValue<const char*>() { return GetValueCharString(); }
	template<> inline const wchar_t* Variable::GetValue<const wchar_t*>() { return GetValueWCharString(); }
	template<> inline FixedString32 Variable::GetValue<FixedString32>() { return GetValueFixedString32(); }
	template<> inline FixedString Variable::GetValue<FixedString>() { return GetValueFixedString(); }




	//////////////////////////////////////////////////////////////////////////////////////////////////
	//
	//	Variable bool
	//

	class VariableBool : public Variable
	{
	public:

		static constexpr FixedString TYPE_NAME = "bool";

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

		virtual FixedString GetTypeName() const override { return TYPE_NAME; }

		virtual void SetValue(bool value) override { m_Value = value; }
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
		virtual void SetValue(const char* value) override { m_Value = (value == nullptr || String::False.IsEqualIgnoreCase(value)) ? false : true; }
		virtual void SetValue(const String& value) override { m_Value = (value == nullptr || String::False.IsEqualIgnoreCase(value)) ? false : true; }
		virtual void SetValue(FixedString32 value) override { m_Value = (value == nullptr || value == "false" || value == "False") ? false : true; }
		virtual void SetValue(FixedString value) override { m_Value = (value == nullptr || value == "false" || value == "False") ? false : true; }

		virtual void* GetDataPtr() const override { return (void*)&m_Value; }
		virtual bool GetValueBool() const override { return m_Value; }
		virtual int8_t GetValueInt8() const override { return m_Value ? 1 : 0; }
		virtual uint8_t GetValueUInt8() const override { return m_Value ? 1 : 0; }
		virtual int16_t GetValueInt16() const override { return m_Value ? 1 : 0; }
		virtual uint16_t GetValueUInt16() const override { return m_Value ? 1 : 0; }
		virtual int32_t GetValueInt32() const override { return m_Value ? 1 : 0; }
		virtual uint32_t GetValueUInt32() const override { return m_Value ? 1 : 0; }
		virtual int64_t GetValueInt64() const override { return m_Value ? 1 : 0; }
		virtual uint64_t GetValueUInt64() const override { return m_Value ? 1 : 0; }
		virtual float GetValueFloat() const override { return m_Value ? 1.f : 0.f; }
		virtual double GetValueDouble() const override { return m_Value ? 1 : 0; }
		virtual String GetValueString() const override { return m_Value ? String::True : String::False; }
		virtual FixedString32 GetValueFixedString32() const override { return m_Value ? "true" : "false"; }
		virtual FixedString GetValueFixedString() const override { return m_Value ? "true" : "false"; }

		virtual Result ToString(ToStringContext& context) const override;

		virtual Variable* Clone(Array<uint8_t>& buffer) const override;
		virtual Variable* Clone(IHeap& heap) const override;

		virtual bool operator == (const Variable& op) const override;
	};


	//////////////////////////////////////////////////////////////////////////////////////////////////
	//
	//	Variable void*
	//

	class VariableVoidP : public Variable
	{
	public:

		static constexpr FixedString TYPE_NAME = "void*";

	private:
		void* m_Value = nullptr;

	public:

		VariableVoidP()
			: m_Value(nullptr)
		{
		}

		VariableVoidP(void* value)
			: m_Value(value)
		{
		}

		virtual FixedString GetTypeName() const override { return TYPE_NAME; }

		virtual void SetValue(int64_t value) override { m_Value = (void*)value; }
		virtual void SetValue(uint64_t value) override { m_Value = (void*)value; }
		virtual void SetValue(const char* value) override { m_Value = (void*)value; }
		virtual void SetValue(const String& value) override { m_Value = (void*)(const char*)value; }

		virtual void* GetDataPtr() const override { return m_Value; }
		virtual bool GetValueBool() const override { return m_Value != nullptr; }
		virtual int64_t GetValueInt64() const override { return (int64_t)m_Value; }
		virtual uint64_t GetValueUInt64() const override { return (uint64_t)m_Value; }

		virtual Result ToString(ToStringContext& context) const override;

		virtual Variable* Clone(Array<uint8_t>& buffer) const override;
		virtual Variable* Clone(IHeap& heap) const override;
	};


	//////////////////////////////////////////////////////////////////////////////////////////////////
	//
	//	Variable int
	//

	class VariableInt : public Variable
	{
	public:

		static constexpr FixedString TYPE_NAME = "int";

	private:
		int32_t m_Value;

	public:

		VariableInt()
			: m_Value(0)
		{
		}

		VariableInt(int32_t value)
			: m_Value(value)
		{
		}

		virtual FixedString GetTypeName() const override { return TYPE_NAME; }

		virtual void SetValue(bool value) override { m_Value = value == false ? 0 : 1; }
		virtual void SetValue(int8_t value) override { m_Value = (int8_t)value; }
		virtual void SetValue(uint8_t value) override { m_Value = (uint8_t)value; }
		virtual void SetValue(int16_t value) override { m_Value = (int16_t)value; }
		virtual void SetValue(uint16_t value) override { m_Value = (uint16_t)value; }
		virtual void SetValue(int32_t value) override { m_Value = (int32_t)value; }
		virtual void SetValue(uint32_t value) override { m_Value = (uint32_t)value; }
		virtual void SetValue(int64_t value) override { m_Value = (int32_t)value; }
		virtual void SetValue(uint64_t value) override { m_Value = (uint32_t)value; }
		virtual void SetValue(float value) override { m_Value = (int32_t)value; }
		virtual void SetValue(double value) override { m_Value = (int32_t)value; }
		virtual void SetValue(const char* value) override;
		virtual void SetValue(const String& value) override;
		virtual void SetValue(FixedString value) override;

		virtual void* GetDataPtr() const override { return (void*)&m_Value; }
		virtual bool GetValueBool() const override { return m_Value != 0; }
		virtual int8_t GetValueInt8() const override { return (int8_t)m_Value; }
		virtual uint8_t GetValueUInt8() const override { return (uint8_t)m_Value; }
		virtual int16_t GetValueInt16() const override { return (int16_t)m_Value; }
		virtual uint16_t GetValueUInt16() const override { return (uint16_t)m_Value; }
		virtual int32_t GetValueInt32() const override { return (int32_t)m_Value; }
		virtual uint32_t GetValueUInt32() const override { return (uint32_t)m_Value; }
		virtual int64_t GetValueInt64() const override { return (int64_t)m_Value; }
		virtual uint64_t GetValueUInt64() const override { return (uint64_t)m_Value; }
		virtual float GetValueFloat() const override { return (float)m_Value; }
		virtual double GetValueDouble() const override { return (double)m_Value; }
		virtual FixedString GetValueFixedString() const override;
		virtual String GetValueString() const override;

		virtual Result ToString(ToStringContext& context) const override;

		virtual Variable* Clone(Array<uint8_t>& buffer) const override;
		virtual Variable* Clone(IHeap& heap) const override;
	};


	//////////////////////////////////////////////////////////////////////////////////////////////////
	//
	//	Variable uint
	//

	class VariableUInt : public Variable
	{
	public:

		static constexpr FixedString TYPE_NAME = "uint";

	private:
		uint32_t m_Value;

	public:
		VariableUInt()
			: m_Value(0)
		{
		}
		VariableUInt(uint32_t value)
			: m_Value(value)
		{
		}

		virtual FixedString GetTypeName() const override { return TYPE_NAME; }

		virtual void SetValue(bool value) override { m_Value = value == false ? 0 : 1; }
		virtual void SetValue(int8_t value) override { m_Value = (int8_t)value; }
		virtual void SetValue(uint8_t value) override { m_Value = (uint8_t)value; }
		virtual void SetValue(int16_t value) override { m_Value = (int16_t)value; }
		virtual void SetValue(uint16_t value) override { m_Value = (uint16_t)value; }
		virtual void SetValue(int32_t value) override { m_Value = (int32_t)value; }
		virtual void SetValue(uint32_t value) override { m_Value = (uint32_t)value; }
		virtual void SetValue(int64_t value) override { m_Value = (uint32_t)value; }
		virtual void SetValue(uint64_t value) override { m_Value = (uint32_t)value; }
		virtual void SetValue(float value) override { m_Value = (uint32_t)value; }
		virtual void SetValue(double value) override { m_Value = (uint32_t)value; }
		virtual void SetValue(const char* value) override;
		virtual void SetValue(const String& value) override;
		virtual void SetValue(FixedString value) override;

		virtual void* GetDataPtr() const override { return (void*)&m_Value; }
		virtual bool GetValueBool() const override { return m_Value != 0; }
		virtual int8_t GetValueInt8() const override { return (int8_t)m_Value; }
		virtual uint8_t GetValueUInt8() const override { return (uint8_t)m_Value; }
		virtual int16_t GetValueInt16() const override { return (int16_t)m_Value; }
		virtual uint16_t GetValueUInt16() const override { return (uint16_t)m_Value; }
		virtual int32_t GetValueInt32() const override { return (int32_t)m_Value; }
		virtual uint32_t GetValueUInt32() const override { return (uint32_t)m_Value; }
		virtual int64_t GetValueInt64() const override { return (int64_t)m_Value; }
		virtual uint64_t GetValueUInt64() const override { return (uint64_t)m_Value; }
		virtual float GetValueFloat() const override { return (float)m_Value; }
		virtual double GetValueDouble() const override { return (double)m_Value; }
		virtual FixedString GetValueFixedString() const override;
		virtual String GetValueString() const override;

		virtual Result ToString(ToStringContext& context) const override;

		virtual Variable* Clone(Array<uint8_t>& buffer) const override;
		virtual Variable* Clone(IHeap& heap) const override;
	};



	//////////////////////////////////////////////////////////////////////////////////////////////////
	//
	//	Variable Result
	//

	class VariableResult : public Variable
	{
	public:

		static constexpr FixedString TYPE_NAME = "Result";

	private:
		Result m_Value;

	public:
		VariableResult()
		{
		}
		VariableResult(Result value)
			: m_Value(value)
		{
		}

		virtual FixedString GetTypeName() const override { return TYPE_NAME; }

		virtual void SetValue(bool value) override { m_Value = value == false ? ResultCode::FAIL : ResultCode::SUCCESS; }
		virtual void SetValue(int8_t value) override { m_Value = (int8_t)value; }
		virtual void SetValue(uint8_t value) override { m_Value = (uint8_t)value; }
		virtual void SetValue(int16_t value) override { m_Value = (int16_t)value; }
		virtual void SetValue(uint16_t value) override { m_Value = (uint16_t)value; }
		virtual void SetValue(int32_t value) override { m_Value = (int32_t)value; }
		virtual void SetValue(uint32_t value) override { m_Value = (uint32_t)value; }
		virtual void SetValue(int64_t value) override { m_Value = (uint32_t)value; }
		virtual void SetValue(uint64_t value) override { m_Value = (uint32_t)value; }
		virtual void SetValue(float value) override { m_Value = (uint32_t)value; }
		virtual void SetValue(double value) override { m_Value = (uint32_t)value; }

		virtual void* GetDataPtr() const override { return (void*)&m_Value; }
		virtual bool GetValueBool() const override { return m_Value; }
		virtual int8_t GetValueInt8() const override { return (int8_t)m_Value; }
		virtual uint8_t GetValueUInt8() const override { return (uint8_t)m_Value; }
		virtual int16_t GetValueInt16() const override { return (int16_t)m_Value; }
		virtual uint16_t GetValueUInt16() const override { return (uint16_t)m_Value; }
		virtual int32_t GetValueInt32() const override { return (int32_t)m_Value; }
		virtual uint32_t GetValueUInt32() const override { return (uint32_t)m_Value; }
		virtual int64_t GetValueInt64() const override { return (int64_t)m_Value; }
		virtual uint64_t GetValueUInt64() const override { return (uint64_t)m_Value; }
		virtual float GetValueFloat() const override { return (float)m_Value; }
		virtual double GetValueDouble() const override { return (double)m_Value; }
		virtual FixedString GetValueFixedString() const override { return m_Value ? "SUCCESS" : "FAIL"; }
		virtual String GetValueString() const override { return m_Value ? "SUCCESS" : "FAIL"; }

		virtual Result ToString(ToStringContext& context) const override;

		virtual Variable* Clone(Array<uint8_t>& buffer) const override;
		virtual Variable* Clone(IHeap& heap) const override;
	};



	//////////////////////////////////////////////////////////////////////////////////////////////////
	//
	//	Variable int64
	//

	class VariableInt64 : public Variable
	{
	public:

		static constexpr FixedString TYPE_NAME = "int64";

	private:
		int64_t m_Value;

	public:

		VariableInt64()
			: m_Value(0)
		{
		}

		VariableInt64(int64_t value)
			: m_Value(value)
		{
		}

		virtual FixedString GetTypeName() const override { return TYPE_NAME; }

		virtual void SetValue(bool value) override { m_Value = value == false ? 0 : 1; }
		virtual void SetValue(int8_t value) override { m_Value = (int8_t)value; }
		virtual void SetValue(uint8_t value) override { m_Value = (uint8_t)value; }
		virtual void SetValue(int16_t value) override { m_Value = (int16_t)value; }
		virtual void SetValue(uint16_t value) override { m_Value = (uint16_t)value; }
		virtual void SetValue(int32_t value) override { m_Value = (int32_t)value; }
		virtual void SetValue(uint32_t value) override { m_Value = (uint32_t)value; }
		virtual void SetValue(int64_t value) override { m_Value = (int32_t)value; }
		virtual void SetValue(uint64_t value) override { m_Value = (uint32_t)value; }
		virtual void SetValue(float value) override { m_Value = (int32_t)value; }
		virtual void SetValue(double value) override { m_Value = (int32_t)value; }
		virtual void SetValue(const char* value) override;
		virtual void SetValue(const String& value) override;
		virtual void SetValue(FixedString value) override;

		virtual void* GetDataPtr() const override { return (void*)&m_Value; }
		virtual bool GetValueBool() const override { return m_Value != 0; }
		virtual int8_t GetValueInt8() const override { return (int8_t)m_Value; }
		virtual uint8_t GetValueUInt8() const override { return (uint8_t)m_Value; }
		virtual int16_t GetValueInt16() const override { return (int16_t)m_Value; }
		virtual uint16_t GetValueUInt16() const override { return (uint16_t)m_Value; }
		virtual int32_t GetValueInt32() const override { return (int32_t)m_Value; }
		virtual uint32_t GetValueUInt32() const override { return (uint32_t)m_Value; }
		virtual int64_t GetValueInt64() const override { return (int64_t)m_Value; }
		virtual uint64_t GetValueUInt64() const override { return (uint64_t)m_Value; }
		virtual float GetValueFloat() const override { return (float)m_Value; }
		virtual double GetValueDouble() const override { return (double)m_Value; }
		virtual FixedString GetValueFixedString() const override;
		virtual String GetValueString() const override;

		virtual Result ToString(ToStringContext& context) const override;

		virtual Variable* Clone(Array<uint8_t>& buffer) const override;
		virtual Variable* Clone(IHeap& heap) const override;
	};


	//////////////////////////////////////////////////////////////////////////////////////////////////
	//
	//	Variable uint64
	//

	class VariableUInt64 : public Variable
	{
	public:

		static constexpr FixedString TYPE_NAME = "uint64";

	private:
		uint64_t m_Value;

	public:
		VariableUInt64()
			: m_Value(0)
		{
		}
		VariableUInt64(uint64_t value)
			: m_Value(value)
		{
		}

		virtual FixedString GetTypeName() const override { return TYPE_NAME; }

		virtual void SetValue(bool value) override { m_Value = value == false ? 0 : 1; }
		virtual void SetValue(int8_t value) override { m_Value = (uint64_t)value; }
		virtual void SetValue(uint8_t value) override { m_Value = (uint64_t)value; }
		virtual void SetValue(int16_t value) override { m_Value = (uint64_t)value; }
		virtual void SetValue(uint16_t value) override { m_Value = (uint64_t)value; }
		virtual void SetValue(int32_t value) override { m_Value = (uint64_t)value; }
		virtual void SetValue(uint32_t value) override { m_Value = (uint64_t)value; }
		virtual void SetValue(int64_t value) override { m_Value = (uint64_t)value; }
		virtual void SetValue(uint64_t value) override { m_Value = (uint64_t)value; }
		virtual void SetValue(float value) override { m_Value = (uint64_t)value; }
		virtual void SetValue(double value) override { m_Value = (uint64_t)value; }
		virtual void SetValue(const char* value) override;
		virtual void SetValue(const String& value) override;
		virtual void SetValue(FixedString value) override;

		virtual void* GetDataPtr() const override { return (void*)&m_Value; }
		virtual bool GetValueBool() const override { return m_Value != 0; }
		virtual int8_t GetValueInt8() const override { return (int8_t)m_Value; }
		virtual uint8_t GetValueUInt8() const override { return (uint8_t)m_Value; }
		virtual int16_t GetValueInt16() const override { return (int16_t)m_Value; }
		virtual uint16_t GetValueUInt16() const override { return (uint16_t)m_Value; }
		virtual int32_t GetValueInt32() const override { return (int32_t)m_Value; }
		virtual uint32_t GetValueUInt32() const override { return (uint32_t)m_Value; }
		virtual int64_t GetValueInt64() const override { return (int64_t)m_Value; }
		virtual uint64_t GetValueUInt64() const override { return (uint64_t)m_Value; }
		virtual float GetValueFloat() const override { return (float)m_Value; }
		virtual double GetValueDouble() const override { return (double)m_Value; }
		virtual FixedString GetValueFixedString() const override;
		virtual String GetValueString() const override;

		virtual Result ToString(ToStringContext& context) const override;

		virtual Variable* Clone(Array<uint8_t>& buffer) const override;
		virtual Variable* Clone(IHeap& heap) const override;
	};


	//////////////////////////////////////////////////////////////////////////////////////////////////
	//
	//	Variable float
	//

	class VariableFloat : public Variable
	{
	public:

		static constexpr FixedString TYPE_NAME = "float";

	private:
		float m_Value;

	public:

		VariableFloat()
			: m_Value(0)
		{
		}

		VariableFloat(float value)
			: m_Value(value)
		{
		}

		virtual FixedString GetTypeName() const override { return TYPE_NAME; }

		virtual void SetValue(bool value) override { m_Value = value == false ? 0.f : 1.f; }
		virtual void SetValue(int8_t value) override { m_Value = (float)value; }
		virtual void SetValue(uint8_t value) override { m_Value = (float)value; }
		virtual void SetValue(int16_t value) override { m_Value = (float)value; }
		virtual void SetValue(uint16_t value) override { m_Value = (float)value; }
		virtual void SetValue(int32_t value) override { m_Value = (float)value; }
		virtual void SetValue(uint32_t value) override { m_Value = (float)value; }
		virtual void SetValue(int64_t value) override { m_Value = (float)value; }
		virtual void SetValue(uint64_t value) override { m_Value = (float)value; }
		virtual void SetValue(float value) override { m_Value = (float)value; }
		virtual void SetValue(double value) override { m_Value = (float)value; }
		virtual void SetValue(const char* value) override;
		virtual void SetValue(const String& value) override;
		virtual void SetValue(FixedString value) override;

		virtual void* GetDataPtr() const override { return (void*)&m_Value; }
		virtual bool GetValueBool() const override { return m_Value != 0; }
		virtual int8_t GetValueInt8() const override { return (int8_t)m_Value; }
		virtual uint8_t GetValueUInt8() const override { return (uint8_t)m_Value; }
		virtual int16_t GetValueInt16() const override { return (int16_t)m_Value; }
		virtual uint16_t GetValueUInt16() const override { return (uint16_t)m_Value; }
		virtual int32_t GetValueInt32() const override { return (int32_t)m_Value; }
		virtual uint32_t GetValueUInt32() const override { return (uint32_t)m_Value; }
		virtual int64_t GetValueInt64() const override { return (int64_t)m_Value; }
		virtual uint64_t GetValueUInt64() const override { return (uint64_t)m_Value; }
		virtual float GetValueFloat() const override { return (float)m_Value; }
		virtual double GetValueDouble() const override { return (double)m_Value; }
		virtual FixedString GetValueFixedString() const override;
		virtual String GetValueString() const override;

		virtual Result ToString(ToStringContext& context) const override;

		virtual Variable* Clone(Array<uint8_t>& buffer) const override;
		virtual Variable* Clone(IHeap& heap) const override;

		virtual bool operator == (const Variable& op) const override;
	};


	//////////////////////////////////////////////////////////////////////////////////////////////////
	//
	//	Variable double
	//

	class VariableDouble : public Variable
	{
	public:

		static constexpr FixedString TYPE_NAME = "double";

	private:
		double m_Value;

	public:
		VariableDouble()
			: m_Value(0)
		{
		}
		VariableDouble(double value)
			: m_Value(value)
		{
		}

		virtual FixedString GetTypeName() const override { return TYPE_NAME; }

		virtual void SetValue(bool value) override { m_Value = value == false ? 0. : 1.; }
		virtual void SetValue(int8_t value) override { m_Value = (double)value; }
		virtual void SetValue(uint8_t value) override { m_Value = (double)value; }
		virtual void SetValue(int16_t value) override { m_Value = (double)value; }
		virtual void SetValue(uint16_t value) override { m_Value = (double)value; }
		virtual void SetValue(int32_t value) override { m_Value = (double)value; }
		virtual void SetValue(uint32_t value) override { m_Value = (double)value; }
		virtual void SetValue(int64_t value) override { m_Value = (double)value; }
		virtual void SetValue(uint64_t value) override { m_Value = (double)value; }
		virtual void SetValue(float value) override { m_Value = (double)value; }
		virtual void SetValue(double value) override { m_Value = (double)value; }
		virtual void SetValue(const char* value) override;
		virtual void SetValue(const String& value) override;
		virtual void SetValue(FixedString value) override;

		virtual void* GetDataPtr() const override { return (void*)&m_Value; }
		virtual bool GetValueBool() const override { return m_Value != 0; }
		virtual int8_t GetValueInt8() const override { return (int8_t)m_Value; }
		virtual uint8_t GetValueUInt8() const override { return (uint8_t)m_Value; }
		virtual int16_t GetValueInt16() const override { return (int16_t)m_Value; }
		virtual uint16_t GetValueUInt16() const override { return (uint16_t)m_Value; }
		virtual int32_t GetValueInt32() const override { return (int32_t)m_Value; }
		virtual uint32_t GetValueUInt32() const override { return (uint32_t)m_Value; }
		virtual int64_t GetValueInt64() const override { return (int64_t)m_Value; }
		virtual uint64_t GetValueUInt64() const override { return (uint64_t)m_Value; }
		virtual float GetValueFloat() const override { return (float)m_Value; }
		virtual double GetValueDouble() const override { return (double)m_Value; }
		virtual FixedString GetValueFixedString() const override;
		virtual String GetValueString() const override;

		virtual Result ToString(ToStringContext& context) const override;

		virtual Variable* Clone(Array<uint8_t>& buffer) const override;
		virtual Variable* Clone(IHeap& heap) const override;

		virtual bool operator == (const Variable& op) const override;
	};



	//////////////////////////////////////////////////////////////////////////////////////////////////
	//
	//	Variable 32 bit base 16 integer
	//

	class VariableHex32 : public VariableUInt
	{
	public:
		typedef VariableUInt super;

		static constexpr FixedString TYPE_NAME = "hex32";

	public:
		VariableHex32()
		{
		}

		VariableHex32(uint32_t value)
			: VariableUInt(value)
		{
		}

		virtual FixedString GetTypeName() const override { return TYPE_NAME; }

		virtual void SetValue(const char* value) override;
		virtual void SetValue(const String& value) override;


		virtual Result ToString(ToStringContext& context) const override;

		virtual Variable* Clone(Array<uint8_t>& buffer) const override;
		virtual Variable* Clone(IHeap& heap) const override;
	};


	//////////////////////////////////////////////////////////////////////////////////////////////////
	//
	//	Variable 64 bit base 16 integer
	//

	class VariableHex64 : public VariableUInt64
	{
	public:

		typedef VariableUInt64 super;

		static constexpr FixedString TYPE_NAME = "hex64";

	public:
		VariableHex64()
		{
		}
		VariableHex64(uint64_t value)
			: VariableUInt64(value)
		{
		}

		virtual FixedString GetTypeName() const override { return TYPE_NAME; }

		virtual void SetValue(const char* value) override;
		virtual void SetValue(const String& value) override;


		virtual Result ToString(ToStringContext& context) const override;

		virtual Variable* Clone(Array<uint8_t>& buffer) const override;
		virtual Variable* Clone(IHeap& heap) const override;
	};


	//////////////////////////////////////////////////////////////////////////////////////////////////
	//
	//	Variable char*
	//	  - This class only holds pointer, doesn't copy or allocate memory internally
	//

	class VariableCharString : public Variable
	{
	public:

		static constexpr FixedString TYPE_NAME = "const char*";

	private:
		const char* m_Value = nullptr;

	public:
		VariableCharString()
		{
		}

		VariableCharString(const char* value)
			: m_Value(value)
		{
		}

		virtual FixedString GetTypeName() const override { return TYPE_NAME; }

		virtual void SetValue(const char* value) override { m_Value = value; }
		// This method will reference original string buffer. be careful when you call this one
		virtual void SetValue(const String& value) override { m_Value = value; } 
		//virtual void SetValue(FixedString value) override;

		virtual void* GetDataPtr() const override { return (void*)m_Value; }
		virtual bool GetValueBool() const override { return m_Value != nullptr; }

		virtual int32_t GetValueInt32() const override { return (int32_t)FixedString32(m_Value); }
		virtual uint32_t GetValueUInt32() const override { return (uint32_t)FixedString32(m_Value); }
		virtual int64_t GetValueInt64() const override { return (int64_t)FixedString(m_Value); }
		virtual uint64_t GetValueUInt64() const override { return (uint64_t)FixedString(m_Value); }

		virtual FixedString GetValueFixedString() const override { return FixedString(m_Value); }
		virtual String GetValueString() const override { return String(m_Value); }

		virtual Result ToString(ToStringContext& context) const override;

		virtual Variable* Clone(Array<uint8_t>& buffer) const override;
		virtual Variable* Clone(IHeap& heap) const override;

		virtual bool operator == (const Variable& op) const override;
	};



	//////////////////////////////////////////////////////////////////////////////////////////////////
	//
	//	Variable wchar_t*
	//	  - This class only holds pointer, doesn't copy or allocate memory internally
	//

	class VariableWCharString : public Variable
	{
	public:

		static constexpr FixedString TYPE_NAME = "const wchar_t*";

	private:
		const wchar_t* m_Value = nullptr;

	public:
		VariableWCharString()
		{
		}

		VariableWCharString(const wchar_t* value)
			: m_Value(value)
		{
		}

		virtual FixedString GetTypeName() const override { return TYPE_NAME; }

		virtual void SetValue(const wchar_t* value) override { m_Value = value; }

		virtual void* GetDataPtr() const override { return (void*)m_Value; }
		virtual bool GetValueBool() const override { return m_Value != nullptr; }
		//virtual FixedString GetValueFixedString() const override { return FixedString(m_Value); }
		//virtual String GetValueString() const override { return String(m_Value); }

		virtual Result ToString(ToStringContext& context) const override;

		virtual Variable* Clone(Array<uint8_t>& buffer) const override;
		virtual Variable* Clone(IHeap& heap) const override;

		virtual bool operator == (const Variable& op) const override;
	};




	//////////////////////////////////////////////////////////////////////////////////////////////////
	//
	//	Variable String
	//

	class VariableString : public Variable
	{
	public:

		static constexpr FixedString TYPE_NAME = "string";

	private:
		String m_Value;

	public:
		VariableString()
			: m_Value(0)
		{
		}
		VariableString(const String& value)
			: m_Value(value)
		{
		}

		virtual FixedString GetTypeName() const override { return TYPE_NAME; }

		virtual void SetValue(bool value) override;
		virtual void SetValue(int8_t value) override;
		virtual void SetValue(uint8_t value) override;
		virtual void SetValue(int16_t value) override;
		virtual void SetValue(uint16_t value) override;
		virtual void SetValue(int32_t value) override;
		virtual void SetValue(uint32_t value) override;
		virtual void SetValue(int64_t value) override;
		virtual void SetValue(uint64_t value) override;
		virtual void SetValue(float value) override;
		virtual void SetValue(double value) override;
		virtual void SetValue(const char* value) override;
		virtual void SetValue(const String& value) override;
		virtual void SetValue(FixedString value) override;

		virtual void* GetDataPtr() const override { return (void*)&m_Value; }
		virtual bool GetValueBool() const override;
		virtual int8_t GetValueInt8() const override;
		virtual uint8_t GetValueUInt8() const override;
		virtual int16_t GetValueInt16() const override;
		virtual uint16_t GetValueUInt16() const override;
		virtual int32_t GetValueInt32() const override;
		virtual uint32_t GetValueUInt32() const override;
		virtual int64_t GetValueInt64() const override;
		virtual uint64_t GetValueUInt64() const override;
		virtual float GetValueFloat() const override;
		virtual double GetValueDouble() const override;
		virtual FixedString GetValueFixedString() const override;
		virtual String GetValueString() const override;

		virtual Result ToString(ToStringContext& context) const override;

		virtual Variable* Clone(Array<uint8_t>& buffer) const override;
		virtual Variable* Clone(IHeap& heap) const override;

		virtual bool operator == (const Variable& op) const override;
	};




	//////////////////////////////////////////////////////////////////////////////////////////////////
	//
	//	Variable FixedString32
	//

	class VariableFixedString32 : public Variable
	{
	public:

		static constexpr FixedString TYPE_NAME = "FixedString";

	private:
		FixedString32 m_Value;

	public:
		VariableFixedString32()
		{
		}

		VariableFixedString32(FixedString32 value)
			: m_Value(value)
		{
		}

		virtual FixedString GetTypeName() const override { return TYPE_NAME; }

		virtual void SetValue(int32_t value) override { m_Value = value; }
		virtual void SetValue(uint32_t value) override { m_Value = value; }
		virtual void SetValue(int64_t value) override { m_Value = (uint32_t)value; }
		virtual void SetValue(uint64_t value) override { m_Value = (uint32_t)value; }
		virtual void SetValue(const char* value) override { m_Value = value; }
		virtual void SetValue(const String& value) override { m_Value = (const char*)value; }
		virtual void SetValue(FixedString32 value) override { m_Value = value; }

		virtual void* GetDataPtr() const override { return (void*)&m_Value; }
		virtual bool GetValueBool() const override { return m_Value != nullptr; }
		virtual int8_t GetValueInt8() const override { return (int8_t)m_Value; }
		virtual uint8_t GetValueUInt8() const override { return (uint8_t)m_Value; }
		virtual int16_t GetValueInt16() const override { return (int16_t)m_Value; }
		virtual uint16_t GetValueUInt16() const override { return (uint16_t)m_Value; }
		virtual int32_t GetValueInt32() const override { return (int32_t)m_Value; }
		virtual uint32_t GetValueUInt32() const override { return (uint32_t)m_Value; }
		virtual int64_t GetValueInt64() const override { return (int64_t)m_Value; }
		virtual uint64_t GetValueUInt64() const override { return (uint64_t)m_Value; }
		virtual float GetValueFloat() const override { return (float)m_Value; }
		virtual double GetValueDouble() const override { return (double)m_Value; }
		virtual FixedString32 GetValueFixedString32() const override { return m_Value; }
		virtual String GetValueString() const override;

		virtual Result ToString(ToStringContext& context) const override;

		virtual Variable* Clone(Array<uint8_t>& buffer) const override;
		virtual Variable* Clone(IHeap& heap) const override;
	};




	//////////////////////////////////////////////////////////////////////////////////////////////////
	//
	//	Variable FixedString
	//

	class VariableFixedString : public Variable
	{
	public:

		static constexpr FixedString TYPE_NAME = "FixedString";

	private:
		FixedString m_Value;

	public:
		VariableFixedString()
		{
		}
		VariableFixedString(FixedString value)
			: m_Value(value)
		{
		}

		virtual FixedString GetTypeName() const override { return TYPE_NAME; }

		virtual void SetValue(int64_t value) override { m_Value = value; }
		virtual void SetValue(uint64_t value) override { m_Value = value; }
		virtual void SetValue(const char* value) override { m_Value = value; }
		virtual void SetValue(const String& value) override { m_Value = (const char*)value; }
		virtual void SetValue(FixedString value) override { m_Value = value; }

		virtual void* GetDataPtr() const override { return (void*)&m_Value; }
		virtual bool GetValueBool() const override { return m_Value != nullptr; }
		virtual int8_t GetValueInt8() const override { return (int8_t)m_Value; }
		virtual uint8_t GetValueUInt8() const override { return (uint8_t)m_Value; }
		virtual int16_t GetValueInt16() const override { return (int16_t)m_Value; }
		virtual uint16_t GetValueUInt16() const override { return (uint16_t)m_Value; }
		virtual int32_t GetValueInt32() const override { return (int32_t)m_Value; }
		virtual uint32_t GetValueUInt32() const override { return (uint32_t)m_Value; }
		virtual int64_t GetValueInt64() const override { return (int64_t)m_Value; }
		virtual uint64_t GetValueUInt64() const override { return (uint64_t)m_Value; }
		virtual float GetValueFloat() const override { return (float)m_Value; }
		virtual double GetValueDouble() const override { return (double)m_Value; }
		virtual FixedString GetValueFixedString() const override { return m_Value; }
		virtual String GetValueString() const override;

		virtual Result ToString(ToStringContext& context) const override;

		virtual Variable* Clone(Array<uint8_t>& buffer) const override;
		virtual Variable* Clone(IHeap& heap) const override;
	};




	//////////////////////////////////////////////////////////////////////////////////////////////////
	//
	//	Variable generic boxing
	//

	template<class ValueType>
	class VariableByBinaryValue : public Variable
	{
	public:


	private:
		ValueType m_Value;

	public:
		VariableByBinaryValue()
		{
		}

		VariableByBinaryValue(const ValueType& value)
			: m_Value(value)
		{
		}

		virtual FixedString GetTypeName() const override { return "BinaryValue"; }

		virtual void* GetDataPtr() const override { return (void*)&m_Value; }


		// Need to be overridden case by case
		virtual Result ToString(ToStringContext& context) const override
		{
			return _ToString(context, m_Value);
		}

		virtual Variable* Clone(Array<uint8_t>& buffer) const override
		{
			return new((void*)buffer.data()) VariableByBinaryValue<ValueType>(m_Value);
		}

		virtual Variable* Clone(IHeap& heap) const override
		{
			return new(heap) VariableByBinaryValue<ValueType>(m_Value);
		}

		virtual bool operator == (const Variable& op) const override
		{
			if (op.GetDataPtr() == nullptr)
				return false;

			if (GetTypeName() == op.GetTypeName())
				return m_Value == *reinterpret_cast<ValueType*>(op.GetDataPtr());

			return memcmp(&m_Value, op.GetDataPtr(), sizeof(ValueType));
		}

	};



	//////////////////////////////////////////////////////////////////////////////////////////////////
	//
	//	Variable void*
	//

	template<class ValueType>
	class VariableValueReference : public Variable
	{
	public:


	private:
		ValueType* m_Value = nullptr;

	public:

		VariableValueReference()
		{
		}

		VariableValueReference(const ValueType& value)
			: m_Value(const_cast<ValueType*>(&value))
		{
		}

		virtual FixedString GetTypeName() const override { return "ref*"; }

		virtual void* GetDataPtr() const override { return m_Value; }

		virtual bool GetValueBool() const override { return m_Value != nullptr; }

		// Need to be overridden case by case
		virtual Result ToString(ToStringContext& context) const override
		{
			if (m_Value == nullptr)
			{
				StrUtil::StringCopyEx(context.StringBuffer, context.StringBufferLength, "(Null)");
				return ResultCode::SUCCESS_FALSE;
			}

			return _ToString(context, *m_Value);
		}

		virtual Variable* Clone(Array<uint8_t>& buffer) const override
		{
			return new((void*)buffer.data()) VariableValueReference<ValueType>(*m_Value);
		}

		virtual Variable* Clone(IHeap& heap) const override
		{
			return new(heap) VariableValueReference<ValueType>(*m_Value);
		}

		virtual bool operator == (const Variable& op) const override
		{
			if (GetDataPtr() == nullptr)
			{
				return GetDataPtr() == op.GetDataPtr();
			}

			// Note: To enable == operator all types need to support compare operator
			//if (GetTypeName() == op.GetTypeName())
			//	return *reinterpret_cast<ValueType*>(GetDataPtr()) == *reinterpret_cast<ValueType*>(op.GetDataPtr());

			return memcmp(GetDataPtr(), op.GetDataPtr(), sizeof(ValueType));
		}
	};


} // namespace SF




