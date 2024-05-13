////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) StormForge
// 
// Author : KyungKun Ko
//
// Description : Network test
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
#include "Util/SFStringCrc32.h"
#include "Util/SFStringCrc64.h"
#include "Util/SFToString.h"
#include "Net/SFMessage.h"
#include "Net/SFMessageWindow.h"
#include "ResultCode/SFResultCodeLibrary.h"
#include "ResultCode/SFResultCodeEngine.h"
#include "UnitTest_HTTP.h"
#include "Online/HTTP/SFHTTPClient.h"
#include "Online/HTTP/SFHTTPClientSystem.h"

using ::testing::EmptyTestEventListener;
using ::testing::InitGoogleTest;
using ::testing::Test;
using ::testing::TestCase;
using ::testing::TestEventListeners;
using ::testing::TestInfo;
using ::testing::TestPartResult;
using ::testing::UnitTest; 
using namespace SF;


TEST_F(HTTPTest, Client)
{
    const char* Urls[] = {
        "https://www.google.com",
        "https://www.google.com"
    };

    Atomic<int> ResponseCount = 0;
    DynamicArray<HTTPClientPtr> requests;
    for (const char* url : Urls)
    {
        HTTPClientPtr httpClient = Service::HTTP->CreateHTTPClient();
        EXPECT_NE(httpClient, nullptr);
        if (httpClient == nullptr)
            return;

        httpClient->SetURL(url);
        httpClient->SetMethod(true);
        httpClient->SetOnFinishedCallback([this, &ResponseCount](HTTPClient* pClient)
            {
                SFLog(Game, Info, "Result:{0], ResultContent:{1}", pClient->GetResultCode(), (const char*)pClient->GetResultContent().data());
                ResponseCount.fetch_add(1, MemoryOrder::relaxed);
            });

        httpClient->SendRequest();
        requests.push_back(httpClient);
    }

    ThisThread::SleepFor(DurationMS(40*1000));

    EXPECT_EQ(ResponseCount, countof(Urls));

    requests.Clear();

    ThisThread::SleepFor(DurationMS(1000));

    requests.Clear();
}
