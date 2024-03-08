// <auto-generated>
//  automatically generated by the FlatBuffers compiler, do not modify
// </auto-generated>

namespace SF.Flat.PlayInstance
{

using global::System;
using global::System.Collections.Generic;
using global::Google.FlatBuffers;

public struct ZoneChatS2CEvt : IFlatbufferObject
{
  private Table __p;
  public ByteBuffer ByteBuffer { get { return __p.bb; } }
  public static void ValidateVersion() { FlatBufferConstants.FLATBUFFERS_24_3_7(); }
  public static ZoneChatS2CEvt GetRootAsZoneChatS2CEvt(ByteBuffer _bb) { return GetRootAsZoneChatS2CEvt(_bb, new ZoneChatS2CEvt()); }
  public static ZoneChatS2CEvt GetRootAsZoneChatS2CEvt(ByteBuffer _bb, ZoneChatS2CEvt obj) { return (obj.__assign(_bb.GetInt(_bb.Position) + _bb.Position, _bb)); }
  public void __init(int _i, ByteBuffer _bb) { __p = new Table(_i, _bb); }
  public ZoneChatS2CEvt __assign(int _i, ByteBuffer _bb) { __init(_i, _bb); return this; }

  public ulong PlayInstanceUid { get { int o = __p.__offset(4); return o != 0 ? __p.bb.GetUlong(o + __p.bb_pos) : (ulong)0; } }
  public ulong SenderId { get { int o = __p.__offset(6); return o != 0 ? __p.bb.GetUlong(o + __p.bb_pos) : (ulong)0; } }
  public sbyte MessageType { get { int o = __p.__offset(8); return o != 0 ? __p.bb.GetSbyte(o + __p.bb_pos) : (sbyte)0; } }
  public byte ChatMetaData(int j) { int o = __p.__offset(10); return o != 0 ? __p.bb.Get(__p.__vector(o) + j * 1) : (byte)0; }
  public int ChatMetaDataLength { get { int o = __p.__offset(10); return o != 0 ? __p.__vector_len(o) : 0; } }
#if ENABLE_SPAN_T
  public Span<byte> GetChatMetaDataBytes() { return __p.__vector_as_span<byte>(10, 1); }
#else
  public ArraySegment<byte>? GetChatMetaDataBytes() { return __p.__vector_as_arraysegment(10); }
#endif
  public byte[] GetChatMetaDataArray() { return __p.__vector_as_array<byte>(10); }
  public string ChatMessage { get { int o = __p.__offset(12); return o != 0 ? __p.__string(o + __p.bb_pos) : null; } }
#if ENABLE_SPAN_T
  public Span<byte> GetChatMessageBytes() { return __p.__vector_as_span<byte>(12, 1); }
#else
  public ArraySegment<byte>? GetChatMessageBytes() { return __p.__vector_as_arraysegment(12); }
#endif
  public byte[] GetChatMessageArray() { return __p.__vector_as_array<byte>(12); }

  public static Offset<SF.Flat.PlayInstance.ZoneChatS2CEvt> CreateZoneChatS2CEvt(FlatBufferBuilder builder,
      ulong play_instance_uid = 0,
      ulong sender_id = 0,
      sbyte message_type = 0,
      VectorOffset chat_meta_dataOffset = default(VectorOffset),
      StringOffset chat_messageOffset = default(StringOffset)) {
    builder.StartTable(5);
    ZoneChatS2CEvt.AddSenderId(builder, sender_id);
    ZoneChatS2CEvt.AddPlayInstanceUid(builder, play_instance_uid);
    ZoneChatS2CEvt.AddChatMessage(builder, chat_messageOffset);
    ZoneChatS2CEvt.AddChatMetaData(builder, chat_meta_dataOffset);
    ZoneChatS2CEvt.AddMessageType(builder, message_type);
    return ZoneChatS2CEvt.EndZoneChatS2CEvt(builder);
  }

  public static void StartZoneChatS2CEvt(FlatBufferBuilder builder) { builder.StartTable(5); }
  public static void AddPlayInstanceUid(FlatBufferBuilder builder, ulong playInstanceUid) { builder.AddUlong(0, playInstanceUid, 0); }
  public static void AddSenderId(FlatBufferBuilder builder, ulong senderId) { builder.AddUlong(1, senderId, 0); }
  public static void AddMessageType(FlatBufferBuilder builder, sbyte messageType) { builder.AddSbyte(2, messageType, 0); }
  public static void AddChatMetaData(FlatBufferBuilder builder, VectorOffset chatMetaDataOffset) { builder.AddOffset(3, chatMetaDataOffset.Value, 0); }
  public static VectorOffset CreateChatMetaDataVector(FlatBufferBuilder builder, byte[] data) { builder.StartVector(1, data.Length, 1); for (int i = data.Length - 1; i >= 0; i--) builder.AddByte(data[i]); return builder.EndVector(); }
  public static VectorOffset CreateChatMetaDataVectorBlock(FlatBufferBuilder builder, byte[] data) { builder.StartVector(1, data.Length, 1); builder.Add(data); return builder.EndVector(); }
  public static VectorOffset CreateChatMetaDataVectorBlock(FlatBufferBuilder builder, ArraySegment<byte> data) { builder.StartVector(1, data.Count, 1); builder.Add(data); return builder.EndVector(); }
  public static VectorOffset CreateChatMetaDataVectorBlock(FlatBufferBuilder builder, IntPtr dataPtr, int sizeInBytes) { builder.StartVector(1, sizeInBytes, 1); builder.Add<byte>(dataPtr, sizeInBytes); return builder.EndVector(); }
  public static void StartChatMetaDataVector(FlatBufferBuilder builder, int numElems) { builder.StartVector(1, numElems, 1); }
  public static void AddChatMessage(FlatBufferBuilder builder, StringOffset chatMessageOffset) { builder.AddOffset(4, chatMessageOffset.Value, 0); }
  public static Offset<SF.Flat.PlayInstance.ZoneChatS2CEvt> EndZoneChatS2CEvt(FlatBufferBuilder builder) {
    int o = builder.EndTable();
    return new Offset<SF.Flat.PlayInstance.ZoneChatS2CEvt>(o);
  }
}


static public class ZoneChatS2CEvtVerify
{
  static public bool Verify(Google.FlatBuffers.Verifier verifier, uint tablePos)
  {
    return verifier.VerifyTableStart(tablePos)
      && verifier.VerifyField(tablePos, 4 /*PlayInstanceUid*/, 8 /*ulong*/, 8, false)
      && verifier.VerifyField(tablePos, 6 /*SenderId*/, 8 /*ulong*/, 8, false)
      && verifier.VerifyField(tablePos, 8 /*MessageType*/, 1 /*sbyte*/, 1, false)
      && verifier.VerifyVectorOfData(tablePos, 10 /*ChatMetaData*/, 1 /*byte*/, false)
      && verifier.VerifyString(tablePos, 12 /*ChatMessage*/, false)
      && verifier.VerifyTableEnd(tablePos);
  }
}

}