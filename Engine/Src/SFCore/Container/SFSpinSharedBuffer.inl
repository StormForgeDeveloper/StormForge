////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2013 Kyungkun Ko
// 
// Author : KyungKun, Ko
//
// Description : Spin shared buffer for multithired thread 
//
////////////////////////////////////////////////////////////////////////////////


namespace SF {


		template <class ItemType>
		SpinSharedBuffer<ItemType>::SpinSharedBuffer(IHeap& memoryManager, uint BufferCount)
			: m_BufferCount(0)
			, m_SpinBuffer(nullptr)
			, m_AccessPosition(0)
			, m_UsedBufferCount(0)
			, m_Heap(memoryManager)
		{
			if (BufferCount > 0)
				SetBufferCount(BufferCount);
		}

		template <class ItemType>
		SpinSharedBuffer<ItemType>::~SpinSharedBuffer(void)
		{
			if (m_SpinBuffer)
				GetHeap().Delete(m_SpinBuffer);
		}

		// Set buffer count, all pervious buffer data will be lost
		template <class ItemType>
		Result SpinSharedBuffer<ItemType>::SetBufferCount(uint BufferCount)
		{
			if (BufferCount == 0)
				return ResultCode::INVALID_ARG;

			if (m_SpinBuffer)
				GetHeap().Delete(m_SpinBuffer);

			m_BufferCount = Util::NearPowerOf2(BufferCount);

			m_SpinBuffer = new Buffer[m_BufferCount];
			if (m_SpinBuffer == nullptr)
				return ResultCode::OUT_OF_MEMORY;

			return ResultCode::SUCCESS;
		}

		// Get buffer count
		template <class ItemType>
		uint SpinSharedBuffer<ItemType>::GetBufferCount()
		{
			return m_BufferCount;
		}

		// Get used buffer count
		template <class ItemType>
		CounterType SpinSharedBuffer<ItemType>::GetUsedBufferCount()
		{
			return m_UsedBufferCount;
		}

		// Try to get one buffer while given times
		template <class ItemType>
		Result SpinSharedBuffer<ItemType>::TryAllocBuffer(INT iTryCount, ItemType* &pBuffer)
		{
			if (m_SpinBuffer == nullptr)
				return ResultCode::INVALID_ARG;

			// get access ticket
			CounterType myTicket = m_AccessPosition.fetch_add(1, std::memory_order_relaxed) + 1;

			// Calculate access position
			CounterType accessPos = myTicket % m_BufferCount;

			INT iTry = 0;
			auto expected = Buffer::STATE_USE;
			do {
				// If i didn't get it's access right then reticketing new one
				while (m_SpinBuffer[accessPos].State.load(std::memory_order_relaxed) != Buffer::STATE_FREE)
				{
					// Try limit
					iTry++;
					if (iTry > iTryCount)
						return ResultCode::FAIL;

					// if enguaged to maximum buffer state
					if (m_UsedBufferCount >= m_BufferCount)
						return ResultCode::OUT_OF_MEMORY;

					myTicket = m_AccessPosition.fetch_add(1, std::memory_order_relaxed) + 1;
					accessPos = myTicket % m_BufferCount;
				}

				expected = Buffer::STATE_FREE;
				//} while( _InterlockedCompareExchange( &m_SpinBuffer[accessPos].State, Buffer::STATE_USE, Buffer::STATE_FREE ) != Buffer::STATE_FREE );
			} while (!m_SpinBuffer[accessPos].State.compare_exchange_weak(expected, Buffer::STATE_USE, std::memory_order_release, std::memory_order_relaxed));

			pBuffer = &m_SpinBuffer[accessPos].Data;

			// Increase used buffer count
			m_UsedBufferCount.fetch_add(1, std::memory_order_relaxed);

			// Writing success!
			return ResultCode::SUCCESS;
		}

		// Get free buffer
		template <class ItemType>
		Result SpinSharedBuffer<ItemType>::AllocBuffer(ItemType* &pBuffer)
		{
			if (m_SpinBuffer == nullptr)
				return ResultCode::INVALID_ARG;

			// get access ticket
			CounterType myTicket = m_AccessPosition.fetch_add(1, std::memory_order_relaxed) + 1;

			// Calculate access position
			CounterType accessPos = myTicket % m_BufferCount;

			INT iTry = 0;
			auto expected = Buffer::STATE_FREE;
			do {
				// If i didn't get it's access right then reticketing new one
				while (m_SpinBuffer[accessPos].State.load(std::memory_order_relaxed) != Buffer::STATE_FREE)
				{
					iTry++;
					// So many try sleep some
					if (iTry > 5)
						ThisThread::SleepFor(DurationMS(0));


					myTicket = m_AccessPosition.fetch_add(1, std::memory_order_relaxed) + 1;
					accessPos = myTicket % m_BufferCount;
				}
				//} while( _InterlockedCompareExchange( &m_SpinBuffer[accessPos].State, Buffer::STATE_USE, Buffer::STATE_FREE ) != Buffer::STATE_FREE );
				expected = Buffer::STATE_FREE;
			} while (!m_SpinBuffer[accessPos].State.compare_exchange_weak(expected, Buffer::STATE_USE, std::memory_order_release, std::memory_order_relaxed));

			// Increase used buffer count
			m_UsedBufferCount.fetch_add(1, std::memory_order_release);

			// Writing success!
			return ResultCode::SUCCESS;
		}

		// Free given buffer
		template <class ItemType>
		Result SpinSharedBuffer<ItemType>::FreeBuffer(ItemType* pBuffer)
		{
			if (pBuffer == NULL)
				return ResultCode::FAIL;

			// Offset calculation for Buffer
			Buffer *pBufferPtr = (Buffer*)(((uint8_t*)pBuffer) + (int64_t)(&m_SpinBuffer[0]) - (int64_t)(&m_SpinBuffer[0].Data));

			if (pBufferPtr < m_SpinBuffer || pBufferPtr >(m_SpinBuffer + m_BufferCount))
				return ResultCode::INVALID_ARG;

			pBufferPtr->State.store(Buffer::STATE_FREE, std::memory_order_relaxed);

			m_UsedBufferCount.fetch_sub(1, std::memory_order_relaxed);

			return ResultCode::SUCCESS;
		}




}

