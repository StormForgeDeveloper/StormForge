// <auto-generated>
//  automatically generated by the FlatBuffers compiler, do not modify
// </auto-generated>

namespace SF.Flat.Game
{

using global::System;
using global::System.Collections.Generic;
using global::Google.FlatBuffers;

public struct FindPlayerByPlayerIDCmd : IFlatbufferObject
{
  private Table __p;
  public ByteBuffer ByteBuffer { get { return __p.bb; } }
  public static void ValidateVersion() { FlatBufferConstants.FLATBUFFERS_23_5_26(); }
  public static FindPlayerByPlayerIDCmd GetRootAsFindPlayerByPlayerIDCmd(ByteBuffer _bb) { return GetRootAsFindPlayerByPlayerIDCmd(_bb, new FindPlayerByPlayerIDCmd()); }
  public static FindPlayerByPlayerIDCmd GetRootAsFindPlayerByPlayerIDCmd(ByteBuffer _bb, FindPlayerByPlayerIDCmd obj) { return (obj.__assign(_bb.GetInt(_bb.Position) + _bb.Position, _bb)); }
  public void __init(int _i, ByteBuffer _bb) { __p = new Table(_i, _bb); }
  public FindPlayerByPlayerIDCmd __assign(int _i, ByteBuffer _bb) { __init(_i, _bb); return this; }

  public ulong PlayerId { get { int o = __p.__offset(4); return o != 0 ? __p.bb.GetUlong(o + __p.bb_pos) : (ulong)0; } }

  public static Offset<SF.Flat.Game.FindPlayerByPlayerIDCmd> CreateFindPlayerByPlayerIDCmd(FlatBufferBuilder builder,
      ulong player_id = 0) {
    builder.StartTable(1);
    FindPlayerByPlayerIDCmd.AddPlayerId(builder, player_id);
    return FindPlayerByPlayerIDCmd.EndFindPlayerByPlayerIDCmd(builder);
  }

  public static void StartFindPlayerByPlayerIDCmd(FlatBufferBuilder builder) { builder.StartTable(1); }
  public static void AddPlayerId(FlatBufferBuilder builder, ulong playerId) { builder.AddUlong(0, playerId, 0); }
  public static Offset<SF.Flat.Game.FindPlayerByPlayerIDCmd> EndFindPlayerByPlayerIDCmd(FlatBufferBuilder builder) {
    int o = builder.EndTable();
    return new Offset<SF.Flat.Game.FindPlayerByPlayerIDCmd>(o);
  }
}


static public class FindPlayerByPlayerIDCmdVerify
{
  static public bool Verify(Google.FlatBuffers.Verifier verifier, uint tablePos)
  {
    return verifier.VerifyTableStart(tablePos)
      && verifier.VerifyField(tablePos, 4 /*PlayerId*/, 8 /*ulong*/, 8, false)
      && verifier.VerifyTableEnd(tablePos);
  }
}

}
