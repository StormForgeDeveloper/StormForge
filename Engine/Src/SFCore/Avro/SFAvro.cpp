////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) The Braves
// 
// Author : KyungKun Ko
//
// Description : Avro wrapper
//	
//
////////////////////////////////////////////////////////////////////////////////

#include "SFCorePCH.h"
#include "Avro/SFAvro.h"
#include "Util/SFString.h"
#include "Util/SFStringFormat.h"
#include "avro.h"
#include "json/json.h"
#include "bson/bson.h"
#include "Stream/SFCompressedStream.h"


namespace SF
{
	namespace Avro
	{

		static_assert(ValueType::String == ValueType(avro_type_t::AVRO_STRING), "The definition should be same with avro_type_t");
		static_assert(ValueType::Bytes == ValueType(avro_type_t::AVRO_BYTES), "The definition should be same with avro_type_t");
		static_assert(ValueType::Int32 == ValueType(avro_type_t::AVRO_INT32), "The definition should be same with avro_type_t");
		static_assert(ValueType::Int64 == ValueType(avro_type_t::AVRO_INT64), "The definition should be same with avro_type_t");
		static_assert(ValueType::Float == ValueType(avro_type_t::AVRO_FLOAT), "The definition should be same with avro_type_t");
		static_assert(ValueType::Double == ValueType(avro_type_t::AVRO_DOUBLE), "The definition should be same with avro_type_t");
		static_assert(ValueType::Boolean == ValueType(avro_type_t::AVRO_BOOLEAN), "The definition should be same with avro_type_t");
		static_assert(ValueType::Null == ValueType(avro_type_t::AVRO_NULL), "The definition should be same with avro_type_t");
		static_assert(ValueType::Record == ValueType(avro_type_t::AVRO_RECORD), "The definition should be same with avro_type_t");
		static_assert(ValueType::Enum == ValueType(avro_type_t::AVRO_ENUM), "The definition should be same with avro_type_t");
		static_assert(ValueType::Fixed == ValueType(avro_type_t::AVRO_FIXED), "The definition should be same with avro_type_t");
		static_assert(ValueType::Map == ValueType(avro_type_t::AVRO_MAP), "The definition should be same with avro_type_t");
		static_assert(ValueType::Array == ValueType(avro_type_t::AVRO_ARRAY), "The definition should be same with avro_type_t");
		static_assert(ValueType::Union == ValueType(avro_type_t::AVRO_UNION), "The definition should be same with avro_type_t");
		static_assert(ValueType::Link == ValueType(avro_type_t::AVRO_LINK), "The definition should be same with avro_type_t");


		const char* GetErrorString()
		{
			return avro_strerror();
		}


        void DumpAvroDataFormat(const AvroValue& value, int indent)
        {
            static const char* ValueTypeNames[] =
            {
                "String",
                "Bytes",
                "Int32",
                "Int64",
                "Float",
                "Double",
                "Boolean",
                "Null",
                "Record",
                "Enum",
                "Fixed",
                "Map",
                "Array",
                "Union",
                "Link"
            };


            String indentString;
            for (int iIndent = 0; iIndent < indent; iIndent++)
                indentString.Append("\t");

            if (value.GetType() == Avro::ValueType::Record || value.GetType() == Avro::ValueType::Array)
            {
                size_t numObjectFields = value.GetArraySize();
                for (int iField = 0; iField < numObjectFields; iField++)
                {
                    SF::AvroValue subValue;
                    const char* subValueName{};
                    value.GetArrayItem(iField, subValue, subValueName);

                    SFLog(System, Info, "{0}name:{1}, type:{2}", indentString, subValueName, ValueTypeNames[(int)subValue.GetType()]);

                    DumpAvroDataFormat(subValue, indent + 1);
                }
            }
            else if (indent == 0)
            {
                SFLog(System, Info, "{0}type:{1}", indentString, ValueTypeNames[(int)value.GetType()]);
            }

            Service::LogModule->Flush();
        }

        Result ParseAvroValue(const Array<const uint8_t>& avorData, AvroValue& outValue)
        {
            if (avorData.size() == 0)
                return ResultCode::NO_DATA_EXIST;

            AvroReader reader(avorData);

            String schemaString = reader.ReadString();
            if (schemaString.IsNullOrEmpty())
                return ResultCode::INVALID_DATA;

            AvroSchema schema(schemaString);

            outValue.Init(schema);
            return reader.ReadValue(outValue);
        }
	}


