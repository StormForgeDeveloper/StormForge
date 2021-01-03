////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2018 StormForge
// 
// Author : KyungKun Ko
//
// Description : AVL tree test
//	
//
////////////////////////////////////////////////////////////////////////////////



#include <gtest/gtest.h>
#include "Thread/SFThread.h"
#include "Memory/SFMemoryManager.h"
#include "String/SFToString.h"
#include "Math/SF3DMath.h"
#include "Util/SFRandom.h"
#include "Util/SFTimeUtil.h"
#include "../SFTestBase.h"


// common setting class
class MathTest : public MyTestBase
{
protected:

	const float EPSILON_HIGH_PRECISION = 0.0001f;
	const float EPSILON_MID_PRECISION = 0.001f;
	const float EPSILON_LOW_PRECISION = 0.2f;
	const float EPSILON_VERY_LOW_PRECISION = 0.6f;

public:

	MathTest()
	{

	}



	const float* RandomVector(bool useW = false)
	{
		static float values[4];
		values[0] = (float)(SF::Util::Random.Rand() % 128) - 64;
		values[1] = (float)(SF::Util::Random.Rand() % 128) - 64;
		values[2] = (float)(SF::Util::Random.Rand() % 128) - 64;
		values[3] = useW ? (float)(SF::Util::Random.Rand() % 128) - 64 : 1;
		return values;
	}


	SF::Matrix4Soft<float> SetRandomTransform(SF::Vector4Soft<float> (&TRS)[3], bool useScale = false, bool useRot = false, bool useTrans = false)
	{
		SF::Matrix4Soft<float> m;
		m.InitIdentity();

		if (useTrans)
		{
			auto randTrans = SF::Vector4Soft<float>(RandomVector());
			TRS[0] = randTrans;
			m.SetTranslation(randTrans);
		}

		if (useRot)
		{
			auto randRot = SF::Vector4Soft<float>(RandomVector());
			randRot.Normalize3();
			randRot.w = (float)(SF::Util::Random.RandF() * SF::C_PI);
			TRS[1] = randRot;
			SF::Matrix4Soft<float> rotMat;
			rotMat.InitRotationMatrix(randRot);
			m *= rotMat;
		}

		if (useScale)
		{
			auto randScale = SF::Vector4Soft<float>(RandomVector());// (SF::Vector4Soft<float>(RandomVector()) - SF::Vector4Soft<float>(64.f, 64.f, 64.f, 1)) * 0.1f;
			SF::Matrix4Soft<float> scaleMat;
			auto absScale = randScale.Abs();
			if (absScale.x < 0.5) randScale.x = 0.5;
			if (absScale.y < 0.5) randScale.y = 0.5;
			if (absScale.z < 0.5) randScale.z = 0.5;
			TRS[2] = randScale;
			scaleMat.InitScaleMatrix(randScale);
			m *= scaleMat;
		}

		return m;
	}


	void CompareQuaternion(const SF::QuaternionSoft<float>& a, const SF::QuaternionSoft<float>& b)
	{
		EXPECT_GE(EPSILON_MID_PRECISION, SF::Math::Abs(a.x - b.x));
		EXPECT_GE(EPSILON_MID_PRECISION, SF::Math::Abs(a.y - b.y));
		EXPECT_GE(EPSILON_MID_PRECISION, SF::Math::Abs(a.z - b.z));
		EXPECT_GE(EPSILON_MID_PRECISION, SF::Math::Abs(a.w - b.w));
	}

	void CompareVector(const SF::Vector4Soft<float>& a, const SF::Vector4Soft<float>& b)
	{
		EXPECT_GE(EPSILON_HIGH_PRECISION, SF::Math::Abs(a.x - b.x));
		EXPECT_GE(EPSILON_HIGH_PRECISION, SF::Math::Abs(a.y - b.y));
		EXPECT_GE(EPSILON_HIGH_PRECISION, SF::Math::Abs(a.z - b.z));
		EXPECT_GE(EPSILON_HIGH_PRECISION, SF::Math::Abs(a.w - b.w));
	}

