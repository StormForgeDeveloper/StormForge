// <auto-generated>
//  automatically generated by the FlatBuffers compiler, do not modify
// </auto-generated>

namespace SF.Flat.Game
{

using global::System;
using global::System.Collections.Generic;
using global::Google.FlatBuffers;

public struct PartyKickPlayerRes : IFlatbufferObject
{
  private Table __p;
  public ByteBuffer ByteBuffer { get { return __p.bb; } }
  public static void ValidateVersion() { FlatBufferConstants.FLATBUFFERS_24_3_7(); }
  public static PartyKickPlayerRes GetRootAsPartyKickPlayerRes(ByteBuffer _bb) { return GetRootAsPartyKickPlayerRes(_bb, new PartyKickPlayerRes()); }
  public static PartyKickPlayerRes GetRootAsPartyKickPlayerRes(ByteBuffer _bb, PartyKickPlayerRes obj) { return (obj.__assign(_bb.GetInt(_bb.Position) + _bb.Position, _bb)); }
  public void __init(int _i, ByteBuffer _bb) { __p = new Table(_i, _bb); }
  public PartyKickPlayerRes __assign(int _i, ByteBuffer _bb) { __init(_i, _bb); return this; }


  public static void StartPartyKickPlayerRes(FlatBufferBuilder builder) { builder.StartTable(0); }
  public static Offset<SF.Flat.Game.PartyKickPlayerRes> EndPartyKickPlayerRes(FlatBufferBuilder builder) {
    int o = builder.EndTable();
    return new Offset<SF.Flat.Game.PartyKickPlayerRes>(o);
  }
}


static public class PartyKickPlayerResVerify
{
  static public bool Verify(Google.FlatBuffers.Verifier verifier, uint tablePos)
  {
    return verifier.VerifyTableStart(tablePos)
      && verifier.VerifyTableEnd(tablePos);
  }
}

}
