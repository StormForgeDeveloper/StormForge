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


#pragma once

#include "SFTypedefs.h"
#include "Thread/SFSynchronization.h"



namespace SF {
namespace Util {

	////////////////////////////////////////////////////////////////////////////////
	//
	//	Random generator ( Combination Generator )
	//

	class RandomGen
	{
	public:
		// Constants definitions
		static constexpr uint NUM_SEED = 1024;
		static constexpr uint RAND_MAXIMUM = 65535;

	private:
		// Seeds for generator
		uint m_uiSeeds[NUM_SEED];
		std::atomic<uint> m_uiCurIdx;
		//uint m_uiRandMax;

	public:
		// Constructor
		// uiRandMax : max random alue
		// puiSeeds : initial seeds must have NUM_SEED count element, if NULL then initialize by STD rand
		RandomGen( uint *puiSeeds = NULL );

		// Destructor
		~RandomGen();

		// Get rand max
		uint RandMax() const { return RAND_MAXIMUM; }

		// Change initial seed and reinitialize
		// puiSeeds : initial seeds must have NUM_SEED count element
		void Srand( uint *puiSeeds );

		// Generate new random number
		uint Rand();

		// Generate new random number
		uint Rand( uint iMax );

		// Generate new random number
		INT Rand( INT iMin, INT iMax );

		// Generate new random number
		float RandF() { return (float)Rand() / (float)RandMax(); }
	};


	////////////////////////////////////////////////////////////////////////////////
	//
	//	Simple Random generator ( linear Generator )
	//

	class RandomGenLinear
	{
	public:

	private:
		// Seeds for generator
		uint m_uiSeed;
		uint m_uiMul, m_uiAdd, m_uiMod;
		uint m_uiRandMax;

	public:
		// Constructor
		// uiRandMax : max random alue
		// uiSeed : initial seed, if 0 then initialize by STD rand
		RandomGenLinear( uint uiRandMax, uint uiSeed = 0 );

		// Destructor
		~RandomGenLinear();

		// Get rand max
		uint RandMax() const { return m_uiRandMax; }

		// GetCurrentSeedValue;
		uint GetSeed();

		// Change initial seed and reinitialize
		// uiSeed : initial seed, if 0 then initialize by STD rand
		void Srand( uint uiSeed );

		// Generate new random number
		uint Rand();

		// Generate new random number
		uint Rand( uint iMax );

		// Generate new random number
		INT Rand( INT iMin, INT iMax );

		// Generate new random number
		float RandF() { return (float)Rand() / (float)RandMax(); }
	};

	// Global random generator
	extern RandomGen Random;



	
#include "SFRandom.inl"


}; // namespace Util
} // namespace SF


