// <auto-generated>
//  automatically generated by the FlatBuffers compiler, do not modify
// </auto-generated>

namespace SF.Flat.Game
{

using global::System;
using global::System.Collections.Generic;
using global::Google.FlatBuffers;

public struct FindPlayerByCharacterNameRes : IFlatbufferObject
{
  private Table __p;
  public ByteBuffer ByteBuffer { get { return __p.bb; } }
  public static void ValidateVersion() { FlatBufferConstants.FLATBUFFERS_24_3_7(); }
  public static FindPlayerByCharacterNameRes GetRootAsFindPlayerByCharacterNameRes(ByteBuffer _bb) { return GetRootAsFindPlayerByCharacterNameRes(_bb, new FindPlayerByCharacterNameRes()); }
  public static FindPlayerByCharacterNameRes GetRootAsFindPlayerByCharacterNameRes(ByteBuffer _bb, FindPlayerByCharacterNameRes obj) { return (obj.__assign(_bb.GetInt(_bb.Position) + _bb.Position, _bb)); }
  public void __init(int _i, ByteBuffer _bb) { __p = new Table(_i, _bb); }
  public FindPlayerByCharacterNameRes __assign(int _i, ByteBuffer _bb) { __init(_i, _bb); return this; }

  public SF.Flat.AccountID? PlayerId { get { int o = __p.__offset(4); return o != 0 ? (SF.Flat.AccountID?)(new SF.Flat.AccountID()).__assign(o + __p.bb_pos, __p.bb) : null; } }

  public static void StartFindPlayerByCharacterNameRes(FlatBufferBuilder builder) { builder.StartTable(1); }
  public static void AddPlayerId(FlatBufferBuilder builder, Offset<SF.Flat.AccountID> playerIdOffset) { builder.AddStruct(0, playerIdOffset.Value, 0); }
  public static Offset<SF.Flat.Game.FindPlayerByCharacterNameRes> EndFindPlayerByCharacterNameRes(FlatBufferBuilder builder) {
    int o = builder.EndTable();
    return new Offset<SF.Flat.Game.FindPlayerByCharacterNameRes>(o);
  }
}


static public class FindPlayerByCharacterNameResVerify
{
  static public bool Verify(Google.FlatBuffers.Verifier verifier, uint tablePos)
  {
    return verifier.VerifyTableStart(tablePos)
      && verifier.VerifyField(tablePos, 4 /*PlayerId*/, 16 /*SF.Flat.AccountID*/, 8, false)
      && verifier.VerifyTableEnd(tablePos);
  }
}

}
