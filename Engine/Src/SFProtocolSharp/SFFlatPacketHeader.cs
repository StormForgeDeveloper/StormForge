
using System.Drawing;
using System.Runtime.InteropServices;

namespace SF.Flat
{
    public struct PacketHeader
    {
        static public readonly int HeaderSize = 6;

        public ushort Size; // Size
        public ushort Signature; // Signature
        public ushort RequestId; // Signature


        public void WriteHeader(Google.FlatBuffers.FlatBufferBuilder buffer)
        {
            // Update size
            Size = (ushort)(buffer.DataBuffer.Length - buffer.DataBuffer.Position + HeaderSize);

            buffer.AddUshort(RequestId); buffer.DataBuffer.Position -= sizeof(ushort);
            buffer.AddUshort(Size); buffer.DataBuffer.Position -= sizeof(ushort);
            buffer.AddUshort(Signature); buffer.DataBuffer.Position -= sizeof(ushort);
        }

        public void ReadHeader(Google.FlatBuffers.ByteBuffer buffer)
        {
            Signature = buffer.GetUshort(0);
            Size = buffer.GetUshort(2);
            RequestId = buffer.GetUshort(4);
            buffer.Position += HeaderSize;
        }
    }

    public static class PacketSignature
    {
        public static ushort Login = 0x1010;
        public static ushort Telemetry = 0x1111;
    }
}
