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
    public unsafe class BinaryMemoryWriter
    {
        // memory buffer
        private byte[] m_MemBuffer;
        private int m_CurPosition;

        public int Length { get { return m_MemBuffer != null ? m_MemBuffer.Length : 0; } }
        public int Position { get { return m_CurPosition; } }
        public int RemainLength { get { return Length - m_CurPosition; } }

        public BinaryMemoryWriter(byte[] memBuffer)
        {
            m_MemBuffer = memBuffer;
            m_CurPosition = 0;
        }

        private void Write(byte* pSrcBuff, int size)
        {
            if ((m_CurPosition + size) > m_MemBuffer.Length)
                throw new System.Exception("BinaryMemoryWriter: Out of destination memory space");

            fixed (byte* pDestData = &(m_MemBuffer[m_CurPosition]))
            {
                m_CurPosition += size;

                UInt32* pDest = (UInt32*)pSrcBuff;
                UInt32* pSrc = (UInt32*)pDestData;
                while (size > 4)
                {
                    *pDest++ = *pSrc++;
                    size -= 4;
                }

                pSrcBuff = (Byte*)pDest;
                byte* pSrcData = (Byte*)pSrc;
                while (size > 0)
                {
                    *pSrcBuff++ = *pSrcData++;
                    size--;
                }
            }
        }

        private void Write16(byte* pSrcBuff)
        {
            if ((m_CurPosition + 2) > m_MemBuffer.Length)
                throw new System.Exception("BinaryMemoryWriter: Out of destination memory space");

            fixed (byte* pData = &(m_MemBuffer[m_CurPosition]))
            {
                m_CurPosition += 2;
                *(((UInt16*)pData)) = *(UInt16*)pSrcBuff;
            }
        }

        private void Write32(byte* pSrcBuff)
        {
            if ((m_CurPosition + 4) > m_MemBuffer.Length)
                throw new System.Exception("BinaryMemoryWriter: Out of destination memory space");

            fixed (byte* pData = &(m_MemBuffer[m_CurPosition]))
            {
                m_CurPosition += 4;
                *(((UInt32*)pData)) = *(UInt32*)pSrcBuff;
            }
        }

        private void Write64(byte* pSrcBuff)
        {
            if ((m_CurPosition + 8) > m_MemBuffer.Length)
                throw new System.Exception("BinaryMemoryWriter: Out of destination memory space");

            fixed (byte* pData = &(m_MemBuffer[m_CurPosition]))
            {
                m_CurPosition += 8;
                *(((UInt64*)pData)) = *(UInt64*)pSrcBuff;
            }
        }

        public void Write( Byte value )
        {
            if ((m_CurPosition + 1) > m_MemBuffer.Length)
                throw new System.Exception("BinaryMemReader: No data is available");

            m_MemBuffer[m_CurPosition] = value;
            m_CurPosition++;
        }

        public void Write(Boolean value)
        {
            Write((byte)(value ? 1 : 0));
        }

        public void Write( Int16 value )
        {
            Write16((byte*)&value);
        }

        public void Write( UInt16 value )
        {
            Write16((byte*)&value);
        }

        public void Write( Int32 value)
        {
            Write32((byte*)&value);
        }

        public void Write( UInt32 value )
        {
            Write32((byte*)&value);
        }

        public void Write( Int64 value )
        {
            Write64((byte*)&value);
        }

        public void Write(UInt64 value)
        {
            Write64((byte*)&value);
        }

        public void Write( float value )
        {
            Write32((byte*)&value);
        }

        public void Write(char[] value)
        {
            fixed (char* pDest = &(value[0]))
            {
                Write((byte*)pDest, value.Length);
            }
        }

        public void Write(byte[] value)
        {
            fixed (byte* pDest = &(value[0]))
            {
                Write(pDest, value.Length);
            }
        }

        // Seek
        public void Seek(int newPos)
        {
            Debug.Assert(newPos >= 0 && newPos < m_MemBuffer.Length);
            m_CurPosition = newPos;
        }

    };

}
