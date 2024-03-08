// <auto-generated>
//  automatically generated by the FlatBuffers compiler, do not modify
// </auto-generated>

namespace SF.Flat.PlayInstance
{

using global::System;
using global::System.Collections.Generic;
using global::Google.FlatBuffers;

public struct UpdateWhiteboardSharingLogEntryCmd : IFlatbufferObject
{
  private Table __p;
  public ByteBuffer ByteBuffer { get { return __p.bb; } }
  public static void ValidateVersion() { FlatBufferConstants.FLATBUFFERS_24_3_7(); }
  public static UpdateWhiteboardSharingLogEntryCmd GetRootAsUpdateWhiteboardSharingLogEntryCmd(ByteBuffer _bb) { return GetRootAsUpdateWhiteboardSharingLogEntryCmd(_bb, new UpdateWhiteboardSharingLogEntryCmd()); }
  public static UpdateWhiteboardSharingLogEntryCmd GetRootAsUpdateWhiteboardSharingLogEntryCmd(ByteBuffer _bb, UpdateWhiteboardSharingLogEntryCmd obj) { return (obj.__assign(_bb.GetInt(_bb.Position) + _bb.Position, _bb)); }
  public void __init(int _i, ByteBuffer _bb) { __p = new Table(_i, _bb); }
  public UpdateWhiteboardSharingLogEntryCmd __assign(int _i, ByteBuffer _bb) { __init(_i, _bb); return this; }

  public ulong PlayInstanceUid { get { int o = __p.__offset(4); return o != 0 ? __p.bb.GetUlong(o + __p.bb_pos) : (ulong)0; } }
  public ulong PlayerId { get { int o = __p.__offset(6); return o != 0 ? __p.bb.GetUlong(o + __p.bb_pos) : (ulong)0; } }
  public byte LogEntry(int j) { int o = __p.__offset(8); return o != 0 ? __p.bb.Get(__p.__vector(o) + j * 1) : (byte)0; }
  public int LogEntryLength { get { int o = __p.__offset(8); return o != 0 ? __p.__vector_len(o) : 0; } }
#if ENABLE_SPAN_T
  public Span<byte> GetLogEntryBytes() { return __p.__vector_as_span<byte>(8, 1); }
#else
  public ArraySegment<byte>? GetLogEntryBytes() { return __p.__vector_as_arraysegment(8); }
#endif
  public byte[] GetLogEntryArray() { return __p.__vector_as_array<byte>(8); }

  public static Offset<SF.Flat.PlayInstance.UpdateWhiteboardSharingLogEntryCmd> CreateUpdateWhiteboardSharingLogEntryCmd(FlatBufferBuilder builder,
      ulong play_instance_uid = 0,
      ulong player_id = 0,
      VectorOffset log_entryOffset = default(VectorOffset)) {
    builder.StartTable(3);
    UpdateWhiteboardSharingLogEntryCmd.AddPlayerId(builder, player_id);
    UpdateWhiteboardSharingLogEntryCmd.AddPlayInstanceUid(builder, play_instance_uid);
    UpdateWhiteboardSharingLogEntryCmd.AddLogEntry(builder, log_entryOffset);
    return UpdateWhiteboardSharingLogEntryCmd.EndUpdateWhiteboardSharingLogEntryCmd(builder);
  }

  public static void StartUpdateWhiteboardSharingLogEntryCmd(FlatBufferBuilder builder) { builder.StartTable(3); }
  public static void AddPlayInstanceUid(FlatBufferBuilder builder, ulong playInstanceUid) { builder.AddUlong(0, playInstanceUid, 0); }
  public static void AddPlayerId(FlatBufferBuilder builder, ulong playerId) { builder.AddUlong(1, playerId, 0); }
  public static void AddLogEntry(FlatBufferBuilder builder, VectorOffset logEntryOffset) { builder.AddOffset(2, logEntryOffset.Value, 0); }
  public static VectorOffset CreateLogEntryVector(FlatBufferBuilder builder, byte[] data) { builder.StartVector(1, data.Length, 1); for (int i = data.Length - 1; i >= 0; i--) builder.AddByte(data[i]); return builder.EndVector(); }
  public static VectorOffset CreateLogEntryVectorBlock(FlatBufferBuilder builder, byte[] data) { builder.StartVector(1, data.Length, 1); builder.Add(data); return builder.EndVector(); }
  public static VectorOffset CreateLogEntryVectorBlock(FlatBufferBuilder builder, ArraySegment<byte> data) { builder.StartVector(1, data.Count, 1); builder.Add(data); return builder.EndVector(); }
  public static VectorOffset CreateLogEntryVectorBlock(FlatBufferBuilder builder, IntPtr dataPtr, int sizeInBytes) { builder.StartVector(1, sizeInBytes, 1); builder.Add<byte>(dataPtr, sizeInBytes); return builder.EndVector(); }
  public static void StartLogEntryVector(FlatBufferBuilder builder, int numElems) { builder.StartVector(1, numElems, 1); }
  public static Offset<SF.Flat.PlayInstance.UpdateWhiteboardSharingLogEntryCmd> EndUpdateWhiteboardSharingLogEntryCmd(FlatBufferBuilder builder) {
    int o = builder.EndTable();
    return new Offset<SF.Flat.PlayInstance.UpdateWhiteboardSharingLogEntryCmd>(o);
  }
}


static public class UpdateWhiteboardSharingLogEntryCmdVerify
{
  static public bool Verify(Google.FlatBuffers.Verifier verifier, uint tablePos)
  {
    return verifier.VerifyTableStart(tablePos)
      && verifier.VerifyField(tablePos, 4 /*PlayInstanceUid*/, 8 /*ulong*/, 8, false)
      && verifier.VerifyField(tablePos, 6 /*PlayerId*/, 8 /*ulong*/, 8, false)
      && verifier.VerifyVectorOfData(tablePos, 8 /*LogEntry*/, 1 /*byte*/, false)
      && verifier.VerifyTableEnd(tablePos);
  }
}

}