	void CompareVectorMID(const SF::Vector4Soft<float>& a, const SF::Vector4Soft<float>& b)
	{
		EXPECT_GE(EPSILON_MID_PRECISION, SF::Math::Abs(a.x - b.x));
		EXPECT_GE(EPSILON_MID_PRECISION, SF::Math::Abs(a.y - b.y));
		EXPECT_GE(EPSILON_MID_PRECISION, SF::Math::Abs(a.z - b.z));
		EXPECT_GE(EPSILON_MID_PRECISION, SF::Math::Abs(a.w - b.w));
	}

	void CompareVectorLOW(const SF::Vector4Soft<float>& a, const SF::Vector4Soft<float>& b)
	{
		EXPECT_GE(EPSILON_LOW_PRECISION, SF::Math::Abs(a.x - b.x));
		EXPECT_GE(EPSILON_LOW_PRECISION, SF::Math::Abs(a.y - b.y));
		EXPECT_GE(EPSILON_LOW_PRECISION, SF::Math::Abs(a.z - b.z));
		EXPECT_GE(EPSILON_LOW_PRECISION, SF::Math::Abs(a.w - b.w));
	}

	void CompareMatrix(const SF::Matrix4Soft<float>& softMat, const SF::Matrix4Soft<float>& sseMat)
	{
		for (int iEle = 0; iEle < 16; iEle++)
		{
			EXPECT_GE(EPSILON_MID_PRECISION, SF::Math::Abs(softMat.Elements[iEle] - sseMat.Elements[iEle]));
		}
	}


#ifdef SF_SIMD_SSE
	void CompareQuaternion(const SF::QuaternionSoft<float>& a, const SF::QuaternionSSE& b)
	{
		EXPECT_GE(EPSILON_MID_PRECISION, SF::Math::Abs(a.x - b.x));
		EXPECT_GE(EPSILON_MID_PRECISION, SF::Math::Abs(a.y - b.y));
		EXPECT_GE(EPSILON_MID_PRECISION, SF::Math::Abs(a.z - b.z));
		EXPECT_GE(EPSILON_MID_PRECISION, SF::Math::Abs(a.w - b.w));
	}

	void CompareQuaternion(const SF::QuaternionSSE& a, const SF::QuaternionSoft<float>& b)
	{
		EXPECT_GE(EPSILON_MID_PRECISION, SF::Math::Abs(a.x - b.x));
		EXPECT_GE(EPSILON_MID_PRECISION, SF::Math::Abs(a.y - b.y));
		EXPECT_GE(EPSILON_MID_PRECISION, SF::Math::Abs(a.z - b.z));
		EXPECT_GE(EPSILON_MID_PRECISION, SF::Math::Abs(a.w - b.w));
	}

	void CompareQuaternion(const SF::QuaternionSSE& a, const SF::QuaternionSSE& b)
	{
		EXPECT_GE(EPSILON_MID_PRECISION, SF::Math::Abs(a.x - b.x));
		EXPECT_GE(EPSILON_MID_PRECISION, SF::Math::Abs(a.y - b.y));
		EXPECT_GE(EPSILON_MID_PRECISION, SF::Math::Abs(a.z - b.z));
		EXPECT_GE(EPSILON_MID_PRECISION, SF::Math::Abs(a.w - b.w));
	}

	void CompareVector(const SF::Vector4Soft<float>& a, const SF::Vector4SSE& b)
	{
		EXPECT_GE(EPSILON_HIGH_PRECISION, SF::Math::Abs(a.x - b.x));
		EXPECT_GE(EPSILON_HIGH_PRECISION, SF::Math::Abs(a.y - b.y));
		EXPECT_GE(EPSILON_HIGH_PRECISION, SF::Math::Abs(a.z - b.z));
		EXPECT_GE(EPSILON_HIGH_PRECISION, SF::Math::Abs(a.w - b.w));
	}

	void CompareVectorMID(const SF::Vector4Soft<float>& a, const SF::Vector4SSE& b)
	{
		EXPECT_GE(EPSILON_MID_PRECISION, SF::Math::Abs(a.x - b.x));
		EXPECT_GE(EPSILON_MID_PRECISION, SF::Math::Abs(a.y - b.y));
		EXPECT_GE(EPSILON_MID_PRECISION, SF::Math::Abs(a.z - b.z));
		EXPECT_GE(EPSILON_MID_PRECISION, SF::Math::Abs(a.w - b.w));
	}

