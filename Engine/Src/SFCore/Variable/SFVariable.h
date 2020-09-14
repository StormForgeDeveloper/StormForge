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
#include "String/SFStringCrc64.h"
#include "String/SFStringCrc32.h"
#include "String/SFString.h"
#include "String/SFStringSerialization.h"
#include "Stream/SFStream.h"

namespace SF {


	struct ToStringContext;
	class IOutputStream;
	class IInputStream;


	/////////////////////////////////////////////////////////////////////////////////
	//
	//	variable base class for boxing/unboxing
	//

	class Variable
	{
	public:

		using TypeNameType = StringCrc32;

	public:

		Variable()
		{
		}

		virtual ~Variable()
		{
		}

		virtual TypeNameType GetTypeName() const = 0;


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
		virtual void SetValue(StringCrc32 value) { unused(value); }
		virtual void SetValue(StringCrc64 value) { unused(value); }
		virtual void SetValue(const Array<uint8_t>& value) { unused(value); }
		virtual void SetValue(Array<uint8_t>&& value) { unused(value); }


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
		virtual StringCrc32 GetValueStringCrc32() const { return StringCrc32(); }
		virtual StringCrc64 GetValueStringCrc64() const { return StringCrc64(); }
		virtual const Array<uint8_t>& GetValueBLOB() const { static StaticArray<uint8_t,1> temp; return temp; }

		// Template implementation for type based GetValue access
		template<class ValueType>
		ValueType GetValue();

		// Variable instance size
		virtual size_t GetVariableSize() const { return sizeof(Variable); }

		// Serialization
		virtual size_t GetSerializedSize() const { return sizeof(StringCrc32); }
		virtual Result Serialize(IOutputStream& output) const { return output.Write(GetTypeName()); }
		virtual Result Deserialize(IInputStream& input)	{ return ResultCode::FAIL; }

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
	template<> inline StringCrc32 Variable::GetValue<StringCrc32>() { return GetValueStringCrc32(); }
	template<> inline StringCrc64 Variable::GetValue<StringCrc64>() { return GetValueStringCrc64(); }
	//template<> inline Array<uint8_t> Variable::GetValue<Array<uint8_t>>() { return GetValueBLOB(); }





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
		virtual void SetValue(const char* value) override { m_Value = (value == nullptr || String::False.IsEqualIgnoreCase(value)) ? false : true; }
		virtual void SetValue(const String& value) override { m_Value = (value == nullptr || String::False.IsEqualIgnoreCase(value)) ? false : true; }
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
		virtual String GetValueString() const override { return m_Value ? String::True : String::False; }
		virtual StringCrc32 GetValueStringCrc32() const override { return m_Value ? "true" : "false"; }
		virtual StringCrc64 GetValueStringCrc64() const override { return m_Value ? "true" : "false"; }

		virtual Result ToString(ToStringContext& context) const override;

		virtual Variable* Clone(Array<uint8_t>& buffer) const override;
		virtual Variable* Clone(IHeap& heap) const override;

