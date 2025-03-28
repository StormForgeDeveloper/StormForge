// UnitTestMath3DVector.cpp : Defines the entry point for the console application.
//

#include "UnitTest1PCH.h"
#include <gtest/gtest.h>
#include "UnitTest_Math.h"
#include "Platform/SFCPUInfo.h"

using ::testing::EmptyTestEventListener;
using ::testing::InitGoogleTest;
using ::testing::Test;
using ::testing::TestCase;
using ::testing::TestEventListeners;
using ::testing::TestInfo;
using ::testing::TestPartResult;
using ::testing::UnitTest;
using namespace ::SF;





TEST_F(MathTest, Guid)
{
    const char* TestValids[] = {
        "511078dd-f145-11ee-80d8-0242ac12000a",
        "00000000-0000-0000-0000-1234556789e7",
        "12345678-0000-0000-0000-000000000000",
        "00000000-1234-0000-0000-000000000000",
        "00000000-0000-5678-0000-000000000000",
        "00000000-0000-0000-abcd-000000000000",
        "000000000000000000001234556789e7",
        "12345678000000000000000000000000",
        "00000000123400000000000000000000",
        "00000000000056780000000000000000",
        "0000000000000000abcd000000000000",
        "01234567-89ab-cdef-ABCD-EF23F9C1A149",
        "69f7df71-9151-4acb-8670-e523f9c1a149",
        "45E22DBC-C7C3-447C-86C1-F103E803FF35",
        "B865CF14-9865-4C9A-AA97-AA79490B792F",
        "9ED9C1DD-4D31-489B-83D4-A79C410B4177",
        "EBD33375-4720-4C00-AB9D-61A17BB19B97",
        "56789e7",
        "7BB19B97"
        "1",
    };

    const char* TestInvalids[] = {
        "0000000000000-0000-0000-1234556789e7",
        "12345678-000000000-0000-000000000000",
        "00000000-1234-000000000-000000000000",
        "00000000-0000-5678-00000000000000000",
        //"00-0000-0000-0000-abcd-00000-00000", // TryParse can't detect this case
        //"00k000000000567800000000q0000000",
        "00000000r0000r5678r0000r000000000000",
    };


    Guid op1, op2, op3;

    //EXPECT_TRUE(Guid::TryParseRFC("00000000-0000-0000-0000-000000000000", op1));
    //op2 = Guid::ParseGeneric("00000000-0000-0000-0000-000000000000");
    //EXPECT_TRUE(op1 == op2);
    //if (CPUInfo::GetFeatures().AVX2)
    //{
    //    CPUInfo::GetFeaturesMutable().AVX2 = 0;

    //    EXPECT_TRUE(Guid::TryParseRFC("00000000-0000-0000-0000-000000000000", op1));
    //    op2 = Guid::ParseGeneric("00000000-0000-0000-0000-000000000000");
    //    EXPECT_TRUE(op1 == op2);

    //    CPUInfo::GetFeaturesMutable().AVX2 = 1;
    //}

    // test RFC byte order
    const char* TestOrder = "01234567-89ab-cdef-ABCD-EF23F9C1A149";
    uint8_t expectedBytes[16] = { 0x67, 0x45, 0x23, 0x01,
        0xab, 0x89,
        0xef, 0xcd,
        0xab, 0xcd,   0xEF, 0x23, 0xF9, 0xC1, 0xA1, 0x49
    };

    EXPECT_TRUE(Guid::TryParseRFC(TestOrder, op1));

    for (int iByte = 0; iByte < countof(expectedBytes); iByte++)
    {
        EXPECT_TRUE(op1.data[iByte] == expectedBytes[iByte]);
    }

    if (CPUInfo::GetFeatures().AVX2)
    {
        CPUInfo::GetFeaturesMutable().AVX2 = 0;

        EXPECT_TRUE(Guid::TryParseRFC(TestOrder, op2));

        for (int iByte = 0; iByte < countof(expectedBytes); iByte++)
        {
            EXPECT_TRUE(op2.data[iByte] == expectedBytes[iByte]);
        }

        CPUInfo::GetFeaturesMutable().AVX2 = 1;
    }




    for (const char* testGuid : TestValids)
    {
        char op1Str[64]{};
        char op2Str[64]{};
        char op3Str[64]{};
        char op4Str[64]{};

        EXPECT_TRUE(Guid::TryParseGeneric(testGuid, op1));
        EXPECT_EQ(op1.ToString(op1Str, sizeof(op1Str)), 36);

        op2 = Guid::ParseGeneric(testGuid);
        EXPECT_EQ(op2.ToString(op2Str, sizeof(op2Str)), 36);

        op3 = op2;
        if (CPUInfo::GetFeatures().AVX2)
        {
            CPUInfo::GetFeaturesMutable().AVX2 = 0;
            EXPECT_TRUE(Guid::TryParseGeneric(testGuid, op3));
            CPUInfo::GetFeaturesMutable().AVX2 = 1;
        }
        EXPECT_EQ(op3.ToString(op3Str, sizeof(op3Str)), 36);

        Guid op4(op1.ToLow64(), op1.ToHigh64());
        EXPECT_EQ(op4.ToString(op4Str, sizeof(op4Str)), 36);


        EXPECT_TRUE(op1.IsValid());
        EXPECT_TRUE(op2.IsValid());
        EXPECT_TRUE(op3.IsValid());
        EXPECT_TRUE(op4.IsValid());

        EXPECT_TRUE(op1 == op2);
        EXPECT_TRUE(op2 == op3);
        EXPECT_TRUE(op3 == op4);

        EXPECT_TRUE(StrUtil::StringCompair(op1Str, op2Str));
        EXPECT_TRUE(StrUtil::StringCompair(op2Str, op3Str));
    }

    for (const char* testGuid : TestInvalids)
    {
        EXPECT_FALSE(Guid::TryParseGeneric(testGuid, op1));
    }


    {
        uint64_t test64 = 76561198044532044;
        Guid testGuid = Guid::FromUInt64(test64);

        std::string testString = testGuid.ToString();
        EXPECT_TRUE(testString == "4ccd0505-0100-1001-0000-000000000000");

        EXPECT_EQ(testGuid.ToUInt64(), test64);

        if (CPUInfo::GetFeatures().AVX2)
        {
            CPUInfo::GetFeaturesMutable().AVX2 = 0;

            testGuid = Guid::FromUInt64(test64);
            testString = testGuid.ToString();
            EXPECT_TRUE(testString == "4ccd0505-0100-1001-0000-000000000000");

            EXPECT_EQ(testGuid.ToUInt64(), test64);

            CPUInfo::GetFeaturesMutable().AVX2 = 1;
        }

    }


    {
        uint64_t test64 = 3;
        Guid testGuid = Guid::FromUInt64(test64);

        std::string testString = testGuid.ToString();
        EXPECT_TRUE(testString == "03000000-0000-0000-0000-000000000000");

        EXPECT_EQ(testGuid.ToUInt64(), test64);

        if (CPUInfo::GetFeatures().AVX2)
        {
            CPUInfo::GetFeaturesMutable().AVX2 = 0;

            testGuid = Guid::FromUInt64(test64);
            testString = testGuid.ToString();
            EXPECT_TRUE(testString == "03000000-0000-0000-0000-000000000000");

            EXPECT_EQ(testGuid.ToUInt64(), test64);

            CPUInfo::GetFeaturesMutable().AVX2 = 1;
        }

    }
}