    AvroSchema::AvroSchema(const avro_schema_t& schema)
        : m_Handle(schema)
    {
        if (m_Handle)
        {
            avro_schema_incref(m_Handle);
        }
    }

	AvroSchema::AvroSchema(const AvroSchema& schema)
		: m_Handle(schema.m_Handle)
	{
		if (m_Handle != nullptr)
			avro_schema_incref(m_Handle);
	}
	
	AvroSchema::AvroSchema(const Array<char>& schemaData)
	{
		Init(schemaData);
	}

    AvroSchema::AvroSchema(const char* schema)
    {
        Init(ArrayView<const char>(strlen(schema), schema));
    }

	AvroSchema::~AvroSchema()
	{
        Reset();
	}

    void AvroSchema::Reset()
    {
        if (m_Handle != nullptr)
        {
            avro_schema_decref(m_Handle);
            m_Handle = nullptr;
        }
    }

    bool AvroSchema::IsValid() const
    {
        return m_Handle != nullptr;
    }

    Result AvroSchema::Init(const avro_schema_t& schema)
    {
        Reset();

        m_Handle = schema;

        if (m_Handle)
        {
            avro_schema_incref(m_Handle);
        }

        m_SchemaString = nullptr;

        return ResultCode::SUCCESS;
    }

	Result AvroSchema::Init(const Array<const char>& schemaData)
	{
        Reset();

        m_SchemaString = schemaData;

		int res = avro_schema_from_json_length(m_SchemaString.data(), m_SchemaString.length(), &m_Handle);
		if (res)
		{
			SFLog(System, Error, "Error parsing schema file: {0}", avro_strerror());
			return ResultCode::FAIL;
		}

		return ResultCode::SUCCESS;
	}

    Result AvroSchema::Init(const Array<char>& schemaData)
    {
        return Init(ArrayView<const char>(schemaData));
    }

    bool AvroSchema::HasField(const char* fieldName) const
    {
        if (m_Handle == nullptr)
            return false;

        return avro_schema_record_field_get_index(m_Handle, fieldName) >= 0;
    }

    Result AvroSchema::AppendField(const char* fieldName, const AvroSchema& schema)
    {
        if (m_Handle == nullptr)
            return ResultCode::NOT_INITIALIZED;

        if (avro_schema_record_field_get_index(m_Handle, fieldName) >= 0)
        {
            return ResultCode::ALREADY_EXIST;
        }

        int iRet = avro_schema_record_field_append(m_Handle, fieldName, schema);
        if (iRet)
        {
            return ResultCode::FAIL;
        }

        m_SchemaString = "";
        return ResultCode::SUCCESS;
    }

    Result AvroSchema::AppendField(const char* fieldName, const avro_schema_t& schema)
    {
        if (m_Handle == nullptr)
            return ResultCode::NOT_INITIALIZED;

        if (avro_schema_record_field_get_index(m_Handle, fieldName) >= 0)
        {
            return ResultCode::ALREADY_EXIST;
        }

        int iRet = avro_schema_record_field_append(m_Handle, fieldName, schema);
        if (iRet)
        {
            return ResultCode::FAIL;
        }

        m_SchemaString = "";
        return ResultCode::SUCCESS;
    }

    Result AvroSchema::AppendFieldInt(const char* fieldName)
    {
        return AppendField(fieldName, avro_schema_int());
    }

    Result AvroSchema::AppendFieldInt64(const char* fieldName)
    {
        return AppendField(fieldName, avro_schema_long());
    }

    Result AvroSchema::AppendFieldFloat(const char* fieldName)
    {
        return AppendField(fieldName, avro_schema_float());
    }

    Result AvroSchema::AppendFieldDouble(const char* fieldName)
    {
        return AppendField(fieldName, avro_schema_double());
    }

    Result AvroSchema::AppendFieldBool(const char* fieldName)
    {
        return AppendField(fieldName, avro_schema_boolean());
    }

    Result AvroSchema::AppendFieldString(const char* fieldName)
    {
        return AppendField(fieldName, avro_schema_string());
    }

