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
#include "Util/SFStringCrc64.h"
#include "Util/SFStringCrc32.h"
#include "Util/SFString.h"
#include "Stream/SFStream.h"
#include "Util/SFStringSerialization.h"


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


		virtual void SetValue(bool value) { assert(false); unused(value); }
		virtual void SetValue(int8_t value) { assert(false); unused(value); }
		virtual void SetValue(uint8_t value) { assert(false); unused(value); }
		virtual void SetValue(int16_t value) { assert(false); unused(value); }
		virtual void SetValue(uint16_t value) { assert(false); unused(value); }
		virtual void SetValue(int32_t value) { assert(false); unused(value); }
		virtual void SetValue(uint32_t value) { assert(false); unused(value); }
		virtual void SetValue(int64_t value) { assert(false); unused(value); }
		virtual void SetValue(uint64_t value) { assert(false); unused(value); }
		virtual void SetValue(float value) { assert(false); unused(value); }
		virtual void SetValue(double value) { assert(false); unused(value); }
		virtual void SetValue(const char* value) { assert(false); unused(value); }
		virtual void SetValue(const wchar_t* value) { assert(false); unused(value); }
		virtual void SetValue(const String& value) { assert(false); unused(value); }
		virtual void SetValue(StringCrc32 value) { assert(false); unused(value); }
		virtual void SetValue(StringCrc64 value) { assert(false); unused(value); }
		virtual void SetValue(const Array<const uint8_t>& value) { assert(false); unused(value); }


		virtual void* GetDataPtr() const { return nullptr; }
		virtual bool GetValueBool() const { assert(false); return false; }
		virtual int8_t GetValueInt8() const { assert(false); return 0; }
		virtual uint8_t GetValueUInt8() const { assert(false); return 0; }
		virtual int16_t GetValueInt16() const { assert(false); return 0; }
		virtual uint16_t GetValueUInt16() const { assert(false); return 0; }
		virtual int32_t GetValueInt32() const { assert(false); return 0; }
		virtual uint32_t GetValueUInt32() const { assert(false); return 0; }
		virtual int64_t GetValueInt64() const { assert(false); return 0; }
		virtual uint64_t GetValueUInt64() const { assert(false); return 0; }
		virtual float GetValueFloat() const { assert(false); return 0; }
		virtual double GetValueDouble() const { assert(false); return 0; }
		virtual String GetValueString() const { return String_Empty; }
		virtual const char* GetValueCharString() const { return nullptr; }
		virtual const wchar_t* GetValueWCharString() const { return nullptr; }
		virtual StringCrc32 GetValueStringCrc32() const { return StringCrc32(); }
		virtual StringCrc64 GetValueStringCrc64() const { return StringCrc64(); }
		virtual const Array<uint8_t>& GetValueBLOB() const { assert(false); static StaticArray<uint8_t,1> temp; return temp; }

		// Template implementation for type based GetValue access
		template<class ValueType>
		ValueType GetValue() const;

		// Variable instance size
		virtual size_t GetVariableSize() const { return sizeof(Variable); }

		// Serialization
		virtual size_t GetSerializedSize() const { return 0; }
		virtual Result Serialize(IOutputStream& output) const { return ResultCode::SUCCESS; }
		virtual Result Deserialize(IInputStream& input) { return ResultCode::SUCCESS; } // We deserialze type name from caller

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
		virtual bool operator != (const Variable& op) const;
	};



	template<> inline bool Variable::GetValue<bool>() const { return GetValueBool(); }
	template<> inline int8_t Variable::GetValue<int8_t>() const { return GetValueInt8(); }
	template<> inline uint8_t Variable::GetValue<uint8_t>() const { return GetValueUInt8(); }
	template<> inline int16_t Variable::GetValue<int16_t>() const { return GetValueInt16(); }
	template<> inline uint16_t Variable::GetValue<uint16_t>() const { return GetValueUInt16(); }
	template<> inline int32_t Variable::GetValue<int32_t>() const { return GetValueInt32(); }
	template<> inline uint32_t Variable::GetValue<uint32_t>() const { return GetValueUInt32(); }
	template<> inline int64_t Variable::GetValue<int64_t>() const { return GetValueInt64(); }
	template<> inline uint64_t Variable::GetValue<uint64_t>() const { return GetValueUInt64(); }
	template<> inline float Variable::GetValue<float>() const { return GetValueFloat(); }
	template<> inline double Variable::GetValue<double>() const { return GetValueDouble(); }
	template<> inline String Variable::GetValue<String>() const { return GetValueString(); }
	template<> inline const char* Variable::GetValue<const char*>() const { return GetValueCharString(); }
	template<> inline const wchar_t* Variable::GetValue<const wchar_t*>() const { return GetValueWCharString(); }
	template<> inline StringCrc32 Variable::GetValue<StringCrc32>() const { return GetValueStringCrc32(); }
	template<> inline StringCrc64 Variable::GetValue<StringCrc64>() const { return GetValueStringCrc64(); }
	//template<> inline Array<uint8_t> Variable::GetValue<Array<uint8_t>>() const { return GetValueBLOB(); }






	//////////////////////////////////////////////////////////////////////////////////////////////////
	//
	//	Variable generic boxing
	//

	template<class ValueType>
	class SF_DECLARE_ALIGN_DOUBLE VariableByBinaryValue : public Variable
	{
	public:
		typedef std::decay_t<ValueType> ValueTypeDecay;


	private:
		SF_DECLARE_ALIGN_DOUBLE ValueTypeDecay m_Value;

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

		virtual size_t GetSerializedSize() const  override { return sizeof(m_Value); }
		virtual Result Serialize(IOutputStream& output) const override
		{
			return output << m_Value;
		}
		virtual Result Deserialize(IInputStream& input) override
		{
			return input >> m_Value;
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
		virtual void SetValue(const Array<const uint8_t>& value) override { super::SetValue(value); }

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

			return memcmp(GetDataPtr(), op.GetDataPtr(), sizeof(ValueType));
		}


		virtual size_t GetSerializedSize() const  override { return sizeof(*m_Value); }
		virtual Result Serialize(IOutputStream& output) const override
		{
			return output << *m_Value;
		}
		virtual Result Deserialize(IInputStream& input) override
		{
			return input >> *m_Value;
		}

	};

} // namespace SF




