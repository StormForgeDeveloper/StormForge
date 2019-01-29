////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2016 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Object interface
//	
//
////////////////////////////////////////////////////////////////////////////////

using System;
using System.IO;

namespace SF
{
    /// <summary>
    /// Engine object interface
    /// </summary>
    public class SFMemoryStream : MemoryStream
    {
        public SFMemoryStream()
        {

        }

        public SFMemoryStream(byte[] buffer)
            : base(buffer)
        {

        }

        public void Write(byte value)
        {
            WriteByte((byte)value);
        }

        public void Write(Int16 value)
        {
            WriteByte((byte)value);
            WriteByte((byte)(value >> 8));
        }

        public void Write(UInt16 value)
        {
            WriteByte((byte)value);
            WriteByte((byte)(value >> 8));
        }

        public void Write(int value)
        {
            WriteByte((byte)value);
            WriteByte((byte)(value >> 8));
            WriteByte((byte)(value >> 16));
            WriteByte((byte)(value >> 24));
        }

        public void Write(uint value)
        {
            WriteByte((byte)value);
            WriteByte((byte)(value >> 8));
            WriteByte((byte)(value >> 16));
            WriteByte((byte)(value >> 24));
        }

        public void Write(Int64 value)
        {
            Write((uint)value);
            Write((uint)(value >> 32));
        }

        public void Write(UInt64 value)
        {
            Write((uint)value);
            Write((uint)(value >> 32));
        }

    }

}