    Result AvroSchema::AppendFieldBytes(const char* fieldName)
    {
        return AppendField(fieldName, avro_schema_bytes());
    }

    const String& AvroSchema::GetSchemaString() const
    {
        if (m_SchemaString.length() == 0)
        {
            DynamicArray<char> memoryBuffer;
            memoryBuffer.resize(4096);
            AvroWriter writer(memoryBuffer);

            int ret = avro_schema_to_json(m_Handle, writer);
            if (ret)
            {
                SFLog(System, Error, "Avro schema serialization error: {0}", avro_strerror());
                return m_SchemaString;
            }
            memoryBuffer.data()[writer.WrittenSize()] = '\0';
            m_SchemaString = (const char*)memoryBuffer.data();
        }

        return m_SchemaString;
    }

    avro_schema_t AvroSchema::GetArrayItemsSchema() const
    {
        return avro_schema_array_items(m_Handle);
    }

    // 
    Result AvroSchema::operator << (IInputStream& in)
    {
        Result hr;

        Reset();
        String jsonString;

        hr = in >> jsonString;
        if (!hr.IsSuccess())
            return hr;
        
        return Init(jsonString);
    }

    Result AvroSchema::operator >> (IOutputStream& out) const
    {
        return out << GetSchemaString();
    }

    AvroSchema& AvroSchema::operator=(const avro_schema_t& schema)
    {
        Reset();
        m_Handle = schema;
        if (m_Handle != nullptr)
        {
            avro_schema_incref(m_Handle);
        }
        return *this;
    }
    AvroSchema& AvroSchema::operator=(const AvroSchema& schema)
    {
        Reset();
        m_Handle = schema;
        if (m_Handle != nullptr)
        {
            avro_schema_incref(m_Handle);
        }
        return *this;
    }



    // 
    Result operator >> (AvroReader& in, AvroSchema& op)
    {
        Result hr;

        op.Reset();

        String jsonString = in.ReadString();

        return op.Init(jsonString);
    }

    Result operator << (AvroWriter& out, const AvroSchema& op)
    {
        Result hr;

        String schemaString = op.GetSchemaString();

        return out.WriteString(schemaString);
    }

	AvroValue::AvroValue(const AvroSchema& schema)
	{
        static_assert(sizeof(AvroValue::m_ValueBuffer) >= sizeof(avro_value_t));

		m_OwnerOfValue = true;
        avro_value_iface_t* dataClass = avro_generic_class_from_schema(schema);
        if (dataClass != nullptr)
        {
            avro_generic_value_new(dataClass, &m_DataValue);
        }
        else
        {
            const char* avroError = avro_strerror();
            SFLog(System, Error, "Creating generic avro value form schema has failed, error:{0}", avroError);
        }
	}

    AvroValue::AvroValue(const AvroValue& src)
    {
        if (src.m_OwnerOfValue)
        {
            m_OwnerOfValue = true;
            avro_value_copy_ref(&m_DataValue, &src.m_DataValue);
        }
    }

	AvroValue::~AvroValue()
	{
		if (m_OwnerOfValue)
			avro_value_decref(&m_DataValue);
        m_DataValue = {};
	}

    void AvroValue::Init(const AvroSchema& schema)
    {
        m_OwnerOfValue = true;
        avro_value_iface_t* dataClass = avro_generic_class_from_schema(schema);
        if (dataClass == nullptr)
        {
            SFLog(System, Error, "AvroValue::Init, Creating generic avro value form schema has failed, invalid dataClass");
            return;
        }
        avro_generic_value_new(dataClass, &m_DataValue);
    }

    void AvroValue::Reset()
    {
        if (m_OwnerOfValue)
            avro_value_decref(&m_DataValue);
        m_DataValue = {};
    }

    size_t AvroValue::GetSerializedSize() const
    {
        size_t valueSize{};
        avro_value_sizeof(&m_DataValue, &valueSize);
        return valueSize;
    }

    Result AvroValue::GetAvroSchema(AvroSchema& outSchema)
    {
        avro_schema_t schema = avro_value_get_schema(&m_DataValue);
        return outSchema.Init(schema);
    }

	Avro::ValueType AvroValue::GetType() const
	{
		return (Avro::ValueType)avro_value_get_type(&m_DataValue);
	}

