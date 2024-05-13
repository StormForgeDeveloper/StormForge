////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2020 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Common Variables 
//
////////////////////////////////////////////////////////////////////////////////


#pragma once


#include "SFTypedefs.h"
#include "SFAssert.h"
#include "Variable/SFVariable.h"


namespace SF {


	struct ToStringContext;
	class IOutputStream;
	class IInputStream;


	//template<> inline bool Variable::GetValue<bool>() { return GetValueBool(); }
	//template<> inline int8_t Variable::GetValue<int8_t>() { return GetValueInt8(); }
	//template<> inline uint8_t Variable::GetValue<uint8_t>() { return GetValueUInt8(); }
	//template<> inline int16_t Variable::GetValue<int16_t>() { return GetValueInt16(); }
	//template<> inline uint16_t Variable::GetValue<uint16_t>() { return GetValueUInt16(); }
	//template<> inline int32_t Variable::GetValue<int32_t>() { return GetValueInt32(); }
	//template<> inline uint32_t Variable::GetValue<uint32_t>() { return GetValueUInt32(); }
	//template<> inline int64_t Variable::GetValue<int64_t>() { return GetValueInt64(); }
	//template<> inline uint64_t Variable::GetValue<uint64_t>() { return GetValueUInt64(); }
	//template<> inline float Variable::GetValue<float>() { return GetValueFloat(); }
	//template<> inline double Variable::GetValue<double>() { return GetValueDouble(); }
	//template<> inline String Variable::GetValue<String>() { return GetValueString(); }
	//template<> inline const char* Variable::GetValue<const char*>() { return GetValueCharString(); }
	//template<> inline const wchar_t* Variable::GetValue<const wchar_t*>() { return GetValueWCharString(); }
	//template<> inline StringCrc32 Variable::GetValue<StringCrc32>() { return GetValueStringCrc32(); }
	//template<> inline StringCrc64 Variable::GetValue<StringCrc64>() { return GetValueStringCrc64(); }





	//////////////////////////////////////////////////////////////////////////////////////////////////
	//
	//	Variable bool
	//

	class VariableBool : public Variable
	{
	public:

		static constexpr StringCrc32 TYPE_NAME = "bool"_crc32c;

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

		virtual StringCrc32 GetTypeName() const override { return TYPE_NAME; }

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
		virtual void SetValue(const char* value) override { m_Value = (value == nullptr || String_False.EqualsIgnoreCase(value)) ? false : true; }
		virtual void SetValue(const String& value) override { m_Value = (value == nullptr || String_False.EqualsIgnoreCase(value)) ? false : true; }
		virtual void SetValue(StringCrc32 value) override { m_Value = (value == nullptr || value == "false" || value == "False") ? false : true; }
		virtual void SetValue(StringCrc64 value) override { m_Value = (value == nullptr || value == "false" || value == "False") ? false : true; }

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
		virtual String GetValueString() const override { return m_Value ? String_True : String_False; }
		virtual StringCrc32 GetValueStringCrc32() const override { return m_Value ? "true" : "false"; }
		virtual StringCrc64 GetValueStringCrc64() const override { return m_Value ? "true" : "false"; }

		virtual Result ToString(ToStringContext& context) const override;

		virtual Variable* Clone(Array<uint8_t>& buffer) const override;
		virtual Variable* Clone(IHeap& heap) const override;

		virtual size_t GetSerializedSize() const override { return sizeof(m_Value); }
		virtual Result Serialize(IOutputStream& output) const override
		{
			return output << m_Value;
		}
		virtual Result Deserialize(IInputStream& input) override
		{
			return input >> m_Value;
		}

		virtual bool operator == (const Variable& op) const override;
	};


	//////////////////////////////////////////////////////////////////////////////////////////////////
	//
	//	Variable void*
	//

	class VariableVoidP : public Variable
	{
	public:

		static constexpr StringCrc32 TYPE_NAME = "void*"_crc32c;

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

		virtual StringCrc32 GetTypeName() const override { return TYPE_NAME; }

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

		static constexpr StringCrc32 TYPE_NAME = "int"_crc32c;

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

		virtual StringCrc32 GetTypeName() const override { return TYPE_NAME; }

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
		virtual void SetValue(StringCrc64 value) override;

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
        virtual StringCrc32 GetValueStringCrc32() const override;
        virtual StringCrc64 GetValueStringCrc64() const override;
		virtual String GetValueString() const override;

