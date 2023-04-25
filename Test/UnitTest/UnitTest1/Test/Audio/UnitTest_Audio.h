////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2018 StormForge
// 
// Author : KyungKun Ko
//
// Description : Memory
//	
//
////////////////////////////////////////////////////////////////////////////////



#include <gtest/gtest.h>
#include "Multithread/SFThread.h"
#include "MemoryManager/SFMemoryManager.h"
#include "Util/SFToString.h"
#include "../SFTestBase.h"
#include "Variable/SFVariable.h"
#include "Variable/SFVariableTable.h"
#include "Variable/SFVariableStack.h"


// common setting class
class AudioTest : public MyTestBase
{
protected:


public:

    AudioTest()
	{

	}


    void GenerateSinWave(SF::Array<float>& data, double magnitude, uint totalSamples, uint waveCount)
    {
        double sampleCycle = double(totalSamples) / waveCount;
        for (uint i = 0; i < totalSamples; i++)
        {
            double integral;
            double fraction = modf(double(i) / sampleCycle, &integral);
            data[i] += (float)(sin(fraction * 2.0 * M_PI) * magnitude);
        }
    }

	// Remember that SetUp() is run immediately before a test starts.
	virtual void SetUp()
	{
		MyTestBase::SetUp();

	}

	// TearDown() is invoked immediately after a test finishes.  Here we
	virtual void TearDown()
	{
		MyTestBase::TearDown();

	}
};

