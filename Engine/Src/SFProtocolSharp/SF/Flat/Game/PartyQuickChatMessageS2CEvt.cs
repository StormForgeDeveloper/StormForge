// <auto-generated>
//  automatically generated by the FlatBuffers compiler, do not modify
// </auto-generated>

namespace SF.Flat.Game
{

using global::System;
using global::System.Collections.Generic;
using global::Google.FlatBuffers;

public struct PartyQuickChatMessageS2CEvt : IFlatbufferObject
{
  private Table __p;
  public ByteBuffer ByteBuffer { get { return __p.bb; } }
  public static void ValidateVersion() { FlatBufferConstants.FLATBUFFERS_23_5_26(); }
  public static PartyQuickChatMessageS2CEvt GetRootAsPartyQuickChatMessageS2CEvt(ByteBuffer _bb) { return GetRootAsPartyQuickChatMessageS2CEvt(_bb, new PartyQuickChatMessageS2CEvt()); }
  public static PartyQuickChatMessageS2CEvt GetRootAsPartyQuickChatMessageS2CEvt(ByteBuffer _bb, PartyQuickChatMessageS2CEvt obj) { return (obj.__assign(_bb.GetInt(_bb.Position) + _bb.Position, _bb)); }
  public void __init(int _i, ByteBuffer _bb) { __p = new Table(_i, _bb); }
  public PartyQuickChatMessageS2CEvt __assign(int _i, ByteBuffer _bb) { __init(_i, _bb); return this; }

  public ulong SenderId { get { int o = __p.__offset(4); return o != 0 ? __p.bb.GetUlong(o + __p.bb_pos) : (ulong)0; } }
  public uint QuickChatId { get { int o = __p.__offset(6); return o != 0 ? __p.bb.GetUint(o + __p.bb_pos) : (uint)0; } }

  public static Offset<SF.Flat.Game.PartyQuickChatMessageS2CEvt> CreatePartyQuickChatMessageS2CEvt(FlatBufferBuilder builder,
      ulong sender_id = 0,
      uint quick_chat_id = 0) {
    builder.StartTable(2);
    PartyQuickChatMessageS2CEvt.AddSenderId(builder, sender_id);
    PartyQuickChatMessageS2CEvt.AddQuickChatId(builder, quick_chat_id);
    return PartyQuickChatMessageS2CEvt.EndPartyQuickChatMessageS2CEvt(builder);
  }

  public static void StartPartyQuickChatMessageS2CEvt(FlatBufferBuilder builder) { builder.StartTable(2); }
  public static void AddSenderId(FlatBufferBuilder builder, ulong senderId) { builder.AddUlong(0, senderId, 0); }
  public static void AddQuickChatId(FlatBufferBuilder builder, uint quickChatId) { builder.AddUint(1, quickChatId, 0); }
  public static Offset<SF.Flat.Game.PartyQuickChatMessageS2CEvt> EndPartyQuickChatMessageS2CEvt(FlatBufferBuilder builder) {
    int o = builder.EndTable();
    return new Offset<SF.Flat.Game.PartyQuickChatMessageS2CEvt>(o);
  }
}


static public class PartyQuickChatMessageS2CEvtVerify
{
  static public bool Verify(Google.FlatBuffers.Verifier verifier, uint tablePos)
  {
    return verifier.VerifyTableStart(tablePos)
      && verifier.VerifyField(tablePos, 4 /*SenderId*/, 8 /*ulong*/, 8, false)
      && verifier.VerifyField(tablePos, 6 /*QuickChatId*/, 4 /*uint*/, 4, false)
      && verifier.VerifyTableEnd(tablePos);
  }
}

}
