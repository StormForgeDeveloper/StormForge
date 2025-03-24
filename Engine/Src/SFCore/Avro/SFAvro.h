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

#pragma once

#include "SFTypedefs.h"
#include "Util/SFLog.h"
#include "Util/SFGuid.h"


typedef struct avro_obj_t* avro_schema_t;
typedef struct avro_value_iface  avro_value_iface_t; 
typedef struct avro_value avro_value_t;
typedef struct avro_reader_t_* avro_reader_t;
typedef struct avro_writer_t_* avro_writer_t;


namespace SF
{
    class AvroValue;
    class AvroReader;
    class AvroWriter;

	namespace Avro
	{
		// The definition should be same with avro_type_t
		enum class ValueType : uint8_t
		{
			String,
			Bytes,
			Int32,
			Int64,
			Float,
			Double,
			Boolean,
			Null,
			Record,
			Enum,
			Fixed,
			Map,
			Array,
			Union,
			Link
		};

		const char* GetErrorString();

        // Dump Avro schema structure of the value
        void DumpAvroDataFormat(const AvroValue& value, int indent = 0);

        // helper function
        Result ParseAvroValue(const Array<const uint8_t>& avorData, AvroValue& outValue);
	}



	class AvroSchema
	{
	public:
		AvroSchema() {}

		AvroSchema(const avro_schema_t& schema);
		AvroSchema(const AvroSchema& schema);
		AvroSchema(const SF::Array<char>& schemaData);
        AvroSchema(const char* schemaData);

        bool IsValid() const;

		~AvroSchema();

        void Reset();

		// initialize with schema string data
        Result Init(const avro_schema_t& schema);
        Result Init(const Array<char>& schemaData);
        Result Init(const String& schemaData)        { return Init(ArrayView<const char>(schemaData.GetBufferLength(), schemaData.data())); }
        Result Init(const Array<const char>& schemaData);

        bool HasField(const char* fieldName) const;

        Result AppendField(const char* fieldName, const AvroSchema& schema);
        Result AppendField(const char* fieldName, const avro_schema_t& schema);

        Result AppendFieldInt(const char* fieldName);
        Result AppendFieldInt64(const char* fieldName);
        Result AppendFieldFloat(const char* fieldName);
        Result AppendFieldDouble(const char* fieldName);
        Result AppendFieldBool(const char* fieldName);
        Result AppendFieldString(const char* fieldName);
        Result AppendFieldBytes(const char* fieldName);

        template<class FieldType>
        Result AppendField(const char* fieldName)
        {
            return ResultCode::NOT_IMPLEMENTED;
        }

		operator avro_schema_t() { return m_Handle; }
		operator avro_schema_t() const { return m_Handle; }
        const String& GetSchemaString() const;

        // Get Array item schema if it is array
        avro_schema_t GetArrayItemsSchema() const;

        // bson binary stream
        Result operator << (IInputStream& in);
        Result operator >> (IOutputStream& out) const;

        friend Result operator >> (AvroReader& in, AvroSchema& op);
        friend Result operator << (AvroWriter& out, const AvroSchema& op);

        AvroSchema& operator=(const avro_schema_t& schema);
        AvroSchema& operator=(const AvroSchema& schema);


	private:
		avro_schema_t m_Handle{};

        mutable String m_SchemaString;
	};

    template<>
    inline Result AvroSchema::AppendField<int>(const char* fieldName)
    {
        return AppendFieldInt(fieldName);
    }

    template<>
    inline Result AvroSchema::AppendField<int64_t>(const char* fieldName)
    {
        return AppendFieldInt64(fieldName);
    }

    template<>
    inline Result AvroSchema::AppendField<const char*>(const char* fieldName)
    {
        return AppendFieldString(fieldName);
    }

    template<>
    inline Result AvroSchema::AppendField<String>(const char* fieldName)
    {
        return AppendFieldString(fieldName);
    }



	class AvroValue
	{
	public:

		AvroValue() = default;

		AvroValue(const AvroSchema& schema);
        AvroValue(const AvroValue& src);

		~AvroValue();

        // Init value with schema
        void Init(const AvroSchema& schema);

        // Reset and clear all allocated values
        void Reset();

		operator avro_value_t* () const { return &m_DataValue; }

        // Get serialized size of this value
        size_t GetSerializedSize() const;

        // Get avor value schema
        Result GetAvroSchema(AvroSchema& outSchema);

