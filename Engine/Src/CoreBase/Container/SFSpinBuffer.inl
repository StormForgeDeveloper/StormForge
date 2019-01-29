////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2016 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Spin buffer for single in single out
//
////////////////////////////////////////////////////////////////////////////////



#define __BUFFERMODE__ SpinBuffer<T>::BUFFER

namespace SF {


		template <typename T>
		SpinBuffer<T>::SpinBuffer(void)
		{
			m_nWritePos = m_nReadPos = 0;
		}

		template <typename T>
		SpinBuffer<T>::~SpinBuffer(void)
		{

		}

		template <typename T>
		Result SpinBuffer<T>::Push(const T& item)
		{
			// check a condtion 
			if ((this->m_SpinBuffer[m_nWritePos].eBufferMode != __BUFFERMODE__::BUFFERSTATE_FREE))
			{
				return ResultCode::FAIL;
			}

			// Change a mode : free->write (writing now...)
			m_SpinBuffer[m_nWritePos].eBufferMode = __BUFFERMODE__::BUFFERSTATE_WRITE;	// W-1

			// Write to the SpinBuffer
			m_SpinBuffer[m_nWritePos].item = item;									// W-2

			int nBeforePos = m_nWritePos;

			m_nWritePos = (m_nWritePos + 1) % BUFFER_LENGTH;
			//if(BUFFER_LENGTH == ++m_nWritePos)  m_nWritePos = 0;

			// change a mode : write->Read (writing complete...)
			m_SpinBuffer[nBeforePos].eBufferMode = __BUFFERMODE__::BUFFERSTATE_READ;	// W-3

			// Writing success!
			return ResultCode::SUCCESS;
		}

		// Comsumer(reader) read from the Readbuffer
		template <typename T>
		Result SpinBuffer<T>::Pop(T& item)
		{
			// check a condtion 
			if ((this->m_SpinBuffer[m_nReadPos].eBufferMode != __BUFFERMODE__::BUFFERSTATE_READ))
			{
				return ResultCode::FAIL;
			}

			item = m_SpinBuffer[m_nReadPos].item;									// R-1

			// initializing
			//memset(&m_SpinBuffer[m_nReadPos].item, -1, sizeof(T));
			m_SpinBuffer[m_nReadPos].item = T();

			int nBeforePos = m_nReadPos;

			m_nReadPos = (m_nReadPos + 1) % BUFFER_LENGTH;
			//if(BUFFER_LENGTH == ++m_nReadPos)  m_nReadPos = 0;

			// change a mode
			m_SpinBuffer[nBeforePos].eBufferMode = __BUFFERMODE__::BUFFERSTATE_FREE;	// R-2

			// Reading success!
			return ResultCode::SUCCESS;
		}


}

#undef __BUFFERMODE_
