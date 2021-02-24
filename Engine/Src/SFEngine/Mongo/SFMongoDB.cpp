////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c)  Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : MongoDB
//	
//
////////////////////////////////////////////////////////////////////////////////

#include "SFEnginePCH.h"

#include "Mongo/SFMongoDB.h"
#include "Util/SFStringFormat.h"


#ifdef USE_MONGODB

#include <bson/bson.h>
#include <mongoc/mongoc.h>



namespace SF
{

	////////////////////////////////////////////////////////////////////////////////////////////////
	//
	//	class MongoDB
	//
	MongoDB::MongoDB(IHeap& heap)
		: m_Heap(heap)
	{

	}

	MongoDB::~MongoDB()
	{

	}

	void MongoDB::Clear()
	{
		if (m_Database)
		{
			mongoc_database_destroy(m_Database);
			m_Database = nullptr;
		}

		if (m_Collection)
		{
			mongoc_collection_destroy(m_Collection);
			m_Collection = nullptr;
		}

		if (m_Uri)
		{
			mongoc_uri_destroy(m_Uri);
			m_Uri = nullptr;
		}

		if (m_Client)
		{
			mongoc_client_destroy(m_Client);
			m_Client = nullptr;
		}
	}

	void MongoDB::Dispose()
	{
		Clear();
		super::Dispose();
	}

	Result MongoDB::Initialize(const String& serverAddress)
	{
		bson_error_t error;

		Clear();

		mongoc_uri_t* uri = mongoc_uri_new_with_error(serverAddress, &error);
		if (!uri)
		{
			SFLog(Net, Error, "MongoDB: failed to parse URI:{0}, error:{1}", serverAddress, error.message);
			return ResultCode::IO_INVALID_ADDRESS;
		}

		m_Client = mongoc_client_new_from_uri(uri);
		if (!m_Client)
		{
			SFLog(Net, Error, "MongoDB: failed to create client:{0}", serverAddress);
			return ResultCode::OUT_OF_MEMORY;
		}

		mongoc_client_set_appname(m_Client, Util::GetModuleName());

		return ResultCode::SUCCESS;
	}


	Result MongoDB::SetDatabase(const char* database, const char* collection)
	{
		if (m_Database)
		{
			mongoc_database_destroy(m_Database);
			m_Database = nullptr;
		}

		if (m_Collection)
		{
			mongoc_collection_destroy(m_Collection);
			m_Collection = nullptr;
		}

		m_Database = mongoc_client_get_database(m_Client, database);
		m_Collection = mongoc_client_get_collection(m_Client, database, collection);

		return m_Database != nullptr && m_Collection != nullptr ? ResultCode::SUCCESS : ResultCode::FAIL;
	}

	Result MongoDB::Insert(const bson_t* row)
	{
		if (m_Collection == nullptr)
			return ResultCode::NOT_INITIALIZED;

		if (row == nullptr)
			return ResultCode::INVALID_ARG;

		// We don't want auto generated _id
		if (!bson_has_field(row, "_id"))
			return ResultCode::INVALID_FORMAT;

		bson_error_t error;
		auto ret = mongoc_collection_insert_one(m_Collection, row, nullptr, nullptr, &error);
		if (!ret)
		{
			SFLog(Net, Error, "MongoDB:Insert failed error:{0}", error.message);
		}

		return ResultCode::SUCCESS;
	}

	Result MongoDB::AddOrupdate(const bson_t* row)
	{
		if (m_Collection == nullptr)
			return ResultCode::NOT_INITIALIZED;

		if (row == nullptr)
			return ResultCode::INVALID_ARG;

		// We don't want auto generated _id
		if (!bson_has_field(row, "_id"))
			return ResultCode::INVALID_FORMAT;

		bson_error_t error;
		auto ret = mongoc_collection_update(m_Collection, MONGOC_UPDATE_UPSERT, row, nullptr, nullptr, &error);
		if (!ret)
		{
			SFLog(Net, Error, "MongoDB:Insert failed error:{0}", error.message);
		}

		return ResultCode::SUCCESS;
	}


}

#endif
