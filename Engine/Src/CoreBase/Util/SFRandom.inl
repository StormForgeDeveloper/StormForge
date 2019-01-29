////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2016 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Utility library
//	
//
////////////////////////////////////////////////////////////////////////////////




////////////////////////////////////////////////////////////////////////////////
//
//	Random utility functions
//

// Generate new random number
inline uint RandomGen::Rand( uint iMax )
{
	return Rand()%(iMax+1);
}

// Generate new random number
inline INT RandomGen::Rand( INT iMin, INT iMax )
{
	if( iMax <= iMin )
		return iMin;
	return iMin + (INT)( Rand()%(iMax - iMin + 1) );
}



// Generate new random number
inline uint RandomGenLinear::Rand( uint iMax )
{
	return Rand()%iMax;
}

// Generate new random number
inline INT RandomGenLinear::Rand( INT iMin, INT iMax )
{
	if( iMax <= iMin )
		return iMin;
	return iMin + (INT)( Rand()%(iMax-iMin) );
}


