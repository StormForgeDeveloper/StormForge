////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2017 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Enumerator helper
//	
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "SFTypedefs.h"
#include "Types/SFEngineTypedefs.h"
#include "Util/SFStringCrc64.h"
#include "Util/SFString.h"
#include "Container/SFCircularPageQueue.h"
#include "Task/SFTask.h"

#include "Zookeeper/SFZookeeper.h"


typedef struct _xmlNode xmlNode;


namespace SF
{


	template<class EnumType>
	class Enum
	{
	public:
		typedef const char* constCharPtr;

	public:

		constexpr Enum() {}

		const char* GetName() const { return nullptr; }

		size_t GetNumberOfValues() const;
		const char *const* GetValueNames() const;

		const char* GetValueName(EnumType value) const { return nullptr; }
		StringCrc64 GetValueNameCrc(EnumType value) const { return nullptr; }
		EnumType GetValue(const char*) const;
		EnumType GetValue(StringCrc64 valueName) const;
	};




	template<>
	class Enum<DBClusterType>
	{
	public:

		constexpr Enum() {}

		const char* GetName() const;

		size_t GetNumberOfValues() const;
		const char *const* GetValueNames() const;

		const char* GetValueName(DBClusterType value) const;

		StringCrc64 GetValueNameCrc(DBClusterType value) const;

		DBClusterType GetValue(const char*) const;

		DBClusterType GetValue(StringCrc64 valueName) const;
	};



	extern template class Enum<DBClusterType>;


	template<>
	class Enum<ClusterID>
	{
	public:

		constexpr Enum() {}

		const char* GetName() const;

		size_t GetNumberOfValues() const;
		const char *const* GetValueNames() const;

		const char* GetValueName(ClusterID value) const;

		StringCrc64 GetValueNameCrc(ClusterID value) const;

		ClusterID GetValue(const char*) const;

		ClusterID GetValue(StringCrc64 valueName) const;
	};



	extern template class Enum<ClusterID>;

}

