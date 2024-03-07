// <auto-generated>
//  automatically generated by the FlatBuffers compiler, do not modify
// </auto-generated>

namespace SF.Flat.Game
{

using global::System;
using global::System.Collections.Generic;
using global::Google.FlatBuffers;

public struct FindPlayerByPlatformUserNameRes : IFlatbufferObject
{
  private Table __p;
  public ByteBuffer ByteBuffer { get { return __p.bb; } }
  public static void ValidateVersion() { FlatBufferConstants.FLATBUFFERS_23_5_26(); }
  public static FindPlayerByPlatformUserNameRes GetRootAsFindPlayerByPlatformUserNameRes(ByteBuffer _bb) { return GetRootAsFindPlayerByPlatformUserNameRes(_bb, new FindPlayerByPlatformUserNameRes()); }
  public static FindPlayerByPlatformUserNameRes GetRootAsFindPlayerByPlatformUserNameRes(ByteBuffer _bb, FindPlayerByPlatformUserNameRes obj) { return (obj.__assign(_bb.GetInt(_bb.Position) + _bb.Position, _bb)); }
  public void __init(int _i, ByteBuffer _bb) { __p = new Table(_i, _bb); }
  public FindPlayerByPlatformUserNameRes __assign(int _i, ByteBuffer _bb) { __init(_i, _bb); return this; }

  public uint Result { get { int o = __p.__offset(4); return o != 0 ? __p.bb.GetUint(o + __p.bb_pos) : (uint)0; } }
  public ulong PlayerId { get { int o = __p.__offset(6); return o != 0 ? __p.bb.GetUlong(o + __p.bb_pos) : (ulong)0; } }
  public SF.Flat.PlayerPlatformID? PlayerPlatformId { get { int o = __p.__offset(8); return o != 0 ? (SF.Flat.PlayerPlatformID?)(new SF.Flat.PlayerPlatformID()).__assign(o + __p.bb_pos, __p.bb) : null; } }

  public static void StartFindPlayerByPlatformUserNameRes(FlatBufferBuilder builder) { builder.StartTable(3); }
  public static void AddResult(FlatBufferBuilder builder, uint result) { builder.AddUint(0, result, 0); }
  public static void AddPlayerId(FlatBufferBuilder builder, ulong playerId) { builder.AddUlong(1, playerId, 0); }
  public static void AddPlayerPlatformId(FlatBufferBuilder builder, Offset<SF.Flat.PlayerPlatformID> playerPlatformIdOffset) { builder.AddStruct(2, playerPlatformIdOffset.Value, 0); }
  public static Offset<SF.Flat.Game.FindPlayerByPlatformUserNameRes> EndFindPlayerByPlatformUserNameRes(FlatBufferBuilder builder) {
    int o = builder.EndTable();
    return new Offset<SF.Flat.Game.FindPlayerByPlatformUserNameRes>(o);
  }
}


static public class FindPlayerByPlatformUserNameResVerify
{
  static public bool Verify(Google.FlatBuffers.Verifier verifier, uint tablePos)
  {
    return verifier.VerifyTableStart(tablePos)
      && verifier.VerifyField(tablePos, 4 /*Result*/, 4 /*uint*/, 4, false)
      && verifier.VerifyField(tablePos, 6 /*PlayerId*/, 8 /*ulong*/, 8, false)
      && verifier.VerifyField(tablePos, 8 /*PlayerPlatformId*/, 16 /*SF.Flat.PlayerPlatformID*/, 8, false)
      && verifier.VerifyTableEnd(tablePos);
  }
}

}