	Result AvroValue::GetField(const char* fieldName, AvroValue& value) const
	{
        size_t index{};
		int res = avro_value_get_by_name(&m_DataValue, fieldName, value, &index);
		if (res != 0)
		{
            SFLog(System, Error, "AvroValue doesn't have field:{0}, error:{1}", fieldName, avro_strerror());
            return ResultCode::NOT_EXIST;
		}

		return ResultCode::SUCCESS;
	}

	const char* AvroValue::AsString() const
	{
		const char* stringValue{};
		size_t strLen = 0;
		int res = avro_value_get_string(&m_DataValue, &stringValue, &strLen);
        if (res != 0)
        {
            SFLog(System, Error, "AvroValue parsing has type error:{0}, type:{1}, '{2}'", res, (int)GetType(), avro_strerror());
            return nullptr;
        }

		return stringValue;
	}

	int AvroValue::AsInt() const
	{
		int value{};
		int res = avro_value_get_int(&m_DataValue, &value);
		if (res != 0)
        {
            SFLog(System, Error, "AvroValue parsing has type error:{0}, '{1}'", res, avro_strerror());
            return 0;
        }

		return value;
	}

    int64_t AvroValue::AsInt64() const
    {
        int64_t value{};
        int res = avro_value_get_long(&m_DataValue, &value);
        if (res != 0)
        {
            SFLog(System, Error, "AvroValue parsing has type error:{0}, '{1}'", res, avro_strerror());
            return 0;
        }

        return value;
    }

	float AvroValue::AsFloat() const
	{
		float value{};
		int res = avro_value_get_float(&m_DataValue, &value);
		if (res != 0)
        {
            SFLog(System, Error, "AvroValue parsing has type error:{0}, '{1}'", res, avro_strerror());
            return 0;
        }

		return value;
	}

	double AvroValue::AsDouble() const
	{
		double value{};
		int res = avro_value_get_double(&m_DataValue, &value);
		if (res != 0)
        {
            SFLog(System, Error, "AvroValue parsing has type error:{0}, '{1}'", res, avro_strerror());
            return 0;
        }

		return value;
	}

	bool AvroValue::AsBoolean() const
	{
		int value{};
		int res = avro_value_get_boolean(&m_DataValue, &value);
		if (res != 0)
        {
            SFLog(System, Error, "AvroValue parsing has type error:{0}, '{1}'", res, avro_strerror());
            return 0;
        }

		return value != 0;
	}

    Guid AvroValue::AsGuid() const
    {
        const void* buf{};
        size_t size{};
        int res = avro_value_get_fixed(&m_DataValue, &buf, &size);
        if (res != 0)
        {
            SFLog(System, Error, "AvroValue parsing has type error:{0}, '{1}'", res, avro_strerror());
            return Guid();
        }


        return Guid::FromBytes(reinterpret_cast<const uint8_t*>(buf));
    }

	ArrayView<const uint8_t> AvroValue::AsBytes() const
	{
		const void* buf{};
		size_t size{};
		int res = avro_value_get_bytes(&m_DataValue, &buf, &size);
		if (res != 0)
        {
            SFLog(System, Error, "AvroValue parsing has type error:{0}, '{1}'", res, avro_strerror());
            return ArrayView<const uint8_t>();
        }


		return ArrayView<const uint8_t>(size, reinterpret_cast<const uint8_t*>(buf));
	}

	// for array/map
	size_t AvroValue::GetArraySize() const
	{
		size_t value{};
		int res = avro_value_get_size(&m_DataValue, &value);
		if (res != 0)
        {
            SFLog(System, Error, "AvroValue parsing has type error:{0}, '{1}'", res, avro_strerror());
            return 0;
        }

		return value;
	}

	// for array/map
	Result AvroValue::GetArrayItem(int i, AvroValue& value, const char*& name) const
	{
		int res = avro_value_get_by_index(&m_DataValue, i, value, &name);
		if (res != 0)
			return ResultCode::NOT_EXIST;

		return ResultCode::SUCCESS;
	}

    Result AvroValue::NewArrayItem(AvroValue& outValue)
    {
        outValue.Reset();
        int res = avro_value_append(&m_DataValue, outValue, nullptr);
        if (res != 0)
            return ResultCode::NOT_EXIST;

        return ResultCode::SUCCESS;
    }

