// UnitTestMath3DVector.cpp : Defines the entry point for the console application.
//

#include "UnitTest1PCH.h"
#include <gtest/gtest.h>
#include "Container/SFDualSortedMap.h"
#include "../UnitTest_Math.h"


using ::testing::EmptyTestEventListener;
using ::testing::InitGoogleTest;
using ::testing::Test;
using ::testing::TestCase;
using ::testing::TestEventListeners;
using ::testing::TestInfo;
using ::testing::TestPartResult;
using ::testing::UnitTest;
using namespace ::SF;



TEST_F(MathTest, Soft_Matrix4_Simple)
{
	Vector4Soft<float> a(4, 5, 6, 1), b(2, 2, 2, 2);
	Matrix4Soft<float> m;
	Vector4Soft<float> SRT[3];

	const struct {
		bool UseScale = false;
		bool UseRot = false;
		bool UseTrans = false;
	} TestSetting[] = 
	{
		{},
		{true, false, false},
		{false, true, false},
		{false, false, true},
		{true, false, true},
		{true, true, false},
		{false, true, true},
		{true, true, true},
	};

	Matrix4Soft<float> m2(
		1, 2, 3, 4,
		5, 6, 7, 8,
		9, 10, 11, 12,
		13, 14, 15, 16
	);

	
	auto randScale = SF::Vector4Soft<float>(RandomVector()) - 64.f;
	SF::Matrix4Soft<float> scaleMat;
	scaleMat.InitScaleMatrix(randScale);

	EXPECT_GE(EPSILON_MID_PRECISION, Math::Abs(scaleMat.a00 - randScale.x));
	EXPECT_GE(EPSILON_MID_PRECISION, Math::Abs(scaleMat.a01));
	EXPECT_GE(EPSILON_MID_PRECISION, Math::Abs(scaleMat.a02));
	EXPECT_GE(EPSILON_MID_PRECISION, Math::Abs(scaleMat.a03));
	EXPECT_GE(EPSILON_MID_PRECISION, Math::Abs(scaleMat.a11 - randScale.y));
	EXPECT_GE(EPSILON_MID_PRECISION, Math::Abs(scaleMat.a10));
	EXPECT_GE(EPSILON_MID_PRECISION, Math::Abs(scaleMat.a12));
	EXPECT_GE(EPSILON_MID_PRECISION, Math::Abs(scaleMat.a13));
	EXPECT_GE(EPSILON_MID_PRECISION, Math::Abs(scaleMat.a22 - randScale.z));
	EXPECT_GE(EPSILON_MID_PRECISION, Math::Abs(scaleMat.a20));
	EXPECT_GE(EPSILON_MID_PRECISION, Math::Abs(scaleMat.a21));
	EXPECT_GE(EPSILON_MID_PRECISION, Math::Abs(scaleMat.a23));
	EXPECT_GE(EPSILON_MID_PRECISION, Math::Abs(scaleMat.a33 - 1));
	EXPECT_GE(EPSILON_MID_PRECISION, Math::Abs(scaleMat.a30));
	EXPECT_GE(EPSILON_MID_PRECISION, Math::Abs(scaleMat.a31));
	EXPECT_GE(EPSILON_MID_PRECISION, Math::Abs(scaleMat.a32));

	auto randTrans = SF::Vector4Soft<float>(RandomVector());
	SF::Matrix4Soft<float> transMat;
	transMat.InitTranslationMatrix(randTrans);
	EXPECT_GE(EPSILON_MID_PRECISION, Math::Abs(transMat.a00-1));
	EXPECT_GE(EPSILON_MID_PRECISION, Math::Abs(transMat.a01));
	EXPECT_GE(EPSILON_MID_PRECISION, Math::Abs(transMat.a02));
	EXPECT_GE(EPSILON_MID_PRECISION, Math::Abs(transMat.a03 - randTrans.x));
	EXPECT_GE(EPSILON_MID_PRECISION, Math::Abs(transMat.a11-1));
	EXPECT_GE(EPSILON_MID_PRECISION, Math::Abs(transMat.a10));
	EXPECT_GE(EPSILON_MID_PRECISION, Math::Abs(transMat.a12));
	EXPECT_GE(EPSILON_MID_PRECISION, Math::Abs(transMat.a13 - randTrans.y));
	EXPECT_GE(EPSILON_MID_PRECISION, Math::Abs(transMat.a22-1));
	EXPECT_GE(EPSILON_MID_PRECISION, Math::Abs(transMat.a20));
	EXPECT_GE(EPSILON_MID_PRECISION, Math::Abs(transMat.a21));
	EXPECT_GE(EPSILON_MID_PRECISION, Math::Abs(transMat.a23 - randTrans.z));
	EXPECT_GE(EPSILON_MID_PRECISION, Math::Abs(transMat.a33 - 1));
	EXPECT_GE(EPSILON_MID_PRECISION, Math::Abs(transMat.a30));
	EXPECT_GE(EPSILON_MID_PRECISION, Math::Abs(transMat.a31));
	EXPECT_GE(EPSILON_MID_PRECISION, Math::Abs(transMat.a32));


	auto xAxis = SF::Vector4Soft<float>(1, 0, 0, 1);
	auto nxAxis = SF::Vector4Soft<float>(-1, 0, 0, 1);
	auto yAxis = SF::Vector4Soft<float>(0, 1, 0, 1);
	auto nyAxis = SF::Vector4Soft<float>(0, -1, 0, 1);
	auto zAxis = SF::Vector4Soft<float>(0, 0, 1, 1);
	auto nzAxis = SF::Vector4Soft<float>(0, 0, -1, 1);
	SF::Matrix4Soft<float> rotMat;

	auto randRot = SF::Vector4Soft<float>(1, 0, 0, C_HALF_PI);
	rotMat.InitRotationMatrix(randRot);
	auto resVec = rotMat * xAxis;
	CompareVector(resVec, xAxis);
	resVec = rotMat * yAxis;
	CompareVector(resVec, zAxis);
	resVec = rotMat * zAxis;
	CompareVector(resVec, nyAxis);

	randRot = SF::Vector4Soft<float>(-1, 0, 0, C_HALF_PI);
	rotMat.InitRotationMatrix(randRot);
	resVec = rotMat * xAxis;
	CompareVector(resVec, xAxis);
	resVec = rotMat * yAxis;
	CompareVector(resVec, nzAxis);
	resVec = rotMat * zAxis;
	CompareVector(resVec, yAxis);

	randRot = SF::Vector4Soft<float>(0, 1, 0, C_HALF_PI);
	rotMat.InitRotationMatrix(randRot);
	resVec = rotMat * xAxis;
	CompareVector(resVec, nzAxis);
	resVec = rotMat * yAxis;
	CompareVector(resVec, yAxis);
	resVec = rotMat * zAxis;
	CompareVector(resVec, xAxis);

	randRot = SF::Vector4Soft<float>(0, -1, 0, C_HALF_PI);
	rotMat.InitRotationMatrix(randRot);
	resVec = rotMat * xAxis;
	CompareVector(resVec, zAxis);
	resVec = rotMat * yAxis;
	CompareVector(resVec, yAxis);
	resVec = rotMat * zAxis;
	CompareVector(resVec, nxAxis);

	randRot = SF::Vector4Soft<float>(0, 0, 1, C_HALF_PI);
	rotMat.InitRotationMatrix(randRot);
	resVec = rotMat * xAxis;
	CompareVector(resVec, yAxis);
	resVec = rotMat * yAxis;
	CompareVector(resVec, nxAxis);
	resVec = rotMat * zAxis;
	CompareVector(resVec, zAxis);

	randRot = SF::Vector4Soft<float>(0, 0, 1, C_HALF_PI);
	rotMat.InitRotationMatrix(randRot);
	resVec = rotMat * xAxis;
	CompareVector(resVec, yAxis);
	resVec = rotMat * yAxis;
	CompareVector(resVec, nxAxis);
	resVec = rotMat * zAxis;
	CompareVector(resVec, zAxis);


	rotMat.InitRotationMatrix(zAxis, xAxis);
	resVec = rotMat * xAxis;
	CompareVector(resVec, nzAxis);
	resVec = rotMat * yAxis;
	CompareVector(resVec, yAxis);
	resVec = rotMat * zAxis;
	CompareVector(resVec, xAxis);


	for (auto itTestSetting : TestSetting)
	{
		m = SetRandomTransform(SRT, itTestSetting.UseScale, itTestSetting.UseRot, itTestSetting.UseTrans);

		auto sum = m + m2;
		for (int iEle = 0; iEle < 16; iEle++)
		{
			float c = m.Elements[iEle] + m2.Elements[iEle];
			EXPECT_GE(EPSILON_MID_PRECISION, Math::Abs(c - sum.Elements[iEle]));
		}

		auto sub = m - m2;
		for (int iEle = 0; iEle < 16; iEle++)
		{
			float c = m.Elements[iEle] - m2.Elements[iEle];
			EXPECT_GE(EPSILON_MID_PRECISION, Math::Abs(c - sub.Elements[iEle]));
		}


		auto divs = m / 10;
		for (int iEle = 0; iEle < 16; iEle++)
		{
			float c = m.Elements[iEle] / 10.f;
			EXPECT_GE(EPSILON_MID_PRECISION, Math::Abs(c - divs.Elements[iEle]));
		}


		auto muls = m * 10;
		for (int iEle = 0; iEle < 16; iEle++)
		{
			float c = m.Elements[iEle] * 10.f;
			EXPECT_GE(EPSILON_MID_PRECISION, Math::Abs(c - muls.Elements[iEle]));
		}

		auto mulv = m * a;
		{
			float x = m.a00 * a.x + m.a01 * a.y + m.a02 * a.z + m.a03 * a.w;
			float y = m.a10 * a.x + m.a11 * a.y + m.a12 * a.z + m.a13 * a.w;
			float z = m.a20 * a.x + m.a21 * a.y + m.a22 * a.z + m.a23 * a.w;
			float w = m.a30 * a.x + m.a31 * a.y + m.a32 * a.z + m.a33 * a.w;

			EXPECT_GE(EPSILON_MID_PRECISION, Math::Abs(x - mulv.x));
			EXPECT_GE(EPSILON_MID_PRECISION, Math::Abs(y - mulv.y));
			EXPECT_GE(EPSILON_MID_PRECISION, Math::Abs(z - mulv.z));
			EXPECT_GE(EPSILON_MID_PRECISION, Math::Abs(w - mulv.w));
		}

		auto mulv2 = a * m;
		{
			float x = m.a00 * a.x + m.a10 * a.y + m.a20 * a.z + m.a30 * a.w;
			float y = m.a01 * a.x + m.a11 * a.y + m.a21 * a.z + m.a31 * a.w;
			float z = m.a02 * a.x + m.a12 * a.y + m.a22 * a.z + m.a32 * a.w;
			float w = m.a03 * a.x + m.a13 * a.y + m.a23 * a.z + m.a33 * a.w;

			EXPECT_GE(EPSILON_MID_PRECISION, Math::Abs(x - mulv2.x));
			EXPECT_GE(EPSILON_MID_PRECISION, Math::Abs(y - mulv2.y));
			EXPECT_GE(EPSILON_MID_PRECISION, Math::Abs(z - mulv2.z));
			EXPECT_GE(EPSILON_MID_PRECISION, Math::Abs(w - mulv2.w));
		}
	}

}



