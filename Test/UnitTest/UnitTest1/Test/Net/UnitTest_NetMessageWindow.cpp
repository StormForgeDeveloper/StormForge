// UnitTest_NetMessageWindow.cpp : Defines the entry point for the console application.
//

#include "UnitTest1PCH.h"
#include <gtest/gtest.h>
#include "SFAssert.h"
#include "Util/SFUtility.h"
#include "Net/SFNetDef.h"
#include "Net/SFMessage.h"
#include "Net/SFMessageWindow.h"
#include "ResultCode/SFResultCodeLibrary.h"

#include "Protocol/LoginMsgClass.h"

#include "UnitTest_Net.h"
#include "SFEngine.h"



using ::testing::EmptyTestEventListener;
using ::testing::InitGoogleTest;
using ::testing::Test;
using ::testing::TestCase;
using ::testing::TestEventListeners;
using ::testing::TestInfo;
using ::testing::TestPartResult;
using ::testing::UnitTest;
using namespace ::SF;


//const uint32_t TestScale = 2;
const uint32_t TEST_COUNT = 4000 * TestScale;


MessageDataPtr NewMessage(IHeap& memoryManager, uint32_t sequenceID)
{
    MessageData* pResult = MessageData::NewMessage(memoryManager, Message::Login::LoginCmd::MID, 2048);
    Message::Login::LoginCmd::Create(pResult->GetMessageHeader(), 0, StringCrc32("Conspiracy"), "11", "11");
	pResult->AssignSequence(sequenceID);

	return MessageDataPtr(pResult);
}

MessageDataPtr NewMessage(IHeap& memoryManager)
{
    MessageData* pResult = MessageData::NewMessage(memoryManager, Message::Login::LoginCmd::MID, 2048);
    Message::Login::LoginCmd::Create(pResult->GetMessageHeader(), 0, StringCrc32("Conspiracy"), "11", "11");

	return MessageDataPtr(pResult);
}


TEST_F(NetTest, RecvMessageWindowSimple)
{
	Heap testHeap("test", GetSystemHeap());

	Net::RecvMsgWindow recvMessage(testHeap);
	uint16_t uiSequence = 0;

	for (int iTest = 0; iTest < 2048; iTest++)
	{
		auto NewMsg = NewMessage(testHeap, uiSequence++);
		auto hr = recvMessage.AddMsg(NewMsg);
		if (iTest < recvMessage.GetAcceptableSequenceRange())
		{
			EXPECT_EQ(SF::ResultCode::SUCCESS, hr);
		}
		else
		{
			EXPECT_NE(SF::ResultCode::SUCCESS, hr);
		}
	}

	uiSequence = 0;
	for (int iTest = 0; iTest < 2048; iTest++)
	{
		MessageDataPtr pResult;
		Result hr = recvMessage.PopMsg(pResult);
		if (iTest < recvMessage.GetAcceptableSequenceRange())
		{
			EXPECT_TRUE(pResult != nullptr);
			EXPECT_TRUE(hr);

			EXPECT_TRUE(MessageSequence::Difference(pResult->GetMessageHeader()->msgID.IDSeq.Sequence, uiSequence++) == 0);
		}
		else
		{
			EXPECT_TRUE(pResult == nullptr);
			EXPECT_TRUE(!hr);
		}
	}
}

