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

#include "Protocol/Message/LoginMsgClass.h"

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


const UINT TestScale = 5;
const UINT TEST_COUNT = 4000000 * TestScale;


MessageDataPtr NewMessage(IHeap& memoryManager, UINT sequenceID)
{
	Message::MessageData* pResult = Message::Login::LoginCmd::Create(memoryManager, 0, FixedString32("Conspiracy"), "11", "11");
	pResult->AssignSequence(sequenceID);

	return MessageDataPtr(pResult);
}


GTEST_TEST(NetTest, RecvMessageWindowSimple)
{
	Heap testHeap("test", GetSystemHeap());

	Net::RecvMsgWindow recvMessage(testHeap);
	uint16_t uiSequence = 0;

	for (int iTest = 0; iTest < 256; iTest++)
	{
		auto hr = recvMessage.AddMsg(NewMessage(testHeap, uiSequence++));
		if (iTest < recvMessage.GetWindowSize())
		{
			AssertRel(hr);
		}
		else
		{
			AssertRel(!hr);
		}
	}

	uiSequence = 0;
	for (int iTest = 0; iTest < 256; iTest++)
	{
		MessageDataPtr pResult;
		auto hr = recvMessage.PopMsg(pResult);
		if (iTest < recvMessage.GetWindowSize())
		{
			AssertRel(pResult != nullptr);
			AssertRel(hr);

			AssertRel(Message::SequenceDifference(pResult->GetMessageHeader()->msgID.IDSeq.Sequence, uiSequence++) == 0);
		}
		else
		{
			AssertRel(pResult == nullptr);
			AssertRel(!hr);
		}
	}
}

GTEST_TEST(NetTest, RecvMessageWindowSimple2)
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
			hr = recvMessage.AddMsg(NewMessage(testHeap, uiSequence));
			if (Message::SequenceDifference(uiSequence, recvMessage.GetBaseSequence()) < recvMessage.GetWindowSize())
			{
				AssertRel(hr);
				uiSequence++;
			}
			else
			{
				AssertRel(!hr);
			}
			break;
		case 1: // release
			pResult = nullptr;
			hr = recvMessage.PopMsg(pResult);
			if (hr)
			{
				AssertRel(pResult != nullptr);

				AssertRel(Message::SequenceDifference(pResult->GetMessageHeader()->msgID.IDSeq.Sequence, releaseSequence++) == 0);
			}
			else
			{
				AssertRel(pResult == nullptr);
				AssertRel(!hr);
			}
			break;
		}

		recvMessage.GetSyncMask();
	}

	recvMessage.ClearWindow();
}

GTEST_TEST(NetTest, RecvMessageWindowSimple3)
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
				testSequence = std::abs(rand());
			}
			hr = recvMessage.AddMsg(NewMessage(testHeap, testSequence));
			auto seqOffset = Message::SequenceDifference(testSequence, recvMessage.GetBaseSequence());
			if (seqOffset < recvMessage.GetWindowSize() && seqOffset >= 0)
			{
				AssertRel(hr);
				uiSequence++;
			}
			else
			{
				AssertRel(seqOffset < 0 || !hr);
			}
		}
		break;
		case 1: // release
			pResult = nullptr;
			hr = recvMessage.PopMsg(pResult);
			if (hr)
			{
				AssertRel(pResult != nullptr);

				AssertRel(Message::SequenceDifference(pResult->GetMessageHeader()->msgID.IDSeq.Sequence, releaseSequence++) == 0);
			}
			else
			{
				AssertRel(pResult == nullptr);
				AssertRel(!hr);
			}
			break;
		}

		recvMessage.GetSyncMask();
	}

	recvMessage.ClearWindow();
}



INT MySequenceDifference(uint seq1, uint seq2)
{
	const int SEQDIFF_MAX = NET_SEQUENCE_MASK >> 1;
	const int SEQDIFF_MIN = (-SEQDIFF_MAX - 1);

	//NET_SEQUEUCN_BITS
	seq1 = NET_SEQUENCE_MASK & seq1;
	seq2 = NET_SEQUENCE_MASK & seq2;
	auto diff = (INT)(seq1 - seq2);
	if (diff > SEQDIFF_MAX)
		diff -= NET_SEQUENCE_MASK + 1;
	else if (diff < SEQDIFF_MIN)
		diff += NET_SEQUENCE_MASK + 1;

	return diff;
}