TEST_F(MathTest, Soft_Matrix4_Invert)
{

	const struct {
		bool UseScale = false;
		bool UseRot = false;
		bool UseTrans = false;
	} TestSetting[] =
	{
		{true, true, false},
		{false, false, true},
		{true, false, false},
		{false, true, false},
		{},
		{true, false, true},
		{false, true, true},
		{true, true, true},
	};

	Matrix4Soft<float> m2(
		1, 2, 3, 4,
		5, 6, 7, 8,
		9, 10, 11, 12,
		13, 14, 15, 16
	);

	Vector4Soft<float> TRS[3];

	Matrix4Soft<float> m;
	for (auto itTestSetting : TestSetting)
	{
		m = SetRandomTransform(TRS, itTestSetting.UseScale, itTestSetting.UseRot, itTestSetting.UseTrans);

		auto invMat = m.GetInverse();
		auto inv2Mat = invMat.GetInverse();
		auto invMul = invMat * m;
		auto invMul2 = m * invMat;
		for (int iEle = 0; iEle < 16; iEle++)
		{
			EXPECT_GE(EPSILON_LOW_PRECISION, Math::Abs(m.Elements[iEle] - inv2Mat.Elements[iEle]));
		}

		Matrix4Soft<float> identity;
		identity.InitIdentity();
		for (int iEle = 0; iEle < 16; iEle++)
		{
			EXPECT_GE(EPSILON_MID_PRECISION, Math::Abs(identity.Elements[iEle] - invMul.Elements[iEle]));
		}

		for (int iEle = 0; iEle < 16; iEle++)
		{
			EXPECT_GE(EPSILON_MID_PRECISION, Math::Abs(identity.Elements[iEle] - invMul2.Elements[iEle]));
		}
	}


	for (auto itTestSetting : TestSetting)
	{
		//if (itTestSetting.UseScale)
		//	continue;

		m = SetRandomTransform(TRS, itTestSetting.UseScale, itTestSetting.UseRot, itTestSetting.UseTrans);

		auto invMat = m.GetInverseTransform();
		auto invMat2 = m.GetInverse();
		auto inv2Mat = invMat.GetInverseTransform();
		auto inv2Mat2 = invMat2.GetInverse();
		auto invMul = invMat * m;
		auto invMul2 = invMat2 * m;


		for (int iEle = 0; iEle < 16; iEle++)
		{
			EXPECT_GE(EPSILON_MID_PRECISION, Math::Abs(invMat.Elements[iEle] - invMat2.Elements[iEle]));
		}

		// 
		if (!itTestSetting.UseScale)
		{
			for (int iEle = 0; iEle < 16; iEle++)
			{
				EXPECT_GE(EPSILON_MID_PRECISION, Math::Abs(inv2Mat.Elements[iEle] - inv2Mat2.Elements[iEle]));
			}


			for (int iEle = 0; iEle < 16; iEle++)
			{
				EXPECT_GE(EPSILON_MID_PRECISION, Math::Abs(m.Elements[iEle] - inv2Mat.Elements[iEle]));
			}
		}

		Matrix4Soft<float> identity;
		identity.InitIdentity();
		for (int iEle = 0; iEle < 16; iEle++)
		{
			EXPECT_GE(EPSILON_MID_PRECISION, Math::Abs(identity.Elements[iEle] - invMul.Elements[iEle]));
		}

		for (int iEle = 0; iEle < 16; iEle++)
		{
			EXPECT_GE(EPSILON_MID_PRECISION, Math::Abs(identity.Elements[iEle] - invMul2.Elements[iEle]));
		}
	}


	for (auto itTestSetting : TestSetting)
	{
		if (itTestSetting.UseScale)
			continue;

		m = SetRandomTransform(TRS, itTestSetting.UseScale, itTestSetting.UseRot, itTestSetting.UseTrans);

		auto invMat = m.GetInverseTransformNoScale();
		auto invMat2 = m.GetInverse();
		auto inv2Mat = invMat.GetInverseTransformNoScale();
		auto inv2Mat2 = invMat2.GetInverse();
		auto invMul = invMat * m;
		auto invMul2 = invMat2 * m;


		for (int iEle = 0; iEle < 16; iEle++)
		{
			EXPECT_GE(EPSILON_MID_PRECISION, Math::Abs(invMat.Elements[iEle] - invMat2.Elements[iEle]));
		}

		for (int iEle = 0; iEle < 16; iEle++)
		{
			EXPECT_GE(EPSILON_HIGH_PRECISION, Math::Abs(inv2Mat.Elements[iEle] - inv2Mat2.Elements[iEle]));
		}


		for (int iEle = 0; iEle < 16; iEle++)
		{
			EXPECT_GE(EPSILON_MID_PRECISION, Math::Abs(m.Elements[iEle] - inv2Mat.Elements[iEle]));
		}

		Matrix4Soft<float> identity;
		identity.InitIdentity();
		for (int iEle = 0; iEle < 16; iEle++)
		{
			EXPECT_GE(EPSILON_MID_PRECISION, Math::Abs(identity.Elements[iEle] - invMul.Elements[iEle]));
		}

		for (int iEle = 0; iEle < 16; iEle++)
		{
			EXPECT_GE(EPSILON_MID_PRECISION, Math::Abs(identity.Elements[iEle] - invMul2.Elements[iEle]));
		}
	}

}













