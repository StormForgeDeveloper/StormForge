// <auto-generated>
//  automatically generated by the FlatBuffers compiler, do not modify
// </auto-generated>

namespace SF.Flat.Game
{

using global::System;
using global::System.Collections.Generic;
using global::Google.FlatBuffers;

public struct InviteFriendRes : IFlatbufferObject
{
  private Table __p;
  public ByteBuffer ByteBuffer { get { return __p.bb; } }
  public static void ValidateVersion() { FlatBufferConstants.FLATBUFFERS_24_3_7(); }
  public static InviteFriendRes GetRootAsInviteFriendRes(ByteBuffer _bb) { return GetRootAsInviteFriendRes(_bb, new InviteFriendRes()); }
  public static InviteFriendRes GetRootAsInviteFriendRes(ByteBuffer _bb, InviteFriendRes obj) { return (obj.__assign(_bb.GetInt(_bb.Position) + _bb.Position, _bb)); }
  public void __init(int _i, ByteBuffer _bb) { __p = new Table(_i, _bb); }
  public InviteFriendRes __assign(int _i, ByteBuffer _bb) { __init(_i, _bb); return this; }

  public int Result { get { int o = __p.__offset(4); return o != 0 ? __p.bb.GetInt(o + __p.bb_pos) : (int)0; } }

  public static Offset<SF.Flat.Game.InviteFriendRes> CreateInviteFriendRes(FlatBufferBuilder builder,
      int result = 0) {
    builder.StartTable(1);
    InviteFriendRes.AddResult(builder, result);
    return InviteFriendRes.EndInviteFriendRes(builder);
  }

  public static void StartInviteFriendRes(FlatBufferBuilder builder) { builder.StartTable(1); }
  public static void AddResult(FlatBufferBuilder builder, int result) { builder.AddInt(0, result, 0); }
  public static Offset<SF.Flat.Game.InviteFriendRes> EndInviteFriendRes(FlatBufferBuilder builder) {
    int o = builder.EndTable();
    return new Offset<SF.Flat.Game.InviteFriendRes>(o);
  }
}


static public class InviteFriendResVerify
{
  static public bool Verify(Google.FlatBuffers.Verifier verifier, uint tablePos)
  {
    return verifier.VerifyTableStart(tablePos)
      && verifier.VerifyField(tablePos, 4 /*Result*/, 4 /*int*/, 4, false)
      && verifier.VerifyTableEnd(tablePos);
  }
}

}