		virtual Result ToString(ToStringContext& context) const override;

		virtual Variable* Clone(Array<uint8_t>& buffer) const override;
		virtual Variable* Clone(IHeap& heap) const override;

		virtual size_t GetSerializedSize() const  override { return sizeof(m_Value); }
		virtual Result Serialize(IOutputStream& output) const override;
		virtual Result Deserialize(IInputStream& input) override;
	};


	//////////////////////////////////////////////////////////////////////////////////////////////////
	//
	//	Variable uint
	//

	class VariableUInt : public Variable
	{
	public:

		static constexpr StringCrc32 TYPE_NAME = "uint"_crc32c;

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

		virtual StringCrc32 GetTypeName() const override { return TYPE_NAME; }

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
		virtual void SetValue(StringCrc64 value) override;

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
        virtual StringCrc32 GetValueStringCrc32() const override;
		virtual StringCrc64 GetValueStringCrc64() const override;
		virtual String GetValueString() const override;

		virtual Result ToString(ToStringContext& context) const override;

		virtual Variable* Clone(Array<uint8_t>& buffer) const override;
		virtual Variable* Clone(IHeap& heap) const override;

		virtual size_t GetSerializedSize() const  override { return sizeof(m_Value); }
		virtual Result Serialize(IOutputStream& output) const override;
		virtual Result Deserialize(IInputStream& input) override;
	};



	//////////////////////////////////////////////////////////////////////////////////////////////////
	//
	//	Variable Result
	//

	class VariableResult : public Variable
	{
	public:

		static constexpr StringCrc32 TYPE_NAME = "Result"_crc32c;

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

		virtual StringCrc32 GetTypeName() const override { return TYPE_NAME; }

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
		virtual bool GetValueBool() const override { return m_Value.IsSuccess(); }
		virtual int8_t GetValueInt8() const override { return (int8_t)m_Value.GetHResultCode(); }
		virtual uint8_t GetValueUInt8() const override { return (uint8_t)m_Value.GetHResultCode(); }
		virtual int16_t GetValueInt16() const override { return (int16_t)m_Value.GetHResultCode(); }
		virtual uint16_t GetValueUInt16() const override { return (uint16_t)m_Value.GetHResultCode(); }
		virtual int32_t GetValueInt32() const override { return (int32_t)m_Value.GetHResultCode(); }
		virtual uint32_t GetValueUInt32() const override { return (uint32_t)m_Value.GetHResultCode(); }
		virtual int64_t GetValueInt64() const override { return (int64_t)m_Value.GetHResultCode(); }
		virtual uint64_t GetValueUInt64() const override { return (uint64_t)m_Value.GetHResultCode(); }
		virtual float GetValueFloat() const override { return (float)m_Value.IsSuccess(); }
		virtual double GetValueDouble() const override { return (double)m_Value.IsSuccess(); }
		virtual StringCrc64 GetValueStringCrc64() const override { return m_Value.ToString(); }
		virtual String GetValueString() const override { return m_Value.ToString(); }

		virtual Result ToString(ToStringContext& context) const override;

		virtual Variable* Clone(Array<uint8_t>& buffer) const override;
		virtual Variable* Clone(IHeap& heap) const override;

		virtual size_t GetSerializedSize() const  override { return sizeof(m_Value); }
		virtual Result Serialize(IOutputStream& output) const override;
		virtual Result Deserialize(IInputStream& input) override;
	};



	//////////////////////////////////////////////////////////////////////////////////////////////////
	//
	//	Variable int64
	//

	class VariableInt64 : public Variable
	{
	public:

		static constexpr StringCrc32 TYPE_NAME = "int64"_crc32c;

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

		virtual StringCrc32 GetTypeName() const override { return TYPE_NAME; }

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
		virtual void SetValue(StringCrc64 value) override;

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
        virtual StringCrc32 GetValueStringCrc32() const override;
        virtual StringCrc64 GetValueStringCrc64() const override;
		virtual String GetValueString() const override;

		virtual Result ToString(ToStringContext& context) const override;

		virtual Variable* Clone(Array<uint8_t>& buffer) const override;
		virtual Variable* Clone(IHeap& heap) const override;

		virtual size_t GetSerializedSize() const  override { return sizeof(m_Value); }
		virtual Result Serialize(IOutputStream& output) const override;
		virtual Result Deserialize(IInputStream& input) override;
	};


