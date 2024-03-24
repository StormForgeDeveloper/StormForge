// <auto-generated>
//  automatically generated by the FlatBuffers compiler, do not modify
// </auto-generated>

namespace SF.Flat.Game
{

using global::System;
using global::System.Collections.Generic;
using global::Google.FlatBuffers;

public struct CreateCharacterRes : IFlatbufferObject
{
  private Table __p;
  public ByteBuffer ByteBuffer { get { return __p.bb; } }
  public static void ValidateVersion() { FlatBufferConstants.FLATBUFFERS_24_3_7(); }
  public static CreateCharacterRes GetRootAsCreateCharacterRes(ByteBuffer _bb) { return GetRootAsCreateCharacterRes(_bb, new CreateCharacterRes()); }
  public static CreateCharacterRes GetRootAsCreateCharacterRes(ByteBuffer _bb, CreateCharacterRes obj) { return (obj.__assign(_bb.GetInt(_bb.Position) + _bb.Position, _bb)); }
  public void __init(int _i, ByteBuffer _bb) { __p = new Table(_i, _bb); }
  public CreateCharacterRes __assign(int _i, ByteBuffer _bb) { __init(_i, _bb); return this; }

  public int Result { get { int o = __p.__offset(4); return o != 0 ? __p.bb.GetInt(o + __p.bb_pos) : (int)0; } }
  public SF.Flat.CharacterID? CharacterId { get { int o = __p.__offset(6); return o != 0 ? (SF.Flat.CharacterID?)(new SF.Flat.CharacterID()).__assign(o + __p.bb_pos, __p.bb) : null; } }

  public static void StartCreateCharacterRes(FlatBufferBuilder builder) { builder.StartTable(2); }
  public static void AddResult(FlatBufferBuilder builder, int result) { builder.AddInt(0, result, 0); }
  public static void AddCharacterId(FlatBufferBuilder builder, Offset<SF.Flat.CharacterID> characterIdOffset) { builder.AddStruct(1, characterIdOffset.Value, 0); }
  public static Offset<SF.Flat.Game.CreateCharacterRes> EndCreateCharacterRes(FlatBufferBuilder builder) {
    int o = builder.EndTable();
    return new Offset<SF.Flat.Game.CreateCharacterRes>(o);
  }
}


static public class CreateCharacterResVerify
{
  static public bool Verify(Google.FlatBuffers.Verifier verifier, uint tablePos)
  {
    return verifier.VerifyTableStart(tablePos)
      && verifier.VerifyField(tablePos, 4 /*Result*/, 4 /*int*/, 4, false)
      && verifier.VerifyField(tablePos, 6 /*CharacterId*/, 16 /*SF.Flat.CharacterID*/, 8, false)
      && verifier.VerifyTableEnd(tablePos);
  }
}

}
