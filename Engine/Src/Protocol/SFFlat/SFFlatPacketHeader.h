#pragma once


namespace SF
{
#pragma pack(push, 2)
    union SFFlatPacketHeader
    {
        static constexpr uint HeaderSize = 6;

        uint16_t Signature;
        uint16_t Size;
        uint16_t RequestId;

        void WriteHeader(flatbuffers::FlatBufferBuilder& buffer)
        {
            // Update size
            Size = (uint16_t)(buffer.GetSize() + HeaderSize);

            buffer.PushBytes((const uint8_t*)&RequestId, sizeof(uint16_t));
            buffer.PushBytes((const uint8_t*)&Size, sizeof(uint16_t));
            buffer.PushBytes((const uint8_t * )&Signature, sizeof(uint16_t));
        }

        void ReadHeader(const Array<uint8_t>& buffer)
        {
            uint16_t* curPtr = reinterpret_cast<uint16_t*>(buffer.data());

            Signature = *curPtr++;
            Size = *curPtr++;
            RequestId = *curPtr++;
        }
    };
#pragma pack(pop)

    class SFFlatPacketSignature
    {
    public:
        static constexpr uint16_t Login = 0x1010;
        static constexpr uint16_t Telemetry = 0x1111;
    };
}