	//////////////////////////////////////////////////////////////////////////////////////////////////
	//
	//	Variable uint64
	//

	class VariableUInt64 : public Variable
	{
	public:

		static constexpr StringCrc32 TYPE_NAME = "uint64"_crc32c;

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

		virtual StringCrc32 GetTypeName() const override { return TYPE_NAME; }

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
		virtual void SetValue(StringCrc64 value) override;

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
        virtual StringCrc32 GetValueStringCrc32() const override;
        virtual StringCrc64 GetValueStringCrc64() const override;
		virtual String GetValueString() const override;

		virtual Result ToString(ToStringContext& context) const override;

		virtual Variable* Clone(Array<uint8_t>& buffer) const override;
		virtual Variable* Clone(IHeap& heap) const override;

		virtual size_t GetSerializedSize() const  override { return sizeof(m_Value); }
		virtual Result Serialize(IOutputStream& output) const override;
		virtual Result Deserialize(IInputStream& input) override;
	};


	//////////////////////////////////////////////////////////////////////////////////////////////////
	//
	//	Variable float
	//

	class VariableFloat : public Variable
	{
	public:

		static constexpr StringCrc32 TYPE_NAME = "float"_crc32c;

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

		virtual StringCrc32 GetTypeName() const override { return TYPE_NAME; }

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
		virtual void SetValue(StringCrc64 value) override;

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
		virtual StringCrc64 GetValueStringCrc64() const override;
		virtual String GetValueString() const override;

		virtual Result ToString(ToStringContext& context) const override;

		virtual Variable* Clone(Array<uint8_t>& buffer) const override;
		virtual Variable* Clone(IHeap& heap) const override;

		virtual size_t GetSerializedSize() const  override { return sizeof(m_Value); }
		virtual Result Serialize(IOutputStream& output) const override;
		virtual Result Deserialize(IInputStream& input) override;

		virtual bool operator == (const Variable& op) const override;
	};


	//////////////////////////////////////////////////////////////////////////////////////////////////
	//
	//	Variable double
	//

	class VariableDouble : public Variable
	{
	public:

		static constexpr StringCrc32 TYPE_NAME = "double"_crc32c;

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

		virtual StringCrc32 GetTypeName() const override { return TYPE_NAME; }

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
		virtual void SetValue(StringCrc64 value) override;

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
		virtual StringCrc64 GetValueStringCrc64() const override;
		virtual String GetValueString() const override;

		virtual Result ToString(ToStringContext& context) const override;

		virtual Variable* Clone(Array<uint8_t>& buffer) const override;
		virtual Variable* Clone(IHeap& heap) const override;

		virtual size_t GetSerializedSize() const  override { return sizeof(m_Value); }
		virtual Result Serialize(IOutputStream& output) const override;
		virtual Result Deserialize(IInputStream& input) override;

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

		static constexpr StringCrc32 TYPE_NAME = "hex32"_crc32c;

	public:
		VariableHex32()
		{
		}

		VariableHex32(uint32_t value)
			: VariableUInt(value)
		{
		}

		virtual StringCrc32 GetTypeName() const override { return TYPE_NAME; }

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

		static constexpr StringCrc32 TYPE_NAME = "hex64"_crc32c;

	public:
		VariableHex64()
		{
		}
		VariableHex64(uint64_t value)
			: VariableUInt64(value)
		{
		}

		virtual StringCrc32 GetTypeName() const override { return TYPE_NAME; }

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

		static constexpr StringCrc32 TYPE_NAME = "const char*"_crc32c;

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

		virtual StringCrc32 GetTypeName() const override { return TYPE_NAME; }

		virtual void SetValue(const char* value) override { m_Value = value; }
		// This method will reference original string buffer. be careful when you call this one
		virtual void SetValue(const String& value) override { m_Value = value.data(); } 
		//virtual void SetValue(StringCrc64 value) override;

		virtual void* GetDataPtr() const override { return (void*)m_Value; }
		virtual bool GetValueBool() const override { return m_Value != nullptr; }

		virtual int32_t GetValueInt32() const override { return (int32_t)StringCrc32(m_Value); }
		virtual uint32_t GetValueUInt32() const override { return (uint32_t)StringCrc32(m_Value); }
		virtual int64_t GetValueInt64() const override { return (int64_t)StringCrc64(m_Value); }
		virtual uint64_t GetValueUInt64() const override { return (uint64_t)StringCrc64(m_Value); }