TEST_F(MathTest, SSE_Matrix4_Simple)
{
	Vector4SSE a(4, 5, 6, 1), b(2, 2, 2, 2);
	Matrix4SSE m;
	Vector4SSE SRT[3];

	const struct {
		bool UseScale = false;
		bool UseRot = false;
		bool UseTrans = false;
	} TestSetting[] =
	{
		{},
	{ true, false, false },
	{ false, true, false },
	{ false, false, true },
	{ true, false, true },
	{ true, true, false },
	{ false, true, true },
	{ true, true, true },
	};

	Matrix4SSE m2(
		1, 2, 3, 4,
		5, 6, 7, 8,
		9, 10, 11, 12,
		13, 14, 15, 16
	);


	auto randScale = SF::Vector4SSE(RandomVector()) - 64.f;
	SF::Matrix4SSE scaleMat;
	SF::Matrix4Soft<float> scaleMatSoft;
	scaleMat.InitScaleMatrix(randScale);
	scaleMatSoft.InitScaleMatrix(Vector4Soft<float>(randScale.x, randScale.y, randScale.z, randScale.w));

	CompareMatrix(scaleMatSoft, scaleMat);

	EXPECT_GE(EPSILON_MID_PRECISION, Math::Abs(scaleMat.a00 - randScale.x));
	EXPECT_GE(EPSILON_MID_PRECISION, Math::Abs(scaleMat.a01));
	EXPECT_GE(EPSILON_MID_PRECISION, Math::Abs(scaleMat.a02));
	EXPECT_GE(EPSILON_MID_PRECISION, Math::Abs(scaleMat.a03));
	EXPECT_GE(EPSILON_MID_PRECISION, Math::Abs(scaleMat.a11 - randScale.y));
	EXPECT_GE(EPSILON_MID_PRECISION, Math::Abs(scaleMat.a10));
	EXPECT_GE(EPSILON_MID_PRECISION, Math::Abs(scaleMat.a12));
	EXPECT_GE(EPSILON_MID_PRECISION, Math::Abs(scaleMat.a13));
	EXPECT_GE(EPSILON_MID_PRECISION, Math::Abs(scaleMat.a22 - randScale.z));
	EXPECT_GE(EPSILON_MID_PRECISION, Math::Abs(scaleMat.a20));
	EXPECT_GE(EPSILON_MID_PRECISION, Math::Abs(scaleMat.a21));
	EXPECT_GE(EPSILON_MID_PRECISION, Math::Abs(scaleMat.a23));
	EXPECT_GE(EPSILON_MID_PRECISION, Math::Abs(scaleMat.a33 - 1));
	EXPECT_GE(EPSILON_MID_PRECISION, Math::Abs(scaleMat.a30));
	EXPECT_GE(EPSILON_MID_PRECISION, Math::Abs(scaleMat.a31));
	EXPECT_GE(EPSILON_MID_PRECISION, Math::Abs(scaleMat.a32));

	auto randTrans = SF::Vector4SSE(RandomVector());
	SF::Matrix4SSE transMat;
	SF::Matrix4Soft<float> transMatSoft;
	transMat.InitTranslationMatrix(randTrans);
	transMatSoft.InitTranslationMatrix(Vector4Soft<float>(randTrans.x, randTrans.y, randTrans.z, randTrans.w));

	CompareMatrix(transMatSoft, transMat);

	EXPECT_GE(EPSILON_MID_PRECISION, Math::Abs(transMat.a00 - 1));
	EXPECT_GE(EPSILON_MID_PRECISION, Math::Abs(transMat.a01));
	EXPECT_GE(EPSILON_MID_PRECISION, Math::Abs(transMat.a02));
	EXPECT_GE(EPSILON_MID_PRECISION, Math::Abs(transMat.a03 - randTrans.x));
	EXPECT_GE(EPSILON_MID_PRECISION, Math::Abs(transMat.a11 - 1));
	EXPECT_GE(EPSILON_MID_PRECISION, Math::Abs(transMat.a10));
	EXPECT_GE(EPSILON_MID_PRECISION, Math::Abs(transMat.a12));
	EXPECT_GE(EPSILON_MID_PRECISION, Math::Abs(transMat.a13 - randTrans.y));
	EXPECT_GE(EPSILON_MID_PRECISION, Math::Abs(transMat.a22 - 1));
	EXPECT_GE(EPSILON_MID_PRECISION, Math::Abs(transMat.a20));
	EXPECT_GE(EPSILON_MID_PRECISION, Math::Abs(transMat.a21));
	EXPECT_GE(EPSILON_MID_PRECISION, Math::Abs(transMat.a23 - randTrans.z));
	EXPECT_GE(EPSILON_MID_PRECISION, Math::Abs(transMat.a33 - 1));
	EXPECT_GE(EPSILON_MID_PRECISION, Math::Abs(transMat.a30));
	EXPECT_GE(EPSILON_MID_PRECISION, Math::Abs(transMat.a31));
	EXPECT_GE(EPSILON_MID_PRECISION, Math::Abs(transMat.a32));


	auto xAxis = SF::Vector4SSE(1, 0, 0, 1);
	auto nxAxis = SF::Vector4SSE(-1, 0, 0, 1);
	auto yAxis = SF::Vector4SSE(0, 1, 0, 1);
	auto nyAxis = SF::Vector4SSE(0, -1, 0, 1);
	auto zAxis = SF::Vector4SSE(0, 0, 1, 1);
	auto nzAxis = SF::Vector4SSE(0, 0, -1, 1);
	SF::Matrix4SSE rotMat;

	auto randRot = SF::Vector4SSE(1, 0, 0, C_FHALF_PI);
	Matrix4Soft<float> rotMatSoft;
	rotMat.InitRotationMatrix(randRot);
	rotMatSoft.InitRotationMatrix(Vector4Soft<float>(randRot.x, randRot.y, randRot.z, randRot.w));

	CompareMatrix(rotMatSoft, rotMat);


	auto resVec = rotMat * xAxis;
	CompareVector(resVec, xAxis);
	resVec = rotMat * yAxis;
	CompareVector(resVec, zAxis);
	resVec = rotMat * zAxis;
	CompareVector(resVec, nyAxis);

	randRot = SF::Vector4SSE(-1, 0, 0, C_FHALF_PI);
	rotMat.InitRotationMatrix(randRot);
	rotMatSoft.InitRotationMatrix(Vector4Soft<float>(randRot.x, randRot.y, randRot.z, randRot.w));
	CompareMatrix(rotMatSoft, rotMat);

	resVec = rotMat * xAxis;
	CompareVector(resVec, xAxis);
	resVec = rotMat * yAxis;
	CompareVector(resVec, nzAxis);
	resVec = rotMat * zAxis;
	CompareVector(resVec, yAxis);

	randRot = SF::Vector4SSE(0, 1, 0, C_FHALF_PI);
	rotMat.InitRotationMatrix(randRot);
	rotMatSoft.InitRotationMatrix(Vector4Soft<float>(randRot.x, randRot.y, randRot.z, randRot.w));
	CompareMatrix(rotMatSoft, rotMat);

	resVec = rotMat * xAxis;
	CompareVector(resVec, nzAxis);
	resVec = rotMat * yAxis;
	CompareVector(resVec, yAxis);
	resVec = rotMat * zAxis;
	CompareVector(resVec, xAxis);

	randRot = SF::Vector4SSE(0, -1, 0, C_FHALF_PI);
	rotMat.InitRotationMatrix(randRot);
	rotMatSoft.InitRotationMatrix(Vector4Soft<float>(randRot.x, randRot.y, randRot.z, randRot.w));
	CompareMatrix(rotMatSoft, rotMat);

	resVec = rotMat * xAxis;
	CompareVector(resVec, zAxis);
	resVec = rotMat * yAxis;
	CompareVector(resVec, yAxis);
	resVec = rotMat * zAxis;
	CompareVector(resVec, nxAxis);

	randRot = SF::Vector4SSE(0, 0, 1, C_FHALF_PI);
	rotMat.InitRotationMatrix(randRot);
	rotMatSoft.InitRotationMatrix(Vector4Soft<float>(randRot.x, randRot.y, randRot.z, randRot.w));
	CompareMatrix(rotMatSoft, rotMat);

	resVec = rotMat * xAxis;
	CompareVector(resVec, yAxis);
	resVec = rotMat * yAxis;
	CompareVector(resVec, nxAxis);
	resVec = rotMat * zAxis;
	CompareVector(resVec, zAxis);

	randRot = SF::Vector4SSE(0, 0, 1, C_FHALF_PI);
	rotMat.InitRotationMatrix(randRot);
	rotMatSoft.InitRotationMatrix(Vector4Soft<float>(randRot.x, randRot.y, randRot.z, randRot.w));
	CompareMatrix(rotMatSoft, rotMat);

	resVec = rotMat * xAxis;
	CompareVector(resVec, yAxis);
	resVec = rotMat * yAxis;
	CompareVector(resVec, nxAxis);
	resVec = rotMat * zAxis;
	CompareVector(resVec, zAxis);

	rotMat.InitRotationMatrix(zAxis, xAxis);
	rotMatSoft.InitRotationMatrix(Vector4Soft<float>(zAxis.x, zAxis.y, zAxis.z, zAxis.w), Vector4Soft<float>(xAxis.x, xAxis.y, xAxis.z, xAxis.w));
	CompareMatrix(rotMatSoft, rotMat);

	resVec = rotMat * xAxis;
	CompareVector(resVec, nzAxis);
	resVec = rotMat * yAxis;
	CompareVector(resVec, yAxis);
	resVec = rotMat * zAxis;
	CompareVector(resVec, xAxis);


	for (auto itTestSetting : TestSetting)
	{
		m = SetRandomTransform(SRT, itTestSetting.UseScale, itTestSetting.UseRot, itTestSetting.UseTrans);

		auto sum = m + m2;
		for (int iEle = 0; iEle < 16; iEle++)
		{
			float c = m.Elements[iEle] + m2.Elements[iEle];
			EXPECT_GE(EPSILON_MID_PRECISION, Math::Abs(c - sum.Elements[iEle]));
		}

		auto sub = m - m2;
		for (int iEle = 0; iEle < 16; iEle++)
		{
			float c = m.Elements[iEle] - m2.Elements[iEle];
			EXPECT_GE(EPSILON_MID_PRECISION, Math::Abs(c - sub.Elements[iEle]));
		}


		auto divs = m / 10;
		for (int iEle = 0; iEle < 16; iEle++)
		{
			float c = m.Elements[iEle] / 10.f;
			EXPECT_GE(EPSILON_MID_PRECISION, Math::Abs(c - divs.Elements[iEle]));
		}


		auto muls = m * 10;
		for (int iEle = 0; iEle < 16; iEle++)
		{
			float c = m.Elements[iEle] * 10.f;
			EXPECT_GE(EPSILON_MID_PRECISION, Math::Abs(c - muls.Elements[iEle]));
		}

		auto mulv = m * a;
		{
			float x = m.a00 * a.x + m.a01 * a.y + m.a02 * a.z + m.a03 * a.w;
			float y = m.a10 * a.x + m.a11 * a.y + m.a12 * a.z + m.a13 * a.w;
			float z = m.a20 * a.x + m.a21 * a.y + m.a22 * a.z + m.a23 * a.w;
			float w = m.a30 * a.x + m.a31 * a.y + m.a32 * a.z + m.a33 * a.w;

			EXPECT_GE(EPSILON_MID_PRECISION, Math::Abs(x - mulv.x));
			EXPECT_GE(EPSILON_MID_PRECISION, Math::Abs(y - mulv.y));
			EXPECT_GE(EPSILON_MID_PRECISION, Math::Abs(z - mulv.z));
			EXPECT_GE(EPSILON_MID_PRECISION, Math::Abs(w - mulv.w));
		}

		auto mulv2 = a * m;
		{
			float x = m.a00 * a.x + m.a10 * a.y + m.a20 * a.z + m.a30 * a.w;
			float y = m.a01 * a.x + m.a11 * a.y + m.a21 * a.z + m.a31 * a.w;
			float z = m.a02 * a.x + m.a12 * a.y + m.a22 * a.z + m.a32 * a.w;
			float w = m.a03 * a.x + m.a13 * a.y + m.a23 * a.z + m.a33 * a.w;

			EXPECT_GE(EPSILON_MID_PRECISION, Math::Abs(x - mulv2.x));
			EXPECT_GE(EPSILON_MID_PRECISION, Math::Abs(y - mulv2.y));
			EXPECT_GE(EPSILON_MID_PRECISION, Math::Abs(z - mulv2.z));
			EXPECT_GE(EPSILON_MID_PRECISION, Math::Abs(w - mulv2.w));
		}
	}

}



