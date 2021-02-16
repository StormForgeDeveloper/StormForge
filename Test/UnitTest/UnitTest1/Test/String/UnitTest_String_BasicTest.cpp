////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2020 StormForge
// 
// Author : KyungKun Ko
//
// Description : String basic test
//	
//
////////////////////////////////////////////////////////////////////////////////


#include "UnitTest1PCH.h"
#include <gtest/gtest.h>
#include "Multithread/SFSystemSynchronization.h"
#include "Multithread/SFThread.h"
#include "Container/SFDualSortedMap.h"
#include "Util/SFTimeUtil.h"
#include "Util/SFRandom.h"
#include "String/SFToString.h"
#include "String/SFStringFormat.h"
#include "UnitTest_String.h"


using ::testing::EmptyTestEventListener;
using ::testing::InitGoogleTest;
using ::testing::Test;
using ::testing::TestCase;
using ::testing::TestEventListeners;
using ::testing::TestInfo;
using ::testing::TestPartResult;
using ::testing::UnitTest;
using namespace ::SF;


//


TEST_F(StringTest, CharBasic)
{
	String A("A");
	String B("B");
	String C;


	EXPECT_EQ(C.IsNullOrEmpty(), true);

	EXPECT_EQ(A.IsEqual("A"), true);
	EXPECT_EQ(A.size(), 1);
	EXPECT_EQ(A.GetLength(), 1);
	EXPECT_EQ(A.length(), 1);
	EXPECT_EQ(A.IsNullOrEmpty(), false);

	EXPECT_EQ(B.IsEqual("B"), true);

	C = A + B;
	EXPECT_EQ(C.IsEqual("AB"), true);
	EXPECT_EQ(C.length(), 2);

	String D = A;
	D.Append("B");
	D.Append(B);
	EXPECT_EQ(D.IsEqual("ABB"), true);
	EXPECT_EQ(D.length(), 3);
}


TEST_F(StringTest, Substring)
{
	String A("Test1Test2Test3Abcdefg");
	String B, C;

	B = A.SubString(0, 5);
	EXPECT_EQ(B.IsEqual("Test1"), true);

	C = A.SubString(5, 10);
	EXPECT_EQ(C.IsEqual("Test2Test3"), true);

	// over copy test
	C = A.SubString(15, 7);
	EXPECT_EQ(C.IsEqual("Abcdefg"), true);
	EXPECT_EQ(C.length(), 7);

	C = A.SubString(15, 8);
	EXPECT_EQ(C.IsEqual("Abcdefg"), true);
	EXPECT_EQ(C.length(), 7);

	C = A.SubString(15, 20);
	EXPECT_EQ(C.IsEqual("Abcdefg"), true);
	EXPECT_EQ(C.length(), 7);
}

TEST_F(StringTest, Format)
{
	String A("Test1");
	String B("B");
	String C;

	C.Format("{0}/{1}", A, "DBInstance");
	EXPECT_EQ(C.IsEqual("Test1/DBInstance"), true);

	C.Format("{0}/{1}", A, B);
	EXPECT_EQ(C.IsEqual("Test1/B"), true);
}

