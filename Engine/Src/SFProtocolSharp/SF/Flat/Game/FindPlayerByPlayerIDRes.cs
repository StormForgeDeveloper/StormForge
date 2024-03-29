// <auto-generated>
//  automatically generated by the FlatBuffers compiler, do not modify
// </auto-generated>

namespace SF.Flat.Game
{

using global::System;
using global::System.Collections.Generic;
using global::Google.FlatBuffers;

public struct FindPlayerByPlayerIDRes : IFlatbufferObject
{
  private Table __p;
  public ByteBuffer ByteBuffer { get { return __p.bb; } }
  public static void ValidateVersion() { FlatBufferConstants.FLATBUFFERS_24_3_7(); }
  public static FindPlayerByPlayerIDRes GetRootAsFindPlayerByPlayerIDRes(ByteBuffer _bb) { return GetRootAsFindPlayerByPlayerIDRes(_bb, new FindPlayerByPlayerIDRes()); }
  public static FindPlayerByPlayerIDRes GetRootAsFindPlayerByPlayerIDRes(ByteBuffer _bb, FindPlayerByPlayerIDRes obj) { return (obj.__assign(_bb.GetInt(_bb.Position) + _bb.Position, _bb)); }
  public void __init(int _i, ByteBuffer _bb) { __p = new Table(_i, _bb); }
  public FindPlayerByPlayerIDRes __assign(int _i, ByteBuffer _bb) { __init(_i, _bb); return this; }

  public SF.Flat.PlayerInformation? Player { get { int o = __p.__offset(4); return o != 0 ? (SF.Flat.PlayerInformation?)(new SF.Flat.PlayerInformation()).__assign(__p.__indirect(o + __p.bb_pos), __p.bb) : null; } }

  public static Offset<SF.Flat.Game.FindPlayerByPlayerIDRes> CreateFindPlayerByPlayerIDRes(FlatBufferBuilder builder,
      Offset<SF.Flat.PlayerInformation> playerOffset = default(Offset<SF.Flat.PlayerInformation>)) {
    builder.StartTable(1);
    FindPlayerByPlayerIDRes.AddPlayer(builder, playerOffset);
    return FindPlayerByPlayerIDRes.EndFindPlayerByPlayerIDRes(builder);
  }

  public static void StartFindPlayerByPlayerIDRes(FlatBufferBuilder builder) { builder.StartTable(1); }
  public static void AddPlayer(FlatBufferBuilder builder, Offset<SF.Flat.PlayerInformation> playerOffset) { builder.AddOffset(0, playerOffset.Value, 0); }
  public static Offset<SF.Flat.Game.FindPlayerByPlayerIDRes> EndFindPlayerByPlayerIDRes(FlatBufferBuilder builder) {
    int o = builder.EndTable();
    return new Offset<SF.Flat.Game.FindPlayerByPlayerIDRes>(o);
  }
}


static public class FindPlayerByPlayerIDResVerify
{
  static public bool Verify(Google.FlatBuffers.Verifier verifier, uint tablePos)
  {
    return verifier.VerifyTableStart(tablePos)
      && verifier.VerifyTable(tablePos, 4 /*Player*/, SF.Flat.PlayerInformationVerify.Verify, false)
      && verifier.VerifyTableEnd(tablePos);
  }
}

}
