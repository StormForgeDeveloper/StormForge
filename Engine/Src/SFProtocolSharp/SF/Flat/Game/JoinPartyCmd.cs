// <auto-generated>
//  automatically generated by the FlatBuffers compiler, do not modify
// </auto-generated>

namespace SF.Flat.Game
{

using global::System;
using global::System.Collections.Generic;
using global::Google.FlatBuffers;

public struct JoinPartyCmd : IFlatbufferObject
{
  private Table __p;
  public ByteBuffer ByteBuffer { get { return __p.bb; } }
  public static void ValidateVersion() { FlatBufferConstants.FLATBUFFERS_24_3_7(); }
  public static JoinPartyCmd GetRootAsJoinPartyCmd(ByteBuffer _bb) { return GetRootAsJoinPartyCmd(_bb, new JoinPartyCmd()); }
  public static JoinPartyCmd GetRootAsJoinPartyCmd(ByteBuffer _bb, JoinPartyCmd obj) { return (obj.__assign(_bb.GetInt(_bb.Position) + _bb.Position, _bb)); }
  public void __init(int _i, ByteBuffer _bb) { __p = new Table(_i, _bb); }
  public JoinPartyCmd __assign(int _i, ByteBuffer _bb) { __init(_i, _bb); return this; }

  public ulong PartyUid { get { int o = __p.__offset(4); return o != 0 ? __p.bb.GetUlong(o + __p.bb_pos) : (ulong)0; } }
  public ulong InviterId { get { int o = __p.__offset(6); return o != 0 ? __p.bb.GetUlong(o + __p.bb_pos) : (ulong)0; } }

  public static Offset<SF.Flat.Game.JoinPartyCmd> CreateJoinPartyCmd(FlatBufferBuilder builder,
      ulong party_uid = 0,
      ulong inviter_id = 0) {
    builder.StartTable(2);
    JoinPartyCmd.AddInviterId(builder, inviter_id);
    JoinPartyCmd.AddPartyUid(builder, party_uid);
    return JoinPartyCmd.EndJoinPartyCmd(builder);
  }

  public static void StartJoinPartyCmd(FlatBufferBuilder builder) { builder.StartTable(2); }
  public static void AddPartyUid(FlatBufferBuilder builder, ulong partyUid) { builder.AddUlong(0, partyUid, 0); }
  public static void AddInviterId(FlatBufferBuilder builder, ulong inviterId) { builder.AddUlong(1, inviterId, 0); }
  public static Offset<SF.Flat.Game.JoinPartyCmd> EndJoinPartyCmd(FlatBufferBuilder builder) {
    int o = builder.EndTable();
    return new Offset<SF.Flat.Game.JoinPartyCmd>(o);
  }
}


static public class JoinPartyCmdVerify
{
  static public bool Verify(Google.FlatBuffers.Verifier verifier, uint tablePos)
  {
    return verifier.VerifyTableStart(tablePos)
      && verifier.VerifyField(tablePos, 4 /*PartyUid*/, 8 /*ulong*/, 8, false)
      && verifier.VerifyField(tablePos, 6 /*InviterId*/, 8 /*ulong*/, 8, false)
      && verifier.VerifyTableEnd(tablePos);
  }
}

}