TEST_F(NetTest, RecvMessageWindowSimple2)
{
	Heap testHeap("test", GetSystemHeap());
	Net::RecvMsgWindow recvMessage(testHeap);
	uint16_t uiSequence = 0;
	uint16_t releaseSequence = 0;
	MessageDataPtr pResult, pNewMsg;
	Result hr;

	for (unsigned iTest = 0; iTest < TEST_COUNT; iTest++)
	{
		auto random = rand() % 2;
		switch (random)
		{
		case 0: // add
			pNewMsg = NewMessage(testHeap, uiSequence);
			hr = recvMessage.AddMsg(pNewMsg);
			if (MessageSequence::Difference(uiSequence, recvMessage.GetBaseSequence()) < recvMessage.GetAcceptableSequenceRange())
			{
				EXPECT_TRUE(hr);
				uiSequence++;
			}
			else
			{
				EXPECT_TRUE(!hr);
			}
			break;
		case 1: // release
			pResult = nullptr;
			hr = recvMessage.PopMsg(pResult);
			if (hr)
			{
				EXPECT_TRUE(pResult != nullptr);

				EXPECT_TRUE(MessageSequence::Difference(pResult->GetMessageHeader()->msgID.IDSeq.Sequence, releaseSequence++) == 0);
			}
			else
			{
				EXPECT_TRUE(pResult == nullptr);
				EXPECT_TRUE(!hr);
			}
			break;
		}

		recvMessage.GetSyncMask();
	}

	recvMessage.ClearWindow();
}

TEST_F(NetTest, RecvMessageWindowSimple3)
{
	Heap testHeap("test", GetSystemHeap());
	Net::RecvMsgWindow recvMessage(testHeap);
	uint16_t uiSequence = 0;
	uint16_t releaseSequence = 0;
	MessageDataPtr pResult;
	Result hr;

	for (unsigned iTest = 0; iTest < TEST_COUNT; iTest++)
	{
		auto random = rand() % 2;
		switch (random)
		{
		case 0: // add
		{
			auto testSequence = uiSequence;
			if (rand() % 2)
			{
				testSequence = (uint16_t)std::abs(rand());
			}
			auto pNewMsg = NewMessage(testHeap, testSequence);
			hr = recvMessage.AddMsg(pNewMsg);
			auto seqOffset = MessageSequence::Difference(testSequence, recvMessage.GetBaseSequence());
			if (seqOffset < recvMessage.GetAcceptableSequenceRange() && seqOffset >= 0)
			{
				EXPECT_TRUE(hr);
				uiSequence++;
			}
			else
			{
				EXPECT_TRUE(seqOffset < 0 || !hr);
			}
		}
		break;
		case 1: // release
			pResult = nullptr;
			hr = recvMessage.PopMsg(pResult);
			if (hr)
			{
				EXPECT_TRUE(pResult != nullptr);

				EXPECT_TRUE(MessageSequence::Difference(pResult->GetMessageHeader()->msgID.IDSeq.Sequence, releaseSequence++) == 0);
			}
			else
			{
				EXPECT_TRUE(pResult == nullptr);
				EXPECT_TRUE(!hr);
			}
			break;
		}

		recvMessage.GetSyncMask();
	}

	recvMessage.ClearWindow();
}




TEST_F(NetTest, RecvMessageWindowOutOfRange)
{
	Heap testHeap("test", GetSystemHeap());

	Net::RecvMsgWindow recvMessage(testHeap);
	uint16_t uiSequence = 0;
	const int MaxSequenceOffset = NET_SEQUENCE_MAX_DIFF;


	for (int iTest = 0; iTest < TEST_COUNT; iTest++, uiSequence++)
	{
		for (int testSequenceOffset = -MaxSequenceOffset; testSequenceOffset < MaxSequenceOffset; testSequenceOffset++)
		{
			auto testSequence = (int)uiSequence + testSequenceOffset;

			int diff = MessageSequence::Difference(testSequence, iTest);
			GTEST_ASSERT_EQ(diff, testSequenceOffset);
		}
	}


	uiSequence = 0;
	for (int iTest = 0; iTest < TEST_COUNT; iTest++, uiSequence++)
	{
		for (int testSequenceOffset = -MaxSequenceOffset; testSequenceOffset < MaxSequenceOffset; testSequenceOffset++)
		{
			auto testSequence = (int)uiSequence + testSequenceOffset;
			auto pNewMsg = NewMessage(testHeap, testSequence);
			auto hr = recvMessage.AddMsg(pNewMsg);
			if (testSequenceOffset < 0)
			{
				EXPECT_TRUE(hr == ResultCode::IO_SEQUENCE_OVERFLOW || hr == ResultCode::SUCCESS_IO_PROCESSED_SEQUENCE);
			}
			else if (testSequenceOffset > 0)
			{
				if (testSequenceOffset >= recvMessage.GetAcceptableSequenceRange())
				{
					EXPECT_TRUE(hr == ResultCode::IO_SEQUENCE_OVERFLOW || hr == ResultCode::SUCCESS_IO_PROCESSED_SEQUENCE);
				}
				else
				{
					EXPECT_TRUE(hr || hr == ResultCode::IO_SEQUENCE_OVERFLOW);
				}
			}
			else
			{
				EXPECT_TRUE(hr || hr == ResultCode::IO_SEQUENCE_OVERFLOW);
			}
		}

		MessageDataPtr pIMsg;
		auto hRes = recvMessage.PopMsg(pIMsg);
		if (pIMsg != nullptr)
		{
			EXPECT_EQ(MessageSequence::Difference(pIMsg->GetMessageHeader()->msgID.IDSeq.Sequence, uiSequence), 0);
		}
		else
		{
			EXPECT_FALSE(hRes);
		}
	}
}

