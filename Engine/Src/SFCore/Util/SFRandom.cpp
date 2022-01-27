////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2016 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : utility
//	
//
////////////////////////////////////////////////////////////////////////////////


#include "SFCorePCH.h"
#include "Util/SFRandom.h"
#include "Util/SFLog.h"







namespace SF {
namespace Util {


	// Global random generator
	RandomGen Random;

	RandomGenLinear RandomLinear(0xFFFFFFFF, (uint)clock());



	////////////////////////////////////////////////////////////////////////////////
	//
	//	Random generator ( Combination Generator )
	//

	constexpr uint RandomGen::NUM_SEED;
	constexpr uint RandomGen::RAND_MAXIMUM;

	// Constructor
	// uiRandMax : max random alue
	// puiSeeds : initial seeds must have NUM_SEED count element, if NULL then initialize by STD rand
	RandomGen::RandomGen(uint *puiSeeds )
		: m_uiCurIdx(0)
	{
		Srand( puiSeeds );
	}

	// Destructor
	RandomGen::~RandomGen()
	{
	}

	// Change initial seed and reinitialize
	// puiSeeds : initial seeds must have NUM_SEED count element
	void RandomGen::Srand( uint *puiSeeds )
	{
		if( puiSeeds )
		{
			for( uint uiSeed = 0; uiSeed < NUM_SEED; uiSeed++ )
				m_uiSeeds[uiSeed] =  puiSeeds[uiSeed];
		}
		else
		{
			for( uint uiSeed = 0; uiSeed < NUM_SEED; uiSeed++ )
				m_uiSeeds[uiSeed] =  (((uint)rand() << 16) | (uint)rand()) % (RAND_MAXIMUM + 1);
		}
	}

	// Generate new random number
	uint RandomGen::Rand()
	{
		auto curIdx = m_uiCurIdx.fetch_add(1, std::memory_order_relaxed) % NUM_SEED;

		uint uiNewRand = (m_uiSeeds[(curIdx - 24) % NUM_SEED] + m_uiSeeds[(curIdx - 55) % NUM_SEED]) % (RAND_MAXIMUM + 1);

		m_uiSeeds[curIdx] = uiNewRand;


		return uiNewRand;
	}




	////////////////////////////////////////////////////////////////////////////////
	//
	//	Linear Random generator ( Linear Generator )
	//


	// Constructor
	// uiRandMax : max random alue
	// uiSeed : initial seed, if 0 then initialize by STD rand
	RandomGenLinear::RandomGenLinear( uint uiRandMax, uint uiSeed )
		:m_uiRandMax(uiRandMax)
	{
		if( m_uiRandMax <= (1<<15) )
		{
			// MS default
			m_uiMul = 214013L;
			m_uiAdd = 2531011L;
			m_uiMod = 65535;
		}
		else if( m_uiRandMax <= (1<<16) )
		{
			m_uiMul = 47486;
			m_uiAdd = 0;
			m_uiMod = 1<<16;
		}
		else //if( m_uiRandMax <= (0x7FFFFFFFL) ) // 32bit maximum
		{
			m_uiMul = 16807;
			m_uiAdd = 0;
			m_uiMod = 0xFFFFFFFFL;
		}

		Srand( uiSeed );
	}

	// Destructor
	RandomGenLinear::~RandomGenLinear()
	{
	}


	// GetCurrentSeedValue;
	uint RandomGenLinear::GetSeed()
	{
		return m_uiSeed;
	}

	// Change initial seed and reinitialize
	// uiSeed : initial seed, if 0 then initialize by STD rand
	void RandomGenLinear::Srand( uint uiSeed )
	{
		if( uiSeed > 0 )
		{
			m_uiSeed =  uiSeed;
		}
		else
		{
			m_uiSeed =  (((uint)rand() << 16) | (uint)rand()) % m_uiRandMax;
		}
	}

	// Generate new random number
	uint RandomGenLinear::Rand()
	{
		m_uiSeed = (m_uiSeed * m_uiMul + m_uiAdd) % m_uiMod;

		return m_uiSeed % m_uiRandMax;
	}





};	// namespace Util
} // namespace SF