GTEST_TEST(NetTest, RecvMessageWindowOutOfRange)
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

			int diff = MySequenceDifference(testSequence, iTest);
			GTEST_ASSERT_EQ(diff, testSequenceOffset);
		}
	}


	uiSequence = 0;
	for (int iTest = 0; iTest < TEST_COUNT; iTest++, uiSequence++)
	{
		for (int testSequenceOffset = -MaxSequenceOffset; testSequenceOffset < MaxSequenceOffset; testSequenceOffset++)
		{
			auto testSequence = (int)uiSequence + testSequenceOffset;
			auto hr = recvMessage.AddMsg(NewMessage(testHeap, testSequence));
			if (testSequenceOffset < 0)
			{
				GTEST_ASSERT_EQ(hr, ResultCode::SUCCESS_IO_PROCESSED_SEQUENCE);
			}
			else if (testSequenceOffset > 0)
			{
				if (testSequenceOffset >= recvMessage.GetWindowSize())
				{
					GTEST_ASSERT_EQ(hr, ResultCode::IO_SEQUENCE_OVERFLOW);
				}
				else
				{
					GTEST_ASSERT_EQ(hr, ResultCode::SUCCESS);
				}
			}
			else
			{
				GTEST_ASSERT_EQ(hr, ResultCode::SUCCESS);
			}
		}

		MessageDataPtr pIMsg;
		recvMessage.PopMsg(pIMsg);
		GTEST_ASSERT_EQ(Message::SequenceDifference(pIMsg->GetMessageHeader()->msgID.IDSeq.Sequence, uiSequence), 0);
	}
}

GTEST_TEST(NetTest, RecvMessageWindowMT)
{
	Heap testHeap("test", GetSystemHeap());
	const int NUM_SEND_THREAD = 10;
	const int NUM_RECV_THREAD = 1;
	const int NumTry = 2;
	const UINT runningTime = TestScale * 1 * 60 * 1000;

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
					Assert(hr != ResultCode::SUCCESS_IO_PROCESSED_SEQUENCE);
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
					AssertRel(pResult != nullptr);

					AssertRel(Message::SequenceDifference(pResult->GetMessageHeader()->msgID.IDSeq.Sequence, sequence) == 0);
					pResult = nullptr;
					sequence = releaseSequence.fetch_add(1, std::memory_order_relaxed);
				}
				else
				{
					AssertRel(pResult == nullptr);
					AssertRel(!hr);
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
GTEST_TEST(NetTest, RecvMessageWindowMT2)
{
	Heap testHeap("test", GetSystemHeap());
	const int NUM_SEND_THREAD = 5;
	const int NUM_RECV_THREAD = 1;
	const UINT runningTime = TestScale * 1 * 60 * 1000;
	const auto MaxRandomizeSequence = NET_SEQUENCE_MAX_DIFF >> 2;

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
				testSequence = recvMessage.GetBaseSequence() - multiplyer * (std::abs(randValue) % MaxRandomizeSequence);

				pMsg = NewMessage(testHeap, testSequence);
				hr = recvMessage.AddMsg(pMsg);
				if (hr == ResultCode::IO_SEQUENCE_OVERFLOW || ResultCode::SUCCESS_IO_PROCESSED_SEQUENCE)
				{
				}
				else
				{
					AssertRel(pMsg == nullptr);
					GTEST_ASSERT_EQ(pMsg->GetReferenceCount(), 2);
					AssertRel(Message::SequenceDifference(recvMessage.GetBaseSequence(), testSequence) <= recvMessage.GetWindowSize());
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
					AssertRel(pResult != nullptr);

					AssertRel(Message::SequenceDifference(pResult->GetMessageHeader()->msgID.IDSeq.Sequence, (uint)sequence) == 0);
					pResult = nullptr;
					if ((sequence % 10000) == 0)
					{
						printf("Read Sequence: %lld\n", sequence);
					}
					sequence = releaseSequence.fetch_add(1, std::memory_order_relaxed);
				}
				else
				{
					AssertRel(pResult == nullptr);
					AssertRel(!hr);
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

