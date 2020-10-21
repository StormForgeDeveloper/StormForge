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
#include "String/SFStrUtil.h"
#include "String/SFStringCrc32.h"
#include "String/SFStringCrc64.h"


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


		template<>
		class hash<sockaddr_in6>
		{
		public:
			typedef sockaddr_in6 KeyType;
			typedef std::hash<uint32_t> StdHash;

			const unsigned MAGIC = 0x9e3779b9;

			size_t operator()(const KeyType& _Keyval) const
			{
				size_t carry = StdHash()(_Keyval.sin6_port) + MAGIC;

				auto& rawAddress = _Keyval.sin6_addr.s6_addr;
				for (uint iAddr = 0; iAddr < countof(rawAddress); iAddr++)
				{
					carry ^= StdHash()((uint32_t)(rawAddress[iAddr])) + MAGIC;
				}

				return carry;
			}
		};

		template<>
		class hash<sockaddr_storage>
		{
		public:
			typedef sockaddr_storage KeyType;
			typedef std::hash<uint32_t> StdHash;

			const unsigned MAGIC = 0x9e3779b9;

			size_t operator()(const KeyType& _Keyval) const
			{
				if (_Keyval.ss_family == AF_INET6)
				{
					auto sockAddr = (sockaddr_in6*)&_Keyval;
					size_t carry = StdHash()(sockAddr->sin6_port) + MAGIC;

					auto& rawAddress = sockAddr->sin6_addr.s6_addr;
					for (uint iAddr = 0; iAddr < countof(rawAddress); iAddr++)
					{
						carry ^= StdHash()((uint32_t)(rawAddress[iAddr])) + MAGIC;
					}

					return carry;
				}
				else
				{
					auto sockAddr = (sockaddr_in*)&_Keyval;
					size_t carry = StdHash()(sockAddr->sin_port) + MAGIC;

					carry ^= StdHash()((uint32_t)(sockAddr->sin_addr.s_addr)) + MAGIC;

					return carry;
				}
			}
		};


		template<>
		class hash<ULONGLONG>
		{
		public:
			typedef ULONGLONG KeyType;
			typedef std::hash<uint32_t> StdHash;

			size_t operator()(const KeyType& _Keyval) const
			{
				size_t carry = StdHash()((uint32_t)(_Keyval >> 32)) + 0x9e3779b9;
				carry ^= StdHash()((uint32_t)_Keyval) + 0x9e3779b9 + (carry << 6) + (carry >> 2);

				return carry;
			}
		};

		template<>
		class hash<const char*>
		{
		public:
			typedef const char* KeyType;

			size_t operator()(const KeyType& _Keyval) const
			{
				size_t Value = 2166136261U;
				const char* pCur = _Keyval;

				if (pCur == nullptr)
					return Value;

				for (; *pCur; pCur++)
				{
					Value = 16777619U * Value ^ (size_t)(*pCur);
				}

				// do not allow 0 for string hash
				if (Value == 0) Value = ~Value;

				return Value;
			}
		};


		template<>
		class hash<StringCrc32>
		{
		public:
			typedef StringCrc32 KeyType;

			size_t operator()(const KeyType& _Keyval) const
			{
				return _Keyval.GetHash();
			}
		};


		template<>
		class hash<StringCrc64>
		{
		public:
			typedef StringCrc64 KeyType;

			size_t operator()(const KeyType& _Keyval) const
			{
				return _Keyval.GetHash();
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


		template<>
		struct equal_to<const char*>
		{
			bool operator()(const char* _Left, const char* _Right) const
			{
				const int iMaxCmp = 8 * 1024;

				return StrUtil::StringCompair(_Left, _Right, iMaxCmp);
			}

		};



} // namespace SF




