////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2016 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Hash 32
//
////////////////////////////////////////////////////////////////////////////////

#pragma  once

#include <stdint.h>
#include <unordered_map>


namespace SF {

	// Hasher class for crc32
	class Hasher_Crc32
	{
	public:

		static constexpr uint32_t stm_CRC32Table[8][256] =
		{
			#include "SFHashCRC32Table.inl"
		};



		// internal interfaces
	private:

		constexpr uint32_t GetStringLength(const char* str) const
		{
			return *str ? 1 + GetStringLength(str + 1) : 0;
		}

		constexpr uint32_t MakeNonZero(uint32_t hash) const
		{
			return hash == 0 ? 1 : hash;
		}

		template<class byteType>
		constexpr uint32_t GetUint32(const byteType * data) const
		{
			return (uint32_t(uint8_t(data[0])))
				| ((uint32_t(uint8_t(data[1]))) << 8)
				| ((uint32_t(uint8_t(data[2]))) << 16)
				| ((uint32_t(uint8_t(data[3]))) << 24);
		}


		///////////////////////////////////////////////////////////////////////////////////////
		//
		//	Crc32 of little endian
		//

		constexpr uint32_t Crc32LtTranslate(uint32_t crc) const
		{
			return stm_CRC32Table[3][crc & 0xff] ^ stm_CRC32Table[2][(crc >> 8) & 0xff] ^
				stm_CRC32Table[1][(crc >> 16) & 0xff] ^ stm_CRC32Table[0][crc >> 24];
		}

		template<class byteType>
		constexpr uint32_t Crc32Lt4(uint32_t crc, const byteType* pBuffCur) const
		{
			return Crc32LtTranslate(crc ^ GetUint32(pBuffCur));
		}

		template<class byteType>
		constexpr uint32_t Crc32Lt32(uint32_t crc, const byteType* pBuffCur) const
		{
			return Crc32Lt4(
				Crc32Lt4(
					Crc32Lt4(
						Crc32Lt4(
							Crc32Lt4(
								Crc32Lt4(
									Crc32Lt4(
										Crc32Lt4(crc, pBuffCur + 0),
										pBuffCur + (4 * 1)),
									pBuffCur + (4 * 2)),
								pBuffCur + (4 * 3)),
							pBuffCur + (4 * 4)),
						pBuffCur + (4 * 5)),
					pBuffCur + (4 * 6)),
				pBuffCur + (4 * 7));
		}

		template<class byteType>
		constexpr uint32_t Crc32ByteRecursive(uint32_t crc, const byteType* pBuff, size_t length) const
		{
			return length <= 0 ? crc : Crc32ByteRecursive(stm_CRC32Table[0][(crc ^ (*pBuff)) & 0xff] ^ (crc >> 8), pBuff + 1, length - 1);
		}

		template<class byteType>
		constexpr uint32_t Crc32Lt32Recursive(uint32_t crc, const byteType* pBuff, size_t lengthIn32) const
		{
			return lengthIn32 <= 0 ? crc : Crc32Lt32Recursive(Crc32Lt32(crc, pBuff), pBuff + (4 * 8), lengthIn32 - 1);
		}

		template<class byteType>
		constexpr uint32_t Crc32Lt(uint32_t crc, const byteType *pBuff, size_t length) const
		{
			return ~Crc32ByteRecursive(Crc32Lt32Recursive(~crc, pBuff, length / 32), pBuff + (length & (~31)), length & 31);
		}


		///////////////////////////////////////////////////////////////////////////////////////
		//
		//	Crc32 of little endian
		//

		inline void _Crc32Lt4(uint32_t& crc, const uint32_t* &pBuffCur) const
		{
			crc ^= *pBuffCur++;
			crc = stm_CRC32Table[3][crc & 0xff] ^ stm_CRC32Table[2][(crc >> 8) & 0xff] ^
				stm_CRC32Table[1][(crc >> 16) & 0xff] ^ stm_CRC32Table[0][crc >> 24];
		}

		inline void _Crc32Lt32(uint32_t& uiCrc32, const uint32_t* &pBuffCur) const
		{
			_Crc32Lt4(uiCrc32, pBuffCur);
			_Crc32Lt4(uiCrc32, pBuffCur);
			_Crc32Lt4(uiCrc32, pBuffCur);
			_Crc32Lt4(uiCrc32, pBuffCur);
			_Crc32Lt4(uiCrc32, pBuffCur);
			_Crc32Lt4(uiCrc32, pBuffCur);
			_Crc32Lt4(uiCrc32, pBuffCur);
			_Crc32Lt4(uiCrc32, pBuffCur);
		}