    Result AvroValue::GetFieldByIndex(int i, AvroValue& value, const char*& name) const
    {
        int res = avro_value_get_by_index(&m_DataValue, i, value, &name);
        if (res != 0)
            return ResultCode::NOT_EXIST;

        return ResultCode::SUCCESS;
    }

    Result AvroValue::SetValue(const char* Name, bool Value)
    {
        avro_value_t avValue{};
        if (avro_value_get_by_name(&m_DataValue, Name, &avValue, NULL) == 0)
        {
            int ret = avro_value_set_boolean(&avValue, Value);
            if (ret != 0)
            {
                SFLog(System, Error, "Avro SetValue: error invalid type: {0}", Name);
                return ResultCode::INVALID_TYPE;
            }

            return ResultCode::SUCCESS;
        }
        else
        {
            SFLog(System, Error, "Avro SetValue:  error value not found: {0}", Name);
            return ResultCode::VARIABLE_NOT_FOUND;
        }
    }

    Result AvroValue::SetValue(const char* Name, int Value)
    {
        avro_value_t avValue{};
        if (avro_value_get_by_name(&m_DataValue, Name, &avValue, NULL) == 0)
        {
            int ret = avro_value_set_int(&avValue, Value);
            if (ret != 0)
            {
                SFLog(System, Error, "Avro SetValue: error invalid type: {0}", Name);
                return ResultCode::INVALID_TYPE;
            }

            return ResultCode::SUCCESS;
        }
        else
        {
            SFLog(System, Error, "Avro SetValue:  error value not found: {0}", Name);
            return ResultCode::VARIABLE_NOT_FOUND;
        }
    }

    Result AvroValue::SetValue(const char* Name, int64_t Value)
    {
        avro_value_t avValue{};
        if (avro_value_get_by_name(&m_DataValue, Name, &avValue, NULL) == 0)
        {
            int ret = avro_value_set_long(&avValue, Value);
            if (ret != 0)
            {
                SFLog(System, Error, "Avro SetValue: error invalid type: {0}", Name);
                return ResultCode::INVALID_TYPE;
            }

            return ResultCode::SUCCESS;
        }
        else
        {
            SFLog(System, Error, "Avro SetValue:  error value not found: {0}", Name);
            return ResultCode::VARIABLE_NOT_FOUND;
        }
    }
    Result AvroValue::SetValue(const char* Name, const char* Value)
    {
        avro_value_t avValue{};
        if (avro_value_get_by_name(&m_DataValue, Name, &avValue, NULL) == 0)
        {
            //if (avro_value_get_type(avValue) == avro_type_t::AVRO_STRING)
            int ret = avro_value_set_string(&avValue, Value);
            if (ret != 0)
            {
                SFLog(System, Error, "Avro SetValue: error invalid type: {0}", Name);
                return ResultCode::INVALID_TYPE;
            }

            return ResultCode::SUCCESS;
        }
        else
        {
            SFLog(System, Error, "Avro SetValue:  error value not found: {0}", Name);
            return ResultCode::VARIABLE_NOT_FOUND;
        }
    }

    Result AvroValue::SetValue(const char* Name, const String& Value)
    {
        avro_value_t avValue{};
        if (avro_value_get_by_name(&m_DataValue, Name, &avValue, NULL) == 0)
        {
            int ret = avro_value_set_string_len(&avValue, Value.data(), Value.length() + 1);
            if (ret != 0)
            {
                SFLog(System, Error, "Avro SetValue: error invalid type: {0}", Name);
                return ResultCode::INVALID_TYPE;
            }

            return ResultCode::SUCCESS;
        }
        else
        {
            SFLog(System, Error, "Avro SetValue:  error value not found: {0}", Name);
            return ResultCode::VARIABLE_NOT_FOUND;
        }
    }

    Result AvroValue::SetValue(const char* Name, float Value)
    {
        avro_value_t avValue{};
        if (avro_value_get_by_name(&m_DataValue, Name, &avValue, NULL) == 0)
        {
            int ret = avro_value_set_float(&avValue, Value);
            if (ret != 0)
            {
                SFLog(System, Error, "Avro SetValue: error invalid type: {0}", Name);
                return ResultCode::INVALID_TYPE;
            }

            return ResultCode::SUCCESS;
        }
        else
        {
            SFLog(System, Error, "Avro SetValue:  error value not found: {0}", Name);
            return ResultCode::VARIABLE_NOT_FOUND;
        }
    }