TEST_F(NetTest, RecvMessageWindowMT)
{
	Heap testHeap("test", GetSystemHeap());
	const int NUM_SEND_THREAD = 10;
	const int NUM_RECV_THREAD = 1;
	const int NumTry = 2;
	const uint32_t runningTime = TestScale * 1 * 60 * 1000;

	Net::RecvMsgWindow recvMessage(testHeap);
	std::atomic<uint16_t> uiSequence(0);
	std::atomic<uint16_t> releaseSequence(0);
	std::vector<Thread*> threads;

	for (int iThread = 0; iThread < NUM_SEND_THREAD; iThread++)
	{
		auto newThread = new FunctorThread([&](Thread *pThread)
		{
			uint16_t sequence = uiSequence.fetch_add(1, std::memory_order_relaxed);
			MessageDataPtr pMsg;
			Result hr;

			while (!pThread->CheckKillEvent(DurationMS(0)))
			{
				for (int iTry = 0; iTry < NumTry; iTry++)
				{
					pMsg = NewMessage(testHeap, sequence);
					hr = recvMessage.AddMsg(pMsg);
					if (!hr)
					{
						pMsg = nullptr;
					}
					else
					{
						sequence = uiSequence.fetch_add(1, std::memory_order_relaxed);
					}

					recvMessage.GetSyncMask();
					pMsg = nullptr;
				}
			}
		});
		newThread->Start();
		threads.push_back(newThread);
	}

	for (int iThread = 0; iThread < NUM_RECV_THREAD; iThread++)
	{
		auto newThread = new FunctorThread([&](Thread *pThread)
		{
			Result hr;
			MessageDataPtr pResult;
			uint16_t sequence = releaseSequence.fetch_add(1, std::memory_order_relaxed);
			while (!pThread->CheckKillEvent(DurationMS(0)))
			{
				pResult = nullptr;
				hr = recvMessage.PopMsg(pResult);
				if (hr)
				{
					EXPECT_TRUE(pResult != nullptr);

					EXPECT_TRUE(MessageSequence::Difference(pResult->GetMessageHeader()->msgID.IDSeq.Sequence, sequence) == 0);
					pResult = nullptr;
					sequence = releaseSequence.fetch_add(1, std::memory_order_relaxed);
				}
				else
				{
					EXPECT_TRUE(pResult == nullptr);
					EXPECT_TRUE(!hr);
				}
			}
		});
		newThread->Start();
		threads.push_back(newThread);
	}

	ThisThread::SleepFor(DurationMS(runningTime));

	std::for_each(threads.begin(), threads.end(), [](Thread* pThread)
	{
		pThread->Stop(true);
	});

	recvMessage.ClearWindow();
}

