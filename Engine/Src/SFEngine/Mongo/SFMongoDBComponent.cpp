////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) StormForge
// 
// Author : KyungKun Ko
//
// Description : MongoDB component
//	
//
////////////////////////////////////////////////////////////////////////////////


#include "ServerSystemPCH.h"
#include "Util/SFStringCrc32.h"
#include "SFEngine.h"
#include "Mongo/SFMongoDB.h"
#include "Mongo/SFMongoDBComponent.h"

#include <mongoc/mongoc.h>


namespace SF
{

	MongoDBComponent::MongoDBComponent()
		: LibraryComponent(TypeName)
		, m_Heap(GetSystemHeap())
	{
	}

	MongoDBComponent::~MongoDBComponent()
	{
	}


	// Initialize component
	Result MongoDBComponent::InitializeComponent()
	{
		auto result = LibraryComponent::InitializeComponent();
		if (!result)
			return result;

#ifdef USE_MONGODB
		mongoc_init();
#endif

		return result;
	}

	// Terminate component
	void MongoDBComponent::DeinitializeComponent()
	{
#ifdef USE_MONGODB
		mongoc_cleanup();
#endif

		LibraryComponent::DeinitializeComponent();
	}

}


