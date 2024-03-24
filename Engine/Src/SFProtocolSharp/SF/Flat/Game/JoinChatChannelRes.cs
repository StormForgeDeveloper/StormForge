// <auto-generated>
//  automatically generated by the FlatBuffers compiler, do not modify
// </auto-generated>

namespace SF.Flat.Game
{

using global::System;
using global::System.Collections.Generic;
using global::Google.FlatBuffers;

public struct JoinChatChannelRes : IFlatbufferObject
{
  private Table __p;
  public ByteBuffer ByteBuffer { get { return __p.bb; } }
  public static void ValidateVersion() { FlatBufferConstants.FLATBUFFERS_24_3_7(); }
  public static JoinChatChannelRes GetRootAsJoinChatChannelRes(ByteBuffer _bb) { return GetRootAsJoinChatChannelRes(_bb, new JoinChatChannelRes()); }
  public static JoinChatChannelRes GetRootAsJoinChatChannelRes(ByteBuffer _bb, JoinChatChannelRes obj) { return (obj.__assign(_bb.GetInt(_bb.Position) + _bb.Position, _bb)); }
  public void __init(int _i, ByteBuffer _bb) { __p = new Table(_i, _bb); }
  public JoinChatChannelRes __assign(int _i, ByteBuffer _bb) { __init(_i, _bb); return this; }

  public int Result { get { int o = __p.__offset(4); return o != 0 ? __p.bb.GetInt(o + __p.bb_pos) : (int)0; } }
  public SF.Flat.EntityUID? ChatUid { get { int o = __p.__offset(6); return o != 0 ? (SF.Flat.EntityUID?)(new SF.Flat.EntityUID()).__assign(o + __p.bb_pos, __p.bb) : null; } }
  public SF.Flat.AccountID? ChannelLeaderId { get { int o = __p.__offset(8); return o != 0 ? (SF.Flat.AccountID?)(new SF.Flat.AccountID()).__assign(o + __p.bb_pos, __p.bb) : null; } }

  public static void StartJoinChatChannelRes(FlatBufferBuilder builder) { builder.StartTable(3); }
  public static void AddResult(FlatBufferBuilder builder, int result) { builder.AddInt(0, result, 0); }
  public static void AddChatUid(FlatBufferBuilder builder, Offset<SF.Flat.EntityUID> chatUidOffset) { builder.AddStruct(1, chatUidOffset.Value, 0); }
  public static void AddChannelLeaderId(FlatBufferBuilder builder, Offset<SF.Flat.AccountID> channelLeaderIdOffset) { builder.AddStruct(2, channelLeaderIdOffset.Value, 0); }
  public static Offset<SF.Flat.Game.JoinChatChannelRes> EndJoinChatChannelRes(FlatBufferBuilder builder) {
    int o = builder.EndTable();
    return new Offset<SF.Flat.Game.JoinChatChannelRes>(o);
  }
}


static public class JoinChatChannelResVerify
{
  static public bool Verify(Google.FlatBuffers.Verifier verifier, uint tablePos)
  {
    return verifier.VerifyTableStart(tablePos)
      && verifier.VerifyField(tablePos, 4 /*Result*/, 4 /*int*/, 4, false)
      && verifier.VerifyField(tablePos, 6 /*ChatUid*/, 4 /*SF.Flat.EntityUID*/, 4, false)
      && verifier.VerifyField(tablePos, 8 /*ChannelLeaderId*/, 16 /*SF.Flat.AccountID*/, 8, false)
      && verifier.VerifyTableEnd(tablePos);
  }
}

}
