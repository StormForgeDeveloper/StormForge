// <auto-generated>
//  automatically generated by the FlatBuffers compiler, do not modify
// </auto-generated>

namespace SF.Flat.Game
{

using global::System;
using global::System.Collections.Generic;
using global::Google.FlatBuffers;

public struct WhisperMessageS2CEvt : IFlatbufferObject
{
  private Table __p;
  public ByteBuffer ByteBuffer { get { return __p.bb; } }
  public static void ValidateVersion() { FlatBufferConstants.FLATBUFFERS_23_5_26(); }
  public static WhisperMessageS2CEvt GetRootAsWhisperMessageS2CEvt(ByteBuffer _bb) { return GetRootAsWhisperMessageS2CEvt(_bb, new WhisperMessageS2CEvt()); }
  public static WhisperMessageS2CEvt GetRootAsWhisperMessageS2CEvt(ByteBuffer _bb, WhisperMessageS2CEvt obj) { return (obj.__assign(_bb.GetInt(_bb.Position) + _bb.Position, _bb)); }
  public void __init(int _i, ByteBuffer _bb) { __p = new Table(_i, _bb); }
  public WhisperMessageS2CEvt __assign(int _i, ByteBuffer _bb) { __init(_i, _bb); return this; }

  public ulong SenderId { get { int o = __p.__offset(4); return o != 0 ? __p.bb.GetUlong(o + __p.bb_pos) : (ulong)0; } }
  public byte ChatMetaData(int j) { int o = __p.__offset(6); return o != 0 ? __p.bb.Get(__p.__vector(o) + j * 1) : (byte)0; }
  public int ChatMetaDataLength { get { int o = __p.__offset(6); return o != 0 ? __p.__vector_len(o) : 0; } }
#if ENABLE_SPAN_T
  public Span<byte> GetChatMetaDataBytes() { return __p.__vector_as_span<byte>(6, 1); }
#else
  public ArraySegment<byte>? GetChatMetaDataBytes() { return __p.__vector_as_arraysegment(6); }
#endif
  public byte[] GetChatMetaDataArray() { return __p.__vector_as_array<byte>(6); }
  public string ChatMessage { get { int o = __p.__offset(8); return o != 0 ? __p.__string(o + __p.bb_pos) : null; } }
#if ENABLE_SPAN_T
  public Span<byte> GetChatMessageBytes() { return __p.__vector_as_span<byte>(8, 1); }
#else
  public ArraySegment<byte>? GetChatMessageBytes() { return __p.__vector_as_arraysegment(8); }
#endif
  public byte[] GetChatMessageArray() { return __p.__vector_as_array<byte>(8); }

  public static Offset<SF.Flat.Game.WhisperMessageS2CEvt> CreateWhisperMessageS2CEvt(FlatBufferBuilder builder,
      ulong sender_id = 0,
      VectorOffset chat_meta_dataOffset = default(VectorOffset),
      StringOffset chat_messageOffset = default(StringOffset)) {
    builder.StartTable(3);
    WhisperMessageS2CEvt.AddSenderId(builder, sender_id);
    WhisperMessageS2CEvt.AddChatMessage(builder, chat_messageOffset);
    WhisperMessageS2CEvt.AddChatMetaData(builder, chat_meta_dataOffset);
    return WhisperMessageS2CEvt.EndWhisperMessageS2CEvt(builder);
  }

  public static void StartWhisperMessageS2CEvt(FlatBufferBuilder builder) { builder.StartTable(3); }
  public static void AddSenderId(FlatBufferBuilder builder, ulong senderId) { builder.AddUlong(0, senderId, 0); }
  public static void AddChatMetaData(FlatBufferBuilder builder, VectorOffset chatMetaDataOffset) { builder.AddOffset(1, chatMetaDataOffset.Value, 0); }
  public static VectorOffset CreateChatMetaDataVector(FlatBufferBuilder builder, byte[] data) { builder.StartVector(1, data.Length, 1); for (int i = data.Length - 1; i >= 0; i--) builder.AddByte(data[i]); return builder.EndVector(); }
  public static VectorOffset CreateChatMetaDataVectorBlock(FlatBufferBuilder builder, byte[] data) { builder.StartVector(1, data.Length, 1); builder.Add(data); return builder.EndVector(); }
  public static VectorOffset CreateChatMetaDataVectorBlock(FlatBufferBuilder builder, ArraySegment<byte> data) { builder.StartVector(1, data.Count, 1); builder.Add(data); return builder.EndVector(); }
  public static VectorOffset CreateChatMetaDataVectorBlock(FlatBufferBuilder builder, IntPtr dataPtr, int sizeInBytes) { builder.StartVector(1, sizeInBytes, 1); builder.Add<byte>(dataPtr, sizeInBytes); return builder.EndVector(); }
  public static void StartChatMetaDataVector(FlatBufferBuilder builder, int numElems) { builder.StartVector(1, numElems, 1); }
  public static void AddChatMessage(FlatBufferBuilder builder, StringOffset chatMessageOffset) { builder.AddOffset(2, chatMessageOffset.Value, 0); }
  public static Offset<SF.Flat.Game.WhisperMessageS2CEvt> EndWhisperMessageS2CEvt(FlatBufferBuilder builder) {
    int o = builder.EndTable();
    return new Offset<SF.Flat.Game.WhisperMessageS2CEvt>(o);
  }
}


static public class WhisperMessageS2CEvtVerify
{
  static public bool Verify(Google.FlatBuffers.Verifier verifier, uint tablePos)
  {
    return verifier.VerifyTableStart(tablePos)
      && verifier.VerifyField(tablePos, 4 /*SenderId*/, 8 /*ulong*/, 8, false)
      && verifier.VerifyVectorOfData(tablePos, 6 /*ChatMetaData*/, 1 /*byte*/, false)
      && verifier.VerifyString(tablePos, 8 /*ChatMessage*/, false)
      && verifier.VerifyTableEnd(tablePos);
  }
}

}