// random bigger than current seq
TEST_F(NetTest, RecvMessageWindowMT2)
{
	Heap testHeap("test", GetSystemHeap());
	const int NUM_SEND_THREAD = 4;
	const int NUM_RECV_THREAD = 1;
	const uint32_t runningTime = TestScale * 1 * 60 * 1000;
	const auto MaxRandomizeSequence = 64;

	Net::RecvMsgWindow recvMessage(testHeap);
	std::atomic<uint64_t> releaseSequence(0);
	std::vector<Thread*> threads;

	for (int iThread = 0; iThread < NUM_SEND_THREAD; iThread++)
	{
		auto newThread = new FunctorThread([&](Thread *pThread)
		{
			MessageDataPtr pMsg;
			Result hr;

			while (!pThread->CheckKillEvent(DurationMS(0)))
			{
				uint16_t testSequence = 0;
				int randValue = rand();
				int multiplyer = 1;
				if(randValue & 0x1)
					multiplyer = -1;
				randValue >>= 1;
				// Randomly pick test sequence
				testSequence = (uint16_t)(recvMessage.GetBaseSequence() - multiplyer * (std::abs(randValue) % MaxRandomizeSequence));

				pMsg = NewMessage(testHeap, testSequence);
				hr = recvMessage.AddMsg(pMsg);
				if (hr == ResultCode::IO_SEQUENCE_OVERFLOW || ResultCode::SUCCESS_IO_PROCESSED_SEQUENCE)
				{
					pMsg = nullptr;
				}
				else
				{
					EXPECT_TRUE(pMsg == nullptr);
					GTEST_ASSERT_EQ(pMsg->GetReferenceCount(), 2);
					EXPECT_TRUE(MessageSequence::Difference(recvMessage.GetBaseSequence(), testSequence) <= recvMessage.GetAcceptableSequenceRange());
				}

				recvMessage.GetSyncMask();
				pMsg = nullptr;
			}
		});
		newThread->Start();
		threads.push_back(newThread);
	}

	for (int iThread = 0; iThread < NUM_RECV_THREAD; iThread++)
	{
		auto newThread = new FunctorThread([&](Thread *pThread)
		{
			Result hr;
			MessageDataPtr pResult;
			uint64_t sequence = releaseSequence.fetch_add(1, std::memory_order_relaxed);
			while (!pThread->CheckKillEvent(DurationMS(0)))
			{
				pResult = nullptr;
				hr = recvMessage.PopMsg(pResult);
				if (hr)
				{
					EXPECT_TRUE(pResult != nullptr);

					EXPECT_TRUE(MessageSequence::Difference(pResult->GetMessageHeader()->msgID.IDSeq.Sequence, (uint)sequence) == 0);
					pResult = nullptr;
					if ((sequence % 10000) == 0)
					{
						printf("Read Sequence: %lld\n", static_cast<unsigned long long>(sequence));
					}
					sequence = releaseSequence.fetch_add(1, std::memory_order_relaxed);
				}
				else
				{
					EXPECT_TRUE(pResult == nullptr);
					EXPECT_TRUE(!hr);
				}
			}
		});
		newThread->Start();
		threads.push_back(newThread);
	}

	ThisThread::SleepFor(DurationMS(runningTime));

	std::for_each(threads.begin(), threads.end(), [](Thread* pThread)
	{
		pThread->Stop(true);
	});

	recvMessage.ClearWindow();
}


TEST_F(NetTest, RecvMessageWindow2Simple)
{
    Heap testHeap("test", GetSystemHeap());

    Net::RecvMsgWindow2 recvMessage;
    uint16_t uiSequence = 0;

    for (int iTest = 0; iTest < 2048; iTest++)
    {
        auto NewMsg = NewMessage(testHeap, uiSequence++);
        auto hr = recvMessage.AddMsg(NewMsg->GetMessageHeader());
        if (iTest < recvMessage.GetAcceptableSequenceRange())
        {
            EXPECT_EQ(SF::ResultCode::SUCCESS, hr);
        }
        else
        {
            EXPECT_NE(SF::ResultCode::SUCCESS, hr);
        }
    }

    uiSequence = 0;
    for (int iTest = 0; iTest < 2048; iTest++)
    {
        Net::RecvMsgWindow2::MessageBuffer::ItemReadPtr messageData;
        Result hr = recvMessage.PopMsg(messageData);
        if (iTest < recvMessage.GetAcceptableSequenceRange())
        {
            EXPECT_TRUE(messageData);
            EXPECT_TRUE(hr);
            MessageHeader* pHeader = reinterpret_cast<MessageHeader*>(messageData.data());
            EXPECT_TRUE(MessageSequence::Difference(pHeader->msgID.IDSeq.Sequence, uiSequence++) == 0);
        }
        else
        {
            EXPECT_TRUE(!messageData);
            EXPECT_TRUE(!hr);
        }
    }
}

