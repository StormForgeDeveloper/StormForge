// <auto-generated>
//  automatically generated by the FlatBuffers compiler, do not modify
// </auto-generated>

namespace SF.Flat.Game
{

using global::System;
using global::System.Collections.Generic;
using global::Google.FlatBuffers;

public struct RemoveFriendCmd : IFlatbufferObject
{
  private Table __p;
  public ByteBuffer ByteBuffer { get { return __p.bb; } }
  public static void ValidateVersion() { FlatBufferConstants.FLATBUFFERS_23_5_26(); }
  public static RemoveFriendCmd GetRootAsRemoveFriendCmd(ByteBuffer _bb) { return GetRootAsRemoveFriendCmd(_bb, new RemoveFriendCmd()); }
  public static RemoveFriendCmd GetRootAsRemoveFriendCmd(ByteBuffer _bb, RemoveFriendCmd obj) { return (obj.__assign(_bb.GetInt(_bb.Position) + _bb.Position, _bb)); }
  public void __init(int _i, ByteBuffer _bb) { __p = new Table(_i, _bb); }
  public RemoveFriendCmd __assign(int _i, ByteBuffer _bb) { __init(_i, _bb); return this; }

  public ulong FriendId { get { int o = __p.__offset(4); return o != 0 ? __p.bb.GetUlong(o + __p.bb_pos) : (ulong)0; } }

  public static Offset<SF.Flat.Game.RemoveFriendCmd> CreateRemoveFriendCmd(FlatBufferBuilder builder,
      ulong friend_id = 0) {
    builder.StartTable(1);
    RemoveFriendCmd.AddFriendId(builder, friend_id);
    return RemoveFriendCmd.EndRemoveFriendCmd(builder);
  }

  public static void StartRemoveFriendCmd(FlatBufferBuilder builder) { builder.StartTable(1); }
  public static void AddFriendId(FlatBufferBuilder builder, ulong friendId) { builder.AddUlong(0, friendId, 0); }
  public static Offset<SF.Flat.Game.RemoveFriendCmd> EndRemoveFriendCmd(FlatBufferBuilder builder) {
    int o = builder.EndTable();
    return new Offset<SF.Flat.Game.RemoveFriendCmd>(o);
  }
}


static public class RemoveFriendCmdVerify
{
  static public bool Verify(Google.FlatBuffers.Verifier verifier, uint tablePos)
  {
    return verifier.VerifyTableStart(tablePos)
      && verifier.VerifyField(tablePos, 4 /*FriendId*/, 8 /*ulong*/, 8, false)
      && verifier.VerifyTableEnd(tablePos);
  }
}

}
