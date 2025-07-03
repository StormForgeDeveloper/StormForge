////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) The Braves
// 
// Author : KyungKun Ko
//
// Description : indexing helpers
//
////////////////////////////////////////////////////////////////////////////////


#pragma once


#include "SFTypedefs.h"
#include "Container/SFIndexing.h"
#include "Util/SFStrUtil.h"
#include "Util/SFStringCrc32.h"
#include "Util/SFStringCrc64.h"

namespace SF {



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



		///////////////////////////////////////////////////////////////////////////
		//
		//	Hasher
		//



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