TEST_F(NetTest, RecvMessageWindow2Simple2)
{
    Heap testHeap("test", GetSystemHeap());
    Net::RecvMsgWindow2 recvMessage;
    uint16_t uiSequence = 0;
    uint16_t releaseSequence = 0;
    MessageDataPtr pResult, pNewMsg;
    Result hr;

    for (unsigned iTest = 0; iTest < TEST_COUNT; iTest++)
    {
        auto random = rand() % 2;
        switch (random)
        {
        case 0: // add
            pNewMsg = NewMessage(testHeap, uiSequence);
            hr = recvMessage.AddMsg(pNewMsg->GetMessageHeader());
            if (MessageSequence::Difference(uiSequence, recvMessage.GetBaseSequence()) < recvMessage.GetAcceptableSequenceRange())
            {
                EXPECT_TRUE(hr);
                uiSequence++;
            }
            else
            {
                EXPECT_TRUE(!hr);
            }
            break;
        case 1: // release
            Net::RecvMsgWindow2::MessageBuffer::ItemReadPtr messageData;
            hr = recvMessage.PopMsg(messageData);
            if (hr)
            {
                EXPECT_TRUE(messageData);
                MessageHeader* pHeader = reinterpret_cast<MessageHeader*>(messageData.data());
                EXPECT_TRUE(MessageSequence::Difference(pHeader->msgID.IDSeq.Sequence, releaseSequence++) == 0);
            }
            else
            {
                EXPECT_TRUE(pResult == nullptr);
                EXPECT_TRUE(!hr);
            }
            break;
        }

        recvMessage.GetSyncMask();
    }

    recvMessage.Reset();
}

TEST_F(NetTest, RecvMessageWindow2Simple3)
{
    Heap testHeap("test", GetSystemHeap());
    Net::RecvMsgWindow2 recvMessage;
    uint16_t uiSequence = 0;
    uint16_t releaseSequence = 0;
    MessageDataPtr pResult;
    Result hr;

    for (unsigned iTest = 0; iTest < TEST_COUNT; iTest++)
    {
        auto random = rand() % 2;
        switch (random)
        {
        case 0: // add
        {
            auto testSequence = uiSequence;
            if (rand() % 2)
            {
                testSequence = (uint16_t)std::abs(rand());
            }
            auto pNewMsg = NewMessage(testHeap, testSequence);
            hr = recvMessage.AddMsg(pNewMsg->GetMessageHeader());
            auto seqOffset = MessageSequence::Difference(testSequence, recvMessage.GetBaseSequence());
            if (seqOffset < recvMessage.GetAcceptableSequenceRange() && seqOffset >= 0)
            {
                EXPECT_TRUE(hr);
                uiSequence++;
            }
            else
            {
                EXPECT_TRUE(seqOffset < 0 || !hr);
            }
        }
        break;
        case 1: // release
            Net::RecvMsgWindow2::MessageBuffer::ItemReadPtr messageData;
            hr = recvMessage.PopMsg(messageData);
            if (hr)
            {
                EXPECT_TRUE(messageData);
                MessageHeader* pHeader = reinterpret_cast<MessageHeader*>(messageData.data());
                EXPECT_TRUE(MessageSequence::Difference(pHeader->msgID.IDSeq.Sequence, releaseSequence++) == 0);
            }
            else
            {
                EXPECT_TRUE(pResult == nullptr);
                EXPECT_TRUE(!hr);
            }
            break;
        }

        recvMessage.GetSyncMask();
    }

    recvMessage.Reset();
}