	void CompareVectorLOW(const SF::Vector4Soft<float>& a, const SF::Vector4SSE& b)
	{
		EXPECT_GE(EPSILON_LOW_PRECISION, SF::Math::Abs(a.x - b.x));
		EXPECT_GE(EPSILON_LOW_PRECISION, SF::Math::Abs(a.y - b.y));
		EXPECT_GE(EPSILON_LOW_PRECISION, SF::Math::Abs(a.z - b.z));
		EXPECT_GE(EPSILON_LOW_PRECISION, SF::Math::Abs(a.w - b.w));
	}


	void CompareMatrix(const SF::Matrix4Soft<float>& softMat, const SF::Matrix4SSE& sseMat)
	{
		for (int iEle = 0; iEle < 16; iEle++)
		{
			EXPECT_GE(EPSILON_MID_PRECISION, SF::Math::Abs(softMat.Elements[iEle] - sseMat.Elements[iEle]));
		}
	}

	void CompareMatrix(const SF::Matrix4SSE& softMat, const SF::Matrix4Soft<float>& sseMat)
	{
		for (int iEle = 0; iEle < 16; iEle++)
		{
			EXPECT_GE(EPSILON_MID_PRECISION, SF::Math::Abs(softMat.Elements[iEle] - sseMat.Elements[iEle]));
		}
	}

	void CompareMatrix(const SF::Matrix4SSE& softMat, const SF::Matrix4SSE& sseMat)
	{
		for (int iEle = 0; iEle < 16; iEle++)
		{
			EXPECT_GE(EPSILON_MID_PRECISION, SF::Math::Abs(softMat.Elements[iEle] - sseMat.Elements[iEle]));
		}
	}

	SF::Matrix4SSE SetRandomTransform(SF::Vector4SSE(&TRS)[3], bool useScale = false, bool useRot = false, bool useTrans = false)
	{
		SF::Matrix4SSE m;
		m.InitIdentity();

		if (useTrans)
		{
			auto randTrans = SF::Vector4SSE(RandomVector());
			TRS[0] = randTrans;
			m.SetTranslation(randTrans);
		}

		if (useRot)
		{
			auto randRot = SF::Vector4SSE(RandomVector());
			randRot.Normalize3();
			randRot.w = (float)(SF::Util::Random.RandF() * SF::C_PI);
			TRS[1] = randRot;
			SF::Matrix4SSE rotMat;
			rotMat.InitRotationMatrix(randRot);
			m *= rotMat;
		}

		if (useScale)
		{
			auto randScale = (SF::Vector4SSE(RandomVector()) - SF::Vector4SSE(64.f, 64.f, 64.f, 1)) * 0.1f;
			SF::Matrix4SSE scaleMat;
			auto absScale = randScale.Abs();
			if (absScale.x < 0.5) randScale.x = 0.5;
			if (absScale.y < 0.5) randScale.y = 0.5;
			if (absScale.z < 0.5) randScale.z = 0.5;
			TRS[2] = randScale;
			scaleMat.InitScaleMatrix(randScale);
			m *= scaleMat;
		}

		return m;
	}


	void CompareVector(const SF::Vector4SSE& a, const SF::Vector4SSE& b)
	{
		EXPECT_GE(EPSILON_MID_PRECISION, SF::Math::Abs(a.x - b.x));
		EXPECT_GE(EPSILON_MID_PRECISION, SF::Math::Abs(a.y - b.y));
		EXPECT_GE(EPSILON_MID_PRECISION, SF::Math::Abs(a.z - b.z));
		EXPECT_GE(EPSILON_MID_PRECISION, SF::Math::Abs(a.w - b.w));
	}

#endif

	SF::QuaternionSoft<float> RandomQuaternionSoft()
	{
		auto randRot = SF::Vector4Soft<float>(RandomVector());
		randRot.Normalize3();
		randRot.w = (float)(SF::Util::Random.RandF() * SF::C_PI);
		return SF::QuaternionSoft<float>(randRot);
	}

	SF::QuaternionSSE RandomQuaternionSSE()
	{
		auto randRot = SF::Vector4SSE(RandomVector());
		randRot.Normalize3();
		randRot.w = (float)(SF::Util::Random.RandF() * SF::C_PI);
		return SF::QuaternionSSE(randRot);
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

