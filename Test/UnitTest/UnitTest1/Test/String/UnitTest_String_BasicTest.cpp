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
#include "Util/SFToString.h"
#include "Util/SFStringFormat.h"
#include "UnitTest_String.h"
#include "Util/SFString.h"
#include "Util/SFStringConverter.h"


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

TEST_F(StringTest, SFStringBasic)
{
    String A("Test1");
    String B("B");
    String C = A + B;
    WString WA(L"Test1");
    WString WB(L"B");
    WString WC = WA + WB;

    EXPECT_EQ(A.IsEqual("Test1"), true);
    EXPECT_EQ(A.IsEqual("tEst1"), false);
    EXPECT_EQ(A.IsEqualIgnoreCase("tEst1"), true);
    EXPECT_EQ(5, A.GetLength());
    EXPECT_EQ(B.IsEqual("B"), true);
    EXPECT_EQ(B.IsEqual("b"), false);
    EXPECT_EQ(B.IsEqualIgnoreCase("b"), true);
    EXPECT_EQ(1, B.GetLength());
    EXPECT_EQ(C.IsEqual("Test1B"), true);
    EXPECT_EQ(C.IsEqual("TEsT1b"), false);
    EXPECT_EQ(C.IsEqualIgnoreCase("TEsT1b"), true);
    EXPECT_EQ(6, C.GetLength());
    EXPECT_GE(6+1, C.GetBufferLength());

    EXPECT_EQ(WA.IsEqual(L"Test1"), true);
    EXPECT_EQ(WA.IsEqual(L"tEst1"), false);
    EXPECT_EQ(WA.IsEqualIgnoreCase(L"tEst1"), true);
    EXPECT_EQ(5, WA.GetLength());
    EXPECT_EQ(WB.IsEqual(L"B"), true);
    EXPECT_EQ(WB.IsEqual(L"b"), false);
    EXPECT_EQ(WB.IsEqualIgnoreCase(L"b"), true);
    EXPECT_EQ(1, WB.GetLength());
    EXPECT_EQ(WC.IsEqual(L"Test1B"), true);
    EXPECT_EQ(WC.IsEqual(L"TeSt1b"), false);
    EXPECT_EQ(WC.IsEqualIgnoreCase(L"TEsT1b"), true);
    EXPECT_EQ(6, WC.GetLength());
    EXPECT_EQ((6 + 1) * 2, WC.GetBufferLength());
}

TEST_F(StringTest, SFStringConverter)
{
    String A("Test1");
    String B("B");
    String C = A + B;
    WString WA;
    WString WB;
    WString WC;

    WA = StringConverter<wchar_t, char>(A);
    WB = StringConverter<wchar_t, char>(B);
    WC = StringConverter<wchar_t, char>(C);

    EXPECT_EQ(WA.IsEqual(L"Test1"), true);
    EXPECT_EQ(WA.IsEqual(L"tEst1"), false);
    EXPECT_EQ(WA.IsEqualIgnoreCase(L"tEst1"), true);
    EXPECT_EQ(5, WA.GetLength());
    EXPECT_EQ(WB.IsEqual(L"B"), true);
    EXPECT_EQ(WB.IsEqual(L"b"), false);
    EXPECT_EQ(WB.IsEqualIgnoreCase(L"b"), true);
    EXPECT_EQ(1, WB.GetLength());
    EXPECT_EQ(WC.IsEqual(L"Test1B"), true);
    EXPECT_EQ(WC.IsEqual(L"TeSt1b"), false);
    EXPECT_EQ(WC.IsEqualIgnoreCase(L"TEsT1b"), true);
    EXPECT_EQ(6, WC.GetLength());
    EXPECT_EQ((6 + 1) * 2, WC.GetBufferLength());


    A = StringConverter<char, wchar_t>(WA);
    B = StringConverter<char, wchar_t>(WB);
    C = StringConverter<char, wchar_t>(WC);

    EXPECT_EQ(A.IsEqual("Test1"), true);
    EXPECT_EQ(A.IsEqual("tEst1"), false);
    EXPECT_EQ(A.IsEqualIgnoreCase("tEst1"), true);
    EXPECT_EQ(5, A.GetLength());
    EXPECT_EQ(B.IsEqual("B"), true);
    EXPECT_EQ(B.IsEqual("b"), false);
    EXPECT_EQ(B.IsEqualIgnoreCase("b"), true);
    EXPECT_EQ(1, B.GetLength());
    EXPECT_EQ(C.IsEqual("Test1B"), true);
    EXPECT_EQ(C.IsEqual("TEsT1b"), false);
    EXPECT_EQ(C.IsEqualIgnoreCase("TEsT1b"), true);
    EXPECT_EQ(6, C.GetLength());
    EXPECT_GE(6 + 1, C.GetBufferLength());
}

TEST_F(StringTest, ToLowerToUpper)
{
    String A("Ab1cd2ef3gZ");
    String B;

    B = A;

    B.ToLowerInline();
    A.ToUpperInline();

    EXPECT_EQ(A.IsEqual("AB1CD2EF3GZ"), true);
    EXPECT_EQ(B.IsEqual("ab1cd2ef3gz"), true);
}
