// <auto-generated>
//  automatically generated by the FlatBuffers compiler, do not modify
// </auto-generated>

namespace SF.Flat.PlayInstance
{

using global::System;
using global::System.Collections.Generic;
using global::Google.FlatBuffers;

public struct CloseWhiteboardSharingCmd : IFlatbufferObject
{
  private Table __p;
  public ByteBuffer ByteBuffer { get { return __p.bb; } }
  public static void ValidateVersion() { FlatBufferConstants.FLATBUFFERS_24_3_7(); }
  public static CloseWhiteboardSharingCmd GetRootAsCloseWhiteboardSharingCmd(ByteBuffer _bb) { return GetRootAsCloseWhiteboardSharingCmd(_bb, new CloseWhiteboardSharingCmd()); }
  public static CloseWhiteboardSharingCmd GetRootAsCloseWhiteboardSharingCmd(ByteBuffer _bb, CloseWhiteboardSharingCmd obj) { return (obj.__assign(_bb.GetInt(_bb.Position) + _bb.Position, _bb)); }
  public void __init(int _i, ByteBuffer _bb) { __p = new Table(_i, _bb); }
  public CloseWhiteboardSharingCmd __assign(int _i, ByteBuffer _bb) { __init(_i, _bb); return this; }

  public ulong PlayInstanceUid { get { int o = __p.__offset(4); return o != 0 ? __p.bb.GetUlong(o + __p.bb_pos) : (ulong)0; } }
  public ulong PlayerId { get { int o = __p.__offset(6); return o != 0 ? __p.bb.GetUlong(o + __p.bb_pos) : (ulong)0; } }

  public static Offset<SF.Flat.PlayInstance.CloseWhiteboardSharingCmd> CreateCloseWhiteboardSharingCmd(FlatBufferBuilder builder,
      ulong play_instance_uid = 0,
      ulong player_id = 0) {
    builder.StartTable(2);
    CloseWhiteboardSharingCmd.AddPlayerId(builder, player_id);
    CloseWhiteboardSharingCmd.AddPlayInstanceUid(builder, play_instance_uid);
    return CloseWhiteboardSharingCmd.EndCloseWhiteboardSharingCmd(builder);
  }

  public static void StartCloseWhiteboardSharingCmd(FlatBufferBuilder builder) { builder.StartTable(2); }
  public static void AddPlayInstanceUid(FlatBufferBuilder builder, ulong playInstanceUid) { builder.AddUlong(0, playInstanceUid, 0); }
  public static void AddPlayerId(FlatBufferBuilder builder, ulong playerId) { builder.AddUlong(1, playerId, 0); }
  public static Offset<SF.Flat.PlayInstance.CloseWhiteboardSharingCmd> EndCloseWhiteboardSharingCmd(FlatBufferBuilder builder) {
    int o = builder.EndTable();
    return new Offset<SF.Flat.PlayInstance.CloseWhiteboardSharingCmd>(o);
  }
}


static public class CloseWhiteboardSharingCmdVerify
{
  static public bool Verify(Google.FlatBuffers.Verifier verifier, uint tablePos)
  {
    return verifier.VerifyTableStart(tablePos)
      && verifier.VerifyField(tablePos, 4 /*PlayInstanceUid*/, 8 /*ulong*/, 8, false)
      && verifier.VerifyField(tablePos, 6 /*PlayerId*/, 8 /*ulong*/, 8, false)
      && verifier.VerifyTableEnd(tablePos);
  }
}

}