		Avro::ValueType GetType() const;

		Result GetField(const char* fieldName, AvroValue& value) const;

		// Accessor for the value
		template<class FieldDataType>
		FieldDataType As() const
		{
			assert(false);//, "Not implemented for this type";
			return FieldDataType{};
		}

		const char* AsString() const;
		int AsInt() const;
        int64_t AsInt64() const;
		float AsFloat() const;
		double AsDouble() const;
		bool AsBoolean() const;
        Guid AsGuid() const;
		ArrayView<const uint8_t> AsBytes() const;


		// for array
		size_t GetArraySize() const;
		Result GetArrayItem(int i, AvroValue& value, const char*& outName) const;
        Result NewArrayItem(AvroValue& outValue);

        // for map
        size_t GetFieldCount() const { return GetArraySize(); }
        Result GetFieldByIndex(int i, AvroValue& value, const char*& name) const;

		template<class FieldDataType>
		FieldDataType GetFieldValue(const char* fieldName) const
		{
			SF::AvroValue fieldValue;
			Result res = GetField(fieldName, fieldValue);
			if (!res)
			{
				SFLog(System, Error, "Invalid avro field request. field:{0}", fieldName);
				return FieldDataType{};
			}

			return fieldValue.As<FieldDataType>();
		}

        Result SetValue(const char* Name, bool Value);
        Result SetValue(const char* Name, int Value);
        Result SetValue(const char* Name, int64_t Value);
        Result SetValue(const char* Name, const char* Value);
        Result SetValue(const char* Name, const String& Value);
        Result SetValue(const char* Name, float Value);
        Result SetValue(const char* Name, double Value);
        Result SetValue(const char* Name, const Guid& Value);
        Result SetValue(const char* Name, const Array<const uint8_t>& Value);
        Result SetValue(const char* Name, const Array<uint8_t>& Value);


	private:
		bool m_OwnerOfValue = false;

		uint8_t m_ValueBuffer[2 * sizeof(intptr_t)]{};
		avro_value_t& m_DataValue = *(avro_value_t*)m_ValueBuffer;
	};

	template<> inline const char* AvroValue::As() const { return AsString(); }
    template<> inline String AvroValue::As() const { return AsString(); }
    template<> inline int AvroValue::As() const { return AsInt(); }
    template<> inline int64_t AvroValue::As() const { return AsInt64(); }
    template<> inline float AvroValue::As() const { return AsFloat(); }
	template<> inline double AvroValue::As() const { return AsDouble(); }
	template<> inline bool AvroValue::As() const { return AsBoolean(); }
    template<> inline ArrayView<const uint8_t> AvroValue::As() const { return AsBytes(); }
    template<> inline const ArrayView<const uint8_t> AvroValue::As() const { return AsBytes(); }



	class AvroReader
	{
	public:
		AvroReader()
		{
		}

		AvroReader(const avro_reader_t& reader)
			: m_Handle(reader)
		{
		}

		AvroReader(const SF::Array<char>& binData);
        AvroReader(const SF::Array<const uint8_t>& binData);

		~AvroReader();

		operator avro_reader_t() { return m_Handle; }
		operator avro_reader_t() const { return m_Handle; }

        bool IsAtEnd() const;

        bool ReadBool() { return ReadByte() != 0; }
        uint8_t ReadByte();
        Result ReadBytes(Array<uint8_t>& data);
        int64_t ReadInt64();
        String ReadString();
        Result ReadValue(AvroValue& value);

	private:
		avro_reader_t m_Handle{};
	};


    class AvroWriter
    {
    public:
        AvroWriter()
        {
        }

        AvroWriter(const avro_writer_t& writer)
            : m_Handle(writer)
        {
        }

        AvroWriter(SF::Array<char>& memoryBuffer);
        AvroWriter(SF::Array<uint8_t>& memoryBuffer);

        ~AvroWriter();

        operator avro_writer_t() { return m_Handle; }
        operator avro_writer_t() const { return m_Handle; }

        Result Write(bool value);
        Result WriteByte(uint8_t value);
        Result WriteBytes(const Array<const uint8_t>& data);
        Result WriteInt64(int64_t value);
        Result WriteString(const char* strValue);
        Result WriteString(const String& strValue);
        Result WriteValue(const AvroValue& value);

        // return size of bytes has written to the buffer
        size_t WrittenSize();

        void Flush();

    private:
        avro_writer_t m_Handle{};
    };

}
