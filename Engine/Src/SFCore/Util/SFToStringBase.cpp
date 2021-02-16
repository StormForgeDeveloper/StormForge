////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2013 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Base type ToString implementation
//	
//
////////////////////////////////////////////////////////////////////////////////


#include "SFCorePCH.h"
#include "SFTypedefs.h"
#include "SFAssert.h"
#include "ResultCode/SFResultCodeSystem.h"
#include "Util/SFStrUtil.h"
#include "Util/SFToStringBase.h"


namespace SF {


	//////////////////////////////////////////////////////////////////////////////////
	//
	//	help operations
	//

	#define _AppendCharReturn( buf, length, charToAppend ) {*buf++ = charToAppend;	length--;	if(length <=0 ) return ResultCode::OUT_OF_MEMORY;}

	
	////////////////////////////////////////////////////////////////////////////////
	//
	//	String manipulation helper
	//

	// Itoa customized version
	template< class Type >
	Result _MyIToA(
				Type val,
				char* &buf,
				INT& length,
				unsigned radix,
				bool bIsNeg,
				int iDigit = -1 // fixed digit count
				)
	{
		Assert( val >= 0 );

		// Validation
		if( buf == NULL || length <= 0
			|| radix < 2 || radix > 36 )
		{
			return ResultCode::INVALID_ARG;
		}


		if ( bIsNeg )
		{
			// negative, so output '-' and negate
			*buf++ = '-';
			length--;
		}

		if( length <= 0 )
			return ResultCode::OUT_OF_MEMORY;


		char DigitBuffer[128];
		int iFilled = 0;
		do {
			// get next digit
			unsigned digval = unsigned(val % radix);
			val = (Type)( val/ radix );

			// convert to ascii and store
			if (digval > 9)
				DigitBuffer[iFilled] = (char) (digval - 10 + 'A');  // a letter
			else
				DigitBuffer[iFilled] = (char) (digval + '0');       // a digit

			iFilled++;
		} while (val > 0 && length > 0 && iFilled < (INT)countof(DigitBuffer));

		if( iFilled >= (INT)countof(DigitBuffer) ) // temp buffer is full
			return StrUtil::StringCopyEx( buf, length, "(Err:TooBigNumber)" );

		// digit limit
		if( iDigit > 0 )
		{
			if( iDigit >= iFilled )
			{
				for( ; iDigit > iFilled; iDigit-- )
				{
					_AppendCharReturn( buf, length, '0' );
				}
			}
			else
			{
				iDigit = 0;
			}
		}
		else
		{
			iDigit = iFilled;
		}

		// reverse copy to dest buffer
		for( ; iFilled > 0 && length > 0 && iDigit > 0; iDigit-- )
		{
			iFilled--;
			_AppendCharReturn( buf, length, DigitBuffer[iFilled] );
		}


		*buf = '\0';            // terminate string;

		return ResultCode::SUCCESS;
	}



	// 
	Result _IToA(ToStringContext& context, int8_t val)
	{
		bool bIsNeg = false;
		if( val < 0 )
		{
			val = int8_t (-val);
			bIsNeg = true;
		}

		return _MyIToA( val, context.StringBuffer, context.StringBufferLength, context.Radix, bIsNeg, context.MaxDigit);
	}

	Result _IToA(ToStringContext& context, uint8_t val)
	{
		bool bIsNeg = false;
		return _MyIToA( val, context.StringBuffer, context.StringBufferLength, context.Radix, bIsNeg, context.MaxDigit);
	}

	Result _IToA(ToStringContext& context, int16_t val)
	{
		bool bIsNeg = false;
		if( val < 0 )
		{
			val = int16_t (-val);
			bIsNeg = true;
		}

		return _MyIToA( val, context.StringBuffer, context.StringBufferLength, context.Radix, bIsNeg, context.MaxDigit);
	}

	Result _IToA(ToStringContext& context, uint16_t val)
	{
		bool bIsNeg = false;
		return _MyIToA( val, context.StringBuffer, context.StringBufferLength, context.Radix, bIsNeg, context.MaxDigit);
	}

	Result _IToA(ToStringContext& context, int32_t val)
	{
		bool bIsNeg = false;
		if(val < 0 && context.Radix == 10) // use plus sign only for base 10 description
		{
			val = -val;
			bIsNeg = true;
		}

		return _MyIToA( (uint32_t)val, context.StringBuffer, context.StringBufferLength, context.Radix, bIsNeg, context.MaxDigit);
	}

	Result _IToA(ToStringContext& context, uint32_t val)
	{
		bool bIsNeg = false;
		return _MyIToA( val, context.StringBuffer, context.StringBufferLength, context.Radix, bIsNeg, context.MaxDigit);
	}

	Result _IToA(ToStringContext& context, int64_t val)
	{
		bool bIsNeg = false;
		if( val < 0 )
		{
			val = -val;
			bIsNeg = true;
		}

		return _MyIToA( val, context.StringBuffer, context.StringBufferLength, context.Radix, bIsNeg, context.MaxDigit);
	}

	Result _IToA(ToStringContext& context, uint64_t val)
	{
		bool bIsNeg = false;
		return _MyIToA( val, context.StringBuffer, context.StringBufferLength, context.Radix, bIsNeg, context.MaxDigit);
	}


	Result _FToA(ToStringContext& context, double val)
	{
		auto resultLen = snprintf(context.StringBuffer, context.StringBufferLength, "%.4f", val);
		if (resultLen > context.StringBufferLength) resultLen = context.StringBufferLength; // truncated, use original string
		context.StringBuffer += resultLen;
		context.StringBufferLength -= resultLen;

		// Null terminate
		if(context.StringBufferLength > 0 )
			*context.StringBuffer = '\0';
		else
			*(context.StringBuffer -1) = '\0';

		return ResultCode::SUCCESS;
	}


}	// namespace SF


