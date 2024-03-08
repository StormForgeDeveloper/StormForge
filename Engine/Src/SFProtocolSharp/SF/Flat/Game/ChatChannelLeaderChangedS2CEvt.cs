// <auto-generated>
//  automatically generated by the FlatBuffers compiler, do not modify
// </auto-generated>

namespace SF.Flat.Game
{

using global::System;
using global::System.Collections.Generic;
using global::Google.FlatBuffers;

public struct ChatChannelLeaderChangedS2CEvt : IFlatbufferObject
{
  private Table __p;
  public ByteBuffer ByteBuffer { get { return __p.bb; } }
  public static void ValidateVersion() { FlatBufferConstants.FLATBUFFERS_24_3_7(); }
  public static ChatChannelLeaderChangedS2CEvt GetRootAsChatChannelLeaderChangedS2CEvt(ByteBuffer _bb) { return GetRootAsChatChannelLeaderChangedS2CEvt(_bb, new ChatChannelLeaderChangedS2CEvt()); }
  public static ChatChannelLeaderChangedS2CEvt GetRootAsChatChannelLeaderChangedS2CEvt(ByteBuffer _bb, ChatChannelLeaderChangedS2CEvt obj) { return (obj.__assign(_bb.GetInt(_bb.Position) + _bb.Position, _bb)); }
  public void __init(int _i, ByteBuffer _bb) { __p = new Table(_i, _bb); }
  public ChatChannelLeaderChangedS2CEvt __assign(int _i, ByteBuffer _bb) { __init(_i, _bb); return this; }

  public ulong ChatUid { get { int o = __p.__offset(4); return o != 0 ? __p.bb.GetUlong(o + __p.bb_pos) : (ulong)0; } }
  public ulong NewLeaderId { get { int o = __p.__offset(6); return o != 0 ? __p.bb.GetUlong(o + __p.bb_pos) : (ulong)0; } }

  public static Offset<SF.Flat.Game.ChatChannelLeaderChangedS2CEvt> CreateChatChannelLeaderChangedS2CEvt(FlatBufferBuilder builder,
      ulong chat_uid = 0,
      ulong new_leader_id = 0) {
    builder.StartTable(2);
    ChatChannelLeaderChangedS2CEvt.AddNewLeaderId(builder, new_leader_id);
    ChatChannelLeaderChangedS2CEvt.AddChatUid(builder, chat_uid);
    return ChatChannelLeaderChangedS2CEvt.EndChatChannelLeaderChangedS2CEvt(builder);
  }

  public static void StartChatChannelLeaderChangedS2CEvt(FlatBufferBuilder builder) { builder.StartTable(2); }
  public static void AddChatUid(FlatBufferBuilder builder, ulong chatUid) { builder.AddUlong(0, chatUid, 0); }
  public static void AddNewLeaderId(FlatBufferBuilder builder, ulong newLeaderId) { builder.AddUlong(1, newLeaderId, 0); }
  public static Offset<SF.Flat.Game.ChatChannelLeaderChangedS2CEvt> EndChatChannelLeaderChangedS2CEvt(FlatBufferBuilder builder) {
    int o = builder.EndTable();
    return new Offset<SF.Flat.Game.ChatChannelLeaderChangedS2CEvt>(o);
  }
}


static public class ChatChannelLeaderChangedS2CEvtVerify
{
  static public bool Verify(Google.FlatBuffers.Verifier verifier, uint tablePos)
  {
    return verifier.VerifyTableStart(tablePos)
      && verifier.VerifyField(tablePos, 4 /*ChatUid*/, 8 /*ulong*/, 8, false)
      && verifier.VerifyField(tablePos, 6 /*NewLeaderId*/, 8 /*ulong*/, 8, false)
      && verifier.VerifyTableEnd(tablePos);
  }
}

}