TEST_F(NetTest, RecvMessageWindow2OutOfRange)
{
    Heap testHeap("test", GetSystemHeap());

    Net::RecvMsgWindow2 recvMessage;
    uint16_t uiSequence = 0;
    const int MaxSequenceOffset = NET_SEQUENCE_MAX_DIFF;


    for (int iTest = 0; iTest < TEST_COUNT; iTest++, uiSequence++)
    {
        for (int testSequenceOffset = -MaxSequenceOffset; testSequenceOffset < MaxSequenceOffset; testSequenceOffset++)
        {
            auto testSequence = (int)uiSequence + testSequenceOffset;

            int diff = MessageSequence::Difference(testSequence, iTest);
            GTEST_ASSERT_EQ(diff, testSequenceOffset);
        }
    }


    uiSequence = 0;
    for (int iTest = 0; iTest < TEST_COUNT; iTest++, uiSequence++)
    {
        for (int testSequenceOffset = -MaxSequenceOffset; testSequenceOffset < MaxSequenceOffset; testSequenceOffset++)
        {
            int testSequence = (int)uiSequence + testSequenceOffset;
            MessageDataPtr pNewMsg = NewMessage(testHeap, testSequence);
            Result hr = recvMessage.AddMsg(pNewMsg->GetMessageHeader());
            if (testSequenceOffset < 0)
            {
                EXPECT_TRUE(hr == ResultCode::IO_SEQUENCE_OVERFLOW || hr == ResultCode::SUCCESS_IO_PROCESSED_SEQUENCE);
            }
            else if (testSequenceOffset > 0)
            {
                if (testSequenceOffset >= recvMessage.GetAcceptableSequenceRange())
                {
                    EXPECT_TRUE(hr == ResultCode::IO_SEQUENCE_OVERFLOW || hr == ResultCode::SUCCESS_IO_PROCESSED_SEQUENCE);
                }
                else
                {
                    EXPECT_TRUE(hr || hr == ResultCode::IO_SEQUENCE_OVERFLOW);
                }
            }
            else
            {
                EXPECT_TRUE(hr || hr == ResultCode::IO_SEQUENCE_OVERFLOW);
            }
        }

        Net::RecvMsgWindow2::MessageBuffer::ItemReadPtr messageData;
        auto hRes = recvMessage.PopMsg(messageData);
        if (messageData)
        {
            MessageHeader* pHeader = reinterpret_cast<MessageHeader*>(messageData.data());
            EXPECT_EQ(MessageSequence::Difference(pHeader->msgID.IDSeq.Sequence, uiSequence), 0);
        }
        else
        {
            EXPECT_FALSE(hRes);
        }
    }
}

