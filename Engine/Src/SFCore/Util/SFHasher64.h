////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2016 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Hash 64
//
////////////////////////////////////////////////////////////////////////////////

#pragma  once

#include <stdint.h>
#include <unordered_map>


// MSVC compiler generates warning 4307 with constexpr functions which can't be avoided
#ifdef _MSC_VER
#pragma warning(disable : 4307)
#endif

namespace SF {

	class Hasher_Murmur64
	{
	private:

		static constexpr uint64_t m = 0xc6a4a7935bd1e995ull;
		static constexpr int r = 47;


		// internal interfaces
	private:
		constexpr uint64_t GetStringLength(const char* str) const
		{
			return *str ? 1 + GetStringLength(str + 1) : 0;
		}

		constexpr uint64_t InitHash(uint64_t hash, uint64_t length) const
		{
			return hash ^ (length * m);
		}

		template<class byteType>
		constexpr uint64_t RecursiveHashChar(uint64_t hash, const byteType* data, int offset, int remain) const
		{
			//switch (len & 7)
			//{
			//case 7: h ^= uint64_t(data2[6]) << 48;
			//case 6: h ^= uint64_t(data2[5]) << 40;
			//case 5: h ^= uint64_t(data2[4]) << 32;
			//case 4: h ^= uint64_t(data2[3]) << 24;
			//case 3: h ^= uint64_t(data2[2]) << 16;
			//case 2: h ^= uint64_t(data2[1]) << 8;
			//case 1: h ^= uint64_t(data2[0]);
			//	h *= m;
			//};

			return remain <= 0
				? hash
				: RecursiveHashCharSub(hash ^ (uint64_t(uint8_t(data[offset])) << (8 * offset)), data, offset + 1, remain - 1) * m;
		}

		template<class byteType>
		constexpr uint64_t RecursiveHashCharSub(uint64_t hash, const byteType* data, int offset, int remain) const
		{
			return remain <= 0
				? hash
				: RecursiveHashCharSub(hash ^ (uint64_t(uint8_t(data[offset])) << (8 * offset)), data, offset + 1, remain - 1);
		}

		template<class byteType>
		constexpr uint64_t GetUint64(const byteType * data) const
		{
			return (uint64_t(uint8_t(data[0])))
				| ((uint64_t(uint8_t(data[1]))) << 8)
				| ((uint64_t(uint8_t(data[2]))) << 16)
				| ((uint64_t(uint8_t(data[3]))) << 24)
				| ((uint64_t(uint8_t(data[4]))) << 32)
				| ((uint64_t(uint8_t(data[5]))) << 40)
				| ((uint64_t(uint8_t(data[6]))) << 48)
				| ((uint64_t(uint8_t(data[7]))) << 56);
		}

		template<class byteType>
		constexpr uint64_t HashUint64(uint64_t hash, const byteType * data) const
		{
			//uint64_t k = *data++;

			//k *= m;
			//k ^= k >> r;
			//k *= m;

			//h ^= k;
			//h *= m;

			return (hash ^ (Rotate(GetUint64(data) * m) * m)) * m;
		}

		template<class byteType>
		constexpr uint64_t RecursiveHash64x1(uint64_t hash, const byteType * data, int numElement) const
		{
			//uint64_t k = *data++;

			//k *= m;
			//k ^= k >> r;
			//k *= m;

			//h ^= k;
			//h *= m;

			return numElement < 1
				? hash
				: RecursiveHash64x1(HashUint64(hash, data), data + 8, numElement - 1);
		}

		template<class byteType>
		constexpr uint64_t RecursiveHash64x4(uint64_t hash, const byteType * data, int numElement) const
		{
			return numElement < 1
				? hash
				: RecursiveHash64x4(HashUint64(HashUint64(HashUint64(HashUint64(hash, data), data + 8), data + (2 * 8)), data + (3 * 8)), data + (4 * 8), numElement - 1);
		}

