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

TEST_F(MathTest, Soft_Vector4_Simple)
{
	Vector4Soft<float> a(1,1,1,1), b(2,2,2,2);

	auto c = a + b;

	EXPECT_GE(EPSILON_MID_PRECISION, Math::Abs(c.x - 3));
	EXPECT_GE(EPSILON_MID_PRECISION, Math::Abs(c.y - 3));
	EXPECT_GE(EPSILON_MID_PRECISION, Math::Abs(c.z - 3));

	c = b - a;
	EXPECT_GE(EPSILON_MID_PRECISION, Math::Abs(c.x - 1));
	EXPECT_GE(EPSILON_MID_PRECISION, Math::Abs(c.y - 1));
	EXPECT_GE(EPSILON_MID_PRECISION, Math::Abs(c.z - 1));

	c = b * a;
	EXPECT_GE(EPSILON_MID_PRECISION, Math::Abs(c.x - 2));
	EXPECT_GE(EPSILON_MID_PRECISION, Math::Abs(c.y - 2));
	EXPECT_GE(EPSILON_MID_PRECISION, Math::Abs(c.z - 2));

	a = Vector4Soft<float>(4,5,6, 1);
	c = b / a;
	EXPECT_GE(EPSILON_MID_PRECISION, Math::Abs(c.x - 2.f / 4));
	EXPECT_GE(EPSILON_MID_PRECISION, Math::Abs(c.y - 2.f / 5));
	EXPECT_GE(EPSILON_MID_PRECISION, Math::Abs(c.z - 2.f / 6));
}



TEST_F(MathTest, SSE_Vector4_Simple)
{
	Vector4SSE a(1, 1, 1, 1), b(2, 2, 2, 2);

	auto c = a + b;

	EXPECT_GE(EPSILON_MID_PRECISION, Math::Abs(c.x - 3));
	EXPECT_GE(EPSILON_MID_PRECISION, Math::Abs(c.y - 3));
	EXPECT_GE(EPSILON_MID_PRECISION, Math::Abs(c.z - 3));

	c = b - a;
	EXPECT_GE(EPSILON_MID_PRECISION, Math::Abs(c.x - 1));
	EXPECT_GE(EPSILON_MID_PRECISION, Math::Abs(c.y - 1));
	EXPECT_GE(EPSILON_MID_PRECISION, Math::Abs(c.z - 1));

	c = b * a;
	EXPECT_GE(EPSILON_MID_PRECISION, Math::Abs(c.x - 2));
	EXPECT_GE(EPSILON_MID_PRECISION, Math::Abs(c.y - 2));
	EXPECT_GE(EPSILON_MID_PRECISION, Math::Abs(c.z - 2));

	a = Vector4SSE(4, 5, 6, 1);
	c = b / a;
	EXPECT_GE(EPSILON_MID_PRECISION, Math::Abs(c.x - 2.f / 4));
	EXPECT_GE(EPSILON_MID_PRECISION, Math::Abs(c.y - 2.f / 5));
	EXPECT_GE(EPSILON_MID_PRECISION, Math::Abs(c.z - 2.f / 6));
}


TEST_F(MathTest, Vector4_Box)
{
    Box4 volumeBox(Vector4(192.203003f, 3.44500017f, 61.1220016f), Vector4(194.203003f, 5.44500017f, 63.1220016f));
    EXPECT_FALSE(volumeBox.IsInside(Vector4(190.345169f, 4.50027466f, 59.0060959f)));

    EXPECT_TRUE(volumeBox.IsInside(volumeBox.Min));
    EXPECT_TRUE(volumeBox.IsInside(volumeBox.Max));
    EXPECT_TRUE(volumeBox.IsInside(volumeBox.GetMid()));

    EXPECT_FALSE(volumeBox.IsInside(Vector4(192.f, 3.f, 61.f)));
    EXPECT_FALSE(volumeBox.IsInside(Vector4(193.f, 3.f, 61.f)));
    EXPECT_FALSE(volumeBox.IsInside(Vector4(193.f, 4.f, 61.f)));
    EXPECT_TRUE(volumeBox.IsInside(Vector4(193.f, 4.f, 62.f)));
    EXPECT_FALSE(volumeBox.IsInside(Vector4(195.f, 4.f, 62.f)));
    EXPECT_FALSE(volumeBox.IsInside(Vector4(193.f, 6.f, 62.f)));
    EXPECT_FALSE(volumeBox.IsInside(Vector4(193.f, 4.f, 64.f)));
    EXPECT_FALSE(volumeBox.IsInside(Vector4(195.f, 6.f, 64.f)));

}