		uint32_t _Crc32Lt(uint32_t crc, const uint8_t *pBuff, size_t length) const
		{
			const uint32_t *pBuff4;

			crc = ~crc;
			// process untile 32bit boundary
			while (length && ((ptrdiff_t)pBuff & 3))
			{
				crc = stm_CRC32Table[0][(crc ^ *pBuff++) & 0xff] ^ (crc >> 8);
				length--;
			}

			pBuff4 = (const uint32_t*)pBuff;
			while (length >= 32) {
				_Crc32Lt32(crc, pBuff4);
				length -= 32;
			}
			while (length >= 4)
			{
				_Crc32Lt4(crc, pBuff4);
				length -= 4;
			}
			pBuff = (const uint8_t*)pBuff4;

			while (length)
			{
				crc = stm_CRC32Table[0][(crc ^ *pBuff++) & 0xff] ^ (crc >> 8);
				length--;
			}
			crc = ~crc;

			return crc;
		}


		///////////////////////////////////////////////////////////////////////////////////////
		//
		//	Crc32 of big endian
		//


		inline void _Crc32Big4(uint32_t& uiCrc32, const uint32_t* &pBuffCur) const
		{
			uiCrc32 ^= *pBuffCur++;
			uiCrc32 = stm_CRC32Table[4][uiCrc32 & 0xff] ^ stm_CRC32Table[5][(uiCrc32 >> 8) & 0xff] ^ stm_CRC32Table[6][(uiCrc32 >> 16) & 0xff] ^ stm_CRC32Table[7][uiCrc32 >> 24];
		}

		inline void _Crc32Big32(uint32_t& uiCrc32, const uint32_t* &pBuffCur) const
		{
			_Crc32Big4(uiCrc32, pBuffCur);
			_Crc32Big4(uiCrc32, pBuffCur);
			_Crc32Big4(uiCrc32, pBuffCur);
			_Crc32Big4(uiCrc32, pBuffCur);
			_Crc32Big4(uiCrc32, pBuffCur);
			_Crc32Big4(uiCrc32, pBuffCur);
			_Crc32Big4(uiCrc32, pBuffCur);
			_Crc32Big4(uiCrc32, pBuffCur);
		}

		uint32_t SwapByte(uint32_t uiData) const
		{
			return (uiData << 24) | ((uiData & 0xFF00) << 16) | (uiData >> 24) | ((uiData >> 16) & 0xFF00);
		}

		// NOTE: This is not tested as I don't have any big endian machine
		uint32_t _Crc32Big(uint32_t crc, const uint8_t *pBuff, size_t uiLen) const
		{
			const uint32_t *pBuf4;

			crc = SwapByte(crc);
			crc = ~crc;

			// process untile 32bit boundary
			while (uiLen && ((ptrdiff_t)pBuff & 3))
			{
				crc = stm_CRC32Table[4][(crc >> 24) ^ *pBuff++] ^ (crc << 8);
				uiLen--;
			}

			pBuf4 = (const uint32_t*)pBuff;
			while (uiLen >= 32)
			{
				_Crc32Big32(crc, pBuf4);
				uiLen -= 32;
			}
			while (uiLen >= 4)
			{
				_Crc32Big4(crc, pBuf4);
				uiLen -= 4;
			}
			pBuff = (const uint8_t*)pBuf4;

			for (; uiLen > 0; uiLen--)
			{
				crc = stm_CRC32Table[4][(crc >> 24) ^ *pBuff++] ^ (crc << 8);
			}
			crc = ~crc;

			return SwapByte(crc);
		}


	public:

		constexpr Hasher_Crc32()
		{
		}

		template<class byteType>
		constexpr uint32_t Hash(uint32_t crc, const byteType* data, size_t length) const
		{
			return data == nullptr
				? 0
				: MakeNonZero(Crc32Lt(crc, data, length));
		}

		constexpr uint32_t Hash(const char* text) const
		{
			return text == nullptr ? 0 : Hash<char>(0, text, GetStringLength(text));
		}



		uint32_t Crc32(uint32_t crc, const uint8_t* pBuf, size_t length) const
		{
			if (pBuf == nullptr)
				return 0;

			uint32_t endian = 1;

			if (*((unsigned char *)(&endian)))
				return MakeNonZero(_Crc32Lt(crc, pBuf, length));
			else
				return MakeNonZero(_Crc32Big(crc, pBuf, length));

		}

	};





	inline uint32_t Hash32(const char* s) {
		return s == nullptr ? 0 : Hasher_Crc32().Crc32(0, (uint8_t*)s, strlen(s));
	}

	constexpr uint32_t operator "" _crc(const char* s, size_t sz) {
		return Hasher_Crc32().Hash(s);
	}

	constexpr uint32_t operator "" _hash32(const char* s, size_t sz) {
		return Hasher_Crc32().Hash(s);
	}

}

