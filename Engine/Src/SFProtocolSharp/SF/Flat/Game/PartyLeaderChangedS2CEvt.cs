// <auto-generated>
//  automatically generated by the FlatBuffers compiler, do not modify
// </auto-generated>

namespace SF.Flat.Game
{

using global::System;
using global::System.Collections.Generic;
using global::Google.FlatBuffers;

public struct PartyLeaderChangedS2CEvt : IFlatbufferObject
{
  private Table __p;
  public ByteBuffer ByteBuffer { get { return __p.bb; } }
  public static void ValidateVersion() { FlatBufferConstants.FLATBUFFERS_23_5_26(); }
  public static PartyLeaderChangedS2CEvt GetRootAsPartyLeaderChangedS2CEvt(ByteBuffer _bb) { return GetRootAsPartyLeaderChangedS2CEvt(_bb, new PartyLeaderChangedS2CEvt()); }
  public static PartyLeaderChangedS2CEvt GetRootAsPartyLeaderChangedS2CEvt(ByteBuffer _bb, PartyLeaderChangedS2CEvt obj) { return (obj.__assign(_bb.GetInt(_bb.Position) + _bb.Position, _bb)); }
  public void __init(int _i, ByteBuffer _bb) { __p = new Table(_i, _bb); }
  public PartyLeaderChangedS2CEvt __assign(int _i, ByteBuffer _bb) { __init(_i, _bb); return this; }

  public ulong PartyUid { get { int o = __p.__offset(4); return o != 0 ? __p.bb.GetUlong(o + __p.bb_pos) : (ulong)0; } }
  public ulong NewLeaderId { get { int o = __p.__offset(6); return o != 0 ? __p.bb.GetUlong(o + __p.bb_pos) : (ulong)0; } }

  public static Offset<SF.Flat.Game.PartyLeaderChangedS2CEvt> CreatePartyLeaderChangedS2CEvt(FlatBufferBuilder builder,
      ulong party_uid = 0,
      ulong new_leader_id = 0) {
    builder.StartTable(2);
    PartyLeaderChangedS2CEvt.AddNewLeaderId(builder, new_leader_id);
    PartyLeaderChangedS2CEvt.AddPartyUid(builder, party_uid);
    return PartyLeaderChangedS2CEvt.EndPartyLeaderChangedS2CEvt(builder);
  }

  public static void StartPartyLeaderChangedS2CEvt(FlatBufferBuilder builder) { builder.StartTable(2); }
  public static void AddPartyUid(FlatBufferBuilder builder, ulong partyUid) { builder.AddUlong(0, partyUid, 0); }
  public static void AddNewLeaderId(FlatBufferBuilder builder, ulong newLeaderId) { builder.AddUlong(1, newLeaderId, 0); }
  public static Offset<SF.Flat.Game.PartyLeaderChangedS2CEvt> EndPartyLeaderChangedS2CEvt(FlatBufferBuilder builder) {
    int o = builder.EndTable();
    return new Offset<SF.Flat.Game.PartyLeaderChangedS2CEvt>(o);
  }
}


static public class PartyLeaderChangedS2CEvtVerify
{
  static public bool Verify(Google.FlatBuffers.Verifier verifier, uint tablePos)
  {
    return verifier.VerifyTableStart(tablePos)
      && verifier.VerifyField(tablePos, 4 /*PartyUid*/, 8 /*ulong*/, 8, false)
      && verifier.VerifyField(tablePos, 6 /*NewLeaderId*/, 8 /*ulong*/, 8, false)
      && verifier.VerifyTableEnd(tablePos);
  }
}

}