		template<class byteType>
		constexpr uint64_t RecursiveHash64Root(uint64_t hash, const byteType * data, int numElement) const
		{
			//uint64_t k = *data++;

			//k *= m;
			//k ^= k >> r;
			//k *= m;

			//h ^= k;
			//h *= m;

			return numElement < 1
				? hash
				: RecursiveHash64x1(RecursiveHash64x4(hash, data, numElement >> 2), data + ((numElement >> 2) * (4 * 8)), numElement % 4);
		}

		template<class byteType>
		constexpr uint64_t HashBody(uint64_t hash, const byteType* data, uint64_t length) const
		{
			return RecursiveHashChar(
				RecursiveHash64Root(hash, data, (int)length / 8),
				data + (length / 8) * 8,
				0, length % 8
			);
		}

		constexpr uint64_t Rotate(uint64_t hash) const
		{
			//h ^= h >> r;
			return hash ^ (hash >> r);
		}

		constexpr uint64_t MakeNonZero(uint64_t hash) const
		{
			return hash == 0 ? 1 : hash;
		}

	public:

		constexpr Hasher_Murmur64()
		{

		}

		constexpr uint64_t Hash(const char* text) const
		{
			return text == nullptr ? 0 : Hash(0, text, GetStringLength(text));
		}

		constexpr uint64_t Hash(uint64_t hash, const char* data, uint64_t length) const
		{
			//h ^= h >> r;
			//h *= m;
			//h ^= h >> r;

			return data[0] == '\0'
				? 1
				: MakeNonZero(Rotate(Rotate(HashBody(InitHash(hash, length), data, length)) * m));
		}

		constexpr uint64_t Hash(uint64_t hash, const uint8_t* data, uint64_t length) const
		{
			//h ^= h >> r;
			//h *= m;
			//h ^= h >> r;

			return data[0] == '\0'
				? 1
				: MakeNonZero(Rotate(Rotate(HashBody(InitHash(hash, length), data, length)) * m));
		}


		// original murmur hash implementation
		// https://sites.google.com/site/murmurhash/
		uint64_t MurmurHash64A(const void * key, int len, unsigned int seed) const
		{
			//const uint64_t m = 0xc6a4a7935bd1e995;
			//const int r = 47;

			uint64_t h = seed ^ (len * m);

			const uint64_t * data = (const uint64_t *)key;
			const uint64_t * end = data + (len / 8);


			uint32_t endian = 1;

			// Little endian
			if (*((unsigned char *)(&endian)))
			{
				while (data != end)
				{
					uint64_t k = *data++;

					k *= m;
					k ^= k >> r;
					k *= m;

					h ^= k;
					h *= m;
				}
			}
			else // big endian
			{
				while (data != end)
				{
					uint64_t k = GetUint64(data);
					data++;

					k *= m;
					k ^= k >> r;
					k *= m;

					h ^= k;
					h *= m;
				}
			}


			const unsigned char * data2 = (const unsigned char*)data;

			switch (len & 7)
			{
			case 7: h ^= uint64_t(data2[6]) << 48; [[fallthrough]];
			case 6: h ^= uint64_t(data2[5]) << 40; [[fallthrough]];
			case 5: h ^= uint64_t(data2[4]) << 32; [[fallthrough]];
			case 4: h ^= uint64_t(data2[3]) << 24; [[fallthrough]];
			case 3: h ^= uint64_t(data2[2]) << 16; [[fallthrough]];
			case 2: h ^= uint64_t(data2[1]) << 8; [[fallthrough]];
			case 1: h ^= uint64_t(data2[0]);
				h *= m;
			};

			h ^= h >> r;
			h *= m;
			h ^= h >> r;

			return MakeNonZero(h);
		}


	};


	inline uint64_t Hash64(const char* s) {
		return s == nullptr ? 0 : Hasher_Murmur64().MurmurHash64A(s, (int)strlen(s), 0);
	}


	constexpr uint64_t operator "" _hash64(const char* s, size_t sz) {
		return Hasher_Murmur64().Hash(0, s, sz);
	}

	//constexpr uint64_t operator "" _crc(const char* s, size_t sz) {
	//	return Hasher_Murmur64().Hash(s);
	//}


}