		virtual size_t GetSerializedSize() const { return Variable::GetSerializedSize() + sizeof(m_Value); }
		virtual Result Serialize(IOutputStream& output) const
		{
			return Variable::Serialize(output) && output.Write(m_Value);
		}
		virtual Result Deserialize(IInputStream& input)
		{
			return Variable::Deserialize(input) && input.Read(m_Value);
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
		virtual StringCrc64 GetValueStringCrc64() const override;
		virtual String GetValueString() const override;

		virtual Result ToString(ToStringContext& context) const override;

		virtual Variable* Clone(Array<uint8_t>& buffer) const override;
		virtual Variable* Clone(IHeap& heap) const override;

		virtual size_t GetSerializedSize() const { return Variable::GetSerializedSize() + sizeof(m_Value); }
		virtual Result Serialize(IOutputStream& output) const
		{
			return Variable::Serialize(output) && output.Write(m_Value);
		}
		virtual Result Deserialize(IInputStream& input)
		{
			return Variable::Deserialize(input) && input.Read(m_Value);
		}
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
		virtual StringCrc64 GetValueStringCrc64() const override;
		virtual String GetValueString() const override;

		virtual Result ToString(ToStringContext& context) const override;

		virtual Variable* Clone(Array<uint8_t>& buffer) const override;
		virtual Variable* Clone(IHeap& heap) const override;

		virtual size_t GetSerializedSize() const { return Variable::GetSerializedSize() + sizeof(m_Value); }
		virtual Result Serialize(IOutputStream& output) const
		{
			return Variable::Serialize(output) && output.Write(m_Value);
		}
		virtual Result Deserialize(IInputStream& input)
		{
			return Variable::Deserialize(input) && input.Read(m_Value);
		}
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
		virtual StringCrc64 GetValueStringCrc64() const override { return m_Value ? "SUCCESS" : "FAIL"; }
		virtual String GetValueString() const override { return m_Value ? "SUCCESS" : "FAIL"; }

		virtual Result ToString(ToStringContext& context) const override;

		virtual Variable* Clone(Array<uint8_t>& buffer) const override;
		virtual Variable* Clone(IHeap& heap) const override;

		virtual size_t GetSerializedSize() const { return Variable::GetSerializedSize() + sizeof(m_Value); }
		virtual Result Serialize(IOutputStream& output) const
		{
			return Variable::Serialize(output) && output.Write(m_Value);
		}
		virtual Result Deserialize(IInputStream& input)
		{
			return Variable::Deserialize(input) && input.Read(m_Value);
		}
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
		virtual StringCrc64 GetValueStringCrc64() const override;
		virtual String GetValueString() const override;

		virtual Result ToString(ToStringContext& context) const override;

		virtual Variable* Clone(Array<uint8_t>& buffer) const override;
		virtual Variable* Clone(IHeap& heap) const override;

		virtual size_t GetSerializedSize() const { return Variable::GetSerializedSize() + sizeof(m_Value); }
		virtual Result Serialize(IOutputStream& output) const
		{
			return Variable::Serialize(output) && output.Write(m_Value);
		}
		virtual Result Deserialize(IInputStream& input)
		{
			return Variable::Deserialize(input) && input.Read(m_Value);
		}
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
		virtual StringCrc64 GetValueStringCrc64() const override;
		virtual String GetValueString() const override;

		virtual Result ToString(ToStringContext& context) const override;

		virtual Variable* Clone(Array<uint8_t>& buffer) const override;
		virtual Variable* Clone(IHeap& heap) const override;

		virtual size_t GetSerializedSize() const { return Variable::GetSerializedSize() + sizeof(m_Value); }
		virtual Result Serialize(IOutputStream& output) const
		{
			return Variable::Serialize(output) && output.Write(m_Value);
		}
		virtual Result Deserialize(IInputStream& input)
		{
			return Variable::Deserialize(input) && input.Read(m_Value);
		}
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

		virtual size_t GetSerializedSize() const { return Variable::GetSerializedSize() + sizeof(m_Value); }
		virtual Result Serialize(IOutputStream& output) const
		{
			return Variable::Serialize(output) && output.Write(m_Value);
		}
		virtual Result Deserialize(IInputStream& input)
		{
			return Variable::Deserialize(input) && input.Read(m_Value);
		}

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

		virtual size_t GetSerializedSize() const { return Variable::GetSerializedSize() + sizeof(m_Value); }
		virtual Result Serialize(IOutputStream& output) const
		{
			return Variable::Serialize(output) && output.Write(m_Value);
		}
		virtual Result Deserialize(IInputStream& input)
		{
			return Variable::Deserialize(input) && input.Read(m_Value);
		}

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
		virtual StringCrc64 GetValueStringCrc64() const override;
		virtual String GetValueString() const override;

		virtual Result ToString(ToStringContext& context) const override;

		virtual Variable* Clone(Array<uint8_t>& buffer) const override;
		virtual Variable* Clone(IHeap& heap) const override;

		virtual size_t GetSerializedSize() const { return Variable::GetSerializedSize() + sizeof(uint16_t) + m_Value.size() * sizeof(char); }
		virtual Result Serialize(IOutputStream& output) const
		{
			return Variable::Serialize(output) && output.Write(m_Value);
		}
		virtual Result Deserialize(IInputStream& input)
		{
			return Variable::Deserialize(input) && input.Read(m_Value);
		}

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

		virtual Result ToString(ToStringContext& context) const override;

		virtual Variable* Clone(Array<uint8_t>& buffer) const override;
		virtual Variable* Clone(IHeap& heap) const override;


		virtual size_t GetSerializedSize() const { return Variable::GetSerializedSize() + sizeof(m_Value); }
		virtual Result Serialize(IOutputStream& output) const
		{
			return Variable::Serialize(output) && output.Write(m_Value);
		}
		virtual Result Deserialize(IInputStream& input)
		{
			return Variable::Deserialize(input) && input.Read(m_Value);
		}
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

		virtual Result ToString(ToStringContext& context) const override;

		virtual Variable* Clone(Array<uint8_t>& buffer) const override;
		virtual Variable* Clone(IHeap& heap) const override;


		virtual size_t GetSerializedSize() const { return Variable::GetSerializedSize() + sizeof(m_Value); }
		virtual Result Serialize(IOutputStream& output) const
		{
			return Variable::Serialize(output) && output.Write(m_Value);
		}
		virtual Result Deserialize(IInputStream& input)
		{
			return Variable::Deserialize(input) && input.Read(m_Value);
		}
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
		VariableBLOB()
			: m_Value(GetSystemHeap())
		{
		}

		VariableBLOB(IHeap& heap)
			: m_Value(heap)
		{
		}

		VariableBLOB(const Array<uint8_t>& value)
			: m_Value(value.GetHeap())
		{
			m_Value = value;
		}

		VariableBLOB(IHeap& heap, const Array<uint8_t>& value)
			: m_Value(heap)
		{
			m_Value = value;
		}

		VariableBLOB(IHeap& heap, Array<uint8_t>&& value)
			: m_Value(heap)
		{
			m_Value = value;
		}

		virtual StringCrc32 GetTypeName() const override { return TYPE_NAME; }


		virtual void SetValue(const Array<uint8_t>& value) override { unused(value); }
		virtual void SetValue(Array<uint8_t>&& value) override { unused(value); }

		virtual void* GetDataPtr() const override { return const_cast<uint8_t*>(m_Value.data()); }
		virtual bool GetValueBool() const override { return m_Value.size() != 0; }
		virtual const Array<uint8_t>& GetValueBLOB() const override { return m_Value; }

		virtual Result ToString(ToStringContext& context) const override;

		virtual Variable* Clone(Array<uint8_t>& buffer) const override;
		virtual Variable* Clone(IHeap& heap) const override;


		virtual size_t GetSerializedSize() const { return Variable::GetSerializedSize() + sizeof(uint16_t) + m_Value.size(); }
		virtual Result Serialize(IOutputStream& output) const
		{
			uint16_t dataSize = static_cast<uint16_t>(m_Value.size());
			return Variable::Serialize(output)
				&& output.Write(dataSize)
				&& output.Write(m_Value.data());
		}
		virtual Result Deserialize(IInputStream& input)
		{
			if (!Variable::Deserialize(input))
				return false;

			uint16_t dataSize = 0;
			if (!input.Read(dataSize))
				return false;

			m_Value.resize(dataSize);

			return input.Read(m_Value.data(), dataSize);
		}
	};



