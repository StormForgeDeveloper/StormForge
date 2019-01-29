////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2013 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Crc32 calculation based on zlib implementation
//	
//
////////////////////////////////////////////////////////////////////////////////


#include "CoreBasePCH.h"
#include "SFTypedefs.h"
#include "Util/SFUtility.h"
#include "String/SFHasher32.h"




namespace SF {
namespace Util {
	


	///////////////////////////////////////////////////////////////////////////////////////
	//
	//	Crc32 and crypto
	//

	#define CRYPTO_MASK (0x45027602L)

	///////////////////////////////////////////////////////////////////////////////////////
	//
	//	Crc32 and crypto of little endian
	//

	static inline void _Crc32NEncLt4( uint32_t& uiCrc32, uint32_t* &pBuffCur )
	{
		uint32_t oldCrc = uiCrc32;

		uiCrc32 ^= *pBuffCur;
		uiCrc32 = Hasher_Crc32::stm_CRC32Table[3][uiCrc32 & 0xff] ^ Hasher_Crc32::stm_CRC32Table[2][(uiCrc32 >> 8) & 0xff] ^ 
					Hasher_Crc32::stm_CRC32Table[1][(uiCrc32 >> 16) & 0xff] ^ Hasher_Crc32::stm_CRC32Table[0][uiCrc32 >> 24];

		*pBuffCur++ ^= (oldCrc^CRYPTO_MASK);
	}

	static inline void _Crc32NEncLt32( uint32_t& uiCrc32, uint32_t* &pBuffCur )
	{
		_Crc32NEncLt4( uiCrc32, pBuffCur );
		_Crc32NEncLt4( uiCrc32, pBuffCur );
		_Crc32NEncLt4( uiCrc32, pBuffCur );
		_Crc32NEncLt4( uiCrc32, pBuffCur );
		_Crc32NEncLt4( uiCrc32, pBuffCur );
		_Crc32NEncLt4( uiCrc32, pBuffCur );
		_Crc32NEncLt4( uiCrc32, pBuffCur );
		_Crc32NEncLt4( uiCrc32, pBuffCur );
	}


	static uint32_t _Crc32NEncLt( uint32_t uiCrc32, size_t uiLen, uint8_t *pBuff )
	{
		uint32_t crc;
		uint32_t *pBuff4;

		crc = uiCrc32;
		crc = ~crc;

		pBuff4 = (uint32_t*)pBuff;
		while (uiLen >= 32) {
			_Crc32NEncLt32( crc, pBuff4 );
			uiLen -= 32;
		}
		while (uiLen >= 4)
		{
			_Crc32NEncLt4( crc, pBuff4 );
			uiLen -= 4;
		}
		pBuff = (uint8_t*)pBuff4;

		if (uiLen)
		{
			do
			{
				crc = Hasher_Crc32::stm_CRC32Table[0][(crc ^ *pBuff++) & 0xff] ^ (crc >> 8);
			} while (--uiLen);
		}
		crc = ~crc;

		return crc;
	}



	///////////////////////////////////////////////////////////////////////////////////////
	//
	//	Crc32 of big endian
	//


	static inline void _Crc32NEncBig4( uint32_t& uiCrc32, uint32_t* &pBuffCur )
	{
		uint32_t oldCrc = uiCrc32;

		uiCrc32 ^= *pBuffCur;
		uiCrc32 = Hasher_Crc32::stm_CRC32Table[4][uiCrc32 & 0xff] ^ Hasher_Crc32::stm_CRC32Table[5][(uiCrc32 >> 8) & 0xff] ^ 
					Hasher_Crc32::stm_CRC32Table[6][(uiCrc32 >> 16) & 0xff] ^ Hasher_Crc32::stm_CRC32Table[7][uiCrc32 >> 24];

		*pBuffCur++ ^= (oldCrc^CRYPTO_MASK);
	}

	static inline void _Crc32NEncBig32( uint32_t& uiCrc32, uint32_t* &pBuffCur )
	{
		_Crc32NEncBig4( uiCrc32, pBuffCur );
		_Crc32NEncBig4( uiCrc32, pBuffCur );
		_Crc32NEncBig4( uiCrc32, pBuffCur );
		_Crc32NEncBig4( uiCrc32, pBuffCur );
		_Crc32NEncBig4( uiCrc32, pBuffCur );
		_Crc32NEncBig4( uiCrc32, pBuffCur );
		_Crc32NEncBig4( uiCrc32, pBuffCur );
		_Crc32NEncBig4( uiCrc32, pBuffCur );
	}

	// NOTE: This is not tested
	static uint32_t _Crc32NEncBig( uint32_t uiCrc32, size_t uiLen, uint8_t *pBuff )
	{
		uint32_t crc;
		uint32_t *pBuf4;

		crc = Util::SwapByte(uiCrc32);
		crc = ~crc;

		pBuf4 = (uint32_t*)pBuff;
		while (uiLen >= 32)
		{
			_Crc32NEncBig32( crc, pBuf4 );
			uiLen -= 32;
		}
		while (uiLen >= 4)
		{
			_Crc32NEncBig4( crc, pBuf4 );
			uiLen -= 4;
		}
		pBuff = (uint8_t*)pBuf4;

		if (uiLen)
		{
			do 
			{
				crc = Hasher_Crc32::stm_CRC32Table[4][(crc >> 24) ^ *pBuff++] ^ (crc << 8);
			} while (--uiLen);
		}
		crc = ~crc;

		return Util::SwapByte(crc);
	}
	