    Result AvroValue::SetValue(const char* Name, double Value)
    {
        avro_value_t avValue{};
        if (avro_value_get_by_name(&m_DataValue, Name, &avValue, NULL) == 0)
        {
            int ret = avro_value_set_double(&avValue, Value);
            if (ret != 0)
            {
                SFLog(System, Error, "Avro SetValue: error invalid type: {0}", Name);
                return ResultCode::INVALID_TYPE;
            }

            return ResultCode::SUCCESS;
        }
        else
        {
            SFLog(System, Error, "Avro SetValue:  error value not found: {0}", Name);
            return ResultCode::VARIABLE_NOT_FOUND;
        }
    }

    Result AvroValue::SetValue(const char* Name, const Guid& Value)
    {
        avro_value_t avValue{};
        if (avro_value_get_by_name(&m_DataValue, Name, &avValue, NULL) == 0)
        {
            int ret = avro_value_set_fixed(&avValue, (void*)Value.data, 16);
            if (ret != 0)
            {
                SFLog(System, Error, "Avro SetValue: error invalid type: {0}", Name);
                return ResultCode::INVALID_TYPE;
            }

            return ResultCode::SUCCESS;
        }
        else
        {
            SFLog(System, Error, "Avro SetValue:  error value not found: {0}", Name);
            return ResultCode::VARIABLE_NOT_FOUND;
        }
    }

    Result AvroValue::SetValue(const char* Name, const Array<const uint8_t>& Value)
    {
        avro_value_t avValue{};
        if (avro_value_get_by_name(&m_DataValue, Name, &avValue, NULL) == 0)
        {
            int ret = avro_value_set_bytes(&avValue, (void*)Value.data(), Value.size());
            if (ret != 0)
            {
                SFLog(System, Error, "Avro SetValue: error invalid type: {0}", Name);
                return ResultCode::INVALID_TYPE;
            }

            return ResultCode::SUCCESS;
        }
        else
        {
            SFLog(System, Error, "Avro SetValue:  error value not found: {0}", Name);
            return ResultCode::VARIABLE_NOT_FOUND;
        }
    }

    Result AvroValue::SetValue(const char* Name, const Array<uint8_t>& Value)
    {
        avro_value_t avValue{};
        if (avro_value_get_by_name(&m_DataValue, Name, &avValue, NULL) == 0)
        {
            int ret = avro_value_set_bytes(&avValue, (void*)Value.data(), Value.size());
            if (ret != 0)
            {
                SFLog(System, Error, "Avro SetValue: error invalid type: {0}", Name);
                return ResultCode::INVALID_TYPE;
            }

            return ResultCode::SUCCESS;
        }
        else
        {
            SFLog(System, Error, "Avro SetValue:  error value not found: {0}", Name);
            return ResultCode::VARIABLE_NOT_FOUND;
        }
    }



	AvroReader::AvroReader(const SF::Array<char>& binData)
	{
		m_Handle = avro_reader_memory(binData.data(), binData.size());
	}

    AvroReader::AvroReader(const SF::Array<const uint8_t>& binData)
    {
        m_Handle = avro_reader_memory(reinterpret_cast<const char*>(binData.data()), binData.size());
    }
    AvroReader::~AvroReader()
	{
		if (m_Handle != nullptr)
			avro_reader_free(m_Handle);
	}

    bool AvroReader::IsAtEnd() const
    {
        return m_Handle == nullptr || avro_reader_is_eof(m_Handle);
    }

    uint8_t AvroReader::ReadByte()
    {
        uint8_t value;
        avro_read(m_Handle, &value, 1);

        return value;
    }

    Result AvroReader::ReadBytes(Array<uint8_t>& data)
    {
        Result hr;

        size_t readSize = ReadInt64();

        if (data.size() < readSize)
        {
            hr = data.resize(readSize);
            if (!hr.IsSuccess())
                return hr;
        }

        int iRet = avro_read(m_Handle, data.data(), data.size());
        if (iRet)
        {
            SFLog(System, Error, "Avro Error read bytes: size:{0}, error:{1}", readSize, avro_strerror());
        }

        return hr;
    }

