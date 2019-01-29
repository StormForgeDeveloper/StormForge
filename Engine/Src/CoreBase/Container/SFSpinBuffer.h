////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2013 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Spin buffer for single in single out
////////////////////////////////////////////////////////////////////////////////


#pragma once

#include "SFTypedefs.h"

namespace SF {



		//////////////////////////////////////////////////////////////////////////////////
		//
		//	Spin Buffer Class
		//

		template <typename T>
		class SpinBuffer
		{
			enum
			{
				BUFFER_LENGTH = 4,
			};

			struct BUFFER
			{
				// Buffer State 
				typedef enum
				{
					BUFFERSTATE_WRITE,	// Write Buffer State
					BUFFERSTATE_READ,	// Read Buffer State
					BUFFERSTATE_FREE,	// Free Buffer State
				} MODE;

				MODE eBufferMode; // WRITE, READ, FREE

				T item;

				BUFFER::BUFFER()
				{
					// initializing Buffer state as Free
					eBufferMode = BUFFERSTATE_FREE;
				}
			};

		private:
			// Spin Buffer
			BUFFER m_SpinBuffer[BUFFER_LENGTH];

			// Spin Index
			int m_nWritePos;
			int m_nReadPos;

		public:
			// Constructor / Destructor
			SpinBuffer();
			~SpinBuffer();

		public:
			// Public Interface
				// Producer(writer) write 
			Result Push(const T& item);

			// Comsumer(reader) read 
			Result Pop(T& item);
		};



} // namespace SF


#include "SFSpinBuffer.inl"
