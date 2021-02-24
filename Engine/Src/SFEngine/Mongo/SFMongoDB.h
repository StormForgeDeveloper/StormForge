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

namespace SF
{
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
		mongoc_collection_t* m_Collection{};

	public:

		MongoDB(IHeap& heap);
		virtual ~MongoDB();

		IHeap& GetHeap() { return m_Heap; }

		void Clear();

		virtual void Dispose() override;

		virtual Result Initialize(const String& serverAddress);

		// set database and collection to use
		Result SetDatabase(const char* database, const char* collection);

		// row manipulation
		Result Insert(const bson_t* row);
		Result AddOrupdate(const bson_t* row);

		// TODO: supporting bulk operations
	};

}
#endif