TEST_F(NetTest, RecvMessageWindow2MT)
{
    Heap testHeap("test", GetSystemHeap());
    const int NUM_SEND_THREAD = 10;
    const int NUM_RECV_THREAD = 1;
    const int NumTry = 2;
    const uint32_t runningTime = TestScale * 1 * 60 * 1000;

    Net::RecvMsgWindow2 recvMessage;
    std::atomic<uint16_t> uiSequence(0);
    std::atomic<uint16_t> releaseSequence(0);
    std::vector<Thread*> threads;

    for (int iThread = 0; iThread < NUM_SEND_THREAD; iThread++)
    {
        auto newThread = new FunctorThread([&](Thread* pThread)
            {
                uint16_t sequence = uiSequence.fetch_add(1, std::memory_order_relaxed);
                MessageDataPtr pMsg;
                Result hr;

                while (!pThread->CheckKillEvent(DurationMS(0)))
                {
                    for (int iTry = 0; iTry < NumTry; iTry++)
                    {
                        pMsg = NewMessage(testHeap, sequence);
                        hr = recvMessage.AddMsg(pMsg->GetMessageHeader());
                        if (!hr)
                        {
                            pMsg = nullptr;
                        }
                        else
                        {
                            sequence = uiSequence.fetch_add(1, std::memory_order_relaxed);
                        }

                        recvMessage.GetSyncMask();
                        pMsg = nullptr;
                    }
                }
            });
        newThread->Start();
        threads.push_back(newThread);
    }

    for (int iThread = 0; iThread < NUM_RECV_THREAD; iThread++)
    {
        auto newThread = new FunctorThread([&](Thread* pThread)
            {
                Result hr;
                uint16_t sequence = releaseSequence.fetch_add(1, std::memory_order_relaxed);
                while (!pThread->CheckKillEvent(DurationMS(0)))
                {
                    Net::RecvMsgWindow2::MessageBuffer::ItemReadPtr messageData;
                    hr = recvMessage.PopMsg(messageData);
                    if (hr)
                    {
                        EXPECT_TRUE(messageData);
                        MessageHeader* pHeader = reinterpret_cast<MessageHeader*>(messageData.data());

                        EXPECT_TRUE(MessageSequence::Difference(pHeader->msgID.IDSeq.Sequence, sequence) == 0);
                        messageData.Reset();
                        sequence = releaseSequence.fetch_add(1, std::memory_order_relaxed);
                    }
                    else
                    {
                        EXPECT_FALSE(messageData);
                        EXPECT_FALSE(hr);
                    }
                }
            });
        newThread->Start();
        threads.push_back(newThread);
    }

    ThisThread::SleepFor(DurationMS(runningTime));

    std::for_each(threads.begin(), threads.end(), [](Thread* pThread)
        {
            pThread->Stop(true);
        });

    recvMessage.Reset();
}

// random bigger than current seq
TEST_F(NetTest, RecvMessageWindow2MT2)
{
    Heap testHeap("test", GetSystemHeap());
    const int NUM_SEND_THREAD = 4;
    const int NUM_RECV_THREAD = 1;
    const uint32_t runningTime = TestScale * 1 * 60 * 1000;
    const auto MaxRandomizeSequence = 64;

    Net::RecvMsgWindow2 recvMessage;
    std::atomic<uint64_t> releaseSequence(0);
    std::vector<Thread*> threads;

    for (int iThread = 0; iThread < NUM_SEND_THREAD; iThread++)
    {
        auto newThread = new FunctorThread([&](Thread* pThread)
            {
                MessageDataPtr pMsg;
                Result hr;

                while (!pThread->CheckKillEvent(DurationMS(0)))
                {
                    uint16_t testSequence = 0;
                    int randValue = rand();
                    int multiplyer = 1;
                    if (randValue & 0x1)
                        multiplyer = -1;
                    randValue >>= 1;
                    // Randomly pick test sequence
                    testSequence = (uint16_t)(recvMessage.GetBaseSequence() - multiplyer * (std::abs(randValue) % MaxRandomizeSequence));

                    pMsg = NewMessage(testHeap, testSequence);
                    hr = recvMessage.AddMsg(pMsg->GetMessageHeader());
                    if (hr == ResultCode::IO_SEQUENCE_OVERFLOW || ResultCode::SUCCESS_IO_PROCESSED_SEQUENCE)
                    {
                        pMsg = nullptr;
                    }
                    else
                    {
                        EXPECT_TRUE(pMsg == nullptr);
                        GTEST_ASSERT_EQ(pMsg->GetReferenceCount(), 2);
                        EXPECT_TRUE(MessageSequence::Difference(recvMessage.GetBaseSequence(), testSequence) <= recvMessage.GetAcceptableSequenceRange());
                    }

                    recvMessage.GetSyncMask();
                    pMsg = nullptr;
                }
            });
        newThread->Start();
        threads.push_back(newThread);
    }

    for (int iThread = 0; iThread < NUM_RECV_THREAD; iThread++)
    {
        auto newThread = new FunctorThread([&](Thread* pThread)
            {
                Result hr;
                uint64_t sequence = releaseSequence.fetch_add(1, std::memory_order_relaxed);
                while (!pThread->CheckKillEvent(DurationMS(0)))
                {
                    Net::RecvMsgWindow2::MessageBuffer::ItemReadPtr messageData;
                    hr = recvMessage.PopMsg(messageData);
                    if (hr)
                    {
                        EXPECT_TRUE(messageData);

                        MessageHeader* pHeader = reinterpret_cast<MessageHeader*>(messageData.data());
                        EXPECT_TRUE(MessageSequence::Difference(pHeader->msgID.IDSeq.Sequence, (uint)sequence) == 0);

                        if ((sequence % 10000) == 0)
                        {
                            printf("Read Sequence: %lld\n", static_cast<unsigned long long>(sequence));
                        }
                        sequence = releaseSequence.fetch_add(1, std::memory_order_relaxed);
                    }
                    else
                    {
                        EXPECT_FALSE(messageData);
                        EXPECT_FALSE(hr);
                    }
                }
            });
        newThread->Start();
        threads.push_back(newThread);
    }

    ThisThread::SleepFor(DurationMS(runningTime));

    std::for_each(threads.begin(), threads.end(), [](Thread* pThread)
        {
            pThread->Stop(true);
        });

    recvMessage.Reset();
}


