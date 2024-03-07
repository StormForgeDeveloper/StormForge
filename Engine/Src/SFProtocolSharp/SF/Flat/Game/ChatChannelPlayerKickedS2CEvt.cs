// <auto-generated>
//  automatically generated by the FlatBuffers compiler, do not modify
// </auto-generated>

namespace SF.Flat.Game
{

using global::System;
using global::System.Collections.Generic;
using global::Google.FlatBuffers;

public struct ChatChannelPlayerKickedS2CEvt : IFlatbufferObject
{
  private Table __p;
  public ByteBuffer ByteBuffer { get { return __p.bb; } }
  public static void ValidateVersion() { FlatBufferConstants.FLATBUFFERS_23_5_26(); }
  public static ChatChannelPlayerKickedS2CEvt GetRootAsChatChannelPlayerKickedS2CEvt(ByteBuffer _bb) { return GetRootAsChatChannelPlayerKickedS2CEvt(_bb, new ChatChannelPlayerKickedS2CEvt()); }
  public static ChatChannelPlayerKickedS2CEvt GetRootAsChatChannelPlayerKickedS2CEvt(ByteBuffer _bb, ChatChannelPlayerKickedS2CEvt obj) { return (obj.__assign(_bb.GetInt(_bb.Position) + _bb.Position, _bb)); }
  public void __init(int _i, ByteBuffer _bb) { __p = new Table(_i, _bb); }
  public ChatChannelPlayerKickedS2CEvt __assign(int _i, ByteBuffer _bb) { __init(_i, _bb); return this; }

  public ulong ChatUid { get { int o = __p.__offset(4); return o != 0 ? __p.bb.GetUlong(o + __p.bb_pos) : (ulong)0; } }
  public ulong KickedPlayerId { get { int o = __p.__offset(6); return o != 0 ? __p.bb.GetUlong(o + __p.bb_pos) : (ulong)0; } }

  public static Offset<SF.Flat.Game.ChatChannelPlayerKickedS2CEvt> CreateChatChannelPlayerKickedS2CEvt(FlatBufferBuilder builder,
      ulong chat_uid = 0,
      ulong kicked_player_id = 0) {
    builder.StartTable(2);
    ChatChannelPlayerKickedS2CEvt.AddKickedPlayerId(builder, kicked_player_id);
    ChatChannelPlayerKickedS2CEvt.AddChatUid(builder, chat_uid);
    return ChatChannelPlayerKickedS2CEvt.EndChatChannelPlayerKickedS2CEvt(builder);
  }

  public static void StartChatChannelPlayerKickedS2CEvt(FlatBufferBuilder builder) { builder.StartTable(2); }
  public static void AddChatUid(FlatBufferBuilder builder, ulong chatUid) { builder.AddUlong(0, chatUid, 0); }
  public static void AddKickedPlayerId(FlatBufferBuilder builder, ulong kickedPlayerId) { builder.AddUlong(1, kickedPlayerId, 0); }
  public static Offset<SF.Flat.Game.ChatChannelPlayerKickedS2CEvt> EndChatChannelPlayerKickedS2CEvt(FlatBufferBuilder builder) {
    int o = builder.EndTable();
    return new Offset<SF.Flat.Game.ChatChannelPlayerKickedS2CEvt>(o);
  }
}


static public class ChatChannelPlayerKickedS2CEvtVerify
{
  static public bool Verify(Google.FlatBuffers.Verifier verifier, uint tablePos)
  {
    return verifier.VerifyTableStart(tablePos)
      && verifier.VerifyField(tablePos, 4 /*ChatUid*/, 8 /*ulong*/, 8, false)
      && verifier.VerifyField(tablePos, 6 /*KickedPlayerId*/, 8 /*ulong*/, 8, false)
      && verifier.VerifyTableEnd(tablePos);
  }
}

}