		virtual StringCrc64 GetValueStringCrc64() const override { return StringCrc64(m_Value); }
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

		static constexpr StringCrc32 TYPE_NAME = "const wchar_t*"_crc32c;

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

		virtual StringCrc32 GetTypeName() const override { return TYPE_NAME; }

		virtual void SetValue(const wchar_t* value) override { m_Value = value; }

		virtual void* GetDataPtr() const override { return (void*)m_Value; }
		virtual bool GetValueBool() const override { return m_Value != nullptr; }
		//virtual StringCrc64 GetValueStringCrc64() const override { return StringCrc64(m_Value); }
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

		static constexpr StringCrc32 TYPE_NAME = "string"_crc32c;

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

		virtual StringCrc32 GetTypeName() const override { return TYPE_NAME; }

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
		virtual void SetValue(StringCrc64 value) override;

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
		virtual const char* GetValueCharString() const override;
		virtual StringCrc32 GetValueStringCrc32() const override;
		virtual StringCrc64 GetValueStringCrc64() const override;
		virtual String GetValueString() const override;

		virtual Result ToString(ToStringContext& context) const override;

		virtual Variable* Clone(Array<uint8_t>& buffer) const override;
		virtual Variable* Clone(IHeap& heap) const override;

		virtual size_t GetSerializedSize() const  override { return sizeof(uint16_t) + (m_Value.GetLength() + 1) * sizeof(char); }
		virtual Result Serialize(IOutputStream& output) const override;
		virtual Result Deserialize(IInputStream& input) override;

		virtual bool operator == (const Variable& op) const override;
	};



	class VariableWString : public Variable
	{
	public:

		static constexpr StringCrc32 TYPE_NAME = "wstring"_crc32c;

	private:
		WString m_Value;

	public:
		VariableWString()
			: m_Value(0)
		{
		}
		VariableWString(const WString& value)
			: m_Value(value)
		{
		}

		virtual StringCrc32 GetTypeName() const override { return TYPE_NAME; }

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
		virtual void SetValue(StringCrc64 value) override;

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
		virtual const wchar_t* GetValueWCharString() const override;
		virtual StringCrc32 GetValueStringCrc32() const override;
		virtual StringCrc64 GetValueStringCrc64() const override;
		virtual String GetValueString() const override;


		virtual Result ToString(ToStringContext& context) const override;

		virtual Variable* Clone(Array<uint8_t>& buffer) const override;
		virtual Variable* Clone(IHeap& heap) const override;

		virtual size_t GetSerializedSize() const  override { return sizeof(uint16_t) + (m_Value.GetLength() + 1) * sizeof(wchar_t); }
		virtual Result Serialize(IOutputStream& output) const override;
		virtual Result Deserialize(IInputStream& input) override;

		virtual bool operator == (const Variable& op) const override;
	};



	//////////////////////////////////////////////////////////////////////////////////////////////////
	//
	//	Variable StringCrc32
	//

	class VariableStringCrc32 : public Variable
	{
	public:

		static constexpr StringCrc32 TYPE_NAME = "StringCrc32"_crc32c;

	private:
		StringCrc32 m_Value;

	public:
		VariableStringCrc32()
		{
		}

		VariableStringCrc32(StringCrc32 value)
			: m_Value(value)
		{
		}

		virtual StringCrc32 GetTypeName() const override { return TYPE_NAME; }

		virtual void SetValue(int32_t value) override { m_Value = value; }
		virtual void SetValue(uint32_t value) override { m_Value = value; }
		virtual void SetValue(int64_t value) override { m_Value = (uint32_t)value; }
		virtual void SetValue(uint64_t value) override { m_Value = (uint32_t)value; }
		virtual void SetValue(const char* value) override { m_Value = value; }
		virtual void SetValue(const String& value) override { m_Value = (const char*)value; }
		virtual void SetValue(StringCrc32 value) override { m_Value = value; }

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
		virtual StringCrc32 GetValueStringCrc32() const override { return m_Value; }
		virtual String GetValueString() const override;
		virtual const char* GetValueCharString() const override;

		virtual Result ToString(ToStringContext& context) const override;

		virtual Variable* Clone(Array<uint8_t>& buffer) const override;
		virtual Variable* Clone(IHeap& heap) const override;

		virtual size_t GetSerializedSize() const  override { return sizeof(m_Value); }
		virtual Result Serialize(IOutputStream& output) const override;
		virtual Result Deserialize(IInputStream& input) override;
	};