TEST_F(NetTest, SendMessageWindowSimple)
{
	Heap testHeap("test", GetSystemHeap());

	Net::SendMsgWindow msgWindow(testHeap);
	

	for (uint16_t startSequence = 0; startSequence < Net::MessageWindow::MESSAGE_QUEUE_SIZE * 2; startSequence++)
	{

		for (int iTest = 0; iTest < Net::MessageWindow::MESSAGE_QUEUE_SIZE; iTest++)
		{
			auto pNewMsg = NewMessage(testHeap);
			auto hr = msgWindow.EnqueueMessage(Util::Time.GetTimeMs(), pNewMsg);
			if (iTest < msgWindow.GetAcceptableSequenceRange())
			{
				EXPECT_EQ(SF::ResultCode::SUCCESS, hr);
			}
			else
			{
				EXPECT_EQ(SF::ResultCode::IO_NOT_ENOUGH_WINDOWSPACE, hr);
			}
		}

		EXPECT_EQ(SF::ResultCode::SUCCESS, msgWindow.QueueReleasedSequence((uint16_t)msgWindow.GetHeadSequence(), 0));
        msgWindow.UpdateReleasedSequences();
		EXPECT_EQ(uint32_t(0), msgWindow.GetMsgCount());
	}

	SFLog(Net, Info, "Test Finished");
}


TEST_F(NetTest, SendMessageWindowSimple2)
{
	Heap testHeap("test", GetSystemHeap());

	Net::SendMsgWindow msgWindow(testHeap);


	for (uint16_t startSequence = 0; startSequence < Net::MessageWindow::MESSAGE_QUEUE_SIZE * 2; startSequence++)
	{
		auto randNum = Util::Random.Rand(Net::MessageWindow::MESSAGE_QUEUE_SIZE);
		for (int iTest = 0; (uint)iTest < randNum; iTest++)
		{
			auto pNewMsg = NewMessage(testHeap);
			auto hr = msgWindow.EnqueueMessage(Util::Time.GetTimeMs(), pNewMsg);
			if (iTest < msgWindow.GetAcceptableSequenceRange())
			{
				ASSERT_EQ(SF::ResultCode::SUCCESS, hr);
			}
			else
			{
				ASSERT_NE(SF::ResultCode::SUCCESS, hr);
			}
		}

		ASSERT_EQ(SF::ResultCode::SUCCESS, msgWindow.QueueReleasedSequence((uint16_t)(msgWindow.GetBaseSequence() + msgWindow.GetMsgCount()), 0));
        msgWindow.UpdateReleasedSequences();
		ASSERT_EQ(uint(0), msgWindow.GetMsgCount());
	}

	SFLog(Net, Info, "Test Finished");
}

