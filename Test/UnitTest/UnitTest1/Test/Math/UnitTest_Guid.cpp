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
        "69F7DF71-9151-4ACB-8670-E523F9C1A149",
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

    for (const char* testGuid : TestValids)
    {
        EXPECT_TRUE(Guid::TryParseGeneric(testGuid, op1));
        op2 = Guid::ParseGeneric(testGuid);

        if (CPUInfo::GetFeatures().AVX)
        {
            CPUInfo::GetFeaturesMutable().AVX = 0;
            EXPECT_TRUE(Guid::TryParseGeneric(testGuid, op3));
            CPUInfo::GetFeaturesMutable().AVX = 1;
        }

        char op1Str[64]{};
        char op2Str[64]{};
        char op3Str[64]{};

        op1.ToString(op1Str);
        op2.ToString(op2Str);
        op3.ToString(op3Str);

        EXPECT_TRUE(op1.IsValid());
        EXPECT_TRUE(op2.IsValid());
        EXPECT_TRUE(op3.IsValid());

        EXPECT_TRUE(op1 == op2);
        EXPECT_TRUE(op2 == op3);
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
    }
}