	//////////////////////////////////////////////////////////////////////////////////////////////////
	//
	//	Variable StringCrc64
	//

	class VariableStringCrc64 : public Variable
	{
	public:

		static constexpr StringCrc32 TYPE_NAME = "StringCrc64"_crc32c;

	private:
		StringCrc64 m_Value;

	public:
		VariableStringCrc64()
		{
		}
		VariableStringCrc64(StringCrc64 value)
			: m_Value(value)
		{
		}

		virtual StringCrc32 GetTypeName() const override { return TYPE_NAME; }

		virtual void SetValue(int64_t value) override { m_Value = value; }
		virtual void SetValue(uint64_t value) override { m_Value = value; }
		virtual void SetValue(const char* value) override { m_Value = value; }
		virtual void SetValue(const String& value) override { m_Value = (const char*)value; }
		virtual void SetValue(StringCrc64 value) override { m_Value = value; }

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
		virtual StringCrc64 GetValueStringCrc64() const override { return m_Value; }
		virtual String GetValueString() const override;
		virtual const char* GetValueCharString() const override;

		virtual Result ToString(ToStringContext& context) const override;

		virtual Variable* Clone(Array<uint8_t>& buffer) const override;
		virtual Variable* Clone(IHeap& heap) const override;


		virtual size_t GetSerializedSize() const  override { return sizeof(m_Value); }
		virtual Result Serialize(IOutputStream& output) const override;
		virtual Result Deserialize(IInputStream& input) override;
	};




	//////////////////////////////////////////////////////////////////////////////////////////////////
	//
	//	Variable BLOB
	//

	class VariableBLOB : public Variable
	{
	public:

		static constexpr StringCrc32 TYPE_NAME = "BLOB"_crc32c;

	private:
		DynamicArray<uint8_t> m_Value;

	public:

		VariableBLOB(const VariableBLOB& src)
			: m_Value(src.m_Value.GetHeap())
		{
			m_Value.CopyFrom(src.m_Value);
		}

		VariableBLOB()
			: m_Value(GetSystemHeap())
		{
		}

		VariableBLOB(IHeap& heap)
			: m_Value(heap)
		{
		}

		VariableBLOB(const Array<const uint8_t>& value)
			: m_Value(value.GetHeap())
		{
			m_Value.CopyFrom(value);
		}

		VariableBLOB(const Array<uint8_t>& value)
			: m_Value(value.GetHeap())
		{
			m_Value.CopyFrom(value);
		}

		VariableBLOB(IHeap& heap, const Array<uint8_t>& value)
			: m_Value(heap)
		{
			m_Value.CopyFrom(value);
		}

		VariableBLOB(IHeap& heap, const Array<const uint8_t>& value)
			: m_Value(heap)
		{
			m_Value.CopyFrom(value);
		}


		virtual StringCrc32 GetTypeName() const override { return TYPE_NAME; }


		virtual void SetValue(const Array<const uint8_t>& value) override
		{
			m_Value.CopyFrom(value);
		}

		virtual void* GetDataPtr() const override { return const_cast<uint8_t*>(m_Value.data()); }
		virtual bool GetValueBool() const override { return m_Value.size() != 0; }
		virtual const Array<uint8_t>& GetValueBLOB() const override { return m_Value; }

		virtual Result ToString(ToStringContext& context) const override;

		virtual Variable* Clone(Array<uint8_t>& buffer) const override;
		virtual Variable* Clone(IHeap& heap) const override;


		virtual size_t GetSerializedSize() const  override { return sizeof(uint16_t) + m_Value.size(); }
		virtual Result Serialize(IOutputStream& output) const override;
		virtual Result Deserialize(IInputStream& input) override;

		friend size_t SerializedSizeOf(const VariableBLOB& Value);
		friend Result operator >> (IInputStream& input, VariableBLOB& data);
		friend Result operator << (IOutputStream& output, const VariableBLOB& data);
	};


	Result _ToString(ToStringContext& context, const VariableBLOB& Data);

	inline size_t SerializedSizeOf(const VariableBLOB& Value)
	{
		return Value.GetSerializedSize();
	}


	inline Result operator >> (IInputStream& input, VariableBLOB& data)
	{
		return input >> data.m_Value;
	}

	inline Result operator << (IOutputStream& output, const VariableBLOB& data)
	{
		return output << data.m_Value;
	}


} // namespace SF

