////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Utility library
//	
//
////////////////////////////////////////////////////////////////////////////////

#include "SFTypedefs.h"
#include "Container/SFArray.h"
#include "json/json.h"

#pragma once


namespace SF {

    class Guid;

namespace Util {

	////////////////////////////////////////////////////////////////////////////////
	//
	//	Generic utility macros
	//

	#define BR_MAKEMERSION(verMajor,verMinor)	(((uint32_t)(verMajor)<<16) | ((uint32_t)(verMajor)))


	////////////////////////////////////////////////////////////////////////////////
	//
	//	Generic utility functions
	//
	// Swap byte of data
	inline uint16_t SwapByte( uint16_t uiData );
	inline uint32_t SwapByte( uint32_t uiData );
	inline uint64_t SwapByte( uint64_t uiData );


	// Make crc64 checksum
	uint64_t Crc64(uint64_t uiCrc64, size_t uiBuffSize, const uint8_t* pBuff);

	// Make crc32 checksum and encrypt
	uint32_t Crc32NEncrypt( size_t uiBuffSize, uint8_t* pBuff );

	// Make crc32 checksum and decrypt
	uint32_t Crc32NDecrypt( size_t uiBuffSize, uint8_t* pBuff );


	Result HEXEncode(size_t srcSize, const uint8_t* bytes_to_encode, Array<uint8_t>& destBuffer, uint8_t dummyChar = '\0', bool lowercase = false);
	Result HEXDecode(size_t srcSize, const uint8_t* bytes_to_decode, Array<uint8_t>& destBuffer, uint8_t dummyChar = '=');

	// Base 64 encode/decode
	Result Base64Encode(size_t srcSize, const uint8_t* bytes_to_encode, Array<uint8_t> &destBuffer, uint8_t dummyChar = '=');
	Result Base64Decode(size_t srcSize, const uint8_t* bytes_to_decode, Array<uint8_t> &destBuffer, uint8_t dummyChar = '=');

	Result Base64URLEncode(size_t srcSize, const uint8_t* bytes_to_encode, Array<uint8_t> &destBuffer, uint8_t dummyChar = '=');
	Result Base64URLDecode(size_t srcSize, const uint8_t* bytes_to_decode, Array<uint8_t> &destBuffer, uint8_t dummyChar = '=');

	// SHA 256 hashing
	Result SHA256Hash(size_t srcSize, const uint8_t* bytes_to_encode, Array<uint8_t> &destBuffer);

	// Find min bit can embrace the number
	uint32_t FindMinBitShift(uint32_t number);

	// Make power of 2 value from given number, will bigger then input
	uint NearPowerOf2( uint32_t uiNumber );

	// Service Name
	const char* GetServiceName();
	void SetServiceName(const char* serviceName);

    const Guid& GetTitleUID();
    void SetTitleUID(const Guid& titleUID);

    const char* GetTitleEnv();
    void SetTitleEnv(const char* titleEnv);

	// Module Name
	const char* GetModuleName();

	// Module Path
	const char* GetModulePath();

	void SetModulePath(const char* customModulePath, const char* moduleName);


	// Machine unique Id
	const char* GetMachineUniqueId(); // machine unique id. probably mac address
	void SetMachineUniqueId(const char* machineId); // you can override machine unique id


	// Array duplication
	template<class DupType>
	Result ArrayDup(IHeap& memoryManager, DupType* &pDest, INT iSrcCount, const DupType* pSrc );

	// MemCopy Data to binary
	template< size_t szDstSize, class DataType >
	Result MemCpy( uint8_t (&Dest)[szDstSize], const DataType& Src );

	// MemCopy Data From binary
	template< size_t szDstSize, class DataType >
	Result MemCpy( DataType& Dest, const uint8_t (&Src)[szDstSize] );


	template<class ArrayType>
	Result SafeDeleteArray( ArrayType* &pArray );

	template<class ValueType>
	Result SafeDelete( ValueType* &pObj );

    // Load whole file into memory
    Result LoadWholeFile(const char* path, Array<uint8_t>& outData);


	// Peek key from console
	//Result PeekKey( int &inputKey, NativeHandle hConsole = INVALID_NATIVE_HANDLE_VALUE);
    Result LoadJsonFile(const char* jsonPath, Json::Value& outValue);

#include "SFUtility.inl"

} // namespace Util
} // namespace SF


