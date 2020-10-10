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




TEST_F(MathTest, Soft_Quaternion_Simple)
{
	QuaternionSoft<float> quat, quat2;


	auto randRot = SF::Vector4Soft<float>(1, 0, 0, C_FHALF_PI);
	quat = QuaternionSoft<float>(randRot);
	randRot = SF::Vector4Soft<float>(-1, 0, 0, C_FHALF_PI);
	quat2 = QuaternionSoft<float>(randRot);

	auto quat3 = quat * quat2;
	auto randVector = SF::Vector4Soft<float>(RandomVector());
	auto resVec1 = quat.RotateVector(quat2.RotateVector(randVector));
	auto resVec = quat3.RotateVector(randVector);

	CompareVector(resVec1, resVec);

	// 
	quat = QuaternionSoft<float>(RandomVector());
	auto quatConju = quat.GetConjugate();
	EXPECT_GE(EPSILON_HIGH_PRECISION, SF::Math::Abs(quatConju.x + quat.x));
	EXPECT_GE(EPSILON_HIGH_PRECISION, SF::Math::Abs(quatConju.y + quat.y));
	EXPECT_GE(EPSILON_HIGH_PRECISION, SF::Math::Abs(quatConju.z + quat.z));
	EXPECT_GE(EPSILON_HIGH_PRECISION, SF::Math::Abs(quatConju.w - quat.w));

	quat.Normalize();
	EXPECT_GE(EPSILON_HIGH_PRECISION, SF::Math::Abs(quat.Dot(quat) - 1));
	
}



TEST_F(MathTest, Soft_Quaternion_Rotation)
{
	QuaternionSoft<float> quat;


	auto xAxis = SF::Vector4Soft<float>(1, 0, 0, 1);
	auto nxAxis = SF::Vector4Soft<float>(-1, 0, 0, 1);
	auto yAxis = SF::Vector4Soft<float>(0, 1, 0, 1);
	auto nyAxis = SF::Vector4Soft<float>(0, -1, 0, 1);
	auto zAxis = SF::Vector4Soft<float>(0, 0, 1, 1);
	auto nzAxis = SF::Vector4Soft<float>(0, 0, -1, 1);

	auto randRot = SF::Vector4Soft<float>(1, 0, 0, C_FHALF_PI);
	quat = QuaternionSoft<float>(randRot);
	auto resVec = quat.RotateVector(xAxis);
	CompareVector(resVec, xAxis);
	resVec = quat.RotateVector(yAxis);
	CompareVector(resVec, zAxis);
	resVec = quat.RotateVector(zAxis);
	CompareVector(resVec, nyAxis);

	randRot = SF::Vector4Soft<float>(-1, 0, 0, C_FHALF_PI);
	quat = QuaternionSoft<float>(randRot);
	resVec = quat.RotateVector(xAxis);
	CompareVector(resVec, xAxis);
	resVec = quat.RotateVector(yAxis);
	CompareVector(resVec, nzAxis);
	resVec = quat.RotateVector(zAxis);
	CompareVector(resVec, yAxis);

	randRot = SF::Vector4Soft<float>(0, 1, 0, C_FHALF_PI);
	quat = QuaternionSoft<float>(randRot);
	resVec = quat.RotateVector(xAxis);
	CompareVector(resVec, nzAxis);
	resVec = quat.RotateVector(yAxis);
	CompareVector(resVec, yAxis);
	resVec = quat.RotateVector(zAxis);
	CompareVector(resVec, xAxis);

	randRot = SF::Vector4Soft<float>(0, -1, 0, C_FHALF_PI);
	quat = QuaternionSoft<float>(randRot);
	resVec = quat.RotateVector(xAxis);
	CompareVector(resVec, zAxis);
	resVec = quat.RotateVector(yAxis);
	CompareVector(resVec, yAxis);
	resVec = quat.RotateVector(zAxis);
	CompareVector(resVec, nxAxis);

	randRot = SF::Vector4Soft<float>(0, 0, 1, C_FHALF_PI);
	quat = QuaternionSoft<float>(randRot);
	resVec = quat.RotateVector(xAxis);
	CompareVector(resVec, yAxis);
	resVec = quat.RotateVector(yAxis);
	CompareVector(resVec, nxAxis);
	resVec = quat.RotateVector(zAxis);
	CompareVector(resVec, zAxis);

	randRot = SF::Vector4Soft<float>(0, 0, 1, C_FHALF_PI);
	quat = QuaternionSoft<float>(randRot);
	resVec = quat.RotateVector(xAxis);
	CompareVector(resVec, yAxis);
	resVec = quat.RotateVector(yAxis);
	CompareVector(resVec, nxAxis);
	resVec = quat.RotateVector(zAxis);
	CompareVector(resVec, zAxis);
}





