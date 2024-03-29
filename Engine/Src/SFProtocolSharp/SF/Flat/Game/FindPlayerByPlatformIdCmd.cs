// <auto-generated>
//  automatically generated by the FlatBuffers compiler, do not modify
// </auto-generated>

namespace SF.Flat.Game
{

using global::System;
using global::System.Collections.Generic;
using global::Google.FlatBuffers;

public struct FindPlayerByPlatformIdCmd : IFlatbufferObject
{
  private Table __p;
  public ByteBuffer ByteBuffer { get { return __p.bb; } }
  public static void ValidateVersion() { FlatBufferConstants.FLATBUFFERS_24_3_7(); }
  public static FindPlayerByPlatformIdCmd GetRootAsFindPlayerByPlatformIdCmd(ByteBuffer _bb) { return GetRootAsFindPlayerByPlatformIdCmd(_bb, new FindPlayerByPlatformIdCmd()); }
  public static FindPlayerByPlatformIdCmd GetRootAsFindPlayerByPlatformIdCmd(ByteBuffer _bb, FindPlayerByPlatformIdCmd obj) { return (obj.__assign(_bb.GetInt(_bb.Position) + _bb.Position, _bb)); }
  public void __init(int _i, ByteBuffer _bb) { __p = new Table(_i, _bb); }
  public FindPlayerByPlatformIdCmd __assign(int _i, ByteBuffer _bb) { __init(_i, _bb); return this; }

  public SF.Flat.PlayerPlatformID? PlatformPlayerId { get { int o = __p.__offset(4); return o != 0 ? (SF.Flat.PlayerPlatformID?)(new SF.Flat.PlayerPlatformID()).__assign(o + __p.bb_pos, __p.bb) : null; } }

  public static void StartFindPlayerByPlatformIdCmd(FlatBufferBuilder builder) { builder.StartTable(1); }
  public static void AddPlatformPlayerId(FlatBufferBuilder builder, Offset<SF.Flat.PlayerPlatformID> platformPlayerIdOffset) { builder.AddStruct(0, platformPlayerIdOffset.Value, 0); }
  public static Offset<SF.Flat.Game.FindPlayerByPlatformIdCmd> EndFindPlayerByPlatformIdCmd(FlatBufferBuilder builder) {
    int o = builder.EndTable();
    return new Offset<SF.Flat.Game.FindPlayerByPlatformIdCmd>(o);
  }
}


static public class FindPlayerByPlatformIdCmdVerify
{
  static public bool Verify(Google.FlatBuffers.Verifier verifier, uint tablePos)
  {
    return verifier.VerifyTableStart(tablePos)
      && verifier.VerifyField(tablePos, 4 /*PlatformPlayerId*/, 24 /*SF.Flat.PlayerPlatformID*/, 8, false)
      && verifier.VerifyTableEnd(tablePos);
  }
}

}
