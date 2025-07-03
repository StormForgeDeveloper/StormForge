////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2016 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : indexing helpers
//
////////////////////////////////////////////////////////////////////////////////


#pragma once


#include "SFTypedefs.h"


namespace SF {


		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//
		//	Indexing Functor
		//

		// Indexing member data
		template<typename ClassType, typename MemDataType, MemDataType ClassType::*pfMemData>
		class MapItemConverter
		{
		public:
			typedef MemDataType Type;

			Type* operator ()(const ClassType& clsObj) const
			{
				return (Type*)&(clsObj.*pfMemData);
			}

			Type* operator ()(const ClassType* clsObj) const
			{
				return (Type*)&(clsObj->*(pfMemData));
			}

			ClassType* operator ()(const MemDataType* memData) const
			{
				if (memData == nullptr) return nullptr;
				return (ClassType*)((int64_t)memData - (int64_t)&(((ClassType *)0)->*pfMemData));
			}
		};


		// bypassing Self value
		template<typename ClassType, typename IndexType = ClassType>
		class Self
		{
		public:
			typedef IndexType Type;

			IndexType operator ()(const ClassType& clsObj) const
			{
				return (Type)clsObj;
			}

			IndexType operator ()(const ClassType* clsObj) const
			{
				return (Type)(*clsObj);
			}
		};


		// Combine two 32bit value to 64bit value
		template<typename ClassType, typename Index1, typename Index2>
		class Composit64
		{
		public:
			typedef ULONGLONG Type;

			ULONGLONG operator ()(const ClassType& clsObj) const
			{
				ULONGLONG ulIndex = Index1()(clsObj);
				ulIndex = (ulIndex << 32) | (ULONGLONG)(Index2()(clsObj));
				return ulIndex;
			}

			ULONGLONG operator ()(const ClassType* clsObj) const
			{
				ULONGLONG ulIndex = Index1()(clsObj);
				ulIndex = (ulIndex << 32) | (ULONGLONG)(Index2()(clsObj));
				return ulIndex;
			}
		};

		// Combine two 32bit value to 64bit value
		inline ULONGLONG Combine64(uint32_t ulIdx, uint32_t ulIdx2)
		{
			ULONGLONG ulIndex = ulIdx;
			ulIndex = (ulIndex << 32) | (ULONGLONG)(ulIdx2);
			return ulIndex;
		}




		///////////////////////////////////////////////////////////////////////////
		//
		//	Hash specialize
		//

		// default hash to std hash
		template< class KeyType >
		class hash
		{
		public:
			size_t operator()(const KeyType& _Keyval) const
			{
				return std::hash<KeyType>()(_Keyval);
			}
		};


		///////////////////////////////////////////////////////////////////////////
		//
		//	Hasher
		//

		// std hash functor wrapper
		template< typename IndexType >
		class Hasher
		{
		private:

		public:
			size_t operator()(const IndexType& _Keyval) const
			{
				return std::hash<IndexType>()(_Keyval);
			}
		};


		// functor for operator==
		template< typename IndexType >
		struct equal_to
		{
			bool operator()(const IndexType& _Left, const IndexType& _Right) const
			{
				return IndexType(_Left) == IndexType(_Right);
			}

			bool operator()(const IndexType* _Left, const IndexType* _Right) const
			{
				return IndexType(_Left) == IndexType(_Right);
			}
		};


} // namespace SF




