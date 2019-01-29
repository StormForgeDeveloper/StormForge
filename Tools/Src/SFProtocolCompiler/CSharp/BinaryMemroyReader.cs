////////////////////////////////////////////////////////////////////////////////
// 
// 
// Author : KyungKun Ko
//
// Description : network packet class
//	
//
////////////////////////////////////////////////////////////////////////////////

using System;
using System.Diagnostics;


namespace BR
{

    // Unpacked packet header
    public unsafe class BinaryMemoryReader
    {
        // memory buffer
        private byte[]  m_MemBuffer;
        private int m_CurPosition;

        public int Length { get { return m_MemBuffer != null ? m_MemBuffer.Length : 0; } }
        public int Position { get { return m_CurPosition; } }
        public int RemainLength { get { return Length - m_CurPosition; } }

        public BinaryMemoryReader(byte[] memBuffer)
        {
            m_MemBuffer = memBuffer;
            m_CurPosition = 0;
        }

        private void Read(byte* pDestBuff, int size)
        {
            if ((m_CurPosition + size) > m_MemBuffer.Length)
                throw new System.Exception("BinaryMemReader: No data is available");

            fixed (byte* pSrcDataOrg = &(m_MemBuffer[m_CurPosition]))
            {
                m_CurPosition += size;

                UInt32* pDest = (UInt32*)pDestBuff;
                UInt32* pSrc = (UInt32*)pSrcDataOrg;
                while (size > 4)
                {
                    *pDest++ = *pSrc++;
                    size -= 4;
                }

                pDestBuff = (Byte*)pDest;
                byte *pSrcData = (Byte*)pSrc;
                while (size > 0)
                {
                    *pDestBuff++ = *pSrcData++;
                    size--;
                }
            }
        }

        private void Read16(byte* pDestBuff)
        {
            if ((m_CurPosition + 2) > m_MemBuffer.Length)
                throw new System.Exception("BinaryMemoryWriter: Out of destination memory space");

            fixed (byte* pData = &(m_MemBuffer[m_CurPosition]))
            {
                m_CurPosition += 2;
                *(((UInt16*)pDestBuff)) = *(UInt16*)pData;
            }
        }

        private void Read32(byte* pDestBuff)
        {
            if ((m_CurPosition + 4) > m_MemBuffer.Length)
                throw new System.Exception("BinaryMemoryWriter: Out of destination memory space");

            fixed (byte* pData = &(m_MemBuffer[m_CurPosition]))
            {
                m_CurPosition += 4;
                *(((UInt32*)pDestBuff)) = *(UInt32*)pData;
            }
        }

        private void Read64(byte* pDestBuff)
        {
            if ((m_CurPosition + 8) > m_MemBuffer.Length)
                throw new System.Exception("BinaryMemoryWriter: Out of destination memory space");

            fixed (byte* pData = &(m_MemBuffer[m_CurPosition]))
            {
                m_CurPosition += 8;
                *(((UInt64*)pDestBuff)) = *(UInt64*)pData;
            }
        }

        public Byte ReadByte()
        {
            if ((m_CurPosition + 1) > m_MemBuffer.Length)
                throw new System.Exception("BinaryMemReader: No data is available");

            byte value = m_MemBuffer[m_CurPosition];
            m_CurPosition++;
            return value;
        }

        public Byte ReadBoolean()
        {
            return ReadByte();
        }

        public Int16 ReadInt16()
        {
            Int16 value;
            Read16((byte*)&value);
            return value;
        }

        public UInt16 ReadUInt16()
        {
            UInt16 value;
            Read16((byte*)&value);
            return value;
        }

        public Int32 ReadInt32()
        {
            Int32 value;
            Read32((byte*)&value);
            return value;
        }

        public UInt32 ReadUInt32()
        {
            UInt32 value;
            Read32((byte*)&value);
            return value;
        }

        public Int64 ReadInt64()
        {
            Int64 value;
            Read64((byte*)&value);
            return value;
        }

        public UInt64 ReadUInt64()
        {
            UInt64 value;
            Read64((byte*)&value);
            return value;
        }

        public float ReadSingle()
        {
            float value;
            Read32((byte*)&value);
            return value;
        }

        public char[] ReadChars(int count)
        {
            char[] value = new char[count];
            fixed (char* pDest = &(value[0]))
            {
                Read((byte*)pDest, count);
            }
            return value;
        }

        public byte[] ReadBytes(int count)
        {
            byte[] value = new byte[count];
            fixed (byte* pDest = &(value[0]))
            {
                Read(pDest, count);
            }
            return value;
        }

        // Seek
        public void Seek(int newPos)
        {
            Debug.Assert(newPos >= 0 && newPos < m_MemBuffer.Length);
            m_CurPosition = newPos;
        }
    };


}
