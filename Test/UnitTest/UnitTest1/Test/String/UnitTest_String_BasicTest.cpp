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

	EXPECT_EQ(A.Equals("A"), true);
	EXPECT_EQ(A.size(), 1);
	EXPECT_EQ(A.GetLength(), 1);
	EXPECT_EQ(A.length(), 1);
	EXPECT_EQ(A.IsNullOrEmpty(), false);

	EXPECT_EQ(B.Equals("B"), true);

	C = A + B;
	EXPECT_EQ(C.Equals("AB"), true);
	EXPECT_EQ(C.length(), 2);

	String D = A;
	D.Append("B");
	D.Append(B);
	EXPECT_EQ(D.Equals("ABB"), true);
	EXPECT_EQ(D.length(), 3);
}


TEST_F(StringTest, Substring)
{
	String A("Test1Test2Test3Abcdefg");
	String B, C;

	B = A.SubString(0, 5);
	EXPECT_EQ(B.Equals("Test1"), true);

	C = A.SubString(5, 10);
	EXPECT_EQ(C.Equals("Test2Test3"), true);

	// over copy test
	C = A.SubString(15, 7);
	EXPECT_EQ(C.Equals("Abcdefg"), true);
	EXPECT_EQ(C.length(), 7);

	C = A.SubString(15, 8);
	EXPECT_EQ(C.Equals("Abcdefg"), true);
	EXPECT_EQ(C.length(), 7);

	C = A.SubString(15, 20);
	EXPECT_EQ(C.Equals("Abcdefg"), true);
	EXPECT_EQ(C.length(), 7);
}

TEST_F(StringTest, Format)
{
	String A("Test1");
	String B("B");
	String C;

    std::string test = std::format("{0}/{1}", A, "DBInstance");

	C.Format("{0}/{1}", A, "DBInstance");
	EXPECT_EQ(C.Equals("Test1/DBInstance"), true);

	C.Format("{0}/{1}", A, B);
	EXPECT_EQ(C.Equals("Test1/B"), true);
}

TEST_F(StringTest, SFStringBasic)
{
    String A("Test1");
    String B("B");
    String C = A + B;
    WString WA(L"Test1");
    WString WB(L"B");
    WString WC = WA + WB;

    EXPECT_EQ(A.Equals("Test1"), true);
    EXPECT_EQ(A.Equals("tEst1"), false);
    EXPECT_EQ(A.EqualsIgnoreCase("tEst1"), true);
    EXPECT_EQ(5, A.GetLength());
    EXPECT_EQ(B.Equals("B"), true);
    EXPECT_EQ(B.Equals("b"), false);
    EXPECT_EQ(B.EqualsIgnoreCase("b"), true);
    EXPECT_EQ(1, B.GetLength());
    EXPECT_EQ(C.Equals("Test1B"), true);
    EXPECT_EQ(C.Equals("TEsT1b"), false);
    EXPECT_EQ(C.EqualsIgnoreCase("TEsT1b"), true);
    EXPECT_EQ(6, C.GetLength());

    EXPECT_EQ(WA.Equals(L"Test1"), true);
    EXPECT_EQ(WA.Equals(L"tEst1"), false);
    EXPECT_EQ(WA.EqualsIgnoreCase(L"tEst1"), true);
    EXPECT_EQ(5, WA.GetLength());
    EXPECT_EQ(WB.Equals(L"B"), true);
    EXPECT_EQ(WB.Equals(L"b"), false);
    EXPECT_EQ(WB.EqualsIgnoreCase(L"b"), true);
    EXPECT_EQ(1, WB.GetLength());
    EXPECT_EQ(WC.Equals(L"Test1B"), true);
    EXPECT_EQ(WC.Equals(L"TeSt1b"), false);
    EXPECT_EQ(WC.EqualsIgnoreCase(L"TEsT1b"), true);
    EXPECT_EQ(6, WC.GetLength());
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

    EXPECT_EQ(WA.Equals(L"Test1"), true);
    EXPECT_EQ(WA.Equals(L"tEst1"), false);
    EXPECT_EQ(WA.EqualsIgnoreCase(L"tEst1"), true);
    EXPECT_EQ(5, WA.GetLength());
    EXPECT_EQ(WB.Equals(L"B"), true);
    EXPECT_EQ(WB.Equals(L"b"), false);
    EXPECT_EQ(WB.EqualsIgnoreCase(L"b"), true);
    EXPECT_EQ(1, WB.GetLength());
    EXPECT_EQ(WC.Equals(L"Test1B"), true);
    EXPECT_EQ(WC.Equals(L"TeSt1b"), false);
    EXPECT_EQ(WC.EqualsIgnoreCase(L"TEsT1b"), true);
    EXPECT_EQ(6, WC.GetLength());


    A = StringConverter<char, wchar_t>(WA);
    B = StringConverter<char, wchar_t>(WB);
    C = StringConverter<char, wchar_t>(WC);

    EXPECT_EQ(A.Equals("Test1"), true);
    EXPECT_EQ(A.Equals("tEst1"), false);
    EXPECT_EQ(A.EqualsIgnoreCase("tEst1"), true);
    EXPECT_EQ(5, A.GetLength());
    EXPECT_EQ(B.Equals("B"), true);
    EXPECT_EQ(B.Equals("b"), false);
    EXPECT_EQ(B.EqualsIgnoreCase("b"), true);
    EXPECT_EQ(1, B.GetLength());
    EXPECT_EQ(C.Equals("Test1B"), true);
    EXPECT_EQ(C.Equals("TEsT1b"), false);
    EXPECT_EQ(C.EqualsIgnoreCase("TEsT1b"), true);
    EXPECT_EQ(6, C.GetLength());
}

TEST_F(StringTest, ToLowerToUpper)
{
    String A("Ab1cd2ef3gZ");
    String B;

    B = A;

    B.ToLowerInline();
    A.ToUpperInline();

    EXPECT_EQ(A.Equals("AB1CD2EF3GZ"), true);
    EXPECT_EQ(B.Equals("ab1cd2ef3gz"), true);
}

TEST_F(StringTest, Replace)
{
    String A("Ab1cd2b1bbZ");

    A.ReplaceInline("b1", "HHHH");

    EXPECT_EQ(A.Equals("AHHHHcd2HHHHbbZ"), true);


    A = "bAb1cd2b1bb";

    A.ReplaceInline("b1", "HHHH");

    EXPECT_EQ(A.Equals("bAHHHHcd2HHHHbb"), true);
}

TEST_F(StringTest, JoinSplit)
{
    DynamicArray<String> strings;
    strings.push_back("Ab1");
    strings.push_back("Ab2");
    strings.push_back("Ab3");

    String joined = String::Join(strings, "/");

    EXPECT_EQ(joined == "Ab1/Ab2/Ab3", true);

    DynamicArray<String> strings2;
    joined.Split('/', strings2);

    EXPECT_EQ(strings.size(), strings2.size());

    for (uint iStr = 0; iStr < strings.size(); iStr++)
    {
        EXPECT_EQ(strings[iStr], strings2[iStr]);
    }
}
