// <auto-generated>
//  automatically generated by the FlatBuffers compiler, do not modify
// </auto-generated>

namespace SF.Flat.Game
{

using global::System;
using global::System.Collections.Generic;
using global::Google.FlatBuffers;

public struct JoinGameInstanceCmd : IFlatbufferObject
{
  private Table __p;
  public ByteBuffer ByteBuffer { get { return __p.bb; } }
  public static void ValidateVersion() { FlatBufferConstants.FLATBUFFERS_23_5_26(); }
  public static JoinGameInstanceCmd GetRootAsJoinGameInstanceCmd(ByteBuffer _bb) { return GetRootAsJoinGameInstanceCmd(_bb, new JoinGameInstanceCmd()); }
  public static JoinGameInstanceCmd GetRootAsJoinGameInstanceCmd(ByteBuffer _bb, JoinGameInstanceCmd obj) { return (obj.__assign(_bb.GetInt(_bb.Position) + _bb.Position, _bb)); }
  public void __init(int _i, ByteBuffer _bb) { __p = new Table(_i, _bb); }
  public JoinGameInstanceCmd __assign(int _i, ByteBuffer _bb) { __init(_i, _bb); return this; }

  public ulong InsUid { get { int o = __p.__offset(4); return o != 0 ? __p.bb.GetUlong(o + __p.bb_pos) : (ulong)0; } }

  public static Offset<SF.Flat.Game.JoinGameInstanceCmd> CreateJoinGameInstanceCmd(FlatBufferBuilder builder,
      ulong ins_uid = 0) {
    builder.StartTable(1);
    JoinGameInstanceCmd.AddInsUid(builder, ins_uid);
    return JoinGameInstanceCmd.EndJoinGameInstanceCmd(builder);
  }

  public static void StartJoinGameInstanceCmd(FlatBufferBuilder builder) { builder.StartTable(1); }
  public static void AddInsUid(FlatBufferBuilder builder, ulong insUid) { builder.AddUlong(0, insUid, 0); }
  public static Offset<SF.Flat.Game.JoinGameInstanceCmd> EndJoinGameInstanceCmd(FlatBufferBuilder builder) {
    int o = builder.EndTable();
    return new Offset<SF.Flat.Game.JoinGameInstanceCmd>(o);
  }
}


static public class JoinGameInstanceCmdVerify
{
  static public bool Verify(Google.FlatBuffers.Verifier verifier, uint tablePos)
  {
    return verifier.VerifyTableStart(tablePos)
      && verifier.VerifyField(tablePos, 4 /*InsUid*/, 8 /*ulong*/, 8, false)
      && verifier.VerifyTableEnd(tablePos);
  }
}

}