TEST_F(MathTest, SSE_Quaternion_Simple)
{
	QuaternionSSE quat, quat2;


	// for reference
	auto randRotSoft = SF::Vector4Soft<float>(1, 0, 0, C_FHALF_PI);
	auto quatSoft = QuaternionSoft<float>(randRotSoft);
	randRotSoft = SF::Vector4Soft<float>(-1, 0, 0, C_FHALF_PI);
	auto quat2Soft = QuaternionSoft<float>(randRotSoft);

	auto quat3Soft = quatSoft * quat2Soft;
	auto randVectorSoft = SF::Vector4Soft<float>(RandomVector());
	auto resVecSoft = quat3Soft.RotateVector(randVectorSoft);


	auto randRot = SF::Vector4SSE(1, 0, 0, C_FHALF_PI);
	quat = QuaternionSSE(randRot);
	randRot = SF::Vector4SSE(-1, 0, 0, C_FHALF_PI);
	quat2 = QuaternionSSE(randRot);
	auto randVector = SF::Vector4SSE(randVectorSoft.x, randVectorSoft.y, randVectorSoft.z, randVectorSoft.w);

	auto quat3 = quat * quat2;

	auto q = quat3;
	auto v = randVector;
	auto xl = 2 * (q.w*v.z*q.y + q.x*v.z*q.z - q.w*v.y*q.z + q.x*v.y*q.y);
	auto yl = 2 * (q.w*v.x*q.z + q.x*v.x*q.y - q.w*v.z*q.x + q.y*v.z*q.z);
	auto zl = 2 * (q.w*v.y*q.x - q.w*v.x*q.y + q.x*v.x*q.z + q.y*v.y*q.z);

	auto xr = v.x*(q.w*q.w + q.x*q.x - q.y*q.y - q.z*q.z);
	auto yr = v.y*(q.w*q.w - q.x*q.x + q.y*q.y - q.z*q.z);
	auto zr = v.z*(q.w*q.w - q.x*q.x - q.y*q.y + q.z*q.z);

	auto resVec1 = quat.RotateVector(quat2.RotateVector(randVector));
	auto resVec = quat3.RotateVector(randVector);

	CompareQuaternion(quat3, quat3Soft);
	CompareVectorMID(resVecSoft, resVec1);
	CompareVectorMID(resVecSoft, resVec);

	CompareVector(resVec1, resVec);

	// 
	quat = QuaternionSSE(RandomVector());
	auto quatConju = quat.GetConjugate();
	EXPECT_GE(EPSILON_HIGH_PRECISION, SF::Math::Abs(quatConju.x + quat.x));
	EXPECT_GE(EPSILON_HIGH_PRECISION, SF::Math::Abs(quatConju.y + quat.y));
	EXPECT_GE(EPSILON_HIGH_PRECISION, SF::Math::Abs(quatConju.z + quat.z));
	EXPECT_GE(EPSILON_HIGH_PRECISION, SF::Math::Abs(quatConju.w - quat.w));

	quat.Normalize();
	EXPECT_GE(EPSILON_HIGH_PRECISION, SF::Math::Abs(quat.Dot(quat) - 1));

}



TEST_F(MathTest, SSE_Quaternion_Rotation)
{
	QuaternionSSE quat;


	auto xAxis = SF::Vector4SSE(1, 0, 0, 1);
	auto nxAxis = SF::Vector4SSE(-1, 0, 0, 1);
	auto yAxis = SF::Vector4SSE(0, 1, 0, 1);
	auto nyAxis = SF::Vector4SSE(0, -1, 0, 1);
	auto zAxis = SF::Vector4SSE(0, 0, 1, 1);
	auto nzAxis = SF::Vector4SSE(0, 0, -1, 1);

	auto randRot = SF::Vector4SSE(1, 0, 0, C_FHALF_PI);
	quat = QuaternionSSE(randRot);
	auto resVec = quat.RotateVector(xAxis);
	CompareVector(resVec, xAxis);
	resVec = quat.RotateVector(yAxis);
	CompareVector(resVec, zAxis);
	resVec = quat.RotateVector(zAxis);
	CompareVector(resVec, nyAxis);

	randRot = SF::Vector4SSE(-1, 0, 0, C_FHALF_PI);
	quat = QuaternionSSE(randRot);
	resVec = quat.RotateVector(xAxis);
	CompareVector(resVec, xAxis);
	resVec = quat.RotateVector(yAxis);
	CompareVector(resVec, nzAxis);
	resVec = quat.RotateVector(zAxis);
	CompareVector(resVec, yAxis);

	randRot = SF::Vector4SSE(0, 1, 0, C_FHALF_PI);
	quat = QuaternionSSE(randRot);
	resVec = quat.RotateVector(xAxis);
	CompareVector(resVec, nzAxis);
	resVec = quat.RotateVector(yAxis);
	CompareVector(resVec, yAxis);
	resVec = quat.RotateVector(zAxis);
	CompareVector(resVec, xAxis);

	randRot = SF::Vector4SSE(0, -1, 0, C_FHALF_PI);
	quat = QuaternionSSE(randRot);
	resVec = quat.RotateVector(xAxis);
	CompareVector(resVec, zAxis);
	resVec = quat.RotateVector(yAxis);
	CompareVector(resVec, yAxis);
	resVec = quat.RotateVector(zAxis);
	CompareVector(resVec, nxAxis);

	randRot = SF::Vector4SSE(0, 0, 1, C_FHALF_PI);
	quat = QuaternionSSE(randRot);
	resVec = quat.RotateVector(xAxis);
	CompareVector(resVec, yAxis);
	resVec = quat.RotateVector(yAxis);
	CompareVector(resVec, nxAxis);
	resVec = quat.RotateVector(zAxis);
	CompareVector(resVec, zAxis);

	randRot = SF::Vector4SSE(0, 0, 1, C_FHALF_PI);
	quat = QuaternionSSE(randRot);
	resVec = quat.RotateVector(xAxis);
	CompareVector(resVec, yAxis);
	resVec = quat.RotateVector(yAxis);
	CompareVector(resVec, nxAxis);
	resVec = quat.RotateVector(zAxis);
	CompareVector(resVec, zAxis);
}







