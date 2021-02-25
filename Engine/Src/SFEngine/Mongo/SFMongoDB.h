////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : MongoDB warper
//	
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "SFTypedefs.h"

#define USE_MONGODB

#ifdef USE_MONGODB
#include "Util/SFStringCrc32.h"
#include "Util/SFString.h"
#include "Object/SFSharedObject.h"


typedef struct _mongoc_client_t mongoc_client_t;
typedef struct _mongoc_uri_t mongoc_uri_t;
typedef struct _mongoc_database_t mongoc_database_t;
typedef struct _mongoc_collection_t mongoc_collection_t;
typedef struct _bson_t bson_t;
typedef struct _mongoc_cursor_t mongoc_cursor_t;

namespace SF
{


	// SF deleter
	struct BsonDeleter {
		constexpr BsonDeleter() noexcept = default;
		void operator()(bson_t* _Ptr) const noexcept;
	};
	using BsonUniquePtr = std::unique_ptr<bson_t, BsonDeleter>;

	struct MongoCursorDeleter {
		constexpr MongoCursorDeleter() noexcept = default;
		void operator()(mongoc_cursor_t* _Ptr) const noexcept;
	};
	using MongoCursorUniquePtr = std::unique_ptr<mongoc_cursor_t, MongoCursorDeleter>;


	////////////////////////////////////////////////////////////////////////////////////////////
	//
	//  class MongoDBCursor
	//

	class MongoDBCursor
	{
	public:
		MongoDBCursor(mongoc_cursor_t* _Ptr = nullptr);
		~MongoDBCursor();

		void SetCursorRaw(mongoc_cursor_t* _Ptr);

		operator bool() const { return m_Cursor != nullptr; }

		const bson_t* Next();

	private:

		MongoCursorUniquePtr m_Cursor;
	};


	////////////////////////////////////////////////////////////////////////////////////////////
	//
	//  class MongoDB
	//

	class MongoDB : public SharedObject
	{
	public:

		using super = SharedObject;

		IHeap& m_Heap;

		mongoc_uri_t* m_Uri{};
		mongoc_client_t* m_Client{};
		mongoc_database_t* m_Database{};

		BsonUniquePtr m_AddOrUpdateOpt;

	public:

		MongoDB(IHeap& heap);
		virtual ~MongoDB();

		IHeap& GetHeap() { return m_Heap; }

		void Clear();

		virtual void Dispose() override;

		virtual Result Initialize(const String& serverAddress);

		mongoc_client_t* GetClient() const { return m_Client; }
	};


	////////////////////////////////////////////////////////////////////////////////////////////
	//
	//  class MongoDBCollection
	//

	class MongoDBCollection : public SharedObject
	{
	public:

		using super = SharedObject;

		IHeap& m_Heap;

		SharedPointerT<MongoDB> m_DB;
		mongoc_database_t* m_DataBase{};
		mongoc_collection_t* m_Collection{};

		BsonUniquePtr m_AddOrUpdateOpt;

	public:

		MongoDBCollection(IHeap& heap);
		virtual ~MongoDBCollection();

		IHeap& GetHeap() { return m_Heap; }

		void Clear();

		virtual void Dispose() override;

		virtual Result Initialize(MongoDB* pDB, const char* database, const char* collection);

		// row manipulation
		Result Insert(const bson_t* row);
		Result AddOrUpdate(uint64_t id, const bson_t* row);

		Result Find(const bson_t* matchPattern, MongoDBCursor& outCursor);
		Result Aggregate(const bson_t* aggregatePipeline, MongoDBCursor& outCursor);


		Result Remove(uint64_t id);
		// TODO: supporting bulk operations
	};

}
#endif

