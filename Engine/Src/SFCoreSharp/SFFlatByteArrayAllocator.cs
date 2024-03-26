////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Flatbuffer serialization utility
//	
//
////////////////////////////////////////////////////////////////////////////////

using System;
using System.Collections.Generic;
using System.IO;
using Google.FlatBuffers;


#nullable enable
namespace SF.Flat
{
    public class ReadByteArrayAllocator : Google.FlatBuffers.ByteBufferAllocator
    {
        byte[] m_Buffer;
        int m_Pos;
        int m_Count;

        public ReadByteArrayAllocator(byte[] buffer, int startIndex = 0, int count = -1)
        {
            Buffer = buffer;
            m_Buffer = buffer;
            m_Pos = startIndex;
            m_Count = count >= 0 ? count : (buffer.Length - startIndex);
            InitBuffer();
        }

        public override void GrowFront(int newSize)
        {
            throw new Exception("This is readyonly, Grow is not supported");
        }

#if ENABLE_SPAN_T && (UNSAFE_BYTEBUFFER || NETSTANDARD2_1)
		public override Span<byte> Span => new Span<byte>(m_Buffer, m_Pos, m_Count);
		public override ReadOnlySpan<byte> ReadOnlySpan => new ReadOnlySpan<byte>(m_Buffer, m_Pos, m_Count);
		public override Memory<byte> Memory => new Memory<byte>(m_Buffer, m_Pos, m_Count);
		public override ReadOnlyMemory<byte> ReadOnlyMemory => new ReadOnlyMemory<byte>(m_Buffer, m_Pos, m_Count);
#endif
        private void InitBuffer()
        {
            Length = m_Count;
        }
    }


}

#nullable restore