    int64_t AvroReader::ReadInt64()
    {
        // 7bit packed integer
        uint64_t b = ReadByte();
        uint64_t n = b & 0x7FUL;
        int shift = 7;
        while ((b & 0x80) != 0)
        {
            b = ReadByte();
            n |= (b & 0x7FUL) << shift;
            shift += 7;
        }
        int64_t value = (int64_t)n;
        return (-(value & 0x01L)) ^ ((value >> 1) & 0x7fffffffffffffffL);
    }

    String AvroReader::ReadString()
    {
        Result hr;
        size_t len = ReadInt64();

        String stringBuffer;
        stringBuffer.Resize(len);
        int iRet = avro_read(m_Handle, (void*)stringBuffer.data(), len);
        if (iRet)
        {
            SFLog(System, Error, "Avro Error read string: {0}", avro_strerror());
        }

        return stringBuffer;
    }

	Result AvroReader::ReadValue(AvroValue& value)
	{
		int res = avro_value_read(m_Handle, value);
		if (res)
		{
			SFLog(System, Error, "Error reading value: {0}", avro_strerror());
			return ResultCode::FAIL;
		}

		return ResultCode::SUCCESS;
	}





    AvroWriter::AvroWriter(SF::Array<char>& memoryBuffer)
    {
        m_Handle = avro_writer_memory(memoryBuffer.data(), memoryBuffer.size());
    }

    AvroWriter::AvroWriter(SF::Array<uint8_t>& memoryBuffer)
    {
        m_Handle = avro_writer_memory((char*)memoryBuffer.data(), memoryBuffer.size());
    }

    AvroWriter::~AvroWriter()
    {
        if (m_Handle != nullptr)
            avro_writer_free(m_Handle);
    }

    Result AvroWriter::Write(bool value)
    {
        return WriteByte(value ? 1 : 0);
    }

    Result AvroWriter::WriteByte(uint8_t value)
    {
        avro_write(m_Handle, &value, 1);

        return ResultCode::SUCCESS;
    }

    Result AvroWriter::WriteBytes(const Array<const uint8_t>& data)
    {
        WriteInt64(data.size());
        avro_write(m_Handle, (void*)data.data(), data.size());

        return ResultCode::SUCCESS;
    }

    Result AvroWriter::WriteInt64(int64_t value)
    {
        // 7bit packed integer
        uint64_t n = (uint64_t)((value << 1) ^ (value >> 63));
        while ((n & ~0x7FUL) != 0)
        {
            WriteByte((uint8_t)((n & 0x7f) | 0x80));
            n >>= 7;
        }
        WriteByte((uint8_t)n);

        return ResultCode::SUCCESS;
    }

    Result AvroWriter::WriteString(const char* value)
    {
        Result hr;
        size_t len = StrUtil::StringLen(value);

        hr = WriteInt64(len);
        if (!hr.IsSuccess())
            return hr;

        int iRet = avro_write(m_Handle, (void*)value, len);
        if (iRet)
        {
            SFLog(System, Error, "Avro Error read string: {0}", avro_strerror());
            return ResultCode::FAIL;
        }

        return ResultCode::SUCCESS;
    }

    Result AvroWriter::WriteString(const String& value)
    {
        Result hr;
        size_t len = value.length();

        hr = WriteInt64(len);
        if (!hr.IsSuccess())
            return hr;

        int iRet = avro_write(m_Handle, (void*)value.data(), len);
        if (iRet)
        {
            SFLog(System, Error, "Avro Error write string: {0}", avro_strerror());
            return ResultCode::FAIL;
        }

        return ResultCode::SUCCESS;
    }

    Result AvroWriter::WriteValue(const AvroValue& value)
    {
        avro_value_write(m_Handle, value);

        return ResultCode::SUCCESS;
    }

    size_t AvroWriter::WrittenSize()
    {
        if (m_Handle != nullptr)
            return avro_writer_tell(m_Handle);

        return 0;
    }


    void AvroWriter::Flush()
    {
        avro_writer_flush(m_Handle);
    }



}
