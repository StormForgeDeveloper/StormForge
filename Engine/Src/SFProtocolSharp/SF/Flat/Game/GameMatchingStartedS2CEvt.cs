// <auto-generated>
//  automatically generated by the FlatBuffers compiler, do not modify
// </auto-generated>

namespace SF.Flat.Game
{

using global::System;
using global::System.Collections.Generic;
using global::Google.FlatBuffers;

public struct GameMatchingStartedS2CEvt : IFlatbufferObject
{
  private Table __p;
  public ByteBuffer ByteBuffer { get { return __p.bb; } }
  public static void ValidateVersion() { FlatBufferConstants.FLATBUFFERS_23_5_26(); }
  public static GameMatchingStartedS2CEvt GetRootAsGameMatchingStartedS2CEvt(ByteBuffer _bb) { return GetRootAsGameMatchingStartedS2CEvt(_bb, new GameMatchingStartedS2CEvt()); }
  public static GameMatchingStartedS2CEvt GetRootAsGameMatchingStartedS2CEvt(ByteBuffer _bb, GameMatchingStartedS2CEvt obj) { return (obj.__assign(_bb.GetInt(_bb.Position) + _bb.Position, _bb)); }
  public void __init(int _i, ByteBuffer _bb) { __p = new Table(_i, _bb); }
  public GameMatchingStartedS2CEvt __assign(int _i, ByteBuffer _bb) { __init(_i, _bb); return this; }


  public static void StartGameMatchingStartedS2CEvt(FlatBufferBuilder builder) { builder.StartTable(0); }
  public static Offset<SF.Flat.Game.GameMatchingStartedS2CEvt> EndGameMatchingStartedS2CEvt(FlatBufferBuilder builder) {
    int o = builder.EndTable();
    return new Offset<SF.Flat.Game.GameMatchingStartedS2CEvt>(o);
  }
}


static public class GameMatchingStartedS2CEvtVerify
{
  static public bool Verify(Google.FlatBuffers.Verifier verifier, uint tablePos)
  {
    return verifier.VerifyTableStart(tablePos)
      && verifier.VerifyTableEnd(tablePos);
  }
}

}