	//////////////////////////////////////////////////////////////////////////////////////////////////
	//
	//	Variable generic boxing
	//

	template<class ValueType>
	class VariableByBinaryValue : public Variable
	{
	public:
		typedef std::decay_t<ValueType> ValueTypeDecay;


	private:
		ValueTypeDecay m_Value;

	public:
		VariableByBinaryValue()
		{
		}

		VariableByBinaryValue(const ValueTypeDecay& value)
			: m_Value(value)
		{
		}

		VariableByBinaryValue(ValueTypeDecay&& value)
			: m_Value(value)
		{
		}

		virtual StringCrc32 GetTypeName() const override { return "BinaryValue"_crc32c; }

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

			return m_Value == *reinterpret_cast<ValueTypeDecay*>(op.GetDataPtr());
		}

		virtual size_t GetSerializedSize() const { return Variable::GetSerializedSize() + sizeof(m_Value); }
		virtual Result Serialize(IOutputStream& output) const
		{
			return Variable::Serialize(output) && output.Write(m_Value);
		}
		virtual Result Deserialize(IInputStream& input)
		{
			return Variable::Deserialize(input) && input.Read(m_Value);
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
		using super = Variable;
		typedef std::decay_t<ValueType> ValueTypeDecay;

	private:
		ValueTypeDecay* m_Value = nullptr;

	public:

		VariableValueReference()
		{
		}

		VariableValueReference(const ValueTypeDecay& value)
			: m_Value(const_cast<ValueTypeDecay*>(&value))
		{
		}

		VariableValueReference(const VariableValueReference& value)
			: m_Value(value.m_Value)
		{
		}

		virtual StringCrc32 GetTypeName() const override { return "ref*"_crc32c; }// This is supposed to be specialized

		// Those overriding stay here so that we can override
		virtual void SetValue(int8_t value) override { super::SetValue(value); }
		virtual void SetValue(uint8_t value) override { super::SetValue(value); }
		virtual void SetValue(int16_t value) override { super::SetValue(value); }
		virtual void SetValue(uint16_t value) override { super::SetValue(value); }
		virtual void SetValue(int32_t value) override { super::SetValue(value); }
		virtual void SetValue(uint32_t value) override { super::SetValue(value); }
		virtual void SetValue(int64_t value) override { super::SetValue(value); }
		virtual void SetValue(uint64_t value) override { super::SetValue(value); }
		virtual void SetValue(float value) override { super::SetValue(value); }
		virtual void SetValue(double value) override { super::SetValue(value); }
		virtual void SetValue(const char* value) override { super::SetValue(value); }
		virtual void SetValue(const wchar_t* value) override { super::SetValue(value); }
		virtual void SetValue(const String& value) override { super::SetValue(value); }
		virtual void SetValue(StringCrc32 value) override { super::SetValue(value); }
		virtual void SetValue(StringCrc64 value) override { super::SetValue(value); }
		virtual void SetValue(const Array<uint8_t>& value) override { super::SetValue(value); }
		virtual void SetValue(Array<uint8_t>&& value) override { super::SetValue(value); }

		virtual void* GetDataPtr() const override { return m_Value; }
		virtual bool GetValueBool() const override { return super::GetValueBool(); }
		virtual int8_t GetValueInt8() const override { return super::GetValueInt8(); }
		virtual uint8_t GetValueUInt8() const override { return super::GetValueUInt8(); }
		virtual int16_t GetValueInt16() const override { return super::GetValueInt16(); }
		virtual uint16_t GetValueUInt16() const override { return super::GetValueUInt16(); }
		virtual int32_t GetValueInt32() const override { return super::GetValueInt32(); }
		virtual uint32_t GetValueUInt32() const override { return super::GetValueUInt32(); }
		virtual int64_t GetValueInt64() const override { return super::GetValueInt64(); }
		virtual uint64_t GetValueUInt64() const override { return super::GetValueUInt64(); }
		virtual float GetValueFloat() const override { return super::GetValueFloat(); }
		virtual double GetValueDouble() const override { return super::GetValueDouble(); }
		virtual String GetValueString() const override { return super::GetValueString(); }
		virtual const char* GetValueCharString() const override { return super::GetValueCharString(); }
		virtual const wchar_t* GetValueWCharString() const override { return super::GetValueWCharString(); }
		virtual StringCrc32 GetValueStringCrc32() const override { return super::GetValueStringCrc32(); }
		virtual StringCrc64 GetValueStringCrc64() const override { return super::GetValueStringCrc64(); }
		virtual const Array<uint8_t>& GetValueBLOB() const override { return super::GetValueBLOB(); }


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


		virtual size_t GetSerializedSize() const { return Variable::GetSerializedSize() + sizeof(*m_Value); }
		virtual Result Serialize(IOutputStream& output) const
		{
			return Variable::Serialize(output) && output.Write(*m_Value);
		}
		virtual Result Deserialize(IInputStream& input)
		{
			return Variable::Deserialize(input) && input.Read(*m_Value);
		}

	};



} // namespace SF




