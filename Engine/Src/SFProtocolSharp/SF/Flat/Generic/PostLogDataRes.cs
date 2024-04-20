// <auto-generated>
//  automatically generated by the FlatBuffers compiler, do not modify
// </auto-generated>

namespace SF.Flat.Generic
{

using global::System;
using global::System.Collections.Generic;
using global::Google.FlatBuffers;

public struct PostLogDataRes : IFlatbufferObject
{
  private Table __p;
  public ByteBuffer ByteBuffer { get { return __p.bb; } }
  public static void ValidateVersion() { FlatBufferConstants.FLATBUFFERS_24_3_7(); }
  public static PostLogDataRes GetRootAsPostLogDataRes(ByteBuffer _bb) { return GetRootAsPostLogDataRes(_bb, new PostLogDataRes()); }
  public static PostLogDataRes GetRootAsPostLogDataRes(ByteBuffer _bb, PostLogDataRes obj) { return (obj.__assign(_bb.GetInt(_bb.Position) + _bb.Position, _bb)); }
  public static bool VerifyPostLogDataRes(ByteBuffer _bb) {Google.FlatBuffers.Verifier verifier = new Google.FlatBuffers.Verifier(_bb); return verifier.VerifyBuffer("", false, PostLogDataResVerify.Verify); }
  public void __init(int _i, ByteBuffer _bb) { __p = new Table(_i, _bb); }
  public PostLogDataRes __assign(int _i, ByteBuffer _bb) { __init(_i, _bb); return this; }

  public string DestLogChannel { get { int o = __p.__offset(4); return o != 0 ? __p.__string(o + __p.bb_pos) : null; } }
#if ENABLE_SPAN_T
  public Span<byte> GetDestLogChannelBytes() { return __p.__vector_as_span<byte>(4, 1); }
#else
  public ArraySegment<byte>? GetDestLogChannelBytes() { return __p.__vector_as_arraysegment(4); }
#endif
  public byte[] GetDestLogChannelArray() { return __p.__vector_as_array<byte>(4); }
  public byte MessageData(int j) { int o = __p.__offset(6); return o != 0 ? __p.bb.Get(__p.__vector(o) + j * 1) : (byte)0; }
  public int MessageDataLength { get { int o = __p.__offset(6); return o != 0 ? __p.__vector_len(o) : 0; } }
#if ENABLE_SPAN_T
  public Span<byte> GetMessageDataBytes() { return __p.__vector_as_span<byte>(6, 1); }
#else
  public ArraySegment<byte>? GetMessageDataBytes() { return __p.__vector_as_arraysegment(6); }
#endif
  public byte[] GetMessageDataArray() { return __p.__vector_as_array<byte>(6); }

  public static Offset<SF.Flat.Generic.PostLogDataRes> CreatePostLogDataRes(FlatBufferBuilder builder,
      StringOffset dest_log_channelOffset = default(StringOffset),
      VectorOffset message_dataOffset = default(VectorOffset)) {
    builder.StartTable(2);
    PostLogDataRes.AddMessageData(builder, message_dataOffset);
    PostLogDataRes.AddDestLogChannel(builder, dest_log_channelOffset);
    return PostLogDataRes.EndPostLogDataRes(builder);
  }

  public static void StartPostLogDataRes(FlatBufferBuilder builder) { builder.StartTable(2); }
  public static void AddDestLogChannel(FlatBufferBuilder builder, StringOffset destLogChannelOffset) { builder.AddOffset(0, destLogChannelOffset.Value, 0); }
  public static void AddMessageData(FlatBufferBuilder builder, VectorOffset messageDataOffset) { builder.AddOffset(1, messageDataOffset.Value, 0); }
  public static VectorOffset CreateMessageDataVector(FlatBufferBuilder builder, byte[] data) { builder.StartVector(1, data.Length, 1); for (int i = data.Length - 1; i >= 0; i--) builder.AddByte(data[i]); return builder.EndVector(); }
  public static VectorOffset CreateMessageDataVectorBlock(FlatBufferBuilder builder, byte[] data) { builder.StartVector(1, data.Length, 1); builder.Add(data); return builder.EndVector(); }
  public static VectorOffset CreateMessageDataVectorBlock(FlatBufferBuilder builder, ArraySegment<byte> data) { builder.StartVector(1, data.Count, 1); builder.Add(data); return builder.EndVector(); }
  public static VectorOffset CreateMessageDataVectorBlock(FlatBufferBuilder builder, IntPtr dataPtr, int sizeInBytes) { builder.StartVector(1, sizeInBytes, 1); builder.Add<byte>(dataPtr, sizeInBytes); return builder.EndVector(); }
  public static void StartMessageDataVector(FlatBufferBuilder builder, int numElems) { builder.StartVector(1, numElems, 1); }
  public static Offset<SF.Flat.Generic.PostLogDataRes> EndPostLogDataRes(FlatBufferBuilder builder) {
    int o = builder.EndTable();
    return new Offset<SF.Flat.Generic.PostLogDataRes>(o);
  }
  public static void FinishPostLogDataResBuffer(FlatBufferBuilder builder, Offset<SF.Flat.Generic.PostLogDataRes> offset) { builder.Finish(offset.Value); }
  public static void FinishSizePrefixedPostLogDataResBuffer(FlatBufferBuilder builder, Offset<SF.Flat.Generic.PostLogDataRes> offset) { builder.FinishSizePrefixed(offset.Value); }
}


static public class PostLogDataResVerify
{
  static public bool Verify(Google.FlatBuffers.Verifier verifier, uint tablePos)
  {
    return verifier.VerifyTableStart(tablePos)
      && verifier.VerifyString(tablePos, 4 /*DestLogChannel*/, false)
      && verifier.VerifyVectorOfData(tablePos, 6 /*MessageData*/, 1 /*byte*/, false)
      && verifier.VerifyTableEnd(tablePos);
  }
}

}
