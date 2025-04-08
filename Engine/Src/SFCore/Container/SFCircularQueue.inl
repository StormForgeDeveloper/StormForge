////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2016 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Circular queue for multithread
//
////////////////////////////////////////////////////////////////////////////////


namespace SF {

		template <typename T, int SIZE_BUFFER>
		CircularQueue<T, SIZE_BUFFER>::CircularQueue()
			: m_nReadPtr(0), m_nWritePtr(0), m_nItemCount(0)
		{
            // TODO: Need to check POD
			memset(m_Buffer, 0, sizeof(m_Buffer));
		}

		template <typename T, int SIZE_BUFFER>
		CircularQueue<T, SIZE_BUFFER>::~CircularQueue()
		{
		}

		// Clear all items
		template <typename T, int SIZE_BUFFER>
		inline void CircularQueue<T, SIZE_BUFFER>::ClearQueue()
		{
			m_nReadPtr = m_nWritePtr = m_nItemCount = 0;
            // TODO: Need to check POD
			memset(m_Buffer, 0, sizeof(m_Buffer));
		}

		template <typename T, int SIZE_BUFFER>
		bool CircularQueue<T, SIZE_BUFFER>::IsFull()
		{
			if (m_nItemCount != SIZE_BUFFER)
			{
				return false;
			}

			return true;
		}

		template <typename T, int SIZE_BUFFER>
		bool CircularQueue<T, SIZE_BUFFER>::IsEmpty()
		{
			return m_nItemCount == 0;
		}


		template <typename T, int SIZE_BUFFER>
		Result CircularQueue<T, SIZE_BUFFER>::Enqueue(T&& item)
		{
			if (IsFull())
			{
				return ResultCode::FAIL;
			}

			m_Buffer[m_nWritePtr] = Forward<T>(item);

			m_nWritePtr = (m_nWritePtr + 1) % SIZE_BUFFER;

			m_nItemCount++;

			return ResultCode::SUCCESS;
		}

		template <typename T, int SIZE_BUFFER>
		Result CircularQueue<T, SIZE_BUFFER>::Enqueue(const T& item)
		{
			if (IsFull())
			{
				return ResultCode::FAIL;
			}

			m_Buffer[m_nWritePtr] = item;

			m_nWritePtr = (m_nWritePtr + 1) % SIZE_BUFFER;

			m_nItemCount++;

			return ResultCode::SUCCESS;
		}

		template <typename T, int SIZE_BUFFER>
		inline Result CircularQueue<T, SIZE_BUFFER>::Dequeue(T &item)
		{
			if (m_nItemCount == 0)
			{
				return ResultCode::FAIL;
			}

			item = Forward<T>(m_Buffer[m_nReadPtr]);

			m_Buffer[m_nReadPtr] = T{};

			m_nReadPtr = (m_nReadPtr + 1) % SIZE_BUFFER;
			m_nItemCount--;

			return ResultCode::SUCCESS;
		}

		template <typename T, int SIZE_BUFFER>
		inline const T& CircularQueue<T, SIZE_BUFFER>::operator[](int iIndex)
		{
			static const T dummy{};
			if (int(m_nItemCount) <= iIndex)
			{
				// out of bound
				assert(false);
				return dummy;
			}

			auto readIndex = (m_nReadPtr + iIndex) % SIZE_BUFFER;
			return m_Buffer[readIndex];
		}

		template <typename T, int SIZE_BUFFER>
		inline void CircularQueue<T, SIZE_BUFFER>::ReverseForeach(uint from, uint count, std::function<bool(const T& item)> func)
		{
			// nothing to process
			if (m_nItemCount <= from)
				return;

			int iCurPos = m_nWritePtr - from - 1;
			if (iCurPos < 0)
				iCurPos += SIZE_BUFFER;

			for (uint numItem = 0; numItem < count; numItem++, iCurPos--)
			{
				if (iCurPos < 0)
					iCurPos += SIZE_BUFFER;

				if (!func(m_Buffer[iCurPos]))
					return;

				// If we've done, break
				if (iCurPos == m_nReadPtr)
					break;
			}
		}

		template <typename T, int SIZE_BUFFER>
		inline void CircularQueue<T, SIZE_BUFFER>::ReverseForeach(uint from, uint count, std::function<bool(const T& item)> func) const
		{
			const_cast<CircularQueue<T, SIZE_BUFFER>*>(this)->ReverseForeach(from, count, func);
		}

        template <typename T, int SIZE_BUFFER>
        inline void CircularQueue<T, SIZE_BUFFER>::Foreach(uint from, uint count, std::function<bool(const T& item)> func)
        {
            // nothing to process
            if (m_nItemCount <= from)
                return;

            int iCurPos = m_nReadPtr + from;

            for (uint numItem = 0; numItem < count; numItem++, iCurPos++)
            {
                iCurPos = iCurPos % SIZE_BUFFER;

                // If we've done, break
                if (iCurPos == m_nWritePtr)
                    break;

                if (!func(m_Buffer[iCurPos]))
                    return;
            }
        }

        template <typename T, int SIZE_BUFFER>
        inline void CircularQueue<T, SIZE_BUFFER>::Foreach(uint from, uint count, std::function<bool(const T& item)> func) const
        {
            const_cast<CircularQueue<T, SIZE_BUFFER>*>(this)->Foreach(from, count, func);
        }


}
