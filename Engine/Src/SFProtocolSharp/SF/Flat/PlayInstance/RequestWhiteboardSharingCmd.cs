// <auto-generated>
//  automatically generated by the FlatBuffers compiler, do not modify
// </auto-generated>

namespace SF.Flat.PlayInstance
{

using global::System;
using global::System.Collections.Generic;
using global::Google.FlatBuffers;

public struct RequestWhiteboardSharingCmd : IFlatbufferObject
{
  private Table __p;
  public ByteBuffer ByteBuffer { get { return __p.bb; } }
  public static void ValidateVersion() { FlatBufferConstants.FLATBUFFERS_24_3_7(); }
  public static RequestWhiteboardSharingCmd GetRootAsRequestWhiteboardSharingCmd(ByteBuffer _bb) { return GetRootAsRequestWhiteboardSharingCmd(_bb, new RequestWhiteboardSharingCmd()); }
  public static RequestWhiteboardSharingCmd GetRootAsRequestWhiteboardSharingCmd(ByteBuffer _bb, RequestWhiteboardSharingCmd obj) { return (obj.__assign(_bb.GetInt(_bb.Position) + _bb.Position, _bb)); }
  public void __init(int _i, ByteBuffer _bb) { __p = new Table(_i, _bb); }
  public RequestWhiteboardSharingCmd __assign(int _i, ByteBuffer _bb) { __init(_i, _bb); return this; }

  public ulong PlayInstanceUid { get { int o = __p.__offset(4); return o != 0 ? __p.bb.GetUlong(o + __p.bb_pos) : (ulong)0; } }
  public ulong PlayerId { get { int o = __p.__offset(6); return o != 0 ? __p.bb.GetUlong(o + __p.bb_pos) : (ulong)0; } }
  public ulong TargetPlayerId { get { int o = __p.__offset(8); return o != 0 ? __p.bb.GetUlong(o + __p.bb_pos) : (ulong)0; } }
  public byte WhiteboardInfo(int j) { int o = __p.__offset(10); return o != 0 ? __p.bb.Get(__p.__vector(o) + j * 1) : (byte)0; }
  public int WhiteboardInfoLength { get { int o = __p.__offset(10); return o != 0 ? __p.__vector_len(o) : 0; } }
#if ENABLE_SPAN_T
  public Span<byte> GetWhiteboardInfoBytes() { return __p.__vector_as_span<byte>(10, 1); }
#else
  public ArraySegment<byte>? GetWhiteboardInfoBytes() { return __p.__vector_as_arraysegment(10); }
#endif
  public byte[] GetWhiteboardInfoArray() { return __p.__vector_as_array<byte>(10); }

  public static Offset<SF.Flat.PlayInstance.RequestWhiteboardSharingCmd> CreateRequestWhiteboardSharingCmd(FlatBufferBuilder builder,
      ulong play_instance_uid = 0,
      ulong player_id = 0,
      ulong target_player_id = 0,
      VectorOffset whiteboard_infoOffset = default(VectorOffset)) {
    builder.StartTable(4);
    RequestWhiteboardSharingCmd.AddTargetPlayerId(builder, target_player_id);
    RequestWhiteboardSharingCmd.AddPlayerId(builder, player_id);
    RequestWhiteboardSharingCmd.AddPlayInstanceUid(builder, play_instance_uid);
    RequestWhiteboardSharingCmd.AddWhiteboardInfo(builder, whiteboard_infoOffset);
    return RequestWhiteboardSharingCmd.EndRequestWhiteboardSharingCmd(builder);
  }

  public static void StartRequestWhiteboardSharingCmd(FlatBufferBuilder builder) { builder.StartTable(4); }
  public static void AddPlayInstanceUid(FlatBufferBuilder builder, ulong playInstanceUid) { builder.AddUlong(0, playInstanceUid, 0); }
  public static void AddPlayerId(FlatBufferBuilder builder, ulong playerId) { builder.AddUlong(1, playerId, 0); }
  public static void AddTargetPlayerId(FlatBufferBuilder builder, ulong targetPlayerId) { builder.AddUlong(2, targetPlayerId, 0); }
  public static void AddWhiteboardInfo(FlatBufferBuilder builder, VectorOffset whiteboardInfoOffset) { builder.AddOffset(3, whiteboardInfoOffset.Value, 0); }
  public static VectorOffset CreateWhiteboardInfoVector(FlatBufferBuilder builder, byte[] data) { builder.StartVector(1, data.Length, 1); for (int i = data.Length - 1; i >= 0; i--) builder.AddByte(data[i]); return builder.EndVector(); }
  public static VectorOffset CreateWhiteboardInfoVectorBlock(FlatBufferBuilder builder, byte[] data) { builder.StartVector(1, data.Length, 1); builder.Add(data); return builder.EndVector(); }
  public static VectorOffset CreateWhiteboardInfoVectorBlock(FlatBufferBuilder builder, ArraySegment<byte> data) { builder.StartVector(1, data.Count, 1); builder.Add(data); return builder.EndVector(); }
  public static VectorOffset CreateWhiteboardInfoVectorBlock(FlatBufferBuilder builder, IntPtr dataPtr, int sizeInBytes) { builder.StartVector(1, sizeInBytes, 1); builder.Add<byte>(dataPtr, sizeInBytes); return builder.EndVector(); }
  public static void StartWhiteboardInfoVector(FlatBufferBuilder builder, int numElems) { builder.StartVector(1, numElems, 1); }
  public static Offset<SF.Flat.PlayInstance.RequestWhiteboardSharingCmd> EndRequestWhiteboardSharingCmd(FlatBufferBuilder builder) {
    int o = builder.EndTable();
    return new Offset<SF.Flat.PlayInstance.RequestWhiteboardSharingCmd>(o);
  }
}


static public class RequestWhiteboardSharingCmdVerify
{
  static public bool Verify(Google.FlatBuffers.Verifier verifier, uint tablePos)
  {
    return verifier.VerifyTableStart(tablePos)
      && verifier.VerifyField(tablePos, 4 /*PlayInstanceUid*/, 8 /*ulong*/, 8, false)
      && verifier.VerifyField(tablePos, 6 /*PlayerId*/, 8 /*ulong*/, 8, false)
      && verifier.VerifyField(tablePos, 8 /*TargetPlayerId*/, 8 /*ulong*/, 8, false)
      && verifier.VerifyVectorOfData(tablePos, 10 /*WhiteboardInfo*/, 1 /*byte*/, false)
      && verifier.VerifyTableEnd(tablePos);
  }
}

}