TEST_F(MathTest, SSE_Matrix4_Invert)
{

	const struct {
		bool UseScale = false;
		bool UseRot = false;
		bool UseTrans = false;
	} TestSetting[] =
	{
		{ true, true, false },
	{ false, false, true },
	{ true, false, false },
	{ false, true, false },
	{},
	{ true, false, true },
	{ false, true, true },
	{ true, true, true },
	};

	Matrix4SSE m2(
		1, 2, 3, 4,
		5, 6, 7, 8,
		9, 10, 11, 12,
		13, 14, 15, 16
	);

	Vector4SSE TRS[3];

	Matrix4SSE m;
	for (auto itTestSetting : TestSetting)
	{
		m = SetRandomTransform(TRS, itTestSetting.UseScale, itTestSetting.UseRot, itTestSetting.UseTrans);

		auto invMat = m.GetInverse();
		auto inv2Mat = invMat.GetInverse();
		auto invMul = invMat * m;
		auto invMul2 = m * invMat;
		for (int iEle = 0; iEle < 16; iEle++)
		{
			EXPECT_GE(EPSILON_LOW_PRECISION, Math::Abs(m.Elements[iEle] - inv2Mat.Elements[iEle]));
		}

		Matrix4SSE identity;
		identity.InitIdentity();
		for (int iEle = 0; iEle < 16; iEle++)
		{
			EXPECT_GE(EPSILON_MID_PRECISION, Math::Abs(identity.Elements[iEle] - invMul.Elements[iEle]));
		}

		for (int iEle = 0; iEle < 16; iEle++)
		{
			EXPECT_GE(EPSILON_MID_PRECISION, Math::Abs(identity.Elements[iEle] - invMul2.Elements[iEle]));
		}
	}


	for (auto itTestSetting : TestSetting)
	{
		//if (itTestSetting.UseScale)
		//	continue;

		m = SetRandomTransform(TRS, itTestSetting.UseScale, itTestSetting.UseRot, itTestSetting.UseTrans);

		auto invMat = m.GetInverseTransform();
		auto invMat2 = m.GetInverse();
		auto inv2Mat = invMat.GetInverseTransform();
		auto inv2Mat2 = invMat2.GetInverse();
		auto invMul = invMat * m;
		auto invMul2 = invMat2 * m;


		for (int iEle = 0; iEle < 16; iEle++)
		{
			EXPECT_GE(EPSILON_MID_PRECISION, Math::Abs(invMat.Elements[iEle] - invMat2.Elements[iEle]));
		}

		// 
		if (!itTestSetting.UseScale)
		{
			for (int iEle = 0; iEle < 16; iEle++)
			{
				EXPECT_GE(EPSILON_MID_PRECISION, Math::Abs(inv2Mat.Elements[iEle] - inv2Mat2.Elements[iEle]));
			}


			for (int iEle = 0; iEle < 16; iEle++)
			{
				EXPECT_GE(EPSILON_MID_PRECISION, Math::Abs(m.Elements[iEle] - inv2Mat.Elements[iEle]));
			}
		}

		Matrix4SSE identity;
		identity.InitIdentity();
		for (int iEle = 0; iEle < 16; iEle++)
		{
			EXPECT_GE(EPSILON_MID_PRECISION, Math::Abs(identity.Elements[iEle] - invMul.Elements[iEle]));
		}

		for (int iEle = 0; iEle < 16; iEle++)
		{
			EXPECT_GE(EPSILON_MID_PRECISION, Math::Abs(identity.Elements[iEle] - invMul2.Elements[iEle]));
		}
	}


	for (auto itTestSetting : TestSetting)
	{
		if (itTestSetting.UseScale)
			continue;

		m = SetRandomTransform(TRS, itTestSetting.UseScale, itTestSetting.UseRot, itTestSetting.UseTrans);

		auto invMat = m.GetInverseTransformNoScale();
		auto invMat2 = m.GetInverse();
		auto inv2Mat = invMat.GetInverseTransformNoScale();
		auto inv2Mat2 = invMat2.GetInverse();
		auto invMul = invMat * m;
		auto invMul2 = invMat2 * m;


		for (int iEle = 0; iEle < 16; iEle++)
		{
			EXPECT_GE(EPSILON_MID_PRECISION, Math::Abs(invMat.Elements[iEle] - invMat2.Elements[iEle]));
		}

		for (int iEle = 0; iEle < 16; iEle++)
		{
			EXPECT_GE(EPSILON_HIGH_PRECISION, Math::Abs(inv2Mat.Elements[iEle] - inv2Mat2.Elements[iEle]));
		}


		for (int iEle = 0; iEle < 16; iEle++)
		{
			EXPECT_GE(EPSILON_MID_PRECISION, Math::Abs(m.Elements[iEle] - inv2Mat.Elements[iEle]));
		}

		Matrix4SSE identity;
		identity.InitIdentity();
		for (int iEle = 0; iEle < 16; iEle++)
		{
			EXPECT_GE(EPSILON_MID_PRECISION, Math::Abs(identity.Elements[iEle] - invMul.Elements[iEle]));
		}

		for (int iEle = 0; iEle < 16; iEle++)
		{
			EXPECT_GE(EPSILON_MID_PRECISION, Math::Abs(identity.Elements[iEle] - invMul2.Elements[iEle]));
		}
	}

}