	// Make crc32 checksum and encrypt
	uint32_t Crc32NEncrypt( size_t uiBuffSize, uint8_t* pBuff )
	{
		if( pBuff == nullptr )
			return 0;

		uint32_t endian = 1;

		if (*((unsigned char *)(&endian)))
			return _Crc32NEncLt(0, uiBuffSize, pBuff);
		else
			return _Crc32NEncBig(0, uiBuffSize, pBuff);
	}


	

	///////////////////////////////////////////////////////////////////////////////////////
	//
	//	Crc32 and crypto of little endian
	//

	static inline void _Crc32NDecLt4( uint32_t& uiCrc32, uint32_t* &pBuffCur )
	{
		*pBuffCur ^= (uiCrc32^CRYPTO_MASK);
		uiCrc32 ^= *pBuffCur++;
		uiCrc32 = Hasher_Crc32::stm_CRC32Table[3][uiCrc32 & 0xff] ^ Hasher_Crc32::stm_CRC32Table[2][(uiCrc32 >> 8) & 0xff] ^ 
					Hasher_Crc32::stm_CRC32Table[1][(uiCrc32 >> 16) & 0xff] ^ Hasher_Crc32::stm_CRC32Table[0][uiCrc32 >> 24];

	}

	static inline void _Crc32NDecLt32( uint32_t& uiCrc32, uint32_t* &pBuffCur )
	{
		_Crc32NDecLt4( uiCrc32, pBuffCur );
		_Crc32NDecLt4( uiCrc32, pBuffCur );
		_Crc32NDecLt4( uiCrc32, pBuffCur );
		_Crc32NDecLt4( uiCrc32, pBuffCur );
		_Crc32NDecLt4( uiCrc32, pBuffCur );
		_Crc32NDecLt4( uiCrc32, pBuffCur );
		_Crc32NDecLt4( uiCrc32, pBuffCur );
		_Crc32NDecLt4( uiCrc32, pBuffCur );
	}


	static uint32_t _Crc32NDecLt( uint32_t uiCrc32, size_t uiLen, uint8_t *pBuff )
	{
		uint32_t crc;
		uint32_t *pBuff4;

		crc = uiCrc32;
		crc = ~crc;

		pBuff4 = (uint32_t*)pBuff;
		while (uiLen >= 32) {
			_Crc32NDecLt32( crc, pBuff4 );
			uiLen -= 32;
		}
		while (uiLen >= 4)
		{
			_Crc32NDecLt4( crc, pBuff4 );
			uiLen -= 4;
		}
		pBuff = (uint8_t*)pBuff4;

		if (uiLen)
		{
			do
			{
				crc = Hasher_Crc32::stm_CRC32Table[0][(crc ^ *pBuff++) & 0xff] ^ (crc >> 8);
				--uiLen;
			} while (uiLen > 0);
		}
		crc = ~crc;

		return crc;
	}



	///////////////////////////////////////////////////////////////////////////////////////
	//
	//	Crc32 of big endian
	//


	static inline void _Crc32NDecBig4( uint32_t& uiCrc32, uint32_t* &pBuffCur )
	{
		*pBuffCur ^= (uiCrc32^CRYPTO_MASK);
		uiCrc32 ^= *pBuffCur++;

		uiCrc32 = Hasher_Crc32::stm_CRC32Table[4][uiCrc32 & 0xff] ^ Hasher_Crc32::stm_CRC32Table[5][(uiCrc32 >> 8) & 0xff] ^ 
					Hasher_Crc32::stm_CRC32Table[6][(uiCrc32 >> 16) & 0xff] ^ Hasher_Crc32::stm_CRC32Table[7][uiCrc32 >> 24];
	}

	static inline void _Crc32NDecBig32( uint32_t& uiCrc32, uint32_t* &pBuffCur )
	{
		_Crc32NDecBig4( uiCrc32, pBuffCur );
		_Crc32NDecBig4( uiCrc32, pBuffCur );
		_Crc32NDecBig4( uiCrc32, pBuffCur );
		_Crc32NDecBig4( uiCrc32, pBuffCur );
		_Crc32NDecBig4( uiCrc32, pBuffCur );
		_Crc32NDecBig4( uiCrc32, pBuffCur );
		_Crc32NDecBig4( uiCrc32, pBuffCur );
		_Crc32NDecBig4( uiCrc32, pBuffCur );
	}

	// NOTE: This is not tested
	static uint32_t _Crc32NDecBig( uint32_t uiCrc32, size_t uiLen, uint8_t *pBuff )
	{
		uint32_t crc;
		uint32_t *pBuf4;

		crc = Util::SwapByte(uiCrc32);
		crc = ~crc;

		pBuf4 = (uint32_t*)pBuff;
		while (uiLen >= 32)
		{
			_Crc32NDecBig32( crc, pBuf4 );
			uiLen -= 32;
		}
		while (uiLen >= 4)
		{
			_Crc32NDecBig4( crc, pBuf4 );
			uiLen -= 4;
		}
		pBuff = (uint8_t*)pBuf4;

		if (uiLen)
		{
			do 
			{
				crc = Hasher_Crc32::stm_CRC32Table[4][(crc >> 24) ^ *pBuff++] ^ (crc << 8);
			} while (--uiLen);
		}
		crc = ~crc;

		return Util::SwapByte(crc);
	}
	

	// Make crc32 checksum and decrypt
	uint32_t Crc32NDecrypt( size_t uiBuffSize, uint8_t* pBuff )
	{
		if( pBuff == nullptr )
			return 0;

		uint32_t endian = 1;

		if (*((unsigned char *)(&endian)))
			return _Crc32NDecLt(0, uiBuffSize, pBuff);
		else
			return _Crc32NDecBig(0, uiBuffSize, pBuff);
	}


}
} // namespace